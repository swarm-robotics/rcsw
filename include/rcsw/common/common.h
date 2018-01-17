/**
 * @file common.h
 * @ingroup common
 * @brief Definitions, etc. common to all of RCSW.
 *
 * @copyright 2017 John Harwell, All rights reserved.
 *
 * This file is part of RCSW.
 *
 * RCSW is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * RCSW is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * RCSW.  If not, see <http://www.gnu.org/licenses/
 */

#ifndef INCLUDE_RCSW_COMMON_COMMON_H_
#define INCLUDE_RCSW_COMMON_COMMON_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcsw/common/types.h"

/*******************************************************************************
 * Constants
 ******************************************************************************/
#define NS_PER_MS 100000
#define MS_PER_SEC 1000
#define ONEE9 1000000000 /* 1E9 */
#define ONEE6 1000000    /* 1E6 */
#define ONEE3 1000       /* 1E3 */
#define RCSW_FLOAT_EPSILON 0.00000001 /* for comparison with 0.0 */
#define RCSW_DOUBLE_EPSILON 0.00000001 /* for comparison with 0.0 */

/*******************************************************************************
 * String Macros
 ******************************************************************************/
/**
 * @brief Stringification. Use when you need to stringify the result of a macro
 * expansion. CAT() and XSTR() are equivalent.
 */
#define CAT_(x) #x /* don't use this one */
#define CAT(x) CAT_(x)
#define XSTR(X) CAT(X)

/**
 * @brief Stringification. Use when you need to join two tokens together
 */
#define JOIN_(x, y) x##y /* don't use this one */
#define JOIN(x, y) JOIN_(x, y)

/**
 * @def UNIQUE_ID(prefix)
 *
 * Generate a translation unit unique identifier using gcc's __COUNTER__.
 */
#define UNIQUE_ID(prefix) JOIN(JOIN(__UNIQUE_ID_, prefix), __COUNTER__)

/*******************************************************************************
 * Comparison Macros
 ******************************************************************************/
/**
 * @def MIN_(t1, t2, min1, min2, a, b)
 *
 * Gets the minimum of (\a a, \a b) while also performing a type comparison. If
 * the arguments do not have the same type, a compiler warning will be
 * issued. You have to EXPLICITLY cast, which is a good thing. Don't want to get
 * weird behavior when taking the max/min of different types.The type checking
 * will be compiled away at high optimization levels.
 */
#define MIN_(t1, t2, min1, min2, a, b) ({\
      t1 min1 = (a);\
      t2 min2 = (b);\
      (void) (&(min1) == &(min2));              \
      (min1) < (min2) ? (min1) : (min2); })

/**
 * @def MAX_(t1, t2, min1, min2, a, b)
 *
 * Gets the maximum of (\a a, \a b) while also performing a type comparison. If
 * the arguments do not have the same type, a compiler warning will be
 * issued. You have to EXPLICITLY cast, which is a good thing. Don't want to get
 * weird behavior when taking the max/min of different types.The type checking
 * will be compiled away at high optimization levels.
 */
#define MAX_(t1, t2, max1, max2, a, b) ({       \
      t1 max1 = (a);                            \
      t2 max2 = (b);                            \
      (void) (&(max1) == &(max2));                  \
      (max1) > (max2) ? (max1) : (max2); })

/**
 * @def MIN(a, b) Returns a type-same minimum of its arguments (compiler
 * warnings for unsafe comparisons of different types).
 */
#define MIN(a, b)                          \
  MIN_(typeof(a), typeof(b),               \
        UNIQUE_ID(min1_), UNIQUE_ID(min2_), \
        a, b)

/**
 * @def MIN(a, b, c) Returns a type-same minimum of its arguments (compiler
 * warnings for unsafe comparisons of different types).
 */

#define MIN3(a, b, c) MIN((typeof(a))MIN(a, b), c)

/**
 * @def MAX(a, b) Returns a type-same maximum of its arguments (compiler
 * warnings for unsafe comparisons of different types).
 */
#define MAX(a, b)                               \
  MAX_(typeof(a), typeof(b),                    \
       UNIQUE_ID(max1_), UNIQUE_ID(max2_),      \
       a, b)


/**
 * @def MAX(a, b, c) Returns a type-same maximum of its arguments (compiler
 * warnings for unsafe comparisons of different types).
 */
