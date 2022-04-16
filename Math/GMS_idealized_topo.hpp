
#ifndef __GMS_IDEALIZED_TOPO_HPP__
#define __GMS_IDEALIZED_TOPO_HPP__

/*
    Adapted from Fortran implementation.
    Original author description:
    ! <CONTACT EMAIL="Bruce.Wyman@noaa.gov">
    !   Bruce Wyman
    ! </CONTACT>

       ! <HISTORY SRC="http://www.gfdl.noaa.gov/fms-cgi-bin/cvsweb.cgi/FMS/"/>
  
   ! <OVERVIEW>
       !   Routines for creating Gaussian-shaped land surface topography
       !   for latitude-longitude grids.
   ! </OVERVIEW>
*/

namespace file_info {

     const unsigned int GMS_IDEALIZED_TOPO_MAJOR = 1;
     const unsigned int GMS_IDEALIZED_TOPO_MINOR = 1;
     const unsigned int GMS_IDEALIZED_TOPO_MICRO = 0;
     const unsigned int GMS_IDEALIZED_TOPO_FULLVER =
       1000U*GMS_IDEALIZED_TOPO_MAJOR+100U*GMS_IDEALIZED_TOPO_MINOR+
       10U*GMS_IDEALIZED_TOPO_MICRO;
     const char * const GMS_IDEALIZED_TOPO_CREATION_DATE = "16-01-2022 09:34 +00200 (SAT 16 APR 2022 GMT+2)";
     const char * const GMS_IDEALIZED_TOPO_BUILD_DATE    = __DATE__ " " __TIME__;
     const char * const GMS_IDEALIZED_TOPO_SYNOPSIS      = "Idealized gaussian and sinusoidal topography simulator."

}

#include <cstdint>
#include <omp.h>
#include <algorithm>
#include <cmath>
#include "GMS_config.h"
#include "GMS_indices.h"

namespace gms {



                   
                        __ATTR_ALWAYS_INLINE__
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			static inline
                        void gaussian_topography_r4(float * __restrict __ATTR_ALIGN__(64) lon,
			                            const int32_t nlon,
						    float * __restrict __ATTR_ALIGN__(64) lat,
						    const int32_t nlat,
						    float * __restrict __ATTR_ALIGN__(64) zsurf,
						    const float height) {

			      if(__builtin_expect(lon<=0,0) ||
			         __builtin_expect(lat<=0,0)) {
                                 return;
			      }

			      constexpr float tpi = 6.2831853071795864769253f; //!2.0_sp*pi
			      constexpr float dtr = 0.0174532925199432957692f;  //!tpi/360.
			      constexpr float olon = 90.0f*dtr;
			      constexpr float olat = 45.0f*dtr;
			      constexpr float wlon = 15.0f*dtr;
			      constexpr float wlat = wlon;
			      constexpr float rlon = 0.0f;
			      constexpr float rlat = 0.0f;
			      constexpr float inwlat = 0.066666666666666666666666666667f;
			      constexpr float inwlon = inwlat;
			      float xx = 0.0f;
			      float yy = 0.0f;
#if defined(__INTEL_COMPILER) || defined(__ICC)
                              assume_aligned(lon,64);
			      assume_aligned(lat,64);
			      assume_aligned(zsurf,64)
#elif defined(__GNUC__) && (!defined(__INTEL_COMPILER) || !defined(__ICC))
                              lon = (float*)__builtin_assume_aligned(lon,64);
			      lat = (float*)__builtin_assume_aligned(lat,64);
			      zsurf=(float*)__builtin_assume_aligned(zsurf,64);
#endif
#if defined(__INTEL_COMPILER) || defined(__ICC)
                              #pragma code_align(32)
			      #pragma prefetch lat:0:4
			      #pragma prefetch lat:1:16
			      #pragma prefetch lon:0:4
			      #pragma prefetch lon:1:16
#endif
                              #pragma omp simd simdlen(4) linear(i:1) private(ilon,dx,xx)
                              for(int32_t i = 0; i != nlon; ++i) {
			          const float ilon = lon[i];
                                  float dx = std::abs(ilon-olon);
				  dx       = std::min(dx,std::abs(dx-tpi));
				  xx = std::max(0.0f,dx-rlon)*inwlon;
				  #pragma omp simd simdlen(4) linear(j:1) private(ilat,dy,yy)
				  for(int32_t j = 0; j != nlat; ++j) {
				      const float ilat = lat[j];
                                      const float dy = std::abs(ilat-olat);
				      yy = std::max(0.0f,dy-rlat)*inwlat;
				      zsurf[Ix2D(i,nlat,j)] = height*std::exp(-xx*xx-yy*yy);
				  }
			      }
		       }


