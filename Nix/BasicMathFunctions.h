// Copyright (c) 2018-2025 Michele Condo'
// File: C:\Projects\Nix\Nix\BasicMathFunctions.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.


#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "Constants.h"
#include "Trigonometry.h"
#include "Swizzle.h"


// 
// #ifdef max
// #undef max
// #endif //
// 
// #ifdef min
// #undef min
// #endif //


NIX_NAMESPACE_BEGIN

namespace MathFunctions
{
    NIX_INLINE float128 Set(const float& _x, const float& _y, const float& _z, const float& _w) { return _mm_set_ps(_w, _z, _y, _x); }
    NIX_INLINE float128 Add(const float128 _a, const float128 _b) { return _mm_add_ps(_a, _b); }
    NIX_INLINE float128 Sub(const float128 _a, const float128 _b) { return _mm_sub_ps(_a, _b); }
    NIX_INLINE float128 Mul(const float128 _a, const float128 _b) { return _mm_mul_ps(_a, _b); }
    NIX_INLINE float128 Div(const float128 _a, const float128 _b) { return _mm_div_ps(_a, _b); }

	NIX_INLINE float128 Splat(const float& _v)
	{
#   if NIX_ARCH & NIX_ARCH_AVX_FLAG
		return _mm_broadcast_ss(&_v);
#   else
		return _mm_set1_ps(_v);
#   endif
	}

	NIX_INLINE float128 SplatZero()
	{
		return _mm_set1_ps(0.0f);
	}

	NIX_INLINE float128 SplatOne()
	{
		return _mm_set1_ps(1.0f);
	}

	NIX_INLINE float128 SplatX(float128 _vec)
	{
#   if NIX_ARCH & NIX_ARCH_AVX_FLAG
		return _mm_broadcastss_ps(_vec);
#   else
		return MathFunctions::Swizzle<X, X, X, X>(_vec);
#   endif
	}

	NIX_INLINE float128 SplatY(float128 _vec)
	{
		return MathFunctions::Swizzle<Y, Y, Y, Y>(_vec);
	}

	NIX_INLINE float128 SplatZ(float128 _vec)
	{
		return MathFunctions::Swizzle<Z, Z, Z, Z>(_vec);
	}

	NIX_INLINE float128 SplatW(float128 _vec)
	{
		return MathFunctions::Swizzle<W, W, W, W>(_vec);
	}


    NIX_INLINE float128 Abs(const float128 _v) { return _mm_andnot_ps(kSignBit, _v); }
    NIX_INLINE float128 Neg(const float128 _v) { return _mm_xor_ps(_v, kSignBit); }

    NIX_INLINE float128 Sqrt(const float128 _v) { return _mm_sqrt_ps(_v); }
    NIX_INLINE float128 ReciprocalSqrt(const float128 _v) { return _mm_rsqrt_ps(_v); }

    NIX_INLINE float128 Round(const float128 _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_round_ps(_v, _MM_FROUND_TO_NEAREST_INT);
#   else
        const float128 andv = _mm_and_ps(kSignBit, _v);
        const float128 orv = _mm_or_ps(andv, MathFunctions::Splat(8388608.0f));
        const float128 add = MathFunctions::Add(_v, orv);
        const float128 sub = MathFunctions::Sub(add, orv);
        return sub;
#   endif
    }

    NIX_INLINE float128 Floor(const float128 _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_floor_ps(_v);
#   else
        const float128 rnd = MathFunctions::Round(_v);
        const float128 cmp = _mm_cmplt_ps(_v, rnd);
        const float128 andv = _mm_and_ps(cmp, kOneVec4);
        const float128 sub = MathFunctions::Sub(rnd, andv);
        return sub;
#   endif
    }

