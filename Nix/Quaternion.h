#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "Helper.h"
#include "Trigonometry.h"
#include "Matrix4x4.h"

NIX_NAMESPACE_BEGIN


NIX_ALIGN_16 class Quaternion
{
public:
    NIX_INLINE Quaternion() : m_quat(Helper::Set(0.0f, 0.0f, 0.0f, 1.0f)) {}
    NIX_INLINE Quaternion(const Quaternion& _copy) : m_quat(_copy.m_quat) {}
    NIX_INLINE Quaternion(Quaternion&& _copy) noexcept : m_quat(std::move(_copy.m_quat)) {}
    NIX_INLINE Quaternion(const float128& _copy) : m_quat(_copy) {}
    NIX_INLINE Quaternion(float128&& _copy) noexcept : m_quat(std::move(_copy)) {}
    NIX_INLINE Quaternion(const Vector4& _copy) : m_quat(_copy) {}
    NIX_INLINE Quaternion(Vector4&& _copy) noexcept : m_quat(std::move(_copy)) {}
    NIX_INLINE Quaternion(float _x, float _y, float _z, float _w) : m_quat(Helper::Set(_x, _y, _z, _w)) { }
    NIX_INLINE Quaternion(const float& _radians, const Vector4& _axis) { SetFromAngleAxis(_radians, _axis); }
    NIX_INLINE Quaternion(const float& _pitch, const float& _yaw, const float& _roll) { SetFromPitchYawRoll(_pitch, _yaw, _roll); }
    NIX_INLINE Quaternion(const Matrix4x4& _rotMatrix) { SetFromMatrix(_rotMatrix); }

    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    friend NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Quaternion& _quat);
