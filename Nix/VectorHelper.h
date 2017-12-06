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

    static NIX_INLINE __nixFloat4 Sqrt(const __nixFloat4& _v) { return _mm_sqrt_ps(_v); }
    static NIX_INLINE __nixFloat4 ReciprocalSqrt(const __nixFloat4& _v) { return _mm_rsqrt_ps(_v); }

    static NIX_INLINE __nixFloat4 Round(const __nixFloat4& _v)
    {
#   if defined(NIX_ARCH_SSE41)
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
#   if defined(NIX_ARCH_SSE41)
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
#   if defined(NIX_ARCH_SSE41)
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
#   if defined(NIX_ARCH_AVX2)
        return _mm_fmadd_ps(_x, _y, _v);
#   else
        return VectorHelper::Add(VectorHelper::Mul(_x, _y), _v);
#   endif
    }

    static NIX_INLINE __nixFloat4 Dot(const __nixFloat4& _a, const __nixFloat4& _b)
    {
#   if defined(NIX_ARCH_SSE41)
        return _mm_dp_ps(_a, _b, 0xff); // 1111 1111 -> all values are computed and the result is saved to the whole register
#	elif defined(NIX_ARCH_SSE3)
        const __nixFloat4 mul = VectorHelper::Mul(_a, _b);
        const __nixFloat4 add = _mm_hadd_ps(mul, mul);
        const __nixFloat4 res = _mm_hadd_ps(add, add);
        return res;
#   else
        const __nixFloat4 mul = VectorHelper::Mul(_a, _b);
        const __nixFloat4 add = VectorHelper::Add(mul, _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1)));
        const __nixFloat4 res = VectorHelper::Add(add, _mm_shuffle_ps(add, add, _MM_SHUFFLE(0, 1, 2, 3)));
        return res;
