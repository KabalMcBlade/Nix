#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "Helper.h"

NIX_NAMESPACE_BEGIN


/*
    This cover both vector3 and vector4
    For the vector3 version, just referring to the function having the number "3" at the end, like Dot3
*/

NIX_ALIGN_16 class Vector4
{
public:
    //////////////////////////////////////////////////////////////////////////
    // Constructors
    NIX_INLINE Vector4() : m_vec(kZero) {}
    NIX_INLINE Vector4(float _x, float _y, float _z) : m_vec(Helper::Set(_x, _y, _z, 0.0f)) {}
    NIX_INLINE Vector4(float _x, float _y, float _z, float _w) : m_vec(Helper::Set(_x, _y, _z, _w)) {}
    NIX_INLINE Vector4(float _v) : m_vec(Helper::Splat(_v)) {}
    NIX_INLINE Vector4(const Vector4& _copy) : m_vec(_copy.m_vec) {}
    NIX_INLINE Vector4(Vector4&& _copy) noexcept : m_vec(std::move(_copy.m_vec)) {}
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

    NIX_INLINE Vector4& operator= (const Vector4& _v)
    {
        this->m_vec = _v.m_vec;
        return *this;
    }
    NIX_INLINE Vector4& operator+=(const Vector4& _v)
    {
        this->m_vec = Helper::Add(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector4& operator-=(const Vector4& _v)
    {
        this->m_vec = Helper::Sub(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector4& operator*=(const Vector4& _v)
    {
        this->m_vec = Helper::Mul(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector4& operator/=(const Vector4& _v)
    {
        this->m_vec = Helper::Div(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector4& operator+=(const float& _s)
    {
        this->m_vec = Helper::Add(this->m_vec, Helper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector4& operator-=(const float& _s)
    {
        this->m_vec = Helper::Sub(this->m_vec, Helper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector4& operator*=(const float& _s)
    {
        this->m_vec = Helper::Mul(this->m_vec, Helper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector4& operator/=(const float& _s)
    {
        this->m_vec = Helper::Div(this->m_vec, Helper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector4& operator++()
    {
        this->m_vec = Helper::Add(this->m_vec, kOne);
        return *this;
    }
    NIX_INLINE Vector4& operator--()
    {
        this->m_vec = Helper::Sub(this->m_vec, kOne);
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    // Vector3 Version: Means that there are some difference to properly work upon 3 elements
    NIX_INLINE Vector4 Dot3(const Vector4& _other) const
    {
        return Helper::Dot3(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector4 SquareLength3() const
    {
        return Helper::SquareLength3(m_vec);
    }

    NIX_INLINE Vector4 Length3() const
    {
        return Helper::Length3(m_vec);
    }

    NIX_INLINE Vector4 Normalize3() const
    {
        return Helper::Normalize3(m_vec);
    }

    NIX_INLINE Vector4 Distance3(const Vector4& _other) const
    {
        return Helper::Distance3(m_vec, _other.m_vec);
    }

    //////////////////////////////////////////////////////////////////////////
    // Both Vector3 and Vector4 Version (even possible)
    NIX_INLINE Vector4 Abs() const
    {
        return Helper::Abs(m_vec);
    }

    NIX_INLINE Vector4 Floor() const
    {
        return Helper::Floor(m_vec);
    }

    NIX_INLINE Vector4 Ceil() const
    {
        return Helper::Ceil(m_vec);
    }

    // Computes and returns (this * _vecToMul) + _vecToAdd.
    NIX_INLINE Vector4 MulAdd(const Vector4& _vecToMul, const Vector4& _vecToAdd) const
    {
        return Helper::MulAdd(m_vec, _vecToMul.m_vec, _vecToAdd.m_vec);
    }

    NIX_INLINE Vector4 Dot(const Vector4& _other) const
    {
        return Helper::Dot(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector4 SquareLength() const
    {
        return Helper::SquareLength(m_vec);
    }

    NIX_INLINE Vector4 Length() const
    {
        return Helper::Length(m_vec);
    }

    NIX_INLINE Vector4 SquareDistance(const Vector4& _other) const
    {
        return Helper::SquareDistance(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector4 Distance(const Vector4& _other) const
    {
        return Helper::Distance(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector4 Cross(const Vector4& _other) const
    {
        return Helper::Cross(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector4 Mod(const Vector4& _other) const
    {
        return Helper::Mod(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector4 Clamp(const Vector4& _min, const Vector4& _max) const
    {
        return Helper::Clamp(m_vec, _min.m_vec, _max.m_vec);
    }

    NIX_INLINE Vector4 Normalize() const
    {
        return Helper::Normalize(m_vec);
    }

    NIX_INLINE Vector4 Min(const Vector4& _other) const
    {
        return Helper::Min(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector4 Max(const Vector4& _other) const
    {
        return Helper::Max(m_vec, _other.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector4 LerpTo(const Vector4& _to, const Vector4& _time) const
    {
        return Helper::Lerp(m_vec, _to.m_vec, _time.m_vec);
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector4 LerpFrom(const Vector4& _from, const Vector4& _time) const
    {
        return Helper::Lerp(_from.m_vec, m_vec, _time.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector4 LerpTo(const Vector4& _to, const float& _time) const
    {
        return LerpTo(_to, Helper::Splat(_time));
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector4 LerpFrom(const Vector4& _from, const float& _time) const
    {
        return LerpFrom(_from, Helper::Splat(_time));
    }

    NIX_INLINE Vector4 InverseLerp(const Vector4& _min, const Vector4& _max) const
    {
        return Helper::InverseLerp(m_vec, _min.m_vec, _max.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector4 StepTo(const Vector4& _to, const Vector4& _time) const
    {
        return Helper::Step(m_vec, _to.m_vec, _time.m_vec);
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector4 StepFrom(const Vector4& _from, const Vector4& _time) const
    {
        return Helper::Step(_from.m_vec, m_vec, _time.m_vec);
    }

    // It means go FROM *this* vector TO *other* vector in T
    NIX_INLINE Vector4 StepTo(const Vector4& _to, const float& _time) const
    {
        return StepTo(_to, Helper::Splat(_time));
    }

    // It means go FROM *other* vector TO *this* vector in T
    NIX_INLINE Vector4 StepFrom(const Vector4& _from, const float& _time) const
    {
        return StepFrom(_from, Helper::Splat(_time));
    }


    //////////////////////////////////////////////////////////////////////////
    // Utility functions
    NIX_INLINE Vector4 GetX() const
    {
        return Swizzle::XXXX(m_vec);
    }

    NIX_INLINE Vector4 GetY() const
    {
        return Swizzle::YYYY(m_vec);
    }

    NIX_INLINE Vector4 GetZ() const
    {
        return Swizzle::ZZZZ(m_vec);
    }

    NIX_INLINE Vector4 GetW() const
    {
        return Swizzle::WWWW(m_vec);
    }

    // From  [a,b,c,d ] To  [b,c,d,a]
    NIX_INLINE Vector4 Rotate() const
    {
        return _mm_shuffle_ps(m_vec, m_vec, 0x39);    
    }


private:
    friend struct Helper;
    friend class Quaternion;
    friend class Matrix;

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
    friend NIX_INLINE Vector4 operator*(const Matrix& _m, const Vector4& _v);
    friend NIX_INLINE Vector4 operator*(const Vector4& _v, const Matrix& _m);

    float128 m_vec;
};


//////////////////////////////////////////////////////////////////////////
// Operators

#ifdef _DEBUG
NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Vector4& _v)
{
    float *val = (float*)&_v.m_vec;
    _os << "(" << val[0] << ", " << val[1] << ", " << val[2] << ", " << val[3] << ")";
    return _os;
}
#endif

// operator+
NIX_INLINE Vector4 operator+ (const Vector4& _v, float _s)
{
    return Helper::Add(_v.m_vec, Helper::Splat(_s));
}

NIX_INLINE Vector4 operator+ (float _s, const Vector4& _v)
{
    return Helper::Add(Helper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector4 operator+ (const Vector4& _a, const Vector4& _b)
{
    return Helper::Add(_a.m_vec, _b.m_vec);
}

//operator-
NIX_INLINE Vector4 operator- (const Vector4& _v, float _s)
{
    return Helper::Sub(_v.m_vec, Helper::Splat(_s));
}

NIX_INLINE Vector4 operator- (float _s, const Vector4& _v)
{
    return Helper::Sub(Helper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector4 operator- (const Vector4& _a, const Vector4& _b)
{
    return Helper::Sub(_a.m_vec, _b.m_vec);
}

//operator*
NIX_INLINE Vector4 operator* (const Vector4& _v, float _s)
{
    return Helper::Mul(_v.m_vec, Helper::Splat(_s));
}

NIX_INLINE Vector4 operator* (float _s, const Vector4& _v)
{
    return Helper::Mul(Helper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector4 operator* (const Vector4& _a, const Vector4& _b)
{
    return Helper::Mul(_a.m_vec, _b.m_vec);
}

NIX_INLINE Vector4 operator* (const Vector4& _a, const float128& _b)
{
    return Helper::Mul(_a.m_vec, _b);
}

NIX_INLINE Vector4 operator* (const float128& _a, const Vector4& _b)
{
    return Helper::Mul(_a, _b.m_vec);
}


//operator/
NIX_INLINE Vector4  operator/ (const Vector4& _v, float _s)
{
    return Helper::Div(_v.m_vec, Helper::Splat(_s));
}

NIX_INLINE Vector4  operator/ (float _s, const Vector4& _v)
{
    return Helper::Div(Helper::Splat(_s), _v.m_vec);
}

NIX_INLINE Vector4  operator/ (const Vector4& _a, const Vector4& _b)
{
    return Helper::Div(_a.m_vec, _b.m_vec);
}

// Unary constant operators
NIX_INLINE Vector4  operator- (const Vector4& _v)
{
    return _mm_sub_ps(kZero, _v.m_vec);
}

NIX_INLINE Vector4  operator++ (const Vector4& _v, int32)
{
    return _mm_add_ps(_v.m_vec, kOne);
}

NIX_INLINE Vector4  operator-- (const Vector4& _v, int32)
{
    return _mm_sub_ps(_v.m_vec, kOne);
}

NIX_INLINE bool operator==(const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmpeq_ps(_lhs.m_vec, _rhs.m_vec);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE bool operator!=(const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmpneq_ps(_lhs.m_vec, _rhs.m_vec);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE bool operator< (const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmplt_ps(_lhs.m_vec, _rhs.m_vec);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE bool operator> (const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmpgt_ps(_lhs.m_vec, _rhs.m_vec);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE bool operator<=(const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmple_ps(_lhs.m_vec, _rhs.m_vec);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}

NIX_INLINE bool operator>=(const Vector4& _lhs, const Vector4& _rhs)
{
    const float128 equal = _mm_cmpge_ps(_lhs.m_vec, _rhs.m_vec);
    const int16 mask = _mm_movemask_ps(equal);
    return (mask == 0xffffffff);
}


NIX_NAMESPACE_END