#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"


NIX_NAMESPACE_BEGIN


NIX_SIMD_ALIGN class VectorHelper
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
    static NIX_INLINE __nixFloat4 MulAdd(const __nixFloat4& _x, const __nixFloat4& _y, const __nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_AVX2_BIT
        return _mm_fmadd_ps(_x, _y, _v);
#   else
        return VectorHelper::Add(VectorHelper::Mul(_x, _y), _v);
#   endif
    }

    static NIX_INLINE __nixFloat4 Dot(const __nixFloat4& _a, const __nixFloat4& _b)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41
        return _mm_dp_ps(_a, _b, 0xff); // 1111 1111 -> all values are computed and the result is saved to the whole register
#	elif NIX_ARCH & NIX_ARCH_SSE3_BIT
        const __nixFloat4 mul = _mm_mul_ps(_a, _b);
        const __nixFloat4 add = _mm_hadd_ps(mul, mul);
        const __nixFloat4 res = _mm_hadd_ps(add, add);
        return res;
#   else
        const __nixFloat4 const mul = _mm_mul_ps(_a, _b);
        const __nixFloat4 const add = _mm_add_ps(mul, _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1)));
        const __nixFloat4 const res = _mm_add_ps(add, _mm_shuffle_ps(add, add, _MM_SHUFFLE(0, 1, 2, 3)));
        return res;
#   endif
    }

    static NIX_INLINE __nixFloat4 Dot3(const __nixFloat4& _a, const __nixFloat4& _b)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41
        return _mm_dp_ps(_a, _b, 0x7f); // 0111 1111 -> the w value of arrays are not computed. The result is saved to the whole register
#	elif NIX_ARCH & NIX_ARCH_SSE3_BIT
        const __nixFloat4 mul = _mm_mul_ps(_a, _b);
        const __nixFloat4 res = _mm_hadd_ps(mul, mul);
        return res;
#   else
        static const __nixFloat4 mask = _mm_load_ps((const float*)maskRaw);
        const __nixFloat4 mul = _mm_mul_ps(lhs, rhs);
        const __nixFloat4 and = _mm_and_ps(mul, mask);
        const __nixFloat4 res = _mm_add_ps(and, _mm_movehl_ps(and, and));
        return res;
#   endif
    }

    static NIX_INLINE __nixFloat4 Dot33(const __nixFloat4& _a, const __nixFloat4& _b)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41
        return _mm_dp_ps(_a, _b, 0x77); // 0111 0111 -> the w value of arrays are not computed. The result is saved only in the lower 3 bit (result.w=0)
#	elif NIX_ARCH & NIX_ARCH_SSE3_BIT

#   else

#   endif
    }

private:
    constexpr static NIX_SIMD_ALIGN const nixU32 maskRaw[] = { 0xffffffff, 0xffffffff, 0xffffffff, 0 };
};


NIX_NAMESPACE_END