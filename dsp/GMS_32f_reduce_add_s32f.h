
#ifndef __GMS_32F_REDUCE_ADD_S32F_H__
#define __GMS_32F_REDUCE_ADD_S32F_H__


/*
    Based on VOLK project.
    Modified by Bernard Gingold on:
    Date: 12-12-2020 10:40AM +00200
    contact: beniekg@gmail.com
    Few modification were added to original
    implementation (ICC pragmas, alignment directives and code layout rescheduled)
    
*/

/*
 * Copyright 2018 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#include <immintrin.h>
#include <cstdint>
#include "GMS_config.h"


#if !defined(DSP_32F_REDUCE_ADD_S32F_BLOCK)
    #define DSP_32F_REDUCE_ADD_S32F_BLOCK                       \
                __ATTR_ALIGN__(32) float tbuf[8] = {};          \
	       register __m256 accum = _mm256_setzero_ps();     \
	       register __m256 ymm0  = _mm256_setzero_ps();     \
	       int32_t idx = 0;                                 \
	       const int32_t len = npoints/8;                   \
	       float result = 0.0F;
#endif

       
	 __ATTR_HOT__
	 __ATTR_ALIGN__(32)
	float dsp_32f_reduce_add_s32f_u_avx(float * __restrict data,
	                                     const int32_t npoints); 
	                                     
	 __ATTR_HOT__
	 __ATTR_ALIGN__(32)
	float dsp_32f_reduce_add_s32f_a_avx(float * __restrict __ATTR_ALIGN__(32) data,
	                                     const int32_t npoints); 



#endif /*__GMS_32F_REDUCE_ADD_S32F_H__*/
