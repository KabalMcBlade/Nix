#pragma once

#include "Core/Architecture.h"
#include "Core/BasicDefines.h"
#include "Core/Assertions.h"
#include "Core/BasicTypes.h"

#include "MathAligned.h"
#include "BasicMathFunctions.h"
#include "Trigonometry.h"
#include "Vector4.h"

NIX_NAMESPACE_BEGIN


class Matrix4x4 : public MathAligned<16>
{
public:
    //////////////////////////////////////////////////////////////////////////
    NIX_INLINE Matrix4x4()
    {
        this->m_rows[0] = MathFunctions::Set(1.0f, 0.0f, 0.0f, 0.0f);
        this->m_rows[1] = MathFunctions::Set(0.0f, 1.0f, 0.0f, 0.0f);
        this->m_rows[2] = MathFunctions::Set(0.0f, 0.0f, 1.0f, 0.0f);
        this->m_rows[3] = MathFunctions::Set(0.0f, 0.0f, 0.0f, 1.0f);
    }

    NIX_INLINE Matrix4x4(const Scalar& _s)
    {
        this->m_rows[0] = MathFunctions::Set(_s, 0.0f, 0.0f, 0.0f);
        this->m_rows[1] = MathFunctions::Set(0.0f, _s, 0.0f, 0.0f);
        this->m_rows[2] = MathFunctions::Set(0.0f, 0.0f, _s, 0.0f);
        this->m_rows[3] = MathFunctions::Set(0.0f, 0.0f, 0.0f, _s);

    }

	// keep float here, having Scalar is more computation for nothing
    NIX_INLINE Matrix4x4(
        float _x0, float _y0, float _z0, float _w0,
        float _x1, float _y1, float _z1, float _w1,
        float _x2, float _y2, float _z2, float _w2,
        float _x3, float _y3, float _z3, float _w3)
    {
        this->m_rows[0] = MathFunctions::Set(_x0, _y0, _z0, _w0);
        this->m_rows[1] = MathFunctions::Set(_x1, _y1, _z1, _w1);
        this->m_rows[2] = MathFunctions::Set(_x2, _y2, _z2, _w2);
        this->m_rows[3] = MathFunctions::Set(_x3, _y3, _z3, _w3);
    }

	NIX_INLINE Matrix4x4(
		const Scalar& _v0,
		const Scalar& _v1,
		const Scalar& _v2,
		const Scalar& _v3)
	{
		this->m_rows[0] = _v0;
		this->m_rows[1] = _v1;
		this->m_rows[2] = _v2;
		this->m_rows[3] = _v3;
	}

    NIX_INLINE Matrix4x4(
        const Vector4& _v0,
        const Vector4& _v1,
        const Vector4& _v2,
        const Vector4& _v3)
    {
        this->m_rows[0] = _v0;
        this->m_rows[1] = _v1;
        this->m_rows[2] = _v2;
        this->m_rows[3] = _v3;
    }

    NIX_INLINE Matrix4x4(const Matrix4x4& _m)
    {
        this->m_rows[0] = _m.m_rows[0];
        this->m_rows[1] = _m.m_rows[1];
        this->m_rows[2] = _m.m_rows[2];
        this->m_rows[3] = _m.m_rows[3];
    }

    NIX_INLINE Matrix4x4(const Vector4 _v[4])
    {
        this->m_rows[0] = _v[0];
        this->m_rows[1] = _v[1];
        this->m_rows[2] = _v[2];
        this->m_rows[3] = _v[3];
    }

    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    friend NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Matrix4x4& _mat);
