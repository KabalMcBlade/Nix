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
    NIX_INLINE Quaternion(const Vector& _copy) : m_quat(_copy.m_vec) {}
    NIX_INLINE Quaternion(Vector&& _copy) noexcept : m_quat(std::move(_copy.m_vec)) {}
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
    
    NIX_INLINE Quaternion& operator=(const Quaternion& _q)
    {
        this->m_quat = _q.m_quat;
        return *this;
    }

    NIX_INLINE Quaternion& operator*=(nixFloat& _s)
    {
        this->m_quat = VectorHelper::Mul(this->m_quat, VectorHelper::Splat(_s));
        return *this;
    }

    NIX_INLINE Quaternion& operator/=(nixFloat& _s)
    {
        this->m_quat = VectorHelper::Div(this->m_quat, VectorHelper::Splat(_s));
        return *this;
    }

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

    NIX_INLINE Vector Length() const
    {
        return VectorHelper::FastSqrt(VectorHelper::Dot(m_quat, m_quat));
    }

    NIX_INLINE Quaternion Normalize() const
    {
        Vector v = 1.0f / Length();
        Quaternion q(v);
        return VectorHelper::Mul(m_quat, q.m_quat);
    }

    NIX_INLINE Vector Dot(const Quaternion& _other) const
    {
        return VectorHelper::Dot(m_quat, _other.m_quat);
    }

    // It means go FROM *this* quaternion TO *other* quaternion in T
    NIX_INLINE Vector LerpTo(const Quaternion& _to, const Vector& _time) const
    {
        return VectorHelper::Lerp(m_quat, _to.m_quat, _time.m_vec);
    }

    // It means go FROM *other* quaternion TO *this* quaternion in T
    NIX_INLINE Vector LerpFrom(const Quaternion& _from, const Vector& _time) const
    {
        return VectorHelper::Lerp(_from.m_quat, m_quat, _time.m_vec);
    }

    // It means go FROM *this* quaternion TO *other* quaternion in T
    NIX_INLINE Vector LerpTo(const Quaternion& _to, const nixFloat& _time) const
    {
        return LerpTo(_to, VectorHelper::Splat(_time));
    }

    // It means go FROM *other* quaternion TO *this* quaternion in T
    NIX_INLINE Vector LerpFrom(const Quaternion& _from, const nixFloat& _time) const
    {
        return LerpFrom(_from, VectorHelper::Splat(_time));
    }

    NIX_INLINE Quaternion Slerp(const Quaternion& _other, const nixFloat& _time) const
    {
        Vector vCosTheta = Dot(_other);

        nixFloat cosTheta = 0;
        _mm_store_ss(&cosTheta, vCosTheta.m_vec);

        if (cosTheta < 0.0f)
        {
            cosTheta = -cosTheta;
        }

        if (cosTheta > 1.0f - MathHelper::kEpsilon)
        {
            return VectorHelper::Add(m_quat, VectorHelper::Mul(VectorHelper::Splat(_time), VectorHelper::Sub(_other.m_quat, m_quat)));
        }
        else
        {
            nixFloat angle = std::acosh(cosTheta);

            const __nixFloat4 sin = MathHelper::Sin(VectorHelper::Set(0.0f, angle, _time * angle,  (1.0f - _time) * angle));
            const __nixFloat4 div = VectorHelper::Div(VectorHelper::GetOne(), _mm_shuffle_ps(sin, sin, _MM_SHUFFLE(1, 1, 1, 1)));

            return VectorHelper::Mul(VectorHelper::Add(VectorHelper::Mul(_mm_shuffle_ps(sin, sin, _MM_SHUFFLE(3, 3, 3, 3)), m_quat), VectorHelper::Mul(_mm_shuffle_ps(sin, sin, _MM_SHUFFLE(2, 2, 2, 2)), _other.m_quat)), div);
        }
    }

    NIX_INLINE Quaternion Conjugate() const
    {
        return VectorHelper::Mul(m_quat, VectorHelper::Set(-1.0f, -1.0f, -1.0f, 1.0f));
    }

    NIX_INLINE Quaternion Inverse() const
    {
        Vector dot = Dot(m_quat);
        nixFloat sDot = 0;
        _mm_store_ss(&sDot, dot.m_vec);
        return Conjugate() / sDot;
    }

    NIX_INLINE Quaternion FromEuler(const Vector& _euler) const
    {
        const __nixFloat4 angle = VectorHelper::Mul(VectorHelper::GetHalf(), _euler.m_vec);

        __nixFloat4 sn;
        __nixFloat4 cs;
        MathHelper::SinCos(angle, &sn, &cs);

        const __nixFloat4 sc = _mm_shuffle_ps(sn, cs, _MM_SHUFFLE(1, 2, 2, 1));

        const __nixFloat4 l = VectorHelper::Mul(VectorHelper::Mul(_mm_shuffle_ps(sn, sc, _MM_SHUFFLE(2, 0, 0, 2)), _mm_shuffle_ps(cs, cs, _MM_SHUFFLE(0, 2, 2, 0))), _mm_shuffle_ps(cs, cs, _MM_SHUFFLE(1, 1, 0, 1)));
        const __nixFloat4 r = VectorHelper::Mul(VectorHelper::Mul(_mm_shuffle_ps(cs, sc, _MM_SHUFFLE(2, 0, 3, 1)), _mm_shuffle_ps(sn, sn, _MM_SHUFFLE(0, 2, 2, 0))), _mm_shuffle_ps(sn, sn, _MM_SHUFFLE(1, 1, 0, 1)));

        const __nixFloat4 sum = VectorHelper::Add(l, r);
        const __nixFloat4 dif = VectorHelper::Sub(l, r);
        const __nixFloat4 sd = _mm_shuffle_ps(sum, dif, _MM_SHUFFLE(0, 2, 1, 3));
        const __nixFloat4 res = _mm_shuffle_ps(sd, sd, _MM_SHUFFLE(0, 2, 1, 3));

        return res;
    }

