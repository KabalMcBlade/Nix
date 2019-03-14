#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Helper.h"

NIX_NAMESPACE_BEGIN


/*
    This cover both vector3 and vector4
    For the vector3 version, just referring to the function having the number "3" at the end, like Dot3
*/

NIX_SIMD_ALIGN_16 class Vector
{
public:
    //////////////////////////////////////////////////////////////////////////
    // Constructors
    NIX_INLINE Vector() : m_vec(kZero) {}
    NIX_INLINE Vector(nixFloat _x, nixFloat _y, nixFloat _z) : m_vec(Helper::Set(_x, _y, _z, 0.0f)) {}
    NIX_INLINE Vector(nixFloat _x, nixFloat _y, nixFloat _z, nixFloat _w) : m_vec(Helper::Set(_x, _y, _z, _w)) {}
    NIX_INLINE Vector(nixFloat _v) : m_vec(Helper::Splat(_v)) {}
    NIX_INLINE Vector(const Vector& _copy) : m_vec(_copy.m_vec) {}
    NIX_INLINE Vector(Vector&& _copy) noexcept : m_vec(std::move(_copy.m_vec)) {}
    NIX_INLINE Vector(const nixFloat4& _copy) : m_vec(_copy) {}
    NIX_INLINE Vector(nixFloat4&& _copy) noexcept : m_vec(std::move(_copy)) {}

    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    friend NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Vector& _v);
