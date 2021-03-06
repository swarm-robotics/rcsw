/**
 * @file sort.h
 * @ingroup algorithm
 * @brief Collection of sorting algorithms.
 *
 * Quicksort (iterative and recursive), mergesort (linked lists), radix sort
 * (arrays), counting sort (arrays).
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

#ifndef INCLUDE_RCSW_ALGORITHM_SORT_H_
#define INCLUDE_RCSW_ALGORITHM_SORT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcsw/common/common.h"

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
/**
 * @brief The different types flavors of each sort that are available
 *
 */
enum alg_sort_type {
    QSORT_ITER,  /// Iterative quicksort (arrays only).
    QSORT_REC,   /// Recursive quicksort (arrays only).
    MSORT_ITER,  /// Iterative mergesort (linked lists only).
    MSORT_REC    /// Recursive mergesort (linked lists only).
};

/*******************************************************************************
 * Function prototypes
 ******************************************************************************/
BEGIN_C_DECLS

/**
 * @brief Sort an array using quicksort
 *
 * This routine sorts an array by using a recursive implementation of
 * quicksort, rather than an iterative one, so some efficiency is lost.
 *
 * @param a The input array
 * @param min_index Starting index
 * @param max_index Ending index
 * @param el_size Size of elements in bytes
 * @param cmpe Comparision function for elements
 */
void qsort_rec(void *a, int min_index, int max_index,
               size_t el_size,
               int (*cmpe)(const void *const e1, const void *const e2));

/**
 * @brief Sort an array using quicksort
 *
 * This routine sorts an array by using an iterative, rather than a recursive,
 * implementation.
 *
 * @param a Array to sort
 * @param max_index Starting index
 * @param el_size  Size of elements in bytes
 * @param cmpe Comparision function for elements
 */
void qsort_iter(void *a, int max_index, size_t el_size,
                int (*cmpe)(const void *const e1, const void *const e2));

/**
 * @brief Sort a linked list using iterative mergesort
 *
 * This function sorts a linked list using at iterative implementation of//@}
 * mergesort It has minimal stack/memory requirements, beyond a few local
 * variables.  It can be used to sort any singly or doubly linked list. It is
 * assumed that the list has at least 2 items in it.
 *
 * @param list The list to sort
 * @param cmpe A comparison function for the data managed by each node
 * @param isdouble TRUE if the list to be sorted is doubly linked
 *
 * @return A pointer to the sorted list
 *
 */
struct llist_node *mergesort_iter(struct llist_node *list,
                                  int (*cmpe)(const void *const e1,
                                              const void *const e2),
                                  bool_t isdouble);

/**
  * @brief Sort a linked list using recursive mergesort
  *
  * This function sorts a linked list using a recursive implementation of
  * mergesort. It has a complexity of O(NLogN). It can be used to sort any
  * singly or doubly linked list.
  *
  * @param list The list to sort
  * @param cmpe A comparison function for the data managed by each node
  * @param isdouble TRUE if the list to be sorted is doubly linked
  *
  * @return A pointer to the sorted list
  */
struct llist_node *mergesort_rec(struct llist_node *list,
                                 int (*cmpe)(const void *const e1,
                                             const void *const e2),
                                 bool_t isdouble);

/**
 * @brief Sort an array using insertion sort
 *
 * @param arr The array to sort
 * @param n_elts # elements in the array
 * @param el_size Size of elements in the array in bytes
 * @param cmpe Comparison function for elements
 */
void insertion_sort(void *arr, size_t n_elts, size_t el_size,
                    int (*cmpe)(const void *const e1, const void *const e2));

/**
 * @brief Sort an array of non-negative integers using radix sort
 *
 * @param arr The array to sort
 * @param tmp Temporary array to hold elements as they are sorted. Must be at
 * least as large as the array to sort
 * @param n_elts # elements in array
 * @param base Base of numbers (10, 8, 16, etc.)
 */
void radix_sort(size_t *arr, size_t *tmp, size_t n_elts,
                size_t base);

/**
 * @brief Sort an array of non-negative ints via counting sort, as part of radix
 * sort
 *
 * @param arr The array to sort
 * @param tmp Temporary array to hold elements as they are sorted. Must be at
 * least as large as the array to sort
 * @param n_elts # elements in array
 * @param digit Current digit being processed
 * @param base The base of the #s to be sorted (10, 16, etc.)
 *
 * @return \ref status_t
 */
status_t radix_counting_sort(size_t *arr, size_t* tmp,
                             size_t n_elts, size_t digit, size_t base);

status_t radix_sort_prefix_sum(const size_t* arr, size_t n_elts,
                               size_t base, size_t digit,
                               size_t* prefix_sums);
END_C_DECLS

#endif /*  INCLUDE_RCSW_ALGORITHM_SORT_H_  */
