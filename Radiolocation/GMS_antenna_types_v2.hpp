
#ifndef __GMS_ANTENNA_TYPES_V2_HPP__
#define __GMS_ANTENNA_TYPES_V2_HPP__


namespace file_info {

     const unsigned int GMS_ANTENNA_TYPES_V2_MAJOR = 1;
     const unsigned int GMS_ANTENNA_TYPES_V2_MINOR = 1;
     const unsigned int GMS_ANTENNA_TYPES_V2_MICRO = 0;
     const unsigned int GMS_ANTENNA_TYPES_V2_FULLVER =
       1000U*GMS_ANTENNA_TYPES_V2_MAJOR+100U*GMS_ANTENNA_TYPES_V2_MINOR+
       10U*GMS_ANTENNA_TYPES_V2_MICRO;
     const char * const GMS_ANTENNA_TYPES_V2_CREATION_DATE = "24-11-2022 16:08 +00200 (THR 24 NOV 2022 GMT+2)";
     const char * const GMS_ANTENNA_TYPES_V2_BUILD_DATE    = __DATE__ " " __TIME__;
     const char * const GMS_ANTENNA_TYPES_V2_SYNOPSIS      = "Antenna common data types."

}


/*
 Purpose:
 !                        Derived data types for 'antenna_sensor' module implementation.
 !                        Various characteristics of different antenna types  
 !                        Based mainly on book titled (rus):          
 !                        Проектирование антенно фидерных устройств. Жук М.С. Молочков Ю.Б
*/

#if defined (__INTEL_COMPILER)
#include <../perf_headers/c++/valarray>
#else
#include <valarray>
#endif
#include <cstdint>
#include <complex>
#include "GMS_config"


namespace gms {

         namespace radiolocation {

                  template<typename T>
                  struct alignas(64) Exyz_t {

                     int32_t            m_npts;
                     std::valarray<T>   m_ex;
                     std::valarray<T>   m_ey;
                     std::valarray<T>   m_ez;

                     Exyz_t()          = default;
 
                     Exyz_t(const int32_t npts) {

                           m_npts  = npts;
                           m_ex    = std::valarray<T>(m_npts);
                           m_ey    = std::valarray<T>(m_npts);
                           m_ez    = std::valarray<T>(m_npts);
                     }

                     Exyz_t(const Exyz_t &x) {

                           m_npts   = x.m_npts;
                           m_ex     = x.m_ex;
                           m_ey     = x.m_ey;
                           m_ez     = x.m_ez;
                     }

                     Exyz_t(Exyz_t &&x) noexcept(true) {

                          m_npts     = std::move(m_npts);
                          m_ex       = std::move(x.m_ex);
                          m_ey       = std::move(x.m_ey);
                          m_ez       = std::move(x.m_ez); 
                     }

                    ~Exyz()             = default;

                     Exyz_t & operator=(const Exyz_t &x) {

                          if(this == &x) return (*this);
                          Exyz_t<T> tmp(x);
                          std::swap(*this,tmp);
                          return (*this);
                     }

                     Exyz_t & operator=(Exyz_t &&x) noexcept(true) {
                          
                          if(this == &x) return (*this);
                          *this = std::move(x);
                          return (*this);
                     }
                     
               };

                  
                 
                  
                  template<typename T>
                  struct alignas(64) Hxyz_t {

                     int32_t            m_npts;
                     std::valarray<T>   m_hx;
                     std::valarray<T>   m_hy;
                     std::valarray<T>   m_hz;

                     Hxyz_t()          = default;
 
                     Hxyz_t(const int32_t npts) {

                           m_npts  = npts;
                           m_hx    = std::valarray<T>(m_npts);
                           m_hy    = std::valarray<T>(m_npts);
                           m_hz    = std::valarray<T>(m_npts);
                     }

                     Hxyz_t(const Hxyz_t &x) {

                           m_npts   = x.m_npts;
                           m_hx     = x.m_hx;
                           m_hy     = x.m_hy;
                           m_hz     = x.m_hz;
                     }

                     Hxyz_t(Hxyz_t &&x) noexcept(true) {

                          m_npts     = std::move(m_npts);
                          m_hx       = std::move(x.m_hx);
                          m_hy       = std::move(x.m_hy);
                          m_hz       = std::move(x.m_hz); 
                     }

                    ~Hxyz_t()             = default;

                     Hxyz_t & operator=(const Hxyz_t &x) {

                          if(this == &x) return (*this);
                          Hxyz_t<T> tmp(x);
                          std::swap(*this,tmp);
                          return (*this);
                     }

