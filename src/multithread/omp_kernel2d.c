/**
 * @file omp_kernel2d.c
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
#include "rcsw/multithread/omp_kernel2d.h"
#include "rcsw/adapter/simple_image.h"
#include "rcsw/common/dbg.h"
#include "rcsw/common/fpc.h"

/*******************************************************************************
 * API Functions
 ******************************************************************************/
status_t omp_kernel2d_convolve1(float const* const __restrict__ input,
                                float kernel[3][3],
                                size_t width,
                                size_t height,
                                float* const __restrict__ output) {
  RCSW_FPC_NV(ERROR, NULL != input, NULL != output);
#pragma omp parallel
  {
/* just copy boundaries */
#pragma omp for schedule(static) nowait
    for (size_t j = 0; j < width; ++j) {
      output[j + (0)] = input[j + (0)];
      output[j + ((height - 1) * width)] = input[j + ((height - 1) * width)];
    }
#pragma omp for schedule(static) nowait
    for (size_t i = 0; i < height; ++i) {
      output[0 + (i * width)] = input[0 + (i * width)];
      output[(width - 1) + (i * width)] = input[(width - 1) + (i * width)];
    }

#pragma omp for schedule(static)
    for (size_t i = 1; i < height - 1; ++i) {
      for (size_t j = 1; j < width - 1; ++j) {
        float v = 0.;
        for (int is = 0; is < 3; ++is) {
          for (int js = 0; js < 3; ++js) {
            /* global image indices */
            int const g_i = i + (is - 1);
            int const g_j = j + (js - 1);

            v += kernel[is][js] * input[g_j + (g_i * width)];
          } /* for(js..) */
        }   /* for(is..) */

        output[j + (i * width)] = v;
      } /* for(j..) */
    }   /* for(i..) */
  }     /* parallel.. */
  return OK;
} /* omp_kernel2d_convolve1() */
