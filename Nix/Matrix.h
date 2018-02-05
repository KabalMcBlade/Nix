#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"
#include "VectorHelper.h"
#include "MathHelper.h"
#include "Vector.h"
#include "MatrixHelper.h"

NIX_NAMESPACE_BEGIN



#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG
NIX_SIMD_ALIGN_32 class Matrix
#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG
NIX_SIMD_ALIGN_32 class Matrix
#   else 
NIX_SIMD_ALIGN_16 class Matrix
#   endif
{
private:
    //////////////////////////////////////////////////////////////////////////
    friend class VectorHelper;
    friend class MatrixHelper;

#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG
    __nixFloat16 m_rows;
#   define ROWS_REF_T           this->m_rows
#   define ROWS_REF_P(owner)    owner->m_rows
#   define ROWS_REF_R(owner)    owner.m_rows
#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG
    __nixFloat8 m_rows[2];
#   define ROWS_REF_T        &this->m_rows[0]
#   define ROWS_REF_P(owner) &owner->m_rows[0]
#   define ROWS_REF_R(owner) &owner.m_rows[0]
#   else 
    __nixFloat4 m_rows[4];
#   define ROWS_REF_T        &this->m_rows[0]
#   define ROWS_REF_P(owner) &owner->m_rows[0]
#   define ROWS_REF_R(owner) &owner.m_rows[0]
#   endif


public:
    //////////////////////////////////////////////////////////////////////////
    NIX_INLINE Matrix()
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        this->m_rows = VectorHelper::Set(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = VectorHelper::Set(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f);

        this->m_rows[1] = VectorHelper::Set(
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);

#   else 

        this->m_rows[0] = VectorHelper::Set(1.0f, 0.0f, 0.0f, 0.0f);
        this->m_rows[1] = VectorHelper::Set(0.0f, 1.0f, 0.0f, 0.0f);
        this->m_rows[2] = VectorHelper::Set(0.0f, 0.0f, 1.0f, 0.0f);
        this->m_rows[3] = VectorHelper::Set(0.0f, 0.0f, 0.0f, 1.0f);

#   endif
    }

    NIX_INLINE Matrix(const nixFloat& _s)
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        this->m_rows = VectorHelper::Set(
            _s, 0.0f, 0.0f, 0.0f,
            0.0f, _s, 0.0f, 0.0f,
            0.0f, 0.0f, _s, 0.0f,
            0.0f, 0.0f, 0.0f, _s);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = VectorHelper::Set(
            _s, 0.0f, 0.0f, 0.0f,
            0.0f, _s, 0.0f, 0.0f);

        this->m_rows[1] = VectorHelper::Set(
            0.0f, 0.0f, _s, 0.0f,
            0.0f, 0.0f, 0.0f, _s);

#   else 

        this->m_rows[0] = VectorHelper::Set(_s, 0.0f, 0.0f, 0.0f);
        this->m_rows[1] = VectorHelper::Set(0.0f, _s, 0.0f, 0.0f);
        this->m_rows[2] = VectorHelper::Set(0.0f, 0.0f, _s, 0.0f);
        this->m_rows[3] = VectorHelper::Set(0.0f, 0.0f, 0.0f, _s);

#   endif
    }

    NIX_INLINE Matrix(
        const nixFloat& _x0, const nixFloat& _y0, const nixFloat& _z0, const nixFloat& _w0,
        const nixFloat& _x1, const nixFloat& _y1, const nixFloat& _z1, const nixFloat& _w1,
        const nixFloat& _x2, const nixFloat& _y2, const nixFloat& _z2, const nixFloat& _w2,
        const nixFloat& _x3, const nixFloat& _y3, const nixFloat& _z3, const nixFloat& _w3)
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        this->m_rows = VectorHelper::Set(
            _x0, _y0, _z0, _w0,
            _x1, _y1, _z1, _w1,
            _x2, _y2, _z2, _w2,
            _x3, _y3, _z3, _w3);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = VectorHelper::Set(
            _x0, _y0, _z0, _w0,
            _x1, _y1, _z1, _w1);

        this->m_rows[1] = VectorHelper::Set(
            _x2, _y2, _z2, _w2,
            _x3, _y3, _z3, _w3);

#   else 

        this->m_rows[0] = VectorHelper::Set(_x0, _y0, _z0, _w0);
        this->m_rows[1] = VectorHelper::Set(_x1, _y1, _z1, _w1);
        this->m_rows[2] = VectorHelper::Set(_x2, _y2, _z2, _w2);
        this->m_rows[3] = VectorHelper::Set(_x3, _y3, _z3, _w3);