    NIX_INLINE float128 Ceil(const float128 _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_ceil_ps(_v);
#   else
        const float128 rnd = MathFunctions::Round(_v);
        const float128 cmp = _mm_cmpgt_ps(_v, rnd);
        const float128 andv = _mm_and_ps(cmp, kOneVec4);
        const float128 add = MathFunctions::Add(rnd, andv);
        return add;
#   endif
    }

    NIX_INLINE float128 Min(const float128 _x, const float128 _y) { return _mm_min_ps(_x, _y); }
    NIX_INLINE float128 Min(const float128 _x, const float& _y) { return _mm_min_ps(_x, MathFunctions::Splat(_y)); }
    NIX_INLINE float128 Max(const float128 _x, const float128 _y) { return _mm_max_ps(_x, _y); }
    NIX_INLINE float128 Max(const float128 _x, const float& _y) { return _mm_max_ps(_x, MathFunctions::Splat(_y)); }

    NIX_INLINE float128 MulAdd(const float128 _x, const float128 _y, const float128 _v)
    {
#   if NIX_ARCH & NIX_ARCH_AVX2_FLAG
        return _mm_fmadd_ps(_x, _y, _v);
#   else
        return MathFunctions::Add(MathFunctions::Mul(_x, _y), _v);
#   endif
    }

	NIX_INLINE float128 NegMulAdd(const float128 _x, const float128 _y, const float128 _v)
	{
#   if NIX_ARCH & NIX_ARCH_AVX2_FLAG
		return _mm_fnmadd_ps(_x, _y, _v);
#   else
		return MathFunctions::Sub(_v, MathFunctions::Mul(_x, _y));
#   endif
	}

    NIX_INLINE float128 Dot(const float128 _a, const float128 _b)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_dp_ps(_a, _b, 0xff); // 1111 1111 -> all values are computed and the result is saved to the whole register
#    elif NIX_ARCH & NIX_ARCH_SSE3_FLAG
        const float128 mul = MathFunctions::Mul(_a, _b);
        const float128 add = _mm_hadd_ps(mul, mul);
        const float128 res = _mm_hadd_ps(add, add);
        return res;
#   else
        const float128 mul = MathFunctions::Mul(_a, _b);
        const float128 add = MathFunctions::Add(mul, MathFunctions::Swizzle<Y, X, W, Z>(mul));
        const float128 res = MathFunctions::Add(add, MathFunctions::Swizzle<W, Z, Y, X>(add));
        return res;
#   endif
    }

    NIX_INLINE float128 Dot3(const float128 _a, const float128 _b)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        return _mm_dp_ps(_a, _b, 0x7f); // 0111 1111 -> the w value of arrays are not computed. The result is saved to the whole register
#    elif NIX_ARCH & NIX_ARCH_SSE3_FLAG
        const float128 aW0 = MathFunctions::Mul(_a, k1110);
        const float128 bW0 = MathFunctions::Mul(_b, k1110);
        const float128 mul = MathFunctions::Mul(aW0, bW0);
        const float128 add = _mm_hadd_ps(mul, mul);
        const float128 res = _mm_hadd_ps(add, add);
        return res;
#   else
        const float128 aW0 = MathFunctions::Mul(_a, kOneVec3);
        const float128 bW0 = MathFunctions::Mul(_b, kOneVec3);
        const float128 mul = MathFunctions::Mul(aW0, bW0);
        const float128 add = MathFunctions::Add(mul, MathFunctions::Swizzle<Y, X, W, Z>(mul));
        const float128 res = MathFunctions::Add(add, MathFunctions::Swizzle<W, Z, Y, X>(add));
        return res;
