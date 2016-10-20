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
// but if you "DEFER(f)(g(a))" this will keep f away long enough for its
// arguments
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
#define IMPL_TRAFO_01(FCT, T) FCT(T)
#define IMPL_TRAFO_02(FCT, T, ...) FCT(T), IMPL_TRAFO_01(FCT, __VA_ARGS__)
#define IMPL_TRAFO_03(FCT, T, ...) FCT(T), IMPL_TRAFO_02(FCT, __VA_ARGS__)
#define IMPL_TRAFO_04(FCT, T, ...) FCT(T), IMPL_TRAFO_03(FCT, __VA_ARGS__)
#define IMPL_TRAFO_05(FCT, T, ...) FCT(T), IMPL_TRAFO_04(FCT, __VA_ARGS__)
#define IMPL_TRAFO_06(FCT, T, ...) FCT(T), IMPL_TRAFO_05(FCT, __VA_ARGS__)
#define IMPL_TRAFO_07(FCT, T, ...) FCT(T), IMPL_TRAFO_06(FCT, __VA_ARGS__)
#define IMPL_TRAFO_08(FCT, T, ...) FCT(T), IMPL_TRAFO_07(FCT, __VA_ARGS__)
#define IMPL_TRAFO_09(FCT, T, ...) FCT(T), IMPL_TRAFO_08(FCT, __VA_ARGS__)
#define IMPL_TRAFO_10(FCT, T, ...) FCT(T), IMPL_TRAFO_09(FCT, __VA_ARGS__)
#define IMPL_TRAFO_11(FCT, T, ...) FCT(T), IMPL_TRAFO_10(FCT, __VA_ARGS__)
#define IMPL_TRAFO_12(FCT, T, ...) FCT(T), IMPL_TRAFO_11(FCT, __VA_ARGS__)
#define IMPL_TRAFO_13(FCT, T, ...) FCT(T), IMPL_TRAFO_12(FCT, __VA_ARGS__)
#define IMPL_TRAFO_14(FCT, T, ...) FCT(T), IMPL_TRAFO_13(FCT, __VA_ARGS__)
#define IMPL_TRAFO_15(FCT, T, ...) FCT(T), IMPL_TRAFO_14(FCT, __VA_ARGS__)
#define IMPL_TRAFO_16(FCT, T, ...) FCT(T), IMPL_TRAFO_15(FCT, __VA_ARGS__)
#define IMPL_TRAFO_17(FCT, T, ...) FCT(T), IMPL_TRAFO_16(FCT, __VA_ARGS__)
#define IMPL_TRAFO_18(FCT, T, ...) FCT(T), IMPL_TRAFO_17(FCT, __VA_ARGS__)
#define IMPL_TRAFO_19(FCT, T, ...) FCT(T), IMPL_TRAFO_18(FCT, __VA_ARGS__)
#define IMPL_TRAFO_20(FCT, T, ...) FCT(T), IMPL_TRAFO_19(FCT, __VA_ARGS__)
#define IMPL_TRAFO_21(FCT, T, ...) FCT(T), IMPL_TRAFO_20(FCT, __VA_ARGS__)
#define IMPL_TRAFO_22(FCT, T, ...) FCT(T), IMPL_TRAFO_21(FCT, __VA_ARGS__)
#define IMPL_TRAFO_23(FCT, T, ...) FCT(T), IMPL_TRAFO_22(FCT, __VA_ARGS__)
#define IMPL_TRAFO_24(FCT, T, ...) FCT(T), IMPL_TRAFO_23(FCT, __VA_ARGS__)
#define IMPL_TRAFO_25(FCT, T, ...) FCT(T), IMPL_TRAFO_24(FCT, __VA_ARGS__)
#define IMPL_TRAFO_26(FCT, T, ...) FCT(T), IMPL_TRAFO_25(FCT, __VA_ARGS__)
#define IMPL_TRAFO_27(FCT, T, ...) FCT(T), IMPL_TRAFO_26(FCT, __VA_ARGS__)
#define IMPL_TRAFO_28(FCT, T, ...) FCT(T), IMPL_TRAFO_27(FCT, __VA_ARGS__)
#define IMPL_TRAFO_29(FCT, T, ...) FCT(T), IMPL_TRAFO_28(FCT, __VA_ARGS__)
#define IMPL_TRAFO_30(FCT, T, ...) FCT(T), IMPL_TRAFO_29(FCT, __VA_ARGS__)
#define IMPL_TRAFO_31(FCT, T, ...) FCT(T), IMPL_TRAFO_30(FCT, __VA_ARGS__)
#define IMPL_TRAFO_32(FCT, T, ...) FCT(T), IMPL_TRAFO_31(FCT, __VA_ARGS__)
#define IMPL_TRAFO_33(FCT, T, ...) FCT(T), IMPL_TRAFO_32(FCT, __VA_ARGS__)
#define IMPL_TRAFO_34(FCT, T, ...) FCT(T), IMPL_TRAFO_33(FCT, __VA_ARGS__)
#define IMPL_TRAFO_35(FCT, T, ...) FCT(T), IMPL_TRAFO_34(FCT, __VA_ARGS__)
#define IMPL_TRAFO_36(FCT, T, ...) FCT(T), IMPL_TRAFO_35(FCT, __VA_ARGS__)
#define IMPL_TRAFO_37(FCT, T, ...) FCT(T), IMPL_TRAFO_36(FCT, __VA_ARGS__)
#define IMPL_TRAFO_38(FCT, T, ...) FCT(T), IMPL_TRAFO_37(FCT, __VA_ARGS__)
#define IMPL_TRAFO_39(FCT, T, ...) FCT(T), IMPL_TRAFO_38(FCT, __VA_ARGS__)
#define IMPL_TRAFO_40(FCT, T, ...) FCT(T), IMPL_TRAFO_39(FCT, __VA_ARGS__)
#define IMPL_TRAFO_41(FCT, T, ...) FCT(T), IMPL_TRAFO_40(FCT, __VA_ARGS__)
#define IMPL_TRAFO_42(FCT, T, ...) FCT(T), IMPL_TRAFO_41(FCT, __VA_ARGS__)
#define IMPL_TRAFO_43(FCT, T, ...) FCT(T), IMPL_TRAFO_42(FCT, __VA_ARGS__)
#define IMPL_TRAFO_44(FCT, T, ...) FCT(T), IMPL_TRAFO_43(FCT, __VA_ARGS__)
#define IMPL_TRAFO_45(FCT, T, ...) FCT(T), IMPL_TRAFO_44(FCT, __VA_ARGS__)
#define IMPL_TRAFO_46(FCT, T, ...) FCT(T), IMPL_TRAFO_45(FCT, __VA_ARGS__)
#define IMPL_TRAFO_47(FCT, T, ...) FCT(T), IMPL_TRAFO_46(FCT, __VA_ARGS__)
#define IMPL_TRAFO_48(FCT, T, ...) FCT(T), IMPL_TRAFO_47(FCT, __VA_ARGS__)
#define IMPL_TRAFO_49(FCT, T, ...) FCT(T), IMPL_TRAFO_48(FCT, __VA_ARGS__)
#define IMPL_TRAFO_50(FCT, T, ...) FCT(T), IMPL_TRAFO_49(FCT, __VA_ARGS__)

