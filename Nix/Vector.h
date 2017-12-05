#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"
#include "VectorHelper.h"

NIX_NAMESPACE_BEGIN


NIX_SIMD_ALIGN class Vector
{
public:
    //////////////////////////////////////////////////////////////////////////
    // Constructors
    NIX_INLINE Vector() : m_vec(VectorHelper::GetZero()) {}
    NIX_INLINE Vector(nixFloat _x, nixFloat _y, nixFloat _z) : m_vec(VectorHelper::Set(_x, _y, _z, 0.0f)) {}
    NIX_INLINE Vector(nixFloat _x, nixFloat _y, nixFloat _z, nixFloat _w) : m_vec(VectorHelper::Set(_x, _y, _z, _w)) {}
    NIX_INLINE Vector(nixFloat _v) : m_vec(VectorHelper::Splat(_v)) {}
    NIX_INLINE Vector(const Vector& _copy) : m_vec(_copy.m_vec) {}
    NIX_INLINE Vector(Vector&& _copy) noexcept : m_vec(std::move(_copy.m_vec)) {}
    NIX_INLINE Vector(const __nixFloat4& _copy) : m_vec(_copy) {}
    NIX_INLINE Vector(__nixFloat4&& _copy) noexcept : m_vec(std::move(_copy)) {}

    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    NIX_INLINE void Print() const
    {
        nixFloat *val = (nixFloat*)&m_vec;
        printf("vec[%.4f, %.4f, %.4f, %.4f]\n", val[0], val[1], val[2], val[3]);
    }

    NIX_INLINE void Print3() const
    {
        nixFloat *val = (nixFloat*)&m_vec;
        printf("vec[%.4f, %.4f, %.4f]\n", val[0], val[1], val[2]);
    }
#endif

    //////////////////////////////////////////////////////////////////////////
    // Operators
    NIX_INLINE Vector& operator= (const Vector& _v)
    {
        this->m_vec = _v.m_vec;
        return *this;
    }
    NIX_INLINE Vector& operator+=(const Vector& _v)
    {
        this->m_vec = VectorHelper::Add(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator-=(const Vector& _v)
    {
        this->m_vec = VectorHelper::Sub(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator*=(const Vector& _v)
    {
        this->m_vec = VectorHelper::Mul(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator/=(const Vector& _v)
    {
        this->m_vec = VectorHelper::Div(this->m_vec, _v.m_vec);
        return *this;
    }
    NIX_INLINE Vector& operator+=(const nixFloat& _s)
    {
        this->m_vec = VectorHelper::Add(this->m_vec, VectorHelper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator-=(const nixFloat& _s)
    {
        this->m_vec = VectorHelper::Sub(this->m_vec, VectorHelper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator*=(const nixFloat& _s)
    {
        this->m_vec = VectorHelper::Mul(this->m_vec, VectorHelper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator/=(const nixFloat& _s)
    {
        this->m_vec = VectorHelper::Div(this->m_vec, VectorHelper::Splat(_s));
        return *this;
    }
    NIX_INLINE Vector& operator++()
    {
        this->m_vec = VectorHelper::Add(this->m_vec, VectorHelper::GetOne());
        return *this;
    }
    NIX_INLINE Vector& operator--()
    {
        this->m_vec = VectorHelper::Sub(this->m_vec, VectorHelper::GetOne());
        return *this;
    }

    //////////////////////////////////////////////////////////////////////////
    NIX_INLINE Vector Abs()
    {
        return VectorHelper::Abs(m_vec);
    }

    NIX_INLINE Vector Floor()
    {
        return VectorHelper::Floor(m_vec);
    }

    NIX_INLINE Vector Ceil()
    {
        return VectorHelper::Ceil(m_vec);
    }

    // Computes and returns (this * _vecToMul) + _vecToAdd.
    NIX_INLINE Vector MulAdd(const Vector& _vecToMul, const Vector& _vecToAdd)
    {
        return VectorHelper::MulAdd(m_vec, _vecToMul.m_vec, _vecToAdd.m_vec);
    }

    NIX_INLINE Vector Dot(const Vector& _other)
    {
        return VectorHelper::Dot(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Dot3(const Vector& _other)
    {
        return VectorHelper::Dot3(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector SquareLength()
    {
        return VectorHelper::SquareLength(m_vec);
    }

    NIX_INLINE Vector Length()
    {
        return VectorHelper::Length(m_vec);
    }

    NIX_INLINE Vector SquareDistance(const Vector& _other)
    {
        return VectorHelper::SquareDistance(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Distance(const Vector& _other)
    {
        return VectorHelper::Distance(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Cross(const Vector& _other)
    {
        return VectorHelper::Cross(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Mod(const Vector& _other)
    {
        return VectorHelper::Mod(m_vec, _other.m_vec);
    }

    NIX_INLINE Vector Clamp(const Vector& _min, const Vector& _max)
    {
        return VectorHelper::Clamp(m_vec, _min.m_vec, _max.m_vec);
    }

private:
    friend class VectorHelper;

    __nixFloat4 m_vec;
};


NIX_NAMESPACE_END