#endif

    //////////////////////////////////////////////////////////////////////////
    // Accesses

    NIX_INLINE Vector4& operator[](uint8 _i)
    {
        return this->m_rows[_i];
    }


    NIX_INLINE const Vector4& operator[](uint8 _i) const
    {
        return this->m_rows[_i];
    }

    NIX_INLINE const Vector4& GetOrtX() const
    {
        return this->m_rows[0];
    }

    NIX_INLINE const Vector4& GetOrtY() const
    {
        return this->m_rows[1];
    }

    NIX_INLINE const Vector4& GetOrtZ() const
    {
        return this->m_rows[2];
    }

    //////////////////////////////////////////////////////////////////////////
    // Operators
    NIX_INLINE Matrix4x4& operator=(const Matrix4x4& _m)
    {
        m_rows[0] = _m[0];
        m_rows[1] = _m[1];
        m_rows[2] = _m[2];
        m_rows[3] = _m[3];
        return *this;
    }

    NIX_INLINE Matrix4x4& operator+=(const Matrix4x4& _m)
    {
        *this = Add(_m);
        return *this;
    }

    NIX_INLINE Matrix4x4& operator-=(const Matrix4x4& _m)
    {
        *this = Sub(_m);
        return *this;
    }

    NIX_INLINE Matrix4x4& operator*=(const Matrix4x4& _m)
    {
        *this = Mul(_m);
        return *this;
    }

    NIX_INLINE Matrix4x4& operator/=(const Matrix4x4& _m)
    {
        Matrix4x4 inv = Inverse();
        *this = inv.Mul(_m);
        return *this;
    }

    NIX_INLINE Matrix4x4& operator+=(const Scalar& _s)
    {
        *this = Add(_s);
        return *this;
    }

    NIX_INLINE Matrix4x4& operator-=(const Scalar& _s)
    {
        *this = Sub(_s);
        return *this;
    }

    NIX_INLINE Matrix4x4& operator*=(const Scalar& _s)
    {
        *this = Mul(_s);
        return *this;
    }

    NIX_INLINE Matrix4x4& operator/=(const Scalar& _s)
    {
        *this = Div(_s);
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    // Functions
    NIX_INLINE Vector4 Determinant() const
    {
        const float128 swp0 = MathFunctions::Swizzle<Z, Y, Y, X>(m_rows[2]);
        const float128 swp1 = MathFunctions::Swizzle<W, W, Z, W>(m_rows[3]);
        const float128 mul0 = MathFunctions::Mul(swp0, swp1);

        const float128 swp2 = MathFunctions::Swizzle<W, W, Z, W>(m_rows[2]);
        const float128 swp3 = MathFunctions::Swizzle<Z, Y, Y, X>(m_rows[3]);
        const float128 mul1 = MathFunctions::Mul(swp2, swp3);

        const float128 sub0 = MathFunctions::Sub(mul0, mul1);

        const float128 xxyz = MathFunctions::Swizzle<Z, Y, X, X>(m_rows[2]);
        const float128 swp5 = MathFunctions::Swizzle<X, X, Z, Y>(m_rows[3]);
        const float128 mul2 = MathFunctions::Mul(xxyz, swp5);
        const float128 sub1 = MathFunctions::Sub(_mm_movehl_ps(mul2, mul2), mul2);

        const float128 sbf0 = MathFunctions::Swizzle<X, X, Y, Z>(sub0);
        const float128 xxxy = MathFunctions::Swizzle<Y, X, X, X>(m_rows[1]);
        const float128 mlf0 = MathFunctions::Mul(xxxy, sbf0);

        const float128 sbft = _mm_shuffle_ps(sub0, sub1, _MM_SHUFFLE(0, 0, 3, 1));
        const float128 sbf1 = MathFunctions::Swizzle<X, Y, Y, W>(sbft);
        const float128 swf1 = MathFunctions::Swizzle<Z, Z, Y, Y>(m_rows[1]);
        const float128 mlf1 = MathFunctions::Mul(swf1, sbf1);

        const float128 subr = MathFunctions::Sub(mlf0, mlf1);

        const float128 sbt0 = _mm_shuffle_ps(sub0, sub1, _MM_SHUFFLE(1, 0, 2, 2));
        const float128 sbt1 = MathFunctions::Swizzle<X, Z, W, W>(sbt0);
        const float128 swft = MathFunctions::Swizzle<W, W, W, Z>(m_rows[1]);
        const float128 mlfc = MathFunctions::Mul(swft, sbt1);

        const float128 addr = MathFunctions::Add(subr, mlfc);
        const float128 detc = MathFunctions::Mul(addr, _mm_setr_ps(1.0f, -1.0f, 1.0f, -1.0f));

        return MathFunctions::Dot(m_rows[0], detc);
    }

    NIX_INLINE Matrix4x4 Transpose() const
    {
		const float128 tmp0 = MathFunctions::Permute<A_X, B_X, A_Y, B_Y>(m_rows[0], m_rows[2]);
		const float128 tmp1 = MathFunctions::Permute<A_X, B_X, A_Y, B_Y>(m_rows[1], m_rows[3]);
		const float128 tmp2 = MathFunctions::Permute<A_Z, B_Z, A_W, B_W>(m_rows[0], m_rows[2]);
		const float128 tmp3 = MathFunctions::Permute<A_Z, B_Z, A_W, B_W>(m_rows[1], m_rows[3]);
		const float128 res0 = MathFunctions::Permute<A_X, B_X, A_Y, B_Y>(tmp0, tmp1);
		const float128 res1 = MathFunctions::Permute<A_Z, B_Z, A_W, B_W>(tmp0, tmp1);
		const float128 res2 = MathFunctions::Permute<A_X, B_X, A_Y, B_Y>(tmp2, tmp3);
		const float128 res3 = MathFunctions::Permute<A_Z, B_Z, A_W, B_W>(tmp2, tmp3);
		return Matrix4x4(
			Vector4(res0),
			Vector4(res1),
			Vector4(res2),
			Vector4(res3)
		);
    }

    // It works ONLY with transform matrix, not for generic matrix purpose
    // Moreover this not take into consider the scale, so this matrix is treated is of scale 1
	//https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html
    NIX_INLINE Matrix4x4 InverseNoScale() const
    {
		const float128 t0 = MathFunctions::Permute<A_X, A_Y, B_X, B_Y>(m_rows[0], m_rows[1]);
		const float128 t1 = MathFunctions::Permute<A_Z, A_W, B_Z, B_W>(m_rows[0], m_rows[1]);
		const float128 res0 = MathFunctions::Permute<A_X, A_Z, B_X, B_W>(t0, m_rows[2]);
		const float128 res1 = MathFunctions::Permute<A_Y, A_W, B_Y, B_W>(t0, m_rows[2]);
		const float128 res2 = MathFunctions::Permute<A_X, A_Z, B_Z, B_W>(t1, m_rows[2]);

		float128 res3 = MathFunctions::Mul(res0, MathFunctions::Swizzle<X, X, X, X>(m_rows[3]));
		res3 = MathFunctions::Add(res3, MathFunctions::Mul(res1, MathFunctions::Swizzle<Y, Y, Y, Y>(m_rows[3])));
		res3 = MathFunctions::Add(res3, MathFunctions::Mul(res2, MathFunctions::Swizzle<Z, Z, Z, Z>(m_rows[3])));
		res3 = MathFunctions::Sub(MathFunctions::Set(0.0f, 0.0f, 0.0f, 1.0f), res3);

		return Matrix4x4(
			Vector4(res0),
			Vector4(res1),
			Vector4(res2),
			Vector4(res3)
		);
    }

    // It works ONLY with transform matrix, not for generic matrix purpose
	//https://lxjk.github.io/2017/09/03/Fast-4x4-Matrix-Inverse-with-SSE-SIMD-Explained.html
    NIX_INLINE Matrix4x4 Inverse() const
    {
		const float128 t0 = MathFunctions::Permute<A_X, A_Y, B_X, B_Y>(m_rows[0], m_rows[1]);
		const float128 t1 = MathFunctions::Permute<A_Z, A_W, B_Z, B_W>(m_rows[0], m_rows[1]);
		float128 res0 = MathFunctions::Permute<A_X, A_Z, B_X, B_W>(t0, m_rows[2]);
		float128 res1 = MathFunctions::Permute<A_Y, A_W, B_Y, B_W>(t0, m_rows[2]);
		float128 res2 = MathFunctions::Permute<A_X, A_Z, B_Z, B_W>(t1, m_rows[2]);

		float128 sqr = MathFunctions::Mul(res0, res0);
		sqr = MathFunctions::Add(sqr, MathFunctions::Mul(res1, res1));
		sqr = MathFunctions::Add(sqr, MathFunctions::Mul(res2, res2));

		const float128 one = MathFunctions::SplatOne();

#if NIX_ARCH & NIX_ARCH_SSE41_FLAG
		const nixFloat4 rsqr = _mm_blendv_ps(MathFunctions::Div(one, sqr), one, _mm_cmplt_ps(sqr, MathFunctions::Splat(NIX_SMALL_NUMBER)));
#else
		float128 dva = MathFunctions::Div(one, sqr);
		float128 mask = _mm_cmplt_ps(sqr, MathFunctions::Splat(NIX_SMALL_NUMBER));
		float128 omask = _mm_and_ps(mask, one);
		dva = _mm_andnot_ps(mask, dva);

		const float128 rsqr = _mm_or_ps(dva, omask);
#endif

		res0 = MathFunctions::Mul(res0, rsqr);
		res1 = MathFunctions::Mul(res1, rsqr);
		res2 = MathFunctions::Mul(res2, rsqr);

		// last line
		float128 res3 = MathFunctions::Mul(res0, MathFunctions::Swizzle<X, X, X, X>(m_rows[3]));
		res3 = MathFunctions::Add(res3, MathFunctions::Mul(res1, MathFunctions::Swizzle<Y, Y, Y, Y>(m_rows[3])));
		res3 = MathFunctions::Add(res3, MathFunctions::Mul(res2, MathFunctions::Swizzle<Z, Z, Z, Z>(m_rows[3])));
		res3 = MathFunctions::Sub(MathFunctions::Set(0.0f, 0.0f, 0.0f, 1.0f), res3);

		return Matrix4x4(
			Vector4(res0),
			Vector4(res1),
			Vector4(res2),
			Vector4(res3)
		);
    }

    NIX_INLINE Matrix4x4 Translate(const Vector4& _v) const
    {
        Matrix4x4 result;
        const float128& xxxx = MathFunctions::Swizzle<X, X, X, X>(_v);
        const float128& yyyy = MathFunctions::Swizzle<Y, Y, Y, Y>(_v);
        const float128& zzzz = MathFunctions::Swizzle<Z, Z, Z, Z>(_v);

        const float128& v0 = MathFunctions::Mul(m_rows[0], xxxx);
        const float128& v1 = MathFunctions::Mul(m_rows[1], yyyy);
        const float128& v2 = MathFunctions::Mul(m_rows[2], zzzz);

        const float128& row3 = MathFunctions::Add(MathFunctions::Add(v0, v1), v2);
        result[0] = m_rows[0];
        result[1] = m_rows[1];
        result[2] = m_rows[2];
        result[3] = MathFunctions::Add(row3, m_rows[3]);
        return result;
    }

    NIX_INLINE Matrix4x4 Scale(const Vector4& _s) const
    {
        Matrix4x4 result;
        const float128& xxxx = MathFunctions::Swizzle<X, X, X, X>(_s);
        const float128& yyyy = MathFunctions::Swizzle<Y, Y, Y, Y>(_s);
        const float128& zzzz = MathFunctions::Swizzle<Z, Z, Z, Z>(_s);

        result[0] = MathFunctions::Mul(m_rows[0], xxxx);
        result[1] = MathFunctions::Mul(m_rows[1], yyyy);
        result[2] = MathFunctions::Mul(m_rows[2], zzzz);
        result[3] = m_rows[3];
        return result;
    }

    NIX_INLINE Matrix4x4 Mul(const Matrix4x4& _other) const
    {
        Matrix4x4 result;
        {
            const float128 xxxx = MathFunctions::Swizzle<X, X, X, X>(m_rows[0]);
            const float128 yyyy = MathFunctions::Swizzle<Y, Y, Y, Y>(m_rows[0]);
            const float128 zzzz = MathFunctions::Swizzle<Z, Z, Z, Z>(m_rows[0]);
            const float128 wwww = MathFunctions::Swizzle<W, W, W, W>(m_rows[0]);

            const float128 mul0 = MathFunctions::Mul(_other[0], xxxx);
            const float128 mul1 = MathFunctions::Mul(_other[1], yyyy);
            const float128 mul2 = MathFunctions::Mul(_other[2], zzzz);
            const float128 mul3 = MathFunctions::Mul(_other[3], wwww);

            const float128 add0 = MathFunctions::Add(mul0, mul1);
            const float128 add1 = MathFunctions::Add(mul2, mul3);
            const float128 add2 = MathFunctions::Add(add0, add1);

            result[0] = add2;
        }

        {
            const float128 xxxx = MathFunctions::Swizzle<X, X, X, X>(m_rows[1]);
            const float128 yyyy = MathFunctions::Swizzle<Y, Y, Y, Y>(m_rows[1]);
            const float128 zzzz = MathFunctions::Swizzle<Z, Z, Z, Z>(m_rows[1]);
            const float128 wwww = MathFunctions::Swizzle<W, W, W, W>(m_rows[1]);

            const float128 mul0 = MathFunctions::Mul(_other[0], xxxx);
            const float128 mul1 = MathFunctions::Mul(_other[1], yyyy);
            const float128 mul2 = MathFunctions::Mul(_other[2], zzzz);
            const float128 mul3 = MathFunctions::Mul(_other[3], wwww);

            const float128 add0 = MathFunctions::Add(mul0, mul1);
            const float128 add1 = MathFunctions::Add(mul2, mul3);
            const float128 add2 = MathFunctions::Add(add0, add1);

            result[1] = add2;
        }

        {
            const float128 xxxx = MathFunctions::Swizzle<X, X, X, X>(m_rows[2]);
            const float128 yyyy = MathFunctions::Swizzle<Y, Y, Y, Y>(m_rows[2]);
            const float128 zzzz = MathFunctions::Swizzle<Z, Z, Z, Z>(m_rows[2]);
            const float128 wwww = MathFunctions::Swizzle<W, W, W, W>(m_rows[2]);

            const float128 mul0 = MathFunctions::Mul(_other[0], xxxx);
            const float128 mul1 = MathFunctions::Mul(_other[1], yyyy);
            const float128 mul2 = MathFunctions::Mul(_other[2], zzzz);
            const float128 mul3 = MathFunctions::Mul(_other[3], wwww);

            const float128 add0 = MathFunctions::Add(mul0, mul1);
            const float128 add1 = MathFunctions::Add(mul2, mul3);
            const float128 add2 = MathFunctions::Add(add0, add1);

            result[2] = add2;
        }

        {
            const float128 xxxx = MathFunctions::Swizzle<X, X, X, X>(m_rows[3]);
            const float128 yyyy = MathFunctions::Swizzle<Y, Y, Y, Y>(m_rows[3]);
            const float128 zzzz = MathFunctions::Swizzle<Z, Z, Z, Z>(m_rows[3]);
            const float128 wwww = MathFunctions::Swizzle<W, W, W, W>(m_rows[3]);

            const float128 mul0 = MathFunctions::Mul(_other[0], xxxx);
            const float128 mul1 = MathFunctions::Mul(_other[1], yyyy);
            const float128 mul2 = MathFunctions::Mul(_other[2], zzzz);
            const float128 mul3 = MathFunctions::Mul(_other[3], wwww);

            const float128 add0 = MathFunctions::Add(mul0, mul1);
            const float128 add1 = MathFunctions::Add(mul2, mul3);
            const float128 add2 = MathFunctions::Add(add0, add1);

            result[3] = add2;
        }
        return result;
    }

    NIX_INLINE Matrix4x4 Add(const Matrix4x4& _other) const
    {
        Matrix4x4 result;
        result[0] = MathFunctions::Add(m_rows[0], _other[0]);
        result[1] = MathFunctions::Add(m_rows[1], _other[1]);
        result[2] = MathFunctions::Add(m_rows[2], _other[2]);
        result[3] = MathFunctions::Add(m_rows[3], _other[3]);
        return result;
    }

    NIX_INLINE Matrix4x4 Sub(const Matrix4x4& _other) const
    {
        Matrix4x4 result;
        result[0] = MathFunctions::Sub(m_rows[0], _other[0]);
        result[1] = MathFunctions::Sub(m_rows[1], _other[1]);
        result[2] = MathFunctions::Sub(m_rows[2], _other[2]);
        result[3] = MathFunctions::Sub(m_rows[3], _other[3]);
        return result;
    }

    NIX_INLINE Matrix4x4 Add(Scalar _s) const
    {
        Matrix4x4 result;
        result[0] = MathFunctions::Add(m_rows[0], _s);
        result[1] = MathFunctions::Add(m_rows[1], _s);
        result[2] = MathFunctions::Add(m_rows[2], _s);
        result[3] = MathFunctions::Add(m_rows[3], _s);
        return result;
    }

    NIX_INLINE Matrix4x4 Sub(Scalar _s) const
    {
        Matrix4x4 result;
        result[0] = MathFunctions::Sub(m_rows[0], _s);
        result[1] = MathFunctions::Sub(m_rows[1], _s);
        result[2] = MathFunctions::Sub(m_rows[2], _s);
        result[3] = MathFunctions::Sub(m_rows[3], _s);
        return result;
    }

    NIX_INLINE Matrix4x4 Mul(Scalar _s) const
    {
        Matrix4x4 result;
        result[0] = MathFunctions::Mul(m_rows[0], _s);
        result[1] = MathFunctions::Mul(m_rows[1], _s);
        result[2] = MathFunctions::Mul(m_rows[2], _s);
        result[3] = MathFunctions::Mul(m_rows[3], _s);
        return result;
    }

    NIX_INLINE Matrix4x4 Div(Scalar _s) const
    {
        Matrix4x4 result;
        const float128 opv = MathFunctions::Div(kOneVec4, _s);
        result[0] = MathFunctions::Mul(m_rows[0], opv);
        result[1] = MathFunctions::Mul(m_rows[1], opv);
        result[2] = MathFunctions::Mul(m_rows[2], opv);
        result[3] = MathFunctions::Mul(m_rows[3], opv);
        return result;
    }

    NIX_INLINE Vector4 MulMatrixVector(const Vector4& _v) const
    {
        const float128 xxxx = MathFunctions::Swizzle<X, X, X, X>(_v);
        const float128 yyyy = MathFunctions::Swizzle<Y, Y, Y, Y>(_v);
        const float128 zzzz = MathFunctions::Swizzle<Z, Z, Z, Z>(_v);
        const float128 wwww = MathFunctions::Swizzle<W, W, W, W>(_v);

        const float128 mul0 = MathFunctions::Mul(m_rows[0], xxxx);
        const float128 mul1 = MathFunctions::Mul(m_rows[1], yyyy);
        const float128 mul2 = MathFunctions::Mul(m_rows[2], zzzz);
        const float128 mul3 = MathFunctions::Mul(m_rows[3], wwww);

        const float128 add0 = MathFunctions::Add(mul0, mul1);
        const float128 add1 = MathFunctions::Add(mul2, mul3);

        return MathFunctions::Add(add0, add1);
    }

    NIX_INLINE Vector4 MulVectorMatrix(const Vector4& _v) const
    {
        const float128 mul0 = MathFunctions::Mul(_v, m_rows[0]);
        const float128 mul1 = MathFunctions::Mul(_v, m_rows[1]);
        const float128 mul2 = MathFunctions::Mul(_v, m_rows[2]);
        const float128 mul3 = MathFunctions::Mul(_v, m_rows[3]);

        const float128 lo0 = _mm_unpacklo_ps(mul0, mul1);
        const float128 hi0 = _mm_unpackhi_ps(mul0, mul1);
        const float128 add0 = MathFunctions::Add(lo0, hi0);

        const float128 lo1 = _mm_unpacklo_ps(mul2, mul3);
        const float128 hi1 = _mm_unpackhi_ps(mul2, mul3);
        const float128 add1 = MathFunctions::Add(lo1, hi1);

        const float128 mlh = _mm_movelh_ps(add0, add1);
        const float128 mhl = _mm_movehl_ps(add1, add0);

        return MathFunctions::Add(mlh, mhl);
    }

private:
    friend class Vector4;

    // for global operators
    friend NIX_INLINE Matrix4x4 operator+(const Matrix4x4& _m, const Scalar& _s);
    friend NIX_INLINE Matrix4x4 operator+(const Scalar& _s, const Matrix4x4& _m);
    friend NIX_INLINE Matrix4x4 operator+(const Matrix4x4& _a, const Matrix4x4& _b);
    friend NIX_INLINE Matrix4x4 operator-(const Matrix4x4& _m, const Scalar& _s);
    friend NIX_INLINE Matrix4x4 operator-(const Scalar& _s, const Matrix4x4& _m);
    friend NIX_INLINE Matrix4x4 operator-(const Matrix4x4& _a, const Matrix4x4& _b);
    friend NIX_INLINE Matrix4x4 operator*(const Matrix4x4& _m, const Scalar& _s);
    friend NIX_INLINE Matrix4x4 operator*(const Scalar& _s, const Matrix4x4& _m);
    friend NIX_INLINE Vector4 operator*(const Matrix4x4& _m, const Vector4& _v);
    friend NIX_INLINE Vector4 operator*(const Vector4& _v, const Matrix4x4& _m);
    friend NIX_INLINE Matrix4x4 operator*(const Matrix4x4& _a, const Matrix4x4& _b);
    friend NIX_INLINE Matrix4x4 operator/(const Matrix4x4& _m, const Scalar& _s);
    friend NIX_INLINE Matrix4x4 operator/(const Scalar& _s, const Matrix4x4& _m);

private:
    Vector4 m_rows[4];
};


