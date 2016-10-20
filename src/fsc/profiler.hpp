/*******************************************************************************
 *
 * RDTSC based micro-benchmark macros.
 * Programming Techniques for Scientific Simulations II, ETH Zürich, 2015
 * For free use, no rights reserved.
 *
 ******************************************************************************/

#ifndef FSC_PROFILER_HEADER
#define FSC_PROFILER_HEADER

#include <fsc/profiler/accumulator.hpp>
#include <fsc/profiler/rdtsc_timer.hpp>

#include <assert.h>
#include <algorithm>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <vector>

// We can use MIB_DEBUG to catch common errors like stopping the wrong tag
// or violating the unique name constraint

#ifdef MIB_TAGS
#define MIB_REGISTER_MODE
// make sure the user also specifies MIB_TEST
#ifndef MIB_TEST
#error "Please specify MIB_TEST if you define MIB_TAGS"
#endif
#endif

namespace fsc {
    namespace detail {
        enum class msm_mod : uint8_t { cycle = 0, nsec = 1 };

        struct node_struct {
            using res_type = double;
            using pair_type = std::pair<res_type, res_type>;
            node_struct()
                : name(""), parent(nullptr), current_run(pair_type(0, 0)) {}
            std::string name;
            node_struct* parent;
            pair_type current_run;

            res_type cost(msm_mod const& mod) const {
                return acc[int(mod)].mean() * acc[int(mod)].count();
            }
            void sort(msm_mod const& mod) {
                std::sort(
                    children.begin(), children.end(),
                    [&mod](detail::node_struct* a, detail::node_struct* b) {
                        return a->cost(mod) > b->cost(mod);
                    });
                for(auto& c : children) {
                    c->sort(mod);
                }
            }

            accumulator<res_type> acc[2];
            std::vector<node_struct*> children;
        };

        inline rdtsc_timer& get_timer() {
            static rdtsc_timer t;
            return t;
        }
    }  // end namespace detail

    class profiler {
        using res_type = detail::node_struct::res_type;
        using pair_type = detail::node_struct::pair_type;

    public:
        profiler() : timer_(detail::get_timer()) {
            sentinel_.name = "sentinel_root";
            stack_.push_back(&sentinel_);
        }
        profiler(profiler const&) = delete;

        inline void start(std::string const& name) {
            process_start(name, get_cyc());
        }
        inline void next(std::string const& name) {
            process_stop(stack_.back()->name, get_cyc());
            process_start(name, pair_type(0, 0));
        }
        inline void stop(std::string const& name) {
            process_stop(name, get_cyc());
        }
        void print_tree() const {
            auto prec = std::cout.precision();
            std::cout << "Usage of rdtsc (CPU bound):" << std::endl;
            std::vector<bool> marker;
            std::string msm_mod_str =
                mod_ == detail::msm_mod::cycle ? "cycle_mean" : "nsec_mean";
            std::cout << std::setw(8 + 14) << "┬ (% of parent) name"
                      << std::string(80 - 53, ' ') << std::right
                      << std::setw(10) << msm_mod_str << std::setw(10 + 1)
                      << "spread" << std::setw(10) << "run_cnt" << std::endl;
            auto i = sentinel_.children.size();
            auto mod = int(mod_);

            for(auto const& p : sentinel_.children) {
                --i;
                print_tree_helper(p, i == 0, marker,
                                  mod ? sentinel_.current_run.second
                                      : sentinel_.current_run.first,
                                  p->cost(mod_));
            }
            std::cout.precision(prec);
        }
        void set_mod(std::string const& smod) {
            sentinel_.sort(mod_);

            if(smod == "cycle")
                mod_ = detail::msm_mod::cycle;
            else if(smod == "nsec" or smod == "")
                mod_ = detail::msm_mod::nsec;
            else {
                std::stringstream ss;
                ss << "fsc::profiler: invalid mode '" << smod << "'";
                throw std::runtime_error(ss.str());
            }
        }
        void register_help() const {
            std::cout
                << "To change to register mode, paste the following lines "
                << "before the include of fsc/profiler.hpp:" << std::endl;

            std::stringstream ss;
            for(auto const& a : tree_) {
                if(&a != &*tree_.begin()) ss << ", ";
                ss << a.first;
            }

            std::cout << "#define MIB_TAGS " << ss.str() << std::endl;
            std::cout << "#define MIB_TEST " << ss.str() << std::endl;
        }
        void save(std::string file) const {
            while(true) {  // make sure no accidental overwrite can happen
                std::ifstream ifs(file);
                if(ifs.is_open()) {
                    ifs.close();
                    std::cout << "file '" << file << "' already exists"
                              << std::endl;
                    std::cout << "type 'o' for overwrite or new filename: "
                              << std::endl;
                    std::string choice;
                    std::cin >> choice;
                    if(choice != "o")
                        file = choice;
                    else
                        break;
                } else
                    break;
            }
            std::ofstream ofs(file);

            std::string smod =
                mod_ == detail::msm_mod::cycle ? "cycle" : "nsec";
            ofs << "parent name " << smod << "_mean " << smod << "_std calls"
                << std::endl;
            auto mod = int(mod_);
            for(auto const& p : tree_) {
                auto node = p.second;
                auto count = node.acc[mod].count();
                ofs << node.parent->name << " " << node.name << " "
                    << node.acc[mod].mean() << " "
                    << (count > 1 ? node.acc[mod].std() : 0) << " " << count
                    << std::endl;
            }

            ofs.close();
        }