#   endif
    }

    static NIX_INLINE __nixFloat4 Dot3(const __nixFloat4& _a, const __nixFloat4& _b)
    {
#   if defined(NIX_ARCH_SSE41)
        return _mm_dp_ps(_a, _b, 0x7f); // 0111 1111 -> the w value of arrays are not computed. The result is saved to the whole register
#	elif defined(NIX_ARCH_SSE3)
        const __nixFloat4 aW0 = VectorHelper::Mul(_a, m_kZeroingW);
        const __nixFloat4 bW0 = VectorHelper::Mul(_b, m_kZeroingW);
        const __nixFloat4 mul = VectorHelper::Mul(aW0, bW0);
        const __nixFloat4 add = _mm_hadd_ps(mul, mul);
        const __nixFloat4 res = _mm_hadd_ps(add, add);
        return res;
#   else
        const __nixFloat4 aW0 = VectorHelper::Mul(_a, m_kZeroingW);
        const __nixFloat4 bW0 = VectorHelper::Mul(_b, m_kZeroingW);
        const __nixFloat4 mul = VectorHelper::Mul(aW0, bW0);
        const __nixFloat4 add = VectorHelper::Add(mul, _mm_shuffle_ps(mul, mul, _MM_SHUFFLE(2, 3, 0, 1)));
        const __nixFloat4 res = VectorHelper::Add(add, _mm_shuffle_ps(add, add, _MM_SHUFFLE(0, 1, 2, 3)));
        return res;
#   endif
    }

    static NIX_INLINE __nixFloat4 SquareLength(const __nixFloat4& _v)
    {
        return VectorHelper::Dot(_v, _v);
    }

    static NIX_INLINE __nixFloat4 SquareLength3(const __nixFloat4& _v)
    {
        return VectorHelper::Dot3(_v, _v);
    }

    static NIX_INLINE __nixFloat4 Length(const __nixFloat4& _v)
    {
        const __nixFloat4 sln = VectorHelper::SquareLength(_v);
        const __nixFloat4 sqt = VectorHelper::Sqrt(sln);
        return sqt;
    }

    static NIX_INLINE __nixFloat4 Length3(const __nixFloat4& _v)
    {
        const __nixFloat4 sln = VectorHelper::SquareLength3(_v);
        const __nixFloat4 sqt = VectorHelper::Sqrt(sln);
        return sqt;
    }

    static NIX_INLINE __nixFloat4 SquareDistance(const __nixFloat4& _a, const __nixFloat4& _b)
    {
        const __nixFloat4 sub = VectorHelper::Sub(_a, _b);
        const __nixFloat4 sln = VectorHelper::SquareLength(sub);
        return sln;
    }

    static NIX_INLINE __nixFloat4 Distance(const __nixFloat4& _a, const __nixFloat4& _b)
    {
        const __nixFloat4 sub = VectorHelper::Sub(_a, _b);
        const __nixFloat4 len = VectorHelper::Length(sub);
        return len;
    }

    static NIX_INLINE __nixFloat4 Distance3(const __nixFloat4& _a, const __nixFloat4& _b)
    {
        const __nixFloat4 sub = VectorHelper::Sub(_a, _b);
        const __nixFloat4 len = VectorHelper::Length3(sub);
        return len;
    }

    static NIX_INLINE __nixFloat4 Cross(const __nixFloat4& _a, const __nixFloat4& _b)
    {
        const __nixFloat4 swp0 = _mm_shuffle_ps(_a, _a, _MM_SHUFFLE(3, 1, 0, 2));
        const __nixFloat4 swp1 = _mm_shuffle_ps(_b, _b, _MM_SHUFFLE(3, 1, 0, 2));
        const __nixFloat4 mul0 = VectorHelper::Mul(_b, swp0);
        const __nixFloat4 mul1 = VectorHelper::Mul(_a, swp1);
        const __nixFloat4 sub = VectorHelper::Sub(mul0, mul1);
        const __nixFloat4 swp3 = _mm_shuffle_ps(sub, sub, _MM_SHUFFLE(3, 1, 0, 2));
        return swp3;
    }

    static NIX_INLINE __nixFloat4 Mod(const __nixFloat4& _a, const __nixFloat4& _b)
    {
        const __nixFloat4 div = VectorHelper::Div(_a, _b);
        const __nixFloat4 flr = VectorHelper::Floor(div);
        const __nixFloat4 mul = VectorHelper::Mul(_b, flr);
        const __nixFloat4 sub = VectorHelper::Sub(_a, mul);
        return sub;
    }

    static NIX_INLINE __nixFloat4 Clamp(const __nixFloat4& _v, const __nixFloat4& _min, const __nixFloat4& _max)
    {
        const __nixFloat4 min = VectorHelper::Min(_v, _max);
        const __nixFloat4 max = VectorHelper::Max(_min, _min);
        return max;
    }

    static NIX_INLINE __nixFloat4 FastSqrt(const __nixFloat4& _v)
    {
        return VectorHelper::Mul(VectorHelper::ReciprocalSqrt(_v), _v);
    }

    static NIX_INLINE __nixFloat4 Normalize(const __nixFloat4& _v)
    {
        const __nixFloat4 dot = VectorHelper::Dot(_v, _v);
        const __nixFloat4 rsr = VectorHelper::ReciprocalSqrt(dot);
        const __nixFloat4 mul = VectorHelper::Mul(_v, rsr);
        return mul;
    }

    static NIX_INLINE __nixFloat4 Normalize3(const __nixFloat4& _v)
    {
        const __nixFloat4 dot = VectorHelper::Dot3(_v, _v);
        const __nixFloat4 rsr = VectorHelper::ReciprocalSqrt(dot);
        const __nixFloat4 mul = VectorHelper::Mul(_v, rsr);
        return mul;
    }


private:
    constexpr static NIX_SIMD_ALIGN const __nixFloat4 m_kZeroingW = { 1.0f, 1.0f, 1.0f, 0.0f };
    //constexpr static NIX_SIMD_ALIGN const nixU32 maskRaw[] = { 0xffffffff, 0xffffffff, 0xffffffff, 0 };
};


NIX_NAMESPACE_END