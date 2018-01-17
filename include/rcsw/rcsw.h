/**
 * @file rcsw.h
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

#ifndef INCLUDE_RCSW_H_
#define INCLUDE_RCSW_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "rcsw/common/common.h"
#include "rcsw/common/dbg.h"
#include "rcsw/common/exception.h"
#include "rcsw/common/fpc.h"
#include "rcsw/common/test_frmwk.h"

#include "rcsw/adapter/simple_image.h"

#include "rcsw/algorithm/algorithm.h"
#include "rcsw/algorithm/edit_dist.h"
#include "rcsw/algorithm/lcs.h"
#include "rcsw/algorithm/mcm_opt.h"
#include "rcsw/algorithm/search.h"
#include "rcsw/algorithm/sort.h"

#include "rcsw/ds/adj_list.h"
#include "rcsw/ds/adj_matrixs.h"
#include "rcsw/ds/bin_heap.h"
#include "rcsw/ds/bstree.h"
#include "rcsw/ds/bstree_node.h"
#include "rcsw/ds/csmatrix.h"
#include "rcsw/ds/darray.h"
#include "rcsw/ds/ds.h"
#include "rcsw/ds/fifo.h"
#include "rcsw/ds/hashmap.h"
#include "rcsw/ds/int_tree.h"
#include "rcsw/ds/int_tree_node.h"
#include "rcsw/ds/llist.h"
#include "rcsw/ds/llist_node.h"
#include "rcsw/ds/ostree.h"
#include "rcsw/ds/ostree_node.h"
#include "rcsw/ds/rawfifo.h"
#include "rcsw/ds/rbtree.h"
#include "rcsw/ds/rbuffer.h"
#include "rcsw/ds/static_matrix.h"

#include "rcsw/multiprocess/mpi_radix_sort.h"
#include "rcsw/multiprocess/mpi_spmv_mult.h"
#include "rcsw/multiprocess/procm.h"

#include "rcsw/multithread/"
#include "rcsw/multithread/mpool.h"
#include "rcsw/multithread/mt_bsem.h"
#include "rcsw/multithread/mt_cond.h"
#include "rcsw/multithread/mt_csem.h"
#include "rcsw/multithread/mt_cvm.h"
#include "rcsw/multithread/mt.h"
#include "rcsw/multithread/mt_mutex.h"
#include "rcsw/multithread/mt_queue.h"
#include "rcsw/multithread/mt_rdwr_lock.h"
#include "rcsw/multithread/omp_kernel2d.h"
#include "rcsw/multithread/omp_radix_sort.h"
#include "rcsw/multithread/threadm.h"

#include "rcsw/pulse/pulse.h"
#include "rcsw/stdio/sstdio.h"
#include "rcsw/stdio/sstring.h"
#include "rcsw/utils/checksum.h"
#include "rcsw/utils/hash.h"
#include "rcsw/utils/mem.h"
#include "rcsw/utils/time_utils.h"
#include "rcsw/utils/utils.h"

/** \mainpage
*
* @defgroup ds ds
* @brief Data structures library
* @defgroup algorithm algorithm
* @brief Collection of useful algorithms for sorting, searching,
* matrix/list/sequence operations, etc.
*
* @defgroup multiprocess multiprocess
* @brief Functionality for doing things in a multi-process environment, like
* sorting.
* @defgroup multithread multithread
* @brief Functionality for doing things in a multi-threaded environment, like
* sorting, locking, synchronizing, etc.
* @defgroup sstdio sstdio
* @brief Very simple I/O library suitable for bare metal applications.
* @defgroup utils utils
* @brief Miscellaneous things that I found interesting or useful, such as time
* manipulation, checksumming, hashing, and memory manipulation/dumping (for
* embedded systems).
* @defgroup pulse pulse
* @brief Fully connected publisher-subscriber software network where everyone
* can talk to everyone else.
* @defgroup adapter adapter
*/

#endif /* INCLUDE_RCSW_H_ */
