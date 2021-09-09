
#ifndef __GMS_MKL_BETARNG_H__
#define __GMS_MKL_BETARNG_H__

namespace file_info {
 
const unsigned int gGMS_MKL_BETARNG_MAJOR = 1;

const unsigned int gGMS_MKL_BETARNG_MINOR = 1;

const unsigned int gGMS_MKL_BETARNG_MICRO = 0;

const unsigned int gGMS_MKL_BETARNG_FULLVER = 
	1000U*gGMS_MKL_BETARNG_MAJOR + 100U*gGMS_MKL_BETARNG_MINOR + 10U*gGMS_MKL_BETARNG_MICRO;



const char * const pgGMS_MKL_BETARNG_CREATE_DATE = "25-04-2018 15:37 +00200 (WED 25 APR 2018 GMT+2)";

const char * const pgGMS_MKL_BETARNG_BUILD_DATE = __DATE__ ":" __TIME__;

const char * const pgGMS_MKL_BETARNG_AUTHOR = "Programmer: Bernard Gingold, e-mail: beniekg@gmail.com";

const char * const pgGMS_MKL_BETARNG_DESCRIPT = "C++ wrapper around Intel MKL vdRngBeta procedure.";

}

#include <iostream>
#include "GMS_config.h"
#if (USE_MKL) == 1
#include <mkl_vsl.h>
#endif

namespace gms {
	namespace math {
		namespace stat {
				
				//
				//	C++ wrapper for Intel MKL vdRngBeta procedure.
				//


			__attribute__((align(64))) struct MKLBRNGData {

			         // POD and trivial type.
				// Payload aligned on 8-byte and starting at 64-byte boundary.

			        double * __restrict m_rvec;

				double m_p;
				double m_q;
				double m_a;
				double m_beta;
#if (USE_STRUCT_PADDING) == 1
				PAD_TO(1,8)
#endif
				MKL_INT m_nvalues;
				MKL_INT m_brng;
				MKL_INT m_seed;
				MKL_INT m_error;
			};

			  __attribute__((align(64))) struct MKLBetaRNG {

				  

					
					MKLBRNGData datum;
					

					//
					//	Construction and destruction
					//

					MKLBetaRNG();

					MKLBetaRNG(const MKL_INT,
						   const MKL_UINT,
						   const MKL_INT,
					           const double,
						   const double,
						   const double,
						   const double);

					MKLBetaRNG(const MKLBetaRNG &);

					MKLBetaRNG(MKLBetaRNG &&)noexcept(true);

					~MKLBetaRNG()noexcept(true);

					MKLBetaRNG & operator=(const MKLBetaRNG &);

					MKLBetaRNG & operator=(MKLBetaRNG &&)noexcept(true);

					void compute_rand_distribution(const MKL_INT);

					void compute_rand_distribution(VSLStreamStatePtr,const MKL_INT);

			};

			std::ostream &
			operator<<(std::ostream &,
				   const MKLBetaRNG &);
		}
	}
}


#endif /*__GMS_MKL_BETARNG_H_*/
