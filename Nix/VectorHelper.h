#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"

#define USE_SSE2
#include "sse_mathfun.h"


#ifdef max
#undef max
#endif //

#ifdef min
#undef min
#endif //


NIX_NAMESPACE_BEGIN


#define SWIZZLE(V, X, Y, Z, W) __nixFloat4(_mm_shuffle_ps(V, V, _MM_SHUFFLE(W, Z, Y, X)))

NIX_SIMD_ALIGN_16 class VectorHelper
{
public:
    static NIX_INLINE __nixFloat4 GetSignMask() { return _mm_castsi128_ps(_mm_set1_epi32(0x80000000)); }
    static NIX_INLINE __nixFloat4 GetSignMaskNeg() { return _mm_castsi128_ps(_mm_set1_epi32(~0x80000000)); }

    static NIX_INLINE __nixInt4 GetSignMaskI() { return _mm_set1_epi32(0x80000000); }
    static NIX_INLINE __nixInt4 GetSignMaskNegI() { return _mm_set1_epi32(~0x80000000); }

    static NIX_INLINE __nixFloat4 GetNotAll() { return _mm_castsi128_ps(_mm_set1_epi32(~0x00000000)); }

    static NIX_INLINE __nixInt4 GetNotAllI() { return _mm_set1_epi32(~0x00000000); }


    static NIX_INLINE __nixFloat4 GetMaskSignZeroSignZero() { return _mm_castsi128_ps(_mm_set_epi32(0x80000000, 0x00000000, 0x80000000, 0x00000000)); }
    static NIX_INLINE __nixFloat4 GetMaskZeroSignZeroSign() { return _mm_castsi128_ps(_mm_set_epi32(0x00000000, 0x80000000, 0x00000000, 0x80000000)); }

    static NIX_INLINE __nixFloat4 GetTanCP0() { return _mm_set1_ps(9.38540185543E-3f); }
    static NIX_INLINE __nixFloat4 GetTanCP1() { return _mm_set1_ps(3.11992232697E-3f); }
    static NIX_INLINE __nixFloat4 GetTanCP2() { return _mm_set1_ps(2.44301354525E-2f); }
    static NIX_INLINE __nixFloat4 GetTanCP3() { return _mm_set1_ps(5.34112807005E-2f); }
    static NIX_INLINE __nixFloat4 GetTanCP4() { return _mm_set1_ps(1.33387994085E-1f); }
    static NIX_INLINE __nixFloat4 GetTanCP5() { return _mm_set1_ps(3.33331568548E-1f); }

    static NIX_INLINE __nixFloat4 GetNegDP1() { return _mm_set1_ps(0.78515625f); }
    static NIX_INLINE __nixFloat4 GetNegDP2() { return _mm_set1_ps(2.4187564849853515625e-4f); }
    static NIX_INLINE __nixFloat4 GetNegDP3() { return _mm_set1_ps(3.77489497744594108e-8f); }


    static NIX_INLINE __nixFloat4 GetOPI() { return _mm_set1_ps(1.27323954473516f); }
    static NIX_INLINE __nixFloat4 GetPIF() { return _mm_set1_ps(3.141592653589793238f); }
    static NIX_INLINE __nixFloat4 GetPIH() { return _mm_set1_ps(1.5707963267948966192f); }
    static NIX_INLINE __nixFloat4 GetPIQ() { return _mm_set1_ps(0.7853981633974483096f); }

    static NIX_INLINE __nixFloat4 GetTanHI() { return _mm_set1_ps(2.414213562373095f); }
    static NIX_INLINE __nixFloat4 GetTanLO() { return _mm_set1_ps(0.4142135623730950f); }
    static NIX_INLINE __nixFloat4 GetTanP0() { return _mm_set1_ps(8.05374449538e-2f); }
    static NIX_INLINE __nixFloat4 GetTanP1() { return _mm_set1_ps(1.38776856032E-1f); }
    static NIX_INLINE __nixFloat4 GetTanP2() { return _mm_set1_ps(1.99777106478E-1f); }
    static NIX_INLINE __nixFloat4 GetTanP3() { return _mm_set1_ps(3.33329491539E-1f); }



    static NIX_INLINE __nixFloat4 GetZero() { return _mm_setzero_ps(); }
    static NIX_INLINE __nixFloat4 GetOne() { return _mm_set1_ps(1.0f); }
    static NIX_INLINE __nixFloat4 GetMinusOne() { return _mm_set1_ps(-1.0f); }
    static NIX_INLINE __nixFloat4 GetHalf() { return _mm_set1_ps(0.5f); }
    static NIX_INLINE __nixFloat4 Get255() { return _mm_set1_ps(255.0f); }
    static NIX_INLINE __nixFloat4 GetMinChar() { return _mm_set1_ps(-128.0f); }
    static NIX_INLINE __nixFloat4 GetMaxChar() { return _mm_set1_ps(127.0f); }
    static NIX_INLINE __nixFloat4 GetMinShort() { return _mm_set1_ps(-32768.0f); }
    static NIX_INLINE __nixFloat4 GetMaxShort() { return _mm_set1_ps(32767.0f); }
    static NIX_INLINE __nixFloat4 Get255Over2() { return _mm_set1_ps(127.5f); }

    static NIX_INLINE __nixFloat4 Get0001() { return _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f); }
    static NIX_INLINE __nixFloat4 Get1110() { return _mm_set_ps(0.0f, 1.0f, 1.0f, 1.0f); }
    static NIX_INLINE __nixFloat4 GetMin() { return _mm_set1_ps(std::numeric_limits<nixFloat>::min()); }
    static NIX_INLINE __nixFloat4 GetMax() { return _mm_set1_ps(std::numeric_limits<nixFloat>::max()); }
    static NIX_INLINE __nixFloat4 GetPlusInf() { return _mm_set1_ps(std::numeric_limits<nixFloat>::infinity()); }
    static NIX_INLINE __nixFloat4 GetMinusInf() { return _mm_set1_ps(-std::numeric_limits<nixFloat>::infinity()); }

    static NIX_INLINE __nixFloat4 GetSmallNumber() { return _mm_set1_ps(1.e-8f); }
    static NIX_INLINE __nixFloat4 GetBigNumber() { return _mm_set1_ps(1.e+8f); }


    static NIX_INLINE __nixInt4 GetZeroI() { return _mm_set1_epi32(0u); }
    static NIX_INLINE __nixInt4 GetOneI() { return _mm_set1_epi32(1u); }
    static NIX_INLINE __nixInt4 GetOneNegI() { return _mm_set1_epi32(~1u); }
    static NIX_INLINE __nixInt4 GetTwoI() { return _mm_set1_epi32(2u); }
    static NIX_INLINE __nixInt4 GetFourI() { return _mm_set1_epi32(4u); }
    static NIX_INLINE __nixInt4 Get127I() { return _mm_set1_epi32(127u); }


