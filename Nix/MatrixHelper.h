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
    static NIX_INLINE void TransformInverseNoScale(const __nixFloat16 * const _m, __nixFloat16 * _out)
    {
        nixAssert(false, "AVX512 is not yet implemented");
    }

#   elif NIX_ARCH & NIX_ARCH_AVX_FLAG

    static NIX_INLINE void Mul(const __nixFloat8 * const _a, const __nixFloat8 * const _b, __nixFloat8* _out)
    {
        static const nixS32 NIX_SIMD_ALIGN_32 msk01[8] = { 0, 0, 0, 0, 1, 1, 1, 1 };
        static const nixS32 NIX_SIMD_ALIGN_32 msk23[8] = { 2, 2, 2, 2, 3, 3, 3, 3 };
        static const nixS32 NIX_SIMD_ALIGN_32 msk45[8] = { 4, 4, 4, 4, 5, 5, 5, 5 };
        static const nixS32 NIX_SIMD_ALIGN_32 msk67[8] = { 6, 6, 6, 6, 7, 7, 7, 7 };

        static const __nixInt8 prm01 = _mm256_load_si256(reinterpret_cast<const __nixInt8*>(msk01));
        static const __nixInt8 prm23 = _mm256_load_si256(reinterpret_cast<const __nixInt8*>(msk23));
        static const __nixInt8 prm45 = _mm256_load_si256(reinterpret_cast<const __nixInt8*>(msk45));
        static const __nixInt8 prm67 = _mm256_load_si256(reinterpret_cast<const __nixInt8*>(msk67));

        {
            const __nixFloat8 swp0 = _mm256_permutevar8x32_ps(_b[0], prm01);
            const __nixFloat8 swp1 = _mm256_permutevar8x32_ps(_b[0], prm23);
            const __nixFloat8 swp2 = _mm256_permutevar8x32_ps(_b[0], prm45);
            const __nixFloat8 swp3 = _mm256_permutevar8x32_ps(_b[0], prm67);

            const __nixFloat8 mul0 = VectorHelper::Mul(_a[0], swp0);
            const __nixFloat8 mul1 = VectorHelper::Mul(_a[1], swp1);
            const __nixFloat8 mul2 = VectorHelper::Mul(_a[0], swp2);
            const __nixFloat8 mul3 = VectorHelper::Mul(_a[1], swp3);

            const __nixFloat8 add0 = VectorHelper::Add(mul0, mul1);
            const __nixFloat8 add1 = VectorHelper::Add(mul2, mul3);
            const __nixFloat8 prm0 = _mm256_permute2f128_ps(add0, add1, _MM_SHUFFLE(0, 2, 0, 0));
            const __nixFloat8 prm1 = _mm256_permute2f128_ps(add0, add1, _MM_SHUFFLE(0, 3, 0, 1));

            _out[0] = VectorHelper::Add(prm0, prm1);
        }

        {
            const __nixFloat8 swp0 = _mm256_permutevar8x32_ps(_b[1], prm01);
            const __nixFloat8 swp1 = _mm256_permutevar8x32_ps(_b[1], prm23);
            const __nixFloat8 swp2 = _mm256_permutevar8x32_ps(_b[1], prm45);
            const __nixFloat8 swp3 = _mm256_permutevar8x32_ps(_b[1], prm67);

            const __nixFloat8 mul0 = VectorHelper::Mul(_a[0], swp0);
            const __nixFloat8 mul1 = VectorHelper::Mul(_a[1], swp1);
            const __nixFloat8 mul2 = VectorHelper::Mul(_a[0], swp2);
            const __nixFloat8 mul3 = VectorHelper::Mul(_a[1], swp3);

            const __nixFloat8 add0 = VectorHelper::Add(mul0, mul1);
            const __nixFloat8 add1 = VectorHelper::Add(mul2, mul3);
            const __nixFloat8 prm0 = _mm256_permute2f128_ps(add0, add1, _MM_SHUFFLE(0, 2, 0, 0));
            const __nixFloat8 prm1 = _mm256_permute2f128_ps(add0, add1, _MM_SHUFFLE(0, 3, 0, 1));

            _out[1] = VectorHelper::Add(prm0, prm1);
        }

    }

    static NIX_INLINE void Transpose(const __nixFloat8 * const _m, __nixFloat8 * _out)
    {
        static const nixS32 NIX_SIMD_ALIGN_32 msk01[8] = { 0, 4, 2, 6, 1, 5, 3, 7 };
        static const nixS32 NIX_SIMD_ALIGN_32 msk23[8] = { 2, 6, 0, 4, 3, 7, 1, 5 };

        const __nixInt8 prm1 = _mm256_load_si256(reinterpret_cast<const __nixInt8*>(msk01));
        const __nixInt8 prm2 = _mm256_load_si256(reinterpret_cast<const __nixInt8*>(msk23));

        const __nixFloat8 a0 = _mm256_permutevar8x32_ps(_m[0], prm1);
        const __nixFloat8 a1 = _mm256_permutevar8x32_ps(_m[1], prm2);

        _out[0] = _mm256_blend_ps(a0, a1, 0xCC);
        _out[1] = _mm256_shuffle_ps(a0, a1, 0x4E);
    }

    // It works ONLY with transform matrix, not for generic matrix purpose
    // Moreover this not take into consider the scale, so this matrix is treated is of scale 1
    static NIX_INLINE void TransformInverseNoScale(const __nixFloat8 * const _m, __nixFloat8 * _out)
    {
        /*
        // transpose the 3x3 part, so m03 = m13 = m23 = 0
        __nixFloat4 lh = _mm_movelh_ps(_m[0], _m[1]);
        __nixFloat4 hl = _mm_movehl_ps(_m[0], _m[1]);
        _out[0] = _mm_shuffle_ps(lh, _m[2], _MM_SHUFFLE(3, 0, 2, 0));
        _out[1] = _mm_shuffle_ps(lh, _m[2], _MM_SHUFFLE(3, 1, 3, 1));
        _out[2] = _mm_shuffle_ps(hl, _m[2], _MM_SHUFFLE(3, 2, 2, 0));

        // the forth line
        _out[3] = VectorHelper::Mul(_out[0], _mm_shuffle_ps(_m[3], _m[3], 0x00));
        _out[3] = VectorHelper::Add(_out[3], VectorHelper::Mul(_out[1], _mm_shuffle_ps(_m[3], _m[3], 0x55)));
        _out[3] = VectorHelper::Add(_out[3], VectorHelper::Mul(_out[2], _mm_shuffle_ps(_m[3], _m[3], 0xAA)));
        _out[3] = VectorHelper::Sub(VectorHelper::Set(0.f, 0.f, 0.f, 1.f), _out[3]);
        */
    }

