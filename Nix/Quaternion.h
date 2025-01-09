// Copyright (c) 2018-2025 Michele Condo'
// File: C:\Projects\Nix\Nix\Quaternion.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.


#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "MathAligned.h"
#include "BasicMathFunctions.h"
#include "Trigonometry.h"
#include "Matrix4x4.h"


NIX_NAMESPACE_BEGIN


class Quaternion : public MathBase<16, Quaternion>
{
public:
	NIX_INLINE Quaternion() { m_vec = MathFunctions::Set(0.0f, 0.0f, 0.0f, 1.0f); }
	NIX_INLINE Quaternion(const Scalar& _x, const Scalar& _y, const Scalar& _z, const Scalar& _w) { m_vec = MathFunctions::Set(_x, _y, _z, _w); }
	NIX_INLINE Quaternion(const Quaternion& _copy) { m_vec = _copy; }
	NIX_INLINE Quaternion(Quaternion&& _copy) noexcept { m_vec = std::move(_copy); }
	NIX_INLINE Quaternion(const float128& _copy) { m_vec = _copy; }
	NIX_INLINE Quaternion(float128&& _copy) noexcept { m_vec = std::move(_copy); }
    NIX_INLINE Quaternion(const Scalar& _radians, const Vector4& _axis) { SetFromAngleAxis(_radians, _axis); }
    NIX_INLINE Quaternion(const Scalar& _pitch, const Scalar& _yaw, const Scalar& _roll) { SetFromPitchYawRoll(_pitch, _yaw, _roll); }
    NIX_INLINE Quaternion(const Matrix4x4& _rotMatrix) { SetFromMatrix(_rotMatrix); }

    //////////////////////////////////////////////////////////////////////////
    // Operators

    NIX_INLINE Quaternion& operator=(const Quaternion& _q)
    {
        this->m_vec = _q.m_vec;
        return *this;
    }

    NIX_INLINE Quaternion& operator*=(const Scalar& _s)
    {
        this->m_vec = MathFunctions::Mul(this->m_vec, MathFunctions::Splat(_s));
        return *this;
    }