#   endif
    }

    NIX_INLINE float128 HorizontaSum(float128 _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE3_FLAG
        return _mm_hadd_ps(_v, _v);
#   else
        float128 t;
        t = _mm_movehl_ps(t, _v);
        _v = MathFunctions::Add(_v, t);
        t = _mm_shuffle_ps(_v, _v, 0x55);
        _v = MathFunctions::Add(_v, t);
        return _v;

// 		const float128 t = MathFunctions::Add(_v, _mm_movehl_ps(_v, _v));
// 		const float128 s = _mm_add_ss(t, _mm_shuffle_ps(t, t, 1));
// 		const float128 r = MathFunctions::Swizzle<X, X, X, X>(s);
#   endif
    }

    NIX_INLINE float128 SquareLength(const float128 _v)
    {
        return MathFunctions::Dot(_v, _v);
    }

    NIX_INLINE float128 SquareLength3(const float128 _v)
    {
        return MathFunctions::Dot3(_v, _v);
    }

    NIX_INLINE float128 Length(const float128 _v)
    {
        const float128 sln = MathFunctions::SquareLength(_v);
        const float128 sqt = MathFunctions::Sqrt(sln);
        return sqt;
    }

    NIX_INLINE float128 Length3(const float128 _v)
    {
        const float128 sln = MathFunctions::SquareLength3(_v);
        const float128 sqt = MathFunctions::Sqrt(sln);
        return sqt;
    }

    NIX_INLINE float128 SquareDistance(const float128 _a, const float128 _b)
    {
        const float128 sub = MathFunctions::Sub(_a, _b);
        const float128 sln = MathFunctions::SquareLength(sub);
        return sln;
    }

    NIX_INLINE float128 Distance(const float128 _a, const float128 _b)
    {
        const float128 sub = MathFunctions::Sub(_a, _b);
        const float128 len = MathFunctions::Length(sub);
        return len;
    }

	NIX_INLINE float128 SquareDistance3(const float128 _a, const float128 _b)
	{
		const float128 sub = MathFunctions::Sub(_a, _b);
		const float128 sln = MathFunctions::SquareLength3(sub);
		return sln;
	}

    NIX_INLINE float128 Distance3(const float128 _a, const float128 _b)
    {
        const float128 sub = MathFunctions::Sub(_a, _b);
        const float128 len = MathFunctions::Length3(sub);
        return len;
    }

    NIX_INLINE float128 Cross(const float128 _a, const float128 _b)
    {
        return MathFunctions::Sub(
            MathFunctions::Mul(MathFunctions::Swizzle<Y, Z, X, W>(_a), MathFunctions::Swizzle<Z, X, Y, W>(_b)),
            MathFunctions::Mul(MathFunctions::Swizzle<Z, X, Y, W>(_a), MathFunctions::Swizzle<Y, Z, X, W>(_b))
        );
    }

    NIX_INLINE float128 Mod(const float128 _a, const float128 _b)
    {
        const float128 div = MathFunctions::Div(_a, _b);
        const float128 flr = MathFunctions::Floor(div);
        const float128 mul = MathFunctions::Mul(_b, flr);
        const float128 sub = MathFunctions::Sub(_a, mul);
        return sub;
    }

    NIX_INLINE float128 Clamp(const float128 _v, const float128 _min, const float128 _max)
    {
        const float128 min = MathFunctions::Min(_v, _max);
        const float128 max = MathFunctions::Max(min, _min);
        return max;
    }

    NIX_INLINE float128 FastSqrt(const float128 _v)
    {
        return MathFunctions::Mul(MathFunctions::ReciprocalSqrt(_v), _v);
    }

    NIX_INLINE float128 Normalize(const float128 _v)
    {
        const float128 dot = MathFunctions::Dot(_v, _v);
        const float128 rsr = MathFunctions::ReciprocalSqrt(dot);
        const float128 mul = MathFunctions::Mul(_v, rsr);
        return mul;
    }

    NIX_INLINE float128 Normalize3(const float128 _v)
    {
        const float128 dot = MathFunctions::Dot3(_v, _v);
        const float128 rsr = MathFunctions::ReciprocalSqrt(dot);
        const float128 mul = MathFunctions::Mul(_v, rsr);
        return mul;
    }

    NIX_INLINE float128 Pow(const float128 _x, const float128 _y)
    {
        //pow(x, y) == exp(y*log(x))
        return Trigonometry::Exp(MathFunctions::Mul(_y, Trigonometry::Log(_x)));
    }

    NIX_INLINE float128 Lerp(const float128 _from, const float128 _to, const float128 _t)
    {
        const float128 sub = MathFunctions::Sub(kOneVec4, _t);
        const float128 mul0 = MathFunctions::Mul(sub, _from);
        const float128 mul1= MathFunctions::Mul(_t, _to);
        const float128 add = MathFunctions::Add(mul0, mul1);
        return add;
    }

    NIX_INLINE float128 Step(const float128 _from, const float128 _to, const float128 _t)
    {
        const float128 cmp0 = _mm_cmpngt_ps(_t, kOneHalfVec4);

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

    NIX_INLINE float128 HermiteCubicSpline(const float128 _p0, const float128 _m0, const float128 _p1, const float128 _m1, const float128 _t)
    {
        static const float128 one = MathFunctions::Splat(1.0f);
        static const float128 two = MathFunctions::Splat(2.0f);
        static const float128 minustwo = MathFunctions::Splat(-2.0f);
        static const float128 three = MathFunctions::Splat(3.0f);

        const float128 p0c = MathFunctions::Add(MathFunctions::Sub(MathFunctions::Mul(two, Pow(_t, three)), MathFunctions::Mul(three, Pow(_t, two))), one);
        const float128 m0c = MathFunctions::Add(MathFunctions::Sub(Pow(_t, three), MathFunctions::Mul(two, Pow(_t, two))), _t);
        const float128 p1c = MathFunctions::Add(MathFunctions::Mul(minustwo, Pow(_t, three)), MathFunctions::Mul(three, Pow(_t, two)));
        const float128 m1c = MathFunctions::Sub(Pow(_t, three), Pow(_t, two));

        const float128 p0 = MathFunctions::Mul(p0c, _p0);
        const float128 m0 = MathFunctions::Mul(m0c, _m0);
        const float128 p1 = MathFunctions::Mul(p1c, _p1);
        const float128 m1 = MathFunctions::Mul(m1c, _m1);

        const float128 add0 = MathFunctions::Add(p0, m0);
        const float128 add1 = MathFunctions::Add(p1, m1);

        const float128 add = MathFunctions::Add(add0, add1);

        return add;
    }


    // is a bit slow
    NIX_INLINE float128 InverseLerp(const float128 _v, const float128 _min, const float128 _max)
    {
        const float128 equal = _mm_cmpeq_ps(_min, _max);
        const int16 mask = _mm_movemask_ps(equal);
        if (mask == 0xffffffff)
        {
            return kZero;
        }
        else
        {
            const float128 sub0 = MathFunctions::Sub(_v, _min);
            const float128 sub1 = MathFunctions::Sub(_max, _min);
            const float128 div = MathFunctions::Div(sub0, sub1);
            return div;
        }
    }

    //////////////////////////////////////////////////////////////////////////
    // Faster helper accessor
    //////////////////////////////////////////////////////////////////////////

//     NIX_INLINE float128 InsertAt(const float128 _v, float _x, uint32 _i)
//     {
// #   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
//         //return _mm_insert_ps(_v, _mm_set_ss(_x), _i << 4);
//         return _mm_insert_ps(_v, _mm_set_ss(_x), _i);
// #   else
//         NIX_ALIGN_16 uint32 mask[4] = { 0xffffffff,0xffffffff,0xffffffff,0xffffffff };
//         float128 tmp, vec_masked, p_masked;
//         //mask[_i >> 4] = 0x0;
//         mask[_i] = 0x0;
//         vec_masked = _mm_and_ps(*(float128*)mask, _v);
//         p_masked = _mm_andnot_ps(*(float128*)mask, _mm_set_ss(_x));
//         tmp = _mm_or_ps(vec_masked, p_masked);
//         return tmp;
// #   endif
//     }

	NIX_INLINE float128 InsertOnX(const float128 _v, float _x)
	{
		float128 result = _mm_set_ss(_x);
		result = _mm_move_ss(_v, result);
		return result;
	}

	NIX_INLINE float128 InsertOnY(const float128 _v, float _y)
	{
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		float128 result = _mm_set_ss(_y);
		result = _mm_insert_ps(_v, result, 0x10);
		return result;
#   else
		float128 result = MathFunctions::Swizzle<Y, X, Z, W>(_v);
		float128 temp = _mm_set_ss(_y);
		result = _mm_move_ss(result, temp);
		result = MathFunctions::Swizzle<Y, X, Z, W>(result);
		return result;
#	endif
	}

	NIX_INLINE float128 InsertOnZ(const float128 _v, float _z)
	{
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		float128 result = _mm_set_ss(_z);
		result = _mm_insert_ps(_v, result, 0x20);
		return result;
#   else
		float128 result = MathFunctions::Swizzle<Z, Y, X, W>(_v);
		float128 temp = _mm_set_ss(_z);
		result = _mm_move_ss(result, temp);
		result = MathFunctions::Swizzle<Z, Y, X, W>(result);
		return result;
#	endif
	}

	NIX_INLINE float128 InsertOnW(const float128 _v, float _w)
	{
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		float128 result = _mm_set_ss(_w);
		result = _mm_insert_ps(_v, result, 0x30);
		return result;
#   else
		float128 result = MathFunctions::Swizzle<W, Y, Z, X>(_v);
		float128 temp = _mm_set_ss(_w);
		result = _mm_move_ss(result, temp);
		result = MathFunctions::Swizzle<W, Y, Z, X>(result);
		return result;
#	endif
	}

    NIX_INLINE float ExtractX(const float128 _v)
    {
        return _mm_cvtss_f32(_v);
    }

    NIX_INLINE float ExtractY(const float128 _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        float r;
        _MM_EXTRACT_FLOAT(r, _v, 1);
        return r;
#   else
        return _mm_cvtss_f32(MathFunctions::Swizzle<Y, Y, Y, Y>(_v));
#   endif
    }

    NIX_INLINE float ExtractZ(const float128 _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        float r;
        _MM_EXTRACT_FLOAT(r, _v, 2);
        return r;
#   else
        return _mm_cvtss_f32(MathFunctions::Swizzle<Z, Z, Z, Z>(_v));
#   endif
    }

    NIX_INLINE float ExtractW(const float128 _v)
    {
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
        float r;
        _MM_EXTRACT_FLOAT(r, _v, 3);
        return r;
#   else
        return _mm_cvtss_f32(MathFunctions::Swizzle<W, W, W, W>(_v));
#   endif
    }

	NIX_INLINE float128 Select(float128 _v1, float128 _v2, float128 _selectMask)
	{
		float128 masked1 = _mm_andnot_ps(_selectMask, _v1);
		float128 masked2 = _mm_and_ps(_selectMask, _v2);
		return _mm_or_ps(masked1, masked2);
	}

	NIX_INLINE float128 NewtonRaphsonReciprocalSquareRoot(const float128 _v)
	{
		const float128 approx = MathFunctions::ReciprocalSqrt(_v);
		const float128 muls = MathFunctions::Mul(MathFunctions::Mul(_v, approx), approx);
		return MathFunctions::Mul(MathFunctions::Mul(_mm_setr_ps(0.5f, 0.5f, 0.5f, 0.5f), approx), MathFunctions::Sub(_mm_setr_ps(3.0f, 3.0f, 3.0f, 3.0f), muls));
	}

	// https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html
	// 2x2 row major Matrix multiply A*B
	NIX_INLINE float128 Mat2Mul(float128 _v1, float128 _v2)
	{
		return MathFunctions::Add(MathFunctions::Mul(_v1, MathFunctions::Swizzle<X, W, X, W>(_v2)), MathFunctions::Mul(MathFunctions::Swizzle<Y, X, W, Z>(_v1), MathFunctions::Swizzle<Z, Y, Z, Y>(_v2)));
	}
	// https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html
	// 2x2 row major Matrix adjugate multiply (A#)*B
	NIX_INLINE float128 Mat2AdjMul(float128 _v1, float128 _v2)
	{
		return MathFunctions::Sub(MathFunctions::Mul(MathFunctions::Swizzle<W, W, X, X>(_v1), _v2), MathFunctions::Mul(MathFunctions::Swizzle<Y, Y, Z, Z>(_v1), MathFunctions::Swizzle<Z, W, X, Y>(_v2)));

	}
	// https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html
	// 2x2 row major Matrix multiply adjugate A*(B#)
	NIX_INLINE float128 Mat2MulAdj(float128 _v1, float128 _v2)
	{
		return MathFunctions::Sub(MathFunctions::Mul(_v1, MathFunctions::Swizzle<W, X, W, X>(_v2)), MathFunctions::Mul(MathFunctions::Swizzle<Y, X, W, Z>(_v1), MathFunctions::Swizzle<Z, Y, Z, Y>(_v2)));
	}

	NIX_INLINE float128 CreateXUnitVector(float128 _one = SplatOne())
	{
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		return _mm_insert_ps(_one, _one, 0x0E);
#   else
		return _mm_castsi128_ps(_mm_srli_si128(_mm_castps_si128(_one), 12));
#   endif
	}

	NIX_INLINE float128 CreateYUnitVector(float128 _one = SplatOne())
	{
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		return _mm_insert_ps(_one, _one, 0x0D);
#   else
		float128 unitx = CreateXUnitVector(_one);
		return _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(unitx), 4));
