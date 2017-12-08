#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"
#include "VectorHelper.h"
#include "MathHelper.h"


NIX_NAMESPACE_BEGIN


NIX_SIMD_ALIGN class Quaternion
{
public:
    NIX_INLINE Quaternion() : m_quat(VectorHelper::Set(0.0f, 0.0f, 0.0f, 1.0f)) {}
    NIX_INLINE Quaternion(const Quaternion& _copy) : m_quat(_copy.m_quat) {}
    NIX_INLINE Quaternion(Quaternion&& _copy) noexcept : m_quat(std::move(_copy.m_quat)) {}
    NIX_INLINE Quaternion(const __nixFloat4& _copy) : m_quat(_copy) {}
    NIX_INLINE Quaternion(__nixFloat4&& _copy) noexcept : m_quat(std::move(_copy)) {}
    NIX_INLINE Quaternion(nixFloat _x, nixFloat _y, nixFloat _z, nixFloat _w) : m_quat(VectorHelper::Set(_x, _y, _z, _w)) {}
    NIX_INLINE Quaternion(const nixFloat& _radians, const Vector& _axis) { SetFromAngleAxis(_radians, _axis); }

    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    NIX_INLINE void Print() const
    {
        nixFloat *val = (nixFloat*)&m_quat;
        printf("quat[%.4f, %.4f, %.4f, %.4f]\n", val[0], val[1], val[2], val[3]);
    }

    NIX_INLINE void PrintClear() const
    {
        nixFloat *axis = (nixFloat*)&GetAxis().m_vec;
        nixFloat angle = GetAngle();
        printf("axis[%.1f, %.1f, %.1f] angle[rad: %.6f, deg: %.2f]\n", axis[0], axis[1], axis[2], angle, NIX_RAD_TO_DEG(angle));
    }
#endif

    //////////////////////////////////////////////////////////////////////////
    // Operators
    

    //////////////////////////////////////////////////////////////////////////
    // Functions
    NIX_INLINE void SetFromAngleAxis(const nixFloat& _radians, const Vector& _axis)
    {
        __nixFloat4 sin, cos;
        MathHelper::SinCos(VectorHelper::Mul(VectorHelper::Splat(_radians), VectorHelper::Splat(0.5f)), &sin, &cos);

        const __nixFloat4 quat = VectorHelper::Mul(_axis.m_vec, sin);
        const __nixFloat4 high = _mm_unpackhi_ps(quat, cos);  // [_ _ 1 z]
        m_quat = _mm_movelh_ps(quat, high);             // [1 z y x]
    }

    NIX_INLINE void SetFromAngleAxis(const nixFloat& _radians, nixFloat _x, nixFloat _y, nixFloat _z)
    {
        SetFromAngleAxis(_radians, Vector(_x, _y, _z));
    }

    // Mostly used for debug purpose
    NIX_INLINE Vector GetAxis() const
    {
        const __nixFloat4 cos = _mm_shuffle_ps(m_quat, m_quat, _MM_SHUFFLE(3, 3, 3, 3));
        const __nixFloat4 reciprocalSinAngle = VectorHelper::ReciprocalSqrt(VectorHelper::Sub(VectorHelper::GetOne(), VectorHelper::Mul(cos, cos)));
        const __nixFloat4 hp = VectorHelper::Mul(m_quat, reciprocalSinAngle);
        const __nixFloat4 high = _mm_unpackhi_ps(hp, VectorHelper::GetZero()); // [_ _ 0 z]
        const __nixFloat4 res = _mm_movelh_ps(hp, high);                       // [0 z y x]
        return res;
    }

    // Mostly used for debug purpose 
    // Slowly and very cache unfriendly
    NIX_INLINE nixFloat GetAngle() const
    {
        return std::acosf(((nixFloat*)&m_quat)[3]) * 2.0f;
    }

private:
    friend class VectorHelper;

    __nixFloat4 m_quat;
};


NIX_NAMESPACE_END