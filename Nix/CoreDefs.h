#pragma once


//////////////////////////////////////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////////////////////////////////////

#include <assert.h>     // for assert
#include <stdint.h>     // for u8, etc...
#include <math.h>

#include <cmath>
#include <limits>
#include <utility>      // for move, etc...


//////////////////////////////////////////////////////////////////////////
// DEFINES
//////////////////////////////////////////////////////////////////////////

// defines for easy namespace-ing
#define NIX_NAMESPACE_BEGIN namespace nix {
#define NIX_NAMESPACE_END };  

#define NIX_USING_NAMESPACE using namespace nix; 

#define NIX_MEMORY_ALIGNMENT_SIZE_16 16
#define NIX_MEMORY_ALIGNMENT_SIZE_32 32

#define NIX_OPTIMIZATION_OFF __pragma(optimize("",off))
#define NIX_OPTIMIZATION_ON __pragma(optimize("",on))

/// forces a function to be in lined
#define NIX_INLINE    __forceinline

// tells the compiler to never inline a particular function
#define NIX_NO_INLINE    __declspec(noinline)

// Memory alignment
#define NIX_MEMORY_ALIGNMENT(x)     __declspec(align(x))
#define NIX_IS_ALIGNED(ptr, alignment)    ((uint_fast64_t)ptr & (alignment - 1)) == 0


#define NIX_SIMD_ALIGN_16   NIX_MEMORY_ALIGNMENT(NIX_MEMORY_ALIGNMENT_SIZE_16)
#define NIX_SIMD_ALIGN_32   NIX_MEMORY_ALIGNMENT(NIX_MEMORY_ALIGNMENT_SIZE_32)

//////////////////////////////////////////////////////////////////////////
// TYPEDEFS
//////////////////////////////////////////////////////////////////////////

typedef bool            nixBool;
typedef float           nixFloat;
typedef double          nixDouble;


typedef uint_fast8_t    nixU8;
typedef uint_fast16_t   nixU16;
typedef uint_fast32_t   nixU32;
typedef uint_fast64_t   nixU64;

typedef int_fast8_t     nixS8;
typedef int_fast16_t    nixS16;
typedef int_fast32_t    nixS32;
typedef int_fast64_t    nixS64;

typedef std::size_t     nixSize;


//////////////////////////////////////////////////////////////////////////
// ASSERT
//////////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#define nixAssert( condition, message ) \
    if( !(condition) ) { \
        std::cerr << "Assert: " << (#condition) << std::endl; \
        std::cerr << "Message: " << message << std::endl; \
        std::cerr << "File: " << __FILE__ << std::endl; \
        std::cerr << "Line: " << __LINE__ << std::endl << std::endl; \
    }
#define nixAssertDialog( condition ) assert(condition)
#else
#define nixAssert( condition, message )
#define nixAssertDialog( condition )
#endif // DEBUG

#define nixAssertReturnVoid( condition, message ) \
    nixAssert( condition, message )\
    if( !(condition) ) { \
        return;\
    }

#define nixAssertReturnValue( condition, message, return_value ) \
    nixAssert( condition, message )\
    if( !(condition) ) { \
        return return_value;\
    }