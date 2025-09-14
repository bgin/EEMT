
#ifndef __GMS_DYN_CONTAINERS_AVX_HPP__
#define __GMS_DYN_CONTAINERS_AVX_HPP__ 091220230249


namespace file_info {

     const unsigned int GMS_DYN_CONTAINERS_AVX_MAJOR = 1;
     const unsigned int GMS_DYN_CONTAINERS_AVX_MINOR = 1;
     const unsigned int GMS_DYN_CONTAINERS_AVX_MICRO = 0;
     const unsigned int GMS_DYN_CONTAINERS_AVX_FULLVER =
       1000U*GMS_DYN_CONTAINERS_AVX_MAJOR+100U*GMS_DYN_CONTAINERS_AVX_MINOR+
       10U*GMS_DYN_CONTAINERS_AVX_MICRO;
     const char * const GMS_DYN_CONTAINERS_AVX_CREATION_DATE = "09-12-2023 02:49 PM +00200 (SAT 09 DEC 2023 GMT+2)";
     const char * const GMS_DYN_CONTAINERS_AVX_BUILD_DATE    = __DATE__ " " __TIME__;
     const char * const GMS_DYN_CONTAINERS_AVX_SYNOPSIS      = "Dynamically allocated, 64-byte aligned dense AVX containers."

}





#include <cstdint>
#include "GMS_config"
#include "GMS_complex_ymm4r8.hpp"
#include "GMS_complex_ymm8r4.hpp"
#include "GMS_malloc.h"
#include "GMS_simd_memops.h"

// Enable non-temporal stores for this class only( used with free-standing operators)
// defaulted to 0.
#if !defined (USE_GMS_DYN_CONTAINERS_AVX_NT_STORES)
#define USE_GMS_DYN_CONTAINERS_AVX_NT_STORES 0
#endif


namespace gms {


           struct __ATTR_ALIGN__(64) DC3D_ymm4c8_t {
                      // Complmx electric field.
                      ymm4c8_t * __restrict mx
                      ymm4c8_t * __restrict my;
                      ymm4c8_t * __restrict mz;
                      std::size_t                      mnx;
                      std::size_t                      mny;
                      std::size_t                      mnz;
                      bool                             ismmap;
#if (USE_STRUCT_PADDING) == 1
                      PAD_TO(0,15)
#endif
                     inline DC3D_ymm4c8_t()  {
                          
                          this->mnx  = 0ULL;
                          this->mny  = 0ULL;
                          this->mnz  = 0ULL;
                          this->mx  = NULL;
                          this->my  = NULL;
                          this->mz  = NULL;
                      } 
                          
                     inline DC3D_ymm4c8_t(const std::size_t _mnx,
                                   const std::size_t _mny,
                                   const std::size_t _mnz) {
                          using namespace gms::common;
                          this->mnx = _mnx;
                          this->mny = _mny;
                          this->mnz = _mnz;
                          allocate();
                          this->ismmap = false;
                      }  
                      
                     inline DC3D_ymm4c8_t(const std::size_t _mnx,
                                   const std::size_t _mny,
                                   const std::size_t _mnz,
                                   const int32_t prot,
                                   const int32_t flags,
                                   const int32_t fd,
                                   const int32_t offset,
                                   const int32_t fsize) {
                             using namespace gms::common;
                             this->mnx = _mnx;
                             this->mny = _mny;
                             this->mnz = _mnz;
                             switch (fsize) {
                                 case:0
                                      this->mx = (ymm4c8_t*)
                                                 gms_mmap_4KiB<ymm4c8_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm4c8_t*)
                                                 gms_mmap_4KiB<ymm4c8_t>(this->mny,prot,flags,fd,offset);
                                      this->mz = (ymm4c8_t*)
                                                 gms_mmap_4KiB<ymm4c8_t>(this->mnz,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:1
                                      this->mx = (ymm4c8_t*)
                                                 gms_mmap_2MiB<ymm4c8_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm4c8_t*)
                                                 gms_mmap_2MiB<ymm4c8_t>(this->mny,prot,flags,fd,offset);
                                      this->mz = (ymm4c8_t*)
                                                 gms_mmap_2MiB<ymm4c8_t>(this->mnz,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:2
                                      this->mx = (ymm4c8_t*)
                                                 gms_mmap_1GiB<ymm4c8_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm4c8_t*)
                                                 gms_mmap_1GiB<ymm4c8_t>(this->mny,prot,flags,fd,offset);
                                      this->mz = (ymm4c8_t*)
                                                 gms_mmap_1GiB<ymm4c8_t>(this->mnz,prot,flags,fd,offset); 
                                      this->ismmap = true;
                                 break;
                                 default :
                                      allocate();
                                      this->ismmap = false; // do not call mmap!!                        
                             }          
                     }
                      
                                                 
                            
                      
                     inline DC3D_ymm4c8_t(const std::size_t _mnx,
                                          const std::size_t _mny,
                                          const std::size_t _mnz,
                                          const  ymm4c8_t * __restrict m_x,
                                          const  ymm4c8_t * __restrict m_y,
                                          const  ymm4c8_t * __restrict m_z) {
                          using namespace gms::common;
                          this->mnx = _mnx;
                          this->mny = _mny;
                          this->mnz = _mnz;
                          allocate();
                          this->ismmap = false;
#if (USE_GMS_DYN_CONTAINERS_AVX_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_uncached_memmove(&this->my[0],&m_y[0],this->mny);
	                  avx512_uncached_memmove(&this->mz[0],&m_z[0],this->mnz);
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_cached_memmove(&this->my[0],&m_y[0],this->mny);
	                  avx512_cached_memmove(&this->mz[0],&m_z[0],this->mnz);
#endif
                   }  
                   