    NIX_INLINE Quaternion& operator/=(const Scalar& _s)
    {
        this->m_vec = MathFunctions::Div(this->m_vec, MathFunctions::Splat(_s));
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    // Functions

	// keep floats here, or I have to do more computation just to set the values
    NIX_INLINE void SetFromPitchYawRoll(const float& _pitch, const float& _yaw, const float& _roll)
    {
		static const Float128 sign = { { {  -1.0f, 1.0f, -1.0f, 1.0f } } };

		const float128 angles = MathFunctions::Set(_pitch, _pitch, _roll, _yaw);
		const float128 halfAngles = MathFunctions::Mul(angles, kOneHalfVec4);

		float128 sine;
		float128 cosine;
		Trigonometry::SinCos(halfAngles, &sine, &cosine);

		const float128 cx_sy_sz_sw = MathFunctions::Permute<B_X, A_Y, A_Z, A_W>(sine, cosine);
		const float128 sx_cy_cz_cw = MathFunctions::Permute<B_X, A_Y, A_Z, A_W>(cosine, sine);

		const float128 L0 = MathFunctions::Swizzle<Z, Z, Y, Z>(cosine);
		const float128 L1 = MathFunctions::Swizzle<W, W, W, Y>(cosine);
		const float128 R0 = MathFunctions::Swizzle<Z, Z, Y, Z>(sine);
		const float128 R1 = MathFunctions::Swizzle<W, W, W, Y>(sine);

		const float128 left = MathFunctions::Mul(MathFunctions::Mul(cx_sy_sz_sw, L0), L1);
		const float128 right = MathFunctions::Mul(MathFunctions::Mul(sx_cy_cz_cw, R0), R1);

		const float128 adjust = MathFunctions::Mul(right, sign);
		const float128 rotate = MathFunctions::Add(left, adjust);

		m_vec = MathFunctions::Swizzle<Y, Z, W, X>(rotate);
    }

	// x is the canonical right vector
	// y is the canonical forward vector
	// z is the canonical up vector
    NIX_INLINE void SetFromAngleAxis(const Scalar& _radians, const Vector4& _axis)
    {
        float128 sin, cos;

        Trigonometry::SinCos(MathFunctions::Mul(_radians, MathFunctions::Splat(0.5f)), &sin, &cos);

        const float128 quat = MathFunctions::Mul(_axis, sin);
        const float128 high = _mm_unpackhi_ps(quat, cos);  // [_ _ 1 z]
		m_vec = _mm_movelh_ps(quat, high);             // [1 z y x]
    }

	// x is the canonical right vector
	// y is the canonical forward vector
	// z is the canonical up vector
    NIX_INLINE void SetFromAngleAxis(const Scalar& _radians, Scalar _x, Scalar _y, Scalar _z)
    {
        SetFromAngleAxis(_radians, Vector4(_x, _y, _z, 0.0f));
    }

    NIX_INLINE void SetFromMatrix(const Matrix4x4& _matrix)
    {
		const float128 col0 = _matrix[0];
		const float128 col1 = _matrix[1];
		const float128 col2 = _matrix[2];

		const float128 xx_yy = MathFunctions::Select(col0, col1, kSelectY);
		float128 xx_yy_zz_xx = MathFunctions::Swizzle<X, Y, X, X>(xx_yy);
		xx_yy_zz_xx = MathFunctions::Select(xx_yy_zz_xx, col2, kSelectZ);
		const float128 yy_zz_xx_yy = MathFunctions::Swizzle<Y, Z, X, Y>(xx_yy_zz_xx);
		const float128 zz_xx_yy_zz = MathFunctions::Swizzle<Z, X, Y, Z>(xx_yy_zz_xx);

		const float128 diagSum = MathFunctions::Add(MathFunctions::Add(xx_yy_zz_xx, yy_zz_xx_yy), zz_xx_yy_zz);
		const float128 diagDiff = MathFunctions::Sub(MathFunctions::Sub(xx_yy_zz_xx, yy_zz_xx_yy), zz_xx_yy_zz);
		const float128 radicand = MathFunctions::Add(MathFunctions::Select(diagDiff, diagSum, kSelectW), MathFunctions::Splat(1.0f));
		const float128 invSqrt = MathFunctions::NewtonRaphsonReciprocalSquareRoot(radicand);


		float128 zy_xz_yx = MathFunctions::Select(col0, col1, kSelectZ);
		zy_xz_yx = MathFunctions::Swizzle<Z, Z, Y, X>(zy_xz_yx);
		zy_xz_yx = MathFunctions::Select(zy_xz_yx, MathFunctions::Swizzle<X, X, X, X>(col2), kSelectY);
		float128 yz_zx_xy = MathFunctions::Select(col0, col1, kSelectX);
		yz_zx_xy = MathFunctions::Swizzle<X, Z, X, X>(yz_zx_xy);
		yz_zx_xy = MathFunctions::Select(yz_zx_xy, MathFunctions::Swizzle<Y, Y, Y, Y>(col2), kSelectX);

		const float128 sum = MathFunctions::Add(zy_xz_yx, yz_zx_xy);
		const float128 diff = MathFunctions::Sub(zy_xz_yx, yz_zx_xy);

		const float128 scale = MathFunctions::Mul(invSqrt, MathFunctions::Splat(0.5f));

		float128 res0 = MathFunctions::Swizzle<X, Z, Y, X>(sum);
		res0 = MathFunctions::Select(res0, MathFunctions::Swizzle<X, X, X, X>(diff), kSelectW);
		float128 res1 = MathFunctions::Swizzle<Z, X, X, X>(sum);
		res1 = MathFunctions::Select(res1, MathFunctions::Swizzle<Y, Y, Y, Y>(diff), kSelectW);
		float128 res2 = MathFunctions::Swizzle<Y, X, X, X>(sum);
		res2 = MathFunctions::Select(res2, MathFunctions::Swizzle<Z, Z, Z, Z>(diff), kSelectW);
		float128 res3 = diff;
		res0 = MathFunctions::Select(res0, radicand, kSelectX);
		res1 = MathFunctions::Select(res1, radicand, kSelectY);
		res2 = MathFunctions::Select(res2, radicand, kSelectZ);
		res3 = MathFunctions::Select(res3, radicand, kSelectW);
		res0 = MathFunctions::Mul(res0, MathFunctions::Swizzle<X, X, X, X>(scale));
		res1 = MathFunctions::Mul(res1, MathFunctions::Swizzle<Y, Y, Y, Y>(scale));
		res2 = MathFunctions::Mul(res2, MathFunctions::Swizzle<Z, Z, Z, Z>(scale));
		res3 = MathFunctions::Mul(res3, MathFunctions::Swizzle<W, W, W, W>(scale));

		const float128 xx = MathFunctions::Swizzle<X, X, X, X>(col0);
		const float128 yy = MathFunctions::Swizzle<Y, Y, Y, Y>(col1);
		const float128 zz = MathFunctions::Swizzle<Z, Z, Z, Z>(col2);

		float128 res = MathFunctions::Select(res0, res1, _mm_cmpgt_ps(yy, xx));
		res = MathFunctions::Select(res, res2, _mm_and_ps(_mm_cmpgt_ps(zz, xx), _mm_cmpgt_ps(zz, yy)));
		res = MathFunctions::Select(res, res3, _mm_cmpgt_ps(MathFunctions::Swizzle<X, X, X, X>(diagSum), _mm_setzero_ps()));

		m_vec = (res);
    }

    NIX_INLINE Vector4 Length() const
    {
        return MathFunctions::Sqrt(MathFunctions::Dot(m_vec, m_vec));
    }

    NIX_INLINE Quaternion Normalize() const
    {
        const Vector4 len = Length();
		const Vector4 zero = _mm_setzero_ps();

        if (len <= zero)
        {
            return Quaternion();
        }
        else
        {
            const Vector4 oneOverLen(1.0f / len);
            return MathFunctions::Mul(oneOverLen, m_vec);
        }
		
		//return Helper::Normalize(m_vec);
    }

    NIX_INLINE Vector4 Dot(const Quaternion& _other) const
    {
        return MathFunctions::Dot(m_vec, _other.m_vec);
    }

    NIX_INLINE Quaternion Slerp(const Quaternion& _other, const float& _time) const
	{
		static const Vector4 zero = _mm_setzero_ps();
		static const Vector4 one = MathFunctions::SplatOne();
		const Vector4 lerpEpsilon = one - NIX_EPSILON;

        Quaternion other = _other;

		Vector4 cosTheta = Dot(_other);
		Boolean res = cosTheta <= zero;

        if (res.IsTrue())
        {
            other = -_other;
            cosTheta = -cosTheta;
        }

		res = cosTheta > lerpEpsilon;
        if (res.IsTrue())
        {
            return LerpTo(other, _time);
        }
        else
        {
            float angle = std::acos(Scalar(cosTheta));

            float a = std::sinf((1.0f - _time) * angle);
            float b = std::sinf(_time * angle);
            float c = std::sinf(angle);

            const float128 ax = MathFunctions::Mul(MathFunctions::Splat(a), m_vec);
            const float128 by = MathFunctions::Mul(MathFunctions::Splat(b), other);

            const float128 q = MathFunctions::Div(MathFunctions::Add(ax, by), MathFunctions::Splat(c));
            return q;
        }
    }

    NIX_INLINE Quaternion Conjugate() const
    {
        return MathFunctions::Mul(m_vec, MathFunctions::Set(-1.0f, -1.0f, -1.0f, 1.0f));
    }

    NIX_INLINE Quaternion Inverse() const
    {
        Vector4 dot = Dot(m_vec);
        return Conjugate() / dot;
    }

    NIX_INLINE Matrix4x4 ToMatrix() const
    {
        const float qX = MathFunctions::ExtractX(m_vec);
        const float qY = MathFunctions::ExtractY(m_vec);
        const float qZ = MathFunctions::ExtractZ(m_vec);
        const float qW = MathFunctions::ExtractW(m_vec);

        const float XX = qX * qX;
        const float YY = qY * qY;
        const float ZZ = qZ * qZ;
        const float XY = qX * qY;
        const float XZ = qX * qZ;
        const float YZ = qY * qZ;
        const float WX = qW * qX;
        const float WY = qW * qY;
        const float Wz = qW * qZ;

        /*  
        Matrix4x4 rotation(
            1.f - (YY + ZZ) * 2.0f,     (XY - Wz) * 2.0f,           (XZ + WY) * 2.0f,           0.f,
            (XY + Wz) * 2.0f,           1.f - (XX + ZZ) * 2.0f,     (YZ - WX) * 2.0f,           0.f,
            (XZ - WY) * 2.0f,           (YZ + WX) * 2.0f,           1.f - (XX + YY) * 2.0f,     0.f,
            0.f,                        0.f,                        0.f,                        1.f
        );
        */

        Matrix4x4 rotation(
            1.f - (YY + ZZ) * 2.0f,     (XY + Wz) * 2.0f,           (XZ - WY) * 2.0f,           0.f,
            (XY - Wz) * 2.0f,           1.f - (XX + ZZ) * 2.0f,     (YZ + WX) * 2.0f,           0.f,
            (XZ + WY) * 2.0f,           (YZ - WX) * 2.0f,           1.f - (XX + YY) * 2.0f,     0.f,
            0.f,                        0.f,                        0.f,                        1.f
        );

        return rotation;
    }

    NIX_INLINE Matrix4x4 ToMatrix(const Vector4& _translation) const
    {
        const float vX = MathFunctions::ExtractX(_translation);
        const float vY = MathFunctions::ExtractY(_translation);
        const float vZ = MathFunctions::ExtractZ(_translation);

        const float qX = MathFunctions::ExtractX(m_vec);
        const float qY = MathFunctions::ExtractY(m_vec);
        const float qZ = MathFunctions::ExtractZ(m_vec);
        const float qW = MathFunctions::ExtractW(m_vec);

        const float XX = qX * qX;
        const float YY = qY * qY;
        const float ZZ = qZ * qZ;
        const float XY = qX * qY;
        const float XZ = qX * qZ;
        const float YZ = qY * qZ;
        const float WX = qW * qX;
        const float WY = qW * qY;
        const float Wz = qW * qZ;

        /*
        Matrix4x4 rt(
            1.f - (YY + ZZ) * 2.0f,     (XY - Wz) * 2.0f,           (XZ + WY) * 2.0f,           vX,
            (XY + Wz) * 2.0f,           1.f - (XX + ZZ) * 2.0f,     (YZ - WX) * 2.0f,           vY,
            (XZ - WY) * 2.0f,           (YZ + WX) * 2.0f,           1.f - (XX + YY) * 2.0f,     vZ,
            0.f,                        0.f,                        0.f,                        1.f
        );
        */

        Matrix4x4 rt(
            1.f - (YY + ZZ) * 2.0f,     (XY + Wz) * 2.0f,           (XZ - WY) * 2.0f,           0.f,
            (XY - Wz) * 2.0f,           1.f - (XX + ZZ) * 2.0f,     (YZ + WX) * 2.0f,           0.f,
            (XZ + WY) * 2.0f,           (YZ - WX) * 2.0f,           1.f - (XX + YY) * 2.0f,     0.f,
            vX,                         vY,                         vZ,                         1.f
        );


        return rt;
    }

	//////////////////////////////////////////////////////////////////////////
	// Operators
	NIX_INLINE Quaternion operator- () const 
	{ 
		return MathFunctions::Sub(_mm_setzero_ps(), *this);
	}
	NIX_INLINE Quaternion operator+ (const Quaternion& _q) const 
	{ 
		return MathFunctions::Add(*this, _q);
	}
	NIX_INLINE Quaternion operator* (const Quaternion& _q)  const
	{
		const float128 mul0 = MathFunctions::Mul(*this, MathFunctions::Swizzle<W, Z, Y, X>(_q));
		const float128 mul1 = MathFunctions::Mul(*this, MathFunctions::Swizzle<Z, W, X, Y>(_q));
		const float128 mul2 = MathFunctions::Mul(*this, MathFunctions::Swizzle<Y, X, W, Z>(_q));
		const float128 mul3 = MathFunctions::Mul(*this, _q);

#if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		const float128 add00 = _mm_dp_ps(mul0, MathFunctions::Set(1.0f, 1.0f, -1.0f, 1.0f), 0xff);
		const float128 add01 = _mm_dp_ps(mul1, MathFunctions::Set(-1.0f, 1.0f, 1.0f, 1.0f), 0xff);
		const float128 add02 = _mm_dp_ps(mul2, MathFunctions::Set(1.0f, -1.0f, 1.0f, 1.0f), 0xff);
		const float128 add03 = _mm_dp_ps(mul3, MathFunctions::Set(-1.0f, -1.0f, -1.0f, 1.0f), 0xff);
#   else
		const float128 mul00 = MathFunctions::Mul(mul0, MathFunctions::Set(1.0f, 1.0f, -1.0f, 1.0f));
		const float128 mul01 = MathFunctions::Mul(mul1, MathFunctions::Set(-1.0f, 1.0f, 1.0f, 1.0f));
		const float128 mul02 = MathFunctions::Mul(mul2, MathFunctions::Set(1.0f, -1.0f, 1.0f, 1.0f));
		const float128 mul03 = MathFunctions::Mul(mul3, MathFunctions::Set(-1.0f, -1.0f, -1.0f, 1.0f));

		const float128 add0 = MathFunctions::Add(mul00, _mm_movehl_ps(mul00, mul00));
		const float128 add1 = MathFunctions::Add(mul01, _mm_movehl_ps(mul01, mul01));
		const float128 add2 = MathFunctions::Add(mul02, _mm_movehl_ps(mul02, mul02));
		const float128 add3 = MathFunctions::Add(mul03, _mm_movehl_ps(mul03, mul03));

		const float128 add00 = _mm_add_ss(add0, _mm_shuffle_ps(add0, add0, 1));
		const float128 add01 = _mm_add_ss(add1, _mm_shuffle_ps(add1, add1, 1));
		const float128 add02 = _mm_add_ss(add2, _mm_shuffle_ps(add2, add2, 1));
		const float128 add03 = _mm_add_ss(add3, _mm_shuffle_ps(add3, add3, 1));
#endif

		const float128 xxyy = _mm_shuffle_ps(add00, add01, _MM_SHUFFLE(0, 0, 0, 0));
		const float128 zzww = _mm_shuffle_ps(add02, add03, _MM_SHUFFLE(0, 0, 0, 0));

		return _mm_shuffle_ps(xxyy, zzww, _MM_SHUFFLE(2, 0, 2, 0));
	}
	NIX_INLINE Quaternion operator* (const Scalar& _s) const
	{
		return MathFunctions::Mul(*this, _s);
	}
	NIX_INLINE Quaternion operator/ (const Scalar& _s) const
	{ 
		return MathFunctions::Div(*this, _s);
	}
	NIX_INLINE Quaternion operator/ (const Quaternion& _q) const
	{ 
		return MathFunctions::Div(*this, _q);
	}
};

NIX_INLINE Vector4 operator* (const Vector4& _v, const Quaternion& _q)
{
	Quaternion inv = _q.Inverse();
	return inv * _v;
}

NIX_INLINE Vector4 operator* (const Quaternion& _q, const Vector4& _v)
{
	static const float128 two = MathFunctions::Splat(2.0f);

	const float128 q_wwww = MathFunctions::Swizzle<W, W, W, W>(_q);
	const float128 q_yzxw = MathFunctions::Swizzle<Y, Z, X, W>(_q);
	const float128 q_zxyw = MathFunctions::Swizzle<Z, X, Y, W>(_q);
	const float128 v_yzxw = MathFunctions::Swizzle<Y, Z, X, W>(_v);
	const float128 v_wyxz = MathFunctions::Swizzle<Z, X, Y, W>(_v);

	const float128 qv = MathFunctions::Sub(MathFunctions::Mul(q_yzxw, v_wyxz), MathFunctions::Mul(q_zxyw, v_yzxw));
	const float128 qv_yzxw = MathFunctions::Swizzle<Y, Z, X, W>(qv);
	const float128 qv_zxyw = MathFunctions::Swizzle<Z, X, Y, W>(qv);
	const float128 qqv = MathFunctions::Sub(MathFunctions::Mul(q_yzxw, qv_zxyw), MathFunctions::Mul(q_zxyw, qv_yzxw));

	const float128 mul0 = MathFunctions::Mul(qv, MathFunctions::Mul(q_wwww, two));
	const float128 mul1 = MathFunctions::Mul(qqv, two);

	return MathFunctions::Add(_v, MathFunctions::Add(mul0, mul1));
}


#ifdef _DEBUG
NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Quaternion& _q)
{
	float *val = (float*)&_q;
	_os << "(" << val[0] << ", " << val[1] << ", " << val[2] << ", " << val[3] << ")";
	return _os;
}
#endif

NIX_NAMESPACE_END