#pragma once


#include "Constants.h"


NIX_NAMESPACE_BEGIN

template<int32 Align> class MathAligned;
template<> class NIX_ALIGN_16 MathAligned<16> { };

template <int32 Align, typename T> class MathBase : public MathAligned<Align> { };

NIX_NAMESPACE_END