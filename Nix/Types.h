#pragma once

#include "CoreDefs.h"
#include "Architecture.h"


NIX_NAMESPACE_BEGIN

//////////////////////////////////////////////////////////////////////////
#if NIX_ARCH & NIX_ARCH_SSE2_BIT
typedef __m128	__sphFloat4;
typedef __m128i	__sphInt4;
#endif

//////////////////////////////////////////////////////////////////////////
#if NIX_ARCH & NIX_ARCH_AVX_BIT
typedef __m256	__sphFloat8;
typedef __m256i	__sphInt8;
#endif

//////////////////////////////////////////////////////////////////////////
#if NIX_ARCH & NIX_ARCH_AVX512_BIT
typedef __m512  __sphFloat16;
typedef __m512i	__sphInt16;
#endif


NIX_NAMESPACE_END