#endif

    //////////////////////////////////////////////////////////////////////////
    // Operators
	NIX_INLINE operator const float128&() const { return m_quat; }
	//NIX_INLINE operator float128() const { return m_quat; }

    NIX_INLINE Quaternion& operator=(const Quaternion& _q)
    {
        this->m_quat = _q.m_quat;
        return *this;
    }

    NIX_INLINE Quaternion& operator*=(float& _s)
    {
        this->m_quat = Helper::Mul(this->m_quat, Helper::Splat(_s));
        return *this;
    }

    NIX_INLINE Quaternion& operator/=(float& _s)
    {
        this->m_quat = Helper::Div(this->m_quat, Helper::Splat(_s));
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    // Functions
    NIX_INLINE void SetFromPitchYawRoll(const float& _pitch, const float& _yaw, const float& _roll)
    {
		static const Float128 sign = { { {  -1.0f, 1.0f, -1.0f, 1.0f } } };

		const float128 angles = Helper::Set(_pitch, _pitch, _roll, _yaw);
		const float128 halfAngles = Helper::Mul(angles, kOneHalfVec4);

		float128 sine;
		float128 cosine;
		Trigonometry::SinCos(halfAngles, &sine, &cosine);

		const float128 cx_sy_sz_sw = MathFunctions::Permute<B_X, A_Y, A_Z, A_W>(sine, cosine);
		const float128 sx_cy_cz_cw = MathFunctions::Permute<B_X, A_Y, A_Z, A_W>(cosine, sine);

		const float128 L0 = MathFunctions::Swizzle<Z, Z, Y, Z>(cosine);
		const float128 L1 = MathFunctions::Swizzle<W, W, W, Y>(cosine);
		const float128 R0 = MathFunctions::Swizzle<Z, Z, Y, Z>(sine);
		const float128 R1 = MathFunctions::Swizzle<W, W, W, Y>(sine);

		const float128 left = Helper::Mul(Helper::Mul(cx_sy_sz_sw, L0), L1);
		const float128 right = Helper::Mul(Helper::Mul(sx_cy_cz_cw, R0), R1);

		const float128 adjust = Helper::Mul(right, sign);
		const float128 rotate = Helper::Add(left, adjust);

		m_quat = MathFunctions::Swizzle<Y, Z, W, X>(rotate);
    }

	// x is the canonical right vector
	// y is the canonical forward vector
	// z is the canonical up vector
    NIX_INLINE void SetFromAngleAxis(const float& _radians, const Vector4& _axis)
    {
        float128 sin, cos;

        Trigonometry::SinCos(Helper::Mul(Helper::Splat(_radians), Helper::Splat(0.5f)), &sin, &cos);

        const float128 quat = Helper::Mul(_axis, sin);
        const float128 high = _mm_unpackhi_ps(quat, cos);  // [_ _ 1 z]
        m_quat = _mm_movelh_ps(quat, high);             // [1 z y x]
    }

	// x is the canonical right vector
	// y is the canonical forward vector
	// z is the canonical up vector
    NIX_INLINE void SetFromAngleAxis(const float& _radians, float _x, float _y, float _z)
    {
        SetFromAngleAxis(_radians, Vector4(_x, _y, _z));
    }

    NIX_INLINE void SetFromMatrix(const Matrix4x4& _matrix)
    {
		const float128 col0 = _matrix[0];
		const float128 col1 = _matrix[1];
		const float128 col2 = _matrix[2];

		const float128 xx_yy = Helper::Select(col0, col1, kSelectY);
		float128 xx_yy_zz_xx = MathFunctions::Swizzle<X, Y, X, X>(xx_yy);
		xx_yy_zz_xx = Helper::Select(xx_yy_zz_xx, col2, kSelectZ);
		const float128 yy_zz_xx_yy = MathFunctions::Swizzle<Y, Z, X, Y>(xx_yy_zz_xx);
		const float128 zz_xx_yy_zz = MathFunctions::Swizzle<Z, X, Y, Z>(xx_yy_zz_xx);

		const float128 diagSum = _mm_add_ps(_mm_add_ps(xx_yy_zz_xx, yy_zz_xx_yy), zz_xx_yy_zz);
		const float128 diagDiff = _mm_sub_ps(_mm_sub_ps(xx_yy_zz_xx, yy_zz_xx_yy), zz_xx_yy_zz);
		const float128 radicand = _mm_add_ps(Helper::Select(diagDiff, diagSum, kSelectW), _mm_set1_ps(1.0f));
		const float128 invSqrt = Helper::NewtonRaphsonReciprocalSquareRoot(radicand);


		float128 zy_xz_yx = Helper::Select(col0, col1, kSelectZ);
		zy_xz_yx = MathFunctions::Swizzle<Z, Z, Y, X>(zy_xz_yx);
		zy_xz_yx = Helper::Select(zy_xz_yx, MathFunctions::Swizzle<X, X, X, X>(col2), kSelectY);
		float128 yz_zx_xy = Helper::Select(col0, col1, kSelectX);
		yz_zx_xy = MathFunctions::Swizzle<X, Z, X, X>(yz_zx_xy);
		yz_zx_xy = Helper::Select(yz_zx_xy, MathFunctions::Swizzle<Y, Y, Y, Y>(col2), kSelectX);

		const float128 sum = _mm_add_ps(zy_xz_yx, yz_zx_xy);
		const float128 diff = _mm_sub_ps(zy_xz_yx, yz_zx_xy);

		const float128 scale = _mm_mul_ps(invSqrt, _mm_set1_ps(0.5f));

		float128 res0 = MathFunctions::Swizzle<X, Z, Y, X>(sum);
		res0 = Helper::Select(res0, MathFunctions::Swizzle<X, X, X, X>(diff), kSelectW);
		float128 res1 = MathFunctions::Swizzle<Z, X, X, X>(sum);
		res1 = Helper::Select(res1, MathFunctions::Swizzle<Y, Y, Y, Y>(diff), kSelectW);
		float128 res2 = MathFunctions::Swizzle<Y, X, X, X>(sum);
		res2 = Helper::Select(res2, MathFunctions::Swizzle<Z, Z, Z, Z>(diff), kSelectW);
		float128 res3 = diff;
		res0 = Helper::Select(res0, radicand, kSelectX);
		res1 = Helper::Select(res1, radicand, kSelectY);
		res2 = Helper::Select(res2, radicand, kSelectZ);
		res3 = Helper::Select(res3, radicand, kSelectW);
		res0 = _mm_mul_ps(res0, MathFunctions::Swizzle<X, X, X, X>(scale));
		res1 = _mm_mul_ps(res1, MathFunctions::Swizzle<Y, Y, Y, Y>(scale));
		res2 = _mm_mul_ps(res2, MathFunctions::Swizzle<Z, Z, Z, Z>(scale));
		res3 = _mm_mul_ps(res3, MathFunctions::Swizzle<W, W, W, W>(scale));

		const float128 xx = MathFunctions::Swizzle<X, X, X, X>(col0);
		const float128 yy = MathFunctions::Swizzle<Y, Y, Y, Y>(col1);
		const float128 zz = MathFunctions::Swizzle<Z, Z, Z, Z>(col2);

		float128 res = Helper::Select(res0, res1, _mm_cmpgt_ps(yy, xx));
		res = Helper::Select(res, res2, _mm_and_ps(_mm_cmpgt_ps(zz, xx), _mm_cmpgt_ps(zz, yy)));
		res = Helper::Select(res, res3, _mm_cmpgt_ps(MathFunctions::Swizzle<X, X, X, X>(diagSum), _mm_setzero_ps()));

		m_quat = (res);
    }

    NIX_INLINE Vector4 Length() const
    {
        return Helper::Sqrt(Helper::Dot(m_quat, m_quat));
    }

    NIX_INLINE Quaternion Normalize() const
    {
        const Vector4 vLen = Length();

        float len = 0;
        _mm_store_ss(&len, vLen);

        if (len <= 0.0f)
        {
            return Quaternion();
        }
        else
        {
            const Vector4 oneOverLen(1.0f / len);
            return Helper::Mul(oneOverLen, m_quat);
        }
		
		//return Helper::Normalize(m_quat);
    }

    NIX_INLINE Vector4 Dot(const Quaternion& _other) const
    {
        return Helper::Dot(m_quat, _other.m_quat);
    }

    // It means go FROM *this* quaternion TO *other* quaternion in T
    NIX_INLINE Vector4 LerpTo(const Quaternion& _to, const Vector4& _time) const
    {
        return Helper::Lerp(m_quat, _to.m_quat, _time);
    }

    // It means go FROM *other* quaternion TO *this* quaternion in T
    NIX_INLINE Vector4 LerpFrom(const Quaternion& _from, const Vector4& _time) const
    {
        return Helper::Lerp(_from.m_quat, m_quat, _time);
    }

    // It means go FROM *this* quaternion TO *other* quaternion in T
    NIX_INLINE Vector4 LerpTo(const Quaternion& _to, const float& _time) const
    {
        return LerpTo(_to, Helper::Splat(_time));
    }

    // It means go FROM *other* quaternion TO *this* quaternion in T
    NIX_INLINE Vector4 LerpFrom(const Quaternion& _from, const float& _time) const
    {
        return LerpFrom(_from, Helper::Splat(_time));
    }

    // It means go FROM *this* quaternion TO *other* quaternion in T
    NIX_INLINE Vector4 StepTo(const Quaternion& _to, const Vector4& _time) const
    {
        return Helper::Step(m_quat, _to.m_quat, _time);
    }

    // It means go FROM *other* quaternion TO *this* quaternion in T
    NIX_INLINE Vector4 StepFrom(const Quaternion& _from, const Vector4& _time) const
    {
        return Helper::Step(_from.m_quat, m_quat, _time);
    }

    // It means go FROM *this* quaternion TO *other* quaternion in T
    NIX_INLINE Vector4 StepTo(const Quaternion& _to, const float& _time) const
    {
        return StepTo(_to, Helper::Splat(_time));
    }

    // It means go FROM *other* quaternion TO *this* quaternion in T
    NIX_INLINE Vector4 StepFrom(const Quaternion& _from, const float& _time) const
    {
        return StepFrom(_from, Helper::Splat(_time));
    }

    NIX_INLINE Quaternion Slerp(const Quaternion& _other, const float& _time) const
    {
        Quaternion other = _other;

        Vector4 vCosTheta = Dot(_other);

        float cosTheta = 0;
        _mm_store_ss(&cosTheta, vCosTheta);

        if (cosTheta < 0.0f)
        {
            other = -_other;
            cosTheta = -cosTheta;
        }

        if (cosTheta > 1.0f - NIX_EPSILON)
        {
            return LerpTo(other, _time);
        }
        else
        {
            float angle = std::acos(cosTheta);

            float a = std::sinf((1.0f - _time) * angle);
            float b = std::sinf(_time * angle);
            float c = std::sinf(angle);

            const float128 ax = _mm_mul_ps(_mm_set1_ps(a), m_quat);
            const float128 by = _mm_mul_ps(_mm_set1_ps(b), other);

            const float128 q = _mm_div_ps(_mm_add_ps(ax, by), _mm_set1_ps(c));
            return q;
        }
    }

    NIX_INLINE Quaternion Conjugate() const
    {
        return Helper::Mul(m_quat, Helper::Set(-1.0f, -1.0f, -1.0f, 1.0f));
    }

    NIX_INLINE Quaternion Inverse() const
    {
        Vector4 dot = Dot(m_quat);
        float sDot = 0;
        _mm_store_ss(&sDot, dot);
        return Conjugate() / sDot;
    }

    NIX_INLINE Matrix4x4 ToMatrix() const
    {
        const float qX = Helper::ExtractX(m_quat);
        const float qY = Helper::ExtractY(m_quat);
        const float qZ = Helper::ExtractZ(m_quat);
        const float qW = Helper::ExtractW(m_quat);

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
        const float vX = Helper::ExtractX(_translation);
        const float vY = Helper::ExtractY(_translation);
        const float vZ = Helper::ExtractZ(_translation);

        const float qX = Helper::ExtractX(m_quat);
        const float qY = Helper::ExtractY(m_quat);
        const float qZ = Helper::ExtractZ(m_quat);
        const float qW = Helper::ExtractW(m_quat);

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

private:
    friend class Vector4;

    // for global operators
    friend NIX_INLINE Quaternion operator- (const Quaternion& _q);
    friend NIX_INLINE Quaternion operator+ (const Quaternion& _q1, const Quaternion& _q2);
    friend NIX_INLINE Quaternion operator* (const Quaternion& _q1, const Quaternion& _q2);
    friend NIX_INLINE Vector4 operator* (const Quaternion& _q, const Vector4& _v);
    friend NIX_INLINE Vector4 operator* (const Vector4& _v, const Quaternion& _q);
    friend NIX_INLINE Quaternion operator* (const Quaternion& _q, float _s);
    friend NIX_INLINE Quaternion operator* (float _s, const Quaternion& _q);
    friend NIX_INLINE Quaternion operator/ (const Quaternion& _q, float _s);

    float128 m_quat;
};

//////////////////////////////////////////////////////////////////////////
// Operators


#ifdef _DEBUG
NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Quaternion& _quat)
{
    float *val = (float*)&_quat.m_quat;
    _os << "(" << val[0] << ", " << val[1] << ", " << val[2] << ", " << val[3] << ")";
    return _os;
}
#endif