#define SELECT_IMPL(FCT, T0, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10, T11, \
                    T12, T13, T14, T15, T16, T17, T18, T19, T20, T21, T22, \
                    T23, T24, T25, T26, T27, T28, T29, T30, T31, T32, T33, \
                    T34, T35, T36, T37, T38, T39, T40, T41, T42, T43, T44, \
                    T45, T46, T47, T48, T49, IMPL, ...)                    \
    IMPL
#define PP_TRAFO(...)                                                       \
    SELECT_IMPL(__VA_ARGS__, IMPL_TRAFO_50, IMPL_TRAFO_49, IMPL_TRAFO_48,   \
                IMPL_TRAFO_47, IMPL_TRAFO_46, IMPL_TRAFO_45, IMPL_TRAFO_44, \
                IMPL_TRAFO_43, IMPL_TRAFO_42, IMPL_TRAFO_41, IMPL_TRAFO_40, \
                IMPL_TRAFO_39, IMPL_TRAFO_38, IMPL_TRAFO_37, IMPL_TRAFO_36, \
                IMPL_TRAFO_35, IMPL_TRAFO_34, IMPL_TRAFO_33, IMPL_TRAFO_32, \
                IMPL_TRAFO_31, IMPL_TRAFO_30, IMPL_TRAFO_29, IMPL_TRAFO_28, \
                IMPL_TRAFO_27, IMPL_TRAFO_26, IMPL_TRAFO_25, IMPL_TRAFO_24, \
                IMPL_TRAFO_23, IMPL_TRAFO_22, IMPL_TRAFO_21, IMPL_TRAFO_20, \
                IMPL_TRAFO_19, IMPL_TRAFO_18, IMPL_TRAFO_17, IMPL_TRAFO_16, \
                IMPL_TRAFO_15, IMPL_TRAFO_14, IMPL_TRAFO_13, IMPL_TRAFO_12, \
                IMPL_TRAFO_11, IMPL_TRAFO_10, IMPL_TRAFO_09, IMPL_TRAFO_08, \
                IMPL_TRAFO_07, IMPL_TRAFO_06, IMPL_TRAFO_05, IMPL_TRAFO_04, \
                IMPL_TRAFO_03, IMPL_TRAFO_02, IMPL_TRAFO_01, DUMMY)         \
    (__VA_ARGS__)

