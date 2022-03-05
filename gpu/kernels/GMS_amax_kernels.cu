
#include <cfloat>
#include <cstdint>
#include "GMS_atomicops.h"
// Modified by Bernard Gingold, contact: bgin@gmail.com
/*
    GLAS is licensed under the The MIT License:

Copyright (c) 2011 Hans Henrik Brandenborg Sørensen, DTU

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// 
// Generic vector max kernel.
//
// - Designed for architectures with atomicCAS, i.e., sm_11 and higher.
// - Simple design for all capabilities
// - Handled by splitting matrix as
// --------------------------
// |                 |      |
// |                 |      |
// |                 |      |
// | left tiled part | rest | 
// |                 |      |
// |                 |      |
// |                 |      |
// --------------------------
// - Kernel is generic and works for all cases
// - Unrolling of inner loops
//     1) to reduce instruction count from loop
//     2) to collect shared loads into 128 bit transactions (compiler should do that)
//   * Level determined by WORKSIZE_n
//   * For WORKSIZE_n = 1:
//       Given by a constant: full unroll
//       Given by a variable: unroll level 4

#define imax(a,b,c,d) if (a < b) { a = b; c = d; }


__forceinline__ 
__device__ void block_reduce_max_r4(const float * __restrict__ x, 
                                    int32_t * __restrict__ y, 
                                    volatile float * __restrict__ smem, 
                                    volatile int32_t * __restrict__ imem, 
                                    float sum, int index, 
                                    int32_t tid,int32_t BLOCKSIZE_n)
{
	smem[tid] = sum;
	imem[tid] = index;
	__syncthreads();
	if (BLOCKSIZE_n >= 1024) { if (tid < 512) { imax(smem[tid], smem[tid + 512], imem[tid], imem[tid + 512]); } __syncthreads(); }
	if (BLOCKSIZE_n >= 512) { if (tid < 256) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 480) { if (tid < 224) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 448) { if (tid < 192) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 416) { if (tid < 160) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 384) { if (tid < 128) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n >= 256) { if (tid < 128) { imax(smem[tid], smem[tid + 128], imem[tid], imem[tid + 128]); } __syncthreads(); }
	if (BLOCKSIZE_n == 352) { if (tid < 96) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 224) { if (tid < 96) { imax(smem[tid], smem[tid + 128], imem[tid], imem[tid + 128]); } __syncthreads(); }
	if (BLOCKSIZE_n == 320) { if (tid < 64) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 192) { if (tid < 64) { imax(smem[tid], smem[tid + 128], imem[tid], imem[tid + 128]); } __syncthreads(); }
	if (BLOCKSIZE_n >= 128) { if (tid < 64) { imax(smem[tid], smem[tid + 64], imem[tid], imem[tid + 64]); } __syncthreads(); }
	if (BLOCKSIZE_n == 288) { if (tid < 32) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 160) { if (tid < 32) { imax(smem[tid], smem[tid + 128], imem[tid], imem[tid + 128]); } __syncthreads(); }
	if (BLOCKSIZE_n == 96) { if (tid < 32) { imax(smem[tid], smem[tid + 64], imem[tid], imem[tid + 64]); } __syncthreads(); }
	if (BLOCKSIZE_n >= 64) { if (tid < 32) { imax(smem[tid], smem[tid + 32], imem[tid], imem[tid + 32]); } }
	if (BLOCKSIZE_n >= 32) { if (tid < 16) { imax(smem[tid], smem[tid + 16], imem[tid], imem[tid + 16]); } }
	if (BLOCKSIZE_n >= 16) { if (tid < 8) { imax(smem[tid], smem[tid + 8], imem[tid], imem[tid + 8]); } }
	if (BLOCKSIZE_n >= 8) { if (tid < 4) { imax(smem[tid], smem[tid + 4], imem[tid], imem[tid + 4]); } }
	if (BLOCKSIZE_n >= 4) { if (tid < 2) { imax(smem[tid], smem[tid + 2], imem[tid], imem[tid + 2]); } }
	if (BLOCKSIZE_n >= 2) { if (tid < 1) { imax(smem[tid], smem[tid + 1], imem[tid], imem[tid + 1]); } }
	if (tid == 0) { atomicImax(x, smem[tid], y, imem[tid]); }
}

__forceinline__ 
__device__ void block_reduce_max_r8(const double * __restrict__ x, 
                                    int32_t * __restrict__ y, 
                                    volatile double * __restrict__ smem, 
                                    volatile int32_t * __restrict__ imem, 
                                    double sum, int index, 
                                    int32_t tid,int32_t BLOCKSIZE_n)
{
	smem[tid] = sum;
	imem[tid] = index;
	__syncthreads();
	if (BLOCKSIZE_n >= 1024) { if (tid < 512) { imax(smem[tid], smem[tid + 512], imem[tid], imem[tid + 512]); } __syncthreads(); }
	if (BLOCKSIZE_n >= 512) { if (tid < 256) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 480) { if (tid < 224) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 448) { if (tid < 192) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 416) { if (tid < 160) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 384) { if (tid < 128) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n >= 256) { if (tid < 128) { imax(smem[tid], smem[tid + 128], imem[tid], imem[tid + 128]); } __syncthreads(); }
	if (BLOCKSIZE_n == 352) { if (tid < 96) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 224) { if (tid < 96) { imax(smem[tid], smem[tid + 128], imem[tid], imem[tid + 128]); } __syncthreads(); }
	if (BLOCKSIZE_n == 320) { if (tid < 64) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 192) { if (tid < 64) { imax(smem[tid], smem[tid + 128], imem[tid], imem[tid + 128]); } __syncthreads(); }
	if (BLOCKSIZE_n >= 128) { if (tid < 64) { imax(smem[tid], smem[tid + 64], imem[tid], imem[tid + 64]); } __syncthreads(); }
	if (BLOCKSIZE_n == 288) { if (tid < 32) { imax(smem[tid], smem[tid + 256], imem[tid], imem[tid + 256]); } __syncthreads(); }
	if (BLOCKSIZE_n == 160) { if (tid < 32) { imax(smem[tid], smem[tid + 128], imem[tid], imem[tid + 128]); } __syncthreads(); }
	if (BLOCKSIZE_n == 96) { if (tid < 32) { imax(smem[tid], smem[tid + 64], imem[tid], imem[tid + 64]); } __syncthreads(); }
	if (BLOCKSIZE_n >= 64) { if (tid < 32) { imax(smem[tid], smem[tid + 32], imem[tid], imem[tid + 32]); } }
	if (BLOCKSIZE_n >= 32) { if (tid < 16) { imax(smem[tid], smem[tid + 16], imem[tid], imem[tid + 16]); } }
	if (BLOCKSIZE_n >= 16) { if (tid < 8) { imax(smem[tid], smem[tid + 8], imem[tid], imem[tid + 8]); } }
	if (BLOCKSIZE_n >= 8) { if (tid < 4) { imax(smem[tid], smem[tid + 4], imem[tid], imem[tid + 4]); } }
	if (BLOCKSIZE_n >= 4) { if (tid < 2) { imax(smem[tid], smem[tid + 2], imem[tid], imem[tid + 2]); } }
	if (BLOCKSIZE_n >= 2) { if (tid < 1) { imax(smem[tid], smem[tid + 1], imem[tid], imem[tid + 1]); } }
	if (tid == 0) { atomicImax(x, smem[tid], y, imem[tid]); }
}



__global__ void amax_kernel_r4(const float * __restrict__ x, 
                              int32_t * __restrict__ y, 
                              const int32_t n, const int32_t ntile,
                              const int32_t BLOCKSIZE_n,
                              const int32_t WORKSIZE_m,
                              const int32_t WORKSIZE_n)
{
	const int32_t tid = threadIdx.x;
	const int32_t idx = blockIdx.x * BLOCKSIZE_n * WORKSIZE_n;
	int32_t index = idx + tid, index_i = index;
	const float * __restrict__ x_i = x + index;
	float sum = FLT_MIN;
	if (idx != ntile)
	{
        #pragma unroll
		//inner_loop(WORKSIZE_n);
           for (int i = 0; i < WORKSIZE_n; i++ ) {							
																		
		imax(sum, x_i[0], index, index_i); x_i += BLOCKSIZE_n; index_i += BLOCKSIZE_n;
	     }
	}
	else
	{
        #pragma unroll 4
		//inner_loop2(n - idx - tid);
          for (int i = 0; i < n-idx-tid; i += BLOCKSIZE_n) {	
													
		imax(sum, x_i[i], index, index_i + i);	
	    }
	}
	__shared__ volatile float smem[BLOCKSIZE_n];
	__shared__ volatile int32_t imem[BLOCKSIZE_n];
	block_reduce_max_r4(x, y, smem, imem, sum, index, tid, BLOCKSIZE_n);
}


__global__ void amax_kernel_r8(const double * __restrict__ x, 
                                 int32_t * __restrict__ y, 
                                 const int32_t n, const int32_t ntile,
                                 const int32_t BLOCKSIZE_n,
                                 const int32_t WORKSIZE_m,
                                 const int32_t WORKSIZE_n)
{
	const int32_t tid = threadIdx.x;
	const int32_t idx = blockIdx.x * BLOCKSIZE_n * WORKSIZE_n;
	int32_t index = idx + tid, index_i = index;
	const double * __restrict__ x_i = x + index;
	double sum = DBL_MIN;
	if (idx != ntile)
	{
        #pragma unroll
		//inner_loop(WORKSIZE_n);
           for (int i = 0; i < WORKSIZE_n; i++ ) {							
																		
		imax(sum, x_i[0], index, index_i); x_i += BLOCKSIZE_n; index_i += BLOCKSIZE_n;
	     }
	}
	else
	{
        #pragma unroll 4
		//inner_loop2(n - idx - tid);
          for (int i = 0; i < n-idx-tid; i += BLOCKSIZE_n) {	
													
		imax(sum, x_i[i], index, index_i + i);	
	    }
	}
	__shared__ volatile double smem[BLOCKSIZE_n];
	__shared__ volatile int32_t imem[BLOCKSIZE_n];
	block_reduce_max_r8(x, y, smem, imem, sum, index, tid, BLOCKSIZE_n);
}

