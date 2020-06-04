#pragma once


#include "MathAligned.h"
#include "BasicMathFunctions.h"
#include "Boolean.h"


NIX_NAMESPACE_BEGIN



template <typename T>
class MathBase<16, T>
{
public:
	NIX_INLINE operator float128() const { return m_vec; }

	NIX_INLINE T Sqrt() const { return static_cast<T>(MathFunctions::Sqrt(*this)); }
	NIX_INLINE T Recip3() const { return static_cast<T>(MathFunctions::Div(kOneVec3, *this)); }
	NIX_INLINE T Recip4() const { return static_cast<T>(MathFunctions::Div(kOneVec4, *this)); }
	NIX_INLINE T RecipSqrt() const { return static_cast<T>(MathFunctions::ReciprocalSqrt(*this)); }
	NIX_INLINE T Round() const{ return static_cast<T>(MathFunctions::Round(*this)); }
	NIX_INLINE T Floor() const { return static_cast<T>(MathFunctions::Floor(*this)); }
	NIX_INLINE T Ceil() const { return static_cast<T>(MathFunctions::Ceil(*this)); }
	NIX_INLINE T Abs() const { return static_cast<T>(MathFunctions::Abs(*this)); }
	NIX_INLINE T Exp() const { return static_cast<T>(Trigonometry::Exp(*this)); }
	NIX_INLINE T Log() const { return static_cast<T>(Trigonometry::Log(*this)); }
	NIX_INLINE T Sin() const { return static_cast<T>(Trigonometry::Sin(*this)); }
	NIX_INLINE T Cos() const { return static_cast<T>(Trigonometry::Cos(*this)); }
	NIX_INLINE T Mod(const T& _other) const { return MathFunctions::Mod(*this, _other);}
	NIX_INLINE T LerpTo(const T& _to, const float _time) const { return static_cast<T>(MathFunctions::Lerp(*this, _to, MathFunctions::Splat(_time))); }
	NIX_INLINE T LerpFrom(const T& _from, const float _time) const { return static_cast<T>(MathFunctions::Lerp(_from, *this, MathFunctions::Splat(_time))); }
	NIX_INLINE T StepTo(const T& _to, const float _time) const { return static_cast<T>(MathFunctions::Step(*this, _to, MathFunctions::Splat(_time))); }
	NIX_INLINE T StepFrom(const T& _from, const float _time) const { return static_cast<T>(MathFunctions::Step(_from, *this, MathFunctions::Splat(_time))); }
	NIX_INLINE T Max(const T& _other) const { return static_cast<T>(MathFunctions::Max(*this, _other)); }
	NIX_INLINE T Min(const T& _other) const { return static_cast<T>(MathFunctions::Min(*this, _other)); }
	NIX_INLINE T Clamp(const T& _min, const T& _max) const { return static_cast<T>(MathFunctions::Clamp(*this, _min, _max)); }
	NIX_INLINE T InverseLerp(const T& _min, const T& _max) const{ return MathFunctions::InverseLerp(*this, _min, _max); }
	NIX_INLINE T GetX() const { return MathFunctions::ExtractX(*this); }
	NIX_INLINE T GetY() const { return MathFunctions::ExtractY(*this); }
	NIX_INLINE T GetZ() const { return MathFunctions::ExtractZ(*this); }
	NIX_INLINE T GetW() const { return MathFunctions::ExtractW(*this); }
	NIX_INLINE T Rotate() const { return MathFunctions::Rotate(*this); }

	NIX_INLINE Boolean operator<  (const T& _rhs) const { return static_cast<Boolean>(_mm_cmplt_ps(*this, _rhs)); }
	NIX_INLINE Boolean operator<= (const T& _rhs) const { return static_cast<Boolean>(_mm_cmple_ps(*this, _rhs)); }
	NIX_INLINE Boolean operator>  (const T& _rhs) const { return static_cast<Boolean>(_mm_cmpgt_ps(*this, _rhs)); }
	NIX_INLINE Boolean operator>= (const T& _rhs) const { return static_cast<Boolean>(_mm_cmpge_ps(*this, _rhs)); }
	NIX_INLINE Boolean operator== (const T& _rhs) const { return static_cast<Boolean>(_mm_cmpeq_ps(*this, _rhs)); }
	NIX_INLINE Boolean operator!= (const T& _rhs) const { return static_cast<Boolean>(_mm_cmpneq_ps(*this, _rhs)); }


protected:
	float128 m_vec;
};


NIX_NAMESPACE_END