#   endif
    }

    NIX_INLINE Matrix(
        const Vector& _v0,
        const Vector& _v1,
        const Vector& _v2,
        const Vector& _v3)
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        this->m_rows = _mm512_insertf32x4(_mm512_insertf32x4(_mm512_insertf32x4(_mm512_castps128_ps512(_v0.m_vec), _v1.m_vec, 1), _v2.m_vec, 2), _v3.m_vec, 3);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = _mm256_castps128_ps256(_v0.m_vec);
        this->m_rows[0] = _mm256_insertf128_ps(this->m_rows[0], _v1.m_vec, 1);

        this->m_rows[1] = _mm256_castps128_ps256(_v2.m_vec);
        this->m_rows[1] = _mm256_insertf128_ps(this->m_rows[1], _v3.m_vec, 1);

#   else 

        this->m_rows[0] = _v0.m_vec;
        this->m_rows[1] = _v1.m_vec;
        this->m_rows[2] = _v2.m_vec;
        this->m_rows[3] = _v3.m_vec;

#   endif
    }

    NIX_INLINE Matrix(const Matrix& _m)
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        this->m_rows = _m.m_rows;

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = _m.m_rows[0];
        this->m_rows[1] = _m.m_rows[1];

#   else 

        this->m_rows[0] = _m.m_rows[0];
        this->m_rows[1] = _m.m_rows[1];
        this->m_rows[2] = _m.m_rows[2];
        this->m_rows[3] = _m.m_rows[3];

#   endif
    }

    NIX_INLINE Matrix(const Vector _v[4])
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        this->m_rows = _mm512_insertf32x4(_mm512_insertf32x4(_mm512_insertf32x4(_mm512_castps128_ps512(_v[0].m_vec), _v[1].m_vec, 1), _v[2].m_vec, 2), _v[3].m_vec, 3);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = _mm256_castps128_ps256(_v[0].m_vec);
        this->m_rows[0] = _mm256_insertf128_ps(this->m_rows[0], _v[1].m_vec, 1);

        this->m_rows[1] = _mm256_castps128_ps256(_v[2].m_vec);
        this->m_rows[1] = _mm256_insertf128_ps(this->m_rows[1], _v[3].m_vec, 1);

#   else 

        this->m_rows[0] = _v[0].m_vec;
        this->m_rows[1] = _v[1].m_vec;
        this->m_rows[2] = _v[2].m_vec;
        this->m_rows[3] = _v[3].m_vec;

#   endif
    }

    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    NIX_INLINE void Print() const
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG
        nixFloat *val = (nixFloat*)&(this->m_rows);

        printf("matrix{\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n}\n",
            val[0], val[1], val[2], val[3], val[4], val[5], val[6], val[7], val[8], val[9], val[10], val[11], val[12], val[13], val[14], val[15]);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG
        nixFloat *val0 = (nixFloat*)&(this->m_rows[0]);
        nixFloat *val1 = (nixFloat*)&(this->m_rows[1]);

        printf("matrix{\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n}\n",
            val0[0], val0[1], val0[2], val0[3], val0[4], val0[5], val0[6], val0[7], val1[0], val1[1], val1[2], val1[3], val1[4], val1[5], val1[6], val1[7]);
#   else
        nixFloat *val0 = (nixFloat*)&(this->m_rows[0]);
        nixFloat *val1 = (nixFloat*)&(this->m_rows[1]);
        nixFloat *val2 = (nixFloat*)&(this->m_rows[2]);
        nixFloat *val3 = (nixFloat*)&(this->m_rows[3]);

        printf("matrix{\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n[%.4f, %.4f, %.4f, %.4f]\n}\n", 
            val0[0], val0[1], val0[2], val0[3], val1[0], val1[1], val1[2], val1[3], val2[0], val2[1], val2[2], val2[3], val3[0], val3[1], val3[2], val3[3]);
#   endif
    }
#endif


    //////////////////////////////////////////////////////////////////////////
    // Accesses

    NIX_INLINE __nixFloat4& operator[](nixU8 _i)
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        return _mm512_extractf32x4_ps(this->m_rows, _i);
        
#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        switch(_i)
        {
        case 0: return _mm256_extractf128_ps(this->m_rows[0], 0); break;
        case 1: return _mm256_extractf128_ps(this->m_rows[0], 1); break;
        case 2: return _mm256_extractf128_ps(this->m_rows[1], 0); break;
        case 3: return _mm256_extractf128_ps(this->m_rows[1], 1); break;
        }

#   else 

        return this->m_rows[_i];

