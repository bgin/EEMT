



/*
    Based on VOLK project.
    Modified by Bernard Gingold on:
    Date: 02-10-2021 11:32PM +00200
    contact: beniekg@gmail.com
    Few modification were added to original
    implementation (ICC pragmas, alignment directives and code layout rescheduled,
    unrolling completely 2-iteration for-loops)
    
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


#include "GMS_32f_cos_32f.h"
#include "GMS_cephes.h"



	 void dsp_32f_cos_32f_avx512_u_looped(float * __restrict b,
	                                      const float * __restrict a,
					      const int32_t npoints) {
                DSP_32F_COS_32F_AVX512_BLOCK
#if defined __ICC || defined __INTEL_COMPILER
#pragma code_align(32)
#endif
                for(; idx != len; ++idx) {
                     _mm_prefetch((const char*)&a+32,_MM_HINT_T0);
		     aVal = _mm512_loadu_ps(a);
		     s = (__m512)(_mm512_and_si512((__m512i)(aVal),
		                             _mm512_set1_epi32(0x7fffffff)));
                     q = _mm512_cvtps_epi32(_mm512_floor_ps(_mm512_mul_ps(s, m4pi)));
                     r = _mm512_cvtepi32_ps(_mm512_add_epi32(q,
		                             _mm512_and_si512(q, ones)));
                     s = _mm512_fnmadd_ps(r, pio4A, s);
                     s = _mm512_fnmadd_ps(r, pio4B, s);
                     s = _mm512_fnmadd_ps(r, pio4C, s);
		     s = _mm512_div_ps(s,feight);
		     s = _mm512_mul_ps(s,s);
		     s = _mm512_mul_ps(
                                 _mm512_fmadd_ps(
                                         _mm512_fmsub_ps(
                                             _mm512_fmadd_ps(
					          _mm512_fmsub_ps(s, cp5, cp4), s, cp3), s, cp2),
                                             s,
                                        cp1),
                                 s);
		     t0 = _mm512_sub_ps(ffours,a);
		     s  = _mm512_mul_ps(s,t0);
		     s  = _mm512_mul_ps(s,t0);
		     s  = _mm512_mul_ps(s,t0);
		     s  = _mm512_mul_ps(s,finv2);
		     sine = _mm512_sqrt_ps(_mm512_mul_ps(
		                             _mm512_sub_ps(ftwos, s), s));
                     cosine = _mm512_sub_ps(fones, s);
		     condition1 = _mm512_cmpneq_epi32_mask(
                                          _mm512_and_si512(
					           _mm512_add_epi32(q, ones), twos), zeros);
		     condition2 = _mm512_cmpneq_epi32_mask(
                                           _mm512_and_si512(_mm512_add_epi32(q, twos), fours), zeros);
                     cosine = _mm512_mask_blend_ps(condition1, cosine, sine);
                     cosine = _mm512_mask_mul_ps(cosine, condition2, cosine, _mm512_set1_ps(-1.f));
		     _mm512_storeu_ps(b,cosine);
		     a += 16;
		     b += 16;
		}
		idx = len*16;
#if defined __ICC || defined __INTEL_COMPILER
#pragma loop_count min(1),avg(8),max(15)
#endif
              for(; idx != npoints; ++idx) {
                  b[i] = ceph_cosf(a[i]);
	      }		
	}



	
	 void dsp_32f_cos_32f_avx512_a_looped(float * __restrict __ATTR_ALIGN__(64) b,
	                                      const float * __restrict __ATTR_ALIGN__(64) a,
					      const int32_t npoints) {
                DSP_32F_COS_32F_AVX512_BLOCK
#if defined __ICC || defined __INTEL_COMPILER
              __assume_aligned(b,64);
	      __assume_aligned(a,64);
#elif defined __GNUC__ && !defined __INTEL_COMPILER
              b = (float*)__builtin_assume_aligned(b,64);
	      a = (float*)__builtin_assume_aligned(a,64);
#endif	
#if defined __ICC || defined __INTEL_COMPILER
#pragma code_align(32)
#endif
                for(; idx != len; ++idx) {
                     _mm_prefetch((const char*)&a+32,_MM_HINT_T0);
		     aVal = _mm512_load_ps(a);
		     s = (__m512)(_mm512_and_si512((__m512i)(aVal),
		                             _mm512_set1_epi32(0x7fffffff)));
                     q = _mm512_cvtps_epi32(_mm512_floor_ps(_mm512_mul_ps(s, m4pi)));
                     r = _mm512_cvtepi32_ps(_mm512_add_epi32(q,
		                             _mm512_and_si512(q, ones)));
                     s = _mm512_fnmadd_ps(r, pio4A, s);
                     s = _mm512_fnmadd_ps(r, pio4B, s);
                     s = _mm512_fnmadd_ps(r, pio4C, s);
		     s = _mm512_div_ps(s,feight);
		     s = _mm512_mul_ps(s,s);
		     s = _mm512_mul_ps(
                                 _mm512_fmadd_ps(
                                         _mm512_fmsub_ps(
                                             _mm512_fmadd_ps(
					          _mm512_fmsub_ps(s, cp5, cp4), s, cp3), s, cp2),
                                             s,
                                        cp1),
                                 s);
		     t0 = _mm512_sub_ps(ffours,a);
		     s  = _mm512_mul_ps(s,t0);
		     s  = _mm512_mul_ps(s,t0);
		     s  = _mm512_mul_ps(s,t0);
		     s  = _mm512_mul_ps(s,finv2);
		     sine = _mm512_sqrt_ps(_mm512_mul_ps(
		                             _mm512_sub_ps(ftwos, s), s));
                     cosine = _mm512_sub_ps(fones, s);
		     condition1 = _mm512_cmpneq_epi32_mask(
                                          _mm512_and_si512(
					           _mm512_add_epi32(q, ones), twos), zeros);
		     condition2 = _mm512_cmpneq_epi32_mask(
                                           _mm512_and_si512(_mm512_add_epi32(q, twos), fours), zeros);
                     cosine = _mm512_mask_blend_ps(condition1, cosine, sine);
                     cosine = _mm512_mask_mul_ps(cosine, condition2, cosine, _mm512_set1_ps(-1.f));
		     _mm512_store_ps(b,cosine);
		     a += 16;
		     b += 16;
		}
		idx = len*16;
#if defined __ICC || defined __INTEL_COMPILER
#pragma loop_count min(1),avg(8),max(15)
#endif
              for(; idx != npoints; ++idx) {
                  b[i] = ceph_cosf(a[i]);
	      }		
	}



	
          __m512 dsp_32f_cos_32_avx512(const __m512 v) {

	           const __m512 m4pi    = _mm512_set1_ps(1.273239544735162542821171882678754627704620361328125);              
	           const __m512 pio4A   = _mm512_set1_ps(0.7853981554508209228515625);                                                                   
	           const __m512 pio4B   = _mm512_set1_ps(0.794662735614792836713604629039764404296875e-8);                    
	           const __m512 pio4C   = _mm512_set1_ps(0.306161699786838294306516483068750264552437361480769e-16);          
	           const __m512 feight  = _mm512_set1_ps(8.0F);                                                                
	           const __m512 ffours  = _mm512_set1_ps(4.0F);                                                              
	           const __m512 ftwos   = _mm512_set1_ps(2.0F);                                                               
	           const __m512 finv2   = _mm512_set1_ps(0.5f);						                   
	           const __m512 fones   = _mm512_set1_ps(1.0F);                                                               
	           const __m512 cp1     = _mm512_set1_ps(1.0F);                                                               
	           const __m512 cp2     = _mm512_set1_ps(0.08333333333333333F);                                                
	           const __m512 cp2     = _mm512_set1_ps(0.002777777777777778F);                                              
	           const __m512 cp3     = _mm512_set1_ps(0.002777777777777778F);                                              
	           const __m512 cp4     = _mm512_set1_ps(4.96031746031746e-05F);                                                                                    
	           const __m512 cp5     = _mm512_set1_ps(5.511463844797178e-07F);                                              
	           const __m512i zeroes = _mm512_set1_epi32(0);                                                              
	           const __m512i allones = _mm512_set1_epi32(0xFFFFFFFF);                                                     
	           const __m512i twos    = _mm512_set1_epi32(2);                                                              
	           const __m512i fours   = _mm512_set1_epi32(4);                                                              
	           __m512 fzeroes      = _mm512_setzero_ps();                                                                 
	           __m512 aVal         = fzeroes;                                                                              
	           __m512 s   = fzeroes;                                                                                       
	           __m512 r   = fzeroes;                                                                                      
	           __m512 t0 = fzeroes;                                                                                       
	           __m512 sine = fzeroes;                                                                                    
	           __m512 cosine = fzeroes;					                                           
	           __m512i q;					                                                           
                   __mmask16 condition1 = 0;                                                                                                                                                             
	           __mmask16 condition2 = 0;                                                    
                   aVal = v;
		   s = (__m512)(_mm512_and_si512((__m512i)(aVal),
		                             _mm512_set1_epi32(0x7fffffff)));
                   q = _mm512_cvtps_epi32(_mm512_floor_ps(_mm512_mul_ps(s, m4pi)));
                   r = _mm512_cvtepi32_ps(_mm512_add_epi32(q,
		                             _mm512_and_si512(q, ones)));
                   s = _mm512_fnmadd_ps(r, pio4A, s);
                   s = _mm512_fnmadd_ps(r, pio4B, s);
                   s = _mm512_fnmadd_ps(r, pio4C, s);
		   s = _mm512_div_ps(s,feight);
		   s = _mm512_mul_ps(s,s);
		   s = _mm512_mul_ps(
                                 _mm512_fmadd_ps(
                                         _mm512_fmsub_ps(
                                             _mm512_fmadd_ps(
					          _mm512_fmsub_ps(s, cp5, cp4), s, cp3), s, cp2),
                                             s,
                                        cp1),
                                 s);
		    t0 = _mm512_sub_ps(ffours,a);
		    s  = _mm512_mul_ps(s,t0);
		    s  = _mm512_mul_ps(s,t0);
		    s  = _mm512_mul_ps(s,t0);
		    s  = _mm512_mul_ps(s,finv2);
		    sine = _mm512_sqrt_ps(_mm512_mul_ps(
		                             _mm512_sub_ps(ftwos, s), s));
                    cosine = _mm512_sub_ps(fones, s);
		    condition1 = _mm512_cmpneq_epi32_mask(
                                          _mm512_and_si512(
					           _mm512_add_epi32(q, ones), twos), zeros);
		    condition2 = _mm512_cmpneq_epi32_mask(
                                           _mm512_and_si512(_mm512_add_epi32(q, twos), fours), zeros);
                    cosine = _mm512_mask_blend_ps(condition1, cosine, sine);
                    cosine = _mm512_mask_mul_ps(cosine, condition2, cosine, _mm512_set1_ps(-1.f));
		    return (cosine);
	  }










