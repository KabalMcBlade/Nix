#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "MathAligned.h"
#include "BasicMathFunctions.h"


NIX_NAMESPACE_BEGIN


/*
    This cover both vector3 and vector4
    For the vector3 version, just referring to the function having the number "3" at the end, like Dot3
*/

class Vector4 : public MathAligned<16>
{
public:
    //////////////////////////////////////////////////////////////////////////
    // Constructors
    NIX_INLINE Vector4() : m_vec(kZero) {}
    NIX_INLINE Vector4(float _x, float _y, float _z, float _w) : m_vec(MathFunctions::Set(_x, _y, _z, _w)) {}
    NIX_INLINE Vector4(float _v) : m_vec(MathFunctions::Splat(_v)) {}
    NIX_INLINE Vector4(const Vector4& _copy) : m_vec(_copy) {}
    NIX_INLINE Vector4(Vector4&& _copy) noexcept : m_vec(std::move(_copy)) {}
    NIX_INLINE Vector4(const float128& _copy) : m_vec(_copy) {}
    NIX_INLINE Vector4(float128&& _copy) noexcept : m_vec(std::move(_copy)) {}

    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    friend NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Vector4& _v);
#endif

    //////////////////////////////////////////////////////////////////////////
    // Operators
	NIX_INLINE operator const float128&() const { return m_vec; }
	//NIX_INLINE operator float128() const { return m_vec; }

    NIX_INLINE Vector4& operator= (const Vector4& _v)
    {
        this->m_vec = _v;
        return *this;
    }
    NIX_INLINE Vector4& operator+=(const Vector4& _v)
    {
        this->m_vec = MathFunctions::Add(this->m_vec, _v);
        return *this;
    }
    NIX_INLINE Vector4& operator-=(const Vector4& _v)
    {
        this->m_vec = MathFunctions::Sub(this->m_vec, _v);
        return *this;
    }
    NIX_INLINE Vector4& operator*=(const Vector4& _v)
    {
        this->m_vec = MathFunctions::Mul(this->m_vec, _v);
        return *this;
    }
    NIX_INLINE Vector4& operator/=(const Vector4& _v)
    {
        this->m_vec = MathFunctions::Div(this->m_vec, _v);
        return *this;
    }
    NIX_INLINE Vector4& operator+=(const float& _s)
    {
        this->m_vec = MathFunctions::Add(this->m_vec, MathFunctions::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector4& operator-=(const float& _s)
    {
        this->m_vec = MathFunctions::Sub(this->m_vec, MathFunctions::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector4& operator*=(const float& _s)
    {
        this->m_vec = MathFunctions::Mul(this->m_vec, MathFunctions::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector4& operator/=(const float& _s)
    {
        this->m_vec = MathFunctions::Div(this->m_vec, MathFunctions::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector4& operator++()
    {
        this->m_vec = MathFunctions::Add(this->m_vec, kOneVec4);
        return *this;
    }
    NIX_INLINE Vector4& operator--()
    {
        this->m_vec = MathFunctions::Sub(this->m_vec, kOneVec4);
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    // Vector3 Version: Means that there are some difference to properly work upon 3 elements
    NIX_INLINE Vector4 Dot3(const Vector4& _other) const
    {
        return MathFunctions::Dot3(m_vec, _other);
    }

    NIX_INLINE Vector4 SquareLength3() const
    {
        return MathFunctions::SquareLength3(m_vec);
    }

    NIX_INLINE Vector4 Length3() const
    {
        return MathFunctions::Length3(m_vec);
    }

    NIX_INLINE Vector4 Normalize3() const
    {
        return MathFunctions::Normalize3(m_vec);
    }

    NIX_INLINE Vector4 Distance3(const Vector4& _other) const
    {
        return MathFunctions::Distance3(m_vec, _other);
    }

    //////////////////////////////////////////////////////////////////////////
    // Both Vector3 and Vector4 Version (even possible)
    NIX_INLINE Vector4 Abs() const
    {
        return MathFunctions::Abs(m_vec);
    }

    NIX_INLINE Vector4 Floor() const
    {
        return MathFunctions::Floor(m_vec);
    }

    NIX_INLINE Vector4 Ceil() const
    {
        return MathFunctions::Ceil(m_vec);
    }

    // Computes and returns (this * _vecToMul) + _vecToAdd.
    NIX_INLINE Vector4 MulAdd(const Vector4& _vecToMul, const Vector4& _vecToAdd) const
    {
        return MathFunctions::MulAdd(m_vec, _vecToMul, _vecToAdd);
    }

    NIX_INLINE Vector4 Dot(const Vector4& _other) const
    {
        return MathFunctions::Dot(m_vec, _other);
    }

    NIX_INLINE Vector4 SquareLength() const
    {
        return MathFunctions::SquareLength(m_vec);
    }

    NIX_INLINE Vector4 Length() const
    {
        return MathFunctions::Length(m_vec);
    }

    NIX_INLINE Vector4 SquareDistance(const Vector4& _other) const
    {
        return MathFunctions::SquareDistance(m_vec, _other);
    }

    NIX_INLINE Vector4 Distance(const Vector4& _other) const
    {
        return MathFunctions::Distance(m_vec, _other);
    }

    NIX_INLINE Vector4 Cross(const Vector4& _other) const
    {
        return MathFunctions::Cross(m_vec, _other);
    }

    NIX_INLINE Vector4 Mod(const Vector4& _other) const
    {
        return MathFunctions::Mod(m_vec, _other);
    }

    NIX_INLINE Vector4 Clamp(const Vector4& _min, const Vector4& _max) const
    {
        return MathFunctions::Clamp(m_vec, _min, _max);
    }

    NIX_INLINE Vector4 Normalize() const
    {
        return MathFunctions::Normalize(m_vec);
    }

    NIX_INLINE Vector4 Min(const Vector4& _other) const
    {
        return MathFunctions::Min(m_vec, _other);
    }

    NIX_INLINE Vector4 Max(const Vector4& _other) const
    {
        return MathFunctions::Max(m_vec, _other);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector4 LerpTo(const Vector4& _to, const Vector4& _time) const
    {
        return MathFunctions::Lerp(m_vec, _to, _time);
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector4 LerpFrom(const Vector4& _from, const Vector4& _time) const
    {
        return MathFunctions::Lerp(_from, m_vec, _time);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector4 LerpTo(const Vector4& _to, const float& _time) const
    {
        return LerpTo(_to, MathFunctions::Splat(_time));
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector4 LerpFrom(const Vector4& _from, const float& _time) const
    {
        return LerpFrom(_from, MathFunctions::Splat(_time));
    }

    NIX_INLINE Vector4 InverseLerp(const Vector4& _min, const Vector4& _max) const
    {
        return MathFunctions::InverseLerp(m_vec, _min, _max);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector4 StepTo(const Vector4& _to, const Vector4& _time) const
    {
        return MathFunctions::Step(m_vec, _to, _time);
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector4 StepFrom(const Vector4& _from, const Vector4& _time) const
    {
        return MathFunctions::Step(_from, m_vec, _time);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector4 StepTo(const Vector4& _to, const float& _time) const
    {
        return StepTo(_to, MathFunctions::Splat(_time));
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector4 StepFrom(const Vector4& _from, const float& _time) const
    {
        return StepFrom(_from, MathFunctions::Splat(_time));
    }


    //////////////////////////////////////////////////////////////////////////
    // Utility functions
    NIX_INLINE Vector4 GetX() const
    {
        return MathFunctions::Swizzle<X, X, X, X>(m_vec);
    }

    NIX_INLINE Vector4 GetY() const
    {
        return MathFunctions::Swizzle<Y, Y, Y, Y>(m_vec);
    }

    NIX_INLINE Vector4 GetZ() const
    {
        return MathFunctions::Swizzle<Z, Z, Z, Z>(m_vec);
    }

    NIX_INLINE Vector4 GetW() const
    {
        return MathFunctions::Swizzle<W, W, W, W>(m_vec);
    }

    // From  [a,b,c,d ] To  [b,c,d,a]
    NIX_INLINE Vector4 Rotate() const
    {
        return _mm_shuffle_ps(m_vec, m_vec, 0x39);    
    }


private:
    friend class Quaternion;
    friend class Matrix4x4;

    // for global operators
    friend NIX_INLINE Vector4 operator+ (const Vector4& _v, float _s);
    friend NIX_INLINE Vector4 operator+ (float _s, const Vector4& _v);
    friend NIX_INLINE Vector4 operator+ (const Vector4& _a, const Vector4& _b);
    friend NIX_INLINE Vector4 operator- (const Vector4& _v, float _s);
    friend NIX_INLINE Vector4 operator- (float _s, const Vector4& _v);
    friend NIX_INLINE Vector4 operator- (const Vector4& _a, const Vector4& _b);
    friend NIX_INLINE Vector4 operator* (const Vector4& _v, float _s);
    friend NIX_INLINE Vector4 operator* (float _s, const Vector4& _v);
    friend NIX_INLINE Vector4 operator* (const Vector4& _a, const Vector4& _b);
    friend NIX_INLINE Vector4 operator* (const Vector4& _a, const float128& _b);
    friend NIX_INLINE Vector4 operator* (const float128& _a, const Vector4& _b);
    friend NIX_INLINE Vector4 operator/ (const Vector4& _v, float _s);
    friend NIX_INLINE Vector4 operator/ (float _s, const Vector4& _v);
    friend NIX_INLINE Vector4 operator/ (const Vector4& _a, const Vector4& _b);
    friend NIX_INLINE Vector4 operator- (const Vector4& _v);
    friend NIX_INLINE Vector4 operator++ (const Vector4& _v, int32);
    friend NIX_INLINE Vector4 operator-- (const Vector4& _v, int32);
    friend NIX_INLINE bool operator==(const Vector4& _lhs, const Vector4& _rhs);
    friend NIX_INLINE bool operator!=(const Vector4& _lhs, const Vector4& _rhs);
    friend NIX_INLINE bool operator< (const Vector4& _lhs, const Vector4& _rhs);
    friend NIX_INLINE bool operator> (const Vector4& _lhs, const Vector4& _rhs);
    friend NIX_INLINE bool operator<=(const Vector4& _lhs, const Vector4& _rhs);
    friend NIX_INLINE bool operator>=(const Vector4& _lhs, const Vector4& _rhs);

    // from quaternion
    friend NIX_INLINE Quaternion operator* (const Quaternion& _q1, const Quaternion& _q2);
    friend NIX_INLINE Vector4 operator* (const Quaternion& _q, const Vector4& _v);

    // from matrix
    friend NIX_INLINE Vector4 operator*(const Matrix4x4& _m, const Vector4& _v);
    friend NIX_INLINE Vector4 operator*(const Vector4& _v, const Matrix4x4& _m);

    float128 m_vec;
};


//////////////////////////////////////////////////////////////////////////
// Operators

#ifdef _DEBUG
NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Vector4& _v)
{
    float *val = (float*)&_v;
    _os << "(" << val[0] << ", " << val[1] << ", " << val[2] << ", " << val[3] << ")";
    return _os;
}
#endif

// operator+
NIX_INLINE Vector4 operator+ (const Vector4& _v, float _s)
{
    return MathFunctions::Add(_v, MathFunctions::Splat(_s));
}

NIX_INLINE Vector4 operator+ (float _s, const Vector4& _v)
{
    return MathFunctions::Add(MathFunctions::Splat(_s), _v);
}

NIX_INLINE Vector4 operator+ (const Vector4& _a, const Vector4& _b)
{
    return MathFunctions::Add(_a, _b);
}

//operator-
NIX_INLINE Vector4 operator- (const Vector4& _v, float _s)
{
    return MathFunctions::Sub(_v, MathFunctions::Splat(_s));
}

NIX_INLINE Vector4 operator- (float _s, const Vector4& _v)
{
    return MathFunctions::Sub(MathFunctions::Splat(_s), _v);
}

NIX_INLINE Vector4 operator- (const Vector4& _a, const Vector4& _b)
{
    return MathFunctions::Sub(_a, _b);
}

//operator*
NIX_INLINE Vector4 operator* (const Vector4& _v, float _s)
{
    return MathFunctions::Mul(_v, MathFunctions::Splat(_s));
}

NIX_INLINE Vector4 operator* (float _s, const Vector4& _v)
{
    return MathFunctions::Mul(MathFunctions::Splat(_s), _v);
}

NIX_INLINE Vector4 operator* (const Vector4& _a, const Vector4& _b)
{
    return MathFunctions::Mul(_a, _b);
}

NIX_INLINE Vector4 operator* (const Vector4& _a, const float128& _b)
{
    return MathFunctions::Mul(_a, _b);
}

NIX_INLINE Vector4 operator* (const float128& _a, const Vector4& _b)
{
    return MathFunctions::Mul(_a, _b);
}


//operator/
NIX_INLINE Vector4  operator/ (const Vector4& _v, float _s)
{
    return MathFunctions::Div(_v, MathFunctions::Splat(_s));
}

NIX_INLINE Vector4  operator/ (float _s, const Vector4& _v)
{
    return MathFunctions::Div(MathFunctions::Splat(_s), _v);
}

NIX_INLINE Vector4  operator/ (const Vector4& _a, const Vector4& _b)
{
    return MathFunctions::Div(_a, _b);
}

// Unary constant operators
NIX_INLINE Vector4  operator- (const Vector4& _v)
{
    return MathFunctions::Sub(kZero, _v);
}

NIX_INLINE Vector4  operator++ (const Vector4& _v, int32)
{
    return MathFunctions::Add(_v, kOneVec4);
}

NIX_INLINE Vector4  operator-- (const Vector4& _v, int32)
{
    return MathFunctions::Sub(_v, kOneVec4);
}

NIX_INLINE bool operator==(const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmpeq_ps(_lhs, _rhs);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE bool operator!=(const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmpneq_ps(_lhs, _rhs);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE bool operator< (const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmplt_ps(_lhs, _rhs);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE bool operator> (const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmpgt_ps(_lhs, _rhs);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE bool operator<=(const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmple_ps(_lhs, _rhs);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE bool operator>=(const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmpge_ps(_lhs, _rhs);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}


NIX_NAMESPACE_END