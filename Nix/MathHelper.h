#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"
#include "VectorHelper.h"

#include "Operators.h"


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
    static NIX_INLINE __nixFloat4 Cos(const __nixFloat4& _x)
    {
        return cos_ps(_x);
    }

    static NIX_INLINE __nixFloat4 Sin(const __nixFloat4& _x)
    {
        return sin_ps(_x);
    }

    static NIX_INLINE __nixFloat4 Exp(const __nixFloat4& _x)
    {
        return exp_ps(_x);
    }

    static NIX_INLINE __nixFloat4 Log(const __nixFloat4& _x)
    {
        return log_ps(_x);
    }
    
    static NIX_INLINE void SinCos(const __nixFloat4& _x, __nixFloat4* _sin, __nixFloat4* _cos)
    {
        return sincos_ps(_x, _sin, _cos);
    }
    
    static NIX_INLINE __nixFloat4 Tan(const __nixFloat4& _x)
    {
        const __nixFloat4 signs(VectorHelper::GetSignMask()), ones(VectorHelper::GetOne()), signsres(_x & signs), fopi(VectorHelper::GetOPI()), tanp1(VectorHelper::GetTanCP1()), tanp2(VectorHelper::GetTanCP2()), tanp3(VectorHelper::GetTanCP3()), tanp4(VectorHelper::GetTanCP4()), tanp5(VectorHelper::GetTanCP5());
        const __nixInt4 iones(VectorHelper::GetOneI()), ionesn(VectorHelper::GetOneNegI()), twos(VectorHelper::GetTwoI()), nzeros(VectorHelper::GetZeroI());

        __nixFloat4 ax(abs(_x));
        // store the integer part of y in mm0 
        __nixInt4 emm2 = (_mm_cvttps_epi32(ax * fopi) + iones) & ionesn;
        __nixFloat4 y = _mm_cvtepi32_ps(emm2);
        emm2 = cmpeq(emm2 & twos, nzeros);
        const __nixFloat4 polymsk(_mm_castsi128_ps(emm2)), polymskn(~polymsk);

        __nixFloat4 z = ((ax + y * __nixFloat4(VectorHelper::GetNegDP1())) + y * __nixFloat4(VectorHelper::GetNegDP2())) + y * __nixFloat4(VectorHelper::GetNegDP3()), zz(z * z), poly(VectorHelper::GetTanCP0());
        poly = poly * zz + tanp1;
        poly = poly * zz + tanp2;
        poly = poly * zz + tanp3;
        poly = poly * zz + tanp4;
        poly = poly * zz + tanp5;
        poly = poly * zz * z + z;

        __nixFloat4 polyinv = ones / poly;
        poly = (poly & polymsk) | (-polyinv & polymskn);
        return poly ^ signsres;
    }
    
    static NIX_INLINE __nixFloat4 ATan(const __nixFloat4& _x)
    {
        const __nixFloat4 signsn(VectorHelper::GetSignMaskNeg()), signs(VectorHelper::GetSignMask()), ones(VectorHelper::GetOne()), atanhi(VectorHelper::GetTanHI()), atanlo(VectorHelper::GetTanLO()), pih(VectorHelper::GetPIH()), piq(VectorHelper::GetPIQ()), atanp0(VectorHelper::GetTanP0()), atanp1(VectorHelper::GetTanP1()), atanp2(VectorHelper::GetTanP2()), atanp3(VectorHelper::GetTanP3());
        __nixFloat4 ax = abs(_x), r = ax - ones, r0 = _mm_rcp_ps(ax + ones), r1 = -_mm_rcp_ps(ax);
        __nixFloat4 cmp0 = cmpgt(ax, atanhi), cmp1 = cmpgt(ax, atanlo), cmp2 = ~cmp0 & cmp1, cmp = cmp0 | cmp1;
        __nixFloat4 x2 = (cmp2 & (r * r0)) | (cmp0 & r1);
        ax = (cmp & x2) | (~cmp & ax);

        __nixFloat4 zz = ax * ax, acc = atanp0;
        acc = acc * zz - atanp1;
        acc = acc * zz + atanp2;
        acc = acc * zz - atanp3;
        acc = acc * zz * ax + ax + ((cmp0 & pih) | (cmp2 & piq));
        return acc ^ (_x & signs);
    }

    static NIX_INLINE __nixFloat4 ATan2(const __nixFloat4& _x, const __nixFloat4& _y)
    {
        const __nixFloat4 zeros(VectorHelper::GetZero()), signs(VectorHelper::GetSignMask()), pi(VectorHelper::GetPIF()), pih(VectorHelper::GetPIH());
        __nixFloat4 xeq = cmpeq(_x, zeros), xgt = cmpgt(_x, zeros), xle = cmple(_x, zeros), xlt = cmplt(_x, zeros), yeq = cmpeq(_y, zeros), ylt = cmplt(_y, zeros);
        __nixFloat4 zero_mask = (xeq & yeq) | (xgt & yeq), pio2_mask = ~yeq &  xeq;
        __nixFloat4 pio2_result = (pih ^ (ylt & signs)) & pio2_mask;
        __nixFloat4 atan_result = ATan(_y / _x) + (xlt & (pi ^ (xlt & ylt & signs)));

        return (~zero_mask & pio2_result) | (~pio2_mask & atan_result) | (pi & xle & yeq);
    }
    
    //////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////

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

        _out[0] = (nixU8)_mm_extract_epi16(xyz16, 0);    // cannot use _mm_extract_epi8 because it is an SSE4 instruction
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

        _out[0] = (nixU8)_mm_extract_epi16(xyzw16, 0);    // cannot use _mm_extract_epi8 because it is an SSE4 instruction
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

        _out[0] = (nixU8)_mm_extract_epi16(xyz16, 0);    // cannot use _mm_extract_epi8 because it is an SSE4 instruction
        _out[1] = (nixU8)_mm_extract_epi16(xyz16, 1);
        _out[2] = (nixU8)_mm_extract_epi16(xyz16, 2);
    }
};

NIX_NAMESPACE_END
