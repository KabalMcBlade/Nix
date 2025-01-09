// Copyright (c) 2018-2025 Michele Condo'
// File: C:\Projects\Nix\Nix\Boolean.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.


#pragma once


#include "MathAligned.h"
#include "BasicMathFunctions.h"


NIX_NAMESPACE_BEGIN

class Boolean : public MathAligned<16>
{
public:
	NIX_INLINE Boolean() = default;
	NIX_INLINE Boolean(const Boolean& _s) { m_vec = _s; }
	NIX_INLINE Boolean(bool _s) { m_vec = MathFunctions::Splat(_s); }
	NIX_INLINE explicit Boolean(float128 _s) { m_vec = _s; }

	NIX_INLINE operator float128() const { return m_vec; }

	// It works *ONLY* if all he values are the same! Useful for scalar boolean check ONLY!
	NIX_INLINE bool IsTrue() const
	{
		// 		uint16 mask = _mm_movemask_ps(m_vec);
		// 		return (mask == 0x000F);
		const int128 toInt = _mm_cvttps_epi32(m_vec);
		uint16 mask = _mm_movemask_epi8(toInt);
		return (mask > 0);
	}

	NIX_INLINE bool IsFalse() const
	{
		return !IsTrue();
	}

#ifdef _DEBUG
	NIX_INLINE void GetValues(bool _results[4])
	{
		int32 __declspec(align(16)) result[4];
		const int128 toInt = _mm_cvttps_epi32(m_vec);

		_mm_store_si128((int128*)result, toInt);

		_results[0] = result[0] < 0;
		_results[1] = result[1] < 0;
		_results[2] = result[2] < 0;
		_results[3] = result[3] < 0;
	}
#endif

private:
	float128 m_vec;
};


NIX_NAMESPACE_END