#   endif
    }


    NIX_INLINE const __nixFloat4& operator[](nixU8 _i) const
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        return _mm512_extractf32x4_ps(this->m_rows, _i);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        switch (_i)
        {
        case 0: return _mm256_extractf128_ps(this->m_rows[0], 0); break;
        case 1: return _mm256_extractf128_ps(this->m_rows[0], 1); break;
        case 2: return _mm256_extractf128_ps(this->m_rows[1], 0); break;
        case 3: return _mm256_extractf128_ps(this->m_rows[1], 1); break;
        }

#   else 

        return this->m_rows[_i];

#   endif
    }

    NIX_INLINE const __nixFloat4& GetOrtX() const
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        return _mm512_extractf32x4_ps(this->m_rows, 0);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        return _mm256_extractf128_ps(this->m_rows[0], 0);

#   else 

        return this->m_rows[0];

#   endif
    }

    NIX_INLINE const __nixFloat4& GetOrtY() const
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        return _mm512_extractf32x4_ps(this->m_rows, 1);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        return _mm256_extractf128_ps(this->m_rows[0], 1);

#   else 

        return this->m_rows[1];

#   endif
    }

    NIX_INLINE const __nixFloat4& GetOrtZ() const
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        return _mm512_extractf32x4_ps(this->m_rows, 2);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        return _mm256_extractf128_ps(this->m_rows[1], 0);

#   else 

        return this->m_rows[2];

#   endif
    }

    //////////////////////////////////////////////////////////////////////////
    // Operators
    NIX_INLINE Matrix& operator=(const Matrix& _m)
    {
        MatrixHelper::Set(ROWS_REF_R(_m), ROWS_REF_T);
        return *this;
    }

    NIX_INLINE Matrix& operator+=(const Matrix& _m)
    {
        MatrixHelper::Add(ROWS_REF_T, ROWS_REF_R(_m), ROWS_REF_T);
        return *this;
    }

    NIX_INLINE Matrix& operator-=(const Matrix& _m)
    {
        MatrixHelper::Sub(ROWS_REF_T, ROWS_REF_R(_m), ROWS_REF_T);
        return *this;
    }

    NIX_INLINE Matrix& operator*=(const Matrix& _m)
    {
        MatrixHelper::Mul(ROWS_REF_T, ROWS_REF_R(_m), ROWS_REF_T);
        return *this;
    }

    NIX_INLINE Matrix& operator/=(const Matrix& _m)
    {
        Matrix inv;
        MatrixHelper::Inverse(ROWS_REF_R(_m), ROWS_REF_R(inv));
        MatrixHelper::Mul(ROWS_REF_T, ROWS_REF_R(inv), ROWS_REF_T);
        return *this;
    }

    NIX_INLINE Matrix& operator+=(const nixFloat& _s)
    {
        MatrixHelper::Add(ROWS_REF_T, _s, ROWS_REF_T);
        return *this;
    }

    NIX_INLINE Matrix& operator-=(const nixFloat& _s)
    {
        MatrixHelper::Sub(ROWS_REF_T, _s, ROWS_REF_T);
        return *this;
    }

    NIX_INLINE Matrix& operator*=(const nixFloat& _s)
    {
        MatrixHelper::Mul(ROWS_REF_T, _s, ROWS_REF_T);
        return *this;
    }

    NIX_INLINE Matrix& operator/=(const nixFloat& _s)
    {
        MatrixHelper::Div(ROWS_REF_T, _s, ROWS_REF_T);
        return *this;
    }

    NIX_INLINE Matrix& operator++()
    {
        MatrixHelper::Increment(ROWS_REF_T, ROWS_REF_T);
        return *this;
    }

    NIX_INLINE Matrix& operator--()
    {
        MatrixHelper::Decrement(ROWS_REF_T, ROWS_REF_T);
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    // Functions
    NIX_INLINE Matrix Transpose()
    {
        Matrix result;
        MatrixHelper::Transpose(ROWS_REF_T, ROWS_REF_R(result));
        return result;
    }

    NIX_INLINE Matrix InverseNoScale()
    {
        Matrix result;
        MatrixHelper::InverseNoScale(ROWS_REF_T, ROWS_REF_R(result));
        return result;
    }

    NIX_INLINE Matrix Inverse()
    {
        Matrix result;
        MatrixHelper::Inverse(ROWS_REF_T, ROWS_REF_R(result));
        return result;
    }


    private:
        friend class Vector;

        // for global operators
        friend NIX_INLINE Matrix operator+(const Matrix& _m, const nixFloat& _s);
        friend NIX_INLINE Matrix operator+(const nixFloat& _s, const Matrix& _m);
        friend NIX_INLINE Matrix operator+(const Matrix& _a, const Matrix& _b);
        friend NIX_INLINE Matrix operator-(const Matrix& _m, const nixFloat& _s);
        friend NIX_INLINE Matrix operator-(const nixFloat& _s, const Matrix& _m);
        friend NIX_INLINE Matrix operator-(const Matrix& _a, const Matrix& _b);
        friend NIX_INLINE Matrix operator*(const Matrix& _m, const nixFloat& _s);
        friend NIX_INLINE Matrix operator*(const nixFloat& _s, const Matrix& _m);
        friend NIX_INLINE Vector operator*(const Matrix& _m, const Vector& _v);
        friend NIX_INLINE Vector operator*(const Vector& _v, const Matrix& _m);
        friend NIX_INLINE Matrix operator*(const Matrix& _a, const Matrix& _b);
        friend NIX_INLINE Matrix operator/(const Matrix& _m, const nixFloat& _s);
        friend NIX_INLINE Matrix operator/(const nixFloat& _s, const Matrix& _m);
        friend NIX_INLINE Matrix const operator-(const Matrix& _m);
        friend NIX_INLINE Matrix const operator--(const Matrix& _m, nixS32);
        friend NIX_INLINE Matrix const operator++(const Matrix& _m, nixS32);
};


