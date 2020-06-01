#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "Constants.h"
#include "Trigonometry.h"

#ifdef max
#undef max
#endif //

#ifdef min
#undef min
#endif //


NIX_NAMESPACE_BEGIN

NIX_ALIGN_16 struct Helper
{
    static NIX_INLINE float128 Set(const float& _x, const float& _y, const float& _z, const float& _w) { return _mm_set_ps(_w, _z, _y, _x); }
    static NIX_INLINE float128 Add(const float128& _a, const float128& _b) { return _mm_add_ps(_a, _b); }
    static NIX_INLINE float128 Sub(const float128& _a, const float128& _b) { return _mm_sub_ps(_a, _b); }
    static NIX_INLINE float128 Mul(const float128& _a, const float128& _b) { return _mm_mul_ps(_a, _b); }
    static NIX_INLINE float128 Div(const float128& _a, const float128& _b) { return _mm_div_ps(_a, _b); }

    static NIX_INLINE float128 Splat(const float& _v) 
    { 
#   if NIX_ARCH & NIX_ARCH_AVX_FLAG
        return _mm_broadcast_ss(&_v);
#   else
        return _mm_set1_ps(_v);
#   endif
    }

    static NIX_INLINE int128 Splat(const int32& _v)
    {
        return _mm_set1_epi32(_v);
    }
    static NIX_INLINE int128 Splat(const uint32& _v)
    {
        return _mm_set1_epi32(_v);
    }


    static NIX_INLINE float128 Abs(const float128& _v) { return _mm_andnot_ps(kSignBit, _v); }
    static NIX_INLINE float128 Neg(const float128& _v) { return _mm_xor_ps(_v, kSignBit); }

    static NIX_INLINE float128 Sqrt(const float128& _v) { return _mm_sqrt_ps(_v); }
    static NIX_INLINE float128 ReciprocalSqrt(const float128& _v) { return _mm_rsqrt_ps(_v); }

    static NIX_INLINE float128 Round(const float128& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_round_ps(_v, _MM_FROUND_TO_NEAREST_INT);
#   else
        const float128 and = _mm_and_ps(kSignBit, _v);
        const float128 or = _mm_or_ps(and, Helper::Splat(8388608.0f));
        const float128 add = Helper::Add(_v, or );
        const float128 sub = Helper::Sub(add, or );
        return sub;
#   endif
    }

    static NIX_INLINE float128 Floor(const float128& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_floor_ps(_v);
#   else
        const float128 rnd = Helper::Round(_v);
        const float128 cmp = _mm_cmplt_ps(_v, rnd);
        const float128 and = _mm_and_ps(cmp, kOne);
        const float128 sub = Helper::Sub(rnd, and);
        return sub;
#   endif
    }

    static NIX_INLINE float128 Ceil(const float128& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_ceil_ps(_v);
#   else
        const float128 rnd = Helper::Round(_v);
        const float128 cmp = _mm_cmpgt_ps(_v, rnd);
        const float128 and = _mm_and_ps(cmp, kOne);
        const float128 add = Helper::Add(rnd, and);
        return add;
#   endif
    }

    static NIX_INLINE float128 Min(const float128& _x, const float128& _y) { return _mm_min_ps(_x, _y); }
    static NIX_INLINE float128 Min(const float128& _x, const float& _y) { return _mm_min_ps(_x, Helper::Splat(_y)); }
    static NIX_INLINE float128 Max(const float128& _x, const float128& _y) { return _mm_max_ps(_x, _y); }
    static NIX_INLINE float128 Max(const float128& _x, const float& _y) { return _mm_max_ps(_x, Helper::Splat(_y)); }

    // Computes and returns _x * _y + _v.
    static NIX_INLINE float128 MulAdd(const float128& _x, const float128& _y, const float128& _v)
    {
#   if NIX_ARCH & NIX_ARCH_AVX2_FLAG
        return _mm_fmadd_ps(_x, _y, _v);
#   else
        return Helper::Add(Helper::Mul(_x, _y), _v);
#   endif
    }

    static NIX_INLINE float128 Dot(const float128& _a, const float128& _b)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_dp_ps(_a, _b, 0xff); // 1111 1111 -> all values are computed and the result is saved to the whole register
#    elif NIX_ARCH & NIX_ARCH_SSE3_FLAG
        const float128 mul = Helper::Mul(_a, _b);
        const float128 add = _mm_hadd_ps(mul, mul);
        const float128 res = _mm_hadd_ps(add, add);
        return res;
#   else
        const float128 mul = Helper::Mul(_a, _b);
        const float128 add = Helper::Add(mul, Swizzle::YXWZ(mul));
        const float128 res = Helper::Add(add, Swizzle::WZYX(add));
        return res;
#   endif
    }

    static NIX_INLINE float128 Dot3(const float128& _a, const float128& _b)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_dp_ps(_a, _b, 0x7f); // 0111 1111 -> the w value of arrays are not computed. The result is saved to the whole register
