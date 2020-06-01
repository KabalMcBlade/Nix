#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "Constants.h"

NIX_NAMESPACE_BEGIN

static NIX_INLINE float128 FloatToFloat4(const float& _v)
{
#   if NIX_ARCH & NIX_ARCH_AVX_FLAG
    return _mm_broadcast_ss(&_v);
#   else
    return _mm_set1_ps(_v);
#   endif
}

static NIX_INLINE float128   operator!   (float128 a) { a = _mm_andnot_ps(a, kSignBit); return a; }
static NIX_INLINE float128   operator~   (float128 a) { a = _mm_andnot_ps(a, kNotAll); return a; }
static NIX_INLINE float128   operator&   (float128 a, float128 b) { a = _mm_and_ps(a, b); return a; }
static NIX_INLINE float128   operator|   (float128 a, float128 b) { a = _mm_or_ps(a, b); return a; }
static NIX_INLINE float128   operator^   (float128 a, float128 b) { a = _mm_xor_ps(a, b); return a; }
static NIX_INLINE float128&  operator&=  (float128& a, float128 b) { a = a & b; return a; }
static NIX_INLINE float128&  operator|=  (float128& a, float128 b) { a = a | b; return a; }
static NIX_INLINE float128&  operator^=  (float128& a, float128 b) { a = a ^ b; return a; }

static NIX_INLINE int128   operator!   (int128 a) { a = _mm_andnot_si128(a, kSignBit); return a; }
static NIX_INLINE int128   operator~   (int128 a) { a = _mm_andnot_si128(a, kNotAll); return a; }
static NIX_INLINE int128   operator&   (int128 a, int128 b) { a = _mm_and_si128(a, b); return a; }
static NIX_INLINE int128   operator|   (int128 a, int128 b) { a = _mm_or_si128(a, b); return a; }
static NIX_INLINE int128   operator^   (int128 a, int128 b) { a = _mm_xor_si128(a, b); return a; }
static NIX_INLINE int128&  operator&=  (int128& a, int128 b) { a = a & b; return a; }
static NIX_INLINE int128&  operator|=  (int128& a, int128 b) { a = a | b; return a; }
static NIX_INLINE int128&  operator^=  (int128& a, int128 b) { a = a ^ b; return a; }


static NIX_INLINE float128   operator+   (float128 a) { return a; }
static NIX_INLINE float128   operator+   (float128 a, float128 b) { a = _mm_add_ps(a, b); return a; }
static NIX_INLINE float128&  operator+=  (float128& a, float128 b) { a = a + b; return a; }
static NIX_INLINE float128   operator-   (float128 a) { a = _mm_xor_ps(a, kSignBit); return a; }
static NIX_INLINE float128   operator-   (float128 a, float128 b) { a = _mm_sub_ps(a, b); return a; }
static NIX_INLINE float128&  operator-=  (float128& a, float128 b) { a = a - b; return a; }
static NIX_INLINE float128   operator*   (float128 a, float128 b) { a = _mm_mul_ps(a, b); return a; }
static NIX_INLINE float128&  operator*=  (float128& a, float128 b) { a = a * b; return a; }
static NIX_INLINE float128   operator/   (float128 a, float128 b) { a = _mm_div_ps(a, b); return a; }
static NIX_INLINE float128&  operator/=  (float128& a, float128 b) { a = a / b; return a; }


static NIX_INLINE int128   operator+   (int128 a) { return a; }
static NIX_INLINE int128   operator+   (int128 a, int128 b) { a = _mm_add_epi32(a, b); return a; }
static NIX_INLINE int128&  operator+=  (int128& a, int128 b) { a = a + b; return a; }
static NIX_INLINE int128   operator-   (int128 a) { a = _mm_xor_si128(a, kSignBit); return a; }
static NIX_INLINE int128   operator-   (int128 a, int128 b) { a = _mm_sub_epi32(a, b); return a; }
static NIX_INLINE int128&  operator-=  (int128& a, int128 b) { a = a - b; return a; }
static NIX_INLINE int128   operator*   (int128 a, int128 b) { a = _mm_mul_epu32(a, b); return a; }
static NIX_INLINE int128&  operator*=  (int128& a, int128 b) { a = a * b; return a; }



static NIX_INLINE int128   operator<<  (int128 a, uint8 bits) { a = _mm_slli_epi32(a, bits); return a; }
static NIX_INLINE int128   operator >> (int128 a, uint8 bits) { a = _mm_srli_epi32(a, bits); return a; }
static NIX_INLINE int128&  operator<<= (int128& a, uint8 bits) { a = a << bits; return a; }
static NIX_INLINE int128&  operator>>= (int128& a, uint8 bits) { a = a >> bits; return a; }