#   endif
	}

	NIX_INLINE float128 CreateZUnitVector(float128 _one = SplatOne())
	{
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		return _mm_insert_ps(_one, _one, 0x0B);
#   else
		float128 unitx = CreateXUnitVector(_one);
		return _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(unitx), 8));
#   endif
	}

	NIX_INLINE float128 CreateWUnitVector(float128 _one = SplatOne())
	{
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		return _mm_insert_ps(_one, _one, 0x07);
#   else
		return _mm_castsi128_ps(_mm_slli_si128(_mm_castps_si128(_one), 12));
#   endif
	}

	NIX_INLINE float128 SetWToZero(float128 _vec)
	{
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		return _mm_insert_ps(_vec, _vec, 0x08);
#   else
		int128 MaskOffW = _mm_srli_si128(_mm_castps_si128(_mm_cmpeq_ps(_vec, _vec)), 4);
		return _mm_and_ps(_vec, _mm_castsi128_ps(MaskOffW));
#   endif
	}

	NIX_INLINE float128 SetZWToZero(float128 _vec)
	{
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		return _mm_blend_ps(_vec, SplatZero(), 0x0C);
#   else
		int128 MaskOffW = _mm_srli_si128(_mm_castps_si128(_mm_cmpeq_ps(_vec, _vec)), 8);
		return _mm_and_ps(_vec, _mm_castsi128_ps(MaskOffW));
#   endif
	}

	NIX_INLINE float128 SetWToOne(float128 _vec)
	{
#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		return _mm_blend_ps(_vec, SplatOne(), 0x08);
#   else
		return _mm_movelh_ps(_vec, _mm_unpackhi_ps(_vec, SplatOne()));
#   endif
	}

	// From  [a,b,c,d ] To  [b,c,d,a]
	NIX_INLINE float128 Rotate(float128 _vec)
	{
		return _mm_shuffle_ps(_vec, _vec, 0x39);
	}
};


NIX_NAMESPACE_END