#    elif NIX_ARCH & NIX_ARCH_SSE3_FLAG
        const float128 aW0 = Helper::Mul(_a, k1110);
        const float128 bW0 = Helper::Mul(_b, k1110);
        const float128 mul = Helper::Mul(aW0, bW0);
        const float128 add = _mm_hadd_ps(mul, mul);
        const float128 res = _mm_hadd_ps(add, add);
        return res;
#   else
        const float128 aW0 = Helper::Mul(_a, k1110);
        const float128 bW0 = Helper::Mul(_b, k1110);
        const float128 mul = Helper::Mul(aW0, bW0);
        const float128 add = Helper::Add(mul, Swizzle::YXWZ(mul));
        const float128 res = Helper::Add(add, Swizzle::WZYX(add));
        return res;
#   endif
    }

    static NIX_INLINE float128 HorizontaSum(float128 _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE3_FLAG
        return _mm_hadd_ps(_v, _v);
#   else
        float128 t;
        t = _mm_movehl_ps(t, _v);
        _v = _mm_add_ps(_v, t);
        t = _mm_shuffle_ps(_v, _v, 0x55);
        _v = _mm_add_ps(_v, t);
        return _v;
#   endif
    }

    static NIX_INLINE float128 SquareLength(const float128& _v)
    {
        return Helper::Dot(_v, _v);
    }

    static NIX_INLINE float128 SquareLength3(const float128& _v)
    {
        return Helper::Dot3(_v, _v);
    }

    static NIX_INLINE float128 Length(const float128& _v)
    {
        const float128 sln = Helper::SquareLength(_v);
        const float128 sqt = Helper::Sqrt(sln);
        return sqt;
    }

    static NIX_INLINE float128 Length3(const float128& _v)
    {
        const float128 sln = Helper::SquareLength3(_v);
        const float128 sqt = Helper::Sqrt(sln);
        return sqt;
    }

    static NIX_INLINE float128 SquareDistance(const float128& _a, const float128& _b)
    {
        const float128 sub = Helper::Sub(_a, _b);
        const float128 sln = Helper::SquareLength(sub);
        return sln;
    }

    static NIX_INLINE float128 Distance(const float128& _a, const float128& _b)
    {
        const float128 sub = Helper::Sub(_a, _b);
        const float128 len = Helper::Length(sub);
        return len;
    }

    static NIX_INLINE float128 Distance3(const float128& _a, const float128& _b)
    {
        const float128 sub = Helper::Sub(_a, _b);
        const float128 len = Helper::Length3(sub);
        return len;
    }

    static NIX_INLINE float128 Cross(const float128& _a, const float128& _b)
    {
        return Helper::Sub(
            Helper::Mul(Swizzle::YZXW(_a), Swizzle::ZXYW(_b)),
            Helper::Mul(Swizzle::ZXYW(_a), Swizzle::YZXW(_b))
        );
    }

    static NIX_INLINE float128 Mod(const float128& _a, const float128& _b)
    {
        const float128 div = Helper::Div(_a, _b);
        const float128 flr = Helper::Floor(div);
        const float128 mul = Helper::Mul(_b, flr);
        const float128 sub = Helper::Sub(_a, mul);
        return sub;
    }

    static NIX_INLINE float128 Clamp(const float128& _v, const float128& _min, const float128& _max)
    {
        const float128 min = Helper::Min(_v, _max);
        const float128 max = Helper::Max(min, _min);
        return max;
    }

    static NIX_INLINE float128 FastSqrt(const float128& _v)
    {
        return Helper::Mul(Helper::ReciprocalSqrt(_v), _v);
    }

    static NIX_INLINE float128 Normalize(const float128& _v)
    {
        const float128 dot = Helper::Dot(_v, _v);
        const float128 rsr = Helper::ReciprocalSqrt(dot);
        const float128 mul = Helper::Mul(_v, rsr);
        return mul;
    }

    static NIX_INLINE float128 Normalize3(const float128& _v)
    {
        const float128 dot = Helper::Dot3(_v, _v);
        const float128 rsr = Helper::ReciprocalSqrt(dot);
        const float128 mul = Helper::Mul(_v, rsr);
        return mul;
    }

    static NIX_INLINE float128 Pow(const float128& _x, const float128& _y)
    {
        //pow(x, y) == exp(y*log(x))
        return Trigonometry::Exp(Helper::Mul(_y, Trigonometry::Log(_x)));
    }

    static NIX_INLINE float128 Lerp(const float128& _from, const float128& _to, const float128& _t)
    {
        const float128 sub = Helper::Sub(kOne, _t);
        const float128 mul0 = Helper::Mul(sub, _from);
        const float128 mul1= Helper::Mul(_t, _to);
        const float128 add = Helper::Add(mul0, mul1);
        return add;
    }

    static NIX_INLINE float128 Step(const float128& _from, const float128& _to, const float128& _t)
    {
        const float128 cmp0 = _mm_cmpngt_ps(_t, kHalf);

        const int16 mask = _mm_movemask_ps(cmp0);
        if (mask == 0xffffffff)
        {
            return _from;
        }
        else
        {
            return _to;
        }
    }

    static NIX_INLINE float128 HermiteCubicSpline(const float128& _p0, const float128& _m0, const float128& _p1, const float128& _m1, const float128& _t)
    {
        static const float128 one = Splat(1.0f);
        static const float128 two = Splat(2.0f);
        static const float128 minustwo = Splat(-2.0f);
        static const float128 three = Splat(3.0f);

        const float128 p0c = Helper::Add(Helper::Sub(Helper::Mul(two, Pow(_t, three)), Helper::Mul(three, Pow(_t, two))), one);
        const float128 m0c = Helper::Add(Helper::Sub(Pow(_t, three), Helper::Mul(two, Pow(_t, two))), _t);
        const float128 p1c = Helper::Add(Helper::Mul(minustwo, Pow(_t, three)), Helper::Mul(three, Pow(_t, two)));
        const float128 m1c = Helper::Sub(Pow(_t, three), Pow(_t, two));

        const float128 p0 = Helper::Mul(p0c, _p0);
        const float128 m0 = Helper::Mul(m0c, _m0);
        const float128 p1 = Helper::Mul(p1c, _p1);
        const float128 m1 = Helper::Mul(m1c, _m1);

        const float128 add0 = Helper::Add(p0, m0);
        const float128 add1 = Helper::Add(p1, m1);

        const float128 add = Helper::Add(add0, add1);

        return add;
    }


    // is a bit slow
    static NIX_INLINE float128 InverseLerp(const float128& _v, const float128& _min, const float128& _max)
    {
        const float128 equal = _mm_cmpeq_ps(_min, _max);
        const int16 mask = _mm_movemask_ps(equal);
        if (mask == 0xffffffff)
        {
            return kZero;
        }
        else
        {
            const float128 sub0 = Helper::Sub(_v, _min);
            const float128 sub1 = Helper::Sub(_max, _min);
            const float128 div = Helper::Div(sub0, sub1);
            return div;
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // Faster helper accessor
    //////////////////////////////////////////////////////////////////////////

    static NIX_INLINE float128 InsertAt(const float128& _v, float _x, uint32 _i)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        //return _mm_insert_ps(_v, _mm_set_ss(_x), _i << 4);
        return _mm_insert_ps(_v, _mm_set_ss(_x), _i);
#   else
        NIX_ALIGN_16 uint32 mask[4] = { 0xffffffff,0xffffffff,0xffffffff,0xffffffff };
        float128 tmp, vec_masked, p_masked;
        //mask[_i >> 4] = 0x0;
        mask[_i] = 0x0;
        vec_masked = _mm_and_ps(*(float128*)mask, _v);
        p_masked = _mm_andnot_ps(*(float128*)mask, _mm_set_ss(_x));
        tmp = _mm_or_ps(vec_masked, p_masked);
        return tmp;
#   endif
    }

    static NIX_INLINE float ExtractX(const float128& _v)
    {
        return _mm_cvtss_f32(_v);
    }

    static NIX_INLINE float ExtractY(const float128& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        float r;
        _MM_EXTRACT_FLOAT(r, _v, 1);
        return r;
#   else
        return _mm_cvtss_f32(Swizzle::YYYY(_v));
#   endif
    }

    static NIX_INLINE float ExtractZ(const float128& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        float r;
        _MM_EXTRACT_FLOAT(r, _v, 2);
        return r;
#   else
        return _mm_cvtss_f32(Swizzle::ZZZZ(_v));
#   endif
    }

    static NIX_INLINE float ExtractW(const float128& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        float r;
        _MM_EXTRACT_FLOAT(r, _v, 3);
        return r;
#   else
        return _mm_cvtss_f32(Swizzle::WWWW(_v));
#   endif
    }

    static NIX_INLINE float128 AX_BX_AY_BY(const float128& _a, const float128& _b)    { return _mm_unpacklo_ps(_a, _b); }
    static NIX_INLINE float128 AX_AY_BX_BY(const float128& _a, const float128& _b)    { return _mm_movelh_ps(_a, _b); }
    static NIX_INLINE float128 AZ_BZ_AW_BW(const float128& _a, const float128& _b)    { return _mm_unpackhi_ps(_a, _b); }
    static NIX_INLINE float128 BZ_BW_AZ_AW(const float128& _a, const float128& _b)    { return _mm_movehl_ps(_a, _b); }
    static NIX_INLINE float128 BX_AY_AZ_AW(const float128& _a, const float128& _b)    { return _mm_move_ss(_a, _b); }
    static NIX_INLINE float128 AX_AX_AZ_AZ(const float128& _a)                          
    {
#   if NIX_ARCH & NIX_ARCH_SSE3_FLAG
        return _mm_moveldup_ps(_a);
#   else
        return _mm_shuffle_ps(_a, _a, _MM_SHUFFLE(2, 2, 0, 0));
#   endif   
    }
    static NIX_INLINE float128 AY_AX_BY_BX(const float128& _a, const float128& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(0, 1, 0, 1)); }
    static NIX_INLINE float128 AW_AZ_BW_BZ(const float128& _a, const float128& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(2, 3, 2, 3)); }
    static NIX_INLINE float128 AW_AX_BY_BZ(const float128& _a, const float128& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(2, 1, 0, 3)); }
    static NIX_INLINE float128 AX_AY_BX_BW(const float128& _a, const float128& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 0, 1, 0)); }
    static NIX_INLINE float128 AZ_AW_BY_BW(const float128& _a, const float128& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 1, 3, 2)); }
    static NIX_INLINE float128 AX_AY_BZ_BW(const float128& _a, const float128& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 2, 1, 0)); }
    static NIX_INLINE float128 AX_AZ_BX_BZ(const float128& _a, const float128& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(2, 0, 2, 0)); }
    static NIX_INLINE float128 AY_AW_BY_BW(const float128& _a, const float128& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 1, 3, 1)); }
};


NIX_NAMESPACE_END