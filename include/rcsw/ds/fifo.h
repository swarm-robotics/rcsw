/**
 * @file fifo.h
 * @ingroup ds
 * @brief Implementation of simple FIFO.
 *
 * This implementation is more full-featured than the "raw" FIFO, but may not be
 * safe to use in ISRs.
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

#ifndef INCLUDE_RCSW_DS_FIFO_H_
#define INCLUDE_RCSW_DS_FIFO_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcsw/ds/rbuffer.h"
#include "rcsw/common/fpc.h"

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
/**
 * @brief FIFO: First In First Out general purpose FIFO.
 */
struct fifo {
    struct rbuffer rb;  /// Underlying ringbuffer the FIFO is built on top of.
    uint32_t flags;     /// Run-time configuration parameters.
};

BEGIN_C_DECLS

/*******************************************************************************
 * Inline Functions
 ******************************************************************************/
/**
 * @brief Determine if the FIFO is currently full
 *
 * @param fifo The FIFO handle
 *
 * @return \ref bool_t
 */
static inline bool_t fifo_isfull(const struct fifo* const fifo) {
    RCSW_FPC_NV(FALSE, NULL != fifo);
    return rbuffer_isfull(&fifo->rb);
}

/**
 * @brief Determine if the FIFO is currently empty
 *
 * @param fifo The FIFO handle
 *
 * @return \ref bool_t
 */
static inline bool_t fifo_isempty(const struct fifo* const fifo) {
    RCSW_FPC_NV(FALSE, NULL != fifo);
    return rbuffer_isempty(&fifo->rb);
}

/**
 * @brief Determine # elements currently in the FIFO.
 *
 * @param fifo The FIFO handle.
 *
 * @return # elements in FIFO, or 0 on ERROR.
 */

static inline size_t fifo_n_elts(const struct fifo* const fifo) {
    RCSW_FPC_NV(0, NULL != fifo);
    return rbuffer_n_elts(&fifo->rb);
}

/**
 * @brief Get the FIFO capacity.
 *
 * @param fifo The FIFO handle.
 *
 * @return Capacity of the FIFO, or 0 on ERROR.
 */
static inline size_t fifo_capacity(const struct fifo* const fifo) {
    RCSW_FPC_NV(0, NULL != fifo);
    return rbuffer_capacity(&fifo->rb);
}

/**
 * @brief Get the first FIFO item without removing it.
 *
 * @param fifo The FIFO handle.
 *
 * @return Pointer to the first element, or NULL if no such element or an error
 * occurred.
 */
static inline void* fifo_front(const struct fifo* const fifo) {
    RCSW_FPC_NV(0, NULL != fifo);
    return rbuffer_front(&fifo->rb);
}

/**
 * @brief Calculate the # of bytes that the FIFO will require if \ref
 * DS_APP_DOMAIN_DATA is passed to manage a specified # of elements of a
 * specified size
 *
 * @param max_elts # of desired elements the FIFO will hold
 * @param el_size size of elements in bytes
 *
 * @return The total # of bytes the application would need to allocate
 */
static inline size_t fifo_element_space(size_t max_elts, size_t el_size) {
    return rbuffer_element_space(max_elts, el_size);
}

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
/**
 * @brief Initialize a FIFO.
 *
 * @param fifo_in An application allocated handle for the FIFO. Can be NULL,
 * depending on if \ref DS_APP_DOMAIN_HANDLE is passed or not.
 * @param params The initialization parameters.
 *
 * @return The initialized FIFO, or NULL if an error occurred.
 */
struct fifo *fifo_init(struct fifo *fifo_in,
                       const struct ds_params * params) RCSW_CHECK_RET;

/**
 * @brief Destroy a FIFO.
 *
 * Any further use of the FIFO after this function is called is undefined.
 *
 * @param fifo The FIFO to destroy.
 */
void fifo_destroy(struct fifo *fifo);

/**
 * @brief Enqueue an element into the FIFO.
 *
 * @param fifo The FIFO handle.
 * @param e The element to enqueue. Cannot be NULL.
 *
 * @return \ref status_t.
 */
status_t fifo_enq(struct fifo * fifo, const void * e);

/**
 * @brief Dequeue an element from the FIFO.
 *
 * @param fifo The FIFO handle.
 * @param e The element to dequeue into from the FIFO.
 *
 * @return \ref status_t.
 */
status_t fifo_deq(struct fifo * fifo, void * e);

/**
 * @brief Clear a FIFO.
 *
 * Empty the FIFO, but do not deallocate its memory.
 *
 * @return \ref status_t.
 */
status_t fifo_clear(struct fifo * fifo);

/**
 * @brief Apply an operation to all elements of the FIFO.
 *
 * @param fifo The FIFO handle.
 * @param f A function pointer which will be called for every element in the.
 * FIFO. This function CAN modify FIFO elements.
 *
 * @return \ref status_t.
 */
status_t fifo_map(struct fifo * fifo, void (*f)(void *e));

/**
 * @brief Compute a cumulative SOMETHING over all elements of a FIFO.
 *
 * @param fifo The FIFO handle.
 * @param f A function point which will be called for every element in the
 * FIFO. This function CAN modify FIFO elements.
 * @param result The initial value for the cumulative SOMETHING to be
 * computed. This will be passed to each invocation of the callback.
 *
 * @return \ref status_t.
 */
status_t fifo_inject(struct fifo * fifo,
                     void (*f)(void *e, void *res), void *result);

/**
 * @brief Print a FIFO.
 *
 * @param fifo The FIFO handle.
 **/
void fifo_print(struct fifo * fifo);

END_C_DECLS

#endif /*  INCLUDE_RCSW_DS_FIFO_H_  */