#define MAX3(a, b, c) MAX((typeof(a))MAX(a, b), c)

/**
 * @def IS_ODD(n)
 *
 * Readability macro for determining if something is odd.
 *
 * You can obviously do this without a macro, but this is (1) more self
 * documenting, and (2) less error prone.
 */
#define IS_ODD(n) ((n)&1)

/**
 * @def IS_EVEN(n)
 *
 * Readability macro for determining if something is even.
 *
 * You can obviously do this without a macro, but this is (1) more self
 * documenting, and (2) less error prone.
 */
#define IS_EVEN(n) (!IS_ODD((n)))

/**
 * @def IS_BETWEEN(n, low, high)
 *
 * Readability macro for determining if something is between an upper and lower
 * bound (inclusive).
 *
 * You can obviously do this without a macro, but this is (1) more self
 * documenting, and (2) less error prone.
 */
#define IS_BETWEEN(n, low, high) ((n) >= (low) && (n) <= (high))

/*******************************************************************************
 * Other Macros
 ******************************************************************************/
/* g++ does not define this for some reason... */
#ifndef isnan
#define isnan(d) __builtin_isnan(d)
#endif

/**
 * @def LIKELY(x)
 *
 * Inform the compiler that a conditional branch is almost certain to be taken,
 * for optimization purposes.
 */
#define LIKELY(x) __builtin_expect((x), 1)

/**
 * @def UNLIKELY(x)
 *
 * Inform the compiler that a conditional branch is almost certain not to be
 * taken, for optimization purposes.
 */
#define UNLIKELY(x) __builtin_expect((x), 0)

/**
 * @def ARRAY_SIZE(arr) Get the size of an array (NOT a pointer to an array) in
 * bytes.
 */
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

#define CONTAINER_OF(ptr, type, member) ({                      \
        const typeof(((type *)0)->member) *__mptr = (ptr);      \
        (type *)( (char *)__mptr - offsetof(type, member) );})

/**
 * @def FIELD_SIZEOF(t, f)
 * Get the size of a field in a struct \a t named \a f.
 */
#define FIELD_SIZEOF(t, f) (sizeof(((t *)0)->f))

/**
 * @brief Masking macros. Get the upper/lower 16 or 32 bits of a 32 or 64 bit
 * number, respectively.
 *
 * Note that these macros cast their arguments as UNSIGNED integers, so using
 * negative ints will likely behave oddly.
 */
#define UPPER16(n) ((uint32_t)((n) >> 16))
#define LOWER16(n) ((uint16_t)((n)))
#define UPPER32(n) ((uint64_t)((n) >> 32))
#define LOWER32(n) ((uint32_t)((n)))

/**
 * @def CHECK(cond) Check a condition in a function.
 *
 * If condition is not true, go to the error/bailout section for function (you
 * must have a label called \c error in your function).
 */
#define CHECK(cond)                             \
  if (UNLIKELY(!(cond))) {                      \
        goto error;                             \
    }

/**
 * @CHECK_PTR(ptr) Check a pointer \a ptr in a function.
 *
 * If \a ptr is NULL, go to the error/bailout section for function (you
 * must have a label called \c error in your function).
 */
#define CHECK_PTR(ptr) CHECK(NULL != (ptr))

/**
 * @CHECK_FD(fd) Check a file descriptor \a fdin a function.
 *
 * If the descriptor \a fdis invalid (i.e. < 0), go to the error/bailout section
 * for function (you must have a label called \c error in your function).
 */
#define CHECK_FD(fd) CHECK((fd) >= 0)

/*******************************************************************************
 * Tricky Variadac Macro Manipulation
 ******************************************************************************/
/* @cond INTERNAL */
/* 3 Helper macros--don't use them */
#define VAR_NARG_(...) VAR_ARG_N(__VA_ARGS__)
#define VAR_ARG_N(                                                      \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, \
    _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, \
    _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, \
    _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, \
    _62, _63, _64, _65, _66, _67, _68, _69, _70, _71, _72, _73, _74, _75, _76, \
    _77, _78, _79, _80, _81, _82, _83, _84, _85, _86, _87, _88, _89, _90, _91, \
    _92, _93, _94, _95, _96, _97, _98, _99, _100, N, ...)               \

