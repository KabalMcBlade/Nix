#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"
#include "VectorHelper.h"

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
    NIX_INLINE Vector() : m_vec(VectorHelper::GetZero()) {}
    NIX_INLINE Vector(nixFloat _x, nixFloat _y, nixFloat _z) : m_vec(VectorHelper::Set(_x, _y, _z, 0.0f)) {}
    NIX_INLINE Vector(nixFloat _x, nixFloat _y, nixFloat _z, nixFloat _w) : m_vec(VectorHelper::Set(_x, _y, _z, _w)) {}
    NIX_INLINE Vector(nixFloat _v) : m_vec(VectorHelper::Splat(_v)) {}
    NIX_INLINE Vector(const Vector& _copy) : m_vec(_copy.m_vec) {}
    NIX_INLINE Vector(Vector&& _copy) noexcept : m_vec(std::move(_copy.m_vec)) {}
    NIX_INLINE Vector(const __nixFloat4& _copy) : m_vec(_copy) {}
    NIX_INLINE Vector(__nixFloat4&& _copy) noexcept : m_vec(std::move(_copy)) {}

    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    NIX_INLINE void Print() const
    {
        nixFloat *val = (nixFloat*)&m_vec;
        printf("vec[%.4f, %.4f, %.4f, %.4f]\n", val[0], val[1], val[2], val[3]);
    }

    NIX_INLINE void Print3() const
    {
        nixFloat *val = (nixFloat*)&m_vec;
        printf("vec[%.4f, %.4f, %.4f]\n", val[0], val[1], val[2]);
    }