                     Hxyz_t & operator=(Hxyz_t &&x) noexcept(true) {
                          
                          if(this == &x) return (*this);
                          *this = std::move(x);
                          return (*this);
                     }
                     
               };


                 


                  /*
                      // Complex magnetic current
                   */  
                  template<typename T>
                  struct alignas(64) JMxyz_t {

                     int32_t            m_npts;
                     std::valarray<T>   m_jmx;
                     std::valarray<T>   m_jmy;
                     std::valarray<T>   m_jmz;

                     JMxyz_t()          = default;
 
                     JMxyz_t(const int32_t npts) {

                           m_npts   = npts;
                           m_jmx    = std::valarray<T>(m_npts);
                           m_jmy    = std::valarray<T>(m_npts);
                           m_jmz    = std::valarray<T>(m_npts);
                     }

                     JMxyz_t(const JMxyz_t &x) {

                           m_npts    = x.m_npts;
                           m_jmx     = x.m_jmx;
                           m_jmy     = x.m_jmy;
                           m_jmz     = x.m_jmz;
                     }

                     JMxyz_t(JMxyz_t &&x) noexcept(true) {

                          m_npts      = std::move(m_npts);
                          m_jmx       = std::move(x.m_jmx);
                          m_jmy       = std::move(x.m_jmy);
                          m_jmz       = std::move(x.m_jmz); 
                     }

                    ~JMxyz()             = default;

                     JMxyz_t & operator=(const JMxyz_t &x) {

                          if(this == &x) return (*this);
                          JMxyz_t<T> tmp(x);
                          std::swap(*this,tmp);
                          return (*this);
                     }

                     JMxyz_t & operator=(JMxyz_t &&x) noexcept(true) {
                          
                          if(this == &x) return (*this);
                          *this = std::move(x);
                          return (*this);
                     }
                     
               }; 


               

                    /*
                      // Complex electric current
                   */  
                  template<typename T>
                  struct alignas(64) JExyz_t {

                     int32_t            m_npts;
                     std::valarray<T>   m_jex;
                     std::valarray<T>   m_jey;
                     std::valarray<T>   m_jez;

                     JExyz_t()          = default;
 
                     JExyz_t(const int32_t npts) {

                           m_npts   = npts;
                           m_jex    = std::valarray<T>(m_npts);
                           m_jey    = std::valarray<T>(m_npts);
                           m_jez    = std::valarray<T>(m_npts);
                     }

                     JExyz_t(const JExyz_t &x) {

                           m_npts    = x.m_npts;
                           m_jex     = x.m_jex;
                           m_jey     = x.m_jey;
                           m_jez     = x.m_jez;
                     }

                     JExyz_t(JExyz_t &&x) noexcept(true) {

                          m_npts      = std::move(m_npts);
                          m_jex       = std::move(x.m_jex);
                          m_jey       = std::move(x.m_jey);
                          m_jez       = std::move(x.m_jez); 
                     }

                    ~JExyz()             = default;

                     JExyz_t & operator=(const JExyz_t &x) {

                          if(this == &x) return (*this);
                          JExyz_t<T> tmp(x);
                          std::swap(*this,tmp);
                          return (*this);
                     }

                     JExyz_t & operator=(JExyz_t &&x) noexcept(true) {
                          
                          if(this == &x) return (*this);
                          *this = std::move(x);
                          return (*this);
                     }
                     
               }; 


                  /*
                        // Time-Harmonic complex exponential
                   */
                  template<typename T1, typename T2>
                  struct alignas(64) eikr_t {

                         int32_t             m_npts;
                         T1                  m_k;
                         std::valarray<T1>   m_R;
                         std::valarray<T2>   m_ce;

                         eikr_t()            = default;
                         eikr_t(const int32_t npts,
                                const T1      k) {

                              m_npts   = npts;
                              m_k      = k;
                              m_R      = std::valarray<T1>(m_npts);
                              m_ce     = std::valarray<T2>(m_npts);
                         }

                         eikr_t(const eikr_t &x) {
                               
                              m_npts   = x.m_npts;
                              m_k      = x.m_k;
                              m_R      = x.m_R;
                              m_ce     = x.m_ce;
                         }

                         eikr_t(eikr_t &&x) noexcept(true) {
                             
                              m_npts    = std::move(x.m_npts);
                              m_k       = std::move(x.m_k);
                              m_R       = std::move(x.m_R);
                              m_ce      = std::move(x.m_ce);
                         }

                        ~eikr_t()              = default;

                         eikr_t & operator=(const eikr_t &x) {
                               
                              if(this == &x) return (*this);
                              eikr_t<T1,T2> tmp(x);
                              std::swap(*this,tmp);
                              return (*this);
                         }