                        __ATTR_ALWAYS_INLINE__
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			static inline
                        void gaussian_topography_r8(double * __restrict __ATTR_ALIGN__(64) lon,
			                            const int32_t nlon,
						    double * __restrict __ATTR_ALIGN__(64) lat,
						    const int32_t nlat,
						    double * __restrict __ATTR_ALIGN__(64) zsurf,
						    const double height) {

			      if(__builtin_expect(lon<=0,0) ||
			         __builtin_expect(lat<=0,0)) {
                                 return;
			      }

			      constexpr double tpi = 6.2831853071795864769253; //!2.0_sp*pi
			      constexpr double dtr = 0.0174532925199432957692;  //!tpi/360.
			      constexpr double olon = 90.0*dtr;
			      constexpr double olat = 45.0*dtr;
			      constexpr double wlon = 15.0*dtr;
			      constexpr double wlat = wlon;
			      constexpr double rlon = 0.0;
			      constexpr double rlat = 0.0;
			      constexpr double inwlat = 0.066666666666666666666666666667;
			      constexpr double inwlon = inwlat;
			      double xx = 0.0;
			      double yy = 0.0;
#if defined(__INTEL_COMPILER) || defined(__ICC)
                              assume_aligned(lon,64);
			      assume_aligned(lat,64);
			      assume_aligned(zsurf,64)
#elif defined(__GNUC__) && (!defined(__INTEL_COMPILER) || !defined(__ICC))
                              lon = (double*)__builtin_assume_aligned(lon,64);
			      lat = (double*)__builtin_assume_aligned(lat,64);
			      zsurf=(double*)__builtin_assume_aligned(zsurf,64);
#endif
#if defined(__INTEL_COMPILER) || defined(__ICC)
                              #pragma code_align(32)
			      #pragma prefetch lat:0:4
			      #pragma prefetch lat:1:16
			      #pragma prefetch lon:0:4
			      #pragma prefetch lon:1:16
#endif
                              #pragma omp simd simdlen(8) linear(i:1) private(ilon,dx,xx)
                              for(int32_t i = 0; i != nlon; ++i) {
			          const double ilon = lon[i];
                                  double dx = std::abs(ilon-olon);
				  dx       = std::min(dx,std::abs(dx-tpi));
				  xx = std::max(0.0,dx-rlon)*inwlon;
				  #pragma omp simd simdlen(8) linear(j:1) private(ilat,dy,yy)
				  for(int32_t j = 0; j != nlat; ++j) {
				      const double ilat = lat[j];
                                      const double dy = std::abs(ilat-olat);
				      yy = std::max(0.0,dy-rlat)*inwlat;
				      zsurf[Ix2D(i,nlat,j)] = height*std::exp(-xx*xx-yy*yy);
				  }
			      }
		       }


                        __ATTR_ALWAYS_INLINE__
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			static inline
			void sinusoidal_topography(float * __restrict __ATTR_ALIGN__(64) lon,
			                           const int32_t nlon,
						   float * __restrict __ATTR_ALIGN__(64) lat,
						   const int32_t nlat,
						   float * __restrict __ATTR_ALIGN__(64) zsurf,
						   const float height_sin,
						   const float m,
						   const float Amp2,
						   const float uneven_fac,
						   const float deltalat,
						   const bool uneven_sin) {

                               if(__builtin_expect(nlon<=0,0) ||
			          __builtin_expect(nlat<=0,0)) {
                                  return;
			       }
			       if(__builtin_expect(height_sin==0.0f,0)) {
                                  return;
			       }
                               constexpr float pi   = 3.1415926535897932384626f;
			       constexpr float tpi4 = 2.356194490192344928847f;
			       constexpr float spi4 = 5.4977871437821381673096f;
                               constexpr float tpi  = 6.2831853071795864769253f; //!2.0*pi
			       constexpr float dtr  = 0.0174532925199432957692f; //!tpi/360.
			       float lat00          = 25.0f+deltalat;
			       lat00                = dtr*lat00;
			       float lat11          = 65.0f+deltalat;
			       lat11                = dtr*lat11;
			       float ldiff          = lat11-lat00;
			       float ildiff         = 1.0f/ldiff;
			       float latj,loni;
#if defined(__INTEL_COMPILER) || defined(__ICC)
                              assume_aligned(lon,64);
			      assume_aligned(lat,64);
			      assume_aligned(zsurf,64)
#elif defined(__GNUC__) && (!defined(__INTEL_COMPILER) || !defined(__ICC))
                              lon = (float*)__builtin_assume_aligned(lon,64);
			      lat = (float*)__builtin_assume_aligned(lat,64);
			      zsurf=(float*)__builtin_assume_aligned(zsurf,64);
#endif
#if defined(__INTEL_COMPILER) || defined(__ICC)
                              #pragma code_align(32)
			      #pragma prefetch lat:0:4
			      #pragma prefetch lat:1:16
			      #pragma prefetch lon:0:4
			      #pragma prefetch lon:1:16
#endif
                              for(int32_t j = 0; j != nlat; ++j) {
                                  latj = lat[j];
				  #pragma simd simdlen(4) linear(i:1) private(loni,t0,t1,t2)
				  for(int32_t i = 0; i != nlon; ++i) {
				      if(latj>lat00 && latj<lat11) {
				         loni = lon[i];
                                         const float t0 = std::sin((latj-lat00)*pi)*ildiff;
					 const float t1 = height_sin*t0*t0;
					 const float t2 = std::cos(m*loni)+Amp2*std::cos(2.0f*loni);
					 zsurf[Ix2D(j,nlon,i)] = t1*t0;
					 if(uneven_sin) {
                                            /*
                                               ! uneven_sig = .true.; one mountain taller than the other by uneven_fac - half of domain taller;
	                                       ! this can only be used for Amp2=0; m=2; and height_sin > 0.
                                            */
					    if(loni>tpi4 && loni<spi4) {
                                               zsurf[Ix2D(j,nlon,i)] *= uneven_fac;
					    }
					 }
				      }
				 } 
			      }
		      }


