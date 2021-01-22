/**
 * @file mt_csem.c
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
#include "rcsw/multithread/mt_csem.h"
#include "rcsw/common/common.h"
#include "rcsw/common/dbg.h"
#include "rcsw/common/fpc.h"
#include "rcsw/utils/time_utils.h"

/*******************************************************************************
 * API Functions
 ******************************************************************************/
BEGIN_C_DECLS

mt_csem_t* mt_csem_init(mt_csem_t* const sem_in,
                        bool_t shared,
                        size_t value,
                        uint32_t flags) {
  mt_csem_t* sem = NULL;
  if (flags & MT_APP_DOMAIN_MEM) {
    sem = sem_in;
  } else {
    sem = calloc(1, sizeof(mt_csem_t));
  }
  RCSW_CHECK_PTR(sem);
  sem->flags = flags;
  RCSW_CHECK(0 == sem_init(&sem->sem, shared, (unsigned int)value));
  return sem;

error:
  return NULL;
} /* mt_csem_init() */

void mt_csem_destroy(mt_csem_t* sem) {
  RCSW_FPC_V(NULL != sem);

  sem_destroy(&sem->sem);
  if (sem->flags & MT_APP_DOMAIN_MEM) {
    free(sem);
  }
} /* mt_csem_destroy() */

status_t mt_csem_wait(mt_csem_t* sem) {
  RCSW_FPC_NV(ERROR, NULL != sem);
  RCSW_CHECK(0 == sem_wait(&sem->sem));
  return OK;

error:
  return ERROR;
} /* mt_csem_wait() */

status_t mt_csem_trywait(mt_csem_t* sem) {
  RCSW_FPC_NV(ERROR, NULL != sem);
  RCSW_CHECK(0 == sem_trywait(&sem->sem));
  return OK;

error:
  return ERROR;
} /* mt_csem_wait() */

status_t mt_csem_timedwait(mt_csem_t* const sem,
                           const struct timespec* const to) {
  RCSW_FPC_NV(ERROR, NULL != sem, NULL != to);
  struct timespec ts = {.tv_sec = 0, .tv_nsec = 0};
  RCSW_CHECK(OK == time_ts_ref_conv(to, &ts));
  RCSW_CHECK(0 == sem_timedwait(&sem->sem, &ts));

  return OK;
error:
  return ERROR;
} /* mt_csem_timedwait() */

status_t mt_csem_post(mt_csem_t* sem) {
  RCSW_FPC_NV(ERROR, NULL != sem);
  RCSW_CHECK(0 == sem_post(&sem->sem));
  return OK;

error:
  return ERROR;
} /* mt_csem_post() */

END_C_DECLS
