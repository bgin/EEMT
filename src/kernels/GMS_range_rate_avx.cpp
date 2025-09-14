

/*LICENSE:
*
*The source code is in the public domain and not licensed or under
*copyright. The information and software may be used freely by the public.
*As required by 17 U.S.C. 403, third parties producing copyrighted works
*consisting predominantly of the material produced by U.S. government
*agencies must provide notice with such work(s) identifying the U.S.
*Government material incorporated and stating that such material is not
*subject to copyright protection.
*
*Derived works shall not identify themselves in a manner that implies an
*endorsement by or an affiliation with the Naval Research Laboratory.
*
*RECIPIENT BEARS ALL RISK RELATING TO QUALITY AND PERFORMANCE OF THE
*SOFTWARE AND ANY RELATED MATERIALS, AND AGREES TO INDEMNIFY THE NAVAL
*RESEARCH LABORATORY FOR ALL THIRD-PARTY CLAIMS RESULTING FROM THE ACTIONS
*OF RECIPIENT IN THE USE OF THE SOFTWARE.
@@Modified by Bernard Gingold, on 14-05-2022 11:11 +00200 (SAT 14 MAY 2022 11:11 GMT+2)
  contact: beniekg@gmail.com
*/


#include "GMS_range_rate_avx.h"




/*GETRANGERATE2DGENCPP A C++ function to convert a Cartesian state in 2D
 *        into a non-relativistic range rate, ignoring atmospheric effects.
 *
 *INPUTS: xTar The 4X1 Cartesian position and velocity vectors
 *             [x;y;xDot;yDot].
 *  useHalfRange A boolean value specifying whether the bistatic (round-
 *             trip) range value (and hence the range rate) has been
 *             divided by two. 
 *         xTx The 4X1 [x;y;xDot;yDot] position and velocity vector of
 *             the transmitter in global Cartesian coordinates.
 *         xRx The 4X1 [x;y;xDot;yDot] position and velocity vector of
 *             the receiver in global Cartesian coordinates.
 *
 *OUTPUTS: rr The range rate as a double.
 *
 *See the comments to the Matlab function getRangeRate for more information
 *on how this function works.
 *
 *April 2017 David F. Crouse, Naval Research Laboratory, Washington D.C.
 *@@Modified by Bernard Gingold, on May 2022
 **/

                      
                       
                      __m256d gms::math::range_rate_2d_ymm4r8(const __m256d tar_x,
		                                   const __m256d tar_y,
						   const __m256d tar_xD,
						   const __m256d tar_yD,
						   const __m256d tx_x,
						   const __m256d tx_y,
						   const __m256d tx_xD,
						   const __m256d tx_yD,
						   const __m256d rx_x,
						   const __m256d rx_y,
						   const __m256d rx_xD,
						   const __m256d rx_yD,
						   const bool useHalfRange) {

                        __m256d rr = _mm256_setzero_pd(); // return value i.e. rate-range
			const __m256d half = _mm256_set1_pd(0.5);
			__m256d dtr0,dtr1,dtl0,dtl1,mag;
			__m256d t0,t1,t2,t3,t4;
			dtr0 = _mm256_sub_pd(tar_x,rx_x);
			dtr1 = _mm256_sub_pd(tar_y,rx_x);
			mag  = _mm256_sqrt_pd(_mm256_add_pd(_mm256_mul_pd(dtr0,dtr0),
			                                    _mm256_mul_pd(dtr1,dtr1)));
		        dtr0 = _mm256_div_pd(dtr0,mag);
			dtl0 = _mm256_sub_pd(tar_x,tx_x);
			dtl1 = _mm256_sub_pd(tar_y,tx_x);
			dtr1 = _mm256_div_pd(dtr1,mag);
			mag  = _mm256_sqrt_pd(_mm256_add_pd(_mm256_mul_pd(dtl0,dtl0),
			                                    _mm256_mul_pd(dtl1,dtl1)));
		        dtl0 = _mm256_div_pd(dtl0,mag);
			dtl1 = _mm256_div_pd(dtl1,mag);
			t0   = _mm256_sub_pd(_mm256_mul_pd(dtr0,rx_xD),
			                     _mm256_mul_pd(dtr1,rx_yD));
			t1   = _mm256_sub_pd(_mm256_mul_pd(dtl0,tx_xD),
			                     _mm256_mul_pd(dtl1,tx_yD));
			t2   = _mm256_mul_pd(_mm256_add_pd(dtr0,dtl0),tar_xD);
			t3   = _mm256_mul_pd(_mm256_add_pd(dtr1,dtl1),tar_yD);
			t4   = _mm256_add_pd(t2,t3);
			rr   = _mm256_sub_ps(t4,_mm256_sub_pd(t1,t0));
		        if(useHalfRange) {
                           rr = _mm256_mul_pd(rr,half);
			}
			return (rr);
		   }


		   
		   
                          
                      __m256 gms::math::range_rate_2d_ymm8r4(const __m256 tar_x,
		                                   const __m256 tar_y,
						   const __m256 tar_xD,
						   const __m256 tar_yD,
						   const __m256 tx_x,
						   const __m256 tx_y,
						   const __m256 tx_xD,
						   const __m256 tx_yD,
						   const __m256 rx_x,
						   const __m256 rx_y,
						   const __m256 rx_xD,
						   const __m256 rx_yD,
						   const bool useHalfRange) {

                        __m256 rr = _mm256_setzero_ps(); // return value i.e. rate-range
			const __m256 half = _mm256_set1_ps(0.5f);
			__m256 dtr0,dtr1,dtl0,dtl1,mag;
			__m256 t0,t1,t2,t3,t4;
			dtr0 = _mm256_sub_ps(tar_x,rx_x);
			dtr1 = _mm256_sub_ps(tar_y,rx_x);
			mag  = _mm256_sqrt_ps(_mm256_add_ps(_mm256_mul_ps(dtr0,dtr0),
			                                    _mm256_mul_ps(dtr1,dtr1)));
		        dtr0 = _mm256_div_ps(dtr0,mag);
			dtl0 = _mm256_sub_ps(tar_x,tx_x);
			dtl1 = _mm256_sub_ps(tar_y,tx_x);
			dtr1 = _mm256_div_ps(dtr1,mag);
			mag  = _mm256_sqrt_ps(_mm256_add_ps(_mm256_mul_ps(dtl0,dtl0),
			                                    _mm256_mul_ps(dtl1,dtl1)));
		        dtl0 = _mm256_div_ps(dtl0,mag);
			dtl1 = _mm256_div_ps(dtl1,mag);
			t0   = _mm256_sub_ps(_mm256_mul_ps(dtr0,rx_xD),
			                     _mm256_mul_ps(dtr1,rx_yD));
			t1   = _mm256_sub_ps(_mm256_mul_ps(dtl0,tx_xD),
			                     _mm256_mul_ps(dtl1,tx_yD));
			t2   = _mm256_mul_ps(_mm256_add_ps(dtr0,dtl0),tar_xD);
			t3   = _mm256_mul_ps(_mm256_add_ps(dtr1,dtl1),tar_yD);
			t4   = _mm256_add_ps(t2,t3);
			rr   = _mm256_sub_ps(t4,_mm256_sub_ps(t1,t0));
			if(useHalfRange) {
                           rr = _mm256_mul_ps(rr,half);
			}
			return (rr);
		   }

/*GETRANGERATE3DGENCPP A C++ function to convert a Cartesian state in 3D
 *        into a non-relativistic range rate, ignoring atmospheric effects.
 *
 *INPUTS: xTar The 6X1 Cartesian position and velocity vectors
 *             [x;y;z;xDot;yDot;zDot].
 * useHalfRange A boolean value specifying whether the bistatic (round-
 *             trip) range value (and hence the range rate) has been
 *             divided by two. 
 *         xTx The 6X1 [x;y;z;xDot;yDot;zDot] position and velocity
 *             vector of the transmitter in global Cartesian coordinates.
 *         xTx The 6X1 [x;y;z;xDot;yDot;zDot] position and velocity
 *             vector of the receiver in global Cartesian coordinates.
 *
 *OUTPUTS: rr The range rate as a double.
 *
 *See the comments to the Matlab function getRangeRate for more information
 *on how this function works.
 *
 *April 2017 David F. Crouse, Naval Research Laboratory, Washington D.C.
 *@@Modified by Bernard Gingold, on May 2022
 **/
		   
				   
                    
                         
                      __m256d gms::math::range_rate_3d_ymm4r8(const __m256d tar_x,
		                                   const __m256d tar_y,
						   const __m256d tar_z,
						   const __m256d tar_xD,
						   const __m256d tar_yD,
						   const __m256d tar_zD,
						   const __m256d tx_x,
						   const __m256d tx_y,
						   const __m256d tx_z,
						   const __m256d tx_xD,
						   const __m256d tx_yD,
						   const __m256d tx_zD,
						   const __m256d rx_x,
						   const __m256d rx_y,
						   const __m256d rx_z,
						   const __m256d rx_xD,
						   const __m256d rx_yD,
						   const __m256d rx_zD,
						   const bool useHalfRange) {

                          __m256d rr = _mm256_setzero_pd(); // return value i.e. rate-range
			  const __m256d half = _mm256_set1_pd(0.5);
			  __m256d dtr0,dtr1,dtr2,dtl0,dtl1,dtl2,mag;
		          __m256d t0,t1,t2,t3,t4,t5;
			  dtr0 = _mm256_sub_pd(tar_x,rx_x);
			  dtr1 = _mm256_sub_pd(tar_y,rx_y);
			  dtr2 = _mm256_sub_pd(tar_z,rx_z);
			  // Normalization
			  mag = _mm256_fmadd_pd(dtr0,dtr0,
			                        _mm256_fmadd_pd(dtr1,dtr1,
						_mm256_fmadd_pd(dtr2,dtr2)));
			  dtr0 = _mm256_div_pd(dtr0,mag);
			  dtl0 = _mm256_sub_pd(tar_x,tx_x);
			  dtr1 = _mm256_div_pd(dtr1,mag);
			  dtl1 = _mm256_sub_pd(tar_y,tx_y);
			  dtl2 = _mm256_sub_pd(tar_z,tx_z);
			  dtr2 = _mm256_div_pd(dtr2,mag);
			  // Normalization
			  mag  = _mm256_fmadd_pd(dtl0,dtl0,
			                        _mm256_fmadd_pd(dtl1,dtl1,
						_mm256_fmadd_pd(dlr2,dtl2)));
			  dtl0 = _mm256_div_pd(dtl0,mag);
			  t0   = _mm256_fmsub_pd(dtr0,rx_xD,
			                         _mm256_fmsub_pd(dtr1,rx_yD,
						 _mm256_fmsub_pd(dtr2,rx_zD)));
			  dtl1 = _mm256_div_pd(dtl1,mag);
			  t1   = _mm256_fmsub_pd(dtl0,tx_xD,
			                         _mm256_fmsub_pd(dtl1,tx_yD,
						 _mm256_fmsub_pd(dtl2,tx_zD)));
			  dtl2 = _mm256_div_pd(dtl2,mag);
			  t2   = _mm256_mul_pd(_mm256_add_pd(dtr0,dtl0),tar_xD);
			  t3   = _mm256_mul_pd(_mm256_add_pd(dtr1,dtl1),tar_yD);
			  t4   = _mm256_mul_pd(_mm256_add_pd(dtr2,dtl2),tar_zD);
			  t5   = _mm256_add_pd(t2,_mm256_add_pd(t3,t4));
			  rr   = _mm256_sub_pd(t5,_mm256_sub_pd(t1,t0));
			  if(useHalfRange) {
                               rr = _mm256_mul_pd(rr,half);
			  }
			  return (rr);
		    }


		       
                      __m256 gms::math::range_rate_3d_ymm8r4(const __m256 tar_x,
		                                   const __m256 tar_y,
						   const __m256 tar_z,
						   const __m256 tar_xD,
						   const __m256 tar_yD,
						   const __m256 tar_zD,
						   const __m256 tx_x,
						   const __m256 tx_y,
						   const __m256 tx_z,
						   const __m256 tx_xD,
						   const __m256 tx_yD,
						   const __m256 tx_zD,
						   const __m256 rx_x,
						   const __m256 rx_y,
						   const __m256 rx_z,
						   const __m256 rx_xD,
						   const __m256 rx_yD,
						   const __m256 rx_zD,
						   const bool useHalfRange) {

                          __m256 rr = _mm256_setzero_ps(); // return value i.e. rate-range
			  const __m256 half = _mm256_set1_ps(0.5f);
			  __m256 dtr0,dtr1,dtr2,dtl0,dtl1,dtl2,mag;
		          __m256 t0,t1,t2,t3,t4,t5;
			  dtr0 = _mm256_sub_ps(tar_x,rx_x);
			  dtr1 = _mm256_sub_ps(tar_y,rx_y);
			  dtr2 = _mm256_sub_ps(tar_z,rx_z);
			  // Normalization
			  mag = _mm256_fmadd_ps(dtr0,dtr0,
			                        _mm256_fmadd_ps(dtr1,dtr1,
						_mm256_fmadd_ps(dtr2,dtr2)));
			  dtr0 = _mm256_div_ps(dtr0,mag);
			  dtl0 = _mm256_sub_ps(tar_x,tx_x);
			  dtr1 = _mm256_div_ps(dtr1,mag);
			  dtl1 = _mm256_sub_ps(tar_y,tx_y);
			  dtl2 = _mm256_sub_ps(tar_z,tx_z);
			  dtr2 = _mm256_div_ps(dtr2,mag);
			  // Normalization
			  mag  = _mm256_fmadd_ps(dtl0,dtl0,
			                        _mm256_fmadd_ps(dtl1,dtl1,
						_mm256_fmadd_ps(dlr2,dtl2)));
			  dtl0 = _mm256_div_ps(dtl0,mag);
			  t0   = _mm256_fmsub_ps(dtr0,rx_xD,
			                         _mm256_fmsub_ps(dtr1,rx_yD,
						 _mm256_fmsub_ps(dtr2,rx_zD)));
			  dtl1 = _mm256_div_ps(dtl1,mag);
			  t1   = _mm256_fmsub_ps(dtl0,tx_xD,
			                         _mm256_fmsub_ps(dtl1,tx_yD,
						 _mm256_fmsub_ps(dtl2,tx_zD)));
			  dtl2 = _mm256_div_ps(dtl2,mag);
			  t2   = _mm256_mul_ps(_mm256_add_ps(dtr0,dtl0),tar_xD);
			  t3   = _mm256_mul_ps(_mm256_add_ps(dtr1,dtl1),tar_yD);
			  t4   = _mm256_mul_ps(_mm256_add_ps(dtr2,dtl2),tar_zD);
			  t5   = _mm256_add_ps(t2,_mm256_add_ps(t3,t4));
			  rr   = _mm256_sub_ps(t5,_mm256_sub_ps(t1,t0));
			  if(useHalfRange) {
                               rr = _mm256_mul_ps(rr,half);
			  }
			  return (rr);
		    }

/*A C++-only implementations of a functions for computing the gradient of
 *bistatic range.  See the Matlab equivalents for more comments.
 *
*February 2017 David F. Crouse, Naval Research Laboratory, Washington D.C.
**@@Modified by Bernard Gingold, on May 2022
**/
/*(UNCLASSIFIED) DISTRIBUTION STATEMENT A. Approved for public release.*/
		     
                      
                      __m256d gms::math::range_grad_ymm4r8(const __m256d p,
					        const __m256d Tx,
					        const __m256d Rx,
					        const bool useHalfRange) {

			  const __m256d half = _mm256_set1_pd(0.5);
			  __m256d temp,vnorm,J;
			  double norm        = 0.0;
			  //deltaTx=x-lTx;
			  temp  = _mm256_sub_pd(p,Tx);
			  norm  = _mm256_reduce_add_pd(_mm256_mul_pd(temp,temp));
			  vnorm = _mm256_set1_pd(norm);
			  vnorm = _mm256_sqrt_pd(vnorm);
			  //deltaTx.'/norm(deltaTx)
			  J     = _mm256_div_pd(temp,vnorm);
			  // eltaRx=x-lRx;
			  temp  = _mm256_sub_pd(p,Rx);
			  norm  = 0.0;
			  vnorm = _mm256_setzero_pd();
			  norm  = _mm256_reduce_add_pd(_mm256_mul_pd(temp,temp));
			  vnorm = _mm256_set1_pd(norm);
			  vnorm = _mm256_sqrt_pd(vnorm);
			  ////deltaTx=x-lTx;
			  J     = _mm256_add_pd(J,_mm256_div_pd(temp,vnorm));
			  if(useHalfRange) {
                             J  = _mm256_mul_pd(J,half);
			  }
			  return (J);
		    }


		     
                     
                      __m256 gms::math::range_grad_ymm8r4(const __m256 p,
					        const __m256 Tx,
					        const __m256 Rx,
					        const bool useHalfRange) {

			  const __m256 half = _mm256_set1_ps(0.5f);
			  __m256 temp,vnorm,J;
			  float norm        = 0.0f;
			  //deltaTx=x-lTx;
			  temp  = _mm256_sub_ps(p,Tx);
			  norm  = _mm256_reduce_add_ps(_mm256_mul_ps(temp,temp));
			  vnorm = _mm256_set1_ps(norm);
			  vnorm = _mm256_sqrt_ps(vnorm);
			  //deltaTx.'/norm(deltaTx)
			  J     = _mm256_div_ps(temp,vnorm);
			  // eltaRx=x-lRx;
			  temp  = _mm256_sub_ps(p,Rx);
			  norm  = 0.0f;
			  vnorm = _mm256_setzero_ps();
			  norm  = _mm256_reduce_add_ps(_mm256_mul_ps(temp,temp));
			  vnorm = _mm256_set1_ps(norm);
			  vnorm = _mm256_sqrt_ps(vnorm);
			  ////deltaTx=x-lTx;
			  J     = _mm256_add_ps(J,_mm256_div_ps(temp,vnorm));
			  if(useHalfRange) {
                             J  = _mm256_mul_ps(J,half);
			  }
			  return (J);
		    }

/**RANGEHESSIANCPP A C++-only implementations of a function for computing
 *the Hessian of bistatic range.  See the Matlab equivalent for more
 *comments.
 *
 *June 2017 David F. Crouse, Naval Research Laboratory, Washington D.C.
 *@@Modified by Bernard Gingold, on May 2022
 */
/*(UNCLASSIFIED) DISTRIBUTION STATEMENT A. Approved for public release.*/
		    
                      
                     
                    
		     
		       
                      __m256d range_hessian_1d_ymm4r8() {
                         __m256d H = _mm256_setzero_pd();
			 return (H);
		     }


		     
                    
		     
		      
		       
                      __m256 range_hessian_1d_ymm8r4() {
                         __m256 H = _mm256_setzero_ps();
			 return (H);
		     }

