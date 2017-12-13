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
    //////////////////////////////////////////////////////////////////////////
    // private at the beginning for macro purpose...
private:
    friend class VectorHelper;
    //friend class Vector;

    //////////////////////////////////////////////////////////////////////////
    // MACROS SECTION

///
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG
    __nixFloat16 m_rows;

#define SET_VALUE_RAW(_00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33) \
        this->m_rows = VectorHelper::Set512(_00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33);

#define SET_VALUE_VEC(_v0, _v1, _v2, _v3) \
    this->m_rows = _mm512_insertf32x4(_mm512_insertf32x4(_mm512_insertf32x4(_mm512_castps128_ps512(_v0, _v1, 1), _v2, 2), _v3, 3);

#define SET_VALUE_MAT(_m) \
        this->m_rows = _m.m_rows;

#define GET_VALUE(_i) \
        _mm512_extractf32x4_ps(this->m_rows, _i);

///
#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG
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

#define GET_VALUE(_i) \
        static const nixU8 imm[4] = { 0, 1, 0, 1}; \
        static const nixU8 idx[4] = { 0, 0, 1, 1}; \
        _mm256_extractf128_ps(this->m_rows[idx[_i]], imm[_i]);
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

#define GET_VALUE(_i) \
        this->m_rows[_i];

#define ADD_MAT(_m) \
        this->m_rows[0] = VectorHelper::Add(this->m_rows[0], _m[0]); \
        this->m_rows[1] = VectorHelper::Add(this->m_rows[1], _m[1]); \
        this->m_rows[2] = VectorHelper::Add(this->m_rows[2], _m[2]); \
        this->m_rows[3] = VectorHelper::Add(this->m_rows[3], _m[3]);

#endif


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


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

    //////////////////////////////////////
    // Accesses
    NIX_INLINE __nixFloat4& operator[](nixU8 _i)
    {
        return GET_VALUE(_i);
    }

    NIX_INLINE const __nixFloat4& operator[](nixU8 _i) const
    {
        return GET_VALUE(_i);
    }

    NIX_INLINE const __nixFloat4& GetOrtX() const
    {
        return GET_VALUE(0);
    }

    NIX_INLINE const __nixFloat4& GetOrtY() const
    {
        return GET_VALUE(1);
    }

    NIX_INLINE const __nixFloat4& GetOrtZ() const
    {
        return GET_VALUE(2);
    }

    //////////////////////////////////////////////////////////////////////////
    // Operators
    NIX_INLINE Matrix& operator=(const Matrix& _m)
    {
        SET_VALUE_MAT(_m);
        return *this;
    }

    NIX_INLINE Matrix& operator+=(const Matrix& _m)
    {
        ADD_MAT(_m);
        return *this;
    }
};

NIX_NAMESPACE_END