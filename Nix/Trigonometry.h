#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"


#define USE_SSE2
#include "Dependencies/sse_mathfun.h"


NIX_NAMESPACE_BEGIN


namespace Trigonometry
{
    NIX_INLINE float128 Cos(const float128& _x)
    {
        return cos_ps(_x);
    }

    NIX_INLINE float128 Sin(const float128& _x)
    {
        return sin_ps(_x);
    }

    NIX_INLINE float128 Exp(const float128& _x)
    {
        return exp_ps(_x);
    }

    NIX_INLINE float128 Log(const float128& _x)
    {
        return log_ps(_x);
    }
    
    NIX_INLINE void SinCos(const float128& _x, float128* _sin, float128* _cos)
    {
        return sincos_ps(_x, _sin, _cos);
    }
};

NIX_NAMESPACE_END