#include "GMS_simd_utils.hpp"

		     
                    
		      void gms::math::range_hessian_2d_ymm4r8_a(double * __restrict __ATTR_ALIGN__(32) H_0,
		                                     double * __restrict __ATTR_ALIGN__(32) H_1,
						     double * __restrict __ATTR_ALIGN__(32) H_2,
						     double * __restrict __ATTR_ALIGN__(32) H_3,
						     const __m256d x_0,
						     const __m256d x_1,
						     const bool useHalfRange) {

			   const __m256d _2   = _mm256_set1_pd(2.0);
			   const __m256d _1   = _mm256_set1_pd(1.0);
			   const __m256d xC2  = _mm256_mul_pd(x_0,x_0);
			   const __m256d yC2  = _mm256_mul_pd(x_1,x_1);
			   const __m256d r    = _mm256_sqrt_pd(_mm256_add_pd(xC2,yC2));
			   const __m256d r3   = _mm256_mul_pd(r,_mm256_mul_pd(r,r));
			   const __m256d invr = _mm256_div_pd(_1,r);
			   _mm256_store_pd(&H_0[0],_mm256_add_pd(_mm256_div_pd(ymm4r8_negate(xC2),
			                                                    r3),invr));
			   _mm256_store_pd(&H_1[0],_mm256_div_pd(_mm256_mul_pd(ymm4r8_negate(x_0),
			                                                    x_1),r3));
			   _mm256_store_pd(&H_2[0],_mm256_load_pd(&H1[0]));
			   _mm256_store_pd(&H_3[0],_mm256_add_pd(_mm256_div_pd(ymm4r8_negate(yC2),
			                                                    r3),invr));
			   if(useHalfRange) {
                              _mm256_store_pd(&H_0[0],_mm256_mul_pd(_mm256_load_pd(&H_0[0],_2)));
			      _mm256_store_pd(&H_1[0],_mm256_mul_pd(_mm256_load_pd(&H_1[0],_2)));
			      _mm256_store_pd(&H_2[0],_mm256_mul_pd(_mm256_load_pd(&H_2[0],_2)));
			      _mm256_store_pd(&H_3[0],_mm256_mul_pd(_mm256_load_pd(&H_3[0],_2)));
			   }
		    }


		     
                     
		      void gms::math::range_hessian_2d_ymm4r8_u(double * __restrict H_0,
		                                     double * __restrict H_1,
						     double * __restrict H_2,
						     double * __restrict H_3,
						     const __m256d x_0,
						     const __m256d x_1,
						     const bool useHalfRange) {

			   const __m256d _2   = _mm256_set1_pd(2.0);
			   const __m256d _1   = _mm256_set1_pd(1.0);
			   const __m256d xC2  = _mm256_mul_pd(x_0,x_0);
			   const __m256d yC2  = _mm256_mul_pd(x_1,x_1);
			   const __m256d r    = _mm256_sqrt_pd(_mm256_add_pd(xC2,yC2));
			   const __m256d r3   = _mm256_mul_pd(r,_mm256_mul_pd(r,r));
			   const __m256d invr = _mm256_div_pd(_1,r);
			   _mm256_storeu_pd(&H_0[0],_mm256_add_pd(_mm256_div_pd(ymm4r8_negate(xC2),
			                                                    r3),invr));
			   _mm256_storeu_pd(&H_1[0],_mm256_div_pd(_mm256_mul_pd(ymm4r8_negate(x_0),
			                                                    x_1),r3));
			   _mm256_storeu_pd(&H_2[0],_mm256_loadu_pd(&H1[0]));
			   _mm256_storeu_pd(&H_3[0],_mm256_add_pd(_mm256_div_pd(ymm4r8_negate(yC2),
			                                                    r3),invr));
			   if(useHalfRange) {
                              _mm256_storeu_pd(&H_0[0],_mm256_mul_pd(_mm256_loadu_pd(&H_0[0],_2)));
			      _mm256_storeu_pd(&H_1[0],_mm256_mul_pd(_mm256_loadu_pd(&H_1[0],_2)));
			      _mm256_storeu_pd(&H_2[0],_mm256_mul_pd(_mm256_loadu_pd(&H_2[0],_2)));
			      _mm256_storeu_pd(&H_3[0],_mm256_mul_pd(_mm256_loadu_pd(&H_3[0],_2)));
			   }
		    }


		     
                      
		      void gms::math::range_hessian_2d_ymm8r4_a(float * __restrict __ATTR_ALIGN__(32) H_0,
		                                      float * __restrict __ATTR_ALIGN__(32) H_1,
						      float * __restrict __ATTR_ALIGN__(32) H_2,
						      float * __restrict __ATTR_ALIGN__(32) H_3,
						      const __m256 x_0,
						      const __m256 x_1,
						      const bool useHalfRange) {

			   const __m256 _2   = _mm256_set1_ps(2.0f);
			   const __m256 _1   = _mm256_set1_ps(1.0f);
			   const __m256 xC2  = _mm256_mul_ps(x_0,x_0);
			   const __m256 yC2  = _mm256_mul_ps(x_1,x_1);
			   const __m256 r    = _mm256_sqrt_ps(_mm256_add_ps(xC2,yC2));
			   const __m256 r3   = _mm256_mul_ps(r,_mm256_mul_ps(r,r));
			   const __m256 invr = _mm256_div_ps(_1,r);
			   _mm256_store_ps(&H_0[0],_mm256_add_ps(_mm256_div_ps(ymm8r4_negate(xC2),
			                                                    r3),invr));
			   _mm256_store_ps(&H_1[0],_mm256_div_ps(_mm256_mul_ps(ymm8r4_negate(x_0),
			                                                    x_1),r3));
			   _mm256_store_ps(&H_2[0],_mm256_load_ps(&H1[0]));
			   _mm256_store_ps(&H_3[0],_mm256_add_ps(_mm256_div_ps(ymm8r4_negate(yC2),
			                                                    r3),invr));
			   if(useHalfRange) {
                              _mm256_store_ps(&H_0[0],_mm256_mul_ps(_mm256_load_ps(&H_0[0],_2)));
			      _mm256_store_ps(&H_1[0],_mm256_mul_ps(_mm256_load_ps(&H_1[0],_2)));
			      _mm256_store_ps(&H_2[0],_mm256_mul_ps(_mm256_load_ps(&H_2[0],_2)));
			      _mm256_store_ps(&H_3[0],_mm256_mul_ps(_mm256_load_ps(&H_3[0],_2)));
			   }
		    }


		     
                    
		     
		      
		     
		      void gms::math::range_hessian_2d_ymm8r4_u(float * __restrict  H_0,
		                                      float * __restrict  H_1,
						      float * __restrict  H_2,
						      float * __restrict  H_3,
						      const __m256 x_0,
						      const __m256 x_1,
						      const bool useHalfRange) {

			   const __m256 _2   = _mm256_set1_ps(2.0f);
			   const __m256 _1   = _mm256_set1_ps(1.0f);
			   const __m256 xC2  = _mm256_mul_ps(x_0,x_0);
			   const __m256 yC2  = _mm256_mul_ps(x_1,x_1);
			   const __m256 r    = _mm256_sqrt_ps(_mm256_add_ps(xC2,yC2));
			   const __m256 r3   = _mm256_mul_ps(r,_mm256_mul_ps(r,r));
			   const __m256 invr = _mm256_div_ps(_1,r);
			   _mm256_storeu_ps(&H_0[0],_mm256_add_ps(_mm256_div_ps(ymm8r4_negate(xC2),
			                                                    r3),invr));
			   _mm256_storeu_ps(&H_1[0],_mm256_div_ps(_mm256_mul_ps(ymm8r4_negate(x_0),
			                                                    x_1),r3));
			   _mm256_storeu_ps(&H_2[0],_mm256_loadu_ps(&H1[0]));
			   _mm256_storeu_ps(&H_3[0],_mm256_add_ps(_mm256_div_ps(ymm8r4_negate(yC2),
			                                                    r3),invr));
			   if(useHalfRange) {
                              _mm256_storeu_ps(&H_0[0],_mm256_mul_ps(_mm256_loadu_ps(&H_0[0],_2)));
			      _mm256_storeu_ps(&H_1[0],_mm256_mul_ps(_mm256_loadu_ps(&H_1[0],_2)));
			      _mm256_storeu_ps(&H_2[0],_mm256_mul_ps(_mm256_loadu_ps(&H_2[0],_2)));
			      _mm256_storeu_ps(&H_3[0],_mm256_mul_ps(_mm256_loadu_ps(&H_3[0],_2)));
			   }
		    }


		     
                    
		     
		      
		     
		      void gms::math::range_hessian_3d_ymm4r8_a(double * __restrict __ATTR_ALIGN__(32) H_0,
		                                     double * __restrict __ATTR_ALIGN__(32) H_1,
						     double * __restrict __ATTR_ALIGN__(32) H_2,
						     double * __restrict __ATTR_ALIGN__(32) H_3,
						     double * __restrict __ATTR_ALIGN__(32) H_4,
						     double * __restrict __ATTR_ALIGN__(32) H_5,
						     double * __restrict __ATTR_ALIGN__(32) H_6,
						     double * __restrict __ATTR_ALIGN__(32) H_7,
						     double * __restrict __ATTR_ALIGN__(32) H_8,
						     const __m256d x_0,
						     const __m256d x_1,
						     const __m256d x_2,
						     const bool useHalfRange) {
                           __m256d invr,invr3;
                           const __m256d _1   = _mm256_set1_pd(1.0);
			   const __m256d xC2  = _mm256_mul_pd(x_0,x_0);
			   const __m256d yC2  = _mm256_mul_pd(x_1,x_1);
			   const __m256d zC2  = _mm256_mul_pd(x_2,x_2);
			   const __m256d r    = _mm256_sqrt_pd(
			                              _mm256_add_pd(xC2,_mm256_add_pd(yC2,zC2)));
			   const __m256d r3   = _mm256_mul_pd(r,_mm256_mul_pd(r,r));
			   invr               = _mm256_div_pd(_1,r);
			   invr3              = _mm256_div_pd(_1,r3);
			   _mm256_store_pd(&H_0[0],_mm256_fmadd_pd(ymm4r8_negate(xC2),invr3,invr));
			   _mm256_store_pd(&H_1[0],_mm256_mul_pd(ymm4r8_negate(x_0),
			                                      _mm256_mul_pd(x_1,invr3)));
			   _mm256_store_pd(&H_2[0],_mm256_mul_pd(ymm4r8_negate(x_0),
			                                      _mm256_mul_pd(x_2,invr3)));
			   _mm256_store_pd(&H_3[0],_mm256_load_pd(&H_1[0]));
			   _mm256_store_pd(&H_4[0],_mm256_fmadd_pd(ymm4r8_negate(yC2),invr3,invr));
			   _mm256_store_pd(&H_5[0],_mm256_mul_pd(ymm4r8_negate(x_1),
			                                      _mm256_mul_pd(x_2,invr3)));
			   _mm256_store_pd(&H_6[0],_mm256_load_pd(&H_2[0]));
			   _mm256_store_pd(&H_7[0],_mm256_load_pd(&H_5[0]));
			   _mm256_store_pd(&H_8[0],_mm256_fmadd_pd(ymm4r8_negate(zC2),invr3,invr));
			   if(useHalfRange) {
			       const __m256d t0 = _mm256_load_pd(&H_0[0]);
                               _mm256_store_pd(&H_0[0],_mm256_add_pd(t0,t0));
			       const __m256d t1 = _mm256_load_pd(&H_1[0]);
			      _mm256_store_pd(&H_1[0],_mm256_add_pd(t1,t1));
			       const __m256d t2 = _mm256_load_pd(&H_2[0]);
			      _mm256_store_pd(&H_2[0],_mm256_add_pd(t2,t2));
			       const __m256d t3 = _mm256_load_pd(&H_3[0]);
			      _mm256_store_pd(&H_3[0],_mm256_add_pd(t3,t3));
			       const __m256d t4 = _mm256_load_pd(&H_4[0]);
			      _mm256_store_pd(&H_4[0],_mm256_add_pd(t4,t4));
			       const __m256d t5 = _mm256_load_pd(&H_5[0]);
			      _mm256_store_pd(&H_5[0],_mm256_add_pd(t5,t5));
			       const __m256d t6 = _mm256_load_pd(&H_6[0]);
			      _mm256_store_pd(&H_6[0],_mm256_add_pd(t6,t6));
			       const __m256d t7 = _mm256_load_pd(&H_7[0]);
			      _mm256_store_pd(&H_7[0],_mm256_add_pd(t7,t7));
			       const __m256d t8 = _mm256_load_pd(&H_8[0]);
			      _mm256_store_pd(&H_8[0],_mm256_add_pd(t8,t8));
			   }
		    }


		     
                    
		     
		      
		     
		      void gms::math::range_hessian_3d_ymm4r8_u(double * __restrict H_0,
		                                     double * __restrict H_1,
						     double * __restrict H_2,
						     double * __restrict H_3,
						     double * __restrict H_4,
						     double * __restrict H_5,
						     double * __restrict H_6,
						     double * __restrict H_7,
						     double * __restrict H_8,
						   const __m256d x_0,
						   const __m256d x_1,
						   const __m256d x_2,
						   const bool useHalfRange) {
                           __m256d invr,invr3;
                           const __m256d _1   = _mm256_set1_pd(1.0);
			   const __m256d xC2  = _mm256_mul_pd(x_0,x_0);
			   const __m256d yC2  = _mm256_mul_pd(x_1,x_1);
			   const __m256d zC2  = _mm256_mul_pd(x_2,x_2);
			   const __m256d r    = _mm256_sqrt_pd(
			                              _mm256_add_pd(xC2,_mm256_add_pd(yC2,zC2)));
			   const __m256d r3   = _mm256_mul_pd(r,_mm256_mul_pd(r,r));
			   invr               = _mm256_div_pd(_1,r);
			   invr3              = _mm256_div_pd(_1,r3);
			   _mm256_storeu_pd(&H_0[0],_mm256_fmadd_pd(ymm4r8_negate(xC2),invr3,invr));
			   _mm256_storeu_pd(&H_1[0],_mm256_mul_pd(ymm4r8_negate(x_0),
			                                      _mm256_mul_pd(x_1,invr3)));
			   _mm256_storeu_pd(&H_2[0],_mm256_mul_pd(ymm4r8_negate(x_0),
			                                      _mm256_mul_pd(x_2,invr3)));
			   _mm256_storeu_pd(&H_3[0],_mm256_load_pd(&H_1[0]));
			   _mm256_storeu_pd(&H_4[0],_mm256_fmadd_pd(ymm4r8_negate(yC2),invr3,invr));
			   _mm256_storeu_pd(&H_5[0],_mm256_mul_pd(ymm4r8_negate(x_1),
			                                      _mm256_mul_pd(x_2,invr3)));
			   _mm256_storeu_pd(&H_6[0],_mm256_load_pd(&H_2[0]));
			   _mm256_storeu_pd(&H_7[0],_mm256_load_pd(&H_5[0]));
			   _mm256_storeu_pd(&H_8[0],_mm256_fmadd_pd(ymm4r8_negate(zC2),invr3,invr));
			   if(useHalfRange) {
			       const __m256d t0 = _mm256_loadu_pd(&H_0[0]);
                               _mm256_storeu_pd(&H_0[0],_mm256_add_pd(t0,t0));
			       const __m256d t1 = _mm256_loadu_pd(&H_1[0]);
			      _mm256_storeu_pd(&H_1[0],_mm256_add_pd(t1,t1));
			       const __m256d t2 = _mm256_loadu_pd(&H_2[0]);
			      _mm256_storeu_pd(&H_2[0],_mm256_add_pd(t2,t2));
			       const __m256d t3 = _mm256_loadu_pd(&H_3[0]);
			      _mm256_storeu_pd(&H_3[0],_mm256_add_pd(t3,t3));
			       const __m256d t4 = _mm256_loadu_pd(&H_4[0]);
			      _mm256_storeu_pd(&H_4[0],_mm256_add_pd(t4,t4));
			       const __m256d t5 = _mm256_loadu_pd(&H_5[0]);
			      _mm256_storeu_pd(&H_5[0],_mm256_add_pd(t5,t5));
			       const __m256d t6 = _mm256_loadu_pd(&H_6[0]);
			      _mm256_storeu_pd(&H_6[0],_mm256_add_pd(t6,t6));
			       const __m256d t7 = _mm256_loadu_pd(&H_7[0]);
			      _mm256_storeu_pd(&H_7[0],_mm256_add_pd(t7,t7));
			       const __m256d t8 = _mm256_loadu_pd(&H_8[0]);
			      _mm256_storeu_pd(&H_8[0],_mm256_add_pd(t8,t8));
			   }
		    }



		     
                    
		     
		      
		     
		      void gms::math::range_hessian_3d_ymm4r8(__m256d * __restrict __ATTR_ALIGN__(32) H,
		                                   const __m256d x_0,
						   const __m256d x_1,
						   const __m256d x_2,
						   const bool useHalfRange) {
                           __m256d invr,invr3;
                           const __m256d _1   = _mm256_set1_pd(1.0);
			   const __m256d xC2  = _mm256_mul_pd(x_0,x_0);
			   const __m256d yC2  = _mm256_mul_pd(x_1,x_1);
			   const __m256d zC2  = _mm256_mul_pd(x_2,x_2);
			   const __m256d r    = _mm256_sqrt_pd(
			                              _mm256_add_pd(xC2,_mm256_add_pd(yC2,zC2)));
			   const __m256d r3   = _mm256_mul_pd(r,_mm256_mul_pd(r,r));
			   invr               = _mm256_div_pd(_1,r);
			   invr3              = _mm256_div_pd(_1,r3);
			   H[0]                = _mm256_fmadd_pd(ymm4r8_negate(xC2),invr3,invr);
			   H[1]                = _mm256_mul_pd(ymm4r8_negate(x_0),
			                                      _mm256_mul_pd(x_1,invr3));
			   H[2]                = _mm256_mul_pd(ymm4r8_negate(x_0),
			                                      _mm256_mul_pd(x_2,invr3));
			   H[3]                = H[1];
			   H[4]                = _mm256_fmadd_pd(ymm4r8_negate(yC2),invr3,invr);
			   H[5]                = _mm256_mul_pd(ymm4r8_negate(x_1),
			                                      _mm256_mul_pd(x_2,invr3));
			   H[6]                = H[2];
			   H[7]                = H[5];
			   H[8]                = _mm256_fmadd_pd(ymm4r8_negate(zC2),invr3,invr);
			   if(useHalfRange) {
                               H[0] = _mm256_add_pd(H[0],H[0]);
			       H[1] = _mm256_add_pd(H[1],H[1]);
			       H[2] = _mm256_add_pd(H[2],H[2]);
			       H[3] = _mm256_add_pd(H[3],H[3]);
			       H[4] = _mm256_add_pd(H[4],H[4]);
			       H[5] = _mm256_add_pd(H[5],H[5]);
			       H[6] = _mm256_add_pd(H[6],H[6]);
			       H[7] = _mm256_add_pd(H[7],H[7]);
			       H[8] = _mm256_add_pd(H[8],H[8]);
			   }
		    }



		     
                    
		     
		      
		     
		      void gms::math::range_hessian_3d_ymm8r4_a(float * __restrict __ATTR_ALIGN__(32) H_0,
		                                      float * __restrict __ATTR_ALIGN__(32) H_1,
						      float * __restrict __ATTR_ALIGN__(32) H_2,
						      float * __restrict __ATTR_ALIGN__(32) H_3,
						      float * __restrict __ATTR_ALIGN__(32) H_4,
						      float * __restrict __ATTR_ALIGN__(32) H_5,
						      float * __restrict __ATTR_ALIGN__(32) H_6,
						      float * __restrict __ATTR_ALIGN__(32) H_7,
						      float * __restrict __ATTR_ALIGN__(32) H_8,
						      const __m256 x_0,
						      const __m256 x_1,
						      const __m256 x_2,
						      const bool useHalfRange) {
                           __m256 invr,invr3;
                           const __m256 _1   = _mm256_set1_ps(1.0f);
			   const __m256 xC2  = _mm256_mul_ps(x_0,x_0);
			   const __m256 yC2  = _mm256_mul_ps(x_1,x_1);
			   const __m256 zC2  = _mm256_mul_ps(x_2,x_2);
			   const __m256 r    = _mm256_sqrt_ps(
			                              _mm256_add_ps(xC2,_mm256_add_ps(yC2,zC2)));
			   const __m256 r3   = _mm256_mul_ps(r,_mm256_mul_ps(r,r));
			   invr               = _mm256_div_ps(_1,r);
			   invr3              = _mm256_div_ps(_1,r3);
			   _mm256_store_pd(&H_0[0],_mm256_fmadd_ps(ymm8r4_negate(xC2),invr3,invr));
			   _mm256_store_pd(&H_1[0],_mm256_mul_ps(ymm8r4_negate(x_0),
			                                      _mm256_mul_ps(x_1,invr3)));
			   _mm256_store_pd(&H_2[0],_mm256_mul_ps(ymm8r4_negate(x_0),
			                                      _mm256_mul_ps(x_2,invr3)));
			   _mm256_store_pd(&H_3[0],_mm256_load_pd(&H_1[0]));
			   _mm256_store_pd(&H_4[0],_mm256_fmadd_ps(ymm8r4_negate(yC2),invr3,invr));
			   _mm256_store_pd(&H_5[0],_mm256_mul_ps(ymm8r4_negate(x_1),
			                                      _mm256_mul_ps(x_2,invr3)));
			   _mm256_store_pd(&H_6[0],_mm256_load_pd(&H_2[0]));
			   _mm256_store_pd(&H_7[0],_mm256_store_pd(&H_5[0]));
			   _mm256_store_pd(&H_8[0],_mm256_fmadd_ps(ymm8r4_negate(zC2),invr3,invr));
			   if(useHalfRange) {
                               const __m256 t0 = _mm256_load_ps(&H_0[0]);
                               _mm256_store_ps(&H_0[0],_mm256_add_ps(t0,t0));
			       const __m256 t1 = _mm256_load_ps(&H_1[0]);
			      _mm256_store_ps(&H_1[0],_mm256_add_ps(t1,t1));
			       const __m256 t2 = _mm256_load_ps(&H_2[0]);
			      _mm256_store_ps(&H_2[0],_mm256_add_ps(t2,t2));
			       const __m256 t3 = _mm256_load_ps(&H_3[0]);
			      _mm256_store_ps(&H_3[0],_mm256_add_ps(t3,t3));
			       const __m256 t4 = _mm256_load_ps(&H_4[0]);
			      _mm256_store_ps(&H_4[0],_mm256_add_ps(t4,t4));
			       const __m256 t5 = _mm256_load_ps(&H_5[0]);
			      _mm256_store_ps(&H_5[0],_mm256_add_ps(t5,t5));
			       const __m256 t6 = _mm256_load_ps(&H_6[0]);
			      _mm256_store_ps(&H_6[0],_mm256_add_ps(t6,t6));
			       const __m256 t7 = _mm256_load_ps(&H_7[0]);
			      _mm256_store_ps(&H_7[0],_mm256_add_ps(t7,t7));
			       const __m256 t8 = _mm256_load_ps(&H_8[0]);
			      _mm256_store_ps(&H_8[0],_mm256_add_ps(t8,t8));
			   }
		    }


		     
                    
		     
		      
		     
		      void gms::math::range_hessian_3d_ymm8r4_u(float * __restrict  H_0,
		                                      float * __restrict  H_1,
						      float * __restrict  H_2,
						      float * __restrict  H_3,
						      float * __restrict  H_4,
						      float * __restrict  H_5,
						      float * __restrict  H_6,
						      float * __restrict  H_7,
						      float * __restrict  H_8,
						      const __m256 x_0,
						      const __m256 x_1,
						      const __m256 x_2,
						      const bool useHalfRange) {
                           __m256 invr,invr3;
                           const __m256 _1   = _mm256_set1_ps(1.0f);
			   const __m256 xC2  = _mm256_mul_ps(x_0,x_0);
			   const __m256 yC2  = _mm256_mul_ps(x_1,x_1);
			   const __m256 zC2  = _mm256_mul_ps(x_2,x_2);
			   const __m256 r    = _mm256_sqrt_ps(
			                              _mm256_add_ps(xC2,_mm256_add_ps(yC2,zC2)));
			   const __m256 r3   = _mm256_mul_ps(r,_mm256_mul_ps(r,r));
			   invr               = _mm256_div_ps(_1,r);
			   invr3              = _mm256_div_ps(_1,r3);
			   _mm256_storeu_pd(&H_0[0],_mm256_fmadd_ps(ymm8r4_negate(xC2),invr3,invr));
			   _mm256_storeu_pd(&H_1[0],_mm256_mul_ps(ymm8r4_negate(x_0),
			                                      _mm256_mul_ps(x_1,invr3)));
			   _mm256_storeu_pd(&H_2[0],_mm256_mul_ps(ymm8r4_negate(x_0),
			                                      _mm256_mul_ps(x_2,invr3)));
			   _mm256_storeu_pd(&H_3[0],_mm256_load_pd(&H_1[0]));
			   _mm256_storeu_pd(&H_4[0],_mm256_fmadd_ps(ymm8r4_negate(yC2),invr3,invr));
			   _mm256_storeu_pd(&H_5[0],_mm256_mul_ps(ymm8r4_negate(x_1),
			                                      _mm256_mul_ps(x_2,invr3)));
			   _mm256_storeu_pd(&H_6[0],_mm256_load_pd(&H_2[0]));
			   _mm256_storeu_pd(&H_7[0],_mm256_store_pd(&H_5[0]));
			   _mm256_storeu_pd(&H_8[0],_mm256_fmadd_ps(ymm8r4_negate(zC2),invr3,invr));
			   if(useHalfRange) {
                               const __m256 t0 = _mm256_loadu_ps(&H_0[0]);
                               _mm256_storeu_ps(&H_0[0],_mm256_add_ps(t0,t0));
			       const __m256 t1 = _mm256_loadu_ps(&H_1[0]);
			      _mm256_storeu_ps(&H_1[0],_mm256_add_ps(t1,t1));
			       const __m256 t2 = _mm256_loadu_ps(&H_2[0]);
			      _mm256_storeu_ps(&H_2[0],_mm256_add_ps(t2,t2));
			       const __m256 t3 = _mm256_loadu_ps(&H_3[0]);
			      _mm256_storeu_ps(&H_3[0],_mm256_add_ps(t3,t3));
			       const __m256 t4 = _mm256_loadu_ps(&H_4[0]);
			      _mm256_storeu_ps(&H_4[0],_mm256_add_ps(t4,t4));
			       const __m256 t5 = _mm256_loadu_ps(&H_5[0]);
			      _mm256_storeu_ps(&H_5[0],_mm256_add_ps(t5,t5));
			       const __m256 t6 = _mm256_loadu_ps(&H_6[0]);
			      _mm256_storeu_ps(&H_6[0],_mm256_add_ps(t6,t6));
			       const __m256 t7 = _mm256_loadu_ps(&H_7[0]);
			      _mm256_storeu_ps(&H_7[0],_mm256_add_ps(t7,t7));
			       const __m256 t8 = _mm256_loadu_ps(&H_8[0]);
			      _mm256_storeu_ps(&H_8[0],_mm256_add_ps(t8,t8));
			   }
		    }



		     
                    
		     
		      
		   


		     
                    
		     
		      
		     
		      void gms::math::range_hess_gen_2d_ymm4r8(__m256d &H_0,
		                                    __m256d &H_1,
						    __m256d &H_2,
						    __m256d &H_3,
						    const __m256d x_0,
						    const __m256d x_1,
						    const __m256d rx_0,
						    const __m256d rx_1,
						    const __m256d tx_0,
						    const __m256d tx_1,
						    const bool useHalfRange) {

			  __m256d inv1,inv2,inv3,inv4;
                          const __m256d _1     = _mm256_set1_pd(1.0);
			  const __m256d _0_5   = _mm256_set1_pd(0.5);
			  const __m256d dRxx   = _mm256_sub_pd(x_0,rx_0);
			  const __m256d dRxx2  = _mm256_mul_pd(dRxx,dRxx);
			  const __m256d dRxy   = _mm256_sub_pd(x_1,rx_1);
			  const __m256d dRxy2  = _mm256_mul_pd(dRxy2,dRxy2);
			  const __m256d nrmdRx = _mm256_sqrt_pd(_mm256_add_pd(dRxx2,dRxy2));
			  inv1                 = _mm256_div_pd(_1,nrmdRx);
			  const __m256d nrmdRx3= _mm256_mul_pd(nrmdRx,_mm256_mul_pd(nrmdRx,nrmdRx));
			  inv3                 = _mm256_div_pd(_1,nrmdRx3);
			  const __m256d dTxx   = _mm256_sub_pd(x_0,tx_0);
			  const __m256d dTxx2  = _mm256_mul_pd(dTxx,dTxx);
			  const __m256d dTxy   = _mm256_sub_pd(x_1,tx_1);
			  const __m256d dTxy2  = _mm256_mul_pd(dTxy2,dTxy2);
			  const __m256d nrmdTx = _mm256_sqrt_pd(_mm256_add_pd(dTxx2,dTxy2));
			  inv2                 = _mm256_div_pd(_1,nrmdTx);
			  const __m256d nrmdTx3= _mm256_mul_pd(nrmdTx,_mm256_mul_pd(nrmdTx,nrmdTx));
			  inv4                 = _mm256_div_pd(_1,nrmdTx3);
			  H_0                  = _mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxx2),inv3,inv1),
			                                       _mm256_fmadd_pd(dTxx2,inv4,inv2));
			  H_1                  = _mm256_sub_pd(_mm256_mul_pd(ymm4r8_negate(dRxx),
			                                       _mm256_mul_pd(dRxy,inv3)),
							       _mm256_mul_pd(dTxx,
							       _mm256_mul_pd(dTxy,inv4)));
			  H_2                  = H_1;
			  H_3                  = _mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxy2),inv3,inv1),
			                                       _mm256_fmadd_pd(dTxy2,inv4,inv2));
			  if(useHalfRange) {
                             H_0 = _mm256_mul_pd(H_0,_0_5);
			     H_1 = _mm256_mul_pd(H_1,_0_5);
			     H_2 = _mm256_mul_pd(H_2,_0_5);
			     H_3 = _mm256_mul_pd(H_3,_0_5);
			  }
			                                                     
		    }



		     
                    
		     
		      
		     
		      void gms::math::range_hess_gen_2d_ymm4r8_a(double * __restrict __ATTR_ALIGN__(32) H_0,
		                                      double * __restrict __ATTR_ALIGN__(32) H_1,
						      double * __restrict __ATTR_ALIGN__(32) H_2,
						      double * __restrict __ATTR_ALIGN__(32) H_3,
						      const __m256d x_0,
						      const __m256d x_1,
						      const __m256d rx_0,
						      const __m256d rx_1,
						      const __m256d tx_0,
						      const __m256d tx_1,
						      const bool useHalfRange) {

			  __m256d inv1,inv2,inv3,inv4;
                          const __m256d _1     = _mm256_set1_pd(1.0);
			  const __m256d _0_5   = _mm256_set1_pd(0.5);
			  const __m256d dRxx   = _mm256_sub_pd(x_0,rx_0);
			  const __m256d dRxx2  = _mm256_mul_pd(dRxx,dRxx);
			  const __m256d dRxy   = _mm256_sub_pd(x_1,rx_1);
			  const __m256d dRxy2  = _mm256_mul_pd(dRxy2,dRxy2);
			  const __m256d nrmdRx = _mm256_sqrt_pd(_mm256_add_pd(dRxx2,dRxy2));
			  inv1                 = _mm256_div_pd(_1,nrmdRx);
			  const __m256d nrmdRx3= _mm256_mul_pd(nrmdRx,_mm256_mul_pd(nrmdRx,nrmdRx));
			  inv3                 = _mm256_div_pd(_1,nrmdRx3);
			  const __m256d dTxx   = _mm256_sub_pd(x_0,tx_0);
			  const __m256d dTxx2  = _mm256_mul_pd(dTxx,dTxx);
			  const __m256d dTxy   = _mm256_sub_pd(x_1,tx_1);
			  const __m256d dTxy2  = _mm256_mul_pd(dTxy2,dTxy2);
			  const __m256d nrmdTx = _mm256_sqrt_pd(_mm256_add_pd(dTxx2,dTxy2));
			  inv2                 = _mm256_div_pd(_1,nrmdTx);
			  const __m256d nrmdTx3= _mm256_mul_pd(nrmdTx,_mm256_mul_pd(nrmdTx,nrmdTx));
			  inv4                 = _mm256_div_pd(_1,nrmdTx3);
			  _mm256_store_pd(&H_0[0],_mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxx2),inv3,inv1),
			                                       _mm256_fmadd_pd(dTxx2,inv4,inv2)));
			  _mm256_store_pd(&H_1[0],_mm256_sub_pd(_mm256_mul_pd(ymm4r8_negate(dRxx),
			                                       _mm256_mul_pd(dRxy,inv3)),
							       _mm256_mul_pd(dTxx,
							       _mm256_mul_pd(dTxy,inv4))));
			  _mm256_store_pd(&H_2[0],_mm256_load_pd(&H_1[0]));
			  _mm256_store_pd(&H_3[0],_mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxy2),inv3,inv1),
			                                       _mm256_fmadd_pd(dTxy2,inv4,inv2)));
			  if(useHalfRange) {
                             _mm256_store_pd(&H_0[0],_mm256_mul_pd(_mm256_load_pd(&H_0[0],_0_5)));
			     _mm256_store_pd(&H_1[0],_mm256_mul_pd(_mm256_load_pd(&H_1[0],_0_5)));
			     _mm256_store_pd(&H_2[0],_mm256_mul_pd(_mm256_load_pd(&H_2[0],_0_5)));
			     _mm256_store_pd(&H_3[0],_mm256_mul_pd(_mm256_load_pd(&H_3[0],_0_5)));
			  }
			                                                     
		    }


		     
                    
		     
		      
		     
		      void gms::math::range_hess_gen_2d_ymm4r8_u(double * __restrict H_0,
		                                      double * __restrict H_1,
						      double * __restrict H_2,
						      double * __restrict H_3,
						      const __m256d x_0,
						      const __m256d x_1,
						      const __m256d rx_0,
						      const __m256d rx_1,
						      const __m256d tx_0,
						      const __m256d tx_1,
						      const bool useHalfRange) {

			  __m256d inv1,inv2,inv3,inv4;
                          const __m256d _1     = _mm256_set1_pd(1.0);
			  const __m256d _0_5   = _mm256_set1_pd(0.5);
			  const __m256d dRxx   = _mm256_sub_pd(x_0,rx_0);
			  const __m256d dRxx2  = _mm256_mul_pd(dRxx,dRxx);
			  const __m256d dRxy   = _mm256_sub_pd(x_1,rx_1);
			  const __m256d dRxy2  = _mm256_mul_pd(dRxy2,dRxy2);
			  const __m256d nrmdRx = _mm256_sqrt_pd(_mm256_add_pd(dRxx2,dRxy2));
			  inv1                 = _mm256_div_pd(_1,nrmdRx);
			  const __m256d nrmdRx3= _mm256_mul_pd(nrmdRx,_mm256_mul_pd(nrmdRx,nrmdRx));
			  inv3                 = _mm256_div_pd(_1,nrmdRx3);
			  const __m256d dTxx   = _mm256_sub_pd(x_0,tx_0);
			  const __m256d dTxx2  = _mm256_mul_pd(dTxx,dTxx);
			  const __m256d dTxy   = _mm256_sub_pd(x_1,tx_1);
			  const __m256d dTxy2  = _mm256_mul_pd(dTxy2,dTxy2);
			  const __m256d nrmdTx = _mm256_sqrt_pd(_mm256_add_pd(dTxx2,dTxy2));
			  inv2                 = _mm256_div_pd(_1,nrmdTx);
			  const __m256d nrmdTx3= _mm256_mul_pd(nrmdTx,_mm256_mul_pd(nrmdTx,nrmdTx));
			  inv4                 = _mm256_div_pd(_1,nrmdTx3);
			  _mm256_storeu_pd(&H_0[0],_mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxx2),inv3,inv1),
			                                       _mm256_fmadd_pd(dTxx2,inv4,inv2)));
			  _mm256_storeu_pd(&H_1[0],_mm256_sub_pd(_mm256_mul_pd(ymm4r8_negate(dRxx),
			                                       _mm256_mul_pd(dRxy,inv3)),
							       _mm256_mul_pd(dTxx,
							       _mm256_mul_pd(dTxy,inv4))));
			  _mm256_storeu_pd(&H_2[0],_mm256_load_pd(&H_1[0]));
			  _mm256_storeu_pd(&H_3[0],_mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxy2),inv3,inv1),
			                                       _mm256_fmadd_pd(dTxy2,inv4,inv2)));
			  if(useHalfRange) {
                             _mm256_storeu_pd(&H_0[0],_mm256_mul_pd(_mm256_loadu_pd(&H_0[0],_0_5)));
			     _mm256_storeu_pd(&H_1[0],_mm256_mul_pd(_mm256_loadu_pd(&H_1[0],_0_5)));
			     _mm256_storeu_pd(&H_2[0],_mm256_mul_pd(_mm256_loadu_pd(&H_2[0],_0_5)));
			     _mm256_storeu_pd(&H_3[0],_mm256_mul_pd(_mm256_loadu_pd(&H_3[0],_0_5)));
			  }
			                                                     
		    }




		     
                    
		     
		      
		     
		      void gms::math::range_hess_gen_2d_ymm8r4(__m256 &H_0,
		                                     __m256 &H_1,
						     __m256 &H_2,
						     __m256 &H_3,
						     const __m256 x_0,
						     const __m256 x_1,
						     const __m256 rx_0,
						     const __m256 rx_1,
						     const __m256 tx_0,
						     const __m256 tx_1,
						     const bool useHalfRange) {

			  __m256 inv1,inv2,inv3,inv4;
                          const __m256 _1     = _mm256_set1_ps(1.0f);
			  const __m256 _0_5   = _mm256_set1_ps(0.5f);
			  const __m256 dRxx   = _mm256_sub_ps(x_0,rx_0);
			  const __m256 dRxx2  = _mm256_mul_ps(dRxx,dRxx);
			  const __m256 dRxy   = _mm256_sub_ps(x_1,rx_1);
			  const __m256 dRxy2  = _mm256_mul_ps(dRxy2,dRxy2);
			  const __m256 nrmdRx = _mm256_sqrt_ps(_mm256_add_ps(dRxx2,dRxy2));
			  inv1                 = _mm256_div_ps(_1,nrmdRx);
			  const __m256 nrmdRx3= _mm256_mul_ps(nrmdRx,_mm256_mul_ps(nrmdRx,nrmdRx));
			  inv3                 = _mm256_div_ps(_1,nrmdRx3);
			  const __m256 dTxx   = _mm256_sub_ps(x_0,tx_0);
			  const __m256 dTxx2  = _mm256_mul_ps(dTxx,dTxx);
			  const __m256 dTxy   = _mm256_sub_ps(x_1,tx_1);
			  const __m256 dTxy2  = _mm256_mul_ps(dTxy2,dTxy2);
			  const __m256 nrmdTx = _mm256_sqrt_ps(_mm256_add_ps(dTxx2,dTxy2));
			  inv2                 = _mm256_div_ps(_1,nrmdTx);
			  const __m256 nrmdTx3= _mm256_mul_ps(nrmdTx,_mm256_mul_ps(nrmdTx,nrmdTx));
			  inv4                 = _mm256_div_ps(_1,nrmdTx3);
			  H_0                  = _mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxx2),inv3,inv1),
			                                       _mm256_fmadd_ps(dTxx2,inv4,inv2));
			  H_1                  = _mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxx),
			                                       _mm256_mul_ps(dRxy,inv3)),
							       _mm256_mul_ps(dTxx,
							       _mm256_mul_ps(dTxy,inv4)));
			  H_2                  = H_1;
			  H_3                  = _mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxy2),inv3,inv1),
			                                       _mm256_fmadd_ps(dTxy2,inv4,inv2));
			  if(useHalfRange) {
                             H_0 = _mm256_mul_ps(H_0,_0_5);
			     H_1 = _mm256_mul_ps(H_1,_0_5);
			     H_2 = _mm256_mul_ps(H_2,_0_5);
			     H_3 = _mm256_mul_ps(H_3,_0_5);
			  }
			                                                     
		    }


		     
                    
		     
		      
		     
		      void gms::math::range_hess_gen_2d_ymm8r4_a(float * __restrict __ATTR_ALIGN__(32) H_0,
		                                       float * __restrict __ATTR_ALIGN__(32) H_1,
						       float * __restrict __ATTR_ALIGN__(32) H_2,
						       float * __restrict __ATTR_ALIGN__(32) H_3,
						       const __m256 x_0,
						       const __m256 x_1,
						       const __m256 rx_0,
						       const __m256 rx_1,
						       const __m256 tx_0,
						       const __m256 tx_1,
						       const bool useHalfRange) {

			  __m256 inv1,inv2,inv3,inv4;
                          const __m256 _1     = _mm256_set1_ps(1.0f);
			  const __m256 _0_5   = _mm256_set1_ps(0.5f);
			  const __m256 dRxx   = _mm256_sub_ps(x_0,rx_0);
			  const __m256 dRxx2  = _mm256_mul_ps(dRxx,dRxx);
			  const __m256 dRxy   = _mm256_sub_ps(x_1,rx_1);
			  const __m256 dRxy2  = _mm256_mul_ps(dRxy2,dRxy2);
			  const __m256 nrmdRx = _mm256_sqrt_ps(_mm256_add_ps(dRxx2,dRxy2));
			  inv1                 = _mm256_div_ps(_1,nrmdRx);
			  const __m256 nrmdRx3= _mm256_mul_ps(nrmdRx,_mm256_mul_ps(nrmdRx,nrmdRx));
			  inv3                 = _mm256_div_ps(_1,nrmdRx3);
			  const __m256 dTxx   = _mm256_sub_ps(x_0,tx_0);
			  const __m256 dTxx2  = _mm256_mul_ps(dTxx,dTxx);
			  const __m256 dTxy   = _mm256_sub_ps(x_1,tx_1);
			  const __m256 dTxy2  = _mm256_mul_ps(dTxy2,dTxy2);
			  const __m256 nrmdTx = _mm256_sqrt_ps(_mm256_add_ps(dTxx2,dTxy2));
			  inv2                 = _mm256_div_ps(_1,nrmdTx);
			  const __m256 nrmdTx3= _mm256_mul_ps(nrmdTx,_mm256_mul_ps(nrmdTx,nrmdTx));
			  inv4                 = _mm256_div_ps(_1,nrmdTx3);
			  _mm256_store_ps(&H_0[0],_mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxx2),inv3,inv1),
			                                       _mm256_fmadd_ps(dTxx2,inv4,inv2)));
			  _mm256_store_ps(&H_1[0],_mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxx),
			                                       _mm256_mul_ps(dRxy,inv3)),
							       _mm256_mul_ps(dTxx,
							       _mm256_mul_ps(dTxy,inv4))));
			  _mm256_store_ps(&H_2[0],_mm256_load_ps(&H_1[0]));
			  _mm256_store_ps(&H_3[0],_mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxy2),inv3,inv1),
			                                       _mm256_fmadd_ps(dTxy2,inv4,inv2)));
			  if(useHalfRange) {
                             _mm256_store_ps(&H_0[0],_mm256_mul_ps(_mm256_load_ps(&H_0[0],_0_5)));
			     _mm256_store_ps(&H_1[0],_mm256_mul_ps(_mm256_load_ps(&H_1[0],_0_5)));
			     _mm256_store_ps(&H_2[0],_mm256_mul_ps(_mm256_load_ps(&H_2[0],_0_5)));
			     _mm256_store_ps(&H_3[0],_mm256_mul_ps(_mm256_load_ps(&H_3[0],_0_5)));
			  }
			                                                     
		    }


		     
                    
		     
		      
		     
		      void gms::math::range_hess_gen_2d_ymm8r4_u(float * __restrict  H_0,
		                                       float * __restrict  H_1,
						       float * __restrict  H_2,
						       float * __restrict  H_3,
						       const __m256 x_0,
						       const __m256 x_1,
						       const __m256 rx_0,
						       const __m256 rx_1,
						       const __m256 tx_0,
						       const __m256 tx_1,
						       const bool useHalfRange) {

			  __m256 inv1,inv2,inv3,inv4;
                          const __m256 _1     = _mm256_set1_ps(1.0f);
			  const __m256 _0_5   = _mm256_set1_ps(0.5f);
			  const __m256 dRxx   = _mm256_sub_ps(x_0,rx_0);
			  const __m256 dRxx2  = _mm256_mul_ps(dRxx,dRxx);
			  const __m256 dRxy   = _mm256_sub_ps(x_1,rx_1);
			  const __m256 dRxy2  = _mm256_mul_ps(dRxy2,dRxy2);
			  const __m256 nrmdRx = _mm256_sqrt_ps(_mm256_add_ps(dRxx2,dRxy2));
			  inv1                 = _mm256_div_ps(_1,nrmdRx);
			  const __m256 nrmdRx3= _mm256_mul_ps(nrmdRx,_mm256_mul_ps(nrmdRx,nrmdRx));
			  inv3                 = _mm256_div_ps(_1,nrmdRx3);
			  const __m256 dTxx   = _mm256_sub_ps(x_0,tx_0);
			  const __m256 dTxx2  = _mm256_mul_ps(dTxx,dTxx);
			  const __m256 dTxy   = _mm256_sub_ps(x_1,tx_1);
			  const __m256 dTxy2  = _mm256_mul_ps(dTxy2,dTxy2);
			  const __m256 nrmdTx = _mm256_sqrt_ps(_mm256_add_ps(dTxx2,dTxy2));
			  inv2                 = _mm256_div_ps(_1,nrmdTx);
			  const __m256 nrmdTx3= _mm256_mul_ps(nrmdTx,_mm256_mul_ps(nrmdTx,nrmdTx));
			  inv4                 = _mm256_div_ps(_1,nrmdTx3);
			  _mm256_storeu_ps(&H_0[0],_mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxx2),inv3,inv1),
			                                       _mm256_fmadd_ps(dTxx2,inv4,inv2)));
			  _mm256_storeu_ps(&H_1[0],_mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxx),
			                                       _mm256_mul_ps(dRxy,inv3)),
							       _mm256_mul_ps(dTxx,
							       _mm256_mul_ps(dTxy,inv4))));
			  _mm256_storeu_ps(&H_2[0],_mm256_load_ps(&H_1[0]));
			  _mm256_storeu_ps(&H_3[0],_mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxy2),inv3,inv1),
			                                       _mm256_fmadd_ps(dTxy2,inv4,inv2)));
			  if(useHalfRange) {
                             _mm256_storeu_ps(&H_0[0],_mm256_mul_ps(_mm256_loadu_ps(&H_0[0],_0_5)));
			     _mm256_storeu_ps(&H_1[0],_mm256_mul_ps(_mm256_loadu_ps(&H_1[0],_0_5)));
			     _mm256_storeu_ps(&H_2[0],_mm256_mul_ps(_mm256_loadu_ps(&H_2[0],_0_5)));
			     _mm256_storeu_ps(&H_3[0],_mm256_mul_ps(_mm256_loadu_ps(&H_3[0],_0_5)));
			  }
			                                                     
		    }





		     
                    
		     
		      
		     
		      void gms::math::range_hess_3d_ymm4r8(__m256d &H_0,
		                                __m256d &H_1,
						__m256d &H_2,
						__m256d &H_3,
						__m256d &H_4,
						__m256d &H_5,
						__m256d &H_6,
						__m256d &H_7,
						__m256d &H_8,
						const __m256d x_0,
						const __m256d x_1,
						const __m256d x_2,
						const __m256d rx_0,
						const __m256d rx_1,
						const __m256d rx_2,
						const __m256d tx_0,
						const __m256d tx_1,
						const __m256d tx_2,
						const bool useHalfRange) {


			  const __m256d _1      = _mm256_set1_pd(1.0);
			  const __m256d _0_5    = _mm256_set1_pd(0.5);
			  const __m256d dRxx    = _mm256_sub_pd(x_0,rx_0);
			  const __m256d dRxx2   = _mm256_mul_pd(dRxx,dRxx);
			  const __m256d dRxy    = _mm256_sub_pd(x_1,rx_1);
			  const __m256d dRxy2   = _mm256_mul_pd(dRxy,dRxy);
			  const __m256d dRxz    = _mm256_sub_pd(x_2,rx_2);
			  const __m256d dRxz2   = _mm256_mul_pd(dRxz,dRxz);
			  const __m256d nrmdRx  = _mm256_sqrt_pd(_mm256_mul_pd(dRxx2,
			                                                       _mm256_mul_pd(dRxy2,dRxz2)));
			  const __m256d inv0    = _mm256_div_pd(_1,nrmdRx);						      
			  const __m256d nrmdRx3 = _mm256_mul_pd(nrmdRx,_mm256_mul_pd(nrmdRx3,nrmdRx3));
			  const __m256d inv1    = _mm256_div_pd(_1,nrmdRx3);
			  const __m256d dTxx    = _mm256_sub_pd(x_0,tx_0);
			  const __m256d dTxx2   = _mm256_mul_pd(dTxx,dTxx);
			  const __m256d dTxy    = _mm256_sub_pd(x_1,tx_1);
			  const __m256d dTxy2   = _mm256_mul_pd(dTxy,dTxy);
			  const __m256d dTxz    = _mm256_sub_pd(x_2,tx_2);
			  const __m256d dTxz2   = _mm256_mul_pd(dTxz,dTxz);
			  const __m256d nrmdTx  = _mm256_sqrt_pd(_mm256_mul_pd(dTxx2,
			                                                       _mm256_mul_pd(dTxy2,dTxz2)));
			  const __m256d inv3    = _mm256_div_pd(_1,nrmdTx);
			  const __m256d nrmdTx3 = _mm256_mul_pd(nrmdTx,_mm256_mul_pd(nrmdTx3,nrmdTx3));
			  const __m256d inv2    = _mm256_div_pd(_1,nrmdTx3);
			  H_0                   = _mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxx2),inv1,inv0),
			                                        _mm256_fmadd_pd(dTxx2,inv2,inv3));
			  H_1                   = _mm256_sub_pd(_mm256_mul_pd(ymm4r8_negate(dRxx),
			                                        _mm256_mul_pd(dRxy,inv1)),
								_mm256_mul_pd(dTxx,
								_mm256_mul_pd(dTxy,inv2)));
			  H_2                   = _mm256_sub_pd(_mm256_mul_pd(ymm4r8_negate(dRxx),
			                                        _mm256_mul_pd(dRxz,inv1)),
								_mm256_mul_pd(dTxx,
								_mm256_mul_pd(dTxz,inv2)));
			  H_3                   = H_1;
			  H_4                   = _mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxy2),inv1,inv0),
			                                        _mm256_fmadd_pd(dTxy2,inv2,inv3));
			  H_5                   = _mm256_sub_pd(_mm256_mul_pd(ymm4r8_negate(dRxy),
			                                        _mm256_mul_pd(dRxz,inv1)),
								_mm256_mul_pd(dTxy,
								_mm256_mul_pd(dTxz,inv2)));
			  H_6                   = H_2;
			  H_7                   = H_5;
			  H_8                   = _mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxz2),inv1,inv0),
			                                        _mm256_fmadd_pd(dTxz2,inv2,inv3));
			  if(useHalfRange) {
                             H_0 = _mm256_mul_pd(H_0,_0_5);
			     H_1 = _mm256_mul_pd(H_1,_0_5);
			     H_2 = _mm256_mul_pd(H_2,_0_5);
			     H_3 = _mm256_mul_pd(H_3,_0_5);
			     H_4 = _mm256_mul_pd(H_4,_0_5);
			     H_5 = _mm256_mul_pd(H_5,_0_5);
			     H_6 = _mm256_mul_pd(H_6,_0_5);
			     H_7 = _mm256_mul_pd(H_7,_0_5);
			     H_8 = _mm256_mul_pd(H_8,_0_5);
			  }
		    }


		     
                    
		     
		      
		     
		      void gms::math::range_hess_3d_ymm4r8_a( double * __restrict __ATTR_ALIGN__(32) H_0,
		                                   double * __restrict __ATTR_ALIGN__(32) H_1,
						   double * __restrict __ATTR_ALIGN__(32) H_2,
						   double * __restrict __ATTR_ALIGN__(32) H_3,
						   double * __restrict __ATTR_ALIGN__(32) H_4,
						   double * __restrict __ATTR_ALIGN__(32) H_5,
						   double * __restrict __ATTR_ALIGN__(32) H_6,
						   double * __restrict __ATTR_ALIGN__(32) H_7,
						   double * __restrict __ATTR_ALIGN__(32) H_8,
						   const __m256d x_0,
						   const __m256d x_1,
						   const __m256d x_2,
						   const __m256d rx_0,
						   const __m256d rx_1,
						   const __m256d rx_2,
						   const __m256d tx_0,
						   const __m256d tx_1,
						   const __m256d tx_2,
						   const bool useHalfRange) {


			  const __m256d _1      = _mm256_set1_pd(1.0);
			  const __m256d _0_5    = _mm256_set1_pd(0.5);
			  const __m256d dRxx    = _mm256_sub_pd(x_0,rx_0);
			  const __m256d dRxx2   = _mm256_mul_pd(dRxx,dRxx);
			  const __m256d dRxy    = _mm256_sub_pd(x_1,rx_1);
			  const __m256d dRxy2   = _mm256_mul_pd(dRxy,dRxy);
			  const __m256d dRxz    = _mm256_sub_pd(x_2,rx_2);
			  const __m256d dRxz2   = _mm256_mul_pd(dRxz,dRxz);
			  const __m256d nrmdRx  = _mm256_sqrt_pd(_mm256_mul_pd(dRxx2,
			                                                       _mm256_mul_pd(dRxy2,dRxz2)));
			  const __m256d inv0    = _mm256_div_pd(_1,nrmdRx);						      
			  const __m256d nrmdRx3 = _mm256_mul_pd(nrmdRx,_mm256_mul_pd(nrmdRx3,nrmdRx3));
			  const __m256d inv1    = _mm256_div_pd(_1,nrmdRx3);
			  const __m256d dTxx    = _mm256_sub_pd(x_0,tx_0);
			  const __m256d dTxx2   = _mm256_mul_pd(dTxx,dTxx);
			  const __m256d dTxy    = _mm256_sub_pd(x_1,tx_1);
			  const __m256d dTxy2   = _mm256_mul_pd(dTxy,dTxy);
			  const __m256d dTxz    = _mm256_sub_pd(x_2,tx_2);
			  const __m256d dTxz2   = _mm256_mul_pd(dTxz,dTxz);
			  const __m256d nrmdTx  = _mm256_sqrt_pd(_mm256_mul_pd(dTxx2,
			                                                       _mm256_mul_pd(dTxy2,dTxz2)));
			  const __m256d inv3    = _mm256_div_pd(_1,nrmdTx);
			  const __m256d nrmdTx3 = _mm256_mul_pd(nrmdTx,_mm256_mul_pd(nrmdTx3,nrmdTx3));
			  const __m256d inv2    = _mm256_div_pd(_1,nrmdTx3);
			  _mm256_store_pd(&H_0[0],_mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxx2),inv1,inv0),
			                                        _mm256_fmadd_pd(dTxx2,inv2,inv3)));
			  _mm256_store_pd(&H_1[0],_mm256_sub_pd(_mm256_mul_pd(ymm4r8_negate(dRxx),
			                                        _mm256_mul_pd(dRxy,inv1)),
								_mm256_mul_pd(dTxx,
								_mm256_mul_pd(dTxy,inv2))));
			  _mm256_store_pd(&H_2[0],_mm256_sub_pd(_mm256_mul_pd(ymm4r8_negate(dRxx),
			                                        _mm256_mul_pd(dRxz,inv1)),
								_mm256_mul_pd(dTxx,
								_mm256_mul_pd(dTxz,inv2))));
			  _mm256_store_pd(&H_3[0],_mm256_load_pd(&H_1[0]));
			  _mm256_store_pd(&H_4[0],_mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxy2),inv1,inv0),
			                                        _mm256_fmadd_pd(dTxy2,inv2,inv3)));
			  _mm256_store_pd(&H_5[0],_mm256_sub_pd(_mm256_mul_pd(ymm4r8_negate(dRxy),
			                                        _mm256_mul_pd(dRxz,inv1)),
								_mm256_mul_pd(dTxy,
								_mm256_mul_pd(dTxz,inv2))));
			  _mm256_store_pd(&H_6[0],_mm256_load_pd(&H_2[0]));
			  _mm256_store_pd(&H_7[0],_mm256_load_pd(&H_5[0]));
			  _mm256_store_pd(&H_8[0],_mm256_sub_pd(_mm256_fmadd_pd(ymm4r8_negate(dRxz2),inv1,inv0),
			                                        _mm256_fmadd_pd(dTxz2,inv2,inv3)));
			  if(useHalfRange) {
			     _mm256_store_pd(&H_0[0],_mm256_mul_pd(_mm256_load_pd(&H_0[0],_0_5)));
			     _mm256_store_pd(&H_1[0],_mm256_mul_pd(_mm256_load_pd(&H_1[0],_0_5)));
			     _mm256_store_pd(&H_2[0],_mm256_mul_pd(_mm256_load_pd(&H_2[0],_0_5)));
			     _mm256_store_pd(&H_3[0],_mm256_mul_pd(_mm256_load_pd(&H_3[0],_0_5)));
			     _mm256_store_pd(&H_4[0],_mm256_mul_pd(_mm256_load_pd(&H_4[0],_0_5)));
			     _mm256_store_pd(&H_5[0],_mm256_mul_pd(_mm256_load_pd(&H_5[0],_0_5)));
			     _mm256_store_pd(&H_6[0],_mm256_mul_pd(_mm256_load_pd(&H_6[0],_0_5)));
			     _mm256_store_pd(&H_7[0],_mm256_mul_pd(_mm256_load_pd(&H_7[0],_0_5)));
			     _mm256_store_pd(&H_8[0],_mm256_mul_pd(_mm256_load_pd(&H_8[0],_0_5)));
			  }
		    }



		     
                    
		     
		      
		     
		      void gms::math::range_hess_3d_ymm8r4(__m256 &H_0,
		                                __m256 &H_1,
						__m256 &H_2,
						__m256 &H_3,
						__m256 &H_4,
						__m256 &H_5,
						__m256 &H_6,
						__m256 &H_7,
						__m256 &H_8,
						const __m256 x_0,
						const __m256 x_1,
						const __m256 x_2,
						const __m256 rx_0,
						const __m256 rx_1,
						const __m256 rx_2,
						const __m256 tx_0,
						const __m256 tx_1,
						const __m256 tx_2,
						const bool useHalfRange) {


			  const __m256 _1      = _mm256_set1_ps(1.0f);
			  const __m256 _0_5    = _mm256_set1_ps(0.5f);
			  const __m256 dRxx    = _mm256_sub_ps(x_0,rx_0);
			  const __m256 dRxx2   = _mm256_mul_ps(dRxx,dRxx);
			  const __m256 dRxy    = _mm256_sub_ps(x_1,rx_1);
			  const __m256 dRxy2   = _mm256_mul_ps(dRxy,dRxy);
			  const __m256 dRxz    = _mm256_sub_ps(x_2,rx_2);
			  const __m256 dRxz2   = _mm256_mul_ps(dRxz,dRxz);
			  const __m256 nrmdRx  = _mm256_sqrt_ps(_mm256_mul_ps(dRxx2,
			                                                       _mm256_mul_ps(dRxy2,dRxz2)));
			  const __m256 inv0    = _mm256_div_ps(_1,nrmdRx);						      
			  const __m256 nrmdRx3 = _mm256_mul_ps(nrmdRx,_mm256_mul_pd(nrmdRx3,nrmdRx3));
			  const __m256 inv1    = _mm256_div_ps(_1,nrmdRx3);
			  const __m256 dTxx    = _mm256_sub_ps(x_0,tx_0);
			  const __m256 dTxx2   = _mm256_mul_ps(dTxx,dTxx);
			  const __m256 dTxy    = _mm256_sub_ps(x_1,tx_1);
			  const __m256 dTxy2   = _mm256_mul_ps(dTxy,dTxy);
			  const __m256 dTxz    = _mm256_sub_ps(x_2,tx_2);
			  const __m256 dTxz2   = _mm256_mul_ps(dTxz,dTxz);
			  const __m256 nrmdTx  = _mm256_sqrt_ps(_mm256_mul_ps(dTxx2,
			                                                       _mm256_mul_ps(dTxy2,dTxz2)));
			  const __m256 inv3    = _mm256_div_ps(_1,nrmdTx);
			  const __m256 nrmdTx3 = _mm256_mul_ps(nrmdTx,_mm256_mul_ps(nrmdTx3,nrmdTx3));
			  const __m256 inv2    = _mm256_div_ps(_1,nrmdTx3);
			  H_0                   = _mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxx2),inv1,inv0),
			                                        _mm256_fmadd_ps(dTxx2,inv2,inv3));
			  H_1                   = _mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxx),
			                                        _mm256_mul_ps(dRxy,inv1)),
								_mm256_mul_ps(dTxx,
								_mm256_mul_ps(dTxy,inv2)));
			  H_2                   = _mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxx),
			                                        _mm256_mul_ps(dRxz,inv1)),
								_mm256_mul_ps(dTxx,
								_mm256_mul_ps(dTxz,inv2)));
			  H_3                   = H_1;
			  H_4                   = _mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxy2),inv1,inv0),
			                                        _mm256_fmadd_ps(dTxy2,inv2,inv3));
			  H_5                   = _mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxy),
			                                        _mm256_mul_ps(dRxz,inv1)),
								_mm256_mul_ps(dTxy,
								_mm256_mul_ps(dTxz,inv2)));
			  H_6                   = H_2;
			  H_7                   = H_5;
			  H_8                   = _mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxz2),inv1,inv0),
			                                        _mm256_fmadd_ps(dTxz2,inv2,inv3));
			  if(useHalfRange) {
                             H_0 = _mm256_mul_ps(H_0,_0_5);
			     H_1 = _mm256_mul_ps(H_1,_0_5);
			     H_2 = _mm256_mul_ps(H_2,_0_5);
			     H_3 = _mm256_mul_ps(H_3,_0_5);
			     H_4 = _mm256_mul_ps(H_4,_0_5);
			     H_5 = _mm256_mul_ps(H_5,_0_5);
			     H_6 = _mm256_mul_ps(H_6,_0_5);
			     H_7 = _mm256_mul_ps(H_7,_0_5);
			     H_8 = _mm256_mul_ps(H_8,_0_5);
			  }
		    }


		     
                    
		     
		      
		     
		      void gms::math::range_hess_3d_ymm8r4_a(float * __restrict __ATTR_ALIGN__(32) H_0,
		                                   float * __restrict __ATTR_ALIGN__(32) H_1,
						   float * __restrict __ATTR_ALIGN__(32) H_2,
						   float * __restrict __ATTR_ALIGN__(32) H_3,
						   float * __restrict __ATTR_ALIGN__(32) H_4,
						   float * __restrict __ATTR_ALIGN__(32) H_5,
						   float * __restrict __ATTR_ALIGN__(32) H_6,
						   float * __restrict __ATTR_ALIGN__(32) H_7,
						   float * __restrict __ATTR_ALIGN__(32) H_8,
						   const __m256 x_0,
						   const __m256 x_1,
						   const __m256 x_2,
						   const __m256 rx_0,
						   const __m256 rx_1,
						   const __m256 rx_2,
						   const __m256 tx_0,
						   const __m256 tx_1,
						   const __m256 tx_2,
						   const bool useHalfRange) {


			  const __m256 _1      = _mm256_set1_ps(1.0f);
			  const __m256 _0_5    = _mm256_set1_ps(0.5f);
			  const __m256 dRxx    = _mm256_sub_ps(x_0,rx_0);
			  const __m256 dRxx2   = _mm256_mul_ps(dRxx,dRxx);
			  const __m256 dRxy    = _mm256_sub_ps(x_1,rx_1);
			  const __m256 dRxy2   = _mm256_mul_ps(dRxy,dRxy);
			  const __m256 dRxz    = _mm256_sub_ps(x_2,rx_2);
			  const __m256 dRxz2   = _mm256_mul_ps(dRxz,dRxz);
			  const __m256 nrmdRx  = _mm256_sqrt_ps(_mm256_mul_ps(dRxx2,
			                                                       _mm256_mul_ps(dRxy2,dRxz2)));
			  const __m256 inv0    = _mm256_div_ps(_1,nrmdRx);						      
			  const __m256 nrmdRx3 = _mm256_mul_ps(nrmdRx,_mm256_mul_pd(nrmdRx3,nrmdRx3));
			  const __m256 inv1    = _mm256_div_ps(_1,nrmdRx3);
			  const __m256 dTxx    = _mm256_sub_ps(x_0,tx_0);
			  const __m256 dTxx2   = _mm256_mul_ps(dTxx,dTxx);
			  const __m256 dTxy    = _mm256_sub_ps(x_1,tx_1);
			  const __m256 dTxy2   = _mm256_mul_ps(dTxy,dTxy);
			  const __m256 dTxz    = _mm256_sub_ps(x_2,tx_2);
			  const __m256 dTxz2   = _mm256_mul_ps(dTxz,dTxz);
			  const __m256 nrmdTx  = _mm256_sqrt_ps(_mm256_mul_ps(dTxx2,
			                                                       _mm256_mul_ps(dTxy2,dTxz2)));
			  const __m256 inv3    = _mm256_div_ps(_1,nrmdTx);
			  const __m256 nrmdTx3 = _mm256_mul_ps(nrmdTx,_mm256_mul_ps(nrmdTx3,nrmdTx3));
			  const __m256 inv2    = _mm256_div_ps(_1,nrmdTx3);
			  _mm256_store_ps(&H_0[0],_mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxx2),inv1,inv0),
			                                        _mm256_fmadd_ps(dTxx2,inv2,inv3)));
			  _mm256_store_ps(&H_1[0],_mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxx),
			                                        _mm256_mul_ps(dRxy,inv1)),
								_mm256_mul_ps(dTxx,
								_mm256_mul_ps(dTxy,inv2))));
			  _mm256_store_ps(&H_2[0],_mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxx),
			                                        _mm256_mul_ps(dRxz,inv1)),
								_mm256_mul_ps(dTxx,
								_mm256_mul_ps(dTxz,inv2))));
			  _mm256_store_ps(&H_3[0],_mm256_load_ps(&H_1[0]));
			  _mm256_store_ps(&H_4[0],_mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxy2),inv1,inv0),
			                                        _mm256_fmadd_ps(dTxy2,inv2,inv3)));
			  _mm256_store_ps(&H_5[0],_mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxy),
			                                        _mm256_mul_ps(dRxz,inv1)),
								_mm256_mul_ps(dTxy,
								_mm256_mul_ps(dTxz,inv2))));
			  _mm256_store_ps(&H_6[0],_mm256_load_ps(&H_2[0]));
			  _mm256_store_ps(&H_7[0],_mm256_load_ps(&H_5[0]));
			  _mm256_store_ps(&H_8[0],_mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxz2),inv1,inv0),
			                                        _mm256_fmadd_ps(dTxz2,inv2,inv3)));
			  if(useHalfRange) {
                             _mm256_store_ps(&H_0[0],_mm256_mul_ps(_mm256_load_ps(&H_0[0],_0_5)));
			     _mm256_store_ps(&H_1[0],_mm256_mul_ps(_mm256_load_ps(&H_1[0],_0_5)));
			     _mm256_store_ps(&H_2[0],_mm256_mul_ps(_mm256_load_ps(&H_2[0],_0_5)));
			     _mm256_store_ps(&H_3[0],_mm256_mul_ps(_mm256_load_ps(&H_3[0],_0_5)));
			     _mm256_store_ps(&H_4[0],_mm256_mul_ps(_mm256_load_ps(&H_4[0],_0_5)));
			     _mm256_store_ps(&H_5[0],_mm256_mul_ps(_mm256_load_ps(&H_5[0],_0_5)));
			     _mm256_store_ps(&H_6[0],_mm256_mul_ps(_mm256_load_ps(&H_6[0],_0_5)));
			     _mm256_store_ps(&H_7[0],_mm256_mul_ps(_mm256_load_ps(&H_7[0],_0_5)));
			     _mm256_store_ps(&H_8[0],_mm256_mul_ps(_mm256_load_ps(&H_8[0],_0_5)));
			  }
		    }


		     
                    
		     
		      
		     
		      void gms::math::range_hess_3d_ymm8r4_u(float * __restrict H_0,
		                                   float * __restrict H_1,
						   float * __restrict H_2,
						   float * __restrict H_3,
						   float * __restrict H_4,
						   float * __restrict H_5,
						   float * __restrict H_6,
						   float * __restrict H_7,
						   float * __restrict H_8,
						   const __m256 x_0,
						   const __m256 x_1,
						   const __m256 x_2,
						   const __m256 rx_0,
						   const __m256 rx_1,
						   const __m256 rx_2,
						   const __m256 tx_0,
						   const __m256 tx_1,
						   const __m256 tx_2,
						   const bool useHalfRange) {


			  const __m256 _1      = _mm256_set1_ps(1.0f);
			  const __m256 _0_5    = _mm256_set1_ps(0.5f);
			  const __m256 dRxx    = _mm256_sub_ps(x_0,rx_0);
			  const __m256 dRxx2   = _mm256_mul_ps(dRxx,dRxx);
			  const __m256 dRxy    = _mm256_sub_ps(x_1,rx_1);
			  const __m256 dRxy2   = _mm256_mul_ps(dRxy,dRxy);
			  const __m256 dRxz    = _mm256_sub_ps(x_2,rx_2);
			  const __m256 dRxz2   = _mm256_mul_ps(dRxz,dRxz);
			  const __m256 nrmdRx  = _mm256_sqrt_ps(_mm256_mul_ps(dRxx2,
			                                                       _mm256_mul_ps(dRxy2,dRxz2)));
			  const __m256 inv0    = _mm256_div_ps(_1,nrmdRx);						      
			  const __m256 nrmdRx3 = _mm256_mul_ps(nrmdRx,_mm256_mul_pd(nrmdRx3,nrmdRx3));
			  const __m256 inv1    = _mm256_div_ps(_1,nrmdRx3);
			  const __m256 dTxx    = _mm256_sub_ps(x_0,tx_0);
			  const __m256 dTxx2   = _mm256_mul_ps(dTxx,dTxx);
			  const __m256 dTxy    = _mm256_sub_ps(x_1,tx_1);
			  const __m256 dTxy2   = _mm256_mul_ps(dTxy,dTxy);
			  const __m256 dTxz    = _mm256_sub_ps(x_2,tx_2);
			  const __m256 dTxz2   = _mm256_mul_ps(dTxz,dTxz);
			  const __m256 nrmdTx  = _mm256_sqrt_ps(_mm256_mul_ps(dTxx2,
			                                                       _mm256_mul_ps(dTxy2,dTxz2)));
			  const __m256 inv3    = _mm256_div_ps(_1,nrmdTx);
			  const __m256 nrmdTx3 = _mm256_mul_ps(nrmdTx,_mm256_mul_ps(nrmdTx3,nrmdTx3));
			  const __m256 inv2    = _mm256_div_ps(_1,nrmdTx3);
			  _mm256_storeu_ps(&H_0[0],_mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxx2),inv1,inv0),
			                                        _mm256_fmadd_ps(dTxx2,inv2,inv3)));
			  _mm256_storeu_ps(&H_1[0],_mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxx),
			                                        _mm256_mul_ps(dRxy,inv1)),
								_mm256_mul_ps(dTxx,
								_mm256_mul_ps(dTxy,inv2))));
			  _mm256_storeu_ps(&H_2[0],_mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxx),
			                                        _mm256_mul_ps(dRxz,inv1)),
								_mm256_mul_ps(dTxx,
								_mm256_mul_ps(dTxz,inv2))));
			  _mm256_storeu_ps(&H_3[0],_mm256_loadu_ps(&H_1[0]));
			  _mm256_storeu_ps(&H_4[0],_mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxy2),inv1,inv0),
			                                        _mm256_fmadd_ps(dTxy2,inv2,inv3)));
			  _mm256_storeu_ps(&H_5[0],_mm256_sub_ps(_mm256_mul_ps(ymm8r4_negate(dRxy),
			                                        _mm256_mul_ps(dRxz,inv1)),
								_mm256_mul_ps(dTxy,
								_mm256_mul_ps(dTxz,inv2))));
			  _mm256_storeu_ps(&H_6[0],_mm256_loadu_ps(&H_2[0]));
			  _mm256_storeu_ps(&H_7[0],_mm256_loadu_ps(&H_5[0]));
			  _mm256_storeu_ps(&H_8[0],_mm256_sub_ps(_mm256_fmadd_ps(ymm8r4_negate(dRxz2),inv1,inv0),
			                                        _mm256_fmadd_ps(dTxz2,inv2,inv3)));
			  if(useHalfRange) {
                             _mm256_storeu_ps(&H_0[0],_mm256_mul_ps(_mm256_loadu_ps(&H_0[0],_0_5)));
			     _mm256_storeu_ps(&H_1[0],_mm256_mul_ps(_mm256_loadu_ps(&H_1[0],_0_5)));
			     _mm256_storeu_ps(&H_2[0],_mm256_mul_ps(_mm256_loadu_ps(&H_2[0],_0_5)));
			     _mm256_storeu_ps(&H_3[0],_mm256_mul_ps(_mm256_loadu_ps(&H_3[0],_0_5)));
			     _mm256_storeu_ps(&H_4[0],_mm256_mul_ps(_mm256_loadu_ps(&H_4[0],_0_5)));
			     _mm256_storeu_ps(&H_5[0],_mm256_mul_ps(_mm256_loadu_ps(&H_5[0],_0_5)));
			     _mm256_storeu_ps(&H_6[0],_mm256_mul_ps(_mm256_loadu_ps(&H_6[0],_0_5)));
			     _mm256_storeu_ps(&H_7[0],_mm256_mul_ps(_mm256_loadu_ps(&H_7[0],_0_5)));
			     _mm256_storeu_ps(&H_8[0],_mm256_mul_ps(_mm256_loadu_ps(&H_8[0],_0_5)));
			  }
		    }



 

 
