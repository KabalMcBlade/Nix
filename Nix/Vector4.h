#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "MathAligned.h"
#include "BasicMathFunctions.h"
#include "Scalar.h"


NIX_NAMESPACE_BEGIN


class Vector4 : public MathBase<16, Vector4>
{
public:
    //////////////////////////////////////////////////////////////////////////
    // Constructors
	NIX_INLINE Vector4() { m_vec = kZero; }
	NIX_INLINE Vector4(const Scalar& _x, const Scalar& _y, const Scalar& _z, const Scalar& _w) { m_vec = MathFunctions::Set(_x, _y, _z, _w); }
	NIX_INLINE Vector4(const Scalar& _v) { m_vec = MathFunctions::Splat(_v); }
	NIX_INLINE Vector4(const Vector4& _copy) { m_vec = _copy; }
	NIX_INLINE Vector4(Vector4&& _copy) noexcept { m_vec = std::move(_copy); }
	NIX_INLINE Vector4(const float128& _copy) { m_vec = _copy; }
	NIX_INLINE Vector4(float128&& _copy) noexcept { m_vec = std::move(_copy); }


    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    friend NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Vector4& _v);
#endif

    //////////////////////////////////////////////////////////////////////////
    // Operators

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
    NIX_INLINE Vector4& operator+=(const Scalar& _s)
    {
        this->m_vec = MathFunctions::Add(this->m_vec, _s);
        return *this;
    }
    NIX_INLINE Vector4& operator-=(const Scalar& _s)
    {
        this->m_vec = MathFunctions::Sub(this->m_vec, _s);
        return *this;
    }
    NIX_INLINE Vector4& operator*=(const Scalar& _s)
    {
        this->m_vec = MathFunctions::Mul(this->m_vec, _s);
        return *this;
    }
    NIX_INLINE Vector4& operator/=(const Scalar& _s)
    {
        this->m_vec = MathFunctions::Div(this->m_vec, _s);
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

	NIX_INLINE Vector4 SquareDistance3(const Vector4& _other) const
	{
		return MathFunctions::SquareDistance3(m_vec, _other);
	}

    NIX_INLINE Vector4 Distance3(const Vector4& _other) const
    {
        return MathFunctions::Distance3(m_vec, _other);
    }

    //////////////////////////////////////////////////////////////////////////
    // Vector4 Version: Means that there are some difference to properly work upon 4 elements

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

	NIX_INLINE Vector4 Normalize() const
	{
		return MathFunctions::Normalize(m_vec);
	}

	NIX_INLINE Vector4 SquareDistance(const Vector4& _other) const
	{
		return MathFunctions::SquareDistance(m_vec, _other);
	}

	NIX_INLINE Vector4 Distance(const Vector4& _other) const
	{
		return MathFunctions::Distance(m_vec, _other);
	}

	//////////////////////////////////////////////////////////////////////////
	// Both Vector3 and Vector4 Version 
    NIX_INLINE Vector4 Cross(const Vector4& _other) const
    {
        return MathFunctions::Cross(m_vec, _other);
    }

private:
    friend class Quaternion;
    friend class Matrix4x4;

    // for global operators
    friend NIX_INLINE Vector4 operator+ (const Vector4& _v, const Scalar& _s);
    friend NIX_INLINE Vector4 operator+ (const Scalar& _s, const Vector4& _v);
    friend NIX_INLINE Vector4 operator+ (const Vector4& _a, const Vector4& _b);
    friend NIX_INLINE Vector4 operator- (const Vector4& _v, const Scalar& _s);
    friend NIX_INLINE Vector4 operator- (const Scalar& _s, const Vector4& _v);
    friend NIX_INLINE Vector4 operator- (const Vector4& _a, const Vector4& _b);
    friend NIX_INLINE Vector4 operator* (const Vector4& _v, const Scalar& _s);
    friend NIX_INLINE Vector4 operator* (const Scalar& _s, const Vector4& _v);
    friend NIX_INLINE Vector4 operator* (const Vector4& _a, const Vector4& _b);
    friend NIX_INLINE Vector4 operator* (const Vector4& _a, const float128& _b);
    friend NIX_INLINE Vector4 operator* (const float128& _a, const Vector4& _b);
    friend NIX_INLINE Vector4 operator/ (const Vector4& _v, const Scalar& _s);
    friend NIX_INLINE Vector4 operator/ (const Scalar& _s, const Vector4& _v);
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
NIX_INLINE Vector4 operator+ (const Vector4& _v, const Scalar& _s)
{
    return MathFunctions::Add(_v, _s);
}

NIX_INLINE Vector4 operator+ (const Scalar& _s, const Vector4& _v)
{
    return MathFunctions::Add(_s, _v);
}

NIX_INLINE Vector4 operator+ (const Vector4& _a, const Vector4& _b)
{
    return MathFunctions::Add(_a, _b);
}

//operator-
NIX_INLINE Vector4 operator- (const Vector4& _v, const Scalar& _s)
{
    return MathFunctions::Sub(_v, _s);
}

NIX_INLINE Vector4 operator- (const Scalar& _s, const Vector4& _v)
{
    return MathFunctions::Sub(_s, _v);
}

NIX_INLINE Vector4 operator- (const Vector4& _a, const Vector4& _b)
{
    return MathFunctions::Sub(_a, _b);
}

//operator*
NIX_INLINE Vector4 operator* (const Vector4& _v, const Scalar& _s)
{
    return MathFunctions::Mul(_v, _s);
}

NIX_INLINE Vector4 operator* (const Scalar& _s, const Vector4& _v)
{
    return MathFunctions::Mul(_s, _v);
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
NIX_INLINE Vector4  operator/ (const Vector4& _v, const Scalar& _s)
{
    return MathFunctions::Div(_v, _s);
}

NIX_INLINE Vector4  operator/ (const Scalar& _s, const Vector4& _v)
{
    return MathFunctions::Div(_s, _v);
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
	Boolean res = (_lhs == _rhs);
	return res.IsTrue();
}

NIX_INLINE bool operator!=(const Vector4& _lhs, const Vector4& _rhs)
{
	Boolean res = (_lhs != _rhs);
	return res.IsTrue();
}

NIX_INLINE bool operator< (const Vector4& _lhs, const Vector4& _rhs)
{
	Boolean res = (_lhs < _rhs);
	return res.IsTrue();
}

NIX_INLINE bool operator> (const Vector4& _lhs, const Vector4& _rhs)
{
	Boolean res = (_lhs > _rhs);
	return res.IsTrue();
}

NIX_INLINE bool operator<=(const Vector4& _lhs, const Vector4& _rhs)
{
	Boolean res = (_lhs <= _rhs);
	return res.IsTrue();
}

NIX_INLINE bool operator>=(const Vector4& _lhs, const Vector4& _rhs)
{
	Boolean res = (_lhs >= _rhs);
	return res.IsTrue();
}


NIX_NAMESPACE_END