		        __ATTR_ALWAYS_INLINE__
                        __ATTR_HOT__
                        __ATTR_ALIGN__(32)
			static inline
			void sinusoidal_topography(double * __restrict __ATTR_ALIGN__(64) lon,
			                           const int32_t nlon,
						   double * __restrict __ATTR_ALIGN__(64) lat,
						   const int32_t nlat,
						   double * __restrict __ATTR_ALIGN__(64) zsurf,
						   const double height_sin,
						   const double m,
						   const double Amp2,
						   const double uneven_fac,
						   const double deltalat,
						   const bool uneven_sin) {

                               if(__builtin_expect(nlon<=0,0) ||
			          __builtin_expect(nlat<=0,0)) {
                                  return;
			       }
			       if(__builtin_expect(height_sin==0.0f,0)) {
                                  return;
			       }
                               constexpr double pi   = 3.1415926535897932384626;
			       constexpr double tpi4 = 2.356194490192344928847;
			       constexpr double spi4 = 5.4977871437821381673096;
                               constexpr double tpi  = 6.2831853071795864769253; //!2.0*pi
			       constexpr double dtr  = 0.0174532925199432957692; //!tpi/360.
			       double lat00          = 25.0+deltalat;
			       lat00                = dtr*lat00;
			       double lat11          = 65.0+deltalat;
			       lat11                = dtr*lat11;
			       double ldiff          = lat11-lat00;
			       double ildiff         = 1.0/ldiff;
			       double latj,loni;
#if defined(__INTEL_COMPILER) || defined(__ICC)
                              assume_aligned(lon,64);
			      assume_aligned(lat,64);
			      assume_aligned(zsurf,64)
#elif defined(__GNUC__) && (!defined(__INTEL_COMPILER) || !defined(__ICC))
                              lon = (double*)__builtin_assume_aligned(lon,64);
			      lat = (double*)__builtin_assume_aligned(lat,64);
			      zsurf=(double*)__builtin_assume_aligned(zsurf,64);
#endif
#if defined(__INTEL_COMPILER) || defined(__ICC)
                              #pragma code_align(32)
			      #pragma prefetch lat:0:4
			      #pragma prefetch lat:1:16
			      #pragma prefetch lon:0:4
			      #pragma prefetch lon:1:16
#endif
                              for(int32_t j = 0; j != nlat; ++j) {
                                  latj = lat[j];
				  #pragma simd simdlen(8) linear(i:1) private(loni,t0,t1,t2)
				  for(int32_t i = 0; i != nlon; ++i) {
				      if(latj>lat00 && latj<lat11) {
				         loni = lon[i];
                                         const double t0 = std::sin((latj-lat00)*pi)*ildiff;
					 const double t1 = height_sin*t0*t0;
					 const double t2 = std::cos(m*loni)+Amp2*std::cos(2.0f*loni);
					 zsurf[Ix2D(j,nlon,i)] = t1*t0;
					 if(uneven_sin) {
                                            /*
                                               ! uneven_sig = .true.; one mountain taller than the other by uneven_fac - half of domain taller;
	                                       ! this can only be used for Amp2=0; m=2; and height_sin > 0.
                                            */
					    if(loni>tpi4 && loni<spi4) {
                                               zsurf[Ix2D(j,nlon,i)] *= uneven_fac;
					    }
					 }
				      }
				 } 
			      }
		      }


						   



  
} // gms
















#endif /*__GMS_IDEALIZED_TOPO_HPP__*/
