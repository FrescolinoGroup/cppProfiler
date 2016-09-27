/** ****************************************************************************
 * \file
 * \brief      
 * \author
 * Year      | Name
 * --------: | :------------
 * 2016      | Mario S. Koenz
 * \copyright  todo
 ******************************************************************************/

#ifndef FSC_GENERIC_MACROS_HPP_GUARD
#define FSC_GENERIC_MACROS_HPP_GUARD

// generic macro helper
#define EMPTY()
// DEFER is useful if you have f(a,b,c) = ... and g(a) = a,a,a
// if you call "f(g(a))" this will fail since f has only one argument g(a)
// but if you "DEFER(f)(g(a))" this will keep f away long enough for its arguments
// s.t. g can expand to a,a,a. See EVAL!!!
#define DEFER(expr) expr EMPTY()

// since some macros need multiple scans to complete, we have an eval function
// the DEFER example shows nicely that DEFER(f)(g(a)) produces f(a,a,a) but
// this last MACRO is not evaluated, so we need to apply EVAL(DEFER(f)(g(a)))
#define EVAL(...) EVAL1(EVAL1(EVAL1(__VA_ARGS__)))
#define EVAL1(...) __VA_ARGS__

// CAT is per default defered with it's impl function
#define CAT_IMPL(A, B) A##B
#define CAT(A, B) CAT_IMPL(A, B)

// PP_TRAFO(fct, a,b,c) will return fct(a), fct(b), fct(c)
#define IMPL_TRAFO_1(FCT, T) FCT(T)
#define IMPL_TRAFO_2(FCT, T, ...) FCT(T), IMPL_TRAFO_1(FCT, __VA_ARGS__)
#define IMPL_TRAFO_3(FCT, T, ...) FCT(T), IMPL_TRAFO_2(FCT, __VA_ARGS__)
#define IMPL_TRAFO_4(FCT, T, ...) FCT(T), IMPL_TRAFO_3(FCT, __VA_ARGS__)
#define IMPL_TRAFO_5(FCT, T, ...) FCT(T), IMPL_TRAFO_4(FCT, __VA_ARGS__)
#define IMPL_TRAFO_6(FCT, T, ...) FCT(T), IMPL_TRAFO_5(FCT, __VA_ARGS__)
#define IMPL_TRAFO_7(FCT, T, ...) FCT(T), IMPL_TRAFO_6(FCT, __VA_ARGS__)
#define IMPL_TRAFO_8(FCT, T, ...) FCT(T), IMPL_TRAFO_7(FCT, __VA_ARGS__)
#define IMPL_TRAFO_9(FCT, T, ...) FCT(T), IMPL_TRAFO_8(FCT, __VA_ARGS__)
#define IMPL_TRAFO_10(FCT, T, ...) FCT(T), IMPL_TRAFO_9(FCT, __VA_ARGS__)
#define SELECT_TRAFO_IMPL(FCT, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, IMPL, ...) IMPL
#define PP_TRAFO(...) SELECT_TRAFO_IMPL(__VA_ARGS__, IMPL_TRAFO_10, IMPL_TRAFO_9, IMPL_TRAFO_8, IMPL_TRAFO_7, IMPL_TRAFO_6, IMPL_TRAFO_5, IMPL_TRAFO_4, IMPL_TRAFO_3, IMPL_TRAFO_2, IMPL_TRAFO_1, DUMMY)(__VA_ARGS__)

// PP_APPLY(fct, a,b,c) will return fct(a) fct(b) fct(c)
// works exactly like PP_TRAFO, but does not insert "," in between
#define IMPL_APPLY_1(FCT, T) FCT(T)
#define IMPL_APPLY_2(FCT, T, ...) FCT(T) IMPL_APPLY_1(FCT, __VA_ARGS__)
#define IMPL_APPLY_3(FCT, T, ...) FCT(T) IMPL_APPLY_2(FCT, __VA_ARGS__)
#define IMPL_APPLY_4(FCT, T, ...) FCT(T) IMPL_APPLY_3(FCT, __VA_ARGS__)
#define IMPL_APPLY_5(FCT, T, ...) FCT(T) IMPL_APPLY_4(FCT, __VA_ARGS__)
#define IMPL_APPLY_6(FCT, T, ...) FCT(T) IMPL_APPLY_5(FCT, __VA_ARGS__)
#define IMPL_APPLY_7(FCT, T, ...) FCT(T) IMPL_APPLY_6(FCT, __VA_ARGS__)
#define IMPL_APPLY_8(FCT, T, ...) FCT(T) IMPL_APPLY_7(FCT, __VA_ARGS__)
#define IMPL_APPLY_9(FCT, T, ...) FCT(T) IMPL_APPLY_8(FCT, __VA_ARGS__)
#define IMPL_APPLY_10(FCT, T, ...) FCT(T) IMPL_APPLY_9(FCT, __VA_ARGS__)
#define SELECT_APPLY_IMPL(FCT, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, IMPL, ...) IMPL
#define PP_APPLY(...) SELECT_APPLY_IMPL(__VA_ARGS__, IMPL_APPLY_10, IMPL_APPLY_9, IMPL_APPLY_8, IMPL_APPLY_7, IMPL_APPLY_6, IMPL_APPLY_5, IMPL_APPLY_4, IMPL_APPLY_3, IMPL_APPLY_2, IMPL_APPLY_1, DUMMY)(__VA_ARGS__)

#endif // FSC_GENERIC_MACROS_HPP_GUARD