#   else 

    static NIX_INLINE void Mul(const __nixFloat4 * const _a, const __nixFloat4 * const _b, __nixFloat4* _out)
    {
        {
            const __nixFloat4 swp0 = _mm_shuffle_ps(_b[0], _b[0], _MM_SHUFFLE(0, 0, 0, 0));
            const __nixFloat4 swp1 = _mm_shuffle_ps(_b[0], _b[0], _MM_SHUFFLE(1, 1, 1, 1));
            const __nixFloat4 swp2 = _mm_shuffle_ps(_b[0], _b[0], _MM_SHUFFLE(2, 2, 2, 2));
            const __nixFloat4 swp3 = _mm_shuffle_ps(_b[0], _b[0], _MM_SHUFFLE(3, 3, 3, 3));

            const __nixFloat4 mul0 = VectorHelper::Mul(_a[0], swp0);
            const __nixFloat4 mul1 = VectorHelper::Mul(_a[1], swp1);
            const __nixFloat4 mul2 = VectorHelper::Mul(_a[2], swp2);
            const __nixFloat4 mul3 = VectorHelper::Mul(_a[3], swp3);

            const __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            const __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            const __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            _out[0] = add2;
        }

        {
            const __nixFloat4 swp0 = _mm_shuffle_ps(_b[1], _b[1], _MM_SHUFFLE(0, 0, 0, 0));
            const __nixFloat4 swp1 = _mm_shuffle_ps(_b[1], _b[1], _MM_SHUFFLE(1, 1, 1, 1));
            const __nixFloat4 swp2 = _mm_shuffle_ps(_b[1], _b[1], _MM_SHUFFLE(2, 2, 2, 2));
            const __nixFloat4 swp3 = _mm_shuffle_ps(_b[1], _b[1], _MM_SHUFFLE(3, 3, 3, 3));

            const __nixFloat4 mul0 = VectorHelper::Mul(_a[0], swp0);
            const __nixFloat4 mul1 = VectorHelper::Mul(_a[1], swp1);
            const __nixFloat4 mul2 = VectorHelper::Mul(_a[2], swp2);
            const __nixFloat4 mul3 = VectorHelper::Mul(_a[3], swp3);

            const __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            const __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            const __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            _out[1] = add2;
        }

        {
            const __nixFloat4 swp0 = _mm_shuffle_ps(_b[2], _b[2], _MM_SHUFFLE(0, 0, 0, 0));
            const __nixFloat4 swp1 = _mm_shuffle_ps(_b[2], _b[2], _MM_SHUFFLE(1, 1, 1, 1));
            const __nixFloat4 swp2 = _mm_shuffle_ps(_b[2], _b[2], _MM_SHUFFLE(2, 2, 2, 2));
            const __nixFloat4 swp3 = _mm_shuffle_ps(_b[2], _b[2], _MM_SHUFFLE(3, 3, 3, 3));

            const __nixFloat4 mul0 = VectorHelper::Mul(_a[0], swp0);
            const __nixFloat4 mul1 = VectorHelper::Mul(_a[1], swp1);
            const __nixFloat4 mul2 = VectorHelper::Mul(_a[2], swp2);
            const __nixFloat4 mul3 = VectorHelper::Mul(_a[3], swp3);

            const __nixFloat4 add0 = VectorHelper::Add(mul0, mul1);
            const __nixFloat4 add1 = VectorHelper::Add(mul2, mul3);
            const __nixFloat4 add2 = VectorHelper::Add(add0, add1);

            _out[2] = add2;
        }

        {
            const __nixFloat4 swp0 = _mm_shuffle_ps(_b[3], _b[3], _MM_SHUFFLE(0, 0, 0, 0));
            const __nixFloat4 swp1 = _mm_shuffle_ps(_b[3], _b[3], _MM_SHUFFLE(1, 1, 1, 1));
            const __nixFloat4 swp2 = _mm_shuffle_ps(_b[3], _b[3], _MM_SHUFFLE(2, 2, 2, 2));
            const __nixFloat4 swp3 = _mm_shuffle_ps(_b[3], _b[3], _MM_SHUFFLE(3, 3, 3, 3));

            const __nixFloat4 mul0 = VectorHelper::Mul(_a[0], swp0);
            const __nixFloat4 mul1 = VectorHelper::Mul(_a[1], swp1);
            const __nixFloat4 mul2 = VectorHelper::Mul(_a[2], swp2);
            const __nixFloat4 mul3 = VectorHelper::Mul(_a[3], swp3);

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
    static NIX_INLINE void TransformInverseNoScale(const __nixFloat4 * const _m, __nixFloat4 * _out)
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
    static NIX_INLINE void TransformInverse(const __nixFloat4 * const _m, __nixFloat4 * _out)
    {
        // transpose the 3x3 part, so m03 = m13 = m23 = 0
        const __nixFloat4 lh = _mm_movelh_ps(_m[0], _m[1]);
        const __nixFloat4 hl = _mm_movehl_ps(_m[1], _m[0]);
        _out[0] = _mm_shuffle_ps(lh, _m[2], _MM_SHUFFLE(3, 0, 2, 0));
        _out[1] = _mm_shuffle_ps(lh, _m[2], _MM_SHUFFLE(3, 1, 3, 1));
        _out[2] = _mm_shuffle_ps(hl, _m[2], _MM_SHUFFLE(3, 2, 2, 0));

        __nixFloat4 sqr;
        sqr = VectorHelper::Mul(_out[0], _out[0]);
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

#   endif




private:

};


NIX_NAMESPACE_END