#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

    static NIX_INLINE __nixFloat16 GetZero512() { return _mm512_setzero_ps(); }
    static NIX_INLINE __nixFloat16 GetOne512() { return _mm512_set1_ps(1.0f); }

    static NIX_INLINE __nixFloat16 Set(
        const nixFloat& _x0, const nixFloat& _y0, const nixFloat& _z0, const nixFloat& _w0, 
        const nixFloat& _x1, const nixFloat& _y1, const nixFloat& _z1, const nixFloat& _w1,
        const nixFloat& _x2, const nixFloat& _y2, const nixFloat& _z2, const nixFloat& _w2, 
        const nixFloat&_x3, const nixFloat& _y3, const nixFloat& _z3, const nixFloat& _w3) {
        return _mm512_set_ps(_w3, _z3, _y3, _x3, _w2, _z2, _y2, _x2, _w1, _z1, _y1, _x1, _w0, _z0, _y0, _x0);
    }
    static NIX_INLINE __nixFloat16 Add(const __nixFloat16& _a, const __nixFloat16& _b) { return _mm512_add_ps(_a, _b); }
    static NIX_INLINE __nixFloat16 Sub(const __nixFloat16& _a, const __nixFloat16& _b) { return _mm512_sub_ps(_a, _b); }
    static NIX_INLINE __nixFloat16 Mul(const __nixFloat16& _a, const __nixFloat16& _b) { return _mm512_mul_ps(_a, _b); }
    static NIX_INLINE __nixFloat16 Div(const __nixFloat16& _a, const __nixFloat16& _b) { return _mm512_div_ps(_a, _b); }
    static NIX_INLINE __nixFloat16 Splat512(nixFloat _v) { return _mm512_set1_ps(_v); }


#   endif


#   if NIX_ARCH & NIX_ARCH_AVX_FLAG

    static NIX_INLINE __nixFloat8 GetZero256() { return _mm256_setzero_ps(); }
    static NIX_INLINE __nixFloat8 GetOne256() { return _mm256_set1_ps(1.0f); }

    static NIX_INLINE __nixFloat8 Set(const nixFloat& _x0, const nixFloat& _y0, const nixFloat& _z0, const nixFloat& _w0, const nixFloat& _x1, const nixFloat& _y1, const nixFloat& _z1, const nixFloat& _w1) { return _mm256_set_ps(_w1, _z1, _y1, _x1, _w0, _z0, _y0, _x0); }
    static NIX_INLINE __nixFloat8 Add(const __nixFloat8& _a, const __nixFloat8& _b) { return _mm256_add_ps(_a, _b); }
    static NIX_INLINE __nixFloat8 Sub(const __nixFloat8& _a, const __nixFloat8& _b) { return _mm256_sub_ps(_a, _b); }
    static NIX_INLINE __nixFloat8 Mul(const __nixFloat8& _a, const __nixFloat8& _b) { return _mm256_mul_ps(_a, _b); }
    static NIX_INLINE __nixFloat8 Div(const __nixFloat8& _a, const __nixFloat8& _b) { return _mm256_div_ps(_a, _b); }
    static NIX_INLINE __nixFloat8 Splat256(nixFloat _v) { return _mm256_set1_ps(_v); }

