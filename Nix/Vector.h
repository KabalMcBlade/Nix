#pragma once

#include "CoreDefs.h"
#include "Architecture.h"
#include "Types.h"
#include "VectorHelper.h"

#ifdef _DEBUG
#include <Windows.h>    // just for debug
#endif

NIX_NAMESPACE_BEGIN


NIX_SIMD_ALIGN class Vector
{
public:
    //////////////////////////////////////////////////////////////////////////
    // Constructors
    NIX_INLINE Vector() : m_vec(VectorHelper::GetZero()) {}
    NIX_INLINE Vector(nixFloat _x, nixFloat _y, nixFloat _z) : m_vec(VectorHelper::Set(0.0f, _z, _y, _x)) {}
    NIX_INLINE Vector(nixFloat _x, nixFloat _y, nixFloat _z, nixFloat _w) : m_vec(VectorHelper::Set(_w, _z, _y, _x)) {}
    NIX_INLINE Vector(nixFloat _v) : m_vec(VectorHelper::Splat(_v)) {}
    NIX_INLINE Vector(const Vector& _copy) : m_vec(_copy.m_vec) {}
    NIX_INLINE Vector(Vector&& _copy) noexcept : m_vec(std::move(_copy.m_vec)) {}
    NIX_INLINE Vector(const __nixFloat4& _copy) : m_vec(_copy) {}
    NIX_INLINE Vector(__nixFloat4&& _copy) noexcept : m_vec(std::move(_copy)) {}

    //////////////////////////////////////////////////////////////////////////
    // Print function for debug purpose only

#ifdef _DEBUG
    NIX_INLINE void PrintOnConsole() const
    {
        nixFloat *val = (nixFloat*)&m_vec;
        char buffer[256];
        memset(buffer, 0, 256);
        sprintf_s(buffer, "vec[%.4f, %.4f, %.4f, %.4f]\n", val[3], val[2], val[1], val[0]);
        OutputDebugStringA(buffer);
    }

    NIX_INLINE void PrintOnConsole3() const
    {
        nixFloat *val = (nixFloat*)&m_vec;
        char buffer[256];
        memset(buffer, 0, 256);
        sprintf_s(buffer, "vec[%.4f, %.4f, %.4f]\n", val[3], val[2], val[1]);
        OutputDebugStringA(buffer);
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
    // Outer Functions (return new value and do not change local content)
    NIX_INLINE Vector GetAbs()
    {
        return VectorHelper::Abs(m_vec);
    }

    NIX_INLINE Vector GetFloor()
    {
        return VectorHelper::Floor(m_vec);
    }

    NIX_INLINE Vector GetCeil()
    {
        return VectorHelper::Ceil(m_vec);
    }

    // Computes and returns (this * _vecToMul) + _vecToAdd.
    NIX_INLINE Vector GetMulAdd(const Vector& _vecToMul, const Vector& _vecToAdd)
    {
        return VectorHelper::MulAdd(m_vec, _vecToMul.m_vec, _vecToAdd.m_vec);
    }

    NIX_INLINE Vector GetDot(const Vector& _other)
    {
        return VectorHelper::Dot(m_vec, _other.m_vec);
    }
   
    //////////////////////////////////////////////////////////////////////////
    // Inner Functions (do change local content)
    NIX_INLINE void Abs()
    {
        m_vec = VectorHelper::Abs(m_vec);
    }

    NIX_INLINE void Floor()
    {
        m_vec = VectorHelper::Floor(m_vec);
    }

    NIX_INLINE void Ceil()
    {
        m_vec = VectorHelper::Ceil(m_vec);
    }

    // Computes and set (this * _vecToMul) + _vecToAdd.
    NIX_INLINE void MulAdd(const Vector& _vecToMul, const Vector& _vecToAdd)
    {
        m_vec = VectorHelper::MulAdd(m_vec, _vecToMul.m_vec, _vecToAdd.m_vec);
    }

    NIX_INLINE void Dot(const Vector& _other)
    {
        m_vec = VectorHelper::Dot(m_vec, _other.m_vec);
    }

private:
    friend class VectorHelper;

    __nixFloat4 m_vec;
};


NIX_NAMESPACE_END