                         eikr_t & operator=(eikr_t &&x) noexcept(true) {
                              
                              if(this == &x) return (*this);
                              *this = std::move(x);
                              return (*this);
                         }
               };


                  /*
                       // ! Formula (1-37)
                       //! Average level of side lobes
                   */
                  template<typename T>
                  struct alignas(64) f137_t {
                         
                       int32_t          m_nth;
                       int32_t          m_nph;
                       T                m_ith;
                       T                m_iph;
                       T                m_ifac;
                       T                m_omega;
                       T                m_avsl;
                       std::valarray<T> m_sinth;
                       std::valarray<T> m_F;

                       f137_t()         = default;

                       f137_t(const int32_t nth,
                              const int32_t nph,
                              const T       ith,
                              const T       iph,
                              const T       ifac,
                              const T       omega) {
                           
                           m_nth       = nth;
                           m_nph       = nph;
                           m_ith       = ith;
                           m_iph       = iph;
                           m_ifac      = ifac;
                           m_omega     = omega;
                           m_avsl      = static_cast<T>(0.0);
                           m_sinth     = std::valarray<T>(m_nth);
                           m_F         = std::valarray<T>(m_nth*m_nph);
                      }


                       f137_t(const int32_t nth,
                              const int32_t nph,
                              const T       ith,
                              const T       iph,
                              const T       ifac,
                              const T       omega,
                              std::valarray<T> &&sinth
                              std::valarray<T> &&F) {

                           m_nth       = nth;
                           m_nph       = nph;
                           m_ith       = ith;
                           m_iph       = iph;
                           m_ifac      = ifac;
                           m_omega     = omega;
                           m_avsl      = static_cast<T>(0.0);
                           m_sinth     = std::move(sinth); 
                           m_F         = std::move(F);
                      }


                      f137_t(const f137_t &x) {
                           
                           m_nth       = x.m_nth;
                           m_nph       = x.m_nph;
                           m_ith       = x.m_ith;
                           m_iph       = x.m_iph;
                           m_ifac      = x.m_ifac;
                           m_omega     = x.m_omega;
                           m_avsl      = x.m_avsl;
                           m_sinth     = x.m_sinth;
                           m_F         = x.m_F;
                      }

                      f137_t(f137_t &&x) noexcept(true) {
                           
                           m_nth       = std::move(x.m_nth);
                           m_nph       = std::move(x.m_nph);
                           m_ith       = std::move(x.m_ith);
                           m_iph       = std::move(x.m_iph);
                           m_ifac      = std::move(x.m_ifac);
                           m_omega     = std::move(x.m_omega);
                           m_avsl      = std::move(x.m_avsl);
                           m_sinth     = std::move(x.m_sinth);
                           m_F         = std::move(x.m_F);
                      }

                     ~f137_t()                  = default;

                      f137_t & operator=(const f137_t &x) {
                          
                           if(this == &x) return (*this);
                           f137_t<T> tmp(x);
                           std::swap(*this,tmp);
                           return (*this);
                      }

                      f137_t & operator=(f137_t &&x) noexcept(true) {
                           
                           if(this == &x) return (*this);
                           *this = std::move(x);
                            return (*this);
                      }
               };


                // ! Formula (1-38)
                //! 	Squared-averaged level of side lobes
                  template<typename T>
                  struct alignas(64) f138_t {
                         
                       int32_t          m_nth;
                       int32_t          m_nph;
                       T                m_ith;
                       T                m_iph;
                       T                m_ifac;
                       T                m_omega;
                       T                m_avsl;
                       std::valarray<T> m_sinth;
                       std::valarray<T> m_F;

                       f138_t()         = default;

                       f138_t(const int32_t nth,
                              const int32_t nph,
                              const T       ith,
                              const T       iph,
                              const T       ifac,
                              const T       omega) {
                           
                           m_nth       = nth;
                           m_nph       = nph;
                           m_ith       = ith;
                           m_iph       = iph;
                           m_ifac      = ifac;
                           m_omega     = omega;
                           m_avsl      = static_cast<T>(0.0);
                           m_sinth     = std::valarray<T>(m_nth);
                           m_F         = std::valarray<T>(m_nth*m_nph);
                      }


                      f138_t(const int32_t nth,
                             const int32_t nph,
                             const T       ith,
                             const T       iph,
                             const T       ifac,
                             const T       omega,
                             std::valarray<T> &&sinth,
                             std::valarray<T> &&F) {

                           m_nth       = nth;
                           m_nph       = nph;
                           m_ith       = ith;
                           m_iph       = iph;
                           m_ifac      = ifac;
                           m_omega     = omega;
                           m_avsl      = static_cast<T>(0.0);
                           m_sinth     = std::move(sinth);
                           m_F         = std::move(F);
                      }