#   endif

    static NIX_INLINE __nixFloat4 Set(const nixFloat& _x, const nixFloat& _y, const nixFloat& _z, const nixFloat& _w) { return _mm_set_ps(_w, _z, _y, _x); }
    static NIX_INLINE __nixFloat4 Add(const __nixFloat4& _a, const __nixFloat4& _b) { return _mm_add_ps(_a, _b); }
    static NIX_INLINE __nixFloat4 Sub(const __nixFloat4& _a, const __nixFloat4& _b) { return _mm_sub_ps(_a, _b); }
    static NIX_INLINE __nixFloat4 Mul(const __nixFloat4& _a, const __nixFloat4& _b) { return _mm_mul_ps(_a, _b); }
    static NIX_INLINE __nixFloat4 Div(const __nixFloat4& _a, const __nixFloat4& _b) { return _mm_div_ps(_a, _b); }

    static NIX_INLINE __nixFloat4 Splat(const nixFloat& _v) 
    { 
#   if NIX_ARCH & NIX_ARCH_AVX_FLAG
        return _mm_broadcast_ss(&_v);
#   else
        return _mm_set1_ps(_v);
#   endif
    }

    static NIX_INLINE __nixInt4 Splat(const nixS32& _v)
    {
        return _mm_set1_epi32(_v);
    }
    static NIX_INLINE __nixInt4 Splat(const nixU32& _v)
    {
        return _mm_set1_epi32(_v);
    }


    static NIX_INLINE __nixFloat4 Abs(const __nixFloat4& _v) { return _mm_andnot_ps(VectorHelper::GetSignMask(), _v); }
    static NIX_INLINE __nixFloat4 Neg(const __nixFloat4& _v) { return _mm_xor_ps(_v, VectorHelper::GetSignMask()); }

    static NIX_INLINE __nixFloat4 Sqrt(const __nixFloat4& _v) { return _mm_sqrt_ps(_v); }
    static NIX_INLINE __nixFloat4 ReciprocalSqrt(const __nixFloat4& _v) { return _mm_rsqrt_ps(_v); }

    static NIX_INLINE __nixFloat4 Round(const __nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_round_ps(_v, _MM_FROUND_TO_NEAREST_INT);
#   else
        const __nixFloat4 sgn = VectorHelper::GetSignMask();
        const __nixFloat4 and = _mm_and_ps(sgn, _v);
        const __nixFloat4 or = _mm_or_ps(and, VectorHelper::Splat(8388608.0f));
        const __nixFloat4 add = VectorHelper::Add(_v, or );
        const __nixFloat4 sub = VectorHelper::Sub(add, or );
        return sub;
#   endif
    }

    static NIX_INLINE __nixFloat4 Floor(const __nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
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
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
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
    static NIX_INLINE __nixFloat4 Min(const __nixFloat4& _x, const nixFloat& _y) { return _mm_min_ps(_x, VectorHelper::Splat(_y)); }
    static NIX_INLINE __nixFloat4 Max(const __nixFloat4& _x, const __nixFloat4& _y) { return _mm_max_ps(_x, _y); }
    static NIX_INLINE __nixFloat4 Max(const __nixFloat4& _x, const nixFloat& _y) { return _mm_max_ps(_x, VectorHelper::Splat(_y)); }

    // Computes and returns _x * _y + _v.
    static NIX_INLINE __nixFloat4 MulAdd(const __nixFloat4& _x, const __nixFloat4& _y, const __nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_AVX2_FLAG
        return _mm_fmadd_ps(_x, _y, _v);
#   else
        return VectorHelper::Add(VectorHelper::Mul(_x, _y), _v);
#   endif
    }

    static NIX_INLINE __nixFloat4 Dot(const __nixFloat4& _a, const __nixFloat4& _b)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_dp_ps(_a, _b, 0xff); // 1111 1111 -> all values are computed and the result is saved to the whole register
#    elif NIX_ARCH & NIX_ARCH_SSE3_FLAG
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
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_dp_ps(_a, _b, 0x7f); // 0111 1111 -> the w value of arrays are not computed. The result is saved to the whole register
#    elif NIX_ARCH & NIX_ARCH_SSE3_FLAG
        const __nixFloat4 aW0 = VectorHelper::Mul(_a, kZeroingW);
        const __nixFloat4 bW0 = VectorHelper::Mul(_b, kZeroingW);
        const __nixFloat4 mul = VectorHelper::Mul(aW0, bW0);
        const __nixFloat4 add = _mm_hadd_ps(mul, mul);
        const __nixFloat4 res = _mm_hadd_ps(add, add);
        return res;
#   else
        const __nixFloat4 aW0 = VectorHelper::Mul(_a, kZeroingW);
        const __nixFloat4 bW0 = VectorHelper::Mul(_b, kZeroingW);
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
        const __nixFloat4 max = VectorHelper::Max(min, _min);
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

    static NIX_INLINE __nixFloat4 Pow(const __nixFloat4& _x, const __nixFloat4& _y)
    {
        //pow(x, y) == exp(y*log(x))
        return exp_ps(VectorHelper::Mul(_y, log_ps(_x)));
    }

    static NIX_INLINE __nixFloat4 Lerp(const __nixFloat4& _from, const __nixFloat4& _to, const __nixFloat4& _t)
    {
        const __nixFloat4 sub = VectorHelper::Sub(VectorHelper::GetOne(), _t);
        const __nixFloat4 mul0 = VectorHelper::Mul(sub, _from);
        const __nixFloat4 mul1= VectorHelper::Mul(_t, _to);
        const __nixFloat4 add = VectorHelper::Add(mul0, mul1);
        return add;
    }

    static NIX_INLINE __nixFloat4 Step(const __nixFloat4& _from, const __nixFloat4& _to, const __nixFloat4& _t)
    {
        const __nixFloat4 edge = GetHalf();
        const __nixFloat4 cmp0 = _mm_cmpngt_ps(_t, edge);

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

    static NIX_INLINE __nixFloat4 HermiteCubicSpline(const __nixFloat4& _p0, const __nixFloat4& _m0, const __nixFloat4& _p1, const __nixFloat4& _m1, const __nixFloat4& _t)
    {
        static const __nixFloat4 one = Splat(1.0f);
        static const __nixFloat4 two = Splat(2.0f);
        static const __nixFloat4 minustwo = Splat(-2.0f);
        static const __nixFloat4 three = Splat(3.0f);

        const __nixFloat4 p0c = VectorHelper::Add(VectorHelper::Sub(VectorHelper::Mul(two, Pow(_t, three)), VectorHelper::Mul(three, Pow(_t, two))), one);
        const __nixFloat4 m0c = VectorHelper::Add(VectorHelper::Sub(Pow(_t, three), VectorHelper::Mul(two, Pow(_t, two))), _t);
        const __nixFloat4 p1c = VectorHelper::Add(VectorHelper::Mul(minustwo, Pow(_t, three)), VectorHelper::Mul(three, Pow(_t, two)));
        const __nixFloat4 m1c = VectorHelper::Sub(Pow(_t, three), Pow(_t, two));

        const __nixFloat4 p0 = VectorHelper::Mul(p0c, _p0);
        const __nixFloat4 m0 = VectorHelper::Mul(m0c, _m0);
        const __nixFloat4 p1 = VectorHelper::Mul(p1c, _p1);
        const __nixFloat4 m1 = VectorHelper::Mul(m1c, _m1);

        const __nixFloat4 add0 = VectorHelper::Add(p0, m0);
        const __nixFloat4 add1 = VectorHelper::Add(p1, m1);

        const __nixFloat4 add = VectorHelper::Add(add0, add1);

        return add;
    }


    // is a bit slow
    static NIX_INLINE __nixFloat4 InverseLerp(const __nixFloat4& _v, const __nixFloat4& _min, const __nixFloat4& _max)
    {
        const __nixFloat4 equal = _mm_cmpeq_ps(_min, _max);
        const nixS16 mask = _mm_movemask_ps(equal);
        if (mask == 0xffffffff)
        {
            return VectorHelper::GetZero();
        }
        else
        {
            const __nixFloat4 sub0 = VectorHelper::Sub(_v, _min);
            const __nixFloat4 sub1 = VectorHelper::Sub(_max, _min);
            const __nixFloat4 div = VectorHelper::Div(sub0, sub1);
            return div;
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // Faster helper accessor for swizzle
    //////////////////////////////////////////////////////////////////////////

    static NIX_INLINE __nixFloat4 InsertAt(const __nixFloat4& _v, nixFloat _x, nixU32 _i)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_insert_ps(_v, _mm_set_ss(_x), _i << 4);
#   else
        NIX_SIMD_ALIGN_16 nixU32 mask[4] = { 0xffffffff,0xffffffff,0xffffffff,0xffffffff };
        __nixFloat4 tmp, vec_masked, p_masked;
        mask[_i >> 4] = 0x0; 
        vec_masked = _mm_and_ps(*(__nixFloat4*)mask, _v);
        p_masked = _mm_andnot_ps(*(__nixFloat4*)mask, _mm_set_ss(_x));
        tmp = _mm_or_ps(vec_masked, p_masked);
        return tmp;
#   endif
    }

    static NIX_INLINE nixFloat ExtractX(const __nixFloat4& _v)
    {
        return _mm_cvtss_f32(_v);
    }

    static NIX_INLINE nixFloat ExtractY(const __nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        nixFloat r;
        _MM_EXTRACT_FLOAT(r, _v, 1);
        return r;
#   else
        return _mm_cvtss_f32(_mm_shuffle_ps(_v, _v, _MM_SHUFFLE(1, 1, 1, 1)));
#   endif
    }

    static NIX_INLINE nixFloat ExtractZ(const __nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        nixFloat r;
        _MM_EXTRACT_FLOAT(r, _v, 2);
        return r;
#   else
        return _mm_cvtss_f32(_mm_shuffle_ps(_v, _v, _MM_SHUFFLE(2, 2, 2, 2)));
#   endif
    }

    static NIX_INLINE nixFloat ExtractW(const __nixFloat4& _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        nixFloat r;
        _MM_EXTRACT_FLOAT(r, _v, 3);
        return r;
#   else
        return _mm_cvtss_f32(_mm_shuffle_ps(_v, _v, _MM_SHUFFLE(3, 3, 3, 3)));
#   endif
    }

    static NIX_INLINE __nixFloat4 XXXX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 0, 0); }
    static NIX_INLINE __nixFloat4 XXXY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 0, 1); }
    static NIX_INLINE __nixFloat4 XXXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 0, 2); }
    static NIX_INLINE __nixFloat4 XXXW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 0, 3); }
    static NIX_INLINE __nixFloat4 XXYX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 1, 0); }
    static NIX_INLINE __nixFloat4 XXYY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 1, 1); }
    static NIX_INLINE __nixFloat4 XXYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 1, 2); }
    static NIX_INLINE __nixFloat4 XXYW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 1, 3); }
    static NIX_INLINE __nixFloat4 XXZX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 2, 0); }
    static NIX_INLINE __nixFloat4 XXZY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 2, 1); }
    static NIX_INLINE __nixFloat4 XXZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 2, 2); }
    static NIX_INLINE __nixFloat4 XXZW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 2, 3); }
    static NIX_INLINE __nixFloat4 XXWX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 3, 0); }
    static NIX_INLINE __nixFloat4 XXWY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 3, 1); }
    static NIX_INLINE __nixFloat4 XXWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 3, 2); }
    static NIX_INLINE __nixFloat4 XXWW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 0, 3, 3); }
    static NIX_INLINE __nixFloat4 XYXX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 0, 0); }
    static NIX_INLINE __nixFloat4 XYXY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 0, 1); }
    static NIX_INLINE __nixFloat4 XYXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 0, 2); }
    static NIX_INLINE __nixFloat4 XYXW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 0, 3); }
    static NIX_INLINE __nixFloat4 XYYX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 1, 0); }
    static NIX_INLINE __nixFloat4 XYYY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 1, 1); }
    static NIX_INLINE __nixFloat4 XYYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 1, 2); }
    static NIX_INLINE __nixFloat4 XYYW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 1, 3); }
    static NIX_INLINE __nixFloat4 XYZX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 2, 0); }
    static NIX_INLINE __nixFloat4 XYZY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 2, 1); }
    static NIX_INLINE __nixFloat4 XYZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 2, 2); }
    static NIX_INLINE __nixFloat4 XYZW(const __nixFloat4& _v) { return _v; }
    static NIX_INLINE __nixFloat4 XYWX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 3, 0); }
    static NIX_INLINE __nixFloat4 XYWY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 3, 1); }
    static NIX_INLINE __nixFloat4 XYWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 3, 2); }
    static NIX_INLINE __nixFloat4 XYWW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 1, 3, 3); }
    static NIX_INLINE __nixFloat4 XZXX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 0, 0); }
    static NIX_INLINE __nixFloat4 XZXY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 0, 1); }
    static NIX_INLINE __nixFloat4 XZXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 0, 2); }
    static NIX_INLINE __nixFloat4 XZXW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 0, 3); }
    static NIX_INLINE __nixFloat4 XZYX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 1, 0); }
    static NIX_INLINE __nixFloat4 XZYY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 1, 1); }
    static NIX_INLINE __nixFloat4 XZYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 1, 2); }
    static NIX_INLINE __nixFloat4 XZYW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 1, 3); }
    static NIX_INLINE __nixFloat4 XZZX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 2, 0); }
    static NIX_INLINE __nixFloat4 XZZY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 2, 1); }
    static NIX_INLINE __nixFloat4 XZZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 2, 2); }
    static NIX_INLINE __nixFloat4 XZZW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 2, 3); }
    static NIX_INLINE __nixFloat4 XZWX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 3, 0); }
    static NIX_INLINE __nixFloat4 XZWY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 3, 1); }
    static NIX_INLINE __nixFloat4 XZWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 3, 2); }
    static NIX_INLINE __nixFloat4 XZWW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 2, 3, 3); }
    static NIX_INLINE __nixFloat4 XWXX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 0, 0); }
    static NIX_INLINE __nixFloat4 XWXY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 0, 1); }
    static NIX_INLINE __nixFloat4 XWXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 0, 2); }
    static NIX_INLINE __nixFloat4 XWXW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 0, 3); }
    static NIX_INLINE __nixFloat4 XWYX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 1, 0); }
    static NIX_INLINE __nixFloat4 XWYY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 1, 1); }
    static NIX_INLINE __nixFloat4 XWYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 1, 2); }
    static NIX_INLINE __nixFloat4 XWYW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 1, 3); }
    static NIX_INLINE __nixFloat4 XWZX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 2, 0); }
    static NIX_INLINE __nixFloat4 XWZY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 2, 1); }
    static NIX_INLINE __nixFloat4 XWZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 2, 2); }
    static NIX_INLINE __nixFloat4 XWZW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 2, 3); }
    static NIX_INLINE __nixFloat4 XWWX(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 3, 0); }
    static NIX_INLINE __nixFloat4 XWWY(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 3, 1); }
    static NIX_INLINE __nixFloat4 XWWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 3, 2); }
    static NIX_INLINE __nixFloat4 XWWW(const __nixFloat4& _v) { return SWIZZLE(_v, 0, 3, 3, 3); }

    static NIX_INLINE __nixFloat4 YXXX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 0, 0); }
    static NIX_INLINE __nixFloat4 YXXY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 0, 1); }
    static NIX_INLINE __nixFloat4 YXXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 0, 2); }
    static NIX_INLINE __nixFloat4 YXXW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 0, 3); }
    static NIX_INLINE __nixFloat4 YXYX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 1, 0); }
    static NIX_INLINE __nixFloat4 YXYY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 1, 1); }
    static NIX_INLINE __nixFloat4 YXYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 1, 2); }
    static NIX_INLINE __nixFloat4 YXYW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 1, 3); }
    static NIX_INLINE __nixFloat4 YXZX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 2, 0); }
    static NIX_INLINE __nixFloat4 YXZY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 2, 1); }
    static NIX_INLINE __nixFloat4 YXZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 2, 2); }
    static NIX_INLINE __nixFloat4 YXZW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 2, 3); }
    static NIX_INLINE __nixFloat4 YXWX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 3, 0); }
    static NIX_INLINE __nixFloat4 YXWY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 3, 1); }
    static NIX_INLINE __nixFloat4 YXWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 3, 2); }
    static NIX_INLINE __nixFloat4 YXWW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 0, 3, 3); }
    static NIX_INLINE __nixFloat4 YYXX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 0, 0); }
    static NIX_INLINE __nixFloat4 YYXY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 0, 1); }
    static NIX_INLINE __nixFloat4 YYXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 0, 2); }
    static NIX_INLINE __nixFloat4 YYXW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 0, 3); }
    static NIX_INLINE __nixFloat4 YYYX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 1, 0); }
    static NIX_INLINE __nixFloat4 YYYY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 1, 1); }
    static NIX_INLINE __nixFloat4 YYYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 1, 2); }
    static NIX_INLINE __nixFloat4 YYYW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 1, 3); }
    static NIX_INLINE __nixFloat4 YYZX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 2, 0); }
    static NIX_INLINE __nixFloat4 YYZY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 2, 1); }
    static NIX_INLINE __nixFloat4 YYZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 2, 2); }
    static NIX_INLINE __nixFloat4 YYZW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 2, 3); }
    static NIX_INLINE __nixFloat4 YYWX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 3, 0); }
    static NIX_INLINE __nixFloat4 YYWY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 3, 1); }
    static NIX_INLINE __nixFloat4 YYWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 3, 2); }
    static NIX_INLINE __nixFloat4 YYWW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 1, 3, 3); }
    static NIX_INLINE __nixFloat4 YZXX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 0, 0); }
    static NIX_INLINE __nixFloat4 YZXY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 0, 1); }
    static NIX_INLINE __nixFloat4 YZXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 0, 2); }
    static NIX_INLINE __nixFloat4 YZXW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 0, 3); }
    static NIX_INLINE __nixFloat4 YZYX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 1, 0); }
    static NIX_INLINE __nixFloat4 YZYY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 1, 1); }
    static NIX_INLINE __nixFloat4 YZYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 1, 2); }
    static NIX_INLINE __nixFloat4 YZYW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 1, 3); }
    static NIX_INLINE __nixFloat4 YZZX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 2, 0); }
    static NIX_INLINE __nixFloat4 YZZY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 2, 1); }
    static NIX_INLINE __nixFloat4 YZZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 2, 2); }
    static NIX_INLINE __nixFloat4 YZZW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 2, 3); }
    static NIX_INLINE __nixFloat4 YZWX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 3, 0); }
    static NIX_INLINE __nixFloat4 YZWY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 3, 1); }
    static NIX_INLINE __nixFloat4 YZWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 3, 2); }
    static NIX_INLINE __nixFloat4 YZWW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 2, 3, 3); }
    static NIX_INLINE __nixFloat4 YWXX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 0, 0); }
    static NIX_INLINE __nixFloat4 YWXY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 0, 1); }
    static NIX_INLINE __nixFloat4 YWXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 0, 2); }
    static NIX_INLINE __nixFloat4 YWXW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 0, 3); }
    static NIX_INLINE __nixFloat4 YWYX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 1, 0); }
    static NIX_INLINE __nixFloat4 YWYY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 1, 1); }
    static NIX_INLINE __nixFloat4 YWYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 1, 2); }
    static NIX_INLINE __nixFloat4 YWYW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 1, 3); }
    static NIX_INLINE __nixFloat4 YWZX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 2, 0); }
    static NIX_INLINE __nixFloat4 YWZY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 2, 1); }
    static NIX_INLINE __nixFloat4 YWZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 2, 2); }
    static NIX_INLINE __nixFloat4 YWZW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 2, 3); }
    static NIX_INLINE __nixFloat4 YWWX(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 3, 0); }
    static NIX_INLINE __nixFloat4 YWWY(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 3, 1); }
    static NIX_INLINE __nixFloat4 YWWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 3, 2); }
    static NIX_INLINE __nixFloat4 YWWW(const __nixFloat4& _v) { return SWIZZLE(_v, 1, 3, 3, 3); }

    static NIX_INLINE __nixFloat4 ZXXX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 0, 0); }
    static NIX_INLINE __nixFloat4 ZXXY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 0, 1); }
    static NIX_INLINE __nixFloat4 ZXXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 0, 2); }
    static NIX_INLINE __nixFloat4 ZXXW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 0, 3); }
    static NIX_INLINE __nixFloat4 ZXYX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 1, 0); }
    static NIX_INLINE __nixFloat4 ZXYY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 1, 1); }
    static NIX_INLINE __nixFloat4 ZXYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 1, 2); }
    static NIX_INLINE __nixFloat4 ZXYW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 1, 3); }
    static NIX_INLINE __nixFloat4 ZXZX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 2, 0); }
    static NIX_INLINE __nixFloat4 ZXZY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 2, 1); }
    static NIX_INLINE __nixFloat4 ZXZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 2, 2); }
    static NIX_INLINE __nixFloat4 ZXZW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 2, 3); }
    static NIX_INLINE __nixFloat4 ZXWX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 3, 0); }
    static NIX_INLINE __nixFloat4 ZXWY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 3, 1); }
    static NIX_INLINE __nixFloat4 ZXWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 3, 2); }
    static NIX_INLINE __nixFloat4 ZXWW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 0, 3, 3); }
    static NIX_INLINE __nixFloat4 ZYXX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 0, 0); }
    static NIX_INLINE __nixFloat4 ZYXY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 0, 1); }
    static NIX_INLINE __nixFloat4 ZYXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 0, 2); }
    static NIX_INLINE __nixFloat4 ZYXW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 0, 3); }
    static NIX_INLINE __nixFloat4 ZYYX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 1, 0); }
    static NIX_INLINE __nixFloat4 ZYYY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 1, 1); }
    static NIX_INLINE __nixFloat4 ZYYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 1, 2); }
    static NIX_INLINE __nixFloat4 ZYYW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 1, 3); }
    static NIX_INLINE __nixFloat4 ZYZX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 2, 0); }
    static NIX_INLINE __nixFloat4 ZYZY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 2, 1); }
    static NIX_INLINE __nixFloat4 ZYZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 2, 2); }
    static NIX_INLINE __nixFloat4 ZYZW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 2, 3); }
    static NIX_INLINE __nixFloat4 ZYWX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 3, 0); }
    static NIX_INLINE __nixFloat4 ZYWY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 3, 1); }
    static NIX_INLINE __nixFloat4 ZYWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 3, 2); }
    static NIX_INLINE __nixFloat4 ZYWW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 1, 3, 3); }
    static NIX_INLINE __nixFloat4 ZZXX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 0, 0); }
    static NIX_INLINE __nixFloat4 ZZXY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 0, 1); }
    static NIX_INLINE __nixFloat4 ZZXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 0, 2); }
    static NIX_INLINE __nixFloat4 ZZXW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 0, 3); }
    static NIX_INLINE __nixFloat4 ZZYX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 1, 0); }
    static NIX_INLINE __nixFloat4 ZZYY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 1, 1); }
    static NIX_INLINE __nixFloat4 ZZYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 1, 2); }
    static NIX_INLINE __nixFloat4 ZZYW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 1, 3); }
    static NIX_INLINE __nixFloat4 ZZZX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 2, 0); }
    static NIX_INLINE __nixFloat4 ZZZY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 2, 1); }
    static NIX_INLINE __nixFloat4 ZZZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 2, 2); }
    static NIX_INLINE __nixFloat4 ZZZW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 2, 3); }
    static NIX_INLINE __nixFloat4 ZZWX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 3, 0); }
    static NIX_INLINE __nixFloat4 ZZWY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 3, 1); }
    static NIX_INLINE __nixFloat4 ZZWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 3, 2); }
    static NIX_INLINE __nixFloat4 ZZWW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 2, 3, 3); }
    static NIX_INLINE __nixFloat4 ZWXX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 0, 0); }
    static NIX_INLINE __nixFloat4 ZWXY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 0, 1); }
    static NIX_INLINE __nixFloat4 ZWXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 0, 2); }
    static NIX_INLINE __nixFloat4 ZWXW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 0, 3); }
    static NIX_INLINE __nixFloat4 ZWYX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 1, 0); }
    static NIX_INLINE __nixFloat4 ZWYY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 1, 1); }
    static NIX_INLINE __nixFloat4 ZWYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 1, 2); }
    static NIX_INLINE __nixFloat4 ZWYW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 1, 3); }
    static NIX_INLINE __nixFloat4 ZWZX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 2, 0); }
    static NIX_INLINE __nixFloat4 ZWZY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 2, 1); }
    static NIX_INLINE __nixFloat4 ZWZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 2, 2); }
    static NIX_INLINE __nixFloat4 ZWZW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 2, 3); }
    static NIX_INLINE __nixFloat4 ZWWX(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 3, 0); }
    static NIX_INLINE __nixFloat4 ZWWY(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 3, 1); }
    static NIX_INLINE __nixFloat4 ZWWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 3, 2); }
    static NIX_INLINE __nixFloat4 ZWWW(const __nixFloat4& _v) { return SWIZZLE(_v, 2, 3, 3, 3); }

    static NIX_INLINE __nixFloat4 WXXX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 0, 0); }
    static NIX_INLINE __nixFloat4 WXXY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 0, 1); }
    static NIX_INLINE __nixFloat4 WXXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 0, 2); }
    static NIX_INLINE __nixFloat4 WXXW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 0, 3); }
    static NIX_INLINE __nixFloat4 WXYX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 1, 0); }
    static NIX_INLINE __nixFloat4 WXYY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 1, 1); }
    static NIX_INLINE __nixFloat4 WXYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 1, 2); }
    static NIX_INLINE __nixFloat4 WXYW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 1, 3); }
    static NIX_INLINE __nixFloat4 WXZX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 2, 0); }
    static NIX_INLINE __nixFloat4 WXZY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 2, 1); }
    static NIX_INLINE __nixFloat4 WXZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 2, 2); }
    static NIX_INLINE __nixFloat4 WXZW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 2, 3); }
    static NIX_INLINE __nixFloat4 WXWX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 3, 0); }
    static NIX_INLINE __nixFloat4 WXWY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 3, 1); }
    static NIX_INLINE __nixFloat4 WXWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 3, 2); }
    static NIX_INLINE __nixFloat4 WXWW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 0, 3, 3); }
    static NIX_INLINE __nixFloat4 WYXX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 0, 0); }
    static NIX_INLINE __nixFloat4 WYXY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 0, 1); }
    static NIX_INLINE __nixFloat4 WYXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 0, 2); }
    static NIX_INLINE __nixFloat4 WYXW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 0, 3); }
    static NIX_INLINE __nixFloat4 WYYX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 1, 0); }
    static NIX_INLINE __nixFloat4 WYYY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 1, 1); }
    static NIX_INLINE __nixFloat4 WYYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 1, 2); }
    static NIX_INLINE __nixFloat4 WYYW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 1, 3); }
    static NIX_INLINE __nixFloat4 WYZX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 2, 0); }
    static NIX_INLINE __nixFloat4 WYZY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 2, 1); }
    static NIX_INLINE __nixFloat4 WYZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 2, 2); }
    static NIX_INLINE __nixFloat4 WYZW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 2, 3); }
    static NIX_INLINE __nixFloat4 WYWX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 3, 0); }
    static NIX_INLINE __nixFloat4 WYWY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 3, 1); }
    static NIX_INLINE __nixFloat4 WYWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 3, 2); }
    static NIX_INLINE __nixFloat4 WYWW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 1, 3, 3); }
    static NIX_INLINE __nixFloat4 WZXX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 0, 0); }
    static NIX_INLINE __nixFloat4 WZXY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 0, 1); }
    static NIX_INLINE __nixFloat4 WZXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 0, 2); }
    static NIX_INLINE __nixFloat4 WZXW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 0, 3); }
    static NIX_INLINE __nixFloat4 WZYX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 1, 0); }
    static NIX_INLINE __nixFloat4 WZYY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 1, 1); }
    static NIX_INLINE __nixFloat4 WZYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 1, 2); }
    static NIX_INLINE __nixFloat4 WZYW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 1, 3); }
    static NIX_INLINE __nixFloat4 WZZX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 2, 0); }
    static NIX_INLINE __nixFloat4 WZZY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 2, 1); }
    static NIX_INLINE __nixFloat4 WZZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 2, 2); }
    static NIX_INLINE __nixFloat4 WZZW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 2, 3); }
    static NIX_INLINE __nixFloat4 WZWX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 3, 0); }
    static NIX_INLINE __nixFloat4 WZWY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 3, 1); }
    static NIX_INLINE __nixFloat4 WZWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 3, 2); }
    static NIX_INLINE __nixFloat4 WZWW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 2, 3, 3); }
    static NIX_INLINE __nixFloat4 WWXX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 0, 0); }
    static NIX_INLINE __nixFloat4 WWXY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 0, 1); }
    static NIX_INLINE __nixFloat4 WWXZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 0, 2); }
    static NIX_INLINE __nixFloat4 WWXW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 0, 3); }
    static NIX_INLINE __nixFloat4 WWYX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 1, 0); }
    static NIX_INLINE __nixFloat4 WWYY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 1, 1); }
    static NIX_INLINE __nixFloat4 WWYZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 1, 2); }
    static NIX_INLINE __nixFloat4 WWYW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 1, 3); }
    static NIX_INLINE __nixFloat4 WWZX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 2, 0); }
    static NIX_INLINE __nixFloat4 WWZY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 2, 1); }
    static NIX_INLINE __nixFloat4 WWZZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 2, 2); }
    static NIX_INLINE __nixFloat4 WWZW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 2, 3); }
    static NIX_INLINE __nixFloat4 WWWX(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 3, 0); }
    static NIX_INLINE __nixFloat4 WWWY(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 3, 1); }
    static NIX_INLINE __nixFloat4 WWWZ(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 3, 2); }
    static NIX_INLINE __nixFloat4 WWWW(const __nixFloat4& _v) { return SWIZZLE(_v, 3, 3, 3, 3); }

    //////////////////////////////////////////////////////////////////////////

    static NIX_INLINE __nixFloat4 AX_BX_AY_BY(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_unpacklo_ps(_a, _b); }
    static NIX_INLINE __nixFloat4 AX_AY_BX_BY(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_movelh_ps(_a, _b); }
    static NIX_INLINE __nixFloat4 AZ_BZ_AW_BW(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_unpackhi_ps(_a, _b); }
    static NIX_INLINE __nixFloat4 BZ_BW_AZ_AW(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_movehl_ps(_a, _b); }
    static NIX_INLINE __nixFloat4 BX_AY_AZ_AW(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_move_ss(_a, _b); }
    static NIX_INLINE __nixFloat4 AX_AX_AZ_AZ(const __nixFloat4& _a)                          
    {
#   if NIX_ARCH & NIX_ARCH_SSE3_FLAG
        return _mm_moveldup_ps(_a);
#   else
        return _mm_shuffle_ps(_a, _a, _MM_SHUFFLE(2, 2, 0, 0));
#   endif   
    }
    static NIX_INLINE __nixFloat4 AY_AX_BY_BX(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(0, 1, 0, 1)); }
    static NIX_INLINE __nixFloat4 AW_AZ_BW_BZ(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(2, 3, 2, 3)); }
    static NIX_INLINE __nixFloat4 AW_AX_BY_BZ(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(2, 1, 0, 3)); }
    static NIX_INLINE __nixFloat4 AX_AY_BX_BW(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 0, 1, 0)); }
    static NIX_INLINE __nixFloat4 AZ_AW_BY_BW(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 1, 3, 2)); }
    static NIX_INLINE __nixFloat4 AX_AY_BZ_BW(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 2, 1, 0)); }
    static NIX_INLINE __nixFloat4 AX_AZ_BX_BZ(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(2, 0, 2, 0)); }
    static NIX_INLINE __nixFloat4 AY_AW_BY_BW(const __nixFloat4& _a, const __nixFloat4& _b)    { return _mm_shuffle_ps(_a, _b, _MM_SHUFFLE(3, 1, 3, 1)); }

    //////////////////////////////////////////////////////////////////////////

private:
    constexpr static NIX_SIMD_ALIGN_16 const __nixFloat4 kZeroingW = { 1.0f, 1.0f, 1.0f, 0.0f };
    //constexpr static NIX_SIMD_ALIGN_16 const nixU32 maskRaw[] = { 0xffffffff, 0xffffffff, 0xffffffff, 0 };
};


NIX_NAMESPACE_END