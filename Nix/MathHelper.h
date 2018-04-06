#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"
#include "VectorHelper.h"




#define NIX_VALUE_DEGTORAD   0.017453292519943295769236907684886f    // Degrees to Radians (PI/180)
#define NIX_VALUE_RADTODEG   57.295779513082320876798154814105f      // Radians to Degrees (180/PI)
#define NIX_DEG_TO_RAD(x)      (x * NIX_VALUE_DEGTORAD)
#define NIX_RAD_TO_DEG(x)      (x * NIX_VALUE_RADTODEG)

NIX_NAMESPACE_BEGIN


NIX_SIMD_ALIGN_16 class MathHelper
{
public:
    constexpr static const nixFloat kPI = 3.141593f;
    constexpr static const nixFloat kInv2PI = 0.1591549f;
    constexpr static const nixFloat k2PI = 6.283185f;
    constexpr static const nixFloat kHalfPI = 1.570796f;
    constexpr static const nixFloat k3halfPI = 4.7123889f;

    constexpr static const nixFloat kEpsilon = std::numeric_limits<nixFloat>::epsilon();

public:
    static NIX_INLINE __nixFloat4 Cos(__nixFloat4 _angle)
    {
        __nixFloat4 flr = VectorHelper::Floor(VectorHelper::Mul(_angle, VectorHelper::Splat(kInv2PI)));
        _angle = VectorHelper::Sub(_angle, VectorHelper::Mul(flr, VectorHelper::Splat(k2PI)));

        _angle = VectorHelper::Abs(_angle);

        __nixFloat4 cosangle = _angle;
        cosangle = _mm_xor_ps(cosangle, _mm_and_ps(_mm_cmpge_ps(_angle, VectorHelper::Splat(kHalfPI)), _mm_xor_ps(cosangle, VectorHelper::Sub(VectorHelper::Splat(kPI), _angle))));
        cosangle = _mm_xor_ps(cosangle, _mm_and_ps(_mm_cmpge_ps(_angle, VectorHelper::Splat(kPI)), VectorHelper::GetSignMask()));
        cosangle = _mm_xor_ps(cosangle, _mm_and_ps(_mm_cmpge_ps(_angle, VectorHelper::Splat(k3halfPI)), _mm_xor_ps(cosangle, VectorHelper::Sub(VectorHelper::Splat(k2PI), _angle))));

        __nixFloat4 result = MathHelper::Cos52s(cosangle);

        result = _mm_xor_ps(result, _mm_and_ps(_mm_and_ps(_mm_cmpge_ps(_angle, VectorHelper::Splat(kHalfPI)), _mm_cmplt_ps(_angle, VectorHelper::Splat(k3halfPI))), VectorHelper::GetSignMask()));

        return result;
    }

    static NIX_INLINE __nixFloat4 Sin(__nixFloat4 _angle)
    {
        return MathHelper::Cos(VectorHelper::Sub(VectorHelper::Splat(kHalfPI), _angle));
    }
    
    static NIX_INLINE void SinCos(__nixFloat4 _angle, __nixFloat4* _sin, __nixFloat4* _cos)
    {
        *_cos = Cos(_angle);

        __nixFloat4 flr = VectorHelper::Floor(VectorHelper::Mul(_angle, VectorHelper::Splat(kInv2PI)));
        _angle = VectorHelper::Sub(_angle, VectorHelper::Mul(flr, VectorHelper::Splat(k2PI)));

        __nixFloat4 sinmultiplier = _mm_xor_ps(VectorHelper::GetOne(), _mm_and_ps(_mm_cmplt_ps(_angle, VectorHelper::GetZero()), _mm_and_ps(_mm_cmpge_ps(_angle, VectorHelper::Splat(-kPI)), VectorHelper::GetSignMask())));
        *_sin = VectorHelper::Mul(sinmultiplier, VectorHelper::Sqrt(VectorHelper::Sub(VectorHelper::GetOne(), VectorHelper::Mul(*_cos, *_cos))));
    }
    
    // If a converted result is negative the value (0) is returned and if the
    // converted result is larger than the maximum byte the value (255) is returned.
    static NIX_INLINE nixU8 FloatToByte(nixFloat _value)
    {
        __nixFloat4 x = _mm_load_ss(&_value);
        x = _mm_max_ss(x, VectorHelper::GetZero());
        x = _mm_min_ss(x, VectorHelper::Get255());
        return static_cast<nixU8>(_mm_cvttss_si32(x));
    }

    static NIX_INLINE void VectorToByte(const nixFloat& _x, const nixFloat& _y, const nixFloat& _z, nixU8* _out) 
    {
        const __nixFloat4 xyz = _mm_unpacklo_ps(_mm_unpacklo_ps(_mm_load_ss(&_x), _mm_load_ss(&_z)), _mm_load_ss(&_y));
        const __nixFloat4 xyzScaled = VectorHelper::MulAdd(_mm_add_ps(xyz, VectorHelper::GetOne()), VectorHelper::Get255Over2(), VectorHelper::GetHalf());
        const __nixInt4 xyzInt = _mm_cvtps_epi32(xyzScaled);
        const __nixInt4 xyzShort = _mm_packs_epi32(xyzInt, xyzInt);
        const __nixInt4 xyzChar = _mm_packus_epi16(xyzShort, xyzShort);
        const __nixInt4 xyz16 = _mm_unpacklo_epi8(xyzChar, _mm_setzero_si128());

        _out[0] = (nixU8)_mm_extract_epi16(xyz16, 0);	// cannot use _mm_extract_epi8 because it is an SSE4 instruction
        _out[1] = (nixU8)_mm_extract_epi16(xyz16, 1);
        _out[2] = (nixU8)_mm_extract_epi16(xyz16, 2);
    }

    static NIX_INLINE void VectorToByte(const nixFloat& _x, const nixFloat& _y, const nixFloat& _z, const nixFloat& _w, nixU8* _out)
    {
        const __nixFloat4 xyzw = VectorHelper::Set(_x, _y, _z, _w);
        const __nixFloat4 xyzwScaled = VectorHelper::MulAdd(_mm_add_ps(xyzw, VectorHelper::GetOne()), VectorHelper::Get255Over2(), VectorHelper::GetHalf());
        const __nixInt4 xyzwInt = _mm_cvtps_epi32(xyzwScaled);
        const __nixInt4 xyzwShort = _mm_packs_epi32(xyzwInt, xyzwInt);
        const __nixInt4 xyzwChar = _mm_packus_epi16(xyzwShort, xyzwShort);
        const __nixInt4 xyzw16 = _mm_unpacklo_epi8(xyzwChar, _mm_setzero_si128());

        _out[0] = (nixU8)_mm_extract_epi16(xyzw16, 0);	// cannot use _mm_extract_epi8 because it is an SSE4 instruction
        _out[1] = (nixU8)_mm_extract_epi16(xyzw16, 1);
        _out[2] = (nixU8)_mm_extract_epi16(xyzw16, 2);
        _out[3] = (nixU8)_mm_extract_epi16(xyzw16, 3);
    }

    static NIX_INLINE void VectorToByte(const __nixFloat4& _v, nixU8* _out)
    {
        const __nixFloat4 xyzScaled = VectorHelper::MulAdd(_mm_add_ps(_v, VectorHelper::GetOne()), VectorHelper::Get255Over2(), VectorHelper::GetHalf());
        const __nixInt4 xyzInt = _mm_cvtps_epi32(xyzScaled);
        const __nixInt4 xyzShort = _mm_packs_epi32(xyzInt, xyzInt);
        const __nixInt4 xyzChar = _mm_packus_epi16(xyzShort, xyzShort);
        const __nixInt4 xyz16 = _mm_unpacklo_epi8(xyzChar, _mm_setzero_si128());

        _out[0] = (nixU8)_mm_extract_epi16(xyz16, 0);	// cannot use _mm_extract_epi8 because it is an SSE4 instruction
        _out[1] = (nixU8)_mm_extract_epi16(xyz16, 1);
        _out[2] = (nixU8)_mm_extract_epi16(xyz16, 2);
    }

private:

    // Look at: http://www.ganssle.com/approx.htm for more details
    static NIX_INLINE __nixFloat4 Cos52s(const __nixFloat4& _v)
    {
        const __nixFloat4 c1 = VectorHelper::Splat(0.9999932946f);
        const __nixFloat4 c2 = VectorHelper::Splat(-0.4999124376f);
        const __nixFloat4 c3 = VectorHelper::Splat(0.0414877472f);
        const __nixFloat4 c4 = VectorHelper::Splat(-0.0012712095f);
        const __nixFloat4 x = VectorHelper::Mul(_v, _v);
        return VectorHelper::Add(c1, VectorHelper::Mul(x, VectorHelper::Add(c2, VectorHelper::Mul(x, VectorHelper::Add(c3, VectorHelper::Mul(c4, x))))));
    }
};

NIX_NAMESPACE_END
