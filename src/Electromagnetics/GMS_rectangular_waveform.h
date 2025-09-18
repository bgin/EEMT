
/*MIT License
!Copyright (c) 2020 Bernard Gingold
!Permission is hereby granted, free of charge, to any person obtaining a copy
!of this software and associated documentation files (the "Software"), to deal
!in the Software without restriction, including without limitation the rights
!to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
!copies of the Software, and to permit persons to whom the Software is
!furnished to do so, subject to the following conditions:
!The above copyright notice and this permission notice shall be included in all
!copies or substantial portions of the Software.
!THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
!IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
!FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
!AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
!LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
!OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
!SOFTWARE.
*/

#ifndef __GMS_RECTANGULAR_WAVEFORM_H__
#define __GMS_RECTANGULAR_WAVEFORM_H__ 180920251047

namespace file_info 
{

     static const unsigned int GMS_RECTANGULAR_WAVEFORM_MAJOR = 1;
     static const unsigned int GMS_RECTANGULAR_WAVEFORM_MINOR = 1;
     static const unsigned int GMS_RECTANGULAR_WAVEFORM_MICRO = 0;
     static const unsigned int GMS_RECTANGULAR_WAVEFORM_FULLVER =
       1000U*GMS_RECTANGULAR_WAVEFORM_MAJOR+100U*GMS_RECTANGULAR_WAVEFORM_MINOR+
       10U*GMS_RECTANGULAR_WAVEFORM_MICRO;
     static const char GMS_RECTANGULAR_WAVEFORM_CREATION_DATE[] = "18-09-2025 10:48 +00200 (THR  18 SEP 2025 GMT+2)";
     static const char GMS_RECTANGULAR_WAVEFORM_BUILD_DATE[]    = __DATE__; 
     static const char GMS_RECTANGULAR_WAVEFORM_BUILD_TIME[]    = __TIME__;
     static const char GMS_RECTANGULAR_WAVEFORM_SYNOPSIS[]      = "Rectangular waveform generators.";

}

#include <cstdint>
#include <string>
#include "GMS_config.h"
#include "GMS_dyn_array.h"

// Enable non-temporal stores for this class only( used with free-standing operators)
// defaulted to 0.
// To be added.
#if !defined (RECTANGULAR_WAVEFORM_USE_NT_STORES)
#define RECTANGULAR_WAVEFORM_USE_NT_STORES 0
#endif

#ifdef _OPENMP
// Default init a storage arrays for the first-touch (OpenMP) processing
#if !defined(RECTANGULAR_WAVEFORM_INIT_STORAGE)
#define RECTANGULAR_WAVEFORM_INIT_STORAGE 1
#endif 
#endif

#if (RECTANGULAR_WAVEFORM_INIT_STORAGE) == 1
#define INIT_BY_STD_FILL 0
#endif 

// For inlining of trigo functions (asin,acos,sin,cos)
#if !defined(RECTANGULAR_WAVEFORM_USE_CEPHES)
#define RECTANGULAR_WAVEFORM_USE_CEPHES 1
#endif 

// Enable for the basic PMC tracing (wall-clock) readout (not statistically rigorous)!!
// *** Warning *** -- An access for the PM hardware counters must be enabled for the user-mode space!!
// 
#if !defined (RECTANGULAR_WAVEFORM_USE_PMC_INSTRUMENTATION)
#define RECTANGULAR_WAVEFORM_USE_PMC_INSTRUMENTATION 1
#endif 

#if (RECTANGULAR_WAVEFORM_USE_PMC_INSTRUMENTATION) == 1
#include "GMS_hw_perf_macros.h"

#define PMC_VARS                      \
uint64_t prog_counters_start[4] = {}; \
uint64_t prog_counters_stop[4]  = {}; \
uint64_t tsc_start,tsc_stop;          \
uint64_t act_cyc_start,act_cyc_stop;  \
uint64_t ref_cyc_start,ref_cyc_stop;  \
[[maybe_unused]] uint64_t dummy1;     \
[[maybe_unused]] uint64_t dummy2;     \
[[maybe_unused]] uint64_t dummy3;     \
int32_t core_counter_width;           \
double utilization,nom_ghz,avg_ghz;
#endif 


namespace gms 
{

namespace radiolocation 
{
           
          struct alignas(64) rectangular_waveform_t final 
          {
                 std::size_t   __n_samples__;
                 std::uint32_t __n_waves__;
                 float         __T__;   // period
                 float         __rho__; // pulse length
                 float         __A__;   // Amplitude 
                 darray_r4_t   __rw_samples__;

                 rectangular_waveform_t() = default;

                 rectangular_waveform_t(const std::size_t,
                                        const std::uint32_t,
                                        const float,
                                        const float,
                                        const float)  noexcept(false);

                  rectangular_waveform_t(rectangular_waveform_t &&) noexcept(false);

                  ~rectangular_waveform_t() noexcept(false);

                  rectangular_waveform_t & operator=(const rectangular_waveform_t &) = delete;

                  rectangular_waveform_t & operator=(rectangular_waveform_t &&);

                  void init_storage(const float);

                  static void create_signal_plot(const std::uint32_t,
                                                 const float * __restrict,
                                                 const float * __restrict,
                                                 const std::string &,
                                                 const std::string &,
                                                 const bool );

                  void fourier_series_expansion();
          };

}

}




















#endif /*__GMS_RECTANGULAR_WAVEFORM_H__*/