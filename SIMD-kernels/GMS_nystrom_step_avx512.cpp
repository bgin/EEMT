


/*MIT License
Copyright (c) 2020 Bernard Gingold
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/



/*
   Adapted from: http://www.mymathlib.com/diffeq/runge-kutta/runge_kutta_nystrom.html
   Manually vectorized by Bernard Gingold, beniekg@gmail.com
*/


#include "GMS_nystrom_step_avx512.h"



////////////////////////////////////////////////////////////////////////////////
//  double Runge_Kutta_Nystrom( double (*f)(double, double), double y0,       //
//                               double x0, double h, int number_of_steps );  //
//                                                                            //
//  Description:                                                              //
//     This routine uses the Runge-Kutta-Nystrom method described above to    //
//     approximate the solution at x = x0 + h * number_of_steps of the initial//
//     value problem y'=f(x,y), y(x0) = y0.                                   //
//                                                                            //
//  Arguments:                                                                //
//     double *f                                                              //
//            Pointer to the function which returns the slope at (x,y) of the //
//            integral curve of the differential equation y' = f(x,y) which   //
//            passes through the point (x0,y0).                               //
//     double y0                                                              //
//            The initial value of y at x = x0.                               //
//     double x0                                                              //
//            The initial value of x.                                         //
//     double h                                                               //
//            The step size.                                                  //
//     int    number_of_steps                                                 //
//            The number of steps. Must be a nonnegative integer.             //
//                                                                            //
//  Return Values:                                                            //
//     The solution of the initial value problem y' = f(x,y), y(x0) = y0 at   //
//     x = x0 + number_of_steps * h.                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////


                      
                     
			__m512d
			gms::math::nystrom_step_zmm8r8(__m512d(*f)(__m512d,
			                             __m512d),
					    __m512d y0,
					    __m512d x0,
					    const __m512d h,
					    const int32_t n) {

			    const __m512d _1_25  = _mm512_set1_pd(0.04);
			    const __m512d h25    = _mm512_mul_pd(_1_25,h);
			    const __m512d _1_4   = _mm512_set1_pd(0.25);
			    const __m512d h4     = _mm512_mul_pd(_1_4,h);
			    const __m512d _1_81  = _mm512_set1_pd(0.012345679012345679012345679012);
			    const __m512d h81    = _mm512_mul_pd(_1_81,h);
			    const __m512d _1_75  = _mm512_set1_pd(0.013333333333333333333333333333);
			    const __m512d h75    = _mm512_mul_pd(_1_45,h);
			    const __m512d _1_3   = _mm512_set1_pd(0.333333333333333333333333333333);
			    const __m512d h3     = _mm512_mul_pd(_1_3,h);
			    const __m512d _2_5   = _mm512_set1_pd(0.4);
			    const __m512d h2_5   = _mm512_mul_pd(_2_5,h);
			    const __m512d _2_3   = _mm512_set1_pd(0.666666666666666666666666666667);
			    const __m512d h2_3   = _mm512_mul_pd(_2_3,h);
			    const __m512d _4_5   = _mm512_set1_pd(0.8);
			    const __m512d h4_5   = _mm512_set1_pd(_4_5,h);
			    const __m512d _1_192 = _mm512_set1_pd(0.005208333333333333333333333333);
			    const __m512d h192   = _mm512_mul_pd(_1_192,h);
			    const __m512d _4     = _mm512_set1_pd(4.0);
			    const __m512d _6     = _mm512_set1_pd(6.0);
			    const __m512d _12    = _mm512_set1_pd(12.0);
			    const __m512d _15    = _mm512_set1_pd(15.0);
			    const __m512d _90    = _mm512_set1_pd(90.0);
			    const __m512d _50    = _mm512_set1_pd(50.0);
			    const __m512d _6     = _mm512_set1_pd(6.0);
			    const __m512d _8     = _mm512_set1_pd(8.0);
			    const __m512d _36    = _mm512_set1_pd(36.0);
			    const __m512d _10    = _mm512_set1_pd(10.0);
			    const __m512d _23    = _mm512_set1_pd(23.0);
			    const __m512d _125   = _mm512_set1_pd(125.0);
			    const __m512d _81    = _mm512_set1_pd(81.0);
			    __m512d k1,k2,k3,k4,k5,k6;
			    __m512d t0,t1,t2,t3,t4;

			    while(--n >= 0) {
                                  k1 = f(x0,y0);
				  k2 = f(_mm512_add_pd(x0,h3),
				         _mm512_fmadd_pd(h3,k1,y0));
				  t0 = _mm512_fmadd_pd(h25,
				                   _mm512_fmadd_pd(_4,k1,
						               _mm512_mul_pd(_6,k2)),y0);
				  k3 = f(_mm512_add_pd(x0,h2_5),t0);
				  t1 = _mm512_fmadd_pd(h4,
				                   _mm512_fmadd_pd(_15,k3,
						               _mm512_sub_pd(k1,
							                 _mm512_mul_pd(_12,k2))),y0);
				  k4 = f(_mm512_add_pd(x0,h),t1);
				  t2 = _mm512_fmadd_pd(_6,k1,
				                   _mm512_mul_pd(_90,k2));
				  t3 = _mm512_fmadd_pd(_50,k3,
				                   _mm512_mul_pd(_8,k4));
				  k5 = f(_mm512_add_pd(x0,h2_3),
				         _mm512_fmadd_pd(h81,_mm512_sub_pd(t2,t3),y0));
				  t0 = _mm512_fmadd_pd(_6,k1,
				                   _mm512_fmadd_pd(_36,k2,
						               _mm512_fmadd_pd(_10,k3,
							                   _mm512_mul_pd(_8,k4))));
				  k6 = f(_mm512_add_pd(x0,h4_5),
				         _mm512_fmadd_pd(h75,t0,y0));
				  t1 = _mm512_fmadd_pd(_23,k1,
				                   _mm512_fmsub_pd(_125,k3,_81));
				  t2 = _mm512_fmadd_pd(_125,k6,k5);
				  y0 = _mm512_fmadd_pd(h192,_mm512_mul_pd(t1,t2),y0);
				  x0 = _mm512_add_pd(x0,h);
			    }
			    return (y0);
                      }


		      
			__m512
			gms::math::nystrom_step_zmm16r4(__m512(*f)(__m512,
			                                __m512),
					    __m512 y0,
					    __m512 x0,
					    const __m512 h,
					    const int32_t n) {

			    const __m512 _1_25  = _mm512_set1_ps(0.04f);
			    const __m512 h25    = _mm512_mul_ps(_1_25,h);
			    const __m512 _1_4   = _mm512_set1_ps(0.25f);
			    const __m512 h4     = _mm512_mul_ps(_1_4,h);
			    const __m512 _1_81  = _mm512_set1_ps(0.012345679012345679012345679012f);
			    const __m512 h81    = _mm512_mul_ps(_1_81,h);
			    const __m512 _1_75  = _mm512_set1_ps(0.013333333333333333333333333333f);
			    const __m512 h75    = _mm512_mul_ps(_1_45,h);
			    const __m512 _1_3   = _mm512_set1_ps(0.333333333333333333333333333333f);
			    const __m512 h3     = _mm512_mul_ps(_1_3,h);
			    const __m512 _2_5   = _mm512_set1_ps(0.4f);
			    const __m512 h2_5   = _mm512_mul_ps(_2_5,h);
			    const __m512 _2_3   = _mm512_set1_ps(0.666666666666666666666666666667f);
			    const __m512 h2_3   = _mm512_mul_ps(_2_3,h);
			    const __m512 _4_5   = _mm512_set1_ps(0.8f);
			    const __m512 h4_5   = _mm512_set1_ps(_4_5,h);
			    const __m512 _1_192 = _mm512_set1_ps(0.005208333333333333333333333333f);
			    const __m512 h192   = _mm512_mul_ps(_1_192,h);
			    const __m512 _4     = _mm512_set1_ps(4.0f);
			    const __m512 _6     = _mm512_set1_ps(6.0f);
			    const __m512 _12    = _mm512_set1_ps(12.0f);
			    const __m512 _15    = _mm512_set1_ps(15.0f);
			    const __m512 _90    = _mm512_set1_ps(90.0f);
			    const __m512 _50    = _mm512_set1_ps(50.0f);
			    const __m512 _6     = _mm512_set1_ps(6.0f);
			    const __m512 _8     = _mm512_set1_ps(8.0f);
			    const __m512 _36    = _mm512_set1_ps(36.0f);
			    const __m512 _10    = _mm512_set1_ps(10.0f);
			    const __m512 _23    = _mm512_set1_ps(23.0f);
			    const __m512 _125   = _mm512_set1_ps(125.0f);
			    const __m512 _81    = _mm512_set1_ps(81.0f);
			    __m512 k1,k2,k3,k4,k5,k6;
			    __m512 t0,t1,t2,t3,t4;

			    while(--n >= 0) {
                                  k1 = f(x0,y0);
				  k2 = f(_mm512_add_ps(x0,h3),
				         _mm512_fmadd_ps(h3,k1,y0));
				  t0 = _mm512_fmadd_ps(h25,
				                   _mm512_fmadd_ps(_4,k1,
						               _mm512_mul_ps(_6,k2)),y0);
				  k3 = f(_mm512_add_ps(x0,h2_5),t0);
				  t1 = _mm512_fmadd_ps(h4,
				                   _mm512_fmadd_ps(_15,k3,
						               _mm512_sub_ps(k1,
							                 _mm512_mul_ps(_12,k2))),y0);
				  k4 = f(_mm512_add_ps(x0,h),t1);
				  t2 = _mm512_fmadd_ps(_6,k1,
				                   _mm512_mul_ps(_90,k2));
				  t3 = _mm512_fmadd_ps(_50,k3,
				                   _mm512_mul_ps(_8,k4));
				  k5 = f(_mm512_add_ps(x0,h2_3),
				         _mm512_fmadd_ps(h81,_mm512_sub_pd(t2,t3),y0));
				  t0 = _mm512_fmadd_ps(_6,k1,
				                   _mm512_fmadd_ps(_36,k2,
						               _mm512_fmadd_ps(_10,k3,
							                   _mm512_mul_ps(_8,k4))));
				  k6 = f(_mm512_add_ps(x0,h4_5),
				         _mm512_fmadd_ps(h75,t0,y0));
				  t1 = _mm512_fmadd_ps(_23,k1,
				                   _mm512_fmsub_ps(_125,k3,_81));
				  t2 = _mm512_fmadd_ps(_125,k6,k5);
				  y0 = _mm512_fmadd_ps(h192,_mm512_mul_ps(t1,t2),y0);
				  x0 = _mm512_add_ps(x0,h);
			    }
			    return (y0);
                      }





					    

