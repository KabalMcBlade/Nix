#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"


NIX_NAMESPACE_BEGIN


NIX_ALIGN_16 struct Float128
{
	union
	{
		float m_floats[4];
		float128 m_vector;
	};

	NIX_INLINE operator float128() const { return m_vector; }
	NIX_INLINE operator const float* () const { return m_floats; }
};


NIX_ALIGN_16 struct UInt128
{
	union
	{
		uint32 m_uint[4];
		float128 m_vector;
	};

	NIX_INLINE operator float128() const { return m_vector; }
	NIX_INLINE operator int128() const { return _mm_castps_si128(m_vector); }
	NIX_INLINE operator double128() const { return _mm_castps_pd(m_vector); }
};


NIX_NAMESPACE_END
