
#ifndef __GMS_CUDA_MEMOPS_CUH__
#define __GMS_CUDA_MEMOPS_CUH__




#include <stddef.h>
#include <cstdint>
#include "GMS_gpu_config.cuh"











//
// Copy int32_t array  (linearized) from CPU to GPU.
//
void copy_int32_cpu_to_gpu(int32_t * __restrict, 
                           int32_t * __restrict, 
			   const size_t, 
                           int32_t * 

                )   __attribute__((cold))
		                         __attribute__ ((alloc_size(1)))
				         __attribute__ ((malloc))
					 __attribute__ ((returns_nonnull));



//
// Copy float array  (linearized) from CPU to GPU
//
void copy_float_cpu_to_gpu(float * __restrict, 
                           float * __restrict, 
                           const size_t, 
                           int32_t * 

)   __attribute__((cold))
		                         __attribute__ ((alloc_size(1)))
				         __attribute__ ((malloc))
					 __attribute__ ((returns_nonnull));


//
// Copy double array  (linearized) from CPU to GPU.
//
void copy_double_cpu_to_gpu(double * __restrict, 
                            double * __restrict,
			    const size_t, 
                            int32_t *

 )  __attribute__((cold))
		                         __attribute__ ((alloc_size(1)))
				         __attribute__ ((malloc))
					 __attribute__ ((returns_nonnull));
//
// Copy cuComplex array from CPU to GPU
//
void copy_complex4_cpu_to_gpu(cuComplex * __restrict,
                              cuComplex * __restrict,
                              const size_t,
                              int32_t *

) __attribute__((cold))
		                         __attribute__ ((alloc_size(1)))
				         __attribute__ ((malloc))
					 __attribute__ ((returns_nonnull));

//
// Allocate array  of type int32_t on GPU.
//
void alloc_int32_gpu(int32_t * __restrict, 
                     const size_t, 
                     int32_t * 

)   __attribute__((cold))
		                   __attribute__ ((alloc_size(1)))
				   __attribute__ ((malloc))
		                   __attribute__ ((returns_nonnull));



//
// Allocate array  of type float on GPU.
//
void alloc_float_gpu(float * __restrict, 
                     const size_t, 
                     int32_t * 

)         __attribute__((cold))
		                         __attribute__ ((alloc_size(1)))
				         __attribute__ ((malloc))
					 __attribute__ ((returns_nonnull));


//
// Allocate array of type double on GPU.
//
void alloc_double_gpu(double * __restrict, 
                      const size_t, 
                      int32_t * 

)   __attribute__((cold))
		                    __attribute__ ((alloc_size(1)))
				    __attribute__ ((malloc))
				    __attribute__ ((returns_nonnull));

//
// Allocate float complex array on the GPU
//
void alloc_complex4_gpu(cuComplex * __restrict,
                        const size_t,
                        int32_t *

)   __attribute__((cold))
		                    __attribute__ ((alloc_size(1)))
				    __attribute__ ((malloc))
				    __attribute__ ((returns_nonnull));

//
// GPU to CPU memory copy routines
//

//
// Copy array  of int32_t from GPU to CPU.
//
void copy1D_int32_gpu_to_cpu(int32_t * __restrict, 
                             int32_t * __restrict,
			     const size_t, 
                             int32_t * 

) __attribute__((cold))
		                         __attribute__ ((alloc_size(1)))
				         __attribute__ ((malloc))
					 __attribute__ ((returns_nonnull));



//
// Copy array  of type float from GPU to CPU.
//
void copy_float_gpu_to_cpu(float * __restrict, 
                           float * __restrict, 
			   const size_t, 
                           int32_t * 

) __attribute__((cold))
		                       __attribute__ ((alloc_size(1)))
				       __attribute__ ((malloc))
				       __attribute__ ((returns_nonnull));



//
// Copy array  of type double from GPU to CPU.
//
void copy_double_gpu_to_cpu(double * __restrict, 
                            double * __restrict,
			    const size_t, 
                            int32_t * 

)  __attribute__((cold))
		                         __attribute__ ((alloc_size(1)))
				         __attribute__ ((malloc))
					 __attribute__ ((returns_nonnull));




//
// Copy array of type cuComplex from GPU to CPU
//
void copy_complex4_gpu_to_cpu(cuComplex * __restrict,
                              cuComplex * __restrict,
                              const size_t,
                              int32_t

)   __attribute__((cold))
		                         __attribute__ ((alloc_size(1)))
				         __attribute__ ((malloc))
					 __attribute__ ((returns_nonnull));



#endif /*__GMS_CUDA_MEMOPS_CUH__*/