// PP_APPLY(fct, a,b,c) will return fct(a) fct(b) fct(c)
// works exactly like PP_TRAFO, but does not insert "," in between
#define IMPL_APPLY_01(FCT, T) FCT(T)
#define IMPL_APPLY_02(FCT, T, ...) FCT(T) IMPL_APPLY_01(FCT, __VA_ARGS__)
#define IMPL_APPLY_03(FCT, T, ...) FCT(T) IMPL_APPLY_02(FCT, __VA_ARGS__)
#define IMPL_APPLY_04(FCT, T, ...) FCT(T) IMPL_APPLY_03(FCT, __VA_ARGS__)
#define IMPL_APPLY_05(FCT, T, ...) FCT(T) IMPL_APPLY_04(FCT, __VA_ARGS__)
#define IMPL_APPLY_06(FCT, T, ...) FCT(T) IMPL_APPLY_05(FCT, __VA_ARGS__)
#define IMPL_APPLY_07(FCT, T, ...) FCT(T) IMPL_APPLY_06(FCT, __VA_ARGS__)
#define IMPL_APPLY_08(FCT, T, ...) FCT(T) IMPL_APPLY_07(FCT, __VA_ARGS__)
#define IMPL_APPLY_09(FCT, T, ...) FCT(T) IMPL_APPLY_08(FCT, __VA_ARGS__)
#define IMPL_APPLY_10(FCT, T, ...) FCT(T) IMPL_APPLY_09(FCT, __VA_ARGS__)
#define IMPL_APPLY_11(FCT, T, ...) FCT(T) IMPL_APPLY_10(FCT, __VA_ARGS__)
#define IMPL_APPLY_12(FCT, T, ...) FCT(T) IMPL_APPLY_11(FCT, __VA_ARGS__)
#define IMPL_APPLY_13(FCT, T, ...) FCT(T) IMPL_APPLY_12(FCT, __VA_ARGS__)
#define IMPL_APPLY_14(FCT, T, ...) FCT(T) IMPL_APPLY_13(FCT, __VA_ARGS__)
#define IMPL_APPLY_15(FCT, T, ...) FCT(T) IMPL_APPLY_14(FCT, __VA_ARGS__)
#define IMPL_APPLY_16(FCT, T, ...) FCT(T) IMPL_APPLY_15(FCT, __VA_ARGS__)
#define IMPL_APPLY_17(FCT, T, ...) FCT(T) IMPL_APPLY_16(FCT, __VA_ARGS__)
#define IMPL_APPLY_18(FCT, T, ...) FCT(T) IMPL_APPLY_17(FCT, __VA_ARGS__)
#define IMPL_APPLY_19(FCT, T, ...) FCT(T) IMPL_APPLY_18(FCT, __VA_ARGS__)
#define IMPL_APPLY_20(FCT, T, ...) FCT(T) IMPL_APPLY_19(FCT, __VA_ARGS__)
#define IMPL_APPLY_21(FCT, T, ...) FCT(T) IMPL_APPLY_20(FCT, __VA_ARGS__)
#define IMPL_APPLY_22(FCT, T, ...) FCT(T) IMPL_APPLY_21(FCT, __VA_ARGS__)
#define IMPL_APPLY_23(FCT, T, ...) FCT(T) IMPL_APPLY_22(FCT, __VA_ARGS__)
#define IMPL_APPLY_24(FCT, T, ...) FCT(T) IMPL_APPLY_23(FCT, __VA_ARGS__)
#define IMPL_APPLY_25(FCT, T, ...) FCT(T) IMPL_APPLY_24(FCT, __VA_ARGS__)
#define IMPL_APPLY_26(FCT, T, ...) FCT(T) IMPL_APPLY_25(FCT, __VA_ARGS__)
#define IMPL_APPLY_27(FCT, T, ...) FCT(T) IMPL_APPLY_26(FCT, __VA_ARGS__)
#define IMPL_APPLY_28(FCT, T, ...) FCT(T) IMPL_APPLY_27(FCT, __VA_ARGS__)
#define IMPL_APPLY_29(FCT, T, ...) FCT(T) IMPL_APPLY_28(FCT, __VA_ARGS__)
#define IMPL_APPLY_30(FCT, T, ...) FCT(T) IMPL_APPLY_29(FCT, __VA_ARGS__)
#define IMPL_APPLY_31(FCT, T, ...) FCT(T) IMPL_APPLY_30(FCT, __VA_ARGS__)
#define IMPL_APPLY_32(FCT, T, ...) FCT(T) IMPL_APPLY_31(FCT, __VA_ARGS__)
#define IMPL_APPLY_33(FCT, T, ...) FCT(T) IMPL_APPLY_32(FCT, __VA_ARGS__)
#define IMPL_APPLY_34(FCT, T, ...) FCT(T) IMPL_APPLY_33(FCT, __VA_ARGS__)
#define IMPL_APPLY_35(FCT, T, ...) FCT(T) IMPL_APPLY_34(FCT, __VA_ARGS__)
#define IMPL_APPLY_36(FCT, T, ...) FCT(T) IMPL_APPLY_35(FCT, __VA_ARGS__)
#define IMPL_APPLY_37(FCT, T, ...) FCT(T) IMPL_APPLY_36(FCT, __VA_ARGS__)
#define IMPL_APPLY_38(FCT, T, ...) FCT(T) IMPL_APPLY_37(FCT, __VA_ARGS__)
#define IMPL_APPLY_39(FCT, T, ...) FCT(T) IMPL_APPLY_38(FCT, __VA_ARGS__)
#define IMPL_APPLY_40(FCT, T, ...) FCT(T) IMPL_APPLY_39(FCT, __VA_ARGS__)
#define IMPL_APPLY_41(FCT, T, ...) FCT(T) IMPL_APPLY_40(FCT, __VA_ARGS__)
#define IMPL_APPLY_42(FCT, T, ...) FCT(T) IMPL_APPLY_41(FCT, __VA_ARGS__)
#define IMPL_APPLY_43(FCT, T, ...) FCT(T) IMPL_APPLY_42(FCT, __VA_ARGS__)
#define IMPL_APPLY_44(FCT, T, ...) FCT(T) IMPL_APPLY_43(FCT, __VA_ARGS__)
#define IMPL_APPLY_45(FCT, T, ...) FCT(T) IMPL_APPLY_44(FCT, __VA_ARGS__)
#define IMPL_APPLY_46(FCT, T, ...) FCT(T) IMPL_APPLY_45(FCT, __VA_ARGS__)
#define IMPL_APPLY_47(FCT, T, ...) FCT(T) IMPL_APPLY_46(FCT, __VA_ARGS__)
#define IMPL_APPLY_48(FCT, T, ...) FCT(T) IMPL_APPLY_47(FCT, __VA_ARGS__)
#define IMPL_APPLY_49(FCT, T, ...) FCT(T) IMPL_APPLY_48(FCT, __VA_ARGS__)
#define IMPL_APPLY_50(FCT, T, ...) FCT(T) IMPL_APPLY_49(FCT, __VA_ARGS__)

