/**
 * @file mt_cond.h
 * @ingroup multithread
 * @brief Wrapper for pthread_cond_t.
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

#ifndef INCLUDE_RCSW_MULTITHREAD_MT_COND_H_
#define INCLUDE_RCSW_MULTITHREAD_MT_COND_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <pthread.h>
#include "rcsw/multithread/mt.h"
#include "rcsw/multithread/mt_mutex.h"
#include "rcsw/multithread/mt_cond.h"
#include "rcsw/common/common.h"

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
/**
 * @brief Wrapper around POSIX pthread condition variables. In the future, this
 * may incorporate condition variables from other operating systems.
 */
typedef struct {
    pthread_cond_t cv;
    uint32_t flags;
} mt_cond_t;

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
BEGIN_C_DECLS

/**
 * @brief Initialize the signal condition.
 *
 * @param cv_in cv to initialize. Can be NULL if \ref MT_APP_DOMAIN_MEM passed
 * @param flags Configuration flags.
 *
 * @return The initialized signal condition, or NULL if an ERROR occurred.
 */
mt_cond_t* mt_cond_init(mt_cond_t * cv_in, uint32_t flags);

/**
 * @brief Destroy the signal condition.
 *
 * @param cv The cv handle.
 */
void mt_cond_destroy(mt_cond_t *cv);

/**
 * @brief Signal on a condition variable.
 *
 * @param cv The cv handle.
 *
 * @return \ref status_t.
 */
status_t mt_cond_signal(mt_cond_t * cv);

/**
 * @brief Broadcast to everyone waiting on a condition variable.
 *
 * This function unblocks all threads currently blocked on the condition
 * variable. Each thread, upon its return from cond_wait() or cond_timedwait()
 * will own the mutex it entered its waiting function with.
 *
 * @param cv The cv handle.
 *
 * @return \ref status_t.
 */
status_t mt_cond_broadcast(mt_cond_t * cv);

/**
 * @brief Unconditional wait on a condition variable.
 *
 * @param cv The cv handle.
 * @param mutex The mutex the wait pairs with.
 *
 * @return \ref status_t.
 */
status_t mt_cond_wait(mt_cond_t * cv, mt_mutex_t * mutex);

/**
 * @brief Timed wait on a condition variable.
 *
 * @param cv The cv handle.
 * @param mutex The mutex the wait pairs with.
 * @param to A RELATIVE timeout, NOT an ABSOLUTE timeout, as the POSIX standard
 * specifies. This function converts the relative timeout to absolute timeout
 * required.
 *
 * @return \ref status_t.
 */
status_t mt_cond_timedwait(mt_cond_t * cv, mt_mutex_t * mutex,
                           const struct timespec * to);

END_C_DECLS

#endif /* INCLUDE_RCSW_MULTITHREAD_MT_COND_H_ */
