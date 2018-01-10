#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"
#include "VectorHelper.h"
#include "Matrix.h"


NIX_NAMESPACE_BEGIN


#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG
NIX_SIMD_ALIGN_32 class MatrixHelper
#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG
NIX_SIMD_ALIGN_32 class MatrixHelper
#   else 
NIX_SIMD_ALIGN_16 class MatrixHelper
#   endif
{
public:


private:

};


NIX_NAMESPACE_END