/*CART2RUVGENCPP A C++ function to convert a Cartesian point into range,
 *           and direction cosines, possibly including the w component.
 *
 *INPUTS: retData A pointer to an array of doubles with 3 elements to
 *                hold the result in [r;u;v] order or with 4 elements if
 *                includeW is true to hold [r;u;v;w].
 *             zC The 3X1 Cartesian points [x;y;z] to be converted.
 *   useHalfRange A boolean value specifying whether the bistatic (round-
 *                trip) range value has been divided by two. 
 *            zTx The 3X1 [x;y;z] location vector of the transmitter in
 *                global Cartesian coordinates.
 *            zRx The 3X1 [x;y;z] location vector of the receiver in global
 *                Cartesian coordinates.
 *             M  A 3X3 rotation matrices to go from the alignment of the
 *                global coordinate system to that at the receiver. It is
 *                stored one columns after the other, consistent with how
 *                Matlab indexes matrices.
 *       includeW A boolean value indicating whether retData has space for
 *                a fourth component and the fourth component should be
 *                included.
 *
 *OUTPUTS: None. The results are placed in retData.
 *
 *See the comments to the Matlab function Cart2ruv for more information
 *on how this function works.
 *
 *April 2017 David F. Crouse, Naval Research Laboratory, Washington D.C.
 *@@Modified by Bernard Gingold, on May 2022
 **/

	 	    
	             
                    
		     
		      
		     
		      void gms::math::cart_to_ruv_ymm4r8(__m256d &r,
		                              __m256d &u,
					      __m256d &v,
					      __m256d &w,
					      const __m256d C_x,
					      const __m256d C_y,
					      const __m256d C_z,
					      const __m256d T_x,
					      const __m256d T_y,
					      const __m256d T_z,
					      const __m256d R_x,
					      const __m256d R_y,
					      const __m256d R_z,
					      const __m256d * __restrict __ATTR_ALIGN__(32) M, //flattened 3x3 matrix
					      const bool useHalfRange) {

                          __m256d CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256d r1,r2;
			  __m256d diff0,diff1,diff2,diff3,diff4,diff5;
			  const __m256d M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_pd(C_x,R_x);
			  const __m256d M1 = M[1];
			  diff1 = _mm256_sub_pd(C_y,R_y);
			  const __m256d M2 = M[2];
			  diff2 = _mm256_sub_pd(C_z,R_z);
			  const __m256d M3 = M[3];
			  diff3 = _mm256_sub_pd(T_x,R_x);
			  const __m256d M4 = M[4];
			  diff4 = _mm256_sub_pd(T_y,R_y);
			  const __m256d M5 = M[5];
			  diff5 = _mm256_sub_pd(T_z,R_z);
			  const __m256d M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_pd(M0,diff3,_mm256_fmadd_pd(M3,diff4,_mm256_mul_pd(M6,diff5)));
			  CL0   = _mm256_fmadd_pd(M0,diff0,_mm256_fmadd_pd(M3,diff1,_mm256_mul_pd(M6,diff2)));
			  const __m256d M7 = M[7];
			  CL1   = _mm256_fmadd_pd(M1,diff0,_mm256_fmadd_pd(M4,diff1,_mm256_mul_pd(M7,diff2)));
			  TxL1  = _mm256_fmadd_pd(M1,diff3,_mm256_fmadd_pd(M4,diff4,_mm256_mul_pd(M7,diff5)));
			  const __m256d M8 = M[8];
			  CL2   = _mm256_fmadd_pd(M2,diff0,_mm256_fmadd_pd(M5,diff1,_mm256_mul_pd(M8,diff2)));
			  TxL2  = _mm256_fmadd_pd(M2,diff3,_mm256_fmadd_pd(M5,diff4,_mm256_mul_pd(M8,diff5)));
			  ///Receiver to target.
			  __m256d sarg = _mm256_fmadd_pd(CL0,CL0,_mm256_fmadd_pd(CL1,CL1,_mm256_mul_pd(CL2,CL2)));
			  r1    = _mm256_sqrt_pd(sarg);
			  diff0 = _mm256_sub_pd(CL0,TxL0);
			  diff1 = _mm256_sub_pd(CL1,TxL1);
			  u     = _mm256_div_pd(CL0,r1);
			  diff2 = _mm256_sub_pd(CL2,TxL2);
			  w     = _mm256_div_pd(CL2,r1);
			  //Target to transmitter
			  sarg  = _mm256_fmadd_pd(diff0,diff0,_mm256_fmadd_pd(diff1,diff1,_mm256_mul_pd(diff2,diff2)));
			  r2    = _mm256_sqrt_pd(sarg);
			  r     = _mm256_add_pd(r1,r2);
			  v     = _mm256_div_pd(CL1,r1);
			  if(useHalfRange) {
                             const __m256d _0_5 = _mm256_set1_pd(0.5);
			     r  = _mm256_mul_pd(r,_0_5);
			  }
		     }


		     
                    
		     
		      
		     
		      void gms::math::cart_to_ruv_ymm4r8_a(double * __restrict __ATTR_ALIGN__(32) r,
		                                double * __restrict __ATTR_ALIGN__(32) u,
					        double * __restrict __ATTR_ALIGN__(32) v,
					        double * __restrict __ATTR_ALIGN__(32) w,
					      const __m256d C_x,
					      const __m256d C_y,
					      const __m256d C_z,
					      const __m256d T_x,
					      const __m256d T_y,
					      const __m256d T_z,
					      const __m256d R_x,
					      const __m256d R_y,
					      const __m256d R_z,
					      const __m256d * __restrict __ATTR_ALIGN__(32) M, //flattened 3x3 matrix
					      const bool useHalfRange) {

                          __m256d CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256d r1,r2;
			  __m256d diff0,diff1,diff2,diff3,diff4,diff5;
			  const __m256d M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_pd(C_x,R_x);
			  const __m256d M1 = M[1];
			  diff1 = _mm256_sub_pd(C_y,R_y);
			  const __m256d M2 = M[2];
			  diff2 = _mm256_sub_pd(C_z,R_z);
			  const __m256d M3 = M[3];
			  diff3 = _mm256_sub_pd(T_x,R_x);
			  const __m256d M4 = M[4];
			  diff4 = _mm256_sub_pd(T_y,R_y);
			  const __m256d M5 = M[5];
			  diff5 = _mm256_sub_pd(T_z,R_z);
			  const __m256d M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_pd(M0,diff3,_mm256_fmadd_pd(M3,diff4,_mm256_mul_pd(M6,diff5)));
			  CL0   = _mm256_fmadd_pd(M0,diff0,_mm256_fmadd_pd(M3,diff1,_mm256_mul_pd(M6,diff2)));
			  const __m256d M7 = M[7];
			  CL1   = _mm256_fmadd_pd(M1,diff0,_mm256_fmadd_pd(M4,diff1,_mm256_mul_pd(M7,diff2)));
			  TxL1  = _mm256_fmadd_pd(M1,diff3,_mm256_fmadd_pd(M4,diff4,_mm256_mul_pd(M7,diff5)));
			  const __m256d M8 = M[8];
			  CL2   = _mm256_fmadd_pd(M2,diff0,_mm256_fmadd_pd(M5,diff1,_mm256_mul_pd(M8,diff2)));
			  TxL2  = _mm256_fmadd_pd(M2,diff3,_mm256_fmadd_pd(M5,diff4,_mm256_mul_pd(M8,diff5)));
			  ///Receiver to target.
			  __m256d sarg = _mm256_fmadd_pd(CL0,CL0,_mm256_fmadd_pd(CL1,CL1,_mm256_mul_pd(CL2,CL2)));
			  r1    = _mm256_sqrt_pd(sarg);
			  diff0 = _mm256_sub_pd(CL0,TxL0);
			  diff1 = _mm256_sub_pd(CL1,TxL1);
			  _mm256_store_pd(&u[0],_mm256_div_pd(CL0,r1));
			  diff2 = _mm256_sub_pd(CL2,TxL2);
			  _mm256_store_pd(&w[0],_mm256_div_pd(CL2,r1));
			  //Target to transmitter
			  sarg  = _mm256_fmadd_pd(diff0,diff0,_mm256_fmadd_pd(diff1,diff1,_mm256_mul_pd(diff2,diff2)));
			  r2    = _mm256_sqrt_pd(sarg);
			  _mm256_store_pd(&r[0],_mm256_add_pd(r1,r2));
			  _mm256_store_pd(&v[0],_mm256_div_pd(CL1,r1));
			  if(useHalfRange) {
                             const __m256d _0_5 = _mm256_set1_pd(0.5);
			     _mm256_store_pd(&r[0],_mm256_mul_pd(_mm256_load_pd(&r[0],_0_5)));
			  }
		     }


		     
                    
		     
		      
		     
		      void gms::math::cart_to_ruv_ymm4r8_u(double * __restrict r,
		                                double * __restrict u,
					        double * __restrict v,
					        double * __restrict w,
					      const __m256d C_x,
					      const __m256d C_y,
					      const __m256d C_z,
					      const __m256d T_x,
					      const __m256d T_y,
					      const __m256d T_z,
					      const __m256d R_x,
					      const __m256d R_y,
					      const __m256d R_z,
					      const __m256d * __restrict __ATTR_ALIGN__(32) M, //flattened 3x3 matrix
					      const bool useHalfRange) {

                          __m256d CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256d r1,r2;
			  __m256d diff0,diff1,diff2,diff3,diff4,diff5;
			  const __m256d M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_pd(C_x,R_x);
			  const __m256d M1 = M[1];
			  diff1 = _mm256_sub_pd(C_y,R_y);
			  const __m256d M2 = M[2];
			  diff2 = _mm256_sub_pd(C_z,R_z);
			  const __m256d M3 = M[3];
			  diff3 = _mm256_sub_pd(T_x,R_x);
			  const __m256d M4 = M[4];
			  diff4 = _mm256_sub_pd(T_y,R_y);
			  const __m256d M5 = M[5];
			  diff5 = _mm256_sub_pd(T_z,R_z);
			  const __m256d M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_pd(M0,diff3,_mm256_fmadd_pd(M3,diff4,_mm256_mul_pd(M6,diff5)));
			  CL0   = _mm256_fmadd_pd(M0,diff0,_mm256_fmadd_pd(M3,diff1,_mm256_mul_pd(M6,diff2)));
			  const __m256d M7 = M[7];
			  CL1   = _mm256_fmadd_pd(M1,diff0,_mm256_fmadd_pd(M4,diff1,_mm256_mul_pd(M7,diff2)));
			  TxL1  = _mm256_fmadd_pd(M1,diff3,_mm256_fmadd_pd(M4,diff4,_mm256_mul_pd(M7,diff5)));
			  const __m256d M8 = M[8];
			  CL2   = _mm256_fmadd_pd(M2,diff0,_mm256_fmadd_pd(M5,diff1,_mm256_mul_pd(M8,diff2)));
			  TxL2  = _mm256_fmadd_pd(M2,diff3,_mm256_fmadd_pd(M5,diff4,_mm256_mul_pd(M8,diff5)));
			  ///Receiver to target.
			  __m256d sarg = _mm256_fmadd_pd(CL0,CL0,_mm256_fmadd_pd(CL1,CL1,_mm256_mul_pd(CL2,CL2)));
			  r1    = _mm256_sqrt_pd(sarg);
			  diff0 = _mm256_sub_pd(CL0,TxL0);
			  diff1 = _mm256_sub_pd(CL1,TxL1);
			  _mm256_storeu_pd(&u[0],_mm256_div_pd(CL0,r1));
			  diff2 = _mm256_sub_pd(CL2,TxL2);
			  _mm256_storeu_pd(&w[0],_mm256_div_pd(CL2,r1));
			  //Target to transmitter
			  sarg  = _mm256_fmadd_pd(diff0,diff0,_mm256_fmadd_pd(diff1,diff1,_mm256_mul_pd(diff2,diff2)));
			  r2    = _mm256_sqrt_pd(sarg);
			  _mm256_storeu_pd(&r[0],_mm256_add_pd(r1,r2));
			  _mm256_storeu_pd(&v[0],_mm256_div_pd(CL1,r1));
			  if(useHalfRange) {
                             const __m256d _0_5 = _mm256_set1_pd(0.5);
			     _mm256_storeu_pd(&r[0],_mm256_mul_pd(_mm256_loadu_pd(&r[0],_0_5)));
			  }
		     }





		     
                    
		     
		      
		     
		      void gms::math::cart_to_ruv_ymm8r4(__m256 &r,
		                               __m256 &u,
					       __m256 &v,
					       __m256 &w,
					      const __m256 C_x,
					      const __m256 C_y,
					      const __m256 C_z,
					      const __m256 T_x,
					      const __m256 T_y,
					      const __m256 T_z,
					      const __m256 R_x,
					      const __m256 R_y,
					      const __m256 R_z,
					      const __m256 * __restrict __ATTR_ALIGN__(32) M, //flattened 3x3 matrix
					      const bool useHalfRange) {

                          __m256 CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256 r1,r2;
			  __m256 diff0,diff1,diff2,diff3,diff4,diff5;
			  const __m256 M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_ps(C_x,R_x);
			  const __m256 M1 = M[1];
			  diff1 = _mm256_sub_ps(C_y,R_y);
			  const __m256 M2 = M[2];
			  diff2 = _mm256_sub_ps(C_z,R_z);
			  const __m256 M3 = M[3];
			  diff3 = _mm256_sub_ps(T_x,R_x);
			  const __m256 M4 = M[4];
			  diff4 = _mm256_sub_ps(T_y,R_y);
			  const __m256 M5 = M[5];
			  diff5 = _mm256_sub_ps(T_z,R_z);
			  const __m256 M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_ps(M0,diff3,_mm256_fmadd_ps(M3,diff4,_mm256_mul_ps(M6,diff5)));
			  CL0   = _mm256_fmadd_ps(M0,diff0,_mm256_fmadd_ps(M3,diff1,_mm256_mul_ps(M6,diff2)));
			  const __m256 M7 = M[7];
			  CL1   = _mm256_fmadd_ps(M1,diff0,_mm256_fmadd_ps(M4,diff1,_mm256_mul_ps(M7,diff2)));
			  TxL1  = _mm256_fmadd_ps(M1,diff3,_mm256_fmadd_ps(M4,diff4,_mm256_mul_ps(M7,diff5)));
			  const __m256 M8 = M[8];
			  CL2   = _mm256_fmadd_ps(M2,diff0,_mm256_fmadd_ps(M5,diff1,_mm256_mul_ps(M8,diff2)));
			  TxL2  = _mm256_fmadd_ps(M2,diff3,_mm256_fmadd_ps(M5,diff4,_mm256_mul_ps(M8,diff5)));
			  ///Receiver to target.
			  __m256 sarg = _mm256_fmadd_ps(CL0,CL0,_mm256_fmadd_ps(CL1,CL1,_mm256_mul_ps(CL2,CL2)));
			  r1    = _mm256_sqrt_ps(sarg);
			  diff0 = _mm256_sub_ps(CL0,TxL0);
			  diff1 = _mm256_sub_ps(CL1,TxL1);
			  u     = _mm256_div_ps(CL0,r1);
			  diff2 = _mm256_sub_ps(CL2,TxL2);
			  w     = _mm256_div_ps(CL2,r1);
			  //Target to transmitter
			  sarg  = _mm256_fmadd_ps(diff0,diff0,_mm256_fmadd_ps(diff1,diff1,_mm256_mul_ps(diff2,diff2)));
			  r2    = _mm256_sqrt_ps(sarg);
			  r     = _mm256_add_ps(r1,r2);
			  v     = _mm256_div_ps(CL1,r1);
			  if(useHalfRange) {
                             const __m256 _0_5 = _mm256_set1_ps(0.5f);
			     r  = _mm256_mul_ps(r,_0_5);
			  }
		     }


		     
                    
		     
		      
		     
		      void gms::math::cart_to_ruv_ymm8r4_a(float * __restrict __ATTR_ALIGN__(32) r,
		                                 float * __restrict __ATTR_ALIGN__(32) u,
					         float * __restrict __ATTR_ALIGN__(32) v,
					         float * __restrict __ATTR_ALIGN__(32) w,
					         const __m256 C_x,
					         const __m256 C_y,
					         const __m256 C_z,
					         const __m256 T_x,
					         const __m256 T_y,
					         const __m256 T_z,
					         const __m256 R_x,
					         const __m256 R_y,
					         const __m256 R_z,
					         const __m256 * __restrict __ATTR_ALIGN__(32) M, //flattened 3x3 matrix
					         const bool useHalfRange) {

                          __m256 CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256 r1,r2;
			  __m256 diff0,diff1,diff2,diff3,diff4,diff5;
			  const __m256 M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_ps(C_x,R_x);
			  const __m256 M1 = M[1];
			  diff1 = _mm256_sub_ps(C_y,R_y);
			  const __m256 M2 = M[2];
			  diff2 = _mm256_sub_ps(C_z,R_z);
			  const __m256 M3 = M[3];
			  diff3 = _mm256_sub_ps(T_x,R_x);
			  const __m256 M4 = M[4];
			  diff4 = _mm256_sub_ps(T_y,R_y);
			  const __m256 M5 = M[5];
			  diff5 = _mm256_sub_ps(T_z,R_z);
			  const __m256 M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_ps(M0,diff3,_mm256_fmadd_ps(M3,diff4,_mm256_mul_ps(M6,diff5)));
			  CL0   = _mm256_fmadd_ps(M0,diff0,_mm256_fmadd_ps(M3,diff1,_mm256_mul_ps(M6,diff2)));
			  const __m256 M7 = M[7];
			  CL1   = _mm256_fmadd_ps(M1,diff0,_mm256_fmadd_ps(M4,diff1,_mm256_mul_ps(M7,diff2)));
			  TxL1  = _mm256_fmadd_ps(M1,diff3,_mm256_fmadd_ps(M4,diff4,_mm256_mul_ps(M7,diff5)));
			  const __m256 M8 = M[8];
			  CL2   = _mm256_fmadd_ps(M2,diff0,_mm256_fmadd_ps(M5,diff1,_mm256_mul_ps(M8,diff2)));
			  TxL2  = _mm256_fmadd_ps(M2,diff3,_mm256_fmadd_ps(M5,diff4,_mm256_mul_ps(M8,diff5)));
			  ///Receiver to target.
			  __m256 sarg = _mm256_fmadd_ps(CL0,CL0,_mm256_fmadd_ps(CL1,CL1,_mm256_mul_ps(CL2,CL2)));
			  r1    = _mm256_sqrt_ps(sarg);
			  diff0 = _mm256_sub_ps(CL0,TxL0);
			  diff1 = _mm256_sub_ps(CL1,TxL1);
			  _mm256_store_ps(&u[0],_mm256_div_ps(CL0,r1));
			  diff2 = _mm256_sub_ps(CL2,TxL2);
			  _mm256_store_ps(&w[0],_mm256_div_ps(CL2,r1));
			  //Target to transmitter
			  sarg  = _mm256_fmadd_ps(diff0,diff0,_mm256_fmadd_ps(diff1,diff1,_mm256_mul_ps(diff2,diff2)));
			  r2    = _mm256_sqrt_ps(sarg);
			  _mm256_store_ps(&r[0],_mm256_add_ps(r1,r2));
			  _mm256_store_ps(&v[0],_mm256_div_ps(CL1,r1));
			  if(useHalfRange) {
                             const __m256 _0_5 = _mm256_set1_ps(0.5f);
			     _mm256_store_ps(&r[0],_mm256_mul_ps(_mm256_load_ps(&r[0],_0_5)));
			  }
		     }


		      
                    
		     
		      
		     
		      void gms::math::cart_to_ruv_ymm8r4_u(float * __restrict r,
		                                 float * __restrict u,
					         float * __restrict v,
					         float * __restrict w,
					         const __m256 C_x,
					         const __m256 C_y,
					         const __m256 C_z,
					         const __m256 T_x,
					         const __m256 T_y,
					         const __m256 T_z,
					         const __m256 R_x,
					         const __m256 R_y,
					         const __m256 R_z,
					         const __m256 * __restrict __ATTR_ALIGN__(32) M, //flattened 3x3 matrix
					         const bool useHalfRange) {

                          __m256 CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256 r1,r2;
			  __m256 diff0,diff1,diff2,diff3,diff4,diff5;
			  const __m256 M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_ps(C_x,R_x);
			  const __m256 M1 = M[1];
			  diff1 = _mm256_sub_ps(C_y,R_y);
			  const __m256 M2 = M[2];
			  diff2 = _mm256_sub_ps(C_z,R_z);
			  const __m256 M3 = M[3];
			  diff3 = _mm256_sub_ps(T_x,R_x);
			  const __m256 M4 = M[4];
			  diff4 = _mm256_sub_ps(T_y,R_y);
			  const __m256 M5 = M[5];
			  diff5 = _mm256_sub_ps(T_z,R_z);
			  const __m256 M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_ps(M0,diff3,_mm256_fmadd_ps(M3,diff4,_mm256_mul_ps(M6,diff5)));
			  CL0   = _mm256_fmadd_ps(M0,diff0,_mm256_fmadd_ps(M3,diff1,_mm256_mul_ps(M6,diff2)));
			  const __m256 M7 = M[7];
			  CL1   = _mm256_fmadd_ps(M1,diff0,_mm256_fmadd_ps(M4,diff1,_mm256_mul_ps(M7,diff2)));
			  TxL1  = _mm256_fmadd_ps(M1,diff3,_mm256_fmadd_ps(M4,diff4,_mm256_mul_ps(M7,diff5)));
			  const __m256 M8 = M[8];
			  CL2   = _mm256_fmadd_ps(M2,diff0,_mm256_fmadd_ps(M5,diff1,_mm256_mul_ps(M8,diff2)));
			  TxL2  = _mm256_fmadd_ps(M2,diff3,_mm256_fmadd_ps(M5,diff4,_mm256_mul_ps(M8,diff5)));
			  ///Receiver to target.
			  __m256 sarg = _mm256_fmadd_ps(CL0,CL0,_mm256_fmadd_ps(CL1,CL1,_mm256_mul_ps(CL2,CL2)));
			  r1    = _mm256_sqrt_ps(sarg);
			  diff0 = _mm256_sub_ps(CL0,TxL0);
			  diff1 = _mm256_sub_ps(CL1,TxL1);
			  _mm256_storeu_ps(&u[0],_mm256_div_ps(CL0,r1));
			  diff2 = _mm256_sub_ps(CL2,TxL2);
			  _mm256_storeu_ps(&w[0],_mm256_div_ps(CL2,r1));
			  //Target to transmitter
			  sarg  = _mm256_fmadd_ps(diff0,diff0,_mm256_fmadd_ps(diff1,diff1,_mm256_mul_ps(diff2,diff2)));
			  r2    = _mm256_sqrt_ps(sarg);
			  _mm256_storeu_ps(&r[0],_mm256_add_ps(r1,r2));
			  _mm256_storeu_ps(&v[0],_mm256_div_ps(CL1,r1));
			  if(useHalfRange) {
                             const __m256 _0_5 = _mm256_set1_ps(0.5f);
			     _mm256_storeu_ps(&r[0],_mm256_mul_ps(_mm256_loadu_ps(&r[0],_0_5)));
			  }
		     }



		     
