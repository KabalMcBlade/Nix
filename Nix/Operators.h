#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"

#include "VectorHelper.h"

NIX_NAMESPACE_BEGIN

static NIX_INLINE __nixFloat4   operator!   (__nixFloat4 a) { a = _mm_andnot_ps(a, VectorHelper::GetSignMask()); return a; }
static NIX_INLINE __nixFloat4   operator~   (__nixFloat4 a) { a = _mm_andnot_ps(a, VectorHelper::GetNotAll()); return a; }
static NIX_INLINE __nixFloat4   operator&   (__nixFloat4 a, __nixFloat4 b) { a = _mm_and_ps(a, b); return a; }
static NIX_INLINE __nixFloat4   operator|   (__nixFloat4 a, __nixFloat4 b) { a = _mm_or_ps(a, b); return a; }
static NIX_INLINE __nixFloat4   operator^   (__nixFloat4 a, __nixFloat4 b) { a = _mm_xor_ps(a, b); return a; }
static NIX_INLINE __nixFloat4&  operator&=  (__nixFloat4& a, __nixFloat4 b) { a = a & b; return a; }
static NIX_INLINE __nixFloat4&  operator|=  (__nixFloat4& a, __nixFloat4 b) { a = a | b; return a; }
static NIX_INLINE __nixFloat4&  operator^=  (__nixFloat4& a, __nixFloat4 b) { a = a ^ b; return a; }

static NIX_INLINE __nixInt4   operator!   (__nixInt4 a) { a = _mm_andnot_si128(a, VectorHelper::GetSignMaskI()); return a; }
static NIX_INLINE __nixInt4   operator~   (__nixInt4 a) { a = _mm_andnot_si128(a, VectorHelper::GetNotAllI()); return a; }
static NIX_INLINE __nixInt4   operator&   (__nixInt4 a, __nixInt4 b) { a = _mm_and_si128(a, b); return a; }
static NIX_INLINE __nixInt4   operator|   (__nixInt4 a, __nixInt4 b) { a = _mm_or_si128(a, b); return a; }
static NIX_INLINE __nixInt4   operator^   (__nixInt4 a, __nixInt4 b) { a = _mm_xor_si128(a, b); return a; }
static NIX_INLINE __nixInt4&  operator&=  (__nixInt4& a, __nixInt4 b) { a = a & b; return a; }
static NIX_INLINE __nixInt4&  operator|=  (__nixInt4& a, __nixInt4 b) { a = a | b; return a; }
static NIX_INLINE __nixInt4&  operator^=  (__nixInt4& a, __nixInt4 b) { a = a ^ b; return a; }


static NIX_INLINE __nixFloat4   operator+   (__nixFloat4 a) { return a; }
static NIX_INLINE __nixFloat4   operator+   (__nixFloat4 a, __nixFloat4 b) { a = _mm_add_ps(a, b); return a; }
static NIX_INLINE __nixFloat4&  operator+=  (__nixFloat4& a, __nixFloat4 b) { a = a + b; return a; }
static NIX_INLINE __nixFloat4   operator-   (__nixFloat4 a) { a = _mm_xor_ps(a, VectorHelper::GetSignMask()); return a; }
static NIX_INLINE __nixFloat4   operator-   (__nixFloat4 a, __nixFloat4 b) { a = _mm_sub_ps(a, b); return a; }
static NIX_INLINE __nixFloat4&  operator-=  (__nixFloat4& a, __nixFloat4 b) { a = a - b; return a; }
static NIX_INLINE __nixFloat4   operator*   (__nixFloat4 a, __nixFloat4 b) { a = _mm_mul_ps(a, b); return a; }
static NIX_INLINE __nixFloat4&  operator*=  (__nixFloat4& a, __nixFloat4 b) { a = a * b; return a; }
static NIX_INLINE __nixFloat4   operator/   (__nixFloat4 a, __nixFloat4 b) { a = _mm_div_ps(a, b); return a; }
static NIX_INLINE __nixFloat4&  operator/=  (__nixFloat4& a, __nixFloat4 b) { a = a / b; return a; }


static NIX_INLINE __nixInt4   operator+   (__nixInt4 a) { return a; }
static NIX_INLINE __nixInt4   operator+   (__nixInt4 a, __nixInt4 b) { a = _mm_add_epi32(a, b); return a; }
static NIX_INLINE __nixInt4&  operator+=  (__nixInt4& a, __nixInt4 b) { a = a + b; return a; }
static NIX_INLINE __nixInt4   operator-   (__nixInt4 a) { a = _mm_xor_si128(a, VectorHelper::GetSignMaskI()); return a; }
static NIX_INLINE __nixInt4   operator-   (__nixInt4 a, __nixInt4 b) { a = _mm_sub_epi32(a, b); return a; }
static NIX_INLINE __nixInt4&  operator-=  (__nixInt4& a, __nixInt4 b) { a = a - b; return a; }
static NIX_INLINE __nixInt4   operator*   (__nixInt4 a, __nixInt4 b) { a = _mm_mul_epu32(a, b); return a; }
static NIX_INLINE __nixInt4&  operator*=  (__nixInt4& a, __nixInt4 b) { a = a * b; return a; }



static NIX_INLINE __nixInt4   operator<<  (__nixInt4 a, nixU8 bits) { a = _mm_slli_epi32(a, bits); return a; }
static NIX_INLINE __nixInt4   operator >> (__nixInt4 a, nixU8 bits) { a = _mm_srli_epi32(a, bits); return a; }
static NIX_INLINE __nixInt4&  operator<<= (__nixInt4& a, nixU8 bits) { a = a << bits; return a; }
static NIX_INLINE __nixInt4&  operator>>= (__nixInt4& a, nixU8 bits) { a = a >> bits; return a; }