#endif

    //////////////////////////////////////////////////////////////////////////
    // Operators
    NIX_INLINE operator const __nixFloat4&() const { return m_vec; }

    NIX_INLINE Vector& operator= (const Vector& _v)
    {
        this->m_vec = _v.m_vec;
        return *this;
    }
    NIX_INLINE Vector& operator+=(const Vector& _v)
    {
        this->m_vec = VectorHelper::Add(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator-=(const Vector& _v)
    {
        this->m_vec = VectorHelper::Sub(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator*=(const Vector& _v)
    {
        this->m_vec = VectorHelper::Mul(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator/=(const Vector& _v)
    {
        this->m_vec = VectorHelper::Div(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator+=(const nixFloat& _s)
    {
        this->m_vec = VectorHelper::Add(this->m_vec, VectorHelper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator-=(const nixFloat& _s)
    {
        this->m_vec = VectorHelper::Sub(this->m_vec, VectorHelper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator*=(const nixFloat& _s)
    {
        this->m_vec = VectorHelper::Mul(this->m_vec, VectorHelper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator/=(const nixFloat& _s)
    {
        this->m_vec = VectorHelper::Div(this->m_vec, VectorHelper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator++()
    {
        this->m_vec = VectorHelper::Add(this->m_vec, VectorHelper::GetOne());
        return *this;
    }
    NIX_INLINE Vector& operator--()
    {
        this->m_vec = VectorHelper::Sub(this->m_vec, VectorHelper::GetOne());
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    // Vector3 Version: Means that there are some difference to properly work upon 3 elements
    NIX_INLINE Vector Dot3(const Vector& _other) const
    {
        return VectorHelper::Dot3(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector SquareLength3() const
    {
        return VectorHelper::SquareLength3(m_vec);
    }

    NIX_INLINE Vector Length3() const
    {
        return VectorHelper::Length3(m_vec);
    }

    NIX_INLINE Vector Normalize3() const
    {
        return VectorHelper::Normalize3(m_vec);
    }

    NIX_INLINE Vector Distance3(const Vector& _other) const
    {
        return VectorHelper::Distance3(m_vec, _other.m_vec);
    }

    //////////////////////////////////////////////////////////////////////////
    // Both Vector3 and Vector4 Version (even possible)
    NIX_INLINE Vector Abs() const
    {
        return VectorHelper::Abs(m_vec);
    }

    NIX_INLINE Vector Floor() const
    {
        return VectorHelper::Floor(m_vec);
    }

    NIX_INLINE Vector Ceil() const
    {
        return VectorHelper::Ceil(m_vec);
    }

    // Computes and returns (this * _vecToMul) + _vecToAdd.
    NIX_INLINE Vector MulAdd(const Vector& _vecToMul, const Vector& _vecToAdd) const
    {
        return VectorHelper::MulAdd(m_vec, _vecToMul.m_vec, _vecToAdd.m_vec);
    }

    NIX_INLINE Vector Dot(const Vector& _other) const
    {
        return VectorHelper::Dot(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector SquareLength() const
    {
        return VectorHelper::SquareLength(m_vec);
    }

    NIX_INLINE Vector Length() const
    {
        return VectorHelper::Length(m_vec);
    }

    NIX_INLINE Vector SquareDistance(const Vector& _other) const
    {
        return VectorHelper::SquareDistance(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Distance(const Vector& _other) const
    {
        return VectorHelper::Distance(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Cross(const Vector& _other) const
    {
        return VectorHelper::Cross(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Mod(const Vector& _other) const
    {
        return VectorHelper::Mod(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Clamp(const Vector& _min, const Vector& _max) const
    {
        return VectorHelper::Clamp(m_vec, _min.m_vec, _max.m_vec);
    }

    NIX_INLINE Vector Normalize() const
    {
        return VectorHelper::Normalize(m_vec);
    }

    NIX_INLINE Vector Min(const Vector& _other) const
    {
        return VectorHelper::Min(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Max(const Vector& _other) const
    {
        return VectorHelper::Max(m_vec, _other.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector LerpTo(const Vector& _to, const Vector& _time) const
    {
        return VectorHelper::Lerp(m_vec, _to.m_vec, _time.m_vec);
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector LerpFrom(const Vector& _from, const Vector& _time) const
    {
        return VectorHelper::Lerp(_from.m_vec, m_vec, _time.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector LerpTo(const Vector& _to, const nixFloat& _time) const
    {
        return LerpTo(_to, VectorHelper::Splat(_time));
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector LerpFrom(const Vector& _from, const nixFloat& _time) const
    {
        return LerpFrom(_from, VectorHelper::Splat(_time));
    }

    NIX_INLINE Vector InverseLerp(const Vector& _min, const Vector& _max) const
    {
        return VectorHelper::InverseLerp(m_vec, _min.m_vec, _max.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector StepTo(const Vector& _to, const Vector& _time) const
    {
        return VectorHelper::Step(m_vec, _to.m_vec, _time.m_vec);
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector StepFrom(const Vector& _from, const Vector& _time) const
    {
        return VectorHelper::Step(_from.m_vec, m_vec, _time.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector StepTo(const Vector& _to, const nixFloat& _time) const
    {
        return StepTo(_to, VectorHelper::Splat(_time));
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector StepFrom(const Vector& _from, const nixFloat& _time) const
    {
        return StepFrom(_from, VectorHelper::Splat(_time));
    }


    //////////////////////////////////////////////////////////////////////////
    // Utility functions
    NIX_INLINE Vector GetX() const
    {
        return _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(0, 0, 0, 0));
    }

    NIX_INLINE Vector GetY() const
    {
        return _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(1, 1, 1, 1));
    }

    NIX_INLINE Vector GetZ() const
    {
        return _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(2, 2, 2, 2));
    }

    NIX_INLINE Vector GetW() const
    {
        return _mm_shuffle_ps(m_vec, m_vec, _MM_SHUFFLE(3, 3, 3, 3));
    }

    // From  [a,b,c,d ] To  [b,c,d,a]
    NIX_INLINE Vector Rotate() const
    {
        return _mm_shuffle_ps(m_vec, m_vec, 0x39);    
    }


private:
    friend class VectorHelper;
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

    __nixFloat4 m_vec;
};


//////////////////////////////////////////////////////////////////////////
// Operators

// operator+
NIX_INLINE Vector operator+ (const Vector& _v, nixFloat _s)
{
    return VectorHelper::Add(_v.m_vec, VectorHelper::Splat(_s));
}

NIX_INLINE Vector operator+ (nixFloat _s, const Vector& _v)
{
    return VectorHelper::Add(VectorHelper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector operator+ (const Vector& _a, const Vector& _b)
{
    return VectorHelper::Add(_a.m_vec, _b.m_vec);
}

//operator-
NIX_INLINE Vector operator- (const Vector& _v, nixFloat _s)
{
    return VectorHelper::Sub(_v.m_vec, VectorHelper::Splat(_s));
}

NIX_INLINE Vector operator- (nixFloat _s, const Vector& _v)
{
    return VectorHelper::Sub(VectorHelper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector operator- (const Vector& _a, const Vector& _b)
{
    return VectorHelper::Sub(_a.m_vec, _b.m_vec);
}

//operator*
NIX_INLINE Vector operator* (const Vector& _v, nixFloat _s)
{
    return VectorHelper::Mul(_v.m_vec, VectorHelper::Splat(_s));
}

NIX_INLINE Vector operator* (nixFloat _s, const Vector& _v)
{
    return VectorHelper::Mul(VectorHelper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector operator* (const Vector& _a, const Vector& _b)
{
    return VectorHelper::Mul(_a.m_vec, _b.m_vec);
}

//operator/
NIX_INLINE Vector  operator/ (const Vector& _v, nixFloat _s)
{
    return VectorHelper::Div(_v.m_vec, VectorHelper::Splat(_s));
}

NIX_INLINE Vector  operator/ (nixFloat _s, const Vector& _v)
{
    return VectorHelper::Div(VectorHelper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector  operator/ (const Vector& _a, const Vector& _b)
{
    return VectorHelper::Div(_a.m_vec, _b.m_vec);
}

// Unary constant operators
NIX_INLINE Vector  operator- (const Vector& _v)
{
    return _mm_sub_ps(VectorHelper::GetZero(), _v.m_vec);
}

NIX_INLINE Vector  operator++ (const Vector& _v, nixS32)
{
    return _mm_add_ps(_v.m_vec, VectorHelper::GetOne());
}

NIX_INLINE Vector  operator-- (const Vector& _v, nixS32)
{
    return _mm_sub_ps(_v.m_vec, VectorHelper::GetOne());
}

NIX_INLINE nixBool operator==(const Vector& _lhs, const Vector& _rhs)
{
    const __nixFloat4 equal = _mm_cmpeq_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE nixBool operator!=(const Vector& _lhs, const Vector& _rhs)
{
    const __nixFloat4 equal = _mm_cmpneq_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE nixBool operator< (const Vector& _lhs, const Vector& _rhs)
{
    const __nixFloat4 equal = _mm_cmplt_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE nixBool operator> (const Vector& _lhs, const Vector& _rhs)
{
    const __nixFloat4 equal = _mm_cmpgt_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE nixBool operator<=(const Vector& _lhs, const Vector& _rhs)
{
    const __nixFloat4 equal = _mm_cmple_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE nixBool operator>=(const Vector& _lhs, const Vector& _rhs)
{
    const __nixFloat4 equal = _mm_cmpge_ps(_lhs.m_vec, _rhs.m_vec);
    const nixS16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}


NIX_NAMESPACE_END