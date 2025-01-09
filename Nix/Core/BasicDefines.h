// Copyright (c) 2018-2025 Michele Condo'
// File: C:\Projects\Nix\Nix\Core\BasicDefines.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.


#pragma once



#if _WIN32 || _WIN64
#if _WIN64
#define NIX_x64
#else
#define NIX_x86
#endif
#elif __GNUC__
#if __x86_64__ || __ppc64__
#define NIX_x64
#else
#define NIX_x86
#endif
#else
#define NIX_x86
#endif


// defines for easy namespace
#define NIX_NAMESPACE_BEGIN namespace nix {
#define NIX_NAMESPACE_END };  

#define NIX_USING_NAMESPACE using namespace nix; 

#define NIX_OPTIMIZATION_OFF __pragma(optimize("",off))
#define NIX_OPTIMIZATION_ON __pragma(optimize("",on))

/// forces a function to be in lined
#define NIX_INLINE __forceinline

// tells the compiler to never inline a particular function
#define NIX_NO_INLINE  __declspec(noinline)


// default alignment
#ifdef NIX_x64
#define NIX_MEMORY_ALIGNMENT_SIZE	16
#else
#define NIX_MEMORY_ALIGNMENT_SIZE	8
#endif

// Memory alignment
#define NIX_MEMORY_ALIGN(x)	__declspec(align(x))
#define NIX_ALIGN(x)			NIX_MEMORY_ALIGN(x)

#define NIX_ALIGN_PLATFORM		NIX_ALIGN(NIX_MEMORY_ALIGNMENT_SIZE)

#define NIX_ALIGN_8			NIX_ALIGN(8)
#define NIX_ALIGN_16			NIX_ALIGN(16)

#define NIX_IS_ALIGNED(ptr, alignment)    (((nix::uintPtr)ptr & (alignment - 1)) == 0)


