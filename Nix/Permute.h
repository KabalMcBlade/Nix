// Copyright (c) 2018-2025 Michele Condo'
// File: C:\Projects\Nix\Nix\Permute.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.


#pragma once

#include "Swizzle.h"
#include "Conversion.h"
#include "BasicMathFunctions.h"


NIX_NAMESPACE_BEGIN


enum EPermute : uint32
{
	A_X = 0,
	A_Y = 1,
	A_Z = 2,
	A_W = 3,
	B_X = 4,
	B_Y = 5,
	B_Z = 6,
	B_W = 7
};


namespace MathFunctions
{
	template<EPermute _X, EPermute _Y, EPermute _Z, EPermute _W>
	static NIX_INLINE float128 Permute(float128 _a, float128 _b)
	{
		static_assert(_X <= 7, "X parameter out of range (0 to 7)");
		static_assert(_Y <= 7, "Y parameter out of range (0 to 7)");
		static_assert(_Z <= 7, "Z parameter out of range (0 to 7)");
		static_assert(_W <= 7, "W parameter out of range (0 to 7)");

		constexpr uint32 shuffle = _MM_SHUFFLE(_W & 3, _Z & 3, _Y & 3, _X & 3);

		static const UInt128 selectMask =
		{ { {
				_X > 3 ? 0xFFFFFFFF : 0,
				_Y > 3 ? 0xFFFFFFFF : 0,
				_Z > 3 ? 0xFFFFFFFF : 0,
				_W > 3 ? 0xFFFFFFFF : 0,
		} } };

		float128 shuffled1 = NIX_SHUFFLE_PS(_a, shuffle);
		float128 shuffled2 = NIX_SHUFFLE_PS(_b, shuffle);

		//return MathFunctions::Select(shuffled1, shuffled2, selectMask);
		return MathFunctions::Select(shuffled1, shuffled2, selectMask);
	}

	template<>
	static NIX_INLINE float128 Permute<A_X, B_X, A_Y, B_Y>(float128 _a, float128 _b)
	{
		return _mm_unpacklo_ps(_a, _b);
	}

	template<>
	static NIX_INLINE float128 Permute<A_Z, B_Z, A_W, B_W>(float128 _a, float128 _b)
	{
		return _mm_unpackhi_ps(_a, _b);
	}

	template<>
	static NIX_INLINE float128 Permute<A_X, A_Y, B_X, B_Y>(float128 _a, float128 _b)
	{
		return _mm_movelh_ps(_a, _b);
	}

	template<>
	static NIX_INLINE float128 Permute<A_Z, A_W, B_Z, B_W>(float128 _a, float128 _b)
	{
		return _mm_movehl_ps(_a, _b);
	}
}

NIX_NAMESPACE_END