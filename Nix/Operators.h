#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Constants.h"

NIX_NAMESPACE_BEGIN

static NIX_INLINE nixFloat4 FloatToFloat4(const nixFloat& _v)
{
#   if NIX_ARCH & NIX_ARCH_AVX_FLAG
    return _mm_broadcast_ss(&_v);
#   else
    return _mm_set1_ps(_v);
#   endif
}

static NIX_INLINE nixFloat4   operator!   (nixFloat4 a) { a = _mm_andnot_ps(a, kSignBit); return a; }
static NIX_INLINE nixFloat4   operator~   (nixFloat4 a) { a = _mm_andnot_ps(a, kNotAll); return a; }
static NIX_INLINE nixFloat4   operator&   (nixFloat4 a, nixFloat4 b) { a = _mm_and_ps(a, b); return a; }
static NIX_INLINE nixFloat4   operator|   (nixFloat4 a, nixFloat4 b) { a = _mm_or_ps(a, b); return a; }
static NIX_INLINE nixFloat4   operator^   (nixFloat4 a, nixFloat4 b) { a = _mm_xor_ps(a, b); return a; }
static NIX_INLINE nixFloat4&  operator&=  (nixFloat4& a, nixFloat4 b) { a = a & b; return a; }
static NIX_INLINE nixFloat4&  operator|=  (nixFloat4& a, nixFloat4 b) { a = a | b; return a; }
static NIX_INLINE nixFloat4&  operator^=  (nixFloat4& a, nixFloat4 b) { a = a ^ b; return a; }

static NIX_INLINE nixInt4   operator!   (nixInt4 a) { a = _mm_andnot_si128(a, kSignBit); return a; }
static NIX_INLINE nixInt4   operator~   (nixInt4 a) { a = _mm_andnot_si128(a, kNotAll); return a; }
static NIX_INLINE nixInt4   operator&   (nixInt4 a, nixInt4 b) { a = _mm_and_si128(a, b); return a; }
static NIX_INLINE nixInt4   operator|   (nixInt4 a, nixInt4 b) { a = _mm_or_si128(a, b); return a; }
static NIX_INLINE nixInt4   operator^   (nixInt4 a, nixInt4 b) { a = _mm_xor_si128(a, b); return a; }
static NIX_INLINE nixInt4&  operator&=  (nixInt4& a, nixInt4 b) { a = a & b; return a; }
static NIX_INLINE nixInt4&  operator|=  (nixInt4& a, nixInt4 b) { a = a | b; return a; }
static NIX_INLINE nixInt4&  operator^=  (nixInt4& a, nixInt4 b) { a = a ^ b; return a; }


static NIX_INLINE nixFloat4   operator+   (nixFloat4 a) { return a; }
static NIX_INLINE nixFloat4   operator+   (nixFloat4 a, nixFloat4 b) { a = _mm_add_ps(a, b); return a; }
static NIX_INLINE nixFloat4&  operator+=  (nixFloat4& a, nixFloat4 b) { a = a + b; return a; }
static NIX_INLINE nixFloat4   operator-   (nixFloat4 a) { a = _mm_xor_ps(a, kSignBit); return a; }
static NIX_INLINE nixFloat4   operator-   (nixFloat4 a, nixFloat4 b) { a = _mm_sub_ps(a, b); return a; }
static NIX_INLINE nixFloat4&  operator-=  (nixFloat4& a, nixFloat4 b) { a = a - b; return a; }
static NIX_INLINE nixFloat4   operator*   (nixFloat4 a, nixFloat4 b) { a = _mm_mul_ps(a, b); return a; }
static NIX_INLINE nixFloat4&  operator*=  (nixFloat4& a, nixFloat4 b) { a = a * b; return a; }
static NIX_INLINE nixFloat4   operator/   (nixFloat4 a, nixFloat4 b) { a = _mm_div_ps(a, b); return a; }
static NIX_INLINE nixFloat4&  operator/=  (nixFloat4& a, nixFloat4 b) { a = a / b; return a; }


static NIX_INLINE nixInt4   operator+   (nixInt4 a) { return a; }
static NIX_INLINE nixInt4   operator+   (nixInt4 a, nixInt4 b) { a = _mm_add_epi32(a, b); return a; }
static NIX_INLINE nixInt4&  operator+=  (nixInt4& a, nixInt4 b) { a = a + b; return a; }
static NIX_INLINE nixInt4   operator-   (nixInt4 a) { a = _mm_xor_si128(a, kSignBit); return a; }
static NIX_INLINE nixInt4   operator-   (nixInt4 a, nixInt4 b) { a = _mm_sub_epi32(a, b); return a; }
static NIX_INLINE nixInt4&  operator-=  (nixInt4& a, nixInt4 b) { a = a - b; return a; }
static NIX_INLINE nixInt4   operator*   (nixInt4 a, nixInt4 b) { a = _mm_mul_epu32(a, b); return a; }
static NIX_INLINE nixInt4&  operator*=  (nixInt4& a, nixInt4 b) { a = a * b; return a; }



