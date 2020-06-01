#pragma once


#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "Helper.h"
#include "Constants.h"


NIX_NAMESPACE_BEGIN


namespace Utilities
{
    // If a converted result is negative the value (0) is returned and if the
    // converted result is larger than the maximum byte the value (255) is returned.
    NIX_INLINE uint8 FloatToByte(float _value)
    {
        float128 x = _mm_load_ss(&_value);
        x = _mm_max_ss(x, kZero);
        x = _mm_min_ss(x, k255Vec4);
        return static_cast<uint8>(_mm_cvttss_si32(x));
    }

    NIX_INLINE void VectorToByte(const float& _x, const float& _y, const float& _z, uint8* _out)
    {
        const float128 xyz = _mm_unpacklo_ps(_mm_unpacklo_ps(_mm_load_ss(&_x), _mm_load_ss(&_z)), _mm_load_ss(&_y));
        const float128 xyzScaled = Helper::MulAdd(Helper::Add(xyz, kOneVec4), k255Over2Vec4, kOneHalfVec4);
        const int128 xyzInt = _mm_cvtps_epi32(xyzScaled);
        const int128 xyzShort = _mm_packs_epi32(xyzInt, xyzInt);
        const int128 xyzChar = _mm_packus_epi16(xyzShort, xyzShort);
        const int128 xyz16 = _mm_unpacklo_epi8(xyzChar, _mm_setzero_si128());

        _out[0] = (uint8)_mm_extract_epi16(xyz16, 0);    // cannot use _mm_extract_epi8 because it is an SSE4 instruction
        _out[1] = (uint8)_mm_extract_epi16(xyz16, 1);
        _out[2] = (uint8)_mm_extract_epi16(xyz16, 2);
    }

    NIX_INLINE void VectorToByte(const float& _x, const float& _y, const float& _z, const float& _w, uint8* _out)
    {
        const float128 xyzw = Helper::Set(_x, _y, _z, _w);
        const float128 xyzwScaled = Helper::MulAdd(Helper::Add(xyzw, kOneVec4), k255Over2Vec4, kOneHalfVec4);
        const int128 xyzwInt = _mm_cvtps_epi32(xyzwScaled);
        const int128 xyzwShort = _mm_packs_epi32(xyzwInt, xyzwInt);
        const int128 xyzwChar = _mm_packus_epi16(xyzwShort, xyzwShort);
        const int128 xyzw16 = _mm_unpacklo_epi8(xyzwChar, _mm_setzero_si128());

        _out[0] = (uint8)_mm_extract_epi16(xyzw16, 0);    // cannot use _mm_extract_epi8 because it is an SSE4 instruction
        _out[1] = (uint8)_mm_extract_epi16(xyzw16, 1);
        _out[2] = (uint8)_mm_extract_epi16(xyzw16, 2);
        _out[3] = (uint8)_mm_extract_epi16(xyzw16, 3);
    }

    NIX_INLINE void VectorToByte(const float128& _v, uint8* _out)
    {
        const float128 xyzScaled = Helper::MulAdd(Helper::Add(_v, kOneVec4), k255Over2Vec4, kOneHalfVec4);
        const int128 xyzInt = _mm_cvtps_epi32(xyzScaled);
        const int128 xyzShort = _mm_packs_epi32(xyzInt, xyzInt);
        const int128 xyzChar = _mm_packus_epi16(xyzShort, xyzShort);
        const int128 xyz16 = _mm_unpacklo_epi8(xyzChar, _mm_setzero_si128());

        _out[0] = (uint8)_mm_extract_epi16(xyz16, 0);    // cannot use _mm_extract_epi8 because it is an SSE4 instruction
        _out[1] = (uint8)_mm_extract_epi16(xyz16, 1);
        _out[2] = (uint8)_mm_extract_epi16(xyz16, 2);
    }
};

NIX_NAMESPACE_END
