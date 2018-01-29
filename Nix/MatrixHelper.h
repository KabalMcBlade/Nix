#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"
#include "VectorHelper.h"


NIX_NAMESPACE_BEGIN


#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG
NIX_SIMD_ALIGN_32 class MatrixHelper
#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG
NIX_SIMD_ALIGN_32 class MatrixHelper
#   else 
NIX_SIMD_ALIGN_16 class MatrixHelper
#   endif
{
public:

#   if NIX_ARCH & NIX_ARCH_AVX512_FLAG

    static NIX_INLINE void Mul(const __nixFloat16 * const _a, const __nixFloat16 * const _b, __nixFloat16 * _out)
    {
        nixAssert(false, "AVX512 is not yet implemented");
        /*
        // NOTE: this possibly doesn't work, I don't have possibility to test right now, keep just to left me a crumble about what I want to do.

        static const nixS32 NIX_SIMD_ALIGN_32 msk0123[16] = { 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3 };
        static const nixS32 NIX_SIMD_ALIGN_32 msk4567[16] = { 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7 };

        static const __nixInt16 prm0123 = _mm512_load_si512(reinterpret_cast<const __nixInt16*>(msk0123));
        static const __nixInt16 prm4567 = _mm512_load_si512(reinterpret_cast<const __nixInt16*>(msk4567));

        const __nixInt16 swp0 = _mm512_permutevar_ps(*_b, prm0123);
        const __nixInt16 swp1 = _mm512_permutevar_ps(*_b, prm4567);

        const __nixFloat16 mul0 = VectorHelper::Mul(*_a, swp0);
        const __nixFloat16 mul1 = VectorHelper::Mul(*_a, swp1);

        *_out = VectorHelper::Add(mul0, mul1);
        */
    }

    static NIX_INLINE void Transpose(const __nixFloat16 * const _m, __nixFloat16 * _out)
    {
        nixAssert(false, "AVX512 is not yet implemented");
    }

    // It works ONLY with transform matrix, not for generic matrix purpose
    // Moreover this not take into consider the scale, so this matrix is treated is of scale 1
    static NIX_INLINE void InverseNoScale(const __nixFloat16 * const _m, __nixFloat16 * _out)
    {
        nixAssert(false, "AVX512 is not yet implemented");
    }

    static NIX_INLINE void Set(const __nixFloat16 * const _m, __nixFloat16* _out)
    {
        *_out = *_m;
    }

    static NIX_INLINE void Add(const __nixFloat16 * const _a, const __nixFloat16 * const _b, __nixFloat16* _out)
    {
        *_out = VectorHelper::Add(*_a, *_b);
    }

    static NIX_INLINE void Sub(const __nixFloat16 * const _a, const __nixFloat16 * const _b, __nixFloat16* _out)
    {
        *_out = VectorHelper::Sub(*_a, *_b);
    }

    static NIX_INLINE void Add(const __nixFloat16 * const _m, nixFloat _s, __nixFloat16* _out)
    {
        __nixFloat16 opv = VectorHelper::Splat512(_s);
        *_out = VectorHelper::Add(*_m, opv);
    }

    static NIX_INLINE void Sub(const __nixFloat16 * const _m, nixFloat _s, __nixFloat16* _out)
    {
        __nixFloat16 opv = VectorHelper::Splat512(_s);
        *_out = VectorHelper::Sub(*_m, opv);
    }


    static NIX_INLINE void Mul(const __nixFloat16 * const _m, nixFloat _s, __nixFloat16* _out)
    {
        const __nixFloat16 opv = VectorHelper::Splat512(_s);
        *_out = VectorHelper::Mul(*_m, opv);
    }

    static NIX_INLINE void Div(const __nixFloat16 * const _m, nixFloat _s, __nixFloat16* _out)
    {
        const __nixFloat16 opv = VectorHelper::Div(VectorHelper::GetOne512(), VectorHelper::Splat512(_s));
        *_out = VectorHelper::Mul(*_m, opv);
    }

    static NIX_INLINE void Increment(const __nixFloat16 * const _m, __nixFloat16* _out)
    {
        const __nixFloat16 one = VectorHelper::GetOne512();
        *_out = VectorHelper::Add(*_m, one);
    }

    static NIX_INLINE void Decrement(const __nixFloat16 * const _m, __nixFloat16* _out)
    {
        const __nixFloat16 one = VectorHelper::GetOne512();
        *_out = VectorHelper::Sub(*_m, one);
    }



#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG


    // IS WRONG THE ORDER!
    static NIX_INLINE void Mul(const __nixFloat8 * const _a, const __nixFloat8 * const _b, __nixFloat8* _out)
    {
        static const nixS32 sw0145bit = 0b00000011;

        static const __nixInt8 msk10 = _mm256_set_epi32(1, 1, 1, 1, 0, 0, 0, 0);
        static const __nixInt8 msk32 = _mm256_set_epi32(3, 3, 3, 3, 2, 2, 2, 2);
        static const __nixInt8 msk01 = _mm256_set_epi32(0, 0, 0, 0, 1, 1, 1, 1);
        static const __nixInt8 msk23 = _mm256_set_epi32(2, 2, 2, 2, 3, 3, 3, 3);

        const __nixFloat8 prm0 = _mm256_permute2f128_ps(_b[0], _b[0], sw0145bit);
        const __nixFloat8 prm1 = _mm256_permute2f128_ps(_b[1], _b[1], sw0145bit);

        {
            const __nixFloat8 prm10 = _mm256_permutevar_ps(_a[0], msk10);
            const __nixFloat8 prm32 = _mm256_permutevar_ps(_a[0], msk32);
            const __nixFloat8 prm01 = _mm256_permutevar_ps(_a[0], msk01);
            const __nixFloat8 prm23 = _mm256_permutevar_ps(_a[0], msk23);

            _out[0] = _mm256_add_ps(_mm256_add_ps(_mm256_mul_ps(_b[0], prm10), _mm256_mul_ps(_b[1], prm32)), _mm256_add_ps(_mm256_mul_ps(prm0, prm01), _mm256_mul_ps(prm1, prm23)));
        }

        {
            const __nixFloat8 prm10 = _mm256_permutevar_ps(_a[1], msk10);
            const __nixFloat8 prm32 = _mm256_permutevar_ps(_a[1], msk32);
            const __nixFloat8 prm01 = _mm256_permutevar_ps(_a[1], msk01);
            const __nixFloat8 prm23 = _mm256_permutevar_ps(_a[1], msk23);

            _out[1] = _mm256_add_ps(_mm256_add_ps(_mm256_mul_ps(_b[0], prm10), _mm256_mul_ps(_b[1], prm32)), _mm256_add_ps(_mm256_mul_ps(prm0, prm01), _mm256_mul_ps(prm1, prm23)));
        }
    }

    // Because _mm256_permutevar8x32_ps is not widely implements in CPU, I've to work in 128 instead of 256 here...
    static NIX_INLINE void Transpose(const __nixFloat8 * const _m, __nixFloat8 * _out)
    {
        const __nixFloat4 m0lo = _mm256_castps256_ps128(_m[0]);
        const __nixFloat4 m0hi = _mm256_extractf128_ps(_m[0], 1);

        const __nixFloat4 m1lo = _mm256_castps256_ps128(_m[1]);
        const __nixFloat4 m1hi = _mm256_extractf128_ps(_m[1], 1);

        const __nixFloat4 swp0 = _mm_shuffle_ps(m0lo, m0hi, 0x44);
        const __nixFloat4 swp1 = _mm_shuffle_ps(m1lo, m1hi, 0x44);
        const __nixFloat4 swp2 = _mm_shuffle_ps(m0lo, m0hi, 0xEE);
        const __nixFloat4 swp3 = _mm_shuffle_ps(m1lo, m1hi, 0xEE);

        const __nixFloat4 row0 = _mm_shuffle_ps(swp0, swp1, 0x88);
        const __nixFloat4 row1 = _mm_shuffle_ps(swp0, swp1, 0xDD);
        const __nixFloat4 row2 = _mm_shuffle_ps(swp2, swp3, 0x88);
        const __nixFloat4 row3 = _mm_shuffle_ps(swp2, swp3, 0xDD);

        _out[0] = _mm256_castps128_ps256(row0);
        _out[0] = _mm256_insertf128_ps(_out[0], row1, 1);

        _out[1] = _mm256_castps128_ps256(row2);
        _out[1] = _mm256_insertf128_ps(_out[1], row3, 1);
    }


    // Because _mm256_permutevar8x32_ps is not widely implements in CPU, I've to work in 128 instead of 256 here...
    // So it is NOT optimize at all...
    // It works ONLY with transform matrix, not for generic matrix purpose
    // Moreover this not take into consider the scale, so this matrix is treated is of scale 1
    static NIX_INLINE void InverseNoScale(const __nixFloat8 * const _m, __nixFloat8 * _out)
    {
        const __nixFloat4 m0lo = _mm256_castps256_ps128(_m[0]);
        const __nixFloat4 m0hi = _mm256_extractf128_ps(_m[0], 1);

        const __nixFloat4 m1lo = _mm256_castps256_ps128(_m[1]);
        const __nixFloat4 m1hi = _mm256_extractf128_ps(_m[1], 1);

        // transpose the 3x3 part, so m03 = m13 = m23 = 0
        const __nixFloat4 lh = _mm_movelh_ps(m0lo, m0hi);
        const __nixFloat4 hl = _mm_movehl_ps(m0hi, m0lo);
        const __nixFloat4 row0 = _mm_shuffle_ps(lh, m1lo, _MM_SHUFFLE(3, 0, 2, 0));
        const __nixFloat4 row1 = _mm_shuffle_ps(lh, m1lo, _MM_SHUFFLE(3, 1, 3, 1));
        const __nixFloat4 row2 = _mm_shuffle_ps(hl, m1lo, _MM_SHUFFLE(3, 2, 2, 0));

        _out[0] = _mm256_castps128_ps256(row0);
        _out[0] = _mm256_insertf128_ps(_out[0], row1, 1);


        // the forth line
        __nixFloat4 row3 = VectorHelper::Mul(row0, _mm_shuffle_ps(m1hi, m1hi, 0x00));
        row3 = VectorHelper::Add(row3, VectorHelper::Mul(row1, _mm_shuffle_ps(m1hi, m1hi, 0x55)));
        row3 = VectorHelper::Add(row3, VectorHelper::Mul(row2, _mm_shuffle_ps(m1hi, m1hi, 0xAA)));
        row3 = VectorHelper::Sub(VectorHelper::Set(0.f, 0.f, 0.f, 1.f), row3);

        _out[1] = _mm256_castps128_ps256(row2);
        _out[1] = _mm256_insertf128_ps(_out[1], row3, 1);
    }

    // Because _mm256_permutevar8x32_ps is not widely implements in CPU, I've to work in 128 instead of 256 here...
    // So it is NOT optimize at all...
    // It works ONLY with transform matrix, not for generic matrix purpose
    static NIX_INLINE void Inverse(const __nixFloat8 * const _m, __nixFloat8 * _out)
    {
        const __nixFloat4 m0lo = _mm256_castps256_ps128(_m[0]);
        const __nixFloat4 m0hi = _mm256_extractf128_ps(_m[0], 1);

        const __nixFloat4 m1lo = _mm256_castps256_ps128(_m[1]);
        const __nixFloat4 m1hi = _mm256_extractf128_ps(_m[1], 1);

        // transpose the 3x3 part, so m03 = m13 = m23 = 0
        const __nixFloat4 lh = _mm_movelh_ps(m0lo, m0hi);
        const __nixFloat4 hl = _mm_movehl_ps(m0hi, m0lo);

        __nixFloat4 row0 = _mm_shuffle_ps(lh, m1lo, _MM_SHUFFLE(3, 0, 2, 0));
        __nixFloat4 row1 = _mm_shuffle_ps(lh, m1lo, _MM_SHUFFLE(3, 1, 3, 1));
        __nixFloat4 row2 = _mm_shuffle_ps(hl, m1lo, _MM_SHUFFLE(3, 2, 2, 0));


        __nixFloat4 sqr = VectorHelper::Mul(row0, row0);
        sqr = VectorHelper::Add(sqr, VectorHelper::Mul(row1, row1));
        sqr = VectorHelper::Add(sqr, VectorHelper::Mul(row2, row2));

        const __nixFloat4 msk = _mm_cmplt_ps(sqr, VectorHelper::GetSmallNumber());

#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG

        const __nixFloat4 rsqr = _mm_blendv_ps(VectorHelper::Div(VectorHelper::GetOne(), sqr), VectorHelper::GetOne(), msk);

#   else

        __nixFloat4 one = VectorHelper::GetOne();
        __nixFloat4 dva = VectorHelper::Div(one, sqr);

        one = _mm_and_ps(msk, one);
        dva = _mm_andnot_ps(msk, dva);

        const __nixFloat4 rsqr = _mm_or_ps(dva, one);

#   endif

        row0 = VectorHelper::Mul(row0, rsqr);
        row1 = VectorHelper::Mul(row1, rsqr);

        _out[0] = _mm256_castps128_ps256(row0);
        _out[0] = _mm256_insertf128_ps(_out[0], row1, 1);


        row2 = VectorHelper::Mul(row2, rsqr);

        // the forth line
        __nixFloat4 row3 = VectorHelper::Mul(row0, _mm_shuffle_ps(m1hi, m1hi, 0x00));
        row3 = VectorHelper::Add(row3, VectorHelper::Mul(row1, _mm_shuffle_ps(m1hi, m1hi, 0x55)));
        row3 = VectorHelper::Add(row3, VectorHelper::Mul(row2, _mm_shuffle_ps(m1hi, m1hi, 0xAA)));
        row3 = VectorHelper::Sub(VectorHelper::Set(0.f, 0.f, 0.f, 1.f), row3);

        _out[1] = _mm256_castps128_ps256(row2);
        _out[1] = _mm256_insertf128_ps(_out[1], row3, 1);
    }

    static NIX_INLINE void Set(const __nixFloat8 * const _m, __nixFloat8* _out)
    {
        _out[0] = _m[0];
        _out[1] = _m[1];
    }

    static NIX_INLINE void Add(const __nixFloat8 * const _a, const __nixFloat8 * const _b, __nixFloat8* _out)
    {
        _out[0] = VectorHelper::Add(_a[0], _b[0]);
        _out[1] = VectorHelper::Add(_a[1], _b[1]);
    }

    static NIX_INLINE void Sub(const __nixFloat8 * const _a, const __nixFloat8 * const _b, __nixFloat8* _out)
    {
        _out[0] = VectorHelper::Sub(_a[0], _b[0]);
        _out[1] = VectorHelper::Sub(_a[1], _b[1]);
    }

    static NIX_INLINE void Add(const __nixFloat8 * const _m, nixFloat _s, __nixFloat8* _out)
    {
        const __nixFloat8 opv = VectorHelper::Splat256(_s);
        _out[0] = VectorHelper::Add(_m[0], opv);
        _out[1] = VectorHelper::Add(_m[1], opv);
    }

    static NIX_INLINE void Sub(const __nixFloat8 * const _m, nixFloat _s, __nixFloat8* _out)
    {
        const __nixFloat8 opv = VectorHelper::Splat256(_s);
        _out[0] = VectorHelper::Sub(_m[0], opv);
        _out[1] = VectorHelper::Sub(_m[1], opv);
    }

    static NIX_INLINE void Mul(const __nixFloat8 * const _m, nixFloat _s, __nixFloat8* _out)
    {
        const __nixFloat8 opv = VectorHelper::Splat256(_s);
        _out[0] = VectorHelper::Mul(_m[0], opv);
        _out[1] = VectorHelper::Mul(_m[1], opv);
    }

    static NIX_INLINE void Div(const __nixFloat8 * const _m, nixFloat _s, __nixFloat8* _out)
    {
        const __nixFloat8 opv = VectorHelper::Div(VectorHelper::GetOne256(), VectorHelper::Splat256(_s));
        _out[0] = VectorHelper::Mul(_m[0], opv);
        _out[1] = VectorHelper::Mul(_m[1], opv);
    }

    static NIX_INLINE void Increment(const __nixFloat8 * const _m, __nixFloat8* _out)
    {
        const __nixFloat8 one = VectorHelper::GetOne256();
        _out[0] = VectorHelper::Add(_m[0], one);
        _out[1] = VectorHelper::Add(_m[1], one);
    }

    static NIX_INLINE void Decrement(const __nixFloat8 * const _m, __nixFloat8* _out)
    {
        const __nixFloat8 one = VectorHelper::GetOne256();
        _out[0] = VectorHelper::Sub(_m[0], one);
        _out[1] = VectorHelper::Sub(_m[1], one);
    }

    static NIX_INLINE void MulMatrixVector(const __nixFloat8 * const _m, const __nixFloat4& _v, __nixFloat4* _out)
    {

    }

    static NIX_INLINE void MulVectorMatrix(const __nixFloat4& _v, const __nixFloat8 * const _m, __nixFloat4* _out)
    {

    }





#   else 


    static NIX_INLINE void Mul(const __nixFloat4 * const _a, const __nixFloat4 * const _b, __nixFloat4* _out)
    {
        {
            const __nixFloat4 swp0 = _mm_shuffle_ps(_a[0], _a[0], _MM_SHUFFLE(0, 0, 0, 0));
            const __nixFloat4 swp1 = _mm_shuffle_ps(_a[0], _a[0], _MM_SHUFFLE(1, 1, 1, 1));
            const __nixFloat4 swp2 = _mm_shuffle_ps(_a[0], _a[0], _MM_SHUFFLE(2, 2, 2, 2));
            const __nixFloat4 swp3 = _mm_shuffle_ps(_a[0], _a[0], _MM_SHUFFLE(3, 3, 3, 3));

            const __nixFloat4 mul0 = VectorHelper::Mul(_b[0], swp0);
            const __nixFloat4 mul1 = VectorHelper::Mul(_b[1], swp1);
            const __nixFloat4 mul2 = VectorHelper::Mul(_b[2], swp2);
            const __nixFloat4 mul3 = VectorHelper::Mul(_b[3], swp3);

            const __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            const __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            const __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            _out[0] = add2;
        }

        {
            const __nixFloat4 swp0 = _mm_shuffle_ps(_a[1], _a[1], _MM_SHUFFLE(0, 0, 0, 0));
            const __nixFloat4 swp1 = _mm_shuffle_ps(_a[1], _a[1], _MM_SHUFFLE(1, 1, 1, 1));
            const __nixFloat4 swp2 = _mm_shuffle_ps(_a[1], _a[1], _MM_SHUFFLE(2, 2, 2, 2));
            const __nixFloat4 swp3 = _mm_shuffle_ps(_a[1], _a[1], _MM_SHUFFLE(3, 3, 3, 3));

            const __nixFloat4 mul0 = VectorHelper::Mul(_b[0], swp0);
            const __nixFloat4 mul1 = VectorHelper::Mul(_b[1], swp1);
            const __nixFloat4 mul2 = VectorHelper::Mul(_b[2], swp2);
            const __nixFloat4 mul3 = VectorHelper::Mul(_b[3], swp3);

            const __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            const __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            const __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            _out[1] = add2;
        }

        {
            const __nixFloat4 swp0 = _mm_shuffle_ps(_a[2], _a[2], _MM_SHUFFLE(0, 0, 0, 0));
            const __nixFloat4 swp1 = _mm_shuffle_ps(_a[2], _a[2], _MM_SHUFFLE(1, 1, 1, 1));
            const __nixFloat4 swp2 = _mm_shuffle_ps(_a[2], _a[2], _MM_SHUFFLE(2, 2, 2, 2));
            const __nixFloat4 swp3 = _mm_shuffle_ps(_a[2], _a[2], _MM_SHUFFLE(3, 3, 3, 3));

            const __nixFloat4 mul0 = VectorHelper::Mul(_b[0], swp0);
            const __nixFloat4 mul1 = VectorHelper::Mul(_b[1], swp1);
            const __nixFloat4 mul2 = VectorHelper::Mul(_b[2], swp2);
            const __nixFloat4 mul3 = VectorHelper::Mul(_b[3], swp3);

            const __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            const __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            const __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            _out[2] = add2;
        }

        {
            const __nixFloat4 swp0 = _mm_shuffle_ps(_a[3], _a[3], _MM_SHUFFLE(0, 0, 0, 0));
            const __nixFloat4 swp1 = _mm_shuffle_ps(_a[3], _a[3], _MM_SHUFFLE(1, 1, 1, 1));
            const __nixFloat4 swp2 = _mm_shuffle_ps(_a[3], _a[3], _MM_SHUFFLE(2, 2, 2, 2));
            const __nixFloat4 swp3 = _mm_shuffle_ps(_a[3], _a[3], _MM_SHUFFLE(3, 3, 3, 3));

            const __nixFloat4 mul0 = VectorHelper::Mul(_b[0], swp0);
            const __nixFloat4 mul1 = VectorHelper::Mul(_b[1], swp1);
            const __nixFloat4 mul2 = VectorHelper::Mul(_b[2], swp2);
            const __nixFloat4 mul3 = VectorHelper::Mul(_b[3], swp3);

            const __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            const __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            const __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            _out[3] = add2;
        }
    }

    static NIX_INLINE void Transpose(const __nixFloat4 * const _m, __nixFloat4 * _out)
    {
        const __nixFloat4 swp0 = _mm_shuffle_ps(_m[0], _m[1], 0x44);
        const __nixFloat4 swp1 = _mm_shuffle_ps(_m[2], _m[3], 0x44);
        const __nixFloat4 swp2 = _mm_shuffle_ps(_m[0], _m[1], 0xEE);
        const __nixFloat4 swp3 = _mm_shuffle_ps(_m[2], _m[3], 0xEE);
        _out[0] = _mm_shuffle_ps(swp0, swp1, 0x88);
        _out[1] = _mm_shuffle_ps(swp0, swp1, 0xDD);
        _out[2] = _mm_shuffle_ps(swp2, swp3, 0x88);
        _out[3] = _mm_shuffle_ps(swp2, swp3, 0xDD);
    }


    // It works ONLY with transform matrix, not for generic matrix purpose
    // Moreover this not take into consider the scale, so this matrix is treated is of scale 1
    static NIX_INLINE void InverseNoScale(const __nixFloat4 * const _m, __nixFloat4 * _out)
    {
        // transpose the 3x3 part, so m03 = m13 = m23 = 0
        const __nixFloat4 lh = _mm_movelh_ps(_m[0], _m[1]);
        const __nixFloat4 hl = _mm_movehl_ps(_m[1], _m[0]);
        _out[0] = _mm_shuffle_ps(lh, _m[2], _MM_SHUFFLE(3, 0, 2, 0));
        _out[1] = _mm_shuffle_ps(lh, _m[2], _MM_SHUFFLE(3, 1, 3, 1));
        _out[2] = _mm_shuffle_ps(hl, _m[2], _MM_SHUFFLE(3, 2, 2, 0));

        // the forth line
        _out[3] = VectorHelper::Mul(_out[0], _mm_shuffle_ps(_m[3], _m[3], 0x00));
        _out[3] = VectorHelper::Add(_out[3], VectorHelper::Mul(_out[1], _mm_shuffle_ps(_m[3], _m[3], 0x55)));
        _out[3] = VectorHelper::Add(_out[3], VectorHelper::Mul(_out[2], _mm_shuffle_ps(_m[3], _m[3], 0xAA)));
        _out[3] = VectorHelper::Sub(VectorHelper::Set(0.f, 0.f, 0.f, 1.f), _out[3]);
    }

    // It works ONLY with transform matrix, not for generic matrix purpose
    static NIX_INLINE void Inverse(const __nixFloat4 * const _m, __nixFloat4 * _out)
    {
        // transpose the 3x3 part, so m03 = m13 = m23 = 0
        const __nixFloat4 lh = _mm_movelh_ps(_m[0], _m[1]);
        const __nixFloat4 hl = _mm_movehl_ps(_m[1], _m[0]);
        _out[0] = _mm_shuffle_ps(lh, _m[2], _MM_SHUFFLE(3, 0, 2, 0));
        _out[1] = _mm_shuffle_ps(lh, _m[2], _MM_SHUFFLE(3, 1, 3, 1));
        _out[2] = _mm_shuffle_ps(hl, _m[2], _MM_SHUFFLE(3, 2, 2, 0));

        __nixFloat4 sqr = VectorHelper::Mul(_out[0], _out[0]);
        sqr = VectorHelper::Add(sqr, VectorHelper::Mul(_out[1], _out[1]));
        sqr = VectorHelper::Add(sqr, VectorHelper::Mul(_out[2], _out[2]));

        const __nixFloat4 msk = _mm_cmplt_ps(sqr, VectorHelper::GetSmallNumber());

#   if NIX_ARCH & NIX_ARCH_SSE41_FLAG

        const __nixFloat4 rsqr = _mm_blendv_ps(VectorHelper::Div(VectorHelper::GetOne(), sqr), VectorHelper::GetOne(), msk);

#   else

        __nixFloat4 one = VectorHelper::GetOne();
        __nixFloat4 dva = VectorHelper::Div(one, sqr);
        
        one = _mm_and_ps(msk, one);
        dva = _mm_andnot_ps(msk, dva);

        const __nixFloat4 rsqr = _mm_or_ps(dva, one);

#   endif

        _out[0] = VectorHelper::Mul(_out[0], rsqr);
        _out[1] = VectorHelper::Mul(_out[1], rsqr);
        _out[2] = VectorHelper::Mul(_out[2], rsqr);

        // the forth line
        _out[3] = VectorHelper::Mul(_out[0], _mm_shuffle_ps(_m[3], _m[3], 0x00));
        _out[3] = VectorHelper::Add(_out[3], VectorHelper::Mul(_out[1], _mm_shuffle_ps(_m[3], _m[3], 0x55)));
        _out[3] = VectorHelper::Add(_out[3], VectorHelper::Mul(_out[2], _mm_shuffle_ps(_m[3], _m[3], 0xAA)));
        _out[3] = VectorHelper::Sub(VectorHelper::Set(0.f, 0.f, 0.f, 1.f), _out[3]);
    }

    static NIX_INLINE void Set(const __nixFloat4 * const _m, __nixFloat4* _out)
    {
        _out[0] = _m[0];
        _out[1] = _m[1];
        _out[2] = _m[2];
        _out[3] = _m[3];
    }

    static NIX_INLINE void Add(const __nixFloat4 * const _a, const __nixFloat4 * const _b, __nixFloat4* _out)
    {
        _out[0] = VectorHelper::Add(_a[0], _b[0]);
        _out[1] = VectorHelper::Add(_a[1], _b[1]);
        _out[2] = VectorHelper::Add(_a[2], _b[2]);
        _out[3] = VectorHelper::Add(_a[3], _b[3]);
    }

    static NIX_INLINE void Sub(const __nixFloat4 * const _a, const __nixFloat4 * const _b, __nixFloat4* _out)
    {
        _out[0] = VectorHelper::Sub(_a[0], _b[0]);
        _out[1] = VectorHelper::Sub(_a[1], _b[1]);
        _out[2] = VectorHelper::Sub(_a[2], _b[2]);
        _out[3] = VectorHelper::Sub(_a[3], _b[3]);
    }

    static NIX_INLINE void Add(const __nixFloat4 * const _m, nixFloat _s, __nixFloat4* _out)
    {
        const __nixFloat4 opv = VectorHelper::Splat(_s);
        _out[0] = VectorHelper::Add(_m[0], opv);
        _out[1] = VectorHelper::Add(_m[1], opv);
        _out[2] = VectorHelper::Add(_m[2], opv);
        _out[3] = VectorHelper::Add(_m[3], opv);
    }

    static NIX_INLINE void Sub(const __nixFloat4 * const _m, nixFloat _s, __nixFloat4* _out)
    {
        const __nixFloat4 opv = VectorHelper::Splat(_s);
        _out[0] = VectorHelper::Sub(_m[0], opv);
        _out[1] = VectorHelper::Sub(_m[1], opv);
        _out[2] = VectorHelper::Sub(_m[2], opv);
        _out[3] = VectorHelper::Sub(_m[3], opv);
    }

    static NIX_INLINE void Mul(const __nixFloat4 * const _m, nixFloat _s, __nixFloat4* _out)
    {
        const __nixFloat4 opv = VectorHelper::Splat(_s);
        _out[0] = VectorHelper::Mul(_m[0], opv);
        _out[1] = VectorHelper::Mul(_m[1], opv);
        _out[2] = VectorHelper::Mul(_m[2], opv);
        _out[3] = VectorHelper::Mul(_m[3], opv);
    }

    static NIX_INLINE void Div(const __nixFloat4 * const _m, nixFloat _s, __nixFloat4* _out)
    {
        const __nixFloat4 opv = VectorHelper::Div(VectorHelper::GetOne(), VectorHelper::Splat(_s));
        _out[0] = VectorHelper::Mul(_m[0], opv);
        _out[1] = VectorHelper::Mul(_m[1], opv);
        _out[2] = VectorHelper::Mul(_m[2], opv);
        _out[3] = VectorHelper::Mul(_m[3], opv);
    }

    static NIX_INLINE void Increment(const __nixFloat4 * const _m, __nixFloat4* _out)
    {
        const __nixFloat4 one = VectorHelper::GetOne();
        _out[0] = VectorHelper::Add(_m[0], one);
        _out[1] = VectorHelper::Add(_m[1], one);
        _out[2] = VectorHelper::Add(_m[2], one);
        _out[3] = VectorHelper::Add(_m[3], one);
    }

    static NIX_INLINE void Decrement(const __nixFloat4 * const _m, __nixFloat4* _out)
    {
        const __nixFloat4 one = VectorHelper::GetOne();
        _out[0] = VectorHelper::Sub(_m[0], one);
        _out[1] = VectorHelper::Sub(_m[1], one);
        _out[2] = VectorHelper::Sub(_m[2], one);
        _out[3] = VectorHelper::Sub(_m[3], one);
    }

    static NIX_INLINE void MulMatrixVector(const __nixFloat4 * const _m, const __nixFloat4& _v, __nixFloat4* _out)
    {
        const __nixFloat4 swp0 = _mm_shuffle_ps(_v, _v, _MM_SHUFFLE(0, 0, 0, 0));
        const __nixFloat4 swp1 = _mm_shuffle_ps(_v, _v, _MM_SHUFFLE(1, 1, 1, 1));
        const __nixFloat4 swp2 = _mm_shuffle_ps(_v, _v, _MM_SHUFFLE(2, 2, 2, 2));
        const __nixFloat4 swp3 = _mm_shuffle_ps(_v, _v, _MM_SHUFFLE(3, 3, 3, 3));

        const __nixFloat4 mul0 = VectorHelper::Mul(_m[0], swp0);
        const __nixFloat4 mul1 = VectorHelper::Mul(_m[1], swp1);
        const __nixFloat4 mul2 = VectorHelper::Mul(_m[2], swp2);
        const __nixFloat4 mul3 = VectorHelper::Mul(_m[3], swp3);

        const __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
        const __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);

        *_out = VectorHelper::Add(add0, add1);
    }

    static NIX_INLINE void MulVectorMatrix(const __nixFloat4& _v, const __nixFloat4 * const _m, __nixFloat4* _out)
    {
        const __nixFloat4 mul0 = VectorHelper::Mul(_v, _m[0]);
        const __nixFloat4 mul1 = VectorHelper::Mul(_v, _m[1]);
        const __nixFloat4 mul2 = VectorHelper::Mul(_v, _m[2]);
        const __nixFloat4 mul3 = VectorHelper::Mul(_v, _m[3]);

        const __nixFloat4 lo0 = _mm_unpacklo_ps(mul0, mul1);
        const __nixFloat4 hi0 = _mm_unpackhi_ps(mul0, mul1);
        const __nixFloat4 add0 = VectorHelper::Add(lo0, hi0);

        const __nixFloat4 lo1 = _mm_unpacklo_ps(mul2, mul3);
        const __nixFloat4 hi1 = _mm_unpackhi_ps(mul2, mul3);
        const __nixFloat4 add1 = VectorHelper::Add(lo1, hi1);

        const __nixFloat4 mlh = _mm_movelh_ps(add0, add1);
        const __nixFloat4 mhl = _mm_movehl_ps(add1, add0);

        *_out = VectorHelper::Add(mlh, mhl);
    }

#   endif

};


NIX_NAMESPACE_END