//////////////////////////////////////////////////////////////
// Operators

NIX_INLINE Matrix operator+(const Matrix& _m, const nixFloat& _s)
{
    Matrix result;
    MatrixHelper::Add(ROWS_REF_R(_m), _s, ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix operator+(const nixFloat& _s, const Matrix& _m)
{
    Matrix result;
    MatrixHelper::Add(ROWS_REF_R(_m), _s, ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix operator+(const Matrix& _a, const Matrix& _b)
{
    Matrix result;
    MatrixHelper::Add(ROWS_REF_R(_a), ROWS_REF_R(_b), ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix operator-(const Matrix& _m, const nixFloat& _s)
{
    Matrix result;
    MatrixHelper::Sub(ROWS_REF_R(_m), _s, ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix operator-(const nixFloat& _s, const Matrix& _m)
{
    Matrix result;
    MatrixHelper::Sub(ROWS_REF_R(_m), _s, ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix operator-(const Matrix& _a, const Matrix& _b)
{
    Matrix result;
    MatrixHelper::Sub(ROWS_REF_R(_a), ROWS_REF_R(_b), ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix operator*(const Matrix& _m, const nixFloat& _s)
{
    Matrix result;
    MatrixHelper::Mul(ROWS_REF_R(_m), _s, ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix operator*(const nixFloat& _s, const Matrix& _m)
{
    Matrix result;
    MatrixHelper::Mul(ROWS_REF_R(_m), _s, ROWS_REF_R(result));
    return result;
}

NIX_INLINE Vector operator*(const Matrix& _m, const Vector& _v)
{
    Vector result;
    MatrixHelper::MulMatrixVector(ROWS_REF_R(_m), _v.m_vec, &result.m_vec);
    return result;
}

NIX_INLINE Vector operator*(const Vector& _v, const Matrix& _m)
{
    Vector result;
    MatrixHelper::MulVectorMatrix( _v.m_vec, ROWS_REF_R(_m), &result.m_vec);
    return result;
}

NIX_INLINE Matrix operator*(const Matrix& _a, const Matrix& _b)
{
    Matrix result;
    MatrixHelper::Mul(ROWS_REF_R(_a), ROWS_REF_R(_b), ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix operator/(const Matrix& _m, const nixFloat& _s)
{
    Matrix result;
    MatrixHelper::Div(ROWS_REF_R(_m), _s, ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix operator/(const nixFloat& _s, const Matrix& _m)
{
    Matrix result;
    MatrixHelper::Div(ROWS_REF_R(_m), _s, ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix const operator-(const Matrix& _m)
{
    Matrix result;
    MatrixHelper::Negate(ROWS_REF_R(_m), ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix const operator--(const Matrix& _m, nixS32)
{
    Matrix result;
    MatrixHelper::Decrement(ROWS_REF_R(_m), ROWS_REF_R(result));
    return result;
}

NIX_INLINE Matrix const operator++(const Matrix& _m, nixS32)
{
    Matrix result;
    MatrixHelper::Increment(ROWS_REF_R(_m), ROWS_REF_R(result));
    return result;
}



NIX_NAMESPACE_END