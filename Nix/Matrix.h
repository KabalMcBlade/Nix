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
public:
    //////////////////////////////////////////////////////////////////////////
    NIX_INLINE Matrix()
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        this->m_rows = VectorHelper::Set512(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 1.0f);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = VectorHelper::Set256(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f);

        this->m_rows[1] = VectorHelper::Set256(
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

        this->m_rows = VectorHelper::Set512(
            _s, 0.0f, 0.0f, 0.0f,
            0.0f, _s, 0.0f, 0.0f,
            0.0f, 0.0f, _s, 0.0f,
            0.0f, 0.0f, 0.0f, _s);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = VectorHelper::Set256(
            _s, 0.0f, 0.0f, 0.0f,
            0.0f, _s, 0.0f, 0.0f);

        this->m_rows[1] = VectorHelper::Set256(
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

        this->m_rows = VectorHelper::Set512(
            _x0, _y0, _z0, _w0,
            _x1, _y1, _z1, _w1,
            _x2, _y2, _z2, _w2,
            _x3, _y3, _z3, _w3);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = VectorHelper::Set256(
            _x0, _y0, _z0, _w0,
            _x1, _y1, _z1, _w1);

        this->m_rows[1] = VectorHelper::Set256(
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

        this->m_rows[0] = _mmul256_castps128_ps256(_v0.m_vec);
        this->m_rows[0] = _mmul256_insertf128_ps(this->m_rows[0], _v1.m_vec, 1);

        this->m_rows[1] = _mmul256_castps128_ps256(_v2.m_vec);
        this->m_rows[1] = _mmul256_insertf128_ps(this->m_rows[1], _v3.m_vec, 1);

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

        this->m_rows[0] = _mmul256_castps128_ps256(_v[0].m_vec);
        this->m_rows[0] = _mmul256_insertf128_ps(this->m_rows[0].m_vec, _v[1].m_vec, 1);

        this->m_rows[1] = _mmul256_castps128_ps256(_v[2].m_vec);
        this->m_rows[1] = _mmul256_insertf128_ps(this->m_rows[1].m_vec, _v[3].m_vec, 1);

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

    //////////////////////////////////////
    // Accesses
    NIX_INLINE __nixFloat4& operator[](nixU8 _i)
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        return _mm512_extractf32x4_ps(this->m_rows, _i);
        
#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        static const nixU8 imm[4] = { 0, 1, 0, 1 };
        static const nixU8 idx[4] = { 0, 0, 1, 1 };
        return _mmul256_extractf128_ps(this->m_rows[idx[_i]], imm[_i]);

#   else 

        return this->m_rows[_i];

#   endif
    }

    NIX_INLINE const __nixFloat4& operator[](nixU8 _i) const
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        return _mm512_extractf32x4_ps(this->m_rows, _i);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        static const nixU8 imm[4] = { 0, 1, 0, 1 };
        static const nixU8 idx[4] = { 0, 0, 1, 1 };
        return _mmul256_extractf128_ps(this->m_rows[idx[_i]], imm[_i]);

#   else 

        return this->m_rows[_i];

#   endif
    }

    NIX_INLINE const __nixFloat4& GetOrtX() const
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        return _mm512_extractf32x4_ps(this->m_rows, 0);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        static const nixU8 imm[4] = { 0, 1, 0, 1 };
        static const nixU8 idx[4] = { 0, 0, 1, 1 };
        return _mmul256_extractf128_ps(this->m_rows[idx[0]], imm[0]);

#   else 

        return this->m_rows[0];

#   endif
    }

    NIX_INLINE const __nixFloat4& GetOrtY() const
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        return _mm512_extractf32x4_ps(this->m_rows, 1);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        static const nixU8 imm[4] = { 0, 1, 0, 1 };
        static const nixU8 idx[4] = { 0, 0, 1, 1 };
        return _mmul256_extractf128_ps(this->m_rows[idx[1]], imm[1]);

#   else 

        return this->m_rows[1];

#   endif
    }

    NIX_INLINE const __nixFloat4& GetOrtZ() const
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        return _mm512_extractf32x4_ps(this->m_rows, 2);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        static const nixU8 imm[4] = { 0, 1, 0, 1 };
        static const nixU8 idx[4] = { 0, 0, 1, 1 };
        return _mmul256_extractf128_ps(this->m_rows[idx[2]], imm[2]);

#   else 

        return this->m_rows[2];

#   endif
    }

    //////////////////////////////////////////////////////////////////////////
    // Operators
    NIX_INLINE Matrix& operator=(const Matrix& _m)
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

        return *this;
    }

    NIX_INLINE Matrix& operator+=(const Matrix& _m)
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        this->m_rows = VectorHelper::Add(this->m_rows, _m.m_rows);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = VectorHelper::Add(this->m_rows[0], _m.m_rows[0]);
        this->m_rows[1] = VectorHelper::Add(this->m_rows[1], _m.m_rows[1]);

#   else 

        this->m_rows[0] = VectorHelper::Add(this->m_rows[0], _m.m_rows[0]);
        this->m_rows[1] = VectorHelper::Add(this->m_rows[1], _m.m_rows[1]);
        this->m_rows[2] = VectorHelper::Add(this->m_rows[2], _m.m_rows[2]);
        this->m_rows[3] = VectorHelper::Add(this->m_rows[3], _m.m_rows[3]);

#   endif

        return *this;
    }

    NIX_INLINE Matrix& operator-=(const Matrix& _m)
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        this->m_rows = VectorHelper::Sub(this->m_rows, _m.m_rows);

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

        this->m_rows[0] = VectorHelper::Sub(this->m_rows[0], _m.m_rows[0]);
        this->m_rows[1] = VectorHelper::Sub(this->m_rows[1], _m.m_rows[1]);

