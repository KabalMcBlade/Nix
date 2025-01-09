// Copyright (c) 2018-2025 Michele Condo'
// File: C:\Projects\Nix\Nix\Swizzle.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.


#pragma once

#include "Core/BasicDefines.h"

#if NIX_ARCH & NIX_ARCH_AVX_FLAG
#define NIX_SHUFFLE_PS( v, c ) _mm_permute_ps((v), c )
#else
#define NIX_SHUFFLE_PS( v, c ) _mm_shuffle_ps((v), (v), c )
#endif


NIX_NAMESPACE_BEGIN



enum ESwizzle : uint32
{
	X = 0,
	Y = 1,
	Z = 2,
	W = 3
};

namespace MathFunctions
{
	template<ESwizzle _X, ESwizzle _Y, ESwizzle _Z, ESwizzle _W>
	static NIX_INLINE float128 Swizzle(float128 _v)
	{
		static_assert(_X <= 3, "X parameter out of range (0 to 3)");
		static_assert(_Y <= 3, "Y parameter out of range (0 to 3)");
		static_assert(_Z <= 3, "Z parameter out of range (0 to 3)");
		static_assert(_W <= 3, "W parameter out of range (0 to 3)");

		return NIX_SHUFFLE_PS(_v, _MM_SHUFFLE(_W, _Z, _Y, _X));
	}
}


NIX_NAMESPACE_END