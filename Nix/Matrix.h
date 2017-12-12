#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"
#include "VectorHelper.h"
#include "MathHelper.h"
#include "Vector.h"


NIX_NAMESPACE_BEGIN

NIX_SIMD_ALIGN class Matrix
{
    // private at the beginning for macro purpose...
private:
    friend class VectorHelper;
    //friend class Vector;

///
#if defined(NIX_ARCH_AVX512)
    __nixFloat16 m_rows;

#define SET_VALUE_RAW(_00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33) \
        this->m_rows = VectorHelper::Set512(_00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33);

#define SET_VALUE_VEC(_v0, _v1, _v2, _v3) \
    this->m_rows = _mm512_insertf32x4(_mm512_insertf32x4(_mm512_insertf32x4(_mm512_castps128_ps512(_v0, _v1, 1), _v2, 2), _v3, 3);

#define SET_VALUE_MAT(_m) \
        this->m_rows = _m.m_rows;

///
#elif defined(NIX_ARCH_AVX2) || defined(NIX_ARCH_AVX)
    __nixFloat8 m_rows[2];

#define SET_VALUE_RAW(_00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33) \
        this->m_rows[0] = VectorHelper::Set256(_00, _01, _02, _03, _10, _11, _12, _13); \
        this->m_rows[1] = VectorHelper::Set256(_20, _21, _22, _23, _30, _31, _32, _33);

#define SET_VALUE_VEC(_v0, _v1, _v2, _v3) \
    this->m_rows[0] = _mm256_castps128_ps256(_v0); \
    this->m_rows[0] = _mm256_insertf128_ps(this->m_rows[0], _v1, 1); \
    this->m_rows[1] = _mm256_castps128_ps256(_v2); \
    this->m_rows[1] = _mm256_insertf128_ps(this->m_rows[1], _v3, 1); 

#define SET_VALUE_MAT(_m) \
        this->m_rows[0] = _m.m_rows[0]; \
        this->m_rows[1] = _m.m_rows[1];

///
#else 
    __nixFloat4 m_rows[4];

#define SET_VALUE_RAW(_00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33) \
        this->m_rows[0] = VectorHelper::Set(_00, _01, _02, _03); \
        this->m_rows[1] = VectorHelper::Set(_10, _11, _12, _13); \
        this->m_rows[2] = VectorHelper::Set(_20, _21, _22, _23); \
        this->m_rows[3] = VectorHelper::Set(_30, _31, _32, _33);

#define SET_VALUE_VEC(_v0, _v1, _v2, _v3) \
        this->m_rows[0] = _v0.m_vec; \
        this->m_rows[1] = _v1.m_vec; \
        this->m_rows[2] = _v2.m_vec; \
        this->m_rows[3] = _v3.m_vec;

#define SET_VALUE_MAT(_m) \
        this->m_rows[0] = _m.m_rows[0]; \
        this->m_rows[1] = _m.m_rows[1]; \
        this->m_rows[2] = _m.m_rows[2]; \
        this->m_rows[3] = _m.m_rows[3];

#define GET_VALUE_VEC(_i) \
        nixAssert(_i > 0 && _i < 4, "Index out of range"); \
        this->m_rows[i];

#endif

//////////////////////////////////////////////////////////////////////////
public:
    NIX_INLINE Matrix()
    {
        SET_VALUE_RAW(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);
    }

    NIX_INLINE Matrix(const nixFloat& _s)
    {
        SET_VALUE_RAW(
            _s, 0.0f, 0.0f, 0.0f,
            0.0f, _s, 0.0f, 0.0f,
            0.0f, 0.0f, _s, 0.0f,
            0.0f, 0.0f, 0.0f, _s);
    }

    NIX_INLINE Matrix(
        const nixFloat& _x0, const nixFloat& _y0, const nixFloat& _z0, const nixFloat& _w0,
        const nixFloat& _x1, const nixFloat& _y1, const nixFloat& _z1, const nixFloat& _w1,
        const nixFloat& _x2, const nixFloat& _y2, const nixFloat& _z2, const nixFloat& _w2,
        const nixFloat& _x3, const nixFloat& _y3, const nixFloat& _z3, const nixFloat& _w3)
    {
        SET_VALUE_RAW(
            _x0, _y0, _z0, _w0,
            _x1, _y1, _z1, _w1,
            _x2, _y2, _z2, _w2,
            _x3, _y3, _z3, _w3);
    }

    NIX_INLINE Matrix(
        const Vector& _v0,
        const Vector& _v1,
        const Vector& _v2,
        const Vector& _v3)
    {
        SET_VALUE_VEC(_v0, _v1, _v2, _v3);
    }

    NIX_INLINE Matrix(const Matrix& _m)
    {
        SET_VALUE_MAT(_m);
    }

    NIX_INLINE Matrix(const Vector _v[4])
    {
        SET_VALUE_VEC(_v[0], _v[1], _v[2], _v[3]);
    }

    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    NIX_INLINE void Print() const
    {
#if defined(NIX_ARCH_AVX512)
        nixFloat *val = (nixFloat*)&(this->m_rows);

        printf("matrix{\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n}\n",
            val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7], val[8], val[9], val[10], val[11], val[12], val[13], val[14], val[15]);

#elif defined(NIX_ARCH_AVX2) || defined(NIX_ARCH_AVX)
        nixFloat *val0 = (nixFloat*)&(this->m_rows[0]);
        nixFloat *val1 = (nixFloat*)&(this->m_rows[1]);

        printf("matrix{\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n}\n",
            val0[0], val0[1], val0[2], val0[3], val0[4], val0[5], val0[6], val0[7], val1[0], val1[1], val1[2], val1[3], val1[4], val1[5], val1[6], val1[7]);
#else
        nixFloat *val0 = (nixFloat*)&(this->m_rows[0]);
        nixFloat *val1 = (nixFloat*)&(this->m_rows[1]);
        nixFloat *val2 = (nixFloat*)&(this->m_rows[2]);
        nixFloat *val3 = (nixFloat*)&(this->m_rows[3]);

        printf("matrix{\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n}\n", 
            val0[0], val0[1], val0[2], val0[3], val1[0], val1[1], val1[2], val1[3], val2[0], val2[1], val2[2], val2[3], val3[0], val3[1], val3[2], val3[3]);
#endif
    }
#endif

};

NIX_NAMESPACE_END