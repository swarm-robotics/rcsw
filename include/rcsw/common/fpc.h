/**
 * @file fpc.h
 * @ingroup common
 * @brief Function precondition/post-condition definitions (very useful!).
 *
 * Allows you to define a set of conditions that must be met for a function to
 * proceed/must be true when it returns. If any of the conditions fails, the
 * function will return the specified return value if FPC_RETURN=\ref FPC_RETURN
 * is passed at compile time. Otherwise, FPC_RETURN=\ref FPC_ABORT is assumed,
 * and the failure of any condition will cause the program to halt.
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

#ifndef INCLUDE_RCSW_COMMON_FPC_H_
#define INCLUDE_RCSW_COMMON_FPC_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <assert.h>
#include "rcsw/common/common.h"

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
/**
 * @brief Readability constants for determining whether or not the program
 * should halt if a function pre/post condition fails.
 */
#define FPC_ABORT 0

/**
 * @brief Readability constants for determining whether or not the program
 * should return an error code of some kind when a function pre/post condition
 * fails.
 */
#define FPC_RETURN 1

/**
 * @brief Sentinel value to pass as first argument to \ref FPC_CHECKV(), for use
 * in functions that return void.
 */
#define FPC_VOID 2

/*******************************************************************************
 * Function Precondition Checking Macros
 ******************************************************************************/
/**
 * @def FPC_CHECKNV_(X, v)
 *
 * Check a single function pre/post condition \a X, returning a value \a v if
 * the condition is not met. Requires that the function does not return
 * void. The value to return must be convertiable to the return type of the
 * function.
 */
#define FPC_CHECKNV_(X, v)                                              \
  {                                                                     \
      if (!(X)) {                                                       \
        errno = EINVAL;                                                 \
        return v;                                                       \
      }                                                                 \
  }

/**
 * @def FPC_CHECKV_(X, v)
 *
 * Check a single function pre/post condition \a X, returning if the condition
 * is not met. Requires that the function returns void. The value to return
 * (\a v) should always be \ref FPC_VOID.
 */
#define FPC_CHECKV_(X, v)                       \
  {                                             \
    if (!(X)) {                                 \
      errno = EINVAL;                           \
      return;                                   \
    }                                           \
  }

/**
 * @def FPC_ASSERT(X)
 *
 * Check a single function pre/post condition, halting the program if the
 * condition \a X fails.
 */
#define FPC_ASSERT(X) { assert(X); }
#define FPC_CHECK2(X, v) FPC_ASSERT(X)

#if(FPC_TYPE == FPC_RETURN)

/**
 * @def FPC_CHECK(v, ...)
 *
 * Function pre/post condition macro.
 *
 * It performs short circuit evaluation, in that if the check for precondition
 * i-1 fails, conditions [i,n] are not checked, and the function returns/program
 * exits (depending on configuration).
 *
 * \a v is returned if parameter validation fails. Do not use this macro in
 * functions that return void.
 *
 * \a ... is a list of conditions that need to be met before the function can
 * execute/must be true when the function returns.
 */
#define FPC_CHECK(v, ...)                               \
    { RCSW_XFOR_EACH2(FPC_CHECKNV_, v, __VA_ARGS__); }

/**
 * @def FPC_CHECKV(v, ...)
 *
 * Function pre/post condition macro for functions that return void.
 *
 * It performs short circuit evaluation, in that if the check for precondition
 * i-1 fails, conditions [i,n] are not checked, and the function returns/program
 * exits (depending on configuration).
 *
 * \a v is the value to return. Should always be \ref FPC_VOID
 *
 * \a ... is a list of conditions that need to be met before the function can
 * execute/must be true when the function returns.
 */
#define FPC_CHECKV(v, ...)                      \
  { RCSW_XFOR_EACH2(FPC_CHECKV_, v, __VA_ARGS__); }

#elif(FPC_TYPE == FPC_ABORT)

#define FPC_CHECK(v, ...)                       \
    { RCSW_XFOR_EACH2(FPC_CHECK2, v, __VA_ARGS__); }
#define FPC_CHECKV(v, ...)                       \
  { RCSW_XFOR_EACH2(FPC_CHECK2, v, __VA_ARGS__); }
#else
#define FPC_CHECK(v, ...)
#endif /* FPC_TYPE */

#endif /* INCLUDE_RCSW_COMMON_FPC_H_ */