/*CART2SPHEREGENCPP A C++ function to convert Cartesian points to bistatic
 *            range, azimuth and elevation.
 *
 *INPUTS: retData A pointer to an array of doubles with 3 elements to
 *                hold the result in [range;azimuth;elevation]. order.
 *     cartPoints A pointer to the 3X1 Cartesian points [x;y;z] to be
 *                converted.
 *     systemType An integer specifying the axis from which the angles are
 *                measured. Possible values are
 *                0 Azimuth is measured counterclockwise from the x-axis in
 *                  the x-y plane. Elevation is measured up from the x-y
 *                  plane (towards the z-axis). This is consistent with
 *                  common spherical coordinate systems for specifying
 *                  longitude (azimuth) and geocentric latitude
 *                  (elevation).
 *                1 Azimuth is measured counterclockwise from the z-axis in
 *                  the z-x plane. Elevation is measured up from the z-x
 *                  plane (towards the y-axis). This is consistent with
 *                  some spherical coordinate systems that use the z-axis
 *                  as the boresight direction of the radar.
 *                2 This is the same as 0 except instead of being given
 *                  elevation, one desires the angle away from the z-axis,
 *                  which is (pi/2-elevation).
 *                3 This is the same as 0 except azimuth is measured
 *                  clockwise from the y-axis in the x-y plane instead of
 *                  counterclockwise from the x-axis. This coordinate
 *                  system often arises when given "bearings" in a local
 *                  East-North-Up coordinate system, where the bearing
 *                  directions are measured East of North.
 *   useHalfRange A boolean value specifying whether the bistatic (round-
 *                trip) range value has been divided by two. 
 *            zTx The 3X1 [x;y;z] location vector of the transmitter in
 *                global Cartesian coordinates.
 *            zRx The 3X1 [x;y;z] location vector of the receiver in global
 *                Cartesian coordinates.
 *             M  A 3X3  rotation matrices to go from the alignment of the
 *                global coordinate system to that at the receiver. It is
 *                stored one columns after the other, consistent with how
 *                Matlab indexes matrices.
 *
 *OUTPUTS: None. The results are placed in retData.
 *
 *See the comments to the Matlab function Cart2Sphere for more information
 *on how this function works.
 *
 *April 2017 David F. Crouse, Naval Research Laboratory, Washington D.C.
 *@@Modified by Bernard Gingold, on May 2022
 **/

	             
                    
		     
		      
		     
		      void gms::math::cart_to_sphere_ymm4r8(__m256d &range,
		                                 __m256d &az,
						 __m256d &elev,
						 const __m256d C_x,
						 const __m256d C_y,
						 const __m256d C_z,
						 const __m256d T_x,
						 const __m256d T_y,
						 const __m256d T_z,
						 const __m256d R_x,
						 const __m256d R_y,
						 const __m256d R_z,
						 const __m256d * __restrict __ATTR_ALIGN__(32) M,
						 const int sysType,
						 const bool useHalfRange) {

			  const __m256d _0   = _mm256_setzero_pd();
			  const __m256d _0_5 = _mm256_set1_pd(0.5);
                          __m256d CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256d diff0,diff1,diff2,diff3,diff4,diff5;
			  __m256d r1,r2;
			  const __m256d M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_pd(C_x,R_x);
			  const __m256d M1 = M[1];
			  diff1 = _mm256_sub_pd(C_y,R_y);
			  const __m256d M2 = M[2];
			  diff2 = _mm256_sub_pd(C_z,R_z);
			  const __m256d M3 = M[3];
			  diff3 = _mm256_sub_pd(T_x,R_x);
			  const __m256d M4 = M[4];
			  diff4 = _mm256_sub_pd(T_y,R_y);
			  const __m256d M5 = M[5];
			  diff5 = _mm256_sub_pd(T_z,R_z);
			  const __m256d M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_pd(M0,diff3,_mm256_fmadd_pd(M3,diff4,_mm256_mul_pd(M6,diff5)));
			  CL0   = _mm256_fmadd_pd(M0,diff0,_mm256_fmadd_pd(M3,diff1,_mm256_mul_pd(M6,diff2)));
			  const __m256d M7 = M[7];
			  CL1   = _mm256_fmadd_pd(M1,diff0,_mm256_fmadd_pd(M4,diff1,_mm256_mul_pd(M7,diff2)));
			  TxL1  = _mm256_fmadd_pd(M1,diff3,_mm256_fmadd_pd(M4,diff4,_mm256_mul_pd(M7,diff5)));
			  const __m256d M8 = M[8];
			  CL2   = _mm256_fmadd_pd(M2,diff0,_mm256_fmadd_pd(M5,diff1,_mm256_mul_pd(M8,diff2)));
			  TxL2  = _mm256_fmadd_pd(M2,diff3,_mm256_fmadd_pd(M5,diff4,_mm256_mul_pd(M8,diff5)));
			  ///Receiver to target.
			  __m256d sarg = _mm256_fmadd_pd(CL0,CL0,_mm256_fmadd_pd(CL1,CL1,_mm256_mul_pd(CL2,CL2)));
			  r1    = _mm256_sqrt_pd(sarg);
			  diff0 = _mm256_sub_pd(CL0,TxL0);
			  diff1 = _mm256_sub_pd(CL1,TxL1);
			  diff2 = _mm256_sub_pd(CL2,TxL2);
			  //Target to transmitter
			  sarg  = _mm256_fmadd_pd(diff0,diff0,_mm256_fmadd_pd(diff1,diff1,_mm256_mul_pd(diff2,diff2)));
			  r2    = _mm256_sqrt_pd(sarg);
			  range = _mm256_add_pd(r1,r2);
			  if(sysType==0||sysType==2||sysType==3) {
                             __mmask8 m1,m2;
			     m1 = _mm256_cmp_pd_mask(CL1,_0,_CMP_EQ_OQ);
			     m2 = _mm256_cmp_pd_mask(CL0,_0,_CMP_EQ_OQ);
			     if(m1 && m2) {
                                az = _0;
			     }
			     else {
                                az = _mm256_atan2_pd(CL1,CL0);
			     }
			     elev = _mm256_atan2_pd(CL2,_mm256_hypot_pd(CL0,CL1));
			     if(sysType==2) {
                                const __m256d pi2 = _mm256_set1_pd(1.5707963267948966192313);
				elev              = _mm256_sub_pd(pi2,elev);
			     }
			     else if(sysType==3) {
                                const __m256d pi2 = _mm256_set1_pd(1.5707963267948966192313);
				az                = _mm256_sub_pd(pi2,az);
			     }
			  }
			  else {
                              __mmask8 m1,m2;
			      m1 = _mm256_cmp_pd_mask(CL2,_0,_CMP_EQ_OQ);
			      m2 = _mm256_cmp_pd_mask(CL0,_0,_CMP_EQ_OQ);
			      if(m1 && m2) {
                                 az = _0;
			      }
			      else {
                                 az = _mm256_atan2_pd(CL0,CL2);
			      }
			      elev = _mm256_atan2_pd(CL1,_mm256_hypot_pd(CL2,CL0));
			  }

			  if(useHalfRange) {
                             range = _mm256_mul_pd(range,_0_5);
			  }
		     }


		     
                    
		     
		      
		     
		      void gms::math::cart_to_sphere_ymm4r8_a(double * __restrict __ATTR_ALIGN__(32) range,
		                                   double * __restrict __ATTR_ALIGN__(32) az,
						   double * __restrict __ATTR_ALIGN__(32) elev,
						   const __m256d C_x,
						   const __m256d C_y,
						   const __m256d C_z,
						   const __m256d T_x,
						   const __m256d T_y,
						   const __m256d T_z,
						   const __m256d R_x,
						   const __m256d R_y,
						   const __m256d R_z,
						   const __m256d * __restrict __ATTR_ALIGN__(32) M,
						   const int sysType,
						   const bool useHalfRange) {

			  const __m256d _0   = _mm256_setzero_pd();
			  const __m256d _0_5 = _mm256_set1_pd(0.5);
                          __m256d CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256d diff0,diff1,diff2,diff3,diff4,diff5;
			  __m256d r1,r2;
			  const __m256d M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_pd(C_x,R_x);
			  const __m256d M1 = M[1];
			  diff1 = _mm256_sub_pd(C_y,R_y);
			  const __m256d M2 = M[2];
			  diff2 = _mm256_sub_pd(C_z,R_z);
			  const __m256d M3 = M[3];
			  diff3 = _mm256_sub_pd(T_x,R_x);
			  const __m256d M4 = M[4];
			  diff4 = _mm256_sub_pd(T_y,R_y);
			  const __m256d M5 = M[5];
			  diff5 = _mm256_sub_pd(T_z,R_z);
			  const __m256d M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_pd(M0,diff3,_mm256_fmadd_pd(M3,diff4,_mm256_mul_pd(M6,diff5)));
			  CL0   = _mm256_fmadd_pd(M0,diff0,_mm256_fmadd_pd(M3,diff1,_mm256_mul_pd(M6,diff2)));
			  const __m256d M7 = M[7];
			  CL1   = _mm256_fmadd_pd(M1,diff0,_mm256_fmadd_pd(M4,diff1,_mm256_mul_pd(M7,diff2)));
			  TxL1  = _mm256_fmadd_pd(M1,diff3,_mm256_fmadd_pd(M4,diff4,_mm256_mul_pd(M7,diff5)));
			  const __m256d M8 = M[8];
			  CL2   = _mm256_fmadd_pd(M2,diff0,_mm256_fmadd_pd(M5,diff1,_mm256_mul_pd(M8,diff2)));
			  TxL2  = _mm256_fmadd_pd(M2,diff3,_mm256_fmadd_pd(M5,diff4,_mm256_mul_pd(M8,diff5)));
			  ///Receiver to target.
			  __m256d sarg = _mm256_fmadd_pd(CL0,CL0,_mm256_fmadd_pd(CL1,CL1,_mm256_mul_pd(CL2,CL2)));
			  r1    = _mm256_sqrt_pd(sarg);
			  diff0 = _mm256_sub_pd(CL0,TxL0);
			  diff1 = _mm256_sub_pd(CL1,TxL1);
			  diff2 = _mm256_sub_pd(CL2,TxL2);
			  //Target to transmitter
			  sarg  = _mm256_fmadd_pd(diff0,diff0,_mm256_fmadd_pd(diff1,diff1,_mm256_mul_pd(diff2,diff2)));
			  r2    = _mm256_sqrt_pd(sarg);
			  _mm256_store_pd(&range[0],_mm256_add_pd(r1,r2));
			  if(sysType==0||sysType==2||sysType==3) {
                             __mmask8 m1,m2;
			     m1 = _mm256_cmp_pd_mask(CL1,_0,_CMP_EQ_OQ);
			     m2 = _mm256_cmp_pd_mask(CL0,_0,_CMP_EQ_OQ);
			     if(m1 && m2) {
                                _mm256_store_pd(&az[0],_0);
			     }
			     else {
                                _mm256_store_pd(&az[0],_mm256_atan2_pd(CL1,CL0));
			     }
			     _mm256_store_pd(&elev[0],_mm256_atan2_pd(CL2,_mm256_hypot_pd(CL0,CL1)));
			     if(sysType==2) {
                                const __m256d pi2 = _mm256_set1_pd(1.5707963267948966192313);
				_mm256_store_pd(&elev[0],_mm256_sub_pd(pi2,_mm256_load_pd(&elev[0])));
			     }
			     else if(sysType==3) {
                                const __m256d pi2 = _mm256_set1_pd(1.5707963267948966192313);
				_mm256_store_pd(&az[0],_mm256_sub_pd(pi2,_mm256_load_pd(&az[0])));
			     }
			  }
			  else {
                              __mmask8 m1,m2;
			      m1 = _mm256_cmp_pd_mask(CL2,_0,_CMP_EQ_OQ);
			      m2 = _mm256_cmp_pd_mask(CL0,_0,_CMP_EQ_OQ);
			      if(m1 && m2) {
                                 _mm256_store_pd(&az[0],_0);
			      }
			      else {
                                 _mm256_store_pd(&az[0],_mm256_atan2_pd(CL0,CL2));
			      }
			      _mm256_store_pd(&elev[0],_mm256_atan2_pd(CL1,_mm256_hypot_pd(CL2,CL0)));
			  }

			  if(useHalfRange) {
                             _mm256_store_pd(&range[0],_mm256_mul_pd(_mm256_load_pd(&range[0],_0_5)));
			  }
		     }


		     
                    
		     
		      
		     
		      void gms::math::cart_to_sphere_ymm4r8_u(double * __restrict  range,
		                                   double * __restrict  az,
						   double * __restrict  elev,
						   const __m256d C_x,
						   const __m256d C_y,
						   const __m256d C_z,
						   const __m256d T_x,
						   const __m256d T_y,
						   const __m256d T_z,
						   const __m256d R_x,
						   const __m256d R_y,
						   const __m256d R_z,
						   const __m256d * __restrict __ATTR_ALIGN__(32) M,
						   const int sysType,
						   const bool useHalfRange) {

			  const __m256d _0   = _mm256_setzero_pd();
			  const __m256d _0_5 = _mm256_set1_pd(0.5);
                          __m256d CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256d diff0,diff1,diff2,diff3,diff4,diff5;
			  __m256d r1,r2;
			  const __m256d M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_pd(C_x,R_x);
			  const __m256d M1 = M[1];
			  diff1 = _mm256_sub_pd(C_y,R_y);
			  const __m256d M2 = M[2];
			  diff2 = _mm256_sub_pd(C_z,R_z);
			  const __m256d M3 = M[3];
			  diff3 = _mm256_sub_pd(T_x,R_x);
			  const __m256d M4 = M[4];
			  diff4 = _mm256_sub_pd(T_y,R_y);
			  const __m256d M5 = M[5];
			  diff5 = _mm256_sub_pd(T_z,R_z);
			  const __m256d M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_pd(M0,diff3,_mm256_fmadd_pd(M3,diff4,_mm256_mul_pd(M6,diff5)));
			  CL0   = _mm256_fmadd_pd(M0,diff0,_mm256_fmadd_pd(M3,diff1,_mm256_mul_pd(M6,diff2)));
			  const __m256d M7 = M[7];
			  CL1   = _mm256_fmadd_pd(M1,diff0,_mm256_fmadd_pd(M4,diff1,_mm256_mul_pd(M7,diff2)));
			  TxL1  = _mm256_fmadd_pd(M1,diff3,_mm256_fmadd_pd(M4,diff4,_mm256_mul_pd(M7,diff5)));
			  const __m256d M8 = M[8];
			  CL2   = _mm256_fmadd_pd(M2,diff0,_mm256_fmadd_pd(M5,diff1,_mm256_mul_pd(M8,diff2)));
			  TxL2  = _mm256_fmadd_pd(M2,diff3,_mm256_fmadd_pd(M5,diff4,_mm256_mul_pd(M8,diff5)));
			  ///Receiver to target.
			  __m256d sarg = _mm256_fmadd_pd(CL0,CL0,_mm256_fmadd_pd(CL1,CL1,_mm256_mul_pd(CL2,CL2)));
			  r1    = _mm256_sqrt_pd(sarg);
			  diff0 = _mm256_sub_pd(CL0,TxL0);
			  diff1 = _mm256_sub_pd(CL1,TxL1);
			  diff2 = _mm256_sub_pd(CL2,TxL2);
			  //Target to transmitter
			  sarg  = _mm256_fmadd_pd(diff0,diff0,_mm256_fmadd_pd(diff1,diff1,_mm256_mul_pd(diff2,diff2)));
			  r2    = _mm256_sqrt_pd(sarg);
			  _mm256_storeu_pd(&range[0],_mm256_add_pd(r1,r2));
			  if(sysType==0||sysType==2||sysType==3) {
                             __mmask8 m1,m2;
			     m1 = _mm256_cmp_pd_mask(CL1,_0,_CMP_EQ_OQ);
			     m2 = _mm256_cmp_pd_mask(CL0,_0,_CMP_EQ_OQ);
			     if(m1 && m2) {
                                _mm256_storeu_pd(&az[0],_0);
			     }
			     else {
                                _mm256_storeu_pd(&az[0],_mm256_atan2_pd(CL1,CL0));
			     }
			     _mm256_storeu_pd(&elev[0],_mm256_atan2_pd(CL2,_mm256_hypot_pd(CL0,CL1)));
			     if(sysType==2) {
                                const __m256d pi2 = _mm256_set1_pd(1.5707963267948966192313);
				_mm256_storeu_pd(&elev[0],_mm256_sub_pd(pi2,_mm256_loadu_pd(&elev[0])));
			     }
			     else if(sysType==3) {
                                const __m256d pi2 = _mm256_set1_pd(1.5707963267948966192313);
				_mm256_storeu_pd(&az[0],_mm256_sub_pd(pi2,_mm256_loadu_pd(&az[0])));
			     }
			  }
			  else {
                              __mmask8 m1,m2;
			      m1 = _mm256_cmp_pd_mask(CL2,_0,_CMP_EQ_OQ);
			      m2 = _mm256_cmp_pd_mask(CL0,_0,_CMP_EQ_OQ);
			      if(m1 && m2) {
                                 _mm256_storeu_pd(&az[0],_0);
			      }
			      else {
                                 _mm256_storeu_pd(&az[0],_mm256_atan2_pd(CL0,CL2));
			      }
			      _mm256_storeu_pd(&elev[0],_mm256_atan2_pd(CL1,_mm256_hypot_pd(CL2,CL0)));
			  }

			  if(useHalfRange) {
                             _mm256_storeu_pd(&range[0],_mm256_mul_pd(_mm256_loadu_pd(&range[0],_0_5)));
			  }
		     }






		     
                    
		     
		      
		     
		      void gms::math::cart_to_sphere_ymm8r4(__m256 &range,
		                                  __m256 &az,
						  __m256 &elev,
						  const __m256 C_x,
						  const __m256 C_y,
						  const __m256 C_z,
						  const __m256 T_x,
						  const __m256 T_y,
						  const __m256 T_z,
						  const __m256 R_x,
						  const __m256 R_y,
						  const __m256 R_z,
						  const __m256 * __restrict __ATTR_ALIGN__(32) M,
						  const int sysType,
						  const bool useHalfRange) {

			  const __m256 _0   = _mm256_setzero_ps();
			  const __m256 _0_5 = _mm256_set1_ps(0.5f);
                          __m256 CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256 diff0,diff1,diff2,diff3,diff4,diff5;
			  __m256 r1,r2;
			  const __m256 M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_ps(C_x,R_x);
			  const __m256 M1 = M[1];
			  diff1 = _mm256_sub_ps(C_y,R_y);
			  const __m256 M2 = M[2];
			  diff2 = _mm256_sub_ps(C_z,R_z);
			  const __m256 M3 = M[3];
			  diff3 = _mm256_sub_ps(T_x,R_x);
			  const __m256 M4 = M[4];
			  diff4 = _mm256_sub_ps(T_y,R_y);
			  const __m256 M5 = M[5];
			  diff5 = _mm256_sub_ps(T_z,R_z);
			  const __m256 M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_ps(M0,diff3,_mm256_fmadd_ps(M3,diff4,_mm256_mul_ps(M6,diff5)));
			  CL0   = _mm256_fmadd_ps(M0,diff0,_mm256_fmadd_ps(M3,diff1,_mm256_mul_ps(M6,diff2)));
			  const __m256 M7 = M[7];
			  CL1   = _mm256_fmadd_ps(M1,diff0,_mm256_fmadd_ps(M4,diff1,_mm256_mul_ps(M7,diff2)));
			  TxL1  = _mm256_fmadd_ps(M1,diff3,_mm256_fmadd_ps(M4,diff4,_mm256_mul_ps(M7,diff5)));
			  const __m256 M8 = M[8];
			  CL2   = _mm256_fmadd_ps(M2,diff0,_mm256_fmadd_ps(M5,diff1,_mm256_mul_ps(M8,diff2)));
			  TxL2  = _mm256_fmadd_ps(M2,diff3,_mm256_fmadd_ps(M5,diff4,_mm256_mul_ps(M8,diff5)));
			  ///Receiver to target.
			  __m256 sarg = _mm256_fmadd_ps(CL0,CL0,_mm256_fmadd_ps(CL1,CL1,_mm256_mul_ps(CL2,CL2)));
			  r1    = _mm256_sqrt_ps(sarg);
			  diff0 = _mm256_sub_ps(CL0,TxL0);
			  diff1 = _mm256_sub_ps(CL1,TxL1);
			  diff2 = _mm256_sub_ps(CL2,TxL2);
			  //Target to transmitter
			  sarg  = _mm256_fmadd_ps(diff0,diff0,_mm256_fmadd_ps(diff1,diff1,_mm256_mul_ps(diff2,diff2)));
			  r2    = _mm256_sqrt_ps(sarg);
			  range = _mm256_add_ps(r1,r2);
			  if(sysType==0||sysType==2||sysType==3) {
                             __mmask8 m1,m2;
			     m1 = _mm256_cmp_ps_mask(CL1,_0,_CMP_EQ_OQ);
			     m2 = _mm256_cmp_ps_mask(CL0,_0,_CMP_EQ_OQ);
			     if(m1 && m2) {
                                az = _0;
			     }
			     else {
                                az = _mm256_atan2_ps(CL1,CL0);
			     }
			     elev = _mm256_atan2_ps(CL2,_mm256_hypot_ps(CL0,CL1));
			     if(sysType==2) {
                                const __m256 pi2 = _mm256_set1_ps(1.5707963267948966192313f);
				elev              = _mm256_sub_ps(pi2,elev);
			     }
			     else if(sysType==3) {
                                const __m256 pi2 = _mm256_set1_ps(1.5707963267948966192313f);
				az                = _mm256_sub_ps(pi2,az);
			     }
			  }
			  else {
                              __mmask8 m1,m2;
			      m1 = _mm256_cmp_ps_mask(CL2,_0,_CMP_EQ_OQ);
			      m2 = _mm256_cmp_ps_mask(CL0,_0,_CMP_EQ_OQ);
			      if(m1 && m2) {
                                 az = _0;
			      }
			      else {
                                 az = _mm256_atan2_ps(CL0,CL2);
			      }
			      elev = _mm256_atan2_ps(CL1,_mm256_hypot_ps(CL2,CL0));
			  }

			  if(useHalfRange) {
                             range = _mm256_mul_ps(range,_0_5);
			  }
		     }


		     
                    
		     
		      
		     
		      void gms::math::cart_to_sphere_ymm8r4_a(float * __restrict __ATTR_ALIGN__(32) range,
		                                    float * __restrict __ATTR_ALIGN__(32) az,
						    float * __restrict __ATTR_ALIGN__(32) elev,
						    const __m256 C_x,
						    const __m256 C_y,
						    const __m256 C_z,
						    const __m256 T_x,
						    const __m256 T_y,
						    const __m256 T_z,
						    const __m256 R_x,
						    const __m256 R_y,
						    const __m256 R_z,
						    const __m256 * __restrict __ATTR_ALIGN__(32) M,
						    const int sysType,
						    const bool useHalfRange) {

			  const __m256 _0   = _mm256_setzero_ps();
			  const __m256 _0_5 = _mm256_set1_ps(0.5f);
                          __m256 CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256 diff0,diff1,diff2,diff3,diff4,diff5;
			  __m256 r1,r2;
			  const __m256 M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_ps(C_x,R_x);
			  const __m256 M1 = M[1];
			  diff1 = _mm256_sub_ps(C_y,R_y);
			  const __m256 M2 = M[2];
			  diff2 = _mm256_sub_ps(C_z,R_z);
			  const __m256 M3 = M[3];
			  diff3 = _mm256_sub_ps(T_x,R_x);
			  const __m256 M4 = M[4];
			  diff4 = _mm256_sub_ps(T_y,R_y);
			  const __m256 M5 = M[5];
			  diff5 = _mm256_sub_ps(T_z,R_z);
			  const __m256 M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_ps(M0,diff3,_mm256_fmadd_ps(M3,diff4,_mm256_mul_ps(M6,diff5)));
			  CL0   = _mm256_fmadd_ps(M0,diff0,_mm256_fmadd_ps(M3,diff1,_mm256_mul_ps(M6,diff2)));
			  const __m256 M7 = M[7];
			  CL1   = _mm256_fmadd_ps(M1,diff0,_mm256_fmadd_ps(M4,diff1,_mm256_mul_ps(M7,diff2)));
			  TxL1  = _mm256_fmadd_ps(M1,diff3,_mm256_fmadd_ps(M4,diff4,_mm256_mul_ps(M7,diff5)));
			  const __m256 M8 = M[8];
			  CL2   = _mm256_fmadd_ps(M2,diff0,_mm256_fmadd_ps(M5,diff1,_mm256_mul_ps(M8,diff2)));
			  TxL2  = _mm256_fmadd_ps(M2,diff3,_mm256_fmadd_ps(M5,diff4,_mm256_mul_ps(M8,diff5)));
			  ///Receiver to target.
			  __m256 sarg = _mm256_fmadd_ps(CL0,CL0,_mm256_fmadd_ps(CL1,CL1,_mm256_mul_ps(CL2,CL2)));
			  r1    = _mm256_sqrt_ps(sarg);
			  diff0 = _mm256_sub_ps(CL0,TxL0);
			  diff1 = _mm256_sub_ps(CL1,TxL1);
			  diff2 = _mm256_sub_ps(CL2,TxL2);
			  //Target to transmitter
			  sarg  = _mm256_fmadd_ps(diff0,diff0,_mm256_fmadd_ps(diff1,diff1,_mm256_mul_ps(diff2,diff2)));
			  r2    = _mm256_sqrt_ps(sarg);
			  _mm256_store_ps(&range[0],_mm256_add_ps(r1,r2));
			  if(sysType==0||sysType==2||sysType==3) {
                             __mmask8 m1,m2;
			     m1 = _mm256_cmp_ps_mask(CL1,_0,_CMP_EQ_OQ);
			     m2 = _mm256_cmp_ps_mask(CL0,_0,_CMP_EQ_OQ);
			     if(m1 && m2) {
                                _mm256_store_ps(&az[0],_0);
			     }
			     else {
                                _mm256_store_ps(&az[0],_mm256_atan2_ps(CL1,CL0));
			     }
			     _mm256_store_ps(&elev[0],_mm256_atan2_ps(CL2,_mm256_hypot_ps(CL0,CL1)));
			     if(sysType==2) {
                                const __m256 pi2 = _mm256_set1_ps(1.5707963267948966192313f);
				_mm256_store_ps(&elev[0],_mm256_sub_ps(pi2,_mm256_load_ps(&elev[0])));
			     }
			     else if(sysType==3) {
                                const __m256 pi2 = _mm256_set1_ps(1.5707963267948966192313f);
				_mm256_store_ps(&az[0],_mm256_sub_ps(pi2,_mm256_load_ps(&az[0])));
			     }
			  }
			  else {
                              __mmask8 m1,m2;
			      m1 = _mm256_cmp_ps_mask(CL2,_0,_CMP_EQ_OQ);
			      m2 = _mm256_cmp_ps_mask(CL0,_0,_CMP_EQ_OQ);
			      if(m1 && m2) {
                                 _mm256_store_ps(&az[0],_0);
			      }
			      else {
                                 _mm256_store_ps(&az[0],_mm256_atan2_ps(CL0,CL2));
			      }
			      _mm256_store_ps(&elev[0],_mm256_atan2_ps(CL1,_mm256_hypot_ps(CL2,CL0)));
			  }

			  if(useHalfRange) {
                             _mm256_store_ps(&range[0],_mm256_mul_ps(_mm256_load_ps(&range[0],_0_5)));
			  }
		     }

 

		     
                    
		     
		      
		     
		      void gms::math::cart_to_sphere_ymm8r4_u(float * __restrict  range,
		                                    float * __restrict  az,
						    float * __restrict  elev,
						    const __m256 C_x,
						    const __m256 C_y,
						    const __m256 C_z,
						    const __m256 T_x,
						    const __m256 T_y,
						    const __m256 T_z,
						    const __m256 R_x,
						    const __m256 R_y,
						    const __m256 R_z,
						    const __m256 * __restrict __ATTR_ALIGN__(32) M,
						    const int sysType,
						    const bool useHalfRange) {

			  const __m256 _0   = _mm256_setzero_ps();
			  const __m256 _0_5 = _mm256_set1_ps(0.5f);
                          __m256 CL0,CL1,CL2,TxL0,TxL1,TxL2;
			  __m256 diff0,diff1,diff2,diff3,diff4,diff5;
			  __m256 r1,r2;
			  const __m256 M0 = M[0];
			  //Compute the target location in the receiver's coordinate system.
			  diff0 = _mm256_sub_ps(C_x,R_x);
			  const __m256 M1 = M[1];
			  diff1 = _mm256_sub_ps(C_y,R_y);
			  const __m256 M2 = M[2];
			  diff2 = _mm256_sub_ps(C_z,R_z);
			  const __m256 M3 = M[3];
			  diff3 = _mm256_sub_ps(T_x,R_x);
			  const __m256 M4 = M[4];
			  diff4 = _mm256_sub_ps(T_y,R_y);
			  const __m256 M5 = M[5];
			  diff5 = _mm256_sub_ps(T_z,R_z);
			  const __m256 M6 = M[6];
			   //Compute the transmitter location in the receiver's local coordinate
                          //system.
			  TxL0  = _mm256_fmadd_ps(M0,diff3,_mm256_fmadd_ps(M3,diff4,_mm256_mul_ps(M6,diff5)));
			  CL0   = _mm256_fmadd_ps(M0,diff0,_mm256_fmadd_ps(M3,diff1,_mm256_mul_ps(M6,diff2)));
			  const __m256 M7 = M[7];
			  CL1   = _mm256_fmadd_ps(M1,diff0,_mm256_fmadd_ps(M4,diff1,_mm256_mul_ps(M7,diff2)));
			  TxL1  = _mm256_fmadd_ps(M1,diff3,_mm256_fmadd_ps(M4,diff4,_mm256_mul_ps(M7,diff5)));
			  const __m256 M8 = M[8];
			  CL2   = _mm256_fmadd_ps(M2,diff0,_mm256_fmadd_ps(M5,diff1,_mm256_mul_ps(M8,diff2)));
			  TxL2  = _mm256_fmadd_ps(M2,diff3,_mm256_fmadd_ps(M5,diff4,_mm256_mul_ps(M8,diff5)));
			  ///Receiver to target.
			  __m256 sarg = _mm256_fmadd_ps(CL0,CL0,_mm256_fmadd_ps(CL1,CL1,_mm256_mul_ps(CL2,CL2)));
			  r1    = _mm256_sqrt_ps(sarg);
			  diff0 = _mm256_sub_ps(CL0,TxL0);
			  diff1 = _mm256_sub_ps(CL1,TxL1);
			  diff2 = _mm256_sub_ps(CL2,TxL2);
			  //Target to transmitter
			  sarg  = _mm256_fmadd_ps(diff0,diff0,_mm256_fmadd_ps(diff1,diff1,_mm256_mul_ps(diff2,diff2)));
			  r2    = _mm256_sqrt_ps(sarg);
			  _mm256_storeu_ps(&range[0],_mm256_add_ps(r1,r2));
			  if(sysType==0||sysType==2||sysType==3) {
                             __mmask8 m1,m2;
			     m1 = _mm256_cmp_ps_mask(CL1,_0,_CMP_EQ_OQ);
			     m2 = _mm256_cmp_ps_mask(CL0,_0,_CMP_EQ_OQ);
			     if(m1 && m2) {
                                _mm256_storeu_ps(&az[0],_0);
			     }
			     else {
                                _mm256_storeu_ps(&az[0],_mm256_atan2_ps(CL1,CL0));
			     }
			     _mm256_store_ups(&elev[0],_mm256_atan2_ps(CL2,_mm256_hypot_ps(CL0,CL1)));
			     if(sysType==2) {
                                const __m256 pi2 = _mm256_set1_ps(1.5707963267948966192313f);
				_mm256_storeu_ps(&elev[0],_mm256_sub_ps(pi2,_mm256_loadu_ps(&elev[0])));
			     }
			     else if(sysType==3) {
                                const __m256 pi2 = _mm256_set1_ps(1.5707963267948966192313f);
				_mm256_storeu_ps(&az[0],_mm256_sub_ps(pi2,_mm256_loadu_ps(&az[0])));
			     }
			  }
			  else {
                              __mmask8 m1,m2;
			      m1 = _mm256_cmp_ps_mask(CL2,_0,_CMP_EQ_OQ);
			      m2 = _mm256_cmp_ps_mask(CL0,_0,_CMP_EQ_OQ);
			      if(m1 && m2) {
                                 _mm256_storeu_ps(&az[0],_0);
			      }
			      else {
                                 _mm256_storeu_ps(&az[0],_mm256_atan2_ps(CL0,CL2));
			      }
			      _mm256_storeu_ps(&elev[0],_mm256_atan2_ps(CL1,_mm256_hypot_ps(CL2,CL0)));
			  }

			  if(useHalfRange) {
                             _mm256_storeu_ps(&range[0],_mm256_mul_ps(_mm256_loadu_ps(&range[0],_0_5)));
			  }
		     }

 
 
 
 