                      f138_t(const f138_t &x) {
                           
                           m_nth       = x.m_nth;
                           m_nph       = x.m_nph;
                           m_ith       = x.m_ith;
                           m_iph       = x.m_iph;
                           m_ifac      = x.m_ifac;
                           m_omega     = x.m_omega;
                           m_avsl      = x.m_avsl;
                           m_sinth     = x.m_sinth;
                           m_F         = x.m_F;
                      }

                      f138_t(f138_t &&x) noexcept(true) {
                           
                           m_nth       = std::move(x.m_nth);
                           m_nph       = std::move(x.m_nph);
                           m_ith       = std::move(x.m_ith);
                           m_iph       = std::move(x.m_iph);
                           m_ifac      = std::move(x.m_ifac);
                           m_omega     = std::move(x.m_omega);
                           m_avsl      = std::move(x.m_avsl);
                           m_sinth     = std::move(x.m_sinth);
                           m_F         = std::move(x.m_F);
                      }

                     ~f138_t()                  = default;

                      f138_t & operator=(const f138_t &x) {
                          
                           if(this == &x) return (*this);
                           f138_t<T> tmp(x);
                           std::swap(*this,tmp);
                           return (*this);
                      }

                      f138_t & operator=(f138_t &&x) noexcept(true) {
                           
                           if(this == &x) return (*this);
                           *this = std::move(x);
                            return (*this);
                      }
               };


               /*
                   //! Formula (1-39)
                   // ! Dispersion coefficient
               */
                  template<typename T>
                  struct alignas(64) f139_t {
                         
                       int32_t          m_nth;
                       int32_t          m_nph;
                       T                m_ith;
                       T                m_iph;
                       T                m_omega;
                       T                m_rho;
                       std::valarray<T> m_sinth;
                       std::valarray<T> m_P;

                       f139_t()         = default;

                       f139_t(const int32_t nth,
                              const int32_t nph,
                              const T       ith,
                              const T       iph,
                              const T       omega) {
                           
                           m_nth       = nth;
                           m_nph       = nph;
                           m_ith       = ith;
                           m_iph       = iph;
                           m_omega     = omega;
                           m_rho       = static_cast<T>(0.0);
                           m_sinth     = std::valarray<T>(m_nth);
                           m_P         = std::valarray<T>(m_nth*m_nph);
                      }


                      f139_t( const int32_t nth,
                              const int32_t nph,
                              const T       ith,
                              const T       iph,
                              const T       omega,
                              std::valarray<T> &&sinth,
                              std::valarray<T> &&P) {

                           m_nth       = nth;
                           m_nph       = nph;
                           m_ith       = ith;
                           m_iph       = iph;
                           m_omega     = omega;
                           m_rho       = static_cast<T>(0.0);
                           m_sinth     = std::move(sinth);
                           m_F         = std::move(F); 
                      }


                      f139_t(const f139_t &x) {
                           
                           m_nth       = x.m_nth;
                           m_nph       = x.m_nph;
                           m_ith       = x.m_ith;
                           m_iph       = x.m_iph;
                           m_omega     = x.m_omega;
                           m_rho       = x.m_rho;
                           m_sinth     = x.m_sinth;
                           m_P         = x.m_P;
                      }


                      f139_t(f139_t &&x) noexcept(true) {
                           
                           m_nth       = std::move(x.m_nth);
                           m_nph       = std::move(x.m_nph);
                           m_ith       = std::move(x.m_ith);
                           m_iph       = std::move(x.m_iph);
                           m_omega     = std::move(x.m_omega);
                           m_rho       = std::move(x.m_rho);
                           m_sinth     = std::move(x.m_sinth);
                           m_P         = std::move(x.m_P);
                      }

                     ~f139_t()                  = default;

                      f139_t & operator=(const f139_t &x) {
                          
                           if(this == &x) return (*this);
                           f139_t<T> tmp(x);
                           std::swap(*this,tmp);
                           return (*this);
                      }

                      f139_t & operator=(f139_t &&x) noexcept(true) {
                           
                           if(this == &x) return (*this);
                           *this = std::move(x);
                            return (*this);
                      }
               };


                  /*
                      //  ! Formula (2-13)
                      //  ! Hertz vector electric
                   */
                  template<typename T1, typename T2>
                  struct alignas(64)  Hve_t {

