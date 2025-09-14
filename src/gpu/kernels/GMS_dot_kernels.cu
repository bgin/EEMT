

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
// Generic dot product kernel.
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


__forceinline__ 
__device__ void block_reduce_r4(float * __restrict__ z, 
                                volatile float * __restrict__ smem, 
                                float sum, 
                                const int32_t tid,
                                const int32_t BLOCKSIZE_n)
{
	smem[tid] = sum;
	__syncthreads();
	if (BLOCKSIZE_n >= 1024) { if (tid < 512) { smem[tid] += smem[tid + 512]; } __syncthreads(); }
	if (BLOCKSIZE_n >= 512) { if (tid < 256) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 480) { if (tid < 224) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 448) { if (tid < 192) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 416) { if (tid < 160) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 384) { if (tid < 128) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n >= 256) { if (tid < 128) { smem[tid] += smem[tid + 128]; } __syncthreads(); }
	if (BLOCKSIZE_n == 352) { if (tid < 96) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 224) { if (tid < 96) { smem[tid] += smem[tid + 128]; } __syncthreads(); }
	if (BLOCKSIZE_n == 320) { if (tid < 64) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 192) { if (tid < 64) { smem[tid] += smem[tid + 128]; } __syncthreads(); }
	if (BLOCKSIZE_n >= 128) { if (tid < 64) { smem[tid] += smem[tid + 64]; } __syncthreads(); }
	if (BLOCKSIZE_n == 288) { if (tid < 32) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 160) { if (tid < 32) { smem[tid] += smem[tid + 128]; } __syncthreads(); }
	if (BLOCKSIZE_n == 96) { if (tid < 32) { smem[tid] += smem[tid + 64]; } __syncthreads(); }
	if (BLOCKSIZE_n >= 64) { if (tid < 32) { smem[tid] += smem[tid + 32]; } }
	if (BLOCKSIZE_n >= 32) { if (tid < 16) { smem[tid] += smem[tid + 16]; } }
	if (BLOCKSIZE_n >= 16) { if (tid < 8) { smem[tid] += smem[tid + 8]; } }
	if (BLOCKSIZE_n >= 8) { if (tid < 4) { smem[tid] += smem[tid + 4]; } }
	if (BLOCKSIZE_n >= 4) { if (tid < 2) { smem[tid] += smem[tid + 2]; } }
	if (tid == 0) atomicFloatAdd(z, smem[tid] + smem[tid + 1]); 
}

__forceinline__ 
__device__ void block_reduce_r8(double * __restrict__ z, 
                                volatile double * __restrict__ smem, 
                                double sum, 
                                const int32_t tid,
                                const int32_t BLOCKSIZE_n)
{
	smem[tid] = sum;
	__syncthreads();
	if (BLOCKSIZE_n >= 1024) { if (tid < 512) { smem[tid] += smem[tid + 512]; } __syncthreads(); }
	if (BLOCKSIZE_n >= 512) { if (tid < 256) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 480) { if (tid < 224) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 448) { if (tid < 192) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 416) { if (tid < 160) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 384) { if (tid < 128) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n >= 256) { if (tid < 128) { smem[tid] += smem[tid + 128]; } __syncthreads(); }
	if (BLOCKSIZE_n == 352) { if (tid < 96) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 224) { if (tid < 96) { smem[tid] += smem[tid + 128]; } __syncthreads(); }
	if (BLOCKSIZE_n == 320) { if (tid < 64) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 192) { if (tid < 64) { smem[tid] += smem[tid + 128]; } __syncthreads(); }
	if (BLOCKSIZE_n >= 128) { if (tid < 64) { smem[tid] += smem[tid + 64]; } __syncthreads(); }
	if (BLOCKSIZE_n == 288) { if (tid < 32) { smem[tid] += smem[tid + 256]; } __syncthreads(); }
	if (BLOCKSIZE_n == 160) { if (tid < 32) { smem[tid] += smem[tid + 128]; } __syncthreads(); }
	if (BLOCKSIZE_n == 96) { if (tid < 32) { smem[tid] += smem[tid + 64]; } __syncthreads(); }
	if (BLOCKSIZE_n >= 64) { if (tid < 32) { smem[tid] += smem[tid + 32]; } }
	if (BLOCKSIZE_n >= 32) { if (tid < 16) { smem[tid] += smem[tid + 16]; } }
	if (BLOCKSIZE_n >= 16) { if (tid < 8) { smem[tid] += smem[tid + 8]; } }
	if (BLOCKSIZE_n >= 8) { if (tid < 4) { smem[tid] += smem[tid + 4]; } }
	if (BLOCKSIZE_n >= 4) { if (tid < 2) { smem[tid] += smem[tid + 2]; } }
	if (tid == 0) atomicDoubleAdd(z, smem[tid] + smem[tid + 1]); 
}




__global__ void dot_kernel_r4(const float * __restrict__ x, 
                              const float * __restrict__ y, 
                              float * __restrict__ z, 
                              const int32_t n, 
                              const int32_t ntile,
                              const int32_t BLOCKSIZE_n,
                              const int32_t WORKSIZE_m,
                              const int32_t WORKSIZE_n)
{
	const int tid = threadIdx.x;
	const int idx = blockIdx.x * BLOCKSIZE_n * WORKSIZE_n;
	x += idx + tid;
	y += idx + tid;
	float sum = 0.0f;
	if (idx != ntile)
	{
        #pragma unroll
           for (int i = 0; i < WORKSIZE_n; i++ ){				
													
		sum += x[0] * y[0]; x += BLOCKSIZE_n; y += BLOCKSIZE_n;		
	   }
		//inner_loop(WORKSIZE_n);
	}
	else
	{
        #pragma unroll 4
           for (int i = 0; i < n-idx-tid; i += BLOCKSIZE_n) {
	
		sum += x[i] * y[i];
	    }  
		//inner_loop2(n - idx - tid);
	}
	__shared__ volatile float smem[BLOCKSIZE_n];
	block_reduce_r4(z, smem, sum, tid);
}


__global__ void dot_kernel_r8(const double * __restrict__ x, 
                              const double * __restrict__ y, 
                              double * __restrict__ z, 
                              const int32_t n, 
                              const int32_t ntile,
                              const int32_t BLOCKSIZE_n,
                              const int32_t WORKSIZE_m,
                              const int32_t WORKSIZE_n)
{
	const int tid = threadIdx.x;
	const int idx = blockIdx.x * BLOCKSIZE_n * WORKSIZE_n;
	x += idx + tid;
	y += idx + tid;
	double sum = 0.0f;
	if (idx != ntile)
	{
        #pragma unroll
           for (int i = 0; i < WORKSIZE_n; i++ ){				
													
		sum += x[0] * y[0]; x += BLOCKSIZE_n; y += BLOCKSIZE_n;		
	   }
		//inner_loop(WORKSIZE_n);
	}
	else
	{
        #pragma unroll 4
           for (int i = 0; i < n-idx-tid; i += BLOCKSIZE_n) {
	
		sum += x[i] * y[i];
	    }  
		//inner_loop2(n - idx - tid);
	}
	__shared__ volatile double smem[BLOCKSIZE_n];
	block_reduce_r8(z, smem, sum, tid);
}