static NIX_INLINE float128   cmpeq(float128 a, float128 b) { return float128(_mm_cmpeq_ps(a, b)); }
static NIX_INLINE float128   cmpneq(float128 a, float128 b) { return float128(_mm_cmpneq_ps(a, b)); }
static NIX_INLINE float128   cmpgt(float128 a, float128 b) { return float128(_mm_cmpgt_ps(a, b)); }
static NIX_INLINE float128   cmpge(float128 a, float128 b) { return float128(_mm_cmpge_ps(a, b)); }
static NIX_INLINE float128   cmplt(float128 a, float128 b) { return float128(_mm_cmplt_ps(a, b)); }
static NIX_INLINE float128   cmple(float128 a, float128 b) { return float128(_mm_cmple_ps(a, b)); }

static NIX_INLINE int128   cmpeq(int128 a, int128 b) { return int128(_mm_cmpeq_epi32(a, b)); }
//static NIX_INLINE int128   cmpneq(int128 a, int128 b) { return int128(_mm_cmpneq_ss(a, b)); }
static NIX_INLINE int128   cmpgt(int128 a, int128 b) { return int128(_mm_cmpgt_epi32(a, b)); }
//static NIX_INLINE int128   cmpge(int128 a, int128 b) { return int128(_mm_cmpge_ss(a, b)); }
static NIX_INLINE int128   cmplt(int128 a, int128 b) { return int128(_mm_cmplt_epi32(a, b)); }
//static NIX_INLINE int128   cmple(int128 a, int128 b) { return int128(_mm_cmple_ss(a, b)); }

static NIX_INLINE float128   abs(float128 v) { v = _mm_andnot_ps(kSignBit, v); return v; }
static NIX_INLINE float128   sign(float128 v) { return (cmplt(v, kZero) & kMinusOne) | (cmpgt(v, kZero) & kOne); } //https://github.com/g-truc/glm/blob/master/glm/simd/common.h#L99
static NIX_INLINE float128   minv(float128 a, float128 b) { a = _mm_min_ps(a, b); return a; }
static NIX_INLINE float128   maxv(float128 a, float128 b) { a = _mm_max_ps(a, b); return a; }
static NIX_INLINE float128   clamp(float128 t, float128 a, float128 b) { return minv(maxv(t, a), b); }

static NIX_INLINE uint32  mask(int128 v) { return 0x8888 & _mm_movemask_epi8(v); }
static NIX_INLINE uint8   any(int128 v) { return mask(v); }
static NIX_INLINE uint8   none(int128 v) { return !any(v); }
static NIX_INLINE uint8   all(int128 v) { return 0x8888 == mask(v); }

static NIX_INLINE uint32  mask(float128 v) { return 0x8888 & _mm_movemask_epi8(_mm_castps_si128(v)); }
static NIX_INLINE uint8   any(float128 v) { return mask(v); }
static NIX_INLINE uint8   none(float128 v) { return !any(v); }
static NIX_INLINE uint8   all(float128 v) { return 0x8888 == mask(v); }

static NIX_INLINE float128   operator+  (float128 a, float b) { return a + FloatToFloat4(b); }
static NIX_INLINE float128&  operator+= (float128& a, float b) { return a += FloatToFloat4(b); }
static NIX_INLINE float128   operator-  (float128 a, float b) { return a - FloatToFloat4(b); }
static NIX_INLINE float128&  operator-= (float128& a, float b) { return a -= FloatToFloat4(b); }
static NIX_INLINE float128   operator*  (float128 a, float b) { return a * FloatToFloat4(b); }
static NIX_INLINE float128&  operator*= (float128& a, float b) { return a *= FloatToFloat4(b); }
static NIX_INLINE float128   operator/  (float128 a, float b) { return a / FloatToFloat4(b); }
static NIX_INLINE float128&  operator/= (float128& a, float b) { return a /= FloatToFloat4(b); }

static NIX_INLINE float128   operator+  (float a, float128 b) { return FloatToFloat4(a) + b; }
static NIX_INLINE float128   operator-  (float a, float128 b) { return FloatToFloat4(a) - b; }
static NIX_INLINE float128   operator*  (float a, float128 b) { return FloatToFloat4(a) * b; }
static NIX_INLINE float128   operator/  (float a, float128 b) { return FloatToFloat4(a) / b; }


NIX_NAMESPACE_END