//////////////////////////////////////////////////////////////
// Operators

#ifdef _DEBUG
NIX_INLINE std::ostream& operator<<(std::ostream& _os, const Matrix4x4& _mat)
{
    float *val0 = (float*)&(_mat[0]);
    float *val1 = (float*)&(_mat[1]);
    float *val2 = (float*)&(_mat[2]);
    float *val3 = (float*)&(_mat[3]);

    _os << "(" << val0[0] << ", " << val0[1] << ", " << val0[2] << ", " << val0[3] << ")" << std::endl
        << "(" << val1[0] << ", " << val1[1] << ", " << val1[2] << ", " << val1[3] << ")" << std::endl
        << "(" << val2[0] << ", " << val2[1] << ", " << val2[2] << ", " << val2[3] << ")" << std::endl
        << "(" << val3[0] << ", " << val3[1] << ", " << val3[2] << ", " << val3[3] << ")";
    return _os;
}
#endif

NIX_INLINE Matrix4x4 operator+(const Matrix4x4& _m, const Scalar& _s)
{
    return _m.Add(_s);
}

NIX_INLINE Matrix4x4 operator+(const Scalar& _s, const Matrix4x4& _m)
{
    return _m.Add(_s);
}

NIX_INLINE Matrix4x4 operator+(const Matrix4x4& _a, const Matrix4x4& _b)
{
    return _a.Add(_b);
}