#endif

    //////////////////////////////////////////////////////////////////////////
    // Operators
    NIX_INLINE operator const nixFloat4&() const { return m_vec; }

    NIX_INLINE Vector& operator= (const Vector& _v)
    {
        this->m_vec = _v.m_vec;
        return *this;
    }
    NIX_INLINE Vector& operator+=(const Vector& _v)
    {
        this->m_vec = Helper::Add(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator-=(const Vector& _v)
    {
        this->m_vec = Helper::Sub(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator*=(const Vector& _v)
    {
        this->m_vec = Helper::Mul(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator/=(const Vector& _v)
    {
        this->m_vec = Helper::Div(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator+=(const nixFloat& _s)
    {
        this->m_vec = Helper::Add(this->m_vec, Helper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator-=(const nixFloat& _s)
    {
        this->m_vec = Helper::Sub(this->m_vec, Helper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator*=(const nixFloat& _s)
    {
        this->m_vec = Helper::Mul(this->m_vec, Helper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator/=(const nixFloat& _s)
    {
        this->m_vec = Helper::Div(this->m_vec, Helper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator++()
    {
        this->m_vec = Helper::Add(this->m_vec, kOne);
        return *this;
    }
    NIX_INLINE Vector& operator--()
    {
        this->m_vec = Helper::Sub(this->m_vec, kOne);
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    // Vector3 Version: Means that there are some difference to properly work upon 3 elements
    NIX_INLINE Vector Dot3(const Vector& _other) const
    {
        return Helper::Dot3(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector SquareLength3() const
    {
        return Helper::SquareLength3(m_vec);
    }

    NIX_INLINE Vector Length3() const
    {
        return Helper::Length3(m_vec);
    }

    NIX_INLINE Vector Normalize3() const
    {
        return Helper::Normalize3(m_vec);
    }

    NIX_INLINE Vector Distance3(const Vector& _other) const
    {
        return Helper::Distance3(m_vec, _other.m_vec);
    }

    //////////////////////////////////////////////////////////////////////////
    // Both Vector3 and Vector4 Version (even possible)
    NIX_INLINE Vector Abs() const
    {
        return Helper::Abs(m_vec);
    }

    NIX_INLINE Vector Floor() const
    {
        return Helper::Floor(m_vec);
    }

    NIX_INLINE Vector Ceil() const
    {
        return Helper::Ceil(m_vec);
    }

    // Computes and returns (this * _vecToMul) + _vecToAdd.
    NIX_INLINE Vector MulAdd(const Vector& _vecToMul, const Vector& _vecToAdd) const
    {
        return Helper::MulAdd(m_vec, _vecToMul.m_vec, _vecToAdd.m_vec);
    }

    NIX_INLINE Vector Dot(const Vector& _other) const
    {
        return Helper::Dot(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector SquareLength() const
    {
        return Helper::SquareLength(m_vec);
    }

    NIX_INLINE Vector Length() const
    {
        return Helper::Length(m_vec);
    }

    NIX_INLINE Vector SquareDistance(const Vector& _other) const
    {
        return Helper::SquareDistance(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Distance(const Vector& _other) const
    {
        return Helper::Distance(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Cross(const Vector& _other) const
    {
        return Helper::Cross(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Mod(const Vector& _other) const
    {
        return Helper::Mod(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Clamp(const Vector& _min, const Vector& _max) const
    {
        return Helper::Clamp(m_vec, _min.m_vec, _max.m_vec);
    }

    NIX_INLINE Vector Normalize() const
    {
        return Helper::Normalize(m_vec);
    }

    NIX_INLINE Vector Min(const Vector& _other) const
    {
        return Helper::Min(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Max(const Vector& _other) const
    {
        return Helper::Max(m_vec, _other.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector LerpTo(const Vector& _to, const Vector& _time) const
    {
        return Helper::Lerp(m_vec, _to.m_vec, _time.m_vec);
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector LerpFrom(const Vector& _from, const Vector& _time) const
    {
        return Helper::Lerp(_from.m_vec, m_vec, _time.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector LerpTo(const Vector& _to, const nixFloat& _time) const
    {
        return LerpTo(_to, Helper::Splat(_time));
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector LerpFrom(const Vector& _from, const nixFloat& _time) const
    {
        return LerpFrom(_from, Helper::Splat(_time));
    }

    NIX_INLINE Vector InverseLerp(const Vector& _min, const Vector& _max) const
    {
        return Helper::InverseLerp(m_vec, _min.m_vec, _max.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector StepTo(const Vector& _to, const Vector& _time) const
    {
        return Helper::Step(m_vec, _to.m_vec, _time.m_vec);
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector StepFrom(const Vector& _from, const Vector& _time) const
    {
        return Helper::Step(_from.m_vec, m_vec, _time.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector StepTo(const Vector& _to, const nixFloat& _time) const
    {
        return StepTo(_to, Helper::Splat(_time));
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector StepFrom(const Vector& _from, const nixFloat& _time) const
    {
        return StepFrom(_from, Helper::Splat(_time));
    }


    //////////////////////////////////////////////////////////////////////////
    // Utility functions
    NIX_INLINE Vector GetX() const
    {
        return Swizzle::XXXX(m_vec);
    }

    NIX_INLINE Vector GetY() const
    {
        return Swizzle::YYYY(m_vec);
    }

    NIX_INLINE Vector GetZ() const
    {
        return Swizzle::ZZZZ(m_vec);
    }

    NIX_INLINE Vector GetW() const
    {
        return Swizzle::WWWW(m_vec);
    }

    // From  [a,b,c,d ] To  [b,c,d,a]
    NIX_INLINE Vector Rotate() const
    {
        return _mm_shuffle_ps(m_vec, m_vec, 0x39);    
    }


private:
    friend struct Helper;
    friend class Quaternion;
    friend class Matrix;

    // for global operators
    friend NIX_INLINE Vector operator+ (const Vector& _v, nixFloat _s);
    friend NIX_INLINE Vector operator+ (nixFloat _s, const Vector& _v);
    friend NIX_INLINE Vector operator+ (const Vector& _a, const Vector& _b);
    friend NIX_INLINE Vector operator- (const Vector& _v, nixFloat _s);
    friend NIX_INLINE Vector operator- (nixFloat _s, const Vector& _v);
    friend NIX_INLINE Vector operator- (const Vector& _a, const Vector& _b);
    friend NIX_INLINE Vector operator* (const Vector& _v, nixFloat _s);
    friend NIX_INLINE Vector operator* (nixFloat _s, const Vector& _v);
    friend NIX_INLINE Vector operator* (const Vector& _a, const Vector& _b);
    friend NIX_INLINE Vector operator* (const Vector& _a, const nixFloat4& _b);
    friend NIX_INLINE Vector operator* (const nixFloat4& _a, const Vector& _b);
    friend NIX_INLINE Vector operator/ (const Vector& _v, nixFloat _s);
    friend NIX_INLINE Vector operator/ (nixFloat _s, const Vector& _v);
    friend NIX_INLINE Vector operator/ (const Vector& _a, const Vector& _b);
    friend NIX_INLINE Vector operator- (const Vector& _v);
    friend NIX_INLINE Vector operator++ (const Vector& _v, nixS32);
    friend NIX_INLINE Vector operator-- (const Vector& _v, nixS32);
    friend NIX_INLINE nixBool operator==(const Vector& _lhs, const Vector& _rhs);
    friend NIX_INLINE nixBool operator!=(const Vector& _lhs, const Vector& _rhs);
    friend NIX_INLINE nixBool operator< (const Vector& _lhs, const Vector& _rhs);
    friend NIX_INLINE nixBool operator> (const Vector& _lhs, const Vector& _rhs);
    friend NIX_INLINE nixBool operator<=(const Vector& _lhs, const Vector& _rhs);
    friend NIX_INLINE nixBool operator>=(const Vector& _lhs, const Vector& _rhs);

    // from quaternion
    friend NIX_INLINE Quaternion operator* (const Quaternion& _q1, const Quaternion& _q2);
    friend NIX_INLINE Vector operator* (const Quaternion& _q, const Vector& _v);

    // from matrix
    friend NIX_INLINE Vector operator*(const Matrix& _m, const Vector& _v);
    friend NIX_INLINE Vector operator*(const Vector& _v, const Matrix& _m);

    nixFloat4 m_vec;
};


//////////////////////////////////////////////////////////////////////////
// Operators

#ifdef _DEBUG
NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Vector& _v)
{
    nixFloat *val = (nixFloat*)&_v.m_vec;
    _os << "(" << val[0] << ", " << val[1] << ", " << val[2] << ", " << val[3] << ")";
    return _os;
}
#endif

// operator+
NIX_INLINE Vector operator+ (const Vector& _v, nixFloat _s)
{
    return Helper::Add(_v.m_vec, Helper::Splat(_s));
}

NIX_INLINE Vector operator+ (nixFloat _s, const Vector& _v)
{
    return Helper::Add(Helper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector operator+ (const Vector& _a, const Vector& _b)
{
    return Helper::Add(_a.m_vec, _b.m_vec);
}

//operator-
NIX_INLINE Vector operator- (const Vector& _v, nixFloat _s)
{
    return Helper::Sub(_v.m_vec, Helper::Splat(_s));
}

NIX_INLINE Vector operator- (nixFloat _s, const Vector& _v)
{
    return Helper::Sub(Helper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector operator- (const Vector& _a, const Vector& _b)
{
    return Helper::Sub(_a.m_vec, _b.m_vec);
}

//operator*
NIX_INLINE Vector operator* (const Vector& _v, nixFloat _s)
{
    return Helper::Mul(_v.m_vec, Helper::Splat(_s));
}

NIX_INLINE Vector operator* (nixFloat _s, const Vector& _v)
{
    return Helper::Mul(Helper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector operator* (const Vector& _a, const Vector& _b)
{
    return Helper::Mul(_a.m_vec, _b.m_vec);
}

NIX_INLINE Vector operator* (const Vector& _a, const nixFloat4& _b)
{
    return Helper::Mul(_a.m_vec, _b);
}

NIX_INLINE Vector operator* (const nixFloat4& _a, const Vector& _b)
{
    return Helper::Mul(_a, _b.m_vec);
}


//operator/
NIX_INLINE Vector  operator/ (const Vector& _v, nixFloat _s)
{
    return Helper::Div(_v.m_vec, Helper::Splat(_s));
}

NIX_INLINE Vector  operator/ (nixFloat _s, const Vector& _v)
{
    return Helper::Div(Helper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector  operator/ (const Vector& _a, const Vector& _b)
{
    return Helper::Div(_a.m_vec, _b.m_vec);
}

// Unary constant operators
NIX_INLINE Vector  operator- (const Vector& _v)
{
    return _mm_sub_ps(kZero, _v.m_vec);
}

NIX_INLINE Vector  operator++ (const Vector& _v, nixS32)
{
    return _mm_add_ps(_v.m_vec, kOne);
}

NIX_INLINE Vector  operator-- (const Vector& _v, nixS32)
{
    return _mm_sub_ps(_v.m_vec, kOne);
}

NIX_INLINE nixBool operator==(const Vector& _lhs, const Vector& _rhs)
{
    const nixFloat4 equal = _mm_cmpeq_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE nixBool operator!=(const Vector& _lhs, const Vector& _rhs)
{
    const nixFloat4 equal = _mm_cmpneq_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE nixBool operator< (const Vector& _lhs, const Vector& _rhs)
{
    const nixFloat4 equal = _mm_cmplt_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE nixBool operator> (const Vector& _lhs, const Vector& _rhs)
{
    const nixFloat4 equal = _mm_cmpgt_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE nixBool operator<=(const Vector& _lhs, const Vector& _rhs)
{
    const nixFloat4 equal = _mm_cmple_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE nixBool operator>=(const Vector& _lhs, const Vector& _rhs)
{
    const nixFloat4 equal = _mm_cmpge_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}


NIX_NAMESPACE_END