
//
//	Implementation
//

gms::math::
AVX512VecF64::AVX512VecF64()
:
m_v8(_mm512_setzero_pd()) {}

gms::math::
AVX512VecF64::AVX512VecF64(const double v[8])
:
m_v8(_mm512_loadu_pd(&v[0])) {}

gms::math::
AVX512VecF64::AVX512VecF64(const double s)
:
m_v8(_mm512_set1_pd(s)) {}

gms::math::
AVX512VecF64::AVX512VecF64(const double s0,
		          const double s1,
					   const double s2,
					   const double s3,
					  const double s4,
					  const double s5,
					 const double s6,
					 const double s7)
:
m_v8(_mm512_set_pd(s0, s1, s2, s3, s4, s5, s6, s7)) {}

gms::math::
AVX3VecF64::AVX512VecF64(const __m512d v)
:
m_v8(v) {}

gms::math::
AVX512VecF64::AVX512VecF64(_In_ const __m512i v)
:
m_v8(_mm512_castsi512_pd(v)) {}

gms::math::
AVX512VecF64::AVX512VecF64(const AVX512VecF64 &x)
:
m_v8(x.m_vf64) {}

gms::math::
AVX512VecF64::AVX512VecF64(const __m256d v0,
		          const __m256d v1) {
	m_vf64 = _mm512_insertf64x4(m_vf64,v0,0);
	m_vf64 = _mm512_insertf64x4(m_vf64,v1,1);
}

const __m512d
gms::math::AVX512VecF64::get_vf64() const {
	return (m_v8);
}

__m512d
gms::math::AVX512VecF64::get_vf64() {
	return (m_v8);
}

__m256d
gms::math::AVX512VecF64::lo_part() const {
	return (_mm512_extractf64x4_pd(m_v8,0));
}

__m256d
gms::math::AVX512VecF64::hi_part() const {
	return (_mm512_extractf64x4_pd(m_v8,1));
}

gms::math::AVX512VecF64 &
gms::math::AVX512VecF64::load_a(const double* __restrict address) {
	m_v8 = _mm512_load_pd(address);
	return (*this);
}

gms::math::AVX512VecF64 &
gms::math::AVX512VecF64::load_u(const double* __restrict address) {
	m_vf64 = _mm512_loadu_pd(address);
	return (*this);
}

void 
gms::math::AVX512VecF64::store_a(double* __restrict dest) const {
	_mm512_store_pd(&dest[0],m_v8);
}

void
gms::math::AVX512VecF64::store_u(double* __restrict dest) const {
	_mm512_storeu_pd(&dest[0],m_v8);
}

void
gms::math::AVX512VecF64::stream_store(double* __restrict dest) const {
	_mm512_stream_pd(&dest[0],m_v8);
}

double
gms::math::AVX512VecF64::extract_scalar(const uint32_t idx) const {
	__declspec(align(64))double t[8] = {};
	store_a(t);
	return (t[idx&7]);
}

gms::math::AVX512VecF64 &
gms::math::AVX512VecF64::operator=(const AVX512VecF64 &x) {
	if (this == &x)
		return (*this);
	m_vf64 = x.m_v8;
	return (*this);
}

gms::math::AVX512VecF64::operator __m512d () const {
	return (m_v8);
}

double
gms::math::AVX512VecF64::operator[](const uint32_t idx) const {
	return (reinterpret_cast<const double*>(&m_v8)[idx]);
}

std::ostream &
gms::math::operator<<(std::ostream &os,
					  const AVX512VecF64 &x) {
	for (uint32_t i = 0; i != 7; ++i){
	     os << std::fixed << std::showpoint << 
		 "at position: " << i <<  x[i] << std::endl;
	  }	
	return (os);
}

__m256d
gms::math::extract(const AVX512VecF64 &x,
				   const int32_t idx) {
	return (_mm512_extractf64x4_pd(x,idx));
}

gms::math::AVX512VecF64
gms::math::select(const AVX512VecF64 &x,
				  const AVX512VecF64 &y,
				  const __mmask8 pred) {
	return (_mm512_mask_blend_pd(pred,x,y));
}

gms::math::AVX512VecF64
gms::math::simd_max(const AVX512VecF64 &x,
	            const AVX512VecF64 &y) {
	return (_mm512_max_pd(x,y));
}

gms::math::AVX512VecF64
gms::math::simd_min(const AVX512VecF64 &x,
			   _In_ const AVX512VecF64 &y) {
	return (_mm512_min_pd(x,y));
}

gms::math::AVX512VecF64
gms::math::abs(const AVX512VecF64 &x) {
	return (_mm512_abs_pd(x));
}

gms::math::AVX512VecF64
gms::math::sqrt(const AVX512VecF64 &x) {
	return (_mm512_sqrt_pd(x));
}

gms::math::AVX512VecF64
gms::math::rsqrt(const AVX512VecF64 &x) {
	return (_mm512_rsqrt14_pd(x));
}