#define VAR_RSEQ_N()                                                    \
    100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, \
        82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, \
        65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, \
        48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, \
        31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, \
        14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

/**
 * @brief XFOR_EACH() macro helpers. (You should never ever use these)
 *
 * WHAT is the name of the macro/function that each arg of __VA_ARGS__ is
 * successively passed to.
 * XFE1 = X For Each that for which the macro/function takes 1 argument.
 */
#define XFE1_1(WHAT, X) WHAT(X)
#define XFE1_2(WHAT, X, ...) WHAT(X) XFE1_1(WHAT, __VA_ARGS__)
#define XFE1_3(WHAT, X, ...) WHAT(X) XFE1_2(WHAT, __VA_ARGS__)
#define XFE1_4(WHAT, X, ...) WHAT(X) XFE1_3(WHAT, __VA_ARGS__)
#define XFE1_5(WHAT, X, ...) WHAT(X) XFE1_4(WHAT, __VA_ARGS__)
#define XFE1_6(WHAT, X, ...) WHAT(X) XFE1_5(WHAT, __VA_ARGS__)
#define XFE1_7(WHAT, X, ...) WHAT(X) XFE1_6(WHAT, __VA_ARGS__)
#define XFE1_8(WHAT, X, ...) WHAT(X) XFE1_7(WHAT, __VA_ARGS__)
#define XFE1_9(WHAT, X, ...) WHAT(X) XFE1_8(WHAT, __VA_ARGS__)
#define XFE1_10(WHAT, X, ...) WHAT(X) XFE1_9(WHAT, __VA_ARGS__)
#define XFE1_11(WHAT, X, ...) WHAT(X) XFE1_10(WHAT, __VA_ARGS__)
#define XFE1_12(WHAT, X, ...) WHAT(X) XFE1_11(WHAT, __VA_ARGS__)
#define XFE1_13(WHAT, X, ...) WHAT(X) XFE1_12(WHAT, __VA_ARGS__)
#define XFE1_14(WHAT, X, ...) WHAT(X) XFE1_13(WHAT, __VA_ARGS__)
#define XFE1_15(WHAT, X, ...) WHAT(X) XFE1_14(WHAT, __VA_ARGS__)
#define XFE1_16(WHAT, X, ...) WHAT(X) XFE1_15(WHAT, __VA_ARGS__)
#define XFE1_17(WHAT, X, ...) WHAT(X) XFE1_16(WHAT, __VA_ARGS__)
#define XFE1_18(WHAT, X, ...) WHAT(X) XFE1_17(WHAT, __VA_ARGS__)
#define XFE1_19(WHAT, X, ...) WHAT(X) XFE1_18(WHAT, __VA_ARGS__)
#define XFE1_20(WHAT, X, ...) WHAT(X) XFE1_19(WHAT, __VA_ARGS__)
#define XFE1_21(WHAT, X, ...) WHAT(X) XFE1_20(WHAT, __VA_ARGS__)
#define XFE1_22(WHAT, X, ...) WHAT(X) XFE1_21(WHAT, __VA_ARGS__)
#define XFE1_23(WHAT, X, ...) WHAT(X) XFE1_22(WHAT, __VA_ARGS__)
#define XFE1_24(WHAT, X, ...) WHAT(X) XFE1_23(WHAT, __VA_ARGS__)
#define XFE1_25(WHAT, X, ...) WHAT(X) XFE1_24(WHAT, __VA_ARGS__)
#define XFE1_26(WHAT, X, ...) WHAT(X) XFE1_25(WHAT, __VA_ARGS__)
#define XFE1_27(WHAT, X, ...) WHAT(X) XFE1_26(WHAT, __VA_ARGS__)
#define XFE1_28(WHAT, X, ...) WHAT(X) XFE1_27(WHAT, __VA_ARGS__)
#define XFE1_29(WHAT, X, ...) WHAT(X) XFE1_28(WHAT, __VA_ARGS__)
#define XFE1_30(WHAT, X, ...) WHAT(X) XFE1_29(WHAT, __VA_ARGS__)
#define XFE1_31(WHAT, X, ...) WHAT(X) XFE1_30(WHAT, __VA_ARGS__)
#define XFE1_32(WHAT, X, ...) WHAT(X) XFE1_31(WHAT, __VA_ARGS__)
#define XFE1_33(WHAT, X, ...) WHAT(X) XFE1_32(WHAT, __VA_ARGS__)
#define XFE1_34(WHAT, X, ...) WHAT(X) XFE1_33(WHAT, __VA_ARGS__)
#define XFE1_35(WHAT, X, ...) WHAT(X) XFE1_34(WHAT, __VA_ARGS__)
#define XFE1_36(WHAT, X, ...) WHAT(X) XFE1_35(WHAT, __VA_ARGS__)
#define XFE1_37(WHAT, X, ...) WHAT(X) XFE1_36(WHAT, __VA_ARGS__)
#define XFE1_38(WHAT, X, ...) WHAT(X) XFE1_37(WHAT, __VA_ARGS__)
#define XFE1_39(WHAT, X, ...) WHAT(X) XFE1_38(WHAT, __VA_ARGS__)
#define XFE1_40(WHAT, X, ...) WHAT(X) XFE1_39(WHAT, __VA_ARGS__)
#define XFE1_41(WHAT, X, ...) WHAT(X) XFE1_40(WHAT, __VA_ARGS__)
#define XFE1_42(WHAT, X, ...) WHAT(X) XFE1_41(WHAT, __VA_ARGS__)
#define XFE1_43(WHAT, X, ...) WHAT(X) XFE1_42(WHAT, __VA_ARGS__)
#define XFE1_44(WHAT, X, ...) WHAT(X) XFE1_43(WHAT, __VA_ARGS__)
#define XFE1_45(WHAT, X, ...) WHAT(X) XFE1_44(WHAT, __VA_ARGS__)
#define XFE1_46(WHAT, X, ...) WHAT(X) XFE1_45(WHAT, __VA_ARGS__)
#define XFE1_47(WHAT, X, ...) WHAT(X) XFE1_46(WHAT, __VA_ARGS__)
#define XFE1_48(WHAT, X, ...) WHAT(X) XFE1_47(WHAT, __VA_ARGS__)
#define XFE1_49(WHAT, X, ...) WHAT(X) XFE1_48(WHAT, __VA_ARGS__)
#define XFE1_50(WHAT, X, ...) WHAT(X) XFE1_49(WHAT, __VA_ARGS__)