private:
    friend class VectorHelper;
    friend class Vector;

    // for global operators
    friend NIX_INLINE Quaternion operator- (const Quaternion& _q);
    friend NIX_INLINE Quaternion operator+ (const Quaternion& _q1, const Quaternion& _q2);
    friend NIX_INLINE Quaternion operator* (const Quaternion& _q1, const Quaternion& _q2);
    friend NIX_INLINE Vector operator* (const Quaternion& _q, const Vector& _v);
    friend NIX_INLINE Vector operator* (const Vector& _v, const Quaternion& _q);
    friend NIX_INLINE Quaternion operator* (const Quaternion& _q, nixFloat _s);
    friend NIX_INLINE Quaternion operator* (nixFloat _s, const Quaternion& _q);
    friend NIX_INLINE Quaternion operator/ (const Quaternion& _q, nixFloat _s);

    __nixFloat4 m_quat;
};

//////////////////////////////////////////////////////////////////////////
// Operators

// negate operator
NIX_INLINE Quaternion operator- (const Quaternion& _q)
{
    return VectorHelper::Mul(_q.m_quat, VectorHelper::GetMinusOne());
}

// operator+
NIX_INLINE Quaternion operator+ (const Quaternion& _q1, const Quaternion& _q2)
{
    return VectorHelper::Add(_q1.m_quat, _q2.m_quat);
}

//operator*
NIX_INLINE Quaternion operator* (const Quaternion& _q1, const Quaternion& _q2)
{
    const __nixFloat4 mul0 = VectorHelper::Mul(_q1.m_quat, _mm_shuffle_ps(_q2.m_quat, _q2.m_quat, _MM_SHUFFLE(0, 1, 2, 3)));
    const __nixFloat4 mul1 = VectorHelper::Mul(_q1.m_quat, _mm_shuffle_ps(_q2.m_quat, _q2.m_quat, _MM_SHUFFLE(1, 0, 3, 2)));
    const __nixFloat4 mul2 = VectorHelper::Mul(_q1.m_quat, _mm_shuffle_ps(_q2.m_quat, _q2.m_quat, _MM_SHUFFLE(2, 3, 0, 1)));
    const __nixFloat4 mul3 = VectorHelper::Mul(_q1.m_quat, _q2.m_quat);

#   if defined(NIX_ARCH_SSE41)
    const __nixFloat4 add00 = _mm_dp_ps(mul0, VectorHelper::Set(1.0f, 1.0f, -1.0f, 1.0f), 0xff);
    const __nixFloat4 add01 = _mm_dp_ps(mul1, VectorHelper::Set(-1.0f, 1.0f, 1.0f, 1.0f), 0xff);
    const __nixFloat4 add02 = _mm_dp_ps(mul2, VectorHelper::Set(1.0f, -1.0f, 1.0f, 1.0f), 0xff);
    const __nixFloat4 add03 = _mm_dp_ps(mul3, VectorHelper::Set(-1.0f, -1.0f, -1.0f, 1.0f), 0xff);
#   else
    const __nixFloat4 mul00 = VectorHelper::Mul(mul0, VectorHelper::Set(1.0f, 1.0f, -1.0f, 1.0f));
    const __nixFloat4 mul01 = VectorHelper::Mul(mul1, VectorHelper::Set(-1.0f, 1.0f, 1.0f, 1.0f));
    const __nixFloat4 mul02 = VectorHelper::Mul(mul2, VectorHelper::Set(1.0f, -1.0f, 1.0f, 1.0f));
    const __nixFloat4 mul03 = VectorHelper::Mul(mul3, VectorHelper::Set(-1.0f, -1.0f, -1.0f, 1.0f));

    const __nixFloat4 add0 = VectorHelper::Add(mul00, _mm_movehl_ps(mul00, mul00));
    const __nixFloat4 add1 = VectorHelper::Add(mul01, _mm_movehl_ps(mul01, mul01));
    const __nixFloat4 add2 = VectorHelper::Add(mul02, _mm_movehl_ps(mul02, mul02));
    const __nixFloat4 add3 = VectorHelper::Add(mul03, _mm_movehl_ps(mul03, mul03));

    const __nixFloat4 add00 = _mm_add_ss(add0, _mm_shuffle_ps(add0, add0, 1));
    const __nixFloat4 add01 = _mm_add_ss(add1, _mm_shuffle_ps(add1, add1, 1));
    const __nixFloat4 add02 = _mm_add_ss(add2, _mm_shuffle_ps(add2, add2, 1));
    const __nixFloat4 add03 = _mm_add_ss(add3, _mm_shuffle_ps(add3, add3, 1));
#endif

    const __nixFloat4 xxyy = _mm_shuffle_ps(add00, add01, _MM_SHUFFLE(0, 0, 0, 0));
    const __nixFloat4 zzww = _mm_shuffle_ps(add02, add03, _MM_SHUFFLE(0, 0, 0, 0));
    
    return _mm_shuffle_ps(xxyy, zzww, _MM_SHUFFLE(2, 0, 2, 0));
}

