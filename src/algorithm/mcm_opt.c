/**
 * @file mcm_opt.c
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

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcsw/algorithm/mcm_opt.h"
#include <limits.h>
#include "rcsw/common/dbg.h"
#include "rcsw/common/fpc.h"

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/
BEGIN_C_DECLS

/*******************************************************************************
 * Forward Declarations
 ******************************************************************************/
/**
 * @brief Print the optimal parenthesization to stdout
 *
 * Since you want m[1][n], call with i=1, j=length-1
 *
 * @param arr Array containing parenthesization info
 * @param i Current index into row dimension of matrix
 * @param j Current index into column dimension of matrix
 * @param length The length of the matrix chain
 *
 */
static void mcm_opt_print_parens(const size_t* arr,
                                 size_t i,
                                 size_t j,
                                 size_t length);

/**
 * @brief Report optimal parenthesization
 *
 * Since you want m[1][n], call with i=1, j=length-1
 *
 * @param arr Array containing parenthesization info
 * @param i Current index into row dimension of matrix
 * @param j Current index into column dimension of matrix
 * @param length The length of the matrix chain
 * @param ordering Array containing indices of matrices in the chain, to be
 * filled
 * @param count How many positions in the ordering array have been filled so
 * far. Pass this as 0.
 *
 */
static void mcm_opt_report_parens(const size_t* arr,
                                  size_t i,
                                  size_t j,
                                  size_t length,
                                  size_t* __restrict__ ordering,
                                  size_t* __restrict__ count);

/*******************************************************************************
 * API Functions
 ******************************************************************************/
status_t mcm_opt_init(struct mcm_optimizer* mcm,
                      const size_t* matrices,
                      size_t size) {
  RCSW_FPC_NV(ERROR, NULL != mcm, NULL != matrices, size >= 2);
  mcm->matrices = matrices;
  mcm->size = size;

  mcm->results = malloc(size * size * sizeof(size_t));
  RCSW_CHECK_PTR(mcm->results);
  memset(mcm->results, 0, size * size * sizeof(size_t));

  mcm->route = malloc(size * size * sizeof(size_t));
  RCSW_CHECK_PTR(mcm->route);
  memset(mcm->route, 0, size * size * sizeof(size_t));
  return OK;

error:
  mcm_opt_destroy(mcm);
  return ERROR;
} /* mcm_opt_init() */

void mcm_opt_destroy(struct mcm_optimizer* mcm) {
  if (!mcm) {
    return;
  }
  if (mcm->results) {
    free(mcm->results);
  }
  if (mcm->route) {
    free(mcm->route);
  }
} /* mcm_opt_destroy() */

status_t mcm_opt_optimize(struct mcm_optimizer* mcm) {
  RCSW_FPC_NV(ERROR, NULL != mcm);

  size_t n = mcm->size - 1;
  size_t i, j, k, q, num = 0;

  /*
   * A[i][i]Only one matrix multiplication, so the number 0, M[i][i]=0; These
   * are the entries in the main diagonal of m.
   */
  for (i = 1; i < mcm->size; i++) {
    mcm->results[i + mcm->size * i] = 0;
  }
  /*
   * i represents the matrix chain length we are currently optimizing over. We
   *  start at two, because the cost of a chain length of 1 is 0 (see above)
   */
  for (i = 2; i <= n; i++) {
    /*
     * loop over all possible partition points k that result in a chain of
     * length i
     */
    for (j = 1; j <= n - i + 1; j++) {
      k = j + i - 1;
      /*
       * m[j][k] is the optimal results from j to k using the
       * optimal partitioning. Initialize to a very large #.
       */
      mcm->results[j + k * mcm->size] = INT_MAX;
      /*
       * Compute the cost of splitting the current problem at point
       * k. Cost is cost of sub-chain to left of k + cost of sub-chain to
       * right of k (at k+1), + a const # of scalar multiplications
       * derived from the dimensions of the two multiplied matrices.
       *
       * As you are looping through, if you find a better result update
       * m[i][j] accordingly.
       */
      for (q = j; q <= k - 1; q++) {
        num = mcm->results[j + q * mcm->size] +
              mcm->results[q + 1 + mcm->size * k] +
              mcm->matrices[j - 1] * mcm->matrices[q] * mcm->matrices[k];
        if (num < mcm->results[j + mcm->size * k]) {
          mcm->results[j + mcm->size * k] = num;
          mcm->route[j + mcm->size * k] = q;
        }
      } /* for(q=j)... */
    }   /* for(j=1)... */
  }     /* for(i=2)... */
  mcm->min_mults = mcm->results[1 + mcm->size * (mcm->size - 1)];
  return OK;
} /* mcm_opt_optimize() */

status_t mcm_opt_report(const struct mcm_optimizer* mcm, size_t* ordering) {
  RCSW_FPC_NV(ERROR, NULL != mcm, NULL != ordering);
  size_t count = 0;
  mcm_opt_report_parens(
      mcm->route, 1, mcm->size - 1, mcm->size, ordering, &count);
  return OK;
} /* mcm_opt_report() */

status_t mcm_opt_print(const struct mcm_optimizer* mcm) {
  RCSW_FPC_NV(ERROR, NULL != mcm);
  printf("Minimum scalar multiplications: %zu\n", mcm->min_mults);
  printf("Parenthesization:\n");
  mcm_opt_print_parens(mcm->route, 1, mcm->size - 1, mcm->size);
  printf("\n");
  return OK;
} /* mcm_opt_print() */

/*******************************************************************************
 * Static Functions
 ******************************************************************************/
static void mcm_opt_print_parens(const size_t* arr,
                                 size_t i,
                                 size_t j,
                                 size_t length) {
  if (i == j) {
    printf("A%zu", i);
  } else {
    printf("(");
    size_t k = arr[i + length * j];
    mcm_opt_print_parens(arr, i, k, length);
    mcm_opt_print_parens(arr, k + 1, j, length);
    printf(")");
  }
} /* mcm_opt_print_parens() */

static void mcm_opt_report_parens(const size_t* arr,
                                  size_t i,
                                  size_t j,
                                  size_t length,
                                  size_t* ordering,
                                  size_t* count) {
  if (i == j) {
  } else {
    size_t k = arr[i + length * j];
    mcm_opt_report_parens(arr, i, k, length, ordering, count);
    mcm_opt_report_parens(arr, k + 1, j, length, ordering, count);
    if (i == k) {
      ordering[*count] = k;
      *count += 1;
    }
    if (k + 1 == j) {
      ordering[*count] = k + 1;
      *count += 1;
    }
  }
} /* mcm_opt_report_parens() */

END_C_DECLS