/**
 * @brief XFOR_EACH2() macro helpers. (You should never ever use these)
 *
 * WHAT is the name of the macro/function that each arg of __VA_ARGS__ is
 * successively passed to.
 * XFE2 = X For Each for which the macro/function takes 2 arguments.
 */
#define XFE2_1(WHAT, v, X) WHAT(X, v)
#define XFE2_2(WHAT, v, X, ...) WHAT(X, v) XFE2_1(WHAT, v, __VA_ARGS__)
#define XFE2_3(WHAT, v, X, ...) WHAT(X, v) XFE2_2(WHAT, v, __VA_ARGS__)
#define XFE2_4(WHAT, v, X, ...) WHAT(X, v) XFE2_3(WHAT, v, __VA_ARGS__)
#define XFE2_5(WHAT, v, X, ...) WHAT(X, v) XFE2_4(WHAT, v, __VA_ARGS__)
#define XFE2_6(WHAT, v, X, ...) WHAT(X, v) XFE2_5(WHAT, v, __VA_ARGS__)
#define XFE2_7(WHAT, v, X, ...) WHAT(X, v) XFE2_6(WHAT, v, __VA_ARGS__)
#define XFE2_8(WHAT, v, X, ...) WHAT(X, v) XFE2_7(WHAT, v, __VA_ARGS__)
#define XFE2_9(WHAT, v, X, ...) WHAT(X, v) XFE2_8(WHAT, v, __VA_ARGS__)
#define XFE2_10(WHAT, v, X, ...) WHAT(X, v) XFE2_9(WHAT, v, __VA_ARGS__)
#define XFE2_11(WHAT, v, X, ...) WHAT(X, v) XFE2_10(WHAT, v, __VA_ARGS__)
#define XFE2_12(WHAT, v, X, ...) WHAT(X, v) XFE2_11(WHAT, v, __VA_ARGS__)
#define XFE2_13(WHAT, v, X, ...) WHAT(X, v) XFE2_12(WHAT, v, __VA_ARGS__)
#define XFE2_14(WHAT, v, X, ...) WHAT(X, v) XFE2_13(WHAT, v, __VA_ARGS__)
#define XFE2_15(WHAT, v, X, ...) WHAT(X, v) XFE2_14(WHAT, v, __VA_ARGS__)
#define XFE2_16(WHAT, v, X, ...) WHAT(X, v) XFE2_15(WHAT, v, __VA_ARGS__)
#define XFE2_17(WHAT, v, X, ...) WHAT(X, v) XFE2_16(WHAT, v, __VA_ARGS__)
#define XFE2_18(WHAT, v, X, ...) WHAT(X, v) XFE2_17(WHAT, v, __VA_ARGS__)
#define XFE2_19(WHAT, v, X, ...) WHAT(X, v) XFE2_18(WHAT, v, __VA_ARGS__)
#define XFE2_20(WHAT, v, X, ...) WHAT(X, v) XFE2_19(WHAT, v, __VA_ARGS__)
#define XFE2_21(WHAT, v, X, ...) WHAT(X, v) XFE2_20(WHAT, v, __VA_ARGS__)
#define XFE2_22(WHAT, v, X, ...) WHAT(X, v) XFE2_21(WHAT, v, __VA_ARGS__)
#define XFE2_23(WHAT, v, X, ...) WHAT(X, v) XFE2_22(WHAT, v, __VA_ARGS__)
#define XFE2_24(WHAT, v, X, ...) WHAT(X, v) XFE2_23(WHAT, v, __VA_ARGS__)
#define XFE2_25(WHAT, v, X, ...) WHAT(X, v) XFE2_24(WHAT, v, __VA_ARGS__)
#define XFE2_26(WHAT, v, X, ...) WHAT(X, v) XFE2_25(WHAT, v, __VA_ARGS__)
#define XFE2_27(WHAT, v, X, ...) WHAT(X, v) XFE2_26(WHAT, v, __VA_ARGS__)
#define XFE2_28(WHAT, v, X, ...) WHAT(X, v) XFE2_27(WHAT, v, __VA_ARGS__)
#define XFE2_29(WHAT, v, X, ...) WHAT(X, v) XFE2_28(WHAT, v, __VA_ARGS__)
#define XFE2_30(WHAT, v, X, ...) WHAT(X, v) XFE2_29(WHAT, v, __VA_ARGS__)
#define XFE2_31(WHAT, v, X, ...) WHAT(X, v) XFE2_30(WHAT, v, __VA_ARGS__)
#define XFE2_32(WHAT, v, X, ...) WHAT(X, v) XFE2_31(WHAT, v, __VA_ARGS__)
#define XFE2_33(WHAT, v, X, ...) WHAT(X, v) XFE2_32(WHAT, v, __VA_ARGS__)
#define XFE2_34(WHAT, v, X, ...) WHAT(X, v) XFE2_33(WHAT, v, __VA_ARGS__)
#define XFE2_35(WHAT, v, X, ...) WHAT(X, v) XFE2_34(WHAT, v, __VA_ARGS__)
#define XFE2_36(WHAT, v, X, ...) WHAT(X, v) XFE2_35(WHAT, v, __VA_ARGS__)
#define XFE2_37(WHAT, v, X, ...) WHAT(X, v) XFE2_36(WHAT, v, __VA_ARGS__)
#define XFE2_38(WHAT, v, X, ...) WHAT(X, v) XFE2_37(WHAT, v, __VA_ARGS__)
#define XFE2_39(WHAT, v, X, ...) WHAT(X, v) XFE2_38(WHAT, v, __VA_ARGS__)
#define XFE2_40(WHAT, v, X, ...) WHAT(X, v) XFE2_39(WHAT, v, __VA_ARGS__)
#define XFE2_41(WHAT, v, X, ...) WHAT(X, v) XFE2_40(WHAT, v, __VA_ARGS__)
#define XFE2_42(WHAT, v, X, ...) WHAT(X, v) XFE2_41(WHAT, v, __VA_ARGS__)
#define XFE2_43(WHAT, v, X, ...) WHAT(X, v) XFE2_42(WHAT, v, __VA_ARGS__)
#define XFE2_44(WHAT, v, X, ...) WHAT(X, v) XFE2_43(WHAT, v, __VA_ARGS__)
#define XFE2_45(WHAT, v, X, ...) WHAT(X, v) XFE2_44(WHAT, v, __VA_ARGS__)
#define XFE2_46(WHAT, v, X, ...) WHAT(X, v) XFE2_45(WHAT, v, __VA_ARGS__)
#define XFE2_47(WHAT, v, X, ...) WHAT(X, v) XFE2_46(WHAT, v, __VA_ARGS__)
#define XFE2_48(WHAT, v, X, ...) WHAT(X, v) XFE2_47(WHAT, v, __VA_ARGS__)
#define XFE2_49(WHAT, v, X, ...) WHAT(X, v) XFE2_48(WHAT, v, __VA_ARGS__)
#define XFE2_50(WHAT, v, X, ...) WHAT(X, v) XFE2_49(WHAT, v, __VA_ARGS__)