static NIX_INLINE __nixFloat4   cmpeq(__nixFloat4 a, __nixFloat4 b) { return __nixFloat4(_mm_cmpeq_ps(a, b)); }
static NIX_INLINE __nixFloat4   cmpneq(__nixFloat4 a, __nixFloat4 b) { return __nixFloat4(_mm_cmpneq_ps(a, b)); }
static NIX_INLINE __nixFloat4   cmpgt(__nixFloat4 a, __nixFloat4 b) { return __nixFloat4(_mm_cmpgt_ps(a, b)); }
static NIX_INLINE __nixFloat4   cmpge(__nixFloat4 a, __nixFloat4 b) { return __nixFloat4(_mm_cmpge_ps(a, b)); }
static NIX_INLINE __nixFloat4   cmplt(__nixFloat4 a, __nixFloat4 b) { return __nixFloat4(_mm_cmplt_ps(a, b)); }
static NIX_INLINE __nixFloat4   cmple(__nixFloat4 a, __nixFloat4 b) { return __nixFloat4(_mm_cmple_ps(a, b)); }

static NIX_INLINE __nixInt4   cmpeq(__nixInt4 a, __nixInt4 b) { return __nixInt4(_mm_cmpeq_epi32(a, b)); }
//static NIX_INLINE __nixInt4   cmpneq(__nixInt4 a, __nixInt4 b) { return __nixInt4(_mm_cmpneq_ss(a, b)); }
static NIX_INLINE __nixInt4   cmpgt(__nixInt4 a, __nixInt4 b) { return __nixInt4(_mm_cmpgt_epi32(a, b)); }
//static NIX_INLINE __nixInt4   cmpge(__nixInt4 a, __nixInt4 b) { return __nixInt4(_mm_cmpge_ss(a, b)); }
static NIX_INLINE __nixInt4   cmplt(__nixInt4 a, __nixInt4 b) { return __nixInt4(_mm_cmplt_epi32(a, b)); }
//static NIX_INLINE __nixInt4   cmple(__nixInt4 a, __nixInt4 b) { return __nixInt4(_mm_cmple_ss(a, b)); }

static NIX_INLINE __nixFloat4   abs(__nixFloat4 v) { v = _mm_andnot_ps(VectorHelper::GetSignMask(), v); return v; }
static NIX_INLINE __nixFloat4   sign(__nixFloat4 v) { return (cmplt(v, VectorHelper::GetZero()) & VectorHelper::GetMinusOne()) | (cmpgt(v, VectorHelper::GetZero()) & VectorHelper::GetOne()); } //https://github.com/g-truc/glm/blob/master/glm/simd/common.h#L99
static NIX_INLINE __nixFloat4   minv(__nixFloat4 a, __nixFloat4 b) { a = _mm_min_ps(a, b); return a; }
static NIX_INLINE __nixFloat4   maxv(__nixFloat4 a, __nixFloat4 b) { a = _mm_max_ps(a, b); return a; }
static NIX_INLINE __nixFloat4   clamp(__nixFloat4 t, __nixFloat4 a, __nixFloat4 b) { return minv(maxv(t, a), b); }

static NIX_INLINE nixU32    mask(__nixInt4 v) { return 0x8888 & _mm_movemask_epi8(v); }
static NIX_INLINE nixU32    any(__nixInt4 v) { return mask(v); }
static NIX_INLINE nixU32    none(__nixInt4 v) { return !any(v); }
static NIX_INLINE nixU32    all(__nixInt4 v) { return 0x8888 == mask(v); }

static NIX_INLINE __nixFloat4   operator+  (__nixFloat4 a, nixFloat b) { return a + VectorHelper::Splat(b); }
static NIX_INLINE __nixFloat4&  operator+= (__nixFloat4& a, nixFloat b) { return a += VectorHelper::Splat(b); }
static NIX_INLINE __nixFloat4   operator-  (__nixFloat4 a, nixFloat b) { return a - VectorHelper::Splat(b); }
static NIX_INLINE __nixFloat4&  operator-= (__nixFloat4& a, nixFloat b) { return a -= VectorHelper::Splat(b); }
static NIX_INLINE __nixFloat4   operator*  (__nixFloat4 a, nixFloat b) { return a * VectorHelper::Splat(b); }
static NIX_INLINE __nixFloat4&  operator*= (__nixFloat4& a, nixFloat b) { return a *= VectorHelper::Splat(b); }
static NIX_INLINE __nixFloat4   operator/  (__nixFloat4 a, nixFloat b) { return a / VectorHelper::Splat(b); }
static NIX_INLINE __nixFloat4&  operator/= (__nixFloat4& a, nixFloat b) { return a /= VectorHelper::Splat(b); }

static NIX_INLINE __nixFloat4   operator+  (nixFloat a, __nixFloat4 b) { return VectorHelper::Splat(a) + b; }
static NIX_INLINE __nixFloat4   operator-  (nixFloat a, __nixFloat4 b) { return VectorHelper::Splat(a) - b; }
static NIX_INLINE __nixFloat4   operator*  (nixFloat a, __nixFloat4 b) { return VectorHelper::Splat(a) * b; }
static NIX_INLINE __nixFloat4   operator/  (nixFloat a, __nixFloat4 b) { return VectorHelper::Splat(a) / b; }


NIX_NAMESPACE_END
