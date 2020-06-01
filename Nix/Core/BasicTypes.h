#pragma once

#include <cstddef>	// for size_t
#include <cstdint>	// for everything else

#include <stdint.h>     // for u8, etc...
#include <math.h>

#include <cmath>
#include <limits>
#include <utility>      // for move, etc...

#ifdef _DEBUG
#include <iostream>
#endif

#include "BasicDefines.h"

NIX_NAMESPACE_BEGIN


#ifdef max
#undef max
#endif //

#ifdef min
#undef min
#endif //


#define NIX_MATH_CONST extern const __declspec(selectany)


typedef std::int8_t     int8;
typedef std::int16_t    int16;
typedef std::int32_t    int32;
typedef std::int64_t    int64;

typedef std::uint8_t    uint8;
typedef std::uint16_t   uint16;
typedef std::uint32_t   uint32;
typedef std::uint64_t   uint64;

typedef std::size_t     size;

typedef std::intptr_t   intPtr;
typedef std::uintptr_t  uintPtr;



/*
// perhaps debug purpose for instance?
struct __float128
{
	union
	{
		float   m_f32[4];
		uint32  m_u32[4];
	};
};
*/

// for debug purpose?
// typedef __float128 float128;
typedef __m128 float128;
typedef __m128i int128;
typedef __m128d double128;


NIX_NAMESPACE_END