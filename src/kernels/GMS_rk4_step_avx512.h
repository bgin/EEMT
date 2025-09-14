
#ifndef __GMS_RK4_STEP_AVX512_H__
#define __GMS_RK4_STEP_AVX512_H__ 010620220827

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
   Adapted from: http://www.mymathlib.com/diffeq/runge-kutta/
   Manually vectorized by Bernard Gingold, beniekg@gmail.com
*/

namespace file_version {

    const unsigned int GMS_RK4_STEP_AVX512_MAJOR = 1U;
    const unsigned int GMS_RK4_STEP_AVX512_MINOR = 0U;
    const unsigned int GMS_RK4_STEP_AVX512_MICRO = 0U;
    const unsigned int GMS_RK4_STEP_AVX512_FULLVER =
      1000U*GMS_RK4_STEP_AVX512_MAJOR+
      100U*GMS_RK4_STEP_AVX512_MINOR+
      10U*GMS_RK4_STEP_AVX512_MICRO;
    const char * const GMS_RK4_STEP_AVX512_CREATION_DATE = "01-06-2022 08:27 PM +00200 (WED 01 JUN 2022 GMT+2)";
    const char * const GMS_RK4_STEPAVX512_BUILD_DATE    = __DATE__ ":" __TIME__;
    const char * const GMS_RK4_STEP_AVX512_AUTHOR        = "Programmer: Bernard Gingold, contact: beniekg@gmail.com";
    const char * const GMS_RK4_STEP_AVX512_DESCRIPTION   = "Vectorized (AVX512) Runge-Kutta order 4 step."

}


#include <immintrin.h>
#include <cstdint>
#include "GMS_config.h"


namespace gms {

        namespace math {

/*
////////////////////////////////////////////////////////////////////////////////
//  double Runge_Kutta( double (*f)(double, double), double y0, double x0,    //
//                                          double h, int number_of_steps );  //
//                                                                            //
//  Description:                                                              //
//     This routine uses the 4th order Runge-Kutta method described above to  //
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
//                                                                            //
*/

	             
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			__ATTR_VECTORCALL__
	               
			__m512d
		        rk4_step_zmm8r8(__m512d(*f)(__m512d,
			                            __m512d),
				        __m512d y0,
				        __m512d x0,
					const __m512d h,
					const int32_t n); 
					


		      
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			__ATTR_VECTORCALL__
	              
			__m512
		        rk4_step_zmm16r4(__m512(*f)(__m512,
			                            __m512),
				         __m512 y0,
				         __m512 x0,
					 const __m512 h,
					 const int32_t n); 

////////////////////////////////////////////////////////////////////////////////
//  double Runge_Kutta_Richardson( double (*f)(double, double), double y0,    //
//         double x0, double h, int number_of_steps, int richardson_columns)  //
//                                                                            //
//  Description:                                                              //
//     This routine uses the 4th order Runge-Kutta method described above     //
//     together with Richardson extrapolation to approximate the solution at  //
//     x = x0 + h * number_of_steps of the initial value problem y'=f(x,y),   //
//     y(x0) = y0.                                                            //
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
//            The number of steps. Must be nonnegative.                       //
//     int    richardson_columns                                              //
//            The maximum number of columns to use in the Richardson          //
//            extrapolation to the limit.                                     //
//                                                                            //
//  Return Values:                                                            //
//     The solution of the initial value problem y' = f(x,y), y(x0) = y0 at   //
//     x = x0 + number_of_steps * h.                                          //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////



                    
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			__ATTR_VECTORCALL__
	                
			__m512d
			rk4_richardson_zmm8r8(__m512d(*f)(__m512d,
			                                     __m512d),
						 __m512d y0,
						 __m512d x0,
						 const __m512d h,
						 const int32_t n,
						 int32_t n_cols); 
						 

		      
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			__ATTR_VECTORCALL__
	              
			__m512
			rk4_richardson_zmm16r4(__m512(*f)(__m512,
			                                     __m512),
						 __m512 y0,
						 __m512 x0,
						 const __m512 h,
						 const int32_t n,
						 int32_t n_cols); 




	  
			

   } // math

} //gms









#endif /*__GMS_RK4_STEP_AVX512_H__*/