// negate operator
NIX_INLINE Quaternion operator- (const Quaternion& _q)
{
    return Helper::Mul(_q.m_quat, kMinusOneVec4);
}

// operator+
NIX_INLINE Quaternion operator+ (const Quaternion& _q1, const Quaternion& _q2)
{
    return Helper::Add(_q1.m_quat, _q2.m_quat);
}

//operator*
NIX_INLINE Quaternion operator* (const Quaternion& _q1, const Quaternion& _q2)
{
    const float128 mul0 = Helper::Mul(_q1.m_quat, MathFunctions::Swizzle<W, Z, Y, X>(_q2.m_quat));
    const float128 mul1 = Helper::Mul(_q1.m_quat, MathFunctions::Swizzle<Z, W, X, Y>(_q2.m_quat));
    const float128 mul2 = Helper::Mul(_q1.m_quat, MathFunctions::Swizzle<Y, X, W, Z>(_q2.m_quat));
    const float128 mul3 = Helper::Mul(_q1.m_quat, _q2.m_quat);

#if NIX_ARCH & NIX_ARCH_SSE41_FLAG
    const float128 add00 = _mm_dp_ps(mul0, Helper::Set(1.0f, 1.0f, -1.0f, 1.0f), 0xff);
    const float128 add01 = _mm_dp_ps(mul1, Helper::Set(-1.0f, 1.0f, 1.0f, 1.0f), 0xff);
    const float128 add02 = _mm_dp_ps(mul2, Helper::Set(1.0f, -1.0f, 1.0f, 1.0f), 0xff);
    const float128 add03 = _mm_dp_ps(mul3, Helper::Set(-1.0f, -1.0f, -1.0f, 1.0f), 0xff);
#   else
    const float128 mul00 = Helper::Mul(mul0, Helper::Set(1.0f, 1.0f, -1.0f, 1.0f));
    const float128 mul01 = Helper::Mul(mul1, Helper::Set(-1.0f, 1.0f, 1.0f, 1.0f));
    const float128 mul02 = Helper::Mul(mul2, Helper::Set(1.0f, -1.0f, 1.0f, 1.0f));
    const float128 mul03 = Helper::Mul(mul3, Helper::Set(-1.0f, -1.0f, -1.0f, 1.0f));

    const float128 add0 = Helper::Add(mul00, _mm_movehl_ps(mul00, mul00));
    const float128 add1 = Helper::Add(mul01, _mm_movehl_ps(mul01, mul01));
    const float128 add2 = Helper::Add(mul02, _mm_movehl_ps(mul02, mul02));
    const float128 add3 = Helper::Add(mul03, _mm_movehl_ps(mul03, mul03));

    const float128 add00 = _mm_add_ss(add0, _mm_shuffle_ps(add0, add0, 1));
    const float128 add01 = _mm_add_ss(add1, _mm_shuffle_ps(add1, add1, 1));
    const float128 add02 = _mm_add_ss(add2, _mm_shuffle_ps(add2, add2, 1));
    const float128 add03 = _mm_add_ss(add3, _mm_shuffle_ps(add3, add3, 1));
#endif

    const float128 xxyy = _mm_shuffle_ps(add00, add01, _MM_SHUFFLE(0, 0, 0, 0));
    const float128 zzww = _mm_shuffle_ps(add02, add03, _MM_SHUFFLE(0, 0, 0, 0));
    
    return _mm_shuffle_ps(xxyy, zzww, _MM_SHUFFLE(2, 0, 2, 0));
}