                          int32_t           m_npts;
                          T1                m_k;
                          T2                m_ifac;
                          JExyz_t           m_jec;
                          eikr_t            m_ce;
                          std::valarray<T2> m_hex;
                          std::valarray<T2> m_hey;
                          std::valarray<T2> m_hez;

                          Hve_t()             = default;

                          Hve_t(const int32_t npts,
                                const T1      k,
                                const T2      ifac) {

                             m_npts    = npts;
                             m_k       = k;
                             m_ifac    = ifac;
                             m_jec     = JExyz_t<T1>(m_npts);
                             m_ce      = eikr_t<T1,T2>(m_npts,m_k);
                             m_hex     = std::valarray<T1>(m_npts);
                             m_hey     = std::valarray<T1>(m_npts);
                             m_hez     = std::valarray<T1>(m_npts);
                        }

                          Hve_t(const Hve_t &x) {

                             m_npts    = x.m_npts;
                             m_k       = x.m_k;
                             m_ifac    = x.m_ifac;
                             m_jec     = x.m_jec;
                             m_ce      = x.m_ce;
                             m_hex     = x.m_hex;
                             m_hey     = x.m_hey;
                             m_hez     = x.m_hez;
                         }

                          Hve_t(Hve_t &&x) noexcept(true) {

                             m_npts    = std::move(x.m_npts);
                             m_k       = std::move(x.m_k);
                             m_ifac    = std::move(x.m_ifac);
                             m_jec     = std::move(x.m_jec);
                             m_ce      = std::move(x.m_ce);
                             m_hex     = std::move(x.m_hex);
                             m_hey     = std::move(x.m_hey);
                             m_hez     = std::move(x.m_hez);
                         }

                        ~Hve_t()               = default;
 
                         Hve_t & operator=(const Hve_t &x) {

                               if(this == &x) return (*this);
                               Hve_t<T1,T2> tmp(npts,k,ifac);
                               std::swap(*this,tmp);
                               return (*this);
                         }  

                         Hve_t & operator=(Hve_t &&x) noexcept(true) {

                               if(this == &x) return (*this);
                               *this = std::move(x);
                               return (*this);
                         }
                        
               };


                   /*
                      //  ! Formula (2-15)
                      //  ! Hertz vector magnetic
                   */
                  template<typename T1, typename T2>
                  struct alignas(64)  Hvm_t {

                          int32_t           m_npts;
                          T1                m_k;
                          T2                m_ifac;
                          JMxyz_t           m_jmc;
                          eikr_t            m_ce;
                          std::valarray<T2> m_hmx;
                          std::valarray<T2> m_hmy;
                          std::valarray<T2> m_hmz;

                          Hvm_t()             = default;

                          Hvm_t(const int32_t npts,
                                const T1      k,
                                const T2      ifac) {

                             m_npts    = npts;
                             m_k       = k;
                             m_ifac    = ifac;
                             m_jmc     = JMxyz_t<T1>(m_npts);
                             m_ce      = eikr_t<T1,T2>(m_npts,m_k);
                             m_hmx     = std::valarray<T1>(m_npts);
                             m_hmy     = std::valarray<T1>(m_npts);
                             m_hmz     = std::valarray<T1>(m_npts);
                         }

                          Hvm_t(const Hvm_t &x) {

                             m_npts    = x.m_npts;
                             m_k       = x.m_k;
                             m_ifac    = x.m_ifac;
                             m_jmc     = x.m_jmc;
                             m_ce      = x.m_ce;
                             m_hmx     = x.m_hmx;
                             m_hmy     = x.m_hmy;
                             m_hmz     = x.m_hmz;
                         }

                          Hvm_t(Hvm_t &&x) noexcept(true) {

                             m_npts    = std::move(x.m_npts);
                             m_k       = std::move(x.m_k);
                             m_ifac    = std::move(x.m_ifac);
                             m_jmc     = std::move(x.m_jmc);
                             m_ce      = std::move(x.m_ce);
                             m_hmx     = std::move(x.m_hmx);
                             m_hmy     = std::move(x.m_hmy);
                             m_hmz     = std::move(x.m_hmz);
                         }

                        ~Hvm_t()               = default;
 
                         Hvm_t & operator=(const Hvm_t &x) {

                               if(this == &x) return (*this);
                               Hvm_t<T1,T2> tmp(npts,k,ifac);
                               std::swap(*this,tmp);
                               return (*this);
                         }  

                         Hvm_t & operator=(Hvm_t &&x) noexcept(true) {

                               if(this == &x) return (*this);
                               *this = std::move(x);
                               return (*this);
                         }
                        
               };



                 
       } // radiolocation

} // gms












#endif /*__GMS_ANTENNA_TYPES_V2_HPP__*/
