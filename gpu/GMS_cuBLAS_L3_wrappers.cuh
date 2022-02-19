

#ifndef __GMS_CUBLAS_L3_WRAPPERS_CUH__
#define __GMS_CUBLAS_L3_WRAPPERS_CUH__

#include <stdint.h>

extern "C"
void
cuBLAS_Sgemm_iface(cublasOperation_t,
                   cublasOperation_t,
                   const int32_t,
                   const int32_t,
                   const int32_t,
                   const float,
                   const float * __restrict,
                   const int32_t,
                   const float * __restrict,
                   const int32_t,
                   float,
                   float * __restrict,
                   const int32_t,
                   cudaError_t * __restrict,
                   int32_t * __restrict,
                   uint64_t * __restrict) 
                                       __attribute__((hot))
                                       __attribute__((aligned(32)));

extern "C"
void
cuBLAS_Cgemm_iface(cublasOperation_t,
                   cublasOperation_t,
                   const int32_t,
                   const int32_t,
                   const int32_t,
                   const cuComplex,
                   const cuComplex * __restrict,
                   const int32_t,
                   const cuComplex * __restrict,
                   const int32_t,
                   cuComplex,
                   cuComplex * __restrict,
                   const int32_t,
                   cudaError_t * __restrict,
                   int32_t * __restrict,
                   uint64_t * __restrict) 
                                       __attribute__((hot))
                                       __attribute__((aligned(32)));   
                                       


extern "C"
void
cuBLAS_Cgemm3m_iface(cublasOperation_t,
                   cublasOperation_t,
                   const int32_t,
                   const int32_t,
                   const int32_t,
                   const cuComplex,
                   const cuComplex * __restrict,
                   const int32_t,
                   const cuComplex * __restrict,
                   const int32_t,
                   cuComplex,
                   cuComplex * __restrict,
                   const int32_t,
                   cudaError_t * __restrict,
                   int32_t * __restrict,
                   uint64_t * __restrict) 
                                       __attribute__((hot))
                                       __attribute__((aligned(32)));




extern "C"
void
cuBLAS_Chemm_iface(cublasSideMode_t,
                   cublasFillMode_t,
                   const int32_t,
                   const int32_t,
                   const cuComplex,
                   const cuComplex * __restrict,
                   const int32_t,
                   const cuComplex * __restrict,
                   const int32_t,
                   const cuComplex,
                   cuComplex * __restrict,
                   const int32_t,
                   cudaError_t * __restrict,
                   int32_t * __restrict,
                   uint64_t * __restrict) 
                                       __attribute__((hot))
                                       __attribute__((aligned(32)));



extern "C"
void
cuBLAS_Cher2k_iface(cublasOperation_t,
                    cublasOperation_t,
                    cublasFillMode_t,
                    const int32_t,
                    const int32_t,
                    const cuComplex,
                    const cuComplex * __restrict,
                    const int32_t,
                    const cuComplex * __restrict,
                    const int32_t,
                    const cuComplex,
                    cuComplex * __restrict,
                    const int32_t,
                    cudaError_t * __restrict,
                    int32_t * __restrict,
                    uint64_t * __restrict) 
                                       __attribute__((hot))
                                       __attribute__((aligned(32)));


extern "C"
void
cuBLAS_Ssymm_iface(cublasSideMode_t,
                   cublasFillMode_t,
                   int32_t,
                   int32_t,
                   const float,
                   const float * __restrict,
                   const int32_t,
                   const float * __restrict,
                   int32_t,
                   const float,
                   float * __restrict,
                   const int32_t,
                   cudaError_t * __restrict,
                   int32_t * __restrict,
                   uint64_t * __restrict) 
                                       __attribute__((hot))
                                       __attribute__((aligned(32)));


extern "C"
void
cuBLAS_Ssyrk_iface(cublasFillMode_t,
                   cublasOperation_t,
                   const int32_t,
                   const int32_t,
                   const float,
                   const float * __restrict,
                   const int32_t,
                   const float,
                   float * __restrict,
                   const int32_t,
                   cudaError_t * __restrict,
                   int32_t * __restrict,
                   uint64_t * __restrict) 
                                       __attribute__((hot))
                                       __attribute__((aligned(32)));


extern "C"
void
cuBLAS_Csyrk_iface(cublasFillMode_t,
                   cublasOperation_t,
                   const int32_t,
                   const int32_t,
                   const cuComplex,
                   const cuComplex * __restrict,
                   const int32_t,
                   const cuComplex,
                   cuComplex * __restrict,
                   const int32_t,
                   cudaError_t * __restrict,
                   int32_t * __restrict,
                   uint64_t * __restrict) 
                                       __attribute__((hot))
                                       __attribute__((aligned(32)));


extern "C"
void
cuBLAS_Strsm_iface(cublasSideMode_t,
                   cublasFillMode_t,
                   cublasOperation_t,
                   cublasDiagType_t,
                   const int32_t,
                   const int32_t,
                   const float,
                   const float * __restrict,
                   const int32_t,
                   float * __restrict,
                   const int32_t,
                   cudaError_t * __restrict,
                   int32_t * __restrict,
                   uint64_t * __restrict) 
                                       __attribute__((hot))
                                       __attribute__((aligned(32)));



extern "C"
void
cuBLAS_Ctrsm_iface(cublasSideMode_t,
                   cublasFillMode_t,
                   cublasOperation_t,
                   cublasDiagType_t,
                   const int32_t,
                   const int32_t,
                   const cuComplex,
                   const cuComplex * __restrict,
                   const int32_t,
                   cuComplex * __restrict,
                   const int32_t,
                   cudaError_t * __restrict,
                   int32_t * __restrict,
                   uint64_t * __restrict) 
                                       __attribute__((hot))
                                       __attribute__((aligned(32)));



                   






#endif /*__GMS_CUBLAS_L3_WRAPPERS_CUH__*/