    private:
        pair_type get_cyc() {
            auto cyc = timer_.cycles();
            auto nsec = timer_.nsec();
            timer_.start();
            timer_.stop();
            cyc -= timer_.cycles();
            return pair_type(cyc, nsec);
        }
        void process_start(std::string const& name, pair_type const& msm) {
#ifdef MIB_DEBUG
            if(name.find(" ") != std::string::npos) {
                std::stringstream ss;
                ss << "fsc::profiler: name '" << name
                   << "' invalid! no spaces allowed";
                throw std::runtime_error(ss.str());
            }
            if(find_if(stack_.begin(), stack_.end(),
                       [&name](detail::node_struct* XX) {
                           return XX->name == name;
                       }) != stack_.end()) {
                std::stringstream ss;
                ss << "fsc::profiler: the tag '" << name
                   << "' was started a while still active. The tags have to be "
                      "unique!";
                throw std::runtime_error(ss.str());
            }
#endif  // MIB_DEBUG

            static bool first_start = true;
            if(first_start)
                first_start = false;
            else
                for(auto ptr : stack_) {
                    ptr->current_run.first += msm.first;
                    ptr->current_run.second += msm.second;
                }

            tree_[name].name = name;
            tree_[name].parent = stack_.back();
            stack_.push_back(&tree_[name]);
            if(std::find(tree_[name].parent->children.begin(),
                         tree_[name].parent->children.end(),
                         &tree_[name]) == tree_[name].parent->children.end())
                tree_[name].parent->children.push_back(&tree_[name]);
        }
        void process_stop(std::string const& name, pair_type const& msm) {
#ifdef MIB_DEBUG
            if(name != stack_.back()->name) {
                std::stringstream ss;
                ss << "fsc::profiler: stopped '" << name << "' instead of '"
                   << stack_.back()->name << "'";
                throw std::runtime_error(ss.str());
            }
#else
            (void)name;  // removes unused warning
#endif  // MIB_DEBUG

            for(auto ptr : stack_) {
                ptr->current_run.first += msm.first;
                ptr->current_run.second += msm.second;
            }

            auto node = stack_.back();
            node->acc[0] << node->current_run.first;
            node->acc[1] << node->current_run.second;
            node->current_run = pair_type(0, 0);
            stack_.pop_back();
        }
        void print_tree_helper(const detail::node_struct* parent,
                               const bool lastchild, std::vector<bool>& marker,
                               const res_type& parent_time,
                               const res_type& self_time) const {
            auto mod = int(mod_);
            for(auto c : marker) {
                if(!c) {
                    std::cout << "│" << std::string(4 - 1, ' ');

                } else
                    std::cout << std::string(4, ' ');
            }
            int whitespace = 80 - 8 - 12 - 30 - 2 - 1 - 4 * marker.size();
            if(whitespace < 0) whitespace = 0;
            std::cout << (lastchild ? "└" : "├") << "─" << std::setw(3)
                      << int(std::round(100 * self_time / parent_time)) << "% "
                      << std::left << std::setw(12) << parent->name
                      << std::right << std::string(whitespace, ' ')
                      << std::fixed << "[" << std::setw(10)
                      << std::setprecision(parent->acc[mod].mean() < 10 ? 1 : 0)
                      << parent->acc[mod].mean() << std::setw(10)
                      << 100 *
                             (parent->acc[mod].std() / parent->acc[mod].mean())
                      << "%" << std::setw(10) << std::right
                      << parent->acc[mod].count() << "]" << std::defaultfloat
                      << std::endl;
            auto i = parent->children.size();
            marker.push_back(lastchild);

            res_type child_cost = 0;
            for(auto const& p : parent->children) {
                --i;
                child_cost += p->cost(mod_);
                print_tree_helper(p, i == 0, marker, self_time,
                                  int64_t(p->cost(mod_)));
            }
            if(parent->children.size()) {
                uint missing = (1 - child_cost / self_time) * 100;
                if(missing != 0) {
                    for(auto c : marker) {
                        if(!c) {
                            std::cout << "│" << std::string(4 - 1, ' ');

                        } else
                            std::cout << std::string(4, ' ');
                    }
                    std::cout << "  " << std::setw(3) << missing << "% missing"
                              << std::endl;
                }
            }
            marker.pop_back();
        }