NIX_INLINE Vector operator* (const Quaternion& _q, const Vector& _v)
{
    static const __nixFloat4 two = VectorHelper::Splat(2.0f);

    const __nixFloat4 q_wwww = _mm_shuffle_ps(_q.m_quat, _q.m_quat, _MM_SHUFFLE(3, 3, 3, 3));
    const __nixFloat4 q_swp0 = _mm_shuffle_ps(_q.m_quat, _q.m_quat, _MM_SHUFFLE(3, 0, 2, 1));
    const __nixFloat4 q_swp1 = _mm_shuffle_ps(_q.m_quat, _q.m_quat, _MM_SHUFFLE(3, 1, 0, 2));
    const __nixFloat4 v_swp0 = _mm_shuffle_ps(_v.m_vec, _v.m_vec, _MM_SHUFFLE(3, 0, 2, 1));
    const __nixFloat4 v_swp1 = _mm_shuffle_ps(_v.m_vec, _v.m_vec, _MM_SHUFFLE(3, 1, 0, 2));

    const __nixFloat4 qv = VectorHelper::Sub(VectorHelper::Mul(q_swp0, v_swp1), VectorHelper::Mul(q_swp1, v_swp0));
    const __nixFloat4 qv_swp0 = _mm_shuffle_ps(qv, qv, _MM_SHUFFLE(3, 0, 2, 1));
    const __nixFloat4 qv_swp1 = _mm_shuffle_ps(qv, qv, _MM_SHUFFLE(3, 1, 0, 2));
    const __nixFloat4 qqv = VectorHelper::Sub(VectorHelper::Mul(q_swp0, qv_swp1), VectorHelper::Mul(q_swp1, qv_swp0));

    const __nixFloat4 mul0 = VectorHelper::Mul(qv, VectorHelper::Mul(q_wwww, two));
    const __nixFloat4 mul1 = VectorHelper::Mul(qqv, two);

    return VectorHelper::Add(_v.m_vec, VectorHelper::Add(mul0, mul1));
}

NIX_INLINE Vector operator* (const Vector& _v, const Quaternion& _q)
{
    Quaternion inv = _q.Inverse();
    return inv * _v;
}

NIX_INLINE Quaternion operator* (const Quaternion& _q, nixFloat _s)
{
    return VectorHelper::Mul(_q.m_quat, VectorHelper::Splat(_s));
}

NIX_INLINE Quaternion operator* (nixFloat _s, const Quaternion& _q)
{
    return VectorHelper::Mul(VectorHelper::Splat(_s), _q.m_quat);
}

//operator/
NIX_INLINE Quaternion operator/ (const Quaternion& _q, nixFloat _s)
{
    return VectorHelper::Div(_q.m_quat, VectorHelper::Splat(_s));
}

NIX_NAMESPACE_END