NIX_INLINE Matrix4x4 operator-(const Matrix4x4& _m, const Scalar& _s)
{
    return _m.Sub(_s);
}

NIX_INLINE Matrix4x4 operator-(const Scalar& _s, const Matrix4x4& _m)
{
    return _m.Sub(_s);
}

NIX_INLINE Matrix4x4 operator-(const Matrix4x4& _a, const Matrix4x4& _b)
{
    return _a.Sub(_b);
}

NIX_INLINE Matrix4x4 operator*(const Matrix4x4& _m, const Scalar& _s)
{
    return _m.Mul(_s);
}

NIX_INLINE Matrix4x4 operator*(const Scalar& _s, const Matrix4x4& _m)
{
    return _m.Mul(_s);
}

NIX_INLINE Vector4 operator*(const Matrix4x4& _m, const Vector4& _v)
{
    return _m.MulMatrixVector(_v);
}

NIX_INLINE Vector4 operator*(const Vector4& _v, const Matrix4x4& _m)
{
    return _m.MulVectorMatrix(_v);
}

NIX_INLINE Matrix4x4 operator*(const Matrix4x4& _a, const Matrix4x4& _b)
{
    return _a.Mul(_b);
}

NIX_INLINE Matrix4x4 operator/(const Matrix4x4& _m, const Scalar& _s)
{
    return _m.Div(_s);
}

NIX_INLINE Matrix4x4 operator/(const Scalar& _s, const Matrix4x4& _m)
{
    return _m.Div(_s);
}


NIX_NAMESPACE_END