/**
 * @brief Helper macro to get the name of the XFOR_EACH[1,2]() helper macro for the
 * current iteration. Don't ever use it.
 */
#define XGET_MACRO(                                                     \
    _1, _2, _3, _4, _5, _6, _7, _8, _9, _10,                            \
    _11, _12, _13, _14, _15, _16, _17, _18, _19, _20,                   \
    _21, _22, _23, _24, _25, _26, _27, _28, _29, _30,                   \
    _31, _32, _33, _34, _35, _36, _37, _38, _39, _40,                   \
    _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, NAME, ...)        \
    NAME

#define XFOR_EACH1(action, ...)                                         \
    XGET_MACRO(                                                         \
        __VA_ARGS__,                                                    \
        XFE1_50, XFE1_49, XFE1_48, XFE1_47, XFE1_46, XFE1_45, XFE1_44,XFE1_43, XFE1_42, XFE1_41, \
        XFE1_40, XFE1_39, XFE1_38, XFE1_37, XFE1_36, XFE1_35,XFE1_34, XFE1_33, XFE1_32, XFE1_31, \
        XFE1_30, XFE1_29, XFE1_28, XFE1_27, XFE1_26, XFE1_25, XFE1_24, XFE1_23, XFE1_22, XFE1_21, \
        XFE1_20, XFE1_19, XFE1_18, XFE1_17, XFE1_16, XFE1_15, XFE1_14, XFE1_13, XFE1_12, XFE1_11, \
        XFE1_10, XFE1_9, XFE1_8, XFE1_7, XFE1_6, XFE1_5, XFE1_4, XFE1_3, XFE1_2, XFE1_1) \
    (action, __VA_ARGS__)

