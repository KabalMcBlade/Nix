#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "Constants.h"
#include "Operators.h"

#define USE_SSE2
#include "Dependencies/sse_mathfun.h"


NIX_NAMESPACE_BEGIN


NIX_ALIGN_16 struct Trigonometry
{
    static NIX_INLINE float128 Cos(const float128& _x)
    {
        return cos_ps(_x);
    }

    static NIX_INLINE float128 Sin(const float128& _x)
    {
        return sin_ps(_x);
    }

    static NIX_INLINE float128 Exp(const float128& _x)
    {
        return exp_ps(_x);
    }

    static NIX_INLINE float128 Log(const float128& _x)
    {
        return log_ps(_x);
    }
    
    static NIX_INLINE void SinCos(const float128& _x, float128* _sin, float128* _cos)
    {
        return sincos_ps(_x, _sin, _cos);
    }
    
    static NIX_INLINE float128 Tan(const float128& _x)
    {
        const float128 signs(kSignBit), ones(kOne), signsres(_x & signs), fopi(kOrbitalPI), tanp1(kTanCP1), tanp2(kTanCP2), tanp3(kTanCP3), tanp4(kTanCP4), tanp5(kTanCP5);
        const int128 iones(kOne), ionesn(kOneNeg), twos(kTwo), nzeros(kZero);

        float128 ax(abs(_x));
        // store the integer part of y in mm0 
        int128 emm2 = (_mm_cvttps_epi32(ax * fopi) + iones) & ionesn;
        float128 y = _mm_cvtepi32_ps(emm2);
        emm2 = cmpeq(emm2 & twos, nzeros);
        const float128 polymsk(_mm_castsi128_ps(emm2)), polymskn(~polymsk);

        float128 z = ((ax + y * float128(kNegDP1)) + y * float128(kNegDP2)) + y * float128(kNegDP3), zz(z * z), poly(kTanCP0);
        poly = poly * zz + tanp1;
        poly = poly * zz + tanp2;
        poly = poly * zz + tanp3;
        poly = poly * zz + tanp4;
        poly = poly * zz + tanp5;
        poly = poly * zz * z + z;

        float128 polyinv = ones / poly;
        poly = (poly & polymsk) | (-polyinv & polymskn);
        return poly ^ signsres;
    }
    
    static NIX_INLINE float128 ATan(const float128& _x)
    {
        const float128 signsn(kNegSignBit), signs(kSignBit), ones(kOne), atanhi(kTanHI), atanlo(kTanLO), pih(kHalfPI), piq(kQuartPI), atanp0(kTanP0), atanp1(kTanP1), atanp2(kTanP2), atanp3(kTanP3);
        float128 ax = abs(_x), r = ax - ones, r0 = _mm_rcp_ps(ax + ones), r1 = -_mm_rcp_ps(ax);
        float128 cmp0 = cmpgt(ax, atanhi), cmp1 = cmpgt(ax, atanlo), cmp2 = ~cmp0 & cmp1, cmp = cmp0 | cmp1;
        float128 x2 = (cmp2 & (r * r0)) | (cmp0 & r1);
        ax = (cmp & x2) | (~cmp & ax);

        float128 zz = ax * ax, acc = atanp0;
        acc = acc * zz - atanp1;
        acc = acc * zz + atanp2;
        acc = acc * zz - atanp3;
        acc = acc * zz * ax + ax + ((cmp0 & pih) | (cmp2 & piq));
        return acc ^ (_x & signs);
    }

    static NIX_INLINE float128 ATan2(const float128& _x, const float128& _y)
    {
        const float128 zeros(kZero), signs(kSignBit), pi(kPI), pih(kHalfPI);
        float128 xeq = cmpeq(_x, zeros), xgt = cmpgt(_x, zeros), xle = cmple(_x, zeros), xlt = cmplt(_x, zeros), yeq = cmpeq(_y, zeros), ylt = cmplt(_y, zeros);
        float128 zero_mask = (xeq & yeq) | (xgt & yeq), pio2_mask = ~yeq &  xeq;
        float128 pio2_result = (pih ^ (ylt & signs)) & pio2_mask;
        float128 atan_result = ATan(_y / _x) + (xlt & (pi ^ (xlt & ylt & signs)));

        return (~zero_mask & pio2_result) | (~pio2_mask & atan_result) | (pi & xle & yeq);
    }
};

NIX_NAMESPACE_END
