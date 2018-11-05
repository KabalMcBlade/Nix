#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Helper.h"
#include "Constants.h"
#include "Operators.h"


NIX_NAMESPACE_BEGIN


NIX_SIMD_ALIGN_16 struct Utilities
{
    // If a converted result is negative the value (0) is returned and if the
    // converted result is larger than the maximum byte the value (255) is returned.
    static NIX_INLINE nixU8 FloatToByte(nixFloat _value)
    {
        nixFloat4 x = _mm_load_ss(&_value);
        x = _mm_max_ss(x, kZero);
        x = _mm_min_ss(x, k255);
        return static_cast<nixU8>(_mm_cvttss_si32(x));
    }

    static NIX_INLINE void VectorToByte(const nixFloat& _x, const nixFloat& _y, const nixFloat& _z, nixU8* _out)
    {
        const nixFloat4 xyz = _mm_unpacklo_ps(_mm_unpacklo_ps(_mm_load_ss(&_x), _mm_load_ss(&_z)), _mm_load_ss(&_y));
        const nixFloat4 xyzScaled = Helper::MulAdd(Helper::Add(xyz, kOne), k255Over2, kHalf);
        const nixInt4 xyzInt = _mm_cvtps_epi32(xyzScaled);
        const nixInt4 xyzShort = _mm_packs_epi32(xyzInt, xyzInt);
        const nixInt4 xyzChar = _mm_packus_epi16(xyzShort, xyzShort);
        const nixInt4 xyz16 = _mm_unpacklo_epi8(xyzChar, _mm_setzero_si128());

        _out[0] = (nixU8)_mm_extract_epi16(xyz16, 0);    // cannot use _mm_extract_epi8 because it is an SSE4 instruction
        _out[1] = (nixU8)_mm_extract_epi16(xyz16, 1);
        _out[2] = (nixU8)_mm_extract_epi16(xyz16, 2);
    }

    static NIX_INLINE void VectorToByte(const nixFloat& _x, const nixFloat& _y, const nixFloat& _z, const nixFloat& _w, nixU8* _out)
    {
        const nixFloat4 xyzw = Helper::Set(_x, _y, _z, _w);
        const nixFloat4 xyzwScaled = Helper::MulAdd(Helper::Add(xyzw, kOne), k255Over2, kHalf);
        const nixInt4 xyzwInt = _mm_cvtps_epi32(xyzwScaled);
        const nixInt4 xyzwShort = _mm_packs_epi32(xyzwInt, xyzwInt);
        const nixInt4 xyzwChar = _mm_packus_epi16(xyzwShort, xyzwShort);
        const nixInt4 xyzw16 = _mm_unpacklo_epi8(xyzwChar, _mm_setzero_si128());

        _out[0] = (nixU8)_mm_extract_epi16(xyzw16, 0);    // cannot use _mm_extract_epi8 because it is an SSE4 instruction
        _out[1] = (nixU8)_mm_extract_epi16(xyzw16, 1);
        _out[2] = (nixU8)_mm_extract_epi16(xyzw16, 2);
        _out[3] = (nixU8)_mm_extract_epi16(xyzw16, 3);
    }

    static NIX_INLINE void VectorToByte(const nixFloat4& _v, nixU8* _out)
    {
        const nixFloat4 xyzScaled = Helper::MulAdd(Helper::Add(_v, kOne), k255Over2, kHalf);
        const nixInt4 xyzInt = _mm_cvtps_epi32(xyzScaled);
        const nixInt4 xyzShort = _mm_packs_epi32(xyzInt, xyzInt);
        const nixInt4 xyzChar = _mm_packus_epi16(xyzShort, xyzShort);
        const nixInt4 xyz16 = _mm_unpacklo_epi8(xyzChar, _mm_setzero_si128());

        _out[0] = (nixU8)_mm_extract_epi16(xyz16, 0);    // cannot use _mm_extract_epi8 because it is an SSE4 instruction
        _out[1] = (nixU8)_mm_extract_epi16(xyz16, 1);
        _out[2] = (nixU8)_mm_extract_epi16(xyz16, 2);
    }
};

NIX_NAMESPACE_END