    public:
        rdtsc_timer& timer_;

    private:
        detail::msm_mod mod_ = detail::msm_mod::cycle;

        detail::node_struct sentinel_;
        std::vector<detail::node_struct*> stack_;
        std::map<std::string, detail::node_struct> tree_;
    };

    namespace detail {
        inline profiler& get_profiler() {
            static profiler p;
            return p;
        }
        static auto& mib_prof = get_profiler();

        namespace dont_even_ask {  // state of the art... trust me ;P
            inline void fct() { (void)mib_prof; }
        }  // end namespace dont_even_ask

    }  // end namespace detail

}  // end namespace fsc

#ifdef MIB_REGISTER_MODE
//=================== macro/MTP tag system ===================
#include <fsc/profiler/generic_macros.hpp>

namespace fsc {
    namespace detail {

        // just wraps the autogenerated tag-structs into another template
        // bc for inheritance the struct needs to have a body, but I want
        // the tags to have no body
        template <typename T>
        struct mib_tpl_wrap {};

        // find out if one of a variadic number of bool is true (c++17 folding
        // soon...)
        template <typename... ARGS>
        struct mib_any_true;
        template <>
        struct mib_any_true<> {
            constexpr static bool check() { return false; }
        };
        template <typename T, typename... ARGS>
        struct mib_any_true<T, ARGS...> {
            constexpr static bool check(T const& t, ARGS const&... args) {
                if(t)
                    return true;
                else
                    return mib_any_true<ARGS...>::check(args...);
            }
        };
        template <typename... ARGS>
        constexpr bool is_base_impl(ARGS const&... args) {
            return mib_any_true<ARGS...>::check(args...);
        }

        // test if any of the T... is a base of testing
        // this is just a cheap compiletime method to ask the question:
        // is any of the elements T... a member of the list testing
        template <typename testing, typename... T>
        struct is_base {
            constexpr static bool value =
                is_base_impl(std::is_base_of<T, testing>::value...);
        };

    }  // end namespace detail
}  // end namespace fsc

#define FSC_MIB_PREFIX mib_test_tag_
#define FSC_MIB_PRE_IMPL(expr) CAT(FSC_MIB_PREFIX, expr)
#define FSC_MIB_ADD_PRE(...) PP_TRAFO(FSC_MIB_PRE_IMPL, __VA_ARGS__)

