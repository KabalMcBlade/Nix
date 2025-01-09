// Copyright (c) 2018-2025 Michele Condo'
// File: C:\Projects\Nix\Nix\MathAligned.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.


#pragma once


#include "Constants.h"


NIX_NAMESPACE_BEGIN

template<int32 Align> class MathAligned;
template<> class NIX_ALIGN_16 MathAligned<16> { };

template <int32 Align, typename T> class MathBase : public MathAligned<Align> { };

NIX_NAMESPACE_END