#define XFOR_EACH2(action, v, ...)                                      \
  XGET_MACRO(                                                           \
      __VA_ARGS__,                                                      \
      XFE2_50, XFE2_49, XFE2_48, XFE2_47, XFE2_46, XFE2_45, XFE2_44,XFE2_43, XFE2_42, XFE2_41, \
      XFE2_40, XFE2_39, XFE2_38, XFE2_37, XFE2_36, XFE2_35,XFE2_34, XFE2_33, XFE2_32, XFE2_31, \
      XFE2_30, XFE2_29, XFE2_28, XFE2_27, XFE2_26, XFE2_25, XFE2_24, XFE2_23, XFE2_22, XFE2_21, \
      XFE2_20, XFE2_19, XFE2_18, XFE2_17, XFE2_16, XFE2_15, XFE2_14, XFE2_13, XFE2_12, XFE2_11, \
      XFE2_10, XFE2_9, XFE2_8, XFE2_7, XFE2_6, XFE2_5, XFE2_4, XFE2_3, XFE2_2, XFE2_1) \
      (action, v, __VA_ARGS__)
/* @endcond */

/**
 * @brief Tricky preprocessor awesomeness to get the # of arguments passed to a
 * variadac macro.
 *
 * It works by using the fact that __VA_ARGS__ is a comma-separated list of
 * arguments to determine an offset within the list of #'s that corresponds to
 * the # of arguments passed to the macro. Works with up to 100 arguments.
 */
#define VAR_NARG(...) VAR_NARG_(__VA_ARGS__, VAR_RSEQ_N())

/*******************************************************************************
 * Enum Generation Macros
 ******************************************************************************/