#define FSC_MIB_ADD_FSC_DETAIL(expr) \
    namespace fsc {                  \
        namespace detail {           \
            expr                     \
        }                            \
    }
#define FSC_MIB_TAGS_IMPL(expr) FSC_MIB_ADD_FSC_DETAIL(struct expr;)

#define TPL_WRAP_IMPL(expr) \
    fsc::detail::mib_tpl_wrap<fsc::detail::FSC_MIB_PRE_IMPL(expr)>
#define FSC_MIB_ADD_TPL(...) PP_TRAFO(TPL_WRAP_IMPL, __VA_ARGS__)

#define MIB_TAGS_IMPL(...)                                                 \
    EVAL(DEFER(PP_APPLY)(FSC_MIB_TAGS_IMPL, FSC_MIB_ADD_PRE(__VA_ARGS__))) \
    FSC_MIB_TAGS_IMPL(CAT(FSC_MIB_PREFIX, all))                            \
    FSC_MIB_TAGS_IMPL(CAT(FSC_MIB_PREFIX, ))
#define MIB_TEST_IMPL(...) \
    FSC_MIB_ADD_FSC_DETAIL(struct testing : FSC_MIB_ADD_TPL(__VA_ARGS__){};)

MIB_TAGS_IMPL(MIB_TAGS)
MIB_TEST_IMPL(MIB_TEST)
#endif

//=================== Final Macros ===================
#ifndef NMIB
#define MIB_START_IMPL(tag)              \
    fsc::detail::mib_prof.timer_.stop(); \
    fsc::detail::mib_prof.start(#tag);   \
    fsc::detail::mib_prof.timer_.start();  //

#define MIB_STOP_IMPL(tag)               \
    fsc::detail::mib_prof.timer_.stop(); \
    fsc::detail::mib_prof.stop(#tag);    \
    fsc::detail::mib_prof.timer_.start();  //

#define MIB_PRINT_IMPL(mod)              \
    fsc::detail::mib_prof.set_mod(#mod); \
    fsc::detail::mib_prof.print_tree();  //

// in this case we want to switch on and of tags with the register mode
#ifdef MIB_REGISTER_MODE
#define MIB_START(tag)                                           \
    if(fsc::detail::is_base<fsc::detail::testing,                \
                            FSC_MIB_ADD_TPL(tag, all)>::value) { \
        MIB_START_IMPL(tag)                                      \
    }  //

#define MIB_STOP(tag)                                            \
    if(fsc::detail::is_base<fsc::detail::testing,                \
                            FSC_MIB_ADD_TPL(tag, all)>::value) { \
        MIB_STOP_IMPL(tag)                                       \
    }  //

// don't print additional information
#define MIB_PRINT(mod) MIB_PRINT_IMPL(mod)

#else  // in this case we measure all tags unconditionally, which allows us to
// drop the register requirement
#define MIB_START(tag) MIB_START_IMPL(tag)
#define MIB_STOP(tag) MIB_STOP_IMPL(tag)

// tell the user how to switch into register mode
#define MIB_PRINT(mod)                     \
    fsc::detail::mib_prof.register_help(); \
    MIB_PRINT_IMPL(mod)  //

#endif

// this only depends on the impl of start and stop
#define MIB_NEXT(tag1, tag2) MIB_STOP(tag1) MIB_START(tag2)

#define MIB_SAVE(mod, file)              \
    fsc::detail::mib_prof.set_mod(#mod); \
    fsc::detail::mib_prof.save(#file);  //
#else                                   // if we disabled the profiler
#define MIB_START(name) ;

#define MIB_STOP(name) ;

#define MIB_NEXT(name) ;

#ifndef NMIB_SILENT  // even
#define MIB_PRINT(mod) \
    std::cout << "NMIB is defined, MIB deactivated" << std::endl;

#define MIB_SAVE(mod, file) \
    std::cout << "NMIB is defined, MIB deactivated" << std::endl;
#else
#define MIB_PRINT(mod) ;
#define MIB_SAVE(mod, file) ;
#endif  // NMIB_SILENT

#endif  // NMIB

#endif  // FSC_PROFILER_HEADER
