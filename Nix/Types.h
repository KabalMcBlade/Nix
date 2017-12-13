#pragma once

#include "CoreDefs.h"
#include "Architecture.h"


NIX_NAMESPACE_BEGIN


//////////////////////////////////////////////////////////////////////////
#if NIX_ARCH & NIX_ARCH_AVX512_FLAG
    typedef __m512  __nixFloat16;
    typedef __m512i __nixInt16;
#endif

#if NIX_ARCH & NIX_ARCH_AVX_FLAG
    typedef __m256  __nixFloat8;
    typedef __m256i __nixInt8;
#endif

#if NIX_ARCH & NIX_ARCH_SSE2_FLAG
    typedef __m128  __nixFloat4;
    typedef __m128i __nixInt4;
#endif


NIX_NAMESPACE_END