NIX_INLINE Vector4 operator* (const Quaternion& _q, const Vector4& _v)
{
    static const float128 two = Helper::Splat(2.0f);

    const float128 q_wwww = MathFunctions::Swizzle<W, W, W, W>(_q.m_quat);
    const float128 q_yzxw = MathFunctions::Swizzle<Y, Z, X, W>(_q.m_quat);
    const float128 q_zxyw = MathFunctions::Swizzle<Z, X, Y, W>(_q.m_quat);
    const float128 v_yzxw = MathFunctions::Swizzle<Y, Z, X, W>(_v);
    const float128 v_wyxz = MathFunctions::Swizzle<Z, X, Y, W>(_v);

    const float128 qv = Helper::Sub(Helper::Mul(q_yzxw, v_wyxz), Helper::Mul(q_zxyw, v_yzxw));
    const float128 qv_yzxw = MathFunctions::Swizzle<Y, Z, X, W>(qv);
    const float128 qv_zxyw = MathFunctions::Swizzle<Z, X, Y, W>(qv);
    const float128 qqv = Helper::Sub(Helper::Mul(q_yzxw, qv_zxyw), Helper::Mul(q_zxyw, qv_yzxw));

    const float128 mul0 = Helper::Mul(qv, Helper::Mul(q_wwww, two));
    const float128 mul1 = Helper::Mul(qqv, two);

    return Helper::Add(_v, Helper::Add(mul0, mul1));
}

NIX_INLINE Vector4 operator* (const Vector4& _v, const Quaternion& _q)
{
    Quaternion inv = _q.Inverse();
    return inv * _v;
}

NIX_INLINE Quaternion operator* (const Quaternion& _q, float _s)
{
    return Helper::Mul(_q.m_quat, Helper::Splat(_s));
}

NIX_INLINE Quaternion operator* (float _s, const Quaternion& _q)
{
    return Helper::Mul(Helper::Splat(_s), _q.m_quat);
}

//operator/
NIX_INLINE Quaternion operator/ (const Quaternion& _q, float _s)
{
    return Helper::Div(_q.m_quat, Helper::Splat(_s));
}

NIX_NAMESPACE_END