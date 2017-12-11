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


NIX_SIMD_ALIGN class MathHelper
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
