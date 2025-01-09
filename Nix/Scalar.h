// Copyright (c) 2018-2025 Michele Condo'
// File: C:\Projects\Nix\Nix\Scalar.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.


#pragma once


#include "MathBase.h"


NIX_NAMESPACE_BEGIN

class Scalar : public MathBase<16, Scalar>
{
public:
	NIX_INLINE Scalar() { m_vec = MathFunctions::SplatZero(); }
	NIX_INLINE Scalar(const Scalar& _s) { m_vec = _s; }
	NIX_INLINE Scalar(float _s) { m_vec = MathFunctions::Splat(_s); }
	NIX_INLINE explicit Scalar(float128 _s) { m_vec = MathFunctions::SplatX(_s); }

	NIX_INLINE operator float() const { return MathFunctions::ExtractX(m_vec); }

	NIX_INLINE Scalar operator+= (const Scalar& _s) { m_vec = MathFunctions::Add(*this, _s); return *this; }
	NIX_INLINE Scalar operator-= (const Scalar& _s) { m_vec = MathFunctions::Sub(*this, _s); return *this; }
	NIX_INLINE Scalar operator*= (const Scalar& _s) { m_vec = MathFunctions::Mul(*this, _s); return *this; }
	NIX_INLINE Scalar operator/= (const Scalar& _s) { m_vec = MathFunctions::Div(*this, _s); return *this; }
	NIX_INLINE Scalar operator+= (const float128& _s) { m_vec = MathFunctions::Add(*this, _s); return *this; }
	NIX_INLINE Scalar operator-= (const float128& _s) { m_vec = MathFunctions::Sub(*this, _s); return *this; }
	NIX_INLINE Scalar operator*= (const float128& _s) { m_vec = MathFunctions::Mul(*this, _s); return *this; }
	NIX_INLINE Scalar operator/= (const float128& _s) { m_vec = MathFunctions::Div(*this, _s); return *this; }
	NIX_INLINE Scalar operator+= (float128 _s) { m_vec = MathFunctions::Add(*this, _s); return *this; }
	NIX_INLINE Scalar operator-= (float128 _s) { m_vec = MathFunctions::Sub(*this, _s); return *this; }
	NIX_INLINE Scalar operator*= (float128 _s) { m_vec = MathFunctions::Mul(*this, _s); return *this; }
	NIX_INLINE Scalar operator/= (float128 _s) { m_vec = MathFunctions::Div(*this, _s); return *this; }

public:
	static NIX_INLINE Scalar Zero() { return Scalar(MathFunctions::SplatZero()); }
	static NIX_INLINE Scalar One() { return Scalar(MathFunctions::SplatZero()); }
};

NIX_INLINE Scalar operator- (const Scalar& _s) { return static_cast<Scalar>(MathFunctions::Sub(_mm_setzero_ps(), _s)); }
NIX_INLINE Scalar operator+ (const Scalar& _s1, const Scalar& _s2) { return static_cast<Scalar>(MathFunctions::Add(_s1, _s2)); }
NIX_INLINE Scalar operator- (const Scalar& _s1, const Scalar& _s2) { return static_cast<Scalar>(MathFunctions::Sub(_s1, _s2)); }
NIX_INLINE Scalar operator* (const Scalar& _s1, const Scalar& _s2) { return static_cast<Scalar>(MathFunctions::Mul(_s1, _s2)); }
NIX_INLINE Scalar operator/ (const Scalar& _s1, const Scalar& _s2) { return static_cast<Scalar>(MathFunctions::Div(_s1, _s2)); }
NIX_INLINE Scalar operator+ (const Scalar& _s1, float128 _s2) { return _s1 + static_cast<Scalar>(_s2); }
NIX_INLINE Scalar operator- (const Scalar& _s1, float128 _s2) { return _s1 - static_cast<Scalar>(_s2); }
NIX_INLINE Scalar operator* (const Scalar& _s1, float128 _s2) { return _s1 * static_cast<Scalar>(_s2); }
NIX_INLINE Scalar operator/ (const Scalar& _s1, float128 _s2) { return _s1 / static_cast<Scalar>(_s2); }
NIX_INLINE Scalar operator+ (float128 _s1, const Scalar& _s2) { return static_cast<Scalar>(_s1) + _s2; }
NIX_INLINE Scalar operator- (float128 _s1, const Scalar& _s2) { return static_cast<Scalar>(_s1) - _s2; }
NIX_INLINE Scalar operator* (float128 _s1, const Scalar& _s2) { return static_cast<Scalar>(_s1) * _s2; }
NIX_INLINE Scalar operator/ (float128 _s1, const Scalar& _s2) { return static_cast<Scalar>(_s1) / _s2; }
NIX_INLINE float128 operator+ (float128 _s1, float128 _s2) { return static_cast<Scalar>(MathFunctions::Add(_s1, _s2)); }
NIX_INLINE float128 operator- (float128 _s1, float128 _s2) { return static_cast<Scalar>(MathFunctions::Sub(_s1, _s2)); }
NIX_INLINE float128 operator* (float128 _s1, float128 _s2) { return static_cast<Scalar>(MathFunctions::Mul(_s1, _s2)); }
NIX_INLINE float128 operator/ (float128 _s1, float128 _s2) { return static_cast<Scalar>(MathFunctions::Div(_s1, _s2)); }

NIX_NAMESPACE_END