                    inline  DC3D_ymm4c8_t(DC3D_ymm4c8_t && rhs) {
                          
                          this->mnx = rhs.mnx;
                          this->mny = rhs.mny;
                          this->mnz = rhs.mnz;
                          this->mx   = &rhs.mx[0];
                          this->my   = &rhs.my[0];
                          this->mz   = &rhs.mz[0];
                          rhs.mnx    = 0ULL;
                          rhs.mny    = 0ULL;
                          rhs.mnz    = 0ULL;
                          rhs.mx     = NULL;
                          rhs.my     = NULL;
                          rhs.mz     = NULL;
                      }
                                 
                     DC3D_ymm4c8_t(const DC3D_ymm4c8_t &)             = delete;
                      
                     inline ~DC3D_ymm4c8_t() {
                      
                          using namespace gms::common;
                          if(this->issmap) {
                             gms_unmap<ymm4c8_t>(this->mx,this->mnx);
                             gms_unmap<ymm4c8_t>(this->my,this->mny);
                             gms_unmap<ymm4c8_t>(this->mz,this->mnz);
                          }
                          else {
                              gms_mm_free(this->mx);
                              gms_mm_free(this->my);
                              gms_mm_free(this->mz);
                          }
                      }
                      
                     DC3D_ymm4c8_t & operator=(const DC3D_ymm4c8_t &) = delete;
                      
                     inline DC3D_ymm4c8_t & operator=(DC3D_ymm4c8_t &&rhs) {
                           using namespace gms::common;
                           if(this==&rhs) return (*this);
                           if(this->ismmap) {
                             gms_unmap<ymm4c8_t>(this->mx,this->mnx);
                             gms_unmap<ymm4c8_t>(this->my,this->mny);
                             gms_unmap<ymm4c8_t>(this->mz,this->mnz);
                           }
                           else {
                             gms_mm_free(this->mx);
                             gms_mm_free(this->my);
                             gms_mm_free(this->mz);
                           }
                           this->mnx   = rhs.mnx;
                           this->mny   = rhs.mny;
                           this->mnz   = rhs.mnz;
                           this->mx    = &rhs.mx[0];
                           this->my    = &rhs.my[0];
                           this->mz    = &rhs.mz[0];
                           rhs.mnx     = 0ULL;
                           rhs.mny     = 0ULL;
                           rhs.mnz     = 0ULL;
                           rhs.mx      = NULL;
                           rhs.my      = NULL;
                           rhs.mz      = NULL;
                           return (*this);
                      }
                      