gms::math::AVX512VecF64
gms::math::cbrt(const AVX512VecF64 &x) {
	return (_mm512_cbrt_pd(x));
}

double
gms::math::reduce_add(const AVX512VecF64 &x) {
	return (_mm512_reduce_add_pd(x));
}

double
gms::math::reduce_mul(const AVX512VecF64 &x) {
	return (_mm512_reduce_mul_pd(x));
}

double
gms::math::reduce_max(const AVX512VecF64 &x) {
	return (_mm512_reduce_max_pd(x));
}

double
gms::math::reduce_min(const AVX512VecF64 &x) {
	return (_mm512_reduce_min_pd(x));
}

gms::math::AVX512VecF64
gms::math::ceil(const AVX512VecF64 &x) {
	return (_mm512_ceil_pd(x));
}

gms::math::AVX512VecF64
gms::math::floor(const AVX512VecF64 &x) {
	return (_mm512_floor_pd(x));
}

gms::math::AVX512VecF64
gms::math::round(const AVX512VecF64 &x,
		const int32_t imm) {
	return (_mm512_roundscale_pd(x,imm));
}

gms::math::AVX512VecF64
gms::math::sin(const AVX512VecF64 &x) {
	return (_mm512_sin_pd(x));
}

gms::math::AVX512VecF64
gms::math::sind(const AVX512VecF64 &x) {
	return (_mm512_sind_pd(x));
}

gms::math::AVX512VecF64
gms::math::cos(const AVX512VecF64 &x) {
	return (_mm512_cos_pd(x));
}

gms::math::AVX512VecF64
gms::math::cosd(const AVX512VecF64 &x) {
	return (_mm512_cosd_pd(x));
}

gms::math::AVX512VecF64
gms::math::sinh(const AVX512VecF64 &x) {
	return (_mm512_sinh_pd(x));
}

gms::math::AVX512VecF64
gms::math::cosh(const AVX512VecF64 &x) {
	return (_mm512_cosh_pd(x));
}

gms::math::AVX3VecF64
gms::math::tan(const AVX512VecF64 &x) {
	return (_mm512_tan_pd(x));
}

gms::math::AVX512VecF64
gms::math::tanh(const AVX512VecF64 &x) {
	return (_mm512_tanh_pd(x));
}

gms::math::AVX512VecF64
gms::math::asin(const AVX512VecF64 &x) {
	return (_mm512_asin_pd(x));
}

gms::math::AVX512VecF64
gms::math::asinh(const AVX512VecF64 &x) {
	return (_mm512_asinh_pd(x));
}

gms::math::AVX512VecF64
gms::math::acos(const AVX512VecF64 &x) {
	return (_mm512_acos_pd(x));
}

gms::math::AVX512VecF64
gms::math::acosh(const AVX512VecF64 &x) {
	return (_mm512_acosh_pd(x));
}

gms::math::AVX512VecF64
gms::math::atan(const AVX512VecF64 &x) {
	return (_mm512_atan_pd(x));
}

gms::math::AVX512VecF64
gms::math::atanh(const AVX512VecF64 &x) {
	return (_mm512_atanh_pd(x));
}

gms::math::AVX512VecF64
gms::math::log(const AVX512VecF64 &x) {
	return (_mm512_log_pd(x));
}

gms::math::AVX512VecF64
gms::math::exp(const AVX512VecF64 &x) {
	return (_mm512_exp_pd(x));
}

gms::math::AVX512VecF64
gms::math::atan2(const AVX512VecF64 &x,
				const AVX512VecF64 &y) {
	return (_mm512_atan2_pd(x,y));
}

gms::math::AVX512VecF64
gms::math::hypot(const AVX512VecF64 &x,
		const AVX512VecF64 &y) {
	return (_mm512_hypot_pd(x,y));
}

gms::math::AVX512VecF64
gms::math::fmadd(const AVX512VecF64 &x,
				 const AVX512VecF64 &y,
			const AVX512VecF64 &z) {
	return (_mm512_fmadd_pd(x,y,z));
}

gms::math::AVX512VecF64
gms::math::fmadsubb(const AVX512VecF64 &x,
		   const AVX512VecF64 &y,
		   const AVX512VecF64 &z) {
	return (_mm512_fmaddsub_pd(x,y,z));
}

gms::math::AVX512VecF64
gms::math::fmsub(const AVX512VecF64 &x,
				const AVX512VecF64 &y,
				 const AVX512VecF64 &z) {
	return (_mm512_fmsub_pd(x,y,z));
}

gms::math::AVX512VecF64
gms::math::fmsubadd(const AVX512VecF64 &x,
				const AVX512VecF64 &y,
			const AVX512VecF64 &z) {
	return (_mm512_fmsubadd_pd(x,y,z));
}

gms::math::AVX512VecF64
gms::math::fnmadd(const AVX512VecF64 &x,
		const AVX512VecF64 &y,
		const AVX512VecF64 &z) {
	return (_mm512_fnmadd_pd(x,y,z));
}

