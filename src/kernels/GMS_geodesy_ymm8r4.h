
#ifndef __GMS_GEODESY_YMM8R4_H__
#define __GMS_GEODESY_YMM8R4_H__ 201020210942


namespace file_version {

    const unsigned int gGMS_GEODESY_YMM8R4_MAJOR = 1U;
    const unsigned int gGMS_GEODESY_YMM8R4_MINOR = 0U;
    const unsigned int gGMS_GEODESY_YMM8R4_MICRO = 0U;
    const unsigned int gGMS_GEODESY_YMM8R4_FULLVER =
      1000U*gGMS_GEODESY_YMM8R4_MAJOR+
      100U*gGMS_GEODESY_YMM8R4_MINOR+
      10U*gGMS_GEODESY_YMM8R4_MICRO;
    const char * const pgGMS_GEODESY_YMM8R4_CREATION_DATE = "20-10-2021 09:42 AM +00200 (WED 20 OCT 2021 GMT+2)";
    const char * const pgGMS_GEODESY_YMM8R4_BUILD_DATE    = __DATE__ ":" __TIME__;
    const char * const pgGMS_GEODESY_YMM8R4_AUTHOR        = "Programmer: Bernard Gingold, contact: beniekg@gmail.com";
    const char * const pgGMS_GEODESY_YMM8R4_DESCRIPTION   = "Vectorized (AVX packed single-precision) geodesic computation implementation."

}


#include <immintrin.h>
#include <cstdint>
#include "GMS_config.h"



namespace  gms {

          namespace math {


	                 /*
                              Cartesian to geodetic conversion (kernel).
                              
                          */
	             
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			__ATTR_REGCALL__
	               
			void
			cart_to_geodetic_ymm8r4(     const __m256 pos_x, //input position x [km]
			                             const __m256 pos_y, //input position y [km]
						     const __m256 pos_z, //input position z [km]
						     const __m256 a, // semi-minor axis [km]
						     const __m256 b, // semi-major axis [km]
						     __m256 &alt, //output altitude [km]
						     __m256 &lon, //output longtitude [rad]
						     __m256 &lat); 
						     

			
			
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			
			void
			cart_to_geodetic_u_ymm8r4_looped( const float * __restrict pos_x,
			                                  const float * __restrict pos_y,
							  const float * __restrict pos_z,
							  const float a,
							  const float b,
							  float * __restrict alt,
							  float * __restrict lon,
							  float * __restrict lat,
							  const int32_t n); 


			
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
		
			void
			cart_to_geodetic_a_ymm8r4_looped(float * __restrict __ATTR_ALIGN__(32) pos_x,
			                                 float * __restrict __ATTR_ALIGN__(32) pos_y,
							 float * __restrict __ATTR_ALIGN__(32) pos_z,
							 const float a,
							 const float b,
							 float * __restrict __ATTR_ALIGN__(32) alt,
							 float * __restrict __ATTR_ALIGN__(32) lon,
							 float * __restrict __ATTR_ALIGN__(32) lat,
							 const int32_t n); 
							 

                    	
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			__ATTR_REGCALL__
	              
			void geodetic_to_cart_ymm8r4(const __m256 a,
			                              const __m256 b,
						      const __m256 lat,
						      const __m256 lon,
						      const __m256 alt,
						      __m256 &pos_x,
						      __m256 &pos_y,
						      __m256 &pos_z); 


                    	
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			
			void
			geodetic_to_cart_u_ymm8r4_looped(const float a,
			                                  const float b,
							  const float * __restrict lat,
							  const float * __restrict lon,
							  const float * __restrict alt,
							  float * __restrict pos_x,
							  float * __restrict pos_y,
							  float * __restrict pos_z,
							  const int32_t n); 
							  


		
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
		       
			void
			geodetic_to_cart_a_ymm8r4_looped(const float a,
			                                  const float b,
							  float * __restrict __ATTR_ALIGN__(32) lat,
							  float * __restrict __ATTR_ALIGN__(32) lon,
							  float * __restrict __ATTR_ALIGN__(32) alt,
							  float * __restrict __ATTR_ALIGN__(32) pos_x,
							  float * __restrict __ATTR_ALIGN__(32) pos_y,
							  float * __restrict __ATTR_ALIGN__(32) pos_z,
							  const int32_t n); 

			


						     
     }

}














#endif /*__GMS_GEODESY_YMM8R4_H__*/