                      inline void allocate() {
                          using namespace gms::common;
                          this->mx  = (ymm4c8_t*)
                                         gms_mm_malloc( sizeof(ymm4c8_t)*this->mnx,64ULL);
                          this->my  = (ymm4c8_t*)
                                         gms_mm_malloc( sizeof(ymm4c8_t)*this->mny,64ULL);
                          this->mz  = (ymm4c8_t*)
                                         gms_mm_malloc( sizeof(ymm4c8_t)*this->mny,64ULL);
                      }
                      
                     
                    
              };
              
              
              struct __ATTR_ALIGN__(64) DC2D_ymm4c8_t {
                     
                      ymm4c8_t * __restrict mx
                      ymm4c8_t * __restrict my;
                      std::size_t                      mnx;
                      std::size_t                      mny;
                      bool                             ismmap;
#if (USE_STRUCT_PADDING) == 1
                      PAD_TO(0,23)
#endif
                     inline DC2D_ymm4c8_t()  {
                          
                          this->mnx  = 0ULL;
                          this->mny  = 0ULL;
                          this->mx  = NULL;
                          this->my  = NULL;
                    } 
                          
                     inline DC2D_ymm4c8_t(const std::size_t _mnx,
                                   const std::size_t _mny) {
                                   
                          using namespace gms::common;
                          this->mnx = _mnx;
                          this->mny = _mny;
                          allocate();
                          this->ismmap = false;
                      }  
                      
                     inline DC2D_ymm4c8_t(const std::size_t _mnx,
                                   const std::size_t _mny,
                                   const int32_t prot,
                                   const int32_t flags,
                                   const int32_t fd,
                                   const int32_t offset,
                                   const int32_t fsize) {
                             using namespace gms::common;
                             this->mnx = _mnx;
                             this->mny = _mny;
                              switch (fsize) {
                                 case:0
                                      this->mx = (ymm4c8_t*)
                                                 gms_mmap_4KiB<ymm4c8_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm4c8_t*)
                                                 gms_mmap_4KiB<ymm4c8_t>(this->mny,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:1
                                      this->mx = (ymm4c8_t*)
                                                 gms_mmap_2MiB<ymm4c8_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm4c8_t*)
                                                 gms_mmap_2MiB<ymm4c8_t>(this->mny,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:2
                                      this->mx = (ymm4c8_t*)
                                                 gms_mmap_1GiB<ymm4c8_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm4c8_t*)
                                                 gms_mmap_1GiB<ymm4c8_t>(this->mny,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 default :
                                      allocate();
                                      this->ismmap = false; // do not call mmap!!                        
                             }          
                     }
                      
                                                 
                            
                      
                     inline DC2D_ymm4c8_t(const std::size_t _mnx,
                                          const std::size_t _mny,
                                          const  ymm4c8_t * __restrict m_x,
                                          const  ymm4c8_t * __restrict m_y) {
                                          
                          using namespace gms::common;
                          this->mnx = _mnx;
                          this->mny = _mny;
                          allocate();
                          this->ismmap = false;
#if (USE_GMS_DYN_CONTAINERS_AVX_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_uncached_memmove(&this->my[0],&m_y[0],this->mny);
	                  
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_cached_memmove(&this->my[0],&m_y[0],this->mny);
	               
#endif
                   }  
                   
                    inline  DC2D_ymm4c8_t(DC2D_ymm4c8_t && rhs) {
                          
                          this->mnx = rhs.mnx;
                          this->mny = rhs.mny;
                          this->mx   = &rhs.mx[0];
                          this->my   = &rhs.my[0];
                          rhs.mnx    = 0ULL;
                          rhs.mny    = 0ULL;
                          rhs.mx     = NULL;
                          rhs.my     = NULL;
                        
                      }
                                 
                     DC2D_ymm4c8_t(const DC2D_ymm4c8_t &)             = delete;
                      
                     inline ~DC2D_ymm4c8_t() {
                      
                          using namespace gms::common;
                          if(this->issmap) {
                             gms_unmap<ymm4c8_t>(this->mx,this->mnx);
                             gms_unmap<ymm4c8_t>(this->my,this->mny);
                             
                          }
                          else {
                              gms_mm_free(this->mx);
                              gms_mm_free(this->my);
                              
                          }
                      }
                      
                     DC2D_ymm4c8_t & operator=(const DC2D_ymm4c8_t &) = delete;
                      
                     inline DC2D_ymm4c8_t & operator=(DC2D_ymm4c8_t &&rhs) {
                           using namespace gms::common;
                           if(this==&rhs) return (*this);
                           if(this->ismmap) {
                             gms_unmap<ymm4c8_t>(this->mx,this->mnx);
                             gms_unmap<ymm4c8_t>(this->my,this->mny);
                            
                           }
                           else {
                             gms_mm_free(this->mx);
                             gms_mm_free(this->my);
                           
                           }
                           this->mnx   = rhs.mnx;
                           this->mny   = rhs.mny;
                           this->mx    = &rhs.mx[0];
                           this->my    = &rhs.my[0];
                           rhs.mnx     = 0ULL;
                           rhs.mny     = 0ULL;
                           rhs.mx      = NULL;
                           rhs.my      = NULL;
                           return (*this);
                      }
                      
                      inline void allocate() {
                          using namespace gms::common;
                          this->mx  = (ymm4c8_t*)
                                         gms_mm_malloc( sizeof(ymm4c8_t)*this->mnx,64ULL);
                          this->my  = (ymm4c8_t*)
                                         gms_mm_malloc( sizeof(ymm4c8_t)*this->mny,64ULL);
                    }
                      
                     
                    
              };
              
              
               struct __ATTR_ALIGN__(64) DC1D_ymm4c8_t {
                     
                      ymm4c8_t * __restrict mx
                      std::size_t                      mnx;
                      bool                             ismmap;
#if (USE_STRUCT_PADDING) == 1
                      PAD_TO(0,31)
#endif
                     inline DC1D_ymm4c8_t()  {
                          
                          this->mnx  = 0ULL;
                          this->mx  = NULL;
                         
                    } 
                          
                     inline explicit DC1D_ymm4c8_t(const std::size_t _mnx) {
                                 
                          using namespace gms::common;
                          this->mnx = _mnx;
                          allocate();
                          this->ismmap = false;
                      }  
                      
                     inline DC1D_ymm4c8_t(const std::size_t _mnx,
                                   const int32_t prot,
                                   const int32_t flags,
                                   const int32_t fd,
                                   const int32_t offset,
                                   const int32_t fsize) {
                             using namespace gms::common;
                             this->mnx = _mnx;
                             switch (fsize) {
                                 case:0
                                      this->mx = (ymm4c8_t*)
                                                 gms_mmap_4KiB<ymm4c8_t>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:1
                                      this->mx = (ymm4c8_t*)
                                                 gms_mmap_2MiB<ymm4c8_t>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:2
                                      this->mx = (ymm4c8_t*)
                                                 gms_mmap_1GiB<ymm4c8_t>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 default :
                                      allocate();
                                      this->ismmap = false; // do not call mmap!!                        
                             }          
                     }
                      
                                                 
                            
                      
                     inline DC1D_ymm4c8_t(const std::size_t _mnx,
                                          const  ymm4c8_t * __restrict m_x) {
                                     
                          using namespace gms::common;
                          this->mnx = _mnx;
                          allocate();
                          this->ismmap = false;
#if (USE_GMS_DYN_CONTAINERS_AVX_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                 
	                  
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                 
	               
#endif
                   }  
                   
                    inline  DC1D_ymm4c8_t(DC1D_ymm4c8_t && rhs) {
                          
                          this->mnx = rhs.mnx;
                          this->mx   = &rhs.mx[0];
                          rhs.mnx    = 0ULL;
                          rhs.mx     = NULL;
                                                 
                      }
                                 
                     DC1D_ymm4c8_t(const DC1D_ymm4c8_t &)             = delete;
                      
                     inline ~DC1D_ymm4c8_t() {
                      
                          using namespace gms::common;
                          if(this->issmap) 
                             gms_unmap<ymm4c8_t>(this->mx,this->mnx);
                          else 
                              gms_mm_free(this->mx);   
                     }        
                          
                                                 
                                  
                     DC1D_ymm4c8_t & operator=(const DC1D_ymm4c8_t &) = delete;
                      
                     inline DC1D_ymm4c8_t & operator=(DC1D_ymm4c8_t &&rhs) {
                           using namespace gms::common;
                           if(this==&rhs) return (*this);
                           if(this->ismmap) 
                              gms_unmap<ymm4c8_t>(this->mx,this->mnx);
                           else 
                             gms_mm_free(this->mx); 
                                                                                                                         
                           this->mnx   = rhs.mnx;
                           this->mx    = &rhs.mx[0];
                           rhs.mnx     = 0ULL;
                           rhs.mx      = NULL;
                           return (*this);
                      }
                      
                      inline void allocate() {
                          using namespace gms::common;
                          this->mx  = (ymm4c8_t*)
                                         gms_mm_malloc( sizeof(ymm4c8_t)*this->mnx,64ULL);
                         
                    }
                      
                     
                    
              };
              
              
          //////////////////////////////////////////////////////////////////////////////////////////////
          
           struct __ATTR_ALIGN__(64) DC3D_ymm8c4_t {
                      
                      ymm8c4_t * __restrict mx
                      ymm8c4_t * __restrict my;
                      ymm8c4_t * __restrict mz;
                      std::size_t                      mnx;
                      std::size_t                      mny;
                      std::size_t                      mnz;
                      bool                             ismmap;
#if (USE_STRUCT_PADDING) == 1
                      PAD_TO(0,15)
#endif
                     inline DC3D_ymm8c4_t()  {
                          
                          this->mnx  = 0ULL;
                          this->mny  = 0ULL;
                          this->mnz  = 0ULL;
                          this->mx  = NULL;
                          this->my  = NULL;
                          this->mz  = NULL;
                      } 
                          
                     inline DC3D_ymm8c4_t(const std::size_t _mnx,
                                   const std::size_t _mny,
                                   const std::size_t _mnz) {
                          using namespace gms::common;
                          this->mnx = _mnx;
                          this->mny = _mny;
                          this->mnz = _mnz;
                          allocate();
                          this->ismmap = false;
                      }  
                      
                     inline DC3D_ymm8c4_t(const std::size_t _mnx,
                                   const std::size_t _mny,
                                   const std::size_t _mnz,
                                   const int32_t prot,
                                   const int32_t flags,
                                   const int32_t fd,
                                   const int32_t offset,
                                   const int32_t fsize) {
                             using namespace gms::common;
                             this->mnx = _mnx;
                             this->mny = _mny;
                             this->mnz = _mnz;
                             switch (fsize) {
                                 case:0
                                      this->mx = (ymm8c4_t*)
                                                 gms_mmap_4KiB<ymm8c4_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm8c4_t*)
                                                 gms_mmap_4KiB<ymm8c4_t>(this->mny,prot,flags,fd,offset);
                                      this->mz = (ymm8c4_t*)
                                                 gms_mmap_4KiB<ymm8c4_t>(this->mnz,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:1
                                      this->mx = (ymm8c4_t*)
                                                 gms_mmap_2MiB<ymm8c4_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm8c4_t*)
                                                 gms_mmap_2MiB<ymm8c4_t>(this->mny,prot,flags,fd,offset);
                                      this->mz = (ymm8c4_t*)
                                                 gms_mmap_2MiB<ymm8c4_t>(this->mnz,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:2
                                      this->mx = (ymm8c4_t*)
                                                 gms_mmap_1GiB<ymm8c4_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm8c4_t*)
                                                 gms_mmap_1GiB<ymm8c4_t>(this->mny,prot,flags,fd,offset);
                                      this->mz = (ymm8c4_t*)
                                                 gms_mmap_1GiB<ymm8c4_t>(this->mnz,prot,flags,fd,offset); 
                                      this->ismmap = true;
                                 break;
                                 default :
                                      allocate();
                                      this->ismmap = false; // do not call mmap!!                        
                             }          
                     }
                      
                                                 
                            
                      
                     inline DC3D_ymm8c4_t(const std::size_t _mnx,
                                          const std::size_t _mny,
                                          const std::size_t _mnz,
                                          const  ymm8c4_t * __restrict m_x,
                                          const  ymm8c4_t * __restrict m_y,
                                          const  ymm8c4_t * __restrict m_z) {
                          using namespace gms::common;
                          this->mnx = _mnx;
                          this->mny = _mny;
                          this->mnz = _mnz;
                          allocate();
                          this->ismmap = false;
#if (USE_GMS_DYN_CONTAINERS_AVX_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_uncached_memmove(&this->my[0],&m_y[0],this->mny);
	                  avx512_uncached_memmove(&this->mz[0],&m_z[0],this->mnz);
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_cached_memmove(&this->my[0],&m_y[0],this->mny);
	                  avx512_cached_memmove(&this->mz[0],&m_z[0],this->mnz);
#endif
                   }  
                   
                    inline  DC3D_ymm8c4_t(DC3D_ymm8c4_t && rhs) {
                          
                          this->mnx = rhs.mnx;
                          this->mny = rhs.mny;
                          this->mnz = rhs.mnz;
                          this->mx   = &rhs.mx[0];
                          this->my   = &rhs.my[0];
                          this->mz   = &rhs.mz[0];
                          rhs.mnx    = 0ULL;
                          rhs.mny    = 0ULL;
                          rhs.mnz    = 0ULL;
                          rhs.mx     = NULL;
                          rhs.my     = NULL;
                          rhs.mz     = NULL;
                      }
                                 
                     DC3D_ymm8c4_t(const DC3D_ymm8c4_t &)             = delete;
                      
                     inline ~DC3D_ymm8c4_t() {
                      
                          using namespace gms::common;
                          if(this->issmap) {
                             gms_unmap<ymm8c4_t>(this->mx,this->mnx);
                             gms_unmap<ymm8c4_t>(this->my,this->mny);
                             gms_unmap<ymm8c4_t>(this->mz,this->mnz);
                          }
                          else {
                              gms_mm_free(this->mx);
                              gms_mm_free(this->my);
                              gms_mm_free(this->mz);
                          }
                      }
                      
                     DC3D_ymm8c4_t & operator=(const DC3D_ymm8c4_t &) = delete;
                      
                     inline DC3D_ymm8c4_t & operator=(DC3D_ymm8c4_t &&rhs) {
                           using namespace gms::common;
                           if(this==&rhs) return (*this);
                           if(this->ismmap) {
                             gms_unmap<ymm8c4_t>(this->mx,this->mnx);
                             gms_unmap<ymm8c4_t>(this->my,this->mny);
                             gms_unmap<ymm8c4_t>(this->mz,this->mnz);
                           }
                           else {
                             gms_mm_free(this->mx);
                             gms_mm_free(this->my);
                             gms_mm_free(this->mz);
                           }
                           this->mnx   = rhs.mnx;
                           this->mny   = rhs.mny;
                           this->mnz   = rhs.mnz;
                           this->mx    = &rhs.mx[0];
                           this->my    = &rhs.my[0];
                           this->mz    = &rhs.mz[0];
                           rhs.mnx     = 0ULL;
                           rhs.mny     = 0ULL;
                           rhs.mnz     = 0ULL;
                           rhs.mx      = NULL;
                           rhs.my      = NULL;
                           rhs.mz      = NULL;
                           return (*this);
                      }
                      
                      inline void allocate() {
                          using namespace gms::common;
                          this->mx  = (ymm8c4_t*)
                                         gms_mm_malloc( sizeof(ymm8c4_t)*this->mnx,64ULL);
                          this->my  = (ymm8c4_t*)
                                         gms_mm_malloc( sizeof(ymm8c4_t)*this->mny,64ULL);
                          this->mz  = (ymm8c4_t*)
                                         gms_mm_malloc( sizeof(ymm8c4_t)*this->mny,64ULL);
                      }
                      
                     
                    
              };
              
              
              
             struct __ATTR_ALIGN__(64) DC2D_ymm8c4_t {
                     
                      ymm8c4_t * __restrict mx
                      ymm8c4_t * __restrict my;
                      std::size_t                      mnx;
                      std::size_t                      mny;
                      bool                             ismmap;
#if (USE_STRUCT_PADDING) == 1
                      PAD_TO(0,23)
#endif
                     inline DC2D_ymm8c4_t()  {
                          
                          this->mnx  = 0ULL;
                          this->mny  = 0ULL;
                          this->mx  = NULL;
                          this->my  = NULL;
                    } 
                          
                     inline DC2D_ymm8c4_t(const std::size_t _mnx,
                                          const std::size_t _mny) {
                                   
                          using namespace gms::common;
                          this->mnx = _mnx;
                          this->mny = _mny;
                          allocate();
                          this->ismmap = false;
                      }  
                      
                     inline DC2D_ymm8c4_t(const std::size_t _mnx,
                                   const std::size_t _mny,
                                   const int32_t prot,
                                   const int32_t flags,
                                   const int32_t fd,
                                   const int32_t offset,
                                   const int32_t fsize) {
                             using namespace gms::common;
                             this->mnx = _mnx;
                             this->mny = _mny;
                              switch (fsize) {
                                 case:0
                                      this->mx = (ymm8c4_t*)
                                                 gms_mmap_4KiB<ymm8c4_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm8c4_t*)
                                                 gms_mmap_4KiB<ymm8c4_t>(this->mny,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:1
                                      this->mx = (ymm8c4_t*)
                                                 gms_mmap_2MiB<ymm8c4_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm8c4_t*)
                                                 gms_mmap_2MiB<ymm8c4_t>(this->mny,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:2
                                      this->mx = (ymm8c4_t*)
                                                 gms_mmap_1GiB<ymm8c4_t>(this->mnx,prot,flags,fd,offset);
                                      this->my = (ymm4c8_t*)
                                                 gms_mmap_1GiB<ymm8c4_t>(this->mny,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 default :
                                      allocate();
                                      this->ismmap = false; // do not call mmap!!                        
                             }          
                     }
                      
                                                 
                            
                      
                     inline DC2D_ymm8c4_t(const std::size_t _mnx,
                                          const std::size_t _mny,
                                          const  ymm8c4_t * __restrict m_x,
                                          const  ymm8c4_t * __restrict m_y) {
                                          
                          using namespace gms::common;
                          this->mnx = _mnx;
                          this->mny = _mny;
                          allocate();
                          this->ismmap = false;
#if (USE_GMS_DYN_CONTAINERS_AVX_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_uncached_memmove(&this->my[0],&m_y[0],this->mny);
	                  
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                  avx512_cached_memmove(&this->my[0],&m_y[0],this->mny);
	               
#endif
                   }  
                   
                    inline  DC2D_ymm8c4_t(DC2D_ymm8c4_t && rhs) {
                          
                          this->mnx = rhs.mnx;
                          this->mny = rhs.mny;
                          this->mx   = &rhs.mx[0];
                          this->my   = &rhs.my[0];
                          rhs.mnx    = 0ULL;
                          rhs.mny    = 0ULL;
                          rhs.mx     = NULL;
                          rhs.my     = NULL;
                        
                      }
                                 
                     DC2D_ymm8c4_t(const DC2D_ymm8c4_t &)             = delete;
                      
                     inline ~DC2D_ymm8c4_t() {
                      
                          using namespace gms::common;
                          if(this->issmap) {
                             gms_unmap<ymm8c4_t>(this->mx,this->mnx);
                             gms_unmap<ymm8c4_t>(this->my,this->mny);
                             
                          }
                          else {
                              gms_mm_free(this->mx);
                              gms_mm_free(this->my);
                              
                          }
                      }
                      
                     DC2D_ymm8c4_t & operator=(const DC2D_ymm8c4_t &) = delete;
                      
                     inline DC2D_ymm8c4_t & operator=(DC2D_ymm8c4_t &&rhs) {
                           using namespace gms::common;
                           if(this==&rhs) return (*this);
                           if(this->ismmap) {
                             gms_unmap<ymm8c4_t>(this->mx,this->mnx);
                             gms_unmap<ymm8c4_t>(this->my,this->mny);
                            
                           }
                           else {
                             gms_mm_free(this->mx);
                             gms_mm_free(this->my);
                           
                           }
                           this->mnx   = rhs.mnx;
                           this->mny   = rhs.mny;
                           this->mx    = &rhs.mx[0];
                           this->my    = &rhs.my[0];
                           rhs.mnx     = 0ULL;
                           rhs.mny     = 0ULL;
                           rhs.mx      = NULL;
                           rhs.my      = NULL;
                           return (*this);
                      }
                      
                      inline void allocate() {
                          using namespace gms::common;
                          this->mx  = (ymm8c4_t*)
                                         gms_mm_malloc( sizeof(ymm8c4_t)*this->mnx,64ULL);
                          this->my  = (ymm8c4_t*)
                                         gms_mm_malloc( sizeof(ymm8c4_t)*this->mny,64ULL);
                    }
                      
                     
                    
              }; 
              
              
              struct __ATTR_ALIGN__(64) DC1D_ymm8c4_t {
                     
                      ymm8c4_t * __restrict mx
                      std::size_t                      mnx;
                      bool                             ismmap;
#if (USE_STRUCT_PADDING) == 1
                      PAD_TO(0,31)
#endif
                     inline DC1D_ymm8c4_t()  {
                          
                          this->mnx  = 0ULL;
                          this->mx  = NULL;
                         
                    } 
                          
                     inline explicit DC1D_ymm8c4_t(const std::size_t _mnx) {
                                 
                          using namespace gms::common;
                          this->mnx = _mnx;
                          allocate();
                          this->ismmap = false;
                      }  
                      
                     inline DC1D_ymm8c4_t(const std::size_t _mnx,
                                   const int32_t prot,
                                   const int32_t flags,
                                   const int32_t fd,
                                   const int32_t offset,
                                   const int32_t fsize) {
                             using namespace gms::common;
                             this->mnx = _mnx;
                             switch (fsize) {
                                 case:0
                                      this->mx = (ymm8c4_t*)
                                                 gms_mmap_4KiB<ymm8c4_t>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:1
                                      this->mx = (ymm8c4_t*)
                                                 gms_mmap_2MiB<ymm8c4_t>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:2
                                      this->mx = (ymm8c4_t*)
                                                 gms_mmap_1GiB<ymm8c4_t>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 default :
                                      allocate();
                                      this->ismmap = false; // do not call mmap!!                        
                             }          
                     }
                      
                                                 
                            
                      
                     inline DC1D_ymm8c4_t(const std::size_t _mnx,
                                          const  ymm8c4_t * __restrict m_x) {
                                     
                          using namespace gms::common;
                          this->mnx = _mnx;
                          allocate();
                          this->ismmap = false;
#if (USE_GMS_DYN_CONTAINERS_AVX_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                 
	                  
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                 
	               
#endif
                   }  
                   
                    inline  DC1D_ymm8c4_t(DC1D_ymm8c4_t && rhs) {
                          
                          this->mnx = rhs.mnx;
                          this->mx   = &rhs.mx[0];
                          rhs.mnx    = 0ULL;
                          rhs.mx     = NULL;
                                                 
                      }
                                 
                     DC1D_ymm8c4_t(const DC1D_ymm8c4_t &)             = delete;
                      
                     inline ~DC1D_ymm8c4_t() {
                      
                          using namespace gms::common;
                          if(this->issmap) 
                             gms_unmap<ymm8c4_t>(this->mx,this->mnx);
                          else 
                              gms_mm_free(this->mx);   
                     }        
                          
                                                 
                                  
                     DC1D_ymm8c4_t & operator=(const DC1D_ymm8c4_t &) = delete;
                      
                     inline DC1D_ymm8c4_t & operator=(DC1D_ymm8c4_t &&rhs) {
                           using namespace gms::common;
                           if(this==&rhs) return (*this);
                           if(this->ismmap) 
                              gms_unmap<ymm8c4_t>(this->mx,this->mnx);
                           else 
                             gms_mm_free(this->mx); 
                                                                                                                         
                           this->mnx   = rhs.mnx;
                           this->mx    = &rhs.mx[0];
                           rhs.mnx     = 0ULL;
                           rhs.mx      = NULL;
                           return (*this);
                      }
                      
                      inline void allocate() {
                          using namespace gms::common;
                          this->mx  = (ymm8c4_t*)
                                         gms_mm_malloc( sizeof(ymm8c4_t)*this->mnx,64ULL);
                         
                    }
                      
                     
                    
              };
                   
              
                struct __ATTR_ALIGN__(64) DC1D_m256_t {
                     
                      __m256 * __restrict              mx
                      std::size_t                      mnx;
                      bool                             ismmap;
#if (USE_STRUCT_PADDING) == 1
                      PAD_TO(0,31)
#endif
                     inline DC1D_m256_t()  {
                          
                          this->mnx  = 0ULL;
                          this->mx  = NULL;
                         
                    } 
                          
                     inline explicit DC1D_m256_t(const std::size_t _mnx) {
                                 
                          using namespace gms::common;
                          this->mnx = _mnx;
                          allocate();
                          this->ismmap = false;
                      }  
                      
                     inline DC1D_m256_t(const std::size_t _mnx,
                                   const int32_t prot,
                                   const int32_t flags,
                                   const int32_t fd,
                                   const int32_t offset,
                                   const int32_t fsize) {
                             using namespace gms::common;
                             this->mnx = _mnx;
                             switch (fsize) {
                                 case:0
                                      this->mx = (__m256*)
                                                 gms_mmap_4KiB<__m256>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:1
                                      this->mx = (__m256*)
                                                 gms_mmap_2MiB<__m256>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:2
                                      this->mx = (__m256*)
                                                 gms_mmap_1GiB<__m256>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 default :
                                      allocate();
                                      this->ismmap = false; // do not call mmap!!                        
                             }          
                     }
                      
                                                 
                            
                      
                     inline DC1D_m256_t(const std::size_t _mnx,
                                          const  __m256 * __restrict m_x) {
                                     
                          using namespace gms::common;
                          this->mnx = _mnx;
                          allocate();
                          this->ismmap = false;
#if (USE_GMS_DYN_CONTAINERS_AVX_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                 
	                  
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                 
	               
#endif
                   }  
                   
                    inline  DC1D_m256_t(DC1D_m256_t && rhs) {
                          
                          this->mnx = rhs.mnx;
                          this->mx   = &rhs.mx[0];
                          rhs.mnx    = 0ULL;
                          rhs.mx     = NULL;
                                                 
                      }
                                 
                     DC1D_m256_t(const DC1D_m256_t &)             = delete;
                      
                     inline ~DC1D_m256_t() {
                      
                          using namespace gms::common;
                          if(this->issmap) 
                             gms_unmap<__m256>(this->mx,this->mnx);
                          else 
                              gms_mm_free(this->mx);   
                     }        
                          
                                                 
                                  
                     DC1D_m256_t & operator=(const DC1D_m256_t &) = delete;
                      
                     inline DC1D_m256_t & operator=(DC1D_m256_t &&rhs) {
                           using namespace gms::common;
                           if(this==&rhs) return (*this);
                           if(this->ismmap) 
                              gms_unmap<__m256>(this->mx,this->mnx);
                           else 
                             gms_mm_free(this->mx); 
                                                                                                                         
                           this->mnx   = rhs.mnx;
                           this->mx    = &rhs.mx[0];
                           rhs.mnx     = 0ULL;
                           rhs.mx      = NULL;
                           return (*this);
                      }
                      
                      inline void allocate() {
                          using namespace gms::common;
                          this->mx  = (__m256*)
                                         gms_mm_malloc( sizeof(__m256)*this->mnx,64ULL);
                         
                    }
                      
                     
                    
              };
              
              
              
                 struct __ATTR_ALIGN__(64) DC1D_m256d_t {
                     
                      __m256d * __restrict              mx
                      std::size_t                      mnx;
                      bool                             ismmap;
#if (USE_STRUCT_PADDING) == 1
                      PAD_TO(0,31)
#endif
                     inline DC1D_m256d_t()  {
                          
                          this->mnx  = 0ULL;
                          this->mx  = NULL;
                         
                    } 
                          
                     inline explicit DC1D_m256d_t(const std::size_t _mnx) {
                                 
                          using namespace gms::common;
                          this->mnx = _mnx;
                          allocate();
                          this->ismmap = false;
                      }  
                      
                     inline DC1D_m256d_t(const std::size_t _mnx,
                                   const int32_t prot,
                                   const int32_t flags,
                                   const int32_t fd,
                                   const int32_t offset,
                                   const int32_t fsize) {
                             using namespace gms::common;
                             this->mnx = _mnx;
                             switch (fsize) {
                                 case:0
                                      this->mx = (__m256d*)
                                                 gms_mmap_4KiB<__m256d>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:1
                                      this->mx = (__m256d*)
                                                 gms_mmap_2MiB<__m256d>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 case:2
                                      this->mx = (__m256d*)
                                                 gms_mmap_1GiB<__m256d>(this->mnx,prot,flags,fd,offset);
                                      this->ismmap = true;
                                 break;
                                 default :
                                      allocate();
                                      this->ismmap = false; // do not call mmap!!                        
                             }          
                     }
                      
                                                 
                            
                      
                     inline DC1D_m256d_t(const std::size_t _mnx,
                                          const  __m256d * __restrict m_x) {
                                     
                          using namespace gms::common;
                          this->mnx = _mnx;
                          allocate();
                          this->ismmap = false;
#if (USE_GMS_DYN_CONTAINERS_AVX_NT_STORES)  == 1
	                  avx512_uncached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                 
	                  
#else
	                  avx512_cached_memmove(&this->mx[0],&m_x[0],this->mnx);
	                 
	               
#endif
                   }  
                   
                    inline  DC1D_m256d_t(DC1D_m256d_t && rhs) {
                          
                          this->mnx = rhs.mnx;
                          this->mx   = &rhs.mx[0];
                          rhs.mnx    = 0ULL;
                          rhs.mx     = NULL;
                                                 
                      }
                                 
                     DC1D_m256d_t(const DC1D_m256d_t &)             = delete;
                      
                     inline ~DC1D_m256d_t() {
                      
                          using namespace gms::common;
                          if(this->issmap) 
                             gms_unmap<__m256d>(this->mx,this->mnx);
                          else 
                              gms_mm_free(this->mx);   
                     }        
                          
                                                 
                                  
                     DC1D_m256d_t & operator=(const DC1D_m256d_t &) = delete;
                      
                     inline DC1D_m256d_t & operator=(DC1D_m256d_t &&rhs) {
                           using namespace gms::common;
                           if(this==&rhs) return (*this);
                           if(this->ismmap) 
                              gms_unmap<__m256d>(this->mx,this->mnx);
                           else 
                             gms_mm_free(this->mx); 
                                                                                                                         
                           this->mnx   = rhs.mnx;
                           this->mx    = &rhs.mx[0];
                           rhs.mnx     = 0ULL;
                           rhs.mx      = NULL;
                           return (*this);
                      }
                      
                      inline void allocate() {
                          using namespace gms::common;
                          this->mx  = (__m256d*)
                                         gms_mm_malloc( sizeof(__m256d)*this->mnx,64ULL);
                         
                    }
                      
                     
                    
              };
              
               
            
              
              
           
           
           
           
              
              

              
              




} //gms

















#endif /*__GMS_DYN_CONTAINERS_AVX_HPP__*/
