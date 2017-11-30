#pragma once
    
#if _MSC_VER < 1800
#   error "Nix math lib requires Visual C++ 12 - 2013 or higher"
#endif  //_MSC_VER


#define NIX_VERBOSE_ARCH

///////////////////////////////////////////////////////////////////////////////////
// Instruction sets

#define NIX_ARCH_X86_BIT    0x0001
#define NIX_ARCH_SSE2_BIT   0x0002
#define NIX_ARCH_SSE3_BIT   0x0004
#define NIX_ARCH_SSSE3_BIT  0x0008
#define NIX_ARCH_SSE41_BIT  0x0010
#define NIX_ARCH_SSE42_BIT  0x0020
#define NIX_ARCH_AVX_BIT    0x0040
#define NIX_ARCH_AVX2_BIT   0x0080
#define NIX_ARCH_AVX512_BIT 0x0100 // Intel Skylake-X core subset

#define NIX_ARCH_X86    NIX_ARCH_X86_BIT
#define NIX_ARCH_SSE2   (NIX_ARCH_SSE2_BIT | NIX_ARCH_X86)
#define NIX_ARCH_SSE3   (NIX_ARCH_SSE3_BIT | NIX_ARCH_SSE2)
#define NIX_ARCH_SSSE3  (NIX_ARCH_SSSE3_BIT | NIX_ARCH_SSE3)
#define NIX_ARCH_SSE41  (NIX_ARCH_SSE41_BIT | NIX_ARCH_SSSE3)
#define NIX_ARCH_SSE42  (NIX_ARCH_SSE42_BIT | NIX_ARCH_SSE41)
#define NIX_ARCH_AVX    (NIX_ARCH_AVX_BIT | NIX_ARCH_SSE42)
#define NIX_ARCH_AVX2   (NIX_ARCH_AVX2_BIT | NIX_ARCH_AVX)
#define NIX_ARCH_AVX512 (NIX_ARCH_AVX512_BIT | NIX_ARCH_AVX2) // Intel Skylake-X core subset


///////////////////////////////////////////////////////////////////////////////////

#if defined(__AVX2__)
#   define NIX_ARCH NIX_ARCH_AVX2
#elif defined(__AVX__)
#   define NIX_ARCH NIX_ARCH_AVX
#elif defined(_M_X64)
#   define NIX_ARCH NIX_ARCH_SSE2
#elif defined(_M_IX86_FP)
#   if _M_IX86_FP >= 2
#       define NIX_ARCH NIX_ARCH_SSE2
#   else
#       error "Nix architecture support only SIMD >= SSE2"
#   endif
#else
#   error "Nix architecture support only SIMD >= SSE2"
#endif


///////////////////////////////////////////////////////////////////////////////////

#if NIX_ARCH & NIX_ARCH_AVX2_BIT
#   if defined(NIX_VERBOSE_ARCH)
#      pragma message("Supported architecture: AVX 2")
#   endif
#   include <immintrin.h>
#elif NIX_ARCH & NIX_ARCH_AVX_BIT
#   if defined(NIX_VERBOSE_ARCH)
#      pragma message("Supported architecture: AVX")
#   endif
#   include <immintrin.h>
#elif NIX_ARCH & NIX_ARCH_SSE42_BIT
#   if defined(NIX_VERBOSE_ARCH)
#      pragma message("Supported architecture: SSE 4.2")
#   endif
#   include <nmmintrin.h>
#elif NIX_ARCH & NIX_ARCH_SSE41_BIT
#   if defined(NIX_VERBOSE_ARCH)
#      pragma message("Supported architecture: SSE 4.1")
#   endif
#   include <smmintrin.h>
#elif NIX_ARCH & NIX_ARCH_SSSE3_BIT
#   if defined(NIX_VERBOSE_ARCH)
#       pragma message("Supported architecture: SSSE 3")
#   endif
#   include <tmmintrin.h>
#elif NIX_ARCH & NIX_ARCH_SSE3_BIT
#   pragma message("Supported architecture: SSE 3")
#   include <pmmintrin.h>
#elif NIX_ARCH & NIX_ARCH_SSE2_BIT
#   if defined(NIX_VERBOSE_ARCH)
#       pragma message("Supported architecture: SSE 2")
#   endif
#   include <emmintrin.h>
#endif  //NIX_ARCH