#define PP_APPLY(...)                                                       \
    SELECT_IMPL(__VA_ARGS__, IMPL_APPLY_50, IMPL_APPLY_49, IMPL_APPLY_48,   \
                IMPL_APPLY_47, IMPL_APPLY_46, IMPL_APPLY_45, IMPL_APPLY_44, \
                IMPL_APPLY_43, IMPL_APPLY_42, IMPL_APPLY_41, IMPL_APPLY_40, \
                IMPL_APPLY_39, IMPL_APPLY_38, IMPL_APPLY_37, IMPL_APPLY_36, \
                IMPL_APPLY_35, IMPL_APPLY_34, IMPL_APPLY_33, IMPL_APPLY_32, \
                IMPL_APPLY_31, IMPL_APPLY_30, IMPL_APPLY_29, IMPL_APPLY_28, \
                IMPL_APPLY_27, IMPL_APPLY_26, IMPL_APPLY_25, IMPL_APPLY_24, \
                IMPL_APPLY_23, IMPL_APPLY_22, IMPL_APPLY_21, IMPL_APPLY_20, \
                IMPL_APPLY_19, IMPL_APPLY_18, IMPL_APPLY_17, IMPL_APPLY_16, \
                IMPL_APPLY_15, IMPL_APPLY_14, IMPL_APPLY_13, IMPL_APPLY_12, \
                IMPL_APPLY_11, IMPL_APPLY_10, IMPL_APPLY_09, IMPL_APPLY_08, \
                IMPL_APPLY_07, IMPL_APPLY_06, IMPL_APPLY_05, IMPL_APPLY_04, \
                IMPL_APPLY_03, IMPL_APPLY_02, IMPL_APPLY_01, DUMMY)         \
    (__VA_ARGS__)

#endif  // FSC_GENERIC_MACROS_HPP_GUARD
