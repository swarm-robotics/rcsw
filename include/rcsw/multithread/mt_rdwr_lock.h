/**
 * @file mt_rdwr_lock.h
 * @ingroup multithread
 * @brief Implementation of fair reader-writer lock.
 *
 * Guarantees that no reader or writer will starve.
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

#ifndef INCLUDE_RCSW_MULTITHREAD_MT_RDWR_LOCK_H_
#define INCLUDE_RCSW_MULTITHREAD_MT_RDWR_LOCK_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcsw/multithread/mt_csem.h"
#include "rcsw/common/common.h"

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
/**
 * @brief Fair reader-writer lock that guarantees that neither readers nor
 * writers will starve.
 */
typedef struct {
    mt_csem_t order;  /* used to form a queue of readers/writers*/
    mt_csem_t access; /* exclusive access semaphore */
    mt_csem_t read;   /* semaphore for updating n_readers */
    size_t n_readers;    /* # of readers currently accessing resource */
    uint32_t flags;
} mt_rdwr_lock_t;

/*******************************************************************************
 * Function Prototypes
 ******************************************************************************/
BEGIN_C_DECLS

/**
 * @brief Initialize a reader/writer fair lock
 *
 * @param rdwr_in Lock to initialize. Can be NULL if \ref MT_APP_DOMAIN_MEM
 * passed @param flags Configuration flags
 *
 * @return The initialized RDWR lock, or NULL if an ERROR occurred.
 */
status_t mt_rdwr_lock_init(mt_rdwr_lock_t *const rdwr_in,
                           uint32_t flags) RCSW_CHECK_RET;

/**
 * @brief Destroy a reader/writer fair lock
 *
 * Any further use of the lock after calling this function is undefined.
 *
 * @param rdwr The lock handle.
 */
void mt_rdwr_lock_destroy(mt_rdwr_lock_t *const rdwr);

/**
 * @brief Exit a critical section requiring writer privileges.
 *
 * This function is part of a fair (i.e. no rd/wr preference) sequence
 * that guarantees that no reader or write will starve.
 *
 * @param rdwr The lock handle.
 */
void mt_rdwr_lock_wr_exit(mt_rdwr_lock_t *const rdwr);

/**
 * @brief Enter a critical section requiring writer privileges.
 *
 * This function is part of a fair (i.e. no rd/wr preference) sequence
 * that guarantees that no reader or write will starve.
 *
 * @param rdwr The lock handle.
 */
void mt_rdwr_lock_wr_enter(mt_rdwr_lock_t *const rdwr);

/**
 * @brief Enter a critical section requiring writer privileges with a timeout.
 *
 * This function is part of a fair (i.e. no rd/wr preference) sequence
 * that guarantees that no reader or write will starve.
 *
 * @param rdwr The lock handle.
 * @param to A RELATIVE timeout, NOT an ABSOLUTE timeout, as the POSIX standard
 * specifies. This function converts the relative timeout to absolute timeout
 * required.
 *
 * @return \ref status_t.
 */
status_t mt_rdwr_lock_timed_wr_enter(mt_rdwr_lock_t *const rdwr,
                                     const struct timespec *const to);

/**
 * @brief Exit a critical section requiring reader privileges.
 *
 * @param rdwr The lock handle.
 */
void mt_rdwr_lock_rd_exit(mt_rdwr_lock_t *rdwr);

/**
 * @brief Enter a critical section requiring reader privileges.
 *
 * @param rdwr The lock handle.
 */
void mt_rdwr_lock_rd_enter(mt_rdwr_lock_t *rdwr);

/**
 * @brief Enter a critical section requiring reader privileges with a timeout.
 *
 * @param rdwr The lock handle.
 * @param to A RELATIVE timeout, NOT an ABSOLUTE timeout, as the POSIX standard
 * specifies. This function converts the relative timeout to absolute timeout
 * required.
 *
 * @return \ref status_t.
 */
status_t mt_rdwr_lock_timed_rd_enter(mt_rdwr_lock_t *const rdwr,
                                     const struct timespec *const to);
END_C_DECLS

#endif /* INCLUDE_RCSW_MULTITHREAD_MT_RDWR_LOCK_H_ */
