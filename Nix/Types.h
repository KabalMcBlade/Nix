#pragma once

#include "CoreDefs.h"
#include "Architecture.h"


NIX_NAMESPACE_BEGIN


//////////////////////////////////////////////////////////////////////////
#if defined(NIX_ARCH_AVX512)
    typedef __m512  __nixFloat16;
    typedef __m512i __nixInt16;
    typedef __m256  __nixFloat8;
    typedef __m256i __nixInt8;
    typedef __m128  __nixFloat4;
    typedef __m128i __nixInt4;
#elif defined(NIX_ARCH_AVX2) || defined(NIX_ARCH_AVX)
    typedef __m256  __nixFloat8;
    typedef __m256i __nixInt8;
    typedef __m128  __nixFloat4;
    typedef __m128i __nixInt4;
#else   // any other SSE type have only 128 bit register (I don't care about 64 bit register)
    typedef __m128  __nixFloat4;
    typedef __m128i __nixInt4;
#endif


NIX_NAMESPACE_END