static NIX_INLINE nixInt4   operator<<  (nixInt4 a, nixU8 bits) { a = _mm_slli_epi32(a, bits); return a; }
static NIX_INLINE nixInt4   operator >> (nixInt4 a, nixU8 bits) { a = _mm_srli_epi32(a, bits); return a; }
static NIX_INLINE nixInt4&  operator<<= (nixInt4& a, nixU8 bits) { a = a << bits; return a; }
static NIX_INLINE nixInt4&  operator>>= (nixInt4& a, nixU8 bits) { a = a >> bits; return a; }

static NIX_INLINE nixFloat4   cmpeq(nixFloat4 a, nixFloat4 b) { return nixFloat4(_mm_cmpeq_ps(a, b)); }
static NIX_INLINE nixFloat4   cmpneq(nixFloat4 a, nixFloat4 b) { return nixFloat4(_mm_cmpneq_ps(a, b)); }
static NIX_INLINE nixFloat4   cmpgt(nixFloat4 a, nixFloat4 b) { return nixFloat4(_mm_cmpgt_ps(a, b)); }
static NIX_INLINE nixFloat4   cmpge(nixFloat4 a, nixFloat4 b) { return nixFloat4(_mm_cmpge_ps(a, b)); }
static NIX_INLINE nixFloat4   cmplt(nixFloat4 a, nixFloat4 b) { return nixFloat4(_mm_cmplt_ps(a, b)); }
static NIX_INLINE nixFloat4   cmple(nixFloat4 a, nixFloat4 b) { return nixFloat4(_mm_cmple_ps(a, b)); }

static NIX_INLINE nixInt4   cmpeq(nixInt4 a, nixInt4 b) { return nixInt4(_mm_cmpeq_epi32(a, b)); }
//static NIX_INLINE nixInt4   cmpneq(nixInt4 a, nixInt4 b) { return nixInt4(_mm_cmpneq_ss(a, b)); }
static NIX_INLINE nixInt4   cmpgt(nixInt4 a, nixInt4 b) { return nixInt4(_mm_cmpgt_epi32(a, b)); }
//static NIX_INLINE nixInt4   cmpge(nixInt4 a, nixInt4 b) { return nixInt4(_mm_cmpge_ss(a, b)); }
static NIX_INLINE nixInt4   cmplt(nixInt4 a, nixInt4 b) { return nixInt4(_mm_cmplt_epi32(a, b)); }
//static NIX_INLINE nixInt4   cmple(nixInt4 a, nixInt4 b) { return nixInt4(_mm_cmple_ss(a, b)); }

static NIX_INLINE nixFloat4   abs(nixFloat4 v) { v = _mm_andnot_ps(kSignBit, v); return v; }
static NIX_INLINE nixFloat4   sign(nixFloat4 v) { return (cmplt(v, kZero) & kMinusOne) | (cmpgt(v, kZero) & kOne); } //https://github.com/g-truc/glm/blob/master/glm/simd/common.h#L99
static NIX_INLINE nixFloat4   minv(nixFloat4 a, nixFloat4 b) { a = _mm_min_ps(a, b); return a; }
static NIX_INLINE nixFloat4   maxv(nixFloat4 a, nixFloat4 b) { a = _mm_max_ps(a, b); return a; }
static NIX_INLINE nixFloat4   clamp(nixFloat4 t, nixFloat4 a, nixFloat4 b) { return minv(maxv(t, a), b); }

static NIX_INLINE nixU32    mask(nixInt4 v) { return 0x8888 & _mm_movemask_epi8(v); }
static NIX_INLINE nixU32    any(nixInt4 v) { return mask(v); }
static NIX_INLINE nixU32    none(nixInt4 v) { return !any(v); }
static NIX_INLINE nixU32    all(nixInt4 v) { return 0x8888 == mask(v); }

static NIX_INLINE nixFloat4   operator+  (nixFloat4 a, nixFloat b) { return a + FloatToFloat4(b); }
static NIX_INLINE nixFloat4&  operator+= (nixFloat4& a, nixFloat b) { return a += FloatToFloat4(b); }
static NIX_INLINE nixFloat4   operator-  (nixFloat4 a, nixFloat b) { return a - FloatToFloat4(b); }
static NIX_INLINE nixFloat4&  operator-= (nixFloat4& a, nixFloat b) { return a -= FloatToFloat4(b); }
static NIX_INLINE nixFloat4   operator*  (nixFloat4 a, nixFloat b) { return a * FloatToFloat4(b); }
static NIX_INLINE nixFloat4&  operator*= (nixFloat4& a, nixFloat b) { return a *= FloatToFloat4(b); }
static NIX_INLINE nixFloat4   operator/  (nixFloat4 a, nixFloat b) { return a / FloatToFloat4(b); }
static NIX_INLINE nixFloat4&  operator/= (nixFloat4& a, nixFloat b) { return a /= FloatToFloat4(b); }

static NIX_INLINE nixFloat4   operator+  (nixFloat a, nixFloat4 b) { return FloatToFloat4(a) + b; }
static NIX_INLINE nixFloat4   operator-  (nixFloat a, nixFloat4 b) { return FloatToFloat4(a) - b; }
static NIX_INLINE nixFloat4   operator*  (nixFloat a, nixFloat4 b) { return FloatToFloat4(a) * b; }
static NIX_INLINE nixFloat4   operator/  (nixFloat a, nixFloat4 b) { return FloatToFloat4(a) / b; }


NIX_NAMESPACE_END