/**
 * @brief An XTABLE_STR is a string representation of a token passed to
 * XFOR_EACH().  An \ref XTABLE_ENUM is just an entry within an enum.
 *
 * Don't use these.
 */
#define XTABLE_STR(X) STR(X),
#define XTABLE_ENUM(X) X,

/**
 * @brief The actual table generation macros. These are VERY useful if you want
 * to generate a table of strings from a set of tokens and/or a table of enums
 * from a set of tokens.
 *
 * If you have a define like this:
 * #define myents A,B,C,D,E,F,G,H
 *
 * Then you can use it to generate either of the two table types like so:
 *
 * char * foo [] { XGEN_STRS(myents) };
 * enum foo2  {XGEN_ENUMS(myents) };
 *
 * If you need more than 50 entries in a table, then you can do:
 *
 * char * foo [] {XGEN_STRS(myents1) XGEN_STRS(myents2) XGEN_STRS(myents3) };
 *
 * in order to get the # of entries you needsize of the table you need
 *
 * Pretty neat, huh?
 */
#define XGEN_STRS(...) XFOR_EACH1(XTABLE_STR, __VA_ARGS__)
#define XGEN_ENUMS(...) XFOR_EACH1(XTABLE_ENUM, __VA_ARGS__)
#define XGEN_MASKABLE_ENUMS(...) XFOR_EACH1(XTABLE_MASKABLE_ENUM, __VAR_ARGS__)

/*******************************************************************************
 * Attribute Macros
 ******************************************************************************/
#if defined(__unused)
#undef __unused
#endif /* __unused */

/**
 * @def __unused Shorthand for declaring something unused (I'm lazy).
 */
#define __unused __attribute__((unused))

#if defined(__check_return)
#undef __check_return
#endif /* __check_return */

/**
 * @def __check_return Shorthand for enhancing compile checking of return value usage.
 */
#define __check_return __attribute__((warn_unused_result))

#if defined(__deprecated)
#undef __deprecated
#endif /* __deprecated */

/**
 * @def __deprecated Shorthand for marking a function as deprecated so that
 * compile warning is issued if it is used.
 */
#define __deprecated __attribute__((deprecated))

#if defined(__const)
#undef __const
#endif /* __const */

/**
 * @def __const Shorthand for marked a function as purely function of its input
 * parameters only (no global memory access allowed).
 */
#define __const __attribute__((const))

#if defined(__pure)
#undef __pure
#endif /* __pure */

/**
 * @def __pure Shorthand for marked a function as purely function of its input
 * parameters and (possibly) global data.
 */
#define __pure __attribute__((pure))

#if defined(__noreturn)
#undef __noreturn
#endif /* __noreturn */

/**
 * @def __noreturn Shorthand for marked a function as one that will not return.
 */
#define __noreturn __attribute__((noreturn))

#ifdef __cplusplus
/**
 * @def BEGIN_C_DECLS Convenience macros for wrapping all C function, variable
 * declarations for C/C++ interoperability.
 */
#ifndef BEGIN_C_DECLS
#define BEGIN_C_DECLS extern "C" {
#endif

/***
 * @def END_C_DECLS Convenience macros for wrapping all C function, variable
 * declarations for C/C++ interoperability.
 */
#ifndef END_C_DECLS
#define END_C_DECLS }
#endif

#else

#define BEGIN_C_DECLS
#define END_C_DECLS

#endif

/*******************************************************************************
 * General Macros
 ******************************************************************************/
/* @cond INTERNAL */
#define STATIC_ASSERT_HELPER(expr, msg)                                 \
    (!!sizeof(struct { size_t int STATIC_ASSERTION__##msg : (expr) ? 1 : -1; }))
/* @endcond */

/**
 * @brief Compile time asserts for size, alignment, etc.
 *
 * Note that the message can't have spaces (i.e. this will fail):
 *
 * `STATIC_ASSERT(foo != 0,A failure message);`
 *
 * Proper usage:
 *
 * STATIC_ASSERT(foo != 0, A_failure_message);`
 */
#define STATIC_ASSERT(expr, msg)                                        \
    extern int(*assert_function__(void))[STATIC_ASSERT_HELPER(expr, msg)]

#endif /* INCLUDE_RCSW_COMMON_COMMON_H_ */
