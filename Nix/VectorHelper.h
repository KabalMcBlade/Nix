#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"


NIX_NAMESPACE_BEGIN


NIX_MEMORY_ALIGNMENT(NIX_MEMORY_ALIGNMENT_SIZE) class VectorHelper
{
public:
    static NIX_INLINE __nixFloat4 GetZero() { return _mm_setzero_ps(); }
    static NIX_INLINE __nixFloat4 GetOne() { return _mm_set1_ps(1.0f); }

    static NIX_INLINE __nixFloat4 Get0001() { return _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f); }
    static NIX_INLINE __nixFloat4 Get1110() { return _mm_set_ps(0.0f, 1.0f, 1.0f, 1.0f); }
    static NIX_INLINE __nixFloat4 GetMin() { return _mm_set1_ps(std::numeric_limits<nixFloat>::min()); }
    static NIX_INLINE __nixFloat4 GetMax() { return _mm_set1_ps(std::numeric_limits<nixFloat>::max()); }
    static NIX_INLINE __nixFloat4 GetPlusInf() { return _mm_set1_ps(std::numeric_limits<nixFloat>::infinity()); }
    static NIX_INLINE __nixFloat4 GetMinusInf() { return _mm_set1_ps(-std::numeric_limits<nixFloat>::infinity()); }

    static NIX_INLINE __nixFloat4 Set(nixFloat _x, nixFloat _y, nixFloat _z, nixFloat _w) { return _mm_set_ps(_w, _z, _y, _x); }
    static NIX_INLINE __nixFloat4 Splat(nixFloat _v) { return _mm_set1_ps(_v); }

    static NIX_INLINE __nixFloat4 Add(const __nixFloat4& _a, const __nixFloat4& _b) { return _mm_add_ps(_a, _b); }
    static NIX_INLINE __nixFloat4 Sub(const __nixFloat4& _a, const __nixFloat4& _b) { return _mm_sub_ps(_a, _b); }
    static NIX_INLINE __nixFloat4 Mul(const __nixFloat4& _a, const __nixFloat4& _b) { return _mm_mul_ps(_a, _b); }
    static NIX_INLINE __nixFloat4 Div(const __nixFloat4& _a, const __nixFloat4& _b) { return _mm_div_ps(_a, _b); }

    static NIX_INLINE __nixFloat4 Abs(const __nixFloat4& _v) { return _mm_andnot_ps(_mm_castsi128_ps(_mm_set1_epi32(0x80000000)), _v); }
    static NIX_INLINE __nixFloat4 Neg(const __nixFloat4& _v) { return _mm_xor_ps(_v, _mm_castsi128_ps(_mm_set1_epi32(0x80000000))); }

    static NIX_INLINE __nixFloat4 Round(const __nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_BIT
        return _mm_round_ps(_v, _MM_FROUND_TO_NEAREST_INT);
#   else
        const __nixFloat4 sgn = _mm_castsi128_ps(_mm_set1_epi32(0x80000000));
        const __nixFloat4 and = _mm_and_ps(sgn, _v);
        const __nixFloat4 or = _mm_or_ps(and, Splat(8388608.0f));
        const __nixFloat4 add = VectorHelper::Add(_v, or );
        const __nixFloat4 sub = VectorHelper::Sub(add, or );
        return sub;
#   endif
    }

    static NIX_INLINE __nixFloat4 Floor(const __nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_BIT
        return _mm_floor_ps(_v);
#   else
        const __nixFloat4 rnd = VectorHelper::Round(_v);
        const __nixFloat4 cmp = _mm_cmplt_ps(_v, rnd);
        const __nixFloat4 and = _mm_and_ps(cmp, GetOne());
        const __nixFloat4 sub = VectorHelper::Sub(rnd, and);
        return sub;
#   endif
    }

    static NIX_INLINE __nixFloat4 Ceil(const __nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_BIT
        return _mm_ceil_ps(_v);
#   else
        const __nixFloat4 rnd = VectorHelper::Round(_v);
        const __nixFloat4 cmp = _mm_cmpgt_ps(_v, rnd);
        const __nixFloat4 and = _mm_and_ps(cmp, GetOne());
        const __nixFloat4 add = VectorHelper::Add(rnd, and);
        return add;
#   endif
    }

    static NIX_INLINE __nixFloat4 Min(const __nixFloat4& _x, const __nixFloat4& _y) { return _mm_min_ps(_x, _y); }
    static NIX_INLINE __nixFloat4 Min(const __nixFloat4& _x, const nixFloat& _y) { return _mm_min_ps(_x, Splat(_y)); }
    static NIX_INLINE __nixFloat4 Max(const __nixFloat4& _x, const __nixFloat4& _y) { return _mm_max_ps(_x, _y); }
    static NIX_INLINE __nixFloat4 Max(const __nixFloat4& _x, const nixFloat& _y) { return _mm_max_ps(_x, Splat(_y)); }

    // Computes and returns _x * _y + _v.
    static NIX_INLINE __nixFloat4 MulAdd(__nixFloat4 const & _x, __nixFloat4 const & _y, __nixFloat4 const & _v)
    {
#   if NIX_ARCH & NIX_ARCH_AVX2_BIT
        return _mm_fmadd_ps(_x, _y, _v);
#   else
        return VectorHelper::Add(VectorHelper::Mul(_x, _y), _v);
#   endif
    }

    static NIX_INLINE __nixFloat4 Dot(__nixFloat4 const & _a, __nixFloat4 const & _b)
    {
#   if NIX_ARCH & NIX_ARCH_AVX2_BIT
        return _mm_dp_ps(_a, _b, 0xff); // 1111 1111 -> all values are computed and the result is saved to the whole register
#	elif NIX_ARCH & NIX_ARCH_SSE3_BIT
        __nixFloat4 rMul = _mm_mul_ps(_a, _b);
        __nixFloat4 rHAdd0 = _mm_hadd_ps(rMul, rMul);
        __nixFloat4 rHAdd1 = _mm_hadd_ps(rHAdd0, rHAdd0);
        return rHAdd1;
#   else
        __nixFloat4 const rMul0 = _mm_mul_ps(_a, _b);
        __nixFloat4 const rAdd0 = _mm_add_ps(rMul0, _mm_shuffle_ps(rMul0, rMul0, _MM_SHUFFLE(2, 3, 0, 1)));
        __nixFloat4 const rAdd1 = _mm_add_ps(rAdd0, _mm_shuffle_ps(rAdd0, rAdd0, _MM_SHUFFLE(0, 1, 2, 3)));
        return rAdd1;
#   endif
    }

    static NIX_INLINE __nixFloat4 Dot3(__nixFloat4 const & _a, __nixFloat4 const & _b)
    {
#   if NIX_ARCH & NIX_ARCH_AVX2_BIT
        return _mm_dp_ps(_a, _b, 0x7f); // 0111 1111 -> the w value of arrays are not computed. The result is saved to the whole register
#	elif NIX_ARCH & NIX_ARCH_SSE3_BIT

#   else

#   endif
    }

    static NIX_INLINE __nixFloat4 Dot33(__nixFloat4 const & _a, __nixFloat4 const & _b)
    {
#   if NIX_ARCH & NIX_ARCH_AVX2_BIT
        return _mm_dp_ps(_a, _b, 0x77); // 0111 0111 -> the w value of arrays are not computed. The result is saved only in the lower 3 bit (result.w=0)
#	elif NIX_ARCH & NIX_ARCH_SSE3_BIT

#   else

#   endif
    }
};


NIX_NAMESPACE_END