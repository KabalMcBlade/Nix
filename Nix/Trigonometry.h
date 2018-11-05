#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Constants.h"
#include "Operators.h"

#define USE_SSE2
#include "sse_mathfun.h"


NIX_NAMESPACE_BEGIN


NIX_SIMD_ALIGN_16 struct Trigonometry
{
    static NIX_INLINE nixFloat4 Cos(const nixFloat4& _x)
    {
        return cos_ps(_x);
    }

    static NIX_INLINE nixFloat4 Sin(const nixFloat4& _x)
    {
        return sin_ps(_x);
    }

    static NIX_INLINE nixFloat4 Exp(const nixFloat4& _x)
    {
        return exp_ps(_x);
    }

    static NIX_INLINE nixFloat4 Log(const nixFloat4& _x)
    {
        return log_ps(_x);
    }
    
    static NIX_INLINE void SinCos(const nixFloat4& _x, nixFloat4* _sin, nixFloat4* _cos)
    {
        return sincos_ps(_x, _sin, _cos);
    }
    
    static NIX_INLINE nixFloat4 Tan(const nixFloat4& _x)
    {
        const nixFloat4 signs(kSignBit), ones(kOne), signsres(_x & signs), fopi(kOrbitalPI), tanp1(kTanCP1), tanp2(kTanCP2), tanp3(kTanCP3), tanp4(kTanCP4), tanp5(kTanCP5);
        const nixInt4 iones(kOne), ionesn(kOneNeg), twos(kTwo), nzeros(kZero);

        nixFloat4 ax(abs(_x));
        // store the integer part of y in mm0 
        nixInt4 emm2 = (_mm_cvttps_epi32(ax * fopi) + iones) & ionesn;
        nixFloat4 y = _mm_cvtepi32_ps(emm2);
        emm2 = cmpeq(emm2 & twos, nzeros);
        const nixFloat4 polymsk(_mm_castsi128_ps(emm2)), polymskn(~polymsk);

        nixFloat4 z = ((ax + y * nixFloat4(kNegDP1)) + y * nixFloat4(kNegDP2)) + y * nixFloat4(kNegDP3), zz(z * z), poly(kTanCP0);
        poly = poly * zz + tanp1;
        poly = poly * zz + tanp2;
        poly = poly * zz + tanp3;
        poly = poly * zz + tanp4;
        poly = poly * zz + tanp5;
        poly = poly * zz * z + z;

        nixFloat4 polyinv = ones / poly;
        poly = (poly & polymsk) | (-polyinv & polymskn);
        return poly ^ signsres;
    }
    
    static NIX_INLINE nixFloat4 ATan(const nixFloat4& _x)
    {
        const nixFloat4 signsn(kNegSignBit), signs(kSignBit), ones(kOne), atanhi(kTanHI), atanlo(kTanLO), pih(kHalfPI), piq(kQuartPI), atanp0(kTanP0), atanp1(kTanP1), atanp2(kTanP2), atanp3(kTanP3);
        nixFloat4 ax = abs(_x), r = ax - ones, r0 = _mm_rcp_ps(ax + ones), r1 = -_mm_rcp_ps(ax);
        nixFloat4 cmp0 = cmpgt(ax, atanhi), cmp1 = cmpgt(ax, atanlo), cmp2 = ~cmp0 & cmp1, cmp = cmp0 | cmp1;
        nixFloat4 x2 = (cmp2 & (r * r0)) | (cmp0 & r1);
        ax = (cmp & x2) | (~cmp & ax);

        nixFloat4 zz = ax * ax, acc = atanp0;
        acc = acc * zz - atanp1;
        acc = acc * zz + atanp2;
        acc = acc * zz - atanp3;
        acc = acc * zz * ax + ax + ((cmp0 & pih) | (cmp2 & piq));
        return acc ^ (_x & signs);
    }

    static NIX_INLINE nixFloat4 ATan2(const nixFloat4& _x, const nixFloat4& _y)
    {
        const nixFloat4 zeros(kZero), signs(kSignBit), pi(kPI), pih(kHalfPI);
        nixFloat4 xeq = cmpeq(_x, zeros), xgt = cmpgt(_x, zeros), xle = cmple(_x, zeros), xlt = cmplt(_x, zeros), yeq = cmpeq(_y, zeros), ylt = cmplt(_y, zeros);
        nixFloat4 zero_mask = (xeq & yeq) | (xgt & yeq), pio2_mask = ~yeq &  xeq;
        nixFloat4 pio2_result = (pih ^ (ylt & signs)) & pio2_mask;
        nixFloat4 atan_result = ATan(_y / _x) + (xlt & (pi ^ (xlt & ylt & signs)));

        return (~zero_mask & pio2_result) | (~pio2_mask & atan_result) | (pi & xle & yeq);
    }
};

NIX_NAMESPACE_END