gms::math::AVX512VecF64
gms::math::fnmsub(const AVX3VecF64 &x,
	          const AVX512VecF64 &y,
		  const AVX512VecF64 &z) {
	return (_mm512_fnmsub_pd(x,y,z));
}

gms::math::AVX512VecF64
gms::math::operator+(const AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	return (_mm512_add_pd(x,y));
}

gms::math::AVX512VecF64
gms::math::operator+(const AVX512VecF64 &x,
		    const double s) {
	return (x + AVX512VecF64(s));
}

gms::math::AVX512VecF64
gms::math::operator+(const double s,
		const AVX512VecF64 &x) {
	return (AVX512VecF64{s} + x);
}

gms::math::AVX512VecF64
gms::math::operator+=(AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	x = x + y;
	return (x);
}

gms::math::AVX512VecF64
gms::math::operator-(const AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	return (_mm512_sub_pd(x,y));
}

gms::math::AVX512VecF64
gms::math::operator-(const AVX512VecF64 &x,
		const double s) {
	return (x - AVX512VecF64{s});
}

gms::math::AVX512VecF64
gms::math::operator-(const double s,
			const AVX512VecF64 &x) {
	return (AVX512VecF64{s} - x);
}

gms::math::AVX512VecF64
gms::math::operator-=(		 AVX512VecF64 &x,
					  const AVX512VecF64 &y) {
	x = x - y;
	return (x);
}

gms::math::AVX512VecF64
gms::math::operator*(const AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	return (_mm512_mul_pd(x,y));
}

gms::math::AVX512VecF64
gms::math::operator*(const AVX512VecF64 &x,
			const double s) {
	return (x * AVX512VecF64{s});
}

gms::math::AVX512VecF64
gms::math::operator*(const double s,
			const AVX512VecF64 &x) {
	return (AVX512VecF64{s} * x);
}

gms::math::AVX512VecF64
gms::math::operator*=(AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	x = x * y;
	return (x);
}

gms::math::AVX512VecF64
gms::math::operator/(const AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	return (_mm512_div_pd(x,y));
}

gms::math::AVX512VecF64
gms::math::operator/(const AVX512VecF64 &x,
					 const double s) {
	return (x / AVX512VecF64{s});
}

gms::math::AVX512VecF64
gms::math::operator/(const double s,
			const AVX512VecF64 &x) {
	return (AVX512VecF64{s} / x);
}

gms::math::AVX3VecF64
gms::math::operator/=(       AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	x = x / y;
	return (x);
}

__mmask8
gms::math::operator==(const AVX512VecF64 &x,
					  const AVX512VecF64 &y) {
	return (_mm512_cmp_pd_mask(x,y,_CMP_EQ_OQ));
}

__mmask8
gms::math::operator!=(const AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	return (_mm512_cmp_pd_mask(x,y,_CMP_NEQ_OQ));
}

__mmask8
gms::math::operator>(const AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	return (_mm512_cmp_pd_mask(x,y,_CMP_GT_OQ));
}

__mmask8
gms::math::operator<(_const AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	return (_mm512_cmp_pd_mask(x,y,_CMP_LT_OQ));
}

__mmask8
gms::math::operator>=(const AVX512VecF64 &x,
					  _const AVX512VecF64 &y) {
	return (_mm512_cmp_pd_mask(x,y,_CMP_GE_OQ));
}

__mmask8
gms::math::operator<=(const AVX512VecF64 &x,
					 const AVX512VecF64 &y) {
	return (_mm512_cmp_pd_mask(x,y,_CMP_LE_OQ));
}

gms::math::AVX3VecF64
gms::math::operator&(_In_ const AVX3VecF64 &x,
					 _In_ const AVX3VecF64 &y) {
	return (_mm512_and_pd(x,y));
}

gms::math::AVX3VecF64
gms::math::operator&=(AVX512VecF64 &x,
					  const AVX512VecF64 &y) {
	x = x & y;
	return (x);
}

gms::math::AVX3VecF64
gms::math::operator|(const AVX512VecF64 &x,
		     const AVX512VecF64 &y) {
	return (_mm512_or_pd(x,y));
}

gms::math::AVX512VecF64
gms::math::operator|=(AVX512VecF64 &x,
		      const AVX512VecF64 &y) {
	x = x | y;
	return (x);
}

gms::math::AVX512VecF64
gms::math::operator^(const AVX512VecF64 &x,
			const AVX512VecF64 &y) {
	return (_mm512_xor_pd(x,y));
}

gms::math::AVX512VecF64
gms::math::operator^=(AVX512VecF64 &x,
		     const AVX512VecF64 &y) {
	x = x ^ y;
	return (x);
}

gms::math::AVX512VecF64
gms::math::operator++(AVX512VecF64 &x) {
	x = x + 1.0;
	return (x);
}

gms::math::AVX512VecF64
gms::math::operator--(AVX512VecF64 &x) {
	x = x - 1.0;
	return (x);
}
			   
		