#   else 

        this->m_rows[0] = VectorHelper::Sub(this->m_rows[0], _m.m_rows[0]);
        this->m_rows[1] = VectorHelper::Sub(this->m_rows[1], _m.m_rows[1]);
        this->m_rows[2] = VectorHelper::Sub(this->m_rows[2], _m.m_rows[2]);
        this->m_rows[3] = VectorHelper::Sub(this->m_rows[3], _m.m_rows[3]);

#   endif

        return *this;
    }

    NIX_INLINE Matrix& operator*=(const Matrix& _m)
    {
#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

        

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG



#   else 


        {
            __nixFloat4 swp0 = _mm_shuffle_ps(_m.m_rows[0], _m.m_rows[0], _MM_SHUFFLE(0, 0, 0, 0));
            __nixFloat4 swp1 = _mm_shuffle_ps(_m.m_rows[0], _m.m_rows[0], _MM_SHUFFLE(1, 1, 1, 1));
            __nixFloat4 swp2 = _mm_shuffle_ps(_m.m_rows[0], _m.m_rows[0], _MM_SHUFFLE(2, 2, 2, 2));
            __nixFloat4 swp3 = _mm_shuffle_ps(_m.m_rows[0], _m.m_rows[0], _MM_SHUFFLE(3, 3, 3, 3));

            __nixFloat4 mul0 = VectorHelper::Mul(this->m_rows[0], swp0);
            __nixFloat4 mul1 = VectorHelper::Mul(this->m_rows[1], swp1);
            __nixFloat4 mul2 = VectorHelper::Mul(this->m_rows[2], swp2);
            __nixFloat4 mul3 = VectorHelper::Mul(this->m_rows[3], swp3);

            __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            this->m_rows[0] = add2;
        }

        {
            __nixFloat4 swp0 = _mm_shuffle_ps(_m.m_rows[1], _m.m_rows[1], _MM_SHUFFLE(0, 0, 0, 0));
            __nixFloat4 swp1 = _mm_shuffle_ps(_m.m_rows[1], _m.m_rows[1], _MM_SHUFFLE(1, 1, 1, 1));
            __nixFloat4 swp2 = _mm_shuffle_ps(_m.m_rows[1], _m.m_rows[1], _MM_SHUFFLE(2, 2, 2, 2));
            __nixFloat4 swp3 = _mm_shuffle_ps(_m.m_rows[1], _m.m_rows[1], _MM_SHUFFLE(3, 3, 3, 3));

            __nixFloat4 mul0 = VectorHelper::Mul(this->m_rows[0], swp0);
            __nixFloat4 mul1 = VectorHelper::Mul(this->m_rows[1], swp1);
            __nixFloat4 mul2 = VectorHelper::Mul(this->m_rows[2], swp2);
            __nixFloat4 mul3 = VectorHelper::Mul(this->m_rows[3], swp3);

            __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            this->m_rows[1] = add2;
        }

        {
            __nixFloat4 swp0 = _mm_shuffle_ps(_m.m_rows[2], _m.m_rows[2], _MM_SHUFFLE(0, 0, 0, 0));
            __nixFloat4 swp1 = _mm_shuffle_ps(_m.m_rows[2], _m.m_rows[2], _MM_SHUFFLE(1, 1, 1, 1));
            __nixFloat4 swp2 = _mm_shuffle_ps(_m.m_rows[2], _m.m_rows[2], _MM_SHUFFLE(2, 2, 2, 2));
            __nixFloat4 swp3 = _mm_shuffle_ps(_m.m_rows[2], _m.m_rows[2], _MM_SHUFFLE(3, 3, 3, 3));

            __nixFloat4 mul0 = VectorHelper::Mul(this->m_rows[0], swp0);
            __nixFloat4 mul1 = VectorHelper::Mul(this->m_rows[1], swp1);
            __nixFloat4 mul2 = VectorHelper::Mul(this->m_rows[2], swp2);
            __nixFloat4 mul3 = VectorHelper::Mul(this->m_rows[3], swp3);

            __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            this->m_rows[2] = add2;
        }

        {
            __nixFloat4 swp0 = _mm_shuffle_ps(_m.m_rows[3], _m.m_rows[3], _MM_SHUFFLE(0, 0, 0, 0));
            __nixFloat4 swp1 = _mm_shuffle_ps(_m.m_rows[3], _m.m_rows[3], _MM_SHUFFLE(1, 1, 1, 1));
            __nixFloat4 swp2 = _mm_shuffle_ps(_m.m_rows[3], _m.m_rows[3], _MM_SHUFFLE(2, 2, 2, 2));
            __nixFloat4 swp3 = _mm_shuffle_ps(_m.m_rows[3], _m.m_rows[3], _MM_SHUFFLE(3, 3, 3, 3));

            __nixFloat4 mul0 = VectorHelper::Mul(this->m_rows[0], swp0);
            __nixFloat4 mul1 = VectorHelper::Mul(this->m_rows[1], swp1);
            __nixFloat4 mul2 = VectorHelper::Mul(this->m_rows[2], swp2);
            __nixFloat4 mul3 = VectorHelper::Mul(this->m_rows[3], swp3);

            __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            this->m_rows[3] = add2;
        }

#   endif

        return *this;
    }

    private:
        friend class VectorHelper;
        friend class MatrixHelper;

#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG
        __nixFloat16 m_rows;
#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG
        __nixFloat8 m_rows[2];
#   else 
        __nixFloat4 m_rows[4];
#   endif

};

NIX_NAMESPACE_END