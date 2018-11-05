#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Constants.h"
#include "Trigonometry.h"

#ifdef max
#undef max
#endif //

#ifdef min
#undef min
#endif //


NIX_NAMESPACE_BEGIN

NIX_SIMD_ALIGN_16 struct Helper
{
    static NIX_INLINE nixFloat4 Set(const nixFloat& _x, const nixFloat& _y, const nixFloat& _z, const nixFloat& _w) { return _mm_set_ps(_w, _z, _y, _x); }
    static NIX_INLINE nixFloat4 Add(const nixFloat4& _a, const nixFloat4& _b) { return _mm_add_ps(_a, _b); }
    static NIX_INLINE nixFloat4 Sub(const nixFloat4& _a, const nixFloat4& _b) { return _mm_sub_ps(_a, _b); }
    static NIX_INLINE nixFloat4 Mul(const nixFloat4& _a, const nixFloat4& _b) { return _mm_mul_ps(_a, _b); }
    static NIX_INLINE nixFloat4 Div(const nixFloat4& _a, const nixFloat4& _b) { return _mm_div_ps(_a, _b); }

    static NIX_INLINE nixFloat4 Splat(const nixFloat& _v) 
    { 
#   if NIX_ARCH & NIX_ARCH_AVX_FLAG
        return _mm_broadcast_ss(&_v);
#   else
        return _mm_set1_ps(_v);
#   endif
    }

    static NIX_INLINE nixInt4 Splat(const nixS32& _v)
    {
        return _mm_set1_epi32(_v);
    }
    static NIX_INLINE nixInt4 Splat(const nixU32& _v)
    {
        return _mm_set1_epi32(_v);
    }


    static NIX_INLINE nixFloat4 Abs(const nixFloat4& _v) { return _mm_andnot_ps(kSignBit, _v); }
    static NIX_INLINE nixFloat4 Neg(const nixFloat4& _v) { return _mm_xor_ps(_v, kSignBit); }

    static NIX_INLINE nixFloat4 Sqrt(const nixFloat4& _v) { return _mm_sqrt_ps(_v); }
    static NIX_INLINE nixFloat4 ReciprocalSqrt(const nixFloat4& _v) { return _mm_rsqrt_ps(_v); }

    static NIX_INLINE nixFloat4 Round(const nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_round_ps(_v, _MM_FROUND_TO_NEAREST_INT);
#   else
        const nixFloat4 and = _mm_and_ps(kSignBit, _v);
        const nixFloat4 or = _mm_or_ps(and, Helper::Splat(8388608.0f));
        const nixFloat4 add = Helper::Add(_v, or );
        const nixFloat4 sub = Helper::Sub(add, or );
        return sub;
#   endif
    }

    static NIX_INLINE nixFloat4 Floor(const nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_floor_ps(_v);
#   else
        const nixFloat4 rnd = Helper::Round(_v);
        const nixFloat4 cmp = _mm_cmplt_ps(_v, rnd);
        const nixFloat4 and = _mm_and_ps(cmp, kOne);
        const nixFloat4 sub = Helper::Sub(rnd, and);
        return sub;
#   endif
    }

    static NIX_INLINE nixFloat4 Ceil(const nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_ceil_ps(_v);
#   else
        const nixFloat4 rnd = Helper::Round(_v);
        const nixFloat4 cmp = _mm_cmpgt_ps(_v, rnd);
        const nixFloat4 and = _mm_and_ps(cmp, kOne);
        const nixFloat4 add = Helper::Add(rnd, and);
        return add;
#   endif
    }

    static NIX_INLINE nixFloat4 Min(const nixFloat4& _x, const nixFloat4& _y) { return _mm_min_ps(_x, _y); }
    static NIX_INLINE nixFloat4 Min(const nixFloat4& _x, const nixFloat& _y) { return _mm_min_ps(_x, Helper::Splat(_y)); }
    static NIX_INLINE nixFloat4 Max(const nixFloat4& _x, const nixFloat4& _y) { return _mm_max_ps(_x, _y); }
    static NIX_INLINE nixFloat4 Max(const nixFloat4& _x, const nixFloat& _y) { return _mm_max_ps(_x, Helper::Splat(_y)); }

    // Computes and returns _x * _y + _v.
    static NIX_INLINE nixFloat4 MulAdd(const nixFloat4& _x, const nixFloat4& _y, const nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_AVX2_FLAG
        return _mm_fmadd_ps(_x, _y, _v);
#   else
        return Helper::Add(Helper::Mul(_x, _y), _v);
#   endif
    }

    static NIX_INLINE nixFloat4 Dot(const nixFloat4& _a, const nixFloat4& _b)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_dp_ps(_a, _b, 0xff); // 1111 1111 -> all values are computed and the result is saved to the whole register
#    elif NIX_ARCH & NIX_ARCH_SSE3_FLAG
        const nixFloat4 mul = Helper::Mul(_a, _b);
        const nixFloat4 add = _mm_hadd_ps(mul, mul);
        const nixFloat4 res = _mm_hadd_ps(add, add);
        return res;
#   else
        const nixFloat4 mul = Helper::Mul(_a, _b);
        const nixFloat4 add = Helper::Add(mul, Swizzle::YXWZ(mul));
        const nixFloat4 res = Helper::Add(add, Swizzle::WZYX(add));
        return res;
#   endif
    }

    static NIX_INLINE nixFloat4 Dot3(const nixFloat4& _a, const nixFloat4& _b)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_dp_ps(_a, _b, 0x7f); // 0111 1111 -> the w value of arrays are not computed. The result is saved to the whole register
#    elif NIX_ARCH & NIX_ARCH_SSE3_FLAG
        const nixFloat4 aW0 = Helper::Mul(_a, k1110);
        const nixFloat4 bW0 = Helper::Mul(_b, k1110);
        const nixFloat4 mul = Helper::Mul(aW0, bW0);
        const nixFloat4 add = _mm_hadd_ps(mul, mul);
        const nixFloat4 res = _mm_hadd_ps(add, add);
        return res;
#   else
        const nixFloat4 aW0 = Helper::Mul(_a, k1110);
        const nixFloat4 bW0 = Helper::Mul(_b, k1110);
        const nixFloat4 mul = Helper::Mul(aW0, bW0);
        const nixFloat4 add = Helper::Add(mul, Swizzle::YXWZ(mul));
        const nixFloat4 res = Helper::Add(add, Swizzle::WZYX(add));
        return res;
#   endif
    }

    static NIX_INLINE nixFloat4 SquareLength(const nixFloat4& _v)
    {
        return Helper::Dot(_v, _v);
    }

    static NIX_INLINE nixFloat4 SquareLength3(const nixFloat4& _v)
    {
        return Helper::Dot3(_v, _v);
    }

    static NIX_INLINE nixFloat4 Length(const nixFloat4& _v)
    {
        const nixFloat4 sln = Helper::SquareLength(_v);
        const nixFloat4 sqt = Helper::Sqrt(sln);
        return sqt;
    }

    static NIX_INLINE nixFloat4 Length3(const nixFloat4& _v)
    {
        const nixFloat4 sln = Helper::SquareLength3(_v);
        const nixFloat4 sqt = Helper::Sqrt(sln);
        return sqt;
    }

    static NIX_INLINE nixFloat4 SquareDistance(const nixFloat4& _a, const nixFloat4& _b)
    {
        const nixFloat4 sub = Helper::Sub(_a, _b);
        const nixFloat4 sln = Helper::SquareLength(sub);
        return sln;
    }

    static NIX_INLINE nixFloat4 Distance(const nixFloat4& _a, const nixFloat4& _b)
    {
        const nixFloat4 sub = Helper::Sub(_a, _b);
        const nixFloat4 len = Helper::Length(sub);
        return len;
    }

    static NIX_INLINE nixFloat4 Distance3(const nixFloat4& _a, const nixFloat4& _b)
    {
        const nixFloat4 sub = Helper::Sub(_a, _b);
        const nixFloat4 len = Helper::Length3(sub);
        return len;
    }

    static NIX_INLINE nixFloat4 Cross(const nixFloat4& _a, const nixFloat4& _b)
    {
        return Helper::Sub(
            Helper::Mul(Swizzle::YZXW(_a), Swizzle::ZXYW(_b)),
            Helper::Mul(Swizzle::ZXYW(_a), Swizzle::YZXW(_b))
        );
    }

    static NIX_INLINE nixFloat4 Mod(const nixFloat4& _a, const nixFloat4& _b)
    {
        const nixFloat4 div = Helper::Div(_a, _b);
        const nixFloat4 flr = Helper::Floor(div);
        const nixFloat4 mul = Helper::Mul(_b, flr);
        const nixFloat4 sub = Helper::Sub(_a, mul);
        return sub;
    }

    static NIX_INLINE nixFloat4 Clamp(const nixFloat4& _v, const nixFloat4& _min, const nixFloat4& _max)
    {
        const nixFloat4 min = Helper::Min(_v, _max);
        const nixFloat4 max = Helper::Max(min, _min);
        return max;
    }

    static NIX_INLINE nixFloat4 FastSqrt(const nixFloat4& _v)
    {
        return Helper::Mul(Helper::ReciprocalSqrt(_v), _v);
    }

    static NIX_INLINE nixFloat4 Normalize(const nixFloat4& _v)
    {
        const nixFloat4 dot = Helper::Dot(_v, _v);
        const nixFloat4 rsr = Helper::ReciprocalSqrt(dot);
        const nixFloat4 mul = Helper::Mul(_v, rsr);
        return mul;
    }

    static NIX_INLINE nixFloat4 Normalize3(const nixFloat4& _v)
    {
        const nixFloat4 dot = Helper::Dot3(_v, _v);
        const nixFloat4 rsr = Helper::ReciprocalSqrt(dot);
        const nixFloat4 mul = Helper::Mul(_v, rsr);
        return mul;
    }

    static NIX_INLINE nixFloat4 Pow(const nixFloat4& _x, const nixFloat4& _y)
    {
        //pow(x, y) == exp(y*log(x))
        return Trigonometry::Exp(Helper::Mul(_y, Trigonometry::Log(_x)));
    }

    static NIX_INLINE nixFloat4 Lerp(const nixFloat4& _from, const nixFloat4& _to, const nixFloat4& _t)
    {
        const nixFloat4 sub = Helper::Sub(kOne, _t);
        const nixFloat4 mul0 = Helper::Mul(sub, _from);
        const nixFloat4 mul1= Helper::Mul(_t, _to);
        const nixFloat4 add = Helper::Add(mul0, mul1);
        return add;
    }

    static NIX_INLINE nixFloat4 Step(const nixFloat4& _from, const nixFloat4& _to, const nixFloat4& _t)
    {
        const nixFloat4 cmp0 = _mm_cmpngt_ps(_t, kHalf);

        const nixS16 mask = _mm_movemask_ps(cmp0);
        if (mask == 0xffffffff)
        {
            return _from;
        }
        else
        {
            return _to;
        }
    }

    static NIX_INLINE nixFloat4 HermiteCubicSpline(const nixFloat4& _p0, const nixFloat4& _m0, const nixFloat4& _p1, const nixFloat4& _m1, const nixFloat4& _t)
    {
        static const nixFloat4 one = Splat(1.0f);
        static const nixFloat4 two = Splat(2.0f);
        static const nixFloat4 minustwo = Splat(-2.0f);
        static const nixFloat4 three = Splat(3.0f);

        const nixFloat4 p0c = Helper::Add(Helper::Sub(Helper::Mul(two, Pow(_t, three)), Helper::Mul(three, Pow(_t, two))), one);
        const nixFloat4 m0c = Helper::Add(Helper::Sub(Pow(_t, three), Helper::Mul(two, Pow(_t, two))), _t);
        const nixFloat4 p1c = Helper::Add(Helper::Mul(minustwo, Pow(_t, three)), Helper::Mul(three, Pow(_t, two)));
        const nixFloat4 m1c = Helper::Sub(Pow(_t, three), Pow(_t, two));

        const nixFloat4 p0 = Helper::Mul(p0c, _p0);
        const nixFloat4 m0 = Helper::Mul(m0c, _m0);
        const nixFloat4 p1 = Helper::Mul(p1c, _p1);
        const nixFloat4 m1 = Helper::Mul(m1c, _m1);

        const nixFloat4 add0 = Helper::Add(p0, m0);
        const nixFloat4 add1 = Helper::Add(p1, m1);

        const nixFloat4 add = Helper::Add(add0, add1);

        return add;
    }


    // is a bit slow
    static NIX_INLINE nixFloat4 InverseLerp(const nixFloat4& _v, const nixFloat4& _min, const nixFloat4& _max)
    {
        const nixFloat4 equal = _mm_cmpeq_ps(_min, _max);
        const nixS16 mask = _mm_movemask_ps(equal);
        if (mask == 0xffffffff)
        {
            return kZero;
        }
        else
        {
            const nixFloat4 sub0 = Helper::Sub(_v, _min);
            const nixFloat4 sub1 = Helper::Sub(_max, _min);
            const nixFloat4 div = Helper::Div(sub0, sub1);
            return div;
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // Faster helper accessor
    //////////////////////////////////////////////////////////////////////////

    static NIX_INLINE nixFloat4 InsertAt(const nixFloat4& _v, nixFloat _x, nixU32 _i)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        //return _mm_insert_ps(_v, _mm_set_ss(_x), _i << 4);
        return _mm_insert_ps(_v, _mm_set_ss(_x), _i);
#   else
        NIX_SIMD_ALIGN_16 nixU32 mask[4] = { 0xffffffff,0xffffffff,0xffffffff,0xffffffff };
        nixFloat4 tmp, vec_masked, p_masked;
        //mask[_i >> 4] = 0x0;
        mask[_i] = 0x0;
        vec_masked = _mm_and_ps(*(nixFloat4*)mask, _v);
        p_masked = _mm_andnot_ps(*(nixFloat4*)mask, _mm_set_ss(_x));
        tmp = _mm_or_ps(vec_masked, p_masked);
        return tmp;
#   endif
    }

    static NIX_INLINE nixFloat ExtractX(const nixFloat4& _v)
    {
        return _mm_cvtss_f32(_v);
    }

    static NIX_INLINE nixFloat ExtractY(const nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        nixFloat r;
        _MM_EXTRACT_FLOAT(r, _v, 1);
        return r;
#   else
        return _mm_cvtss_f32(Swizzle::YYYY(_v));
#   endif
    }

    static NIX_INLINE nixFloat ExtractZ(const nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        nixFloat r;
        _MM_EXTRACT_FLOAT(r, _v, 2);
        return r;
#   else
        return _mm_cvtss_f32(Swizzle::ZZZZ(_v));
#   endif
    }

    static NIX_INLINE nixFloat ExtractW(const nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        nixFloat r;
        _MM_EXTRACT_FLOAT(r, _v, 3);
        return r;
#   else
        return _mm_cvtss_f32(Swizzle::WWWW(_v));
#   endif
    }

    static NIX_INLINE nixFloat4 AX_BX_AY_BY(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_unpacklo_ps(_a, _b); }
    static NIX_INLINE nixFloat4 AX_AY_BX_BY(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_movelh_ps(_a, _b); }
    static NIX_INLINE nixFloat4 AZ_BZ_AW_BW(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_unpackhi_ps(_a, _b); }
    static NIX_INLINE nixFloat4 BZ_BW_AZ_AW(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_movehl_ps(_a, _b); }
    static NIX_INLINE nixFloat4 BX_AY_AZ_AW(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_move_ss(_a, _b); }
    static NIX_INLINE nixFloat4 AX_AX_AZ_AZ(const nixFloat4& _a)                          
    {
#   if NIX_ARCH & NIX_ARCH_SSE3_FLAG
        return _mm_moveldup_ps(_a);
#   else
        return _mm_shuffle_ps(_a, _a, _MM_SHUFFLE(2, 2, 0, 0));
#   endif   
    }
    static NIX_INLINE nixFloat4 AY_AX_BY_BX(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(0, 1, 0, 1)); }
    static NIX_INLINE nixFloat4 AW_AZ_BW_BZ(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(2, 3, 2, 3)); }
    static NIX_INLINE nixFloat4 AW_AX_BY_BZ(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(2, 1, 0, 3)); }
    static NIX_INLINE nixFloat4 AX_AY_BX_BW(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 0, 1, 0)); }
    static NIX_INLINE nixFloat4 AZ_AW_BY_BW(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 1, 3, 2)); }
    static NIX_INLINE nixFloat4 AX_AY_BZ_BW(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 2, 1, 0)); }
    static NIX_INLINE nixFloat4 AX_AZ_BX_BZ(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(2, 0, 2, 0)); }
    static NIX_INLINE nixFloat4 AY_AW_BY_BW(const nixFloat4& _a, const nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 1, 3, 1)); }
};


NIX_NAMESPACE_END