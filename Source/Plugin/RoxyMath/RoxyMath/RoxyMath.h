#pragma once

#include <RoxySTD/RoxySTD.h>

// @TODO SIMD
#define ROXY_ENABLE_SIMD 1

namespace Roxy::Math
{

template <typename T>
ROXY_NODISCARD ROXY_INLINE constexpr T FastInvSqrt(T X) noexcept requires std::is_floating_point_v<T>
{
    return static_cast<T>(1) / std::sqrt(X);
}

template <>
ROXY_NODISCARD ROXY_INLINE constexpr float FastInvSqrt(float X) noexcept
{
    const float Half = 0.5f * X;
    U32 i = std::bit_cast<U32>(X);
    i = 0x5f3759df - (i >> 1);
    float Y = std::bit_cast<float>(i);
    Y = Y * (1.5f - Half * Y * Y);
    return Y;
}

template <>
ROXY_NODISCARD ROXY_INLINE constexpr double FastInvSqrt(double X) noexcept
{
    const double Half = 0.5 * X;
    U64 i = std::bit_cast<U64>(X);
    i = 0x5fe6eb50c7b537a9ULL - (i >> 1);
    double Y = std::bit_cast<double>(i);
    Y = Y * (1.5 - Half * Y * Y);
    return Y;
}

template <typename T>
ROXY_NODISCARD ROXY_INLINE constexpr T FastSqrt(T X) noexcept requires std::is_floating_point_v<T>
{
    return X * FastInvSqrt(X);
}

template <typename T, FIndex Dim> requires std::is_arithmetic_v<T> && (2 <= Dim && Dim <= 4) class TVec;

template <typename FVec, typename T, FIndex Dim> requires std::is_arithmetic_v<T> && (2 <= Dim && Dim <= 4)
class TVecBase
{
public:
    ROXY_NODISCARD ROXY_INLINE T& operator[](FIndex Idx) noexcept
    {
        ROXY_ASSERT(0 <= Idx && Idx < Dim);
        return static_cast<FVec*>(this)->Payload[Idx];
    }
    ROXY_NODISCARD ROXY_INLINE const T& operator[](FIndex Idx) const noexcept
    {
        ROXY_ASSERT(0 <= Idx && Idx < Dim);
        return static_cast<const FVec*>(this)->Payload[Idx];
    }

    template <typename U>
    ROXY_NODISCARD ROXY_INLINE constexpr TVec<U, Dim> As() const noexcept
    {
        TVec<U, Dim> Temp;
        if constexpr (Dim == 2)
        {
            Temp[0] = static_cast<U>((*this)[0]);
            Temp[1] = static_cast<U>((*this)[1]);
        }
        else if constexpr (Dim == 3)
        {
            Temp[0] = static_cast<U>((*this)[0]);
            Temp[1] = static_cast<U>((*this)[1]);
            Temp[2] = static_cast<U>((*this)[2]);
        }
        else if constexpr (Dim == 4)
        {
            Temp[0] = static_cast<U>((*this)[0]);
            Temp[1] = static_cast<U>((*this)[1]);
            Temp[2] = static_cast<U>((*this)[2]);
            Temp[3] = static_cast<U>((*this)[3]);
        }
        return Temp;
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FVec Zero() noexcept
    {
        return FVec{};
    }
    ROXY_NODISCARD ROXY_INLINE static constexpr FVec One() noexcept
    {
        FVec Temp{};
        if constexpr (Dim == 2)
        {
            Temp[0] = static_cast<T>(1);
            Temp[1] = static_cast<T>(1);
        }
        else if constexpr (Dim == 3)
        {
            Temp[0] = static_cast<T>(1);
            Temp[1] = static_cast<T>(1);
            Temp[2] = static_cast<T>(1);
        }
        else if constexpr (Dim == 4)
        {
            Temp[0] = static_cast<T>(1);
            Temp[1] = static_cast<T>(1);
            Temp[2] = static_cast<T>(1);
            Temp[3] = static_cast<T>(1);
        }
        return Temp;
    }
    ROXY_NODISCARD ROXY_INLINE static constexpr FVec Axis(FIndex Idx) noexcept
    {
        ROXY_ASSERT(0 <= Idx && Idx < Dim);
        FVec Temp{};
        Temp[Idx] = static_cast<T>(1);
        return Temp;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr bool operator==(const FVec& Oth) const noexcept
    {
        if constexpr (Dim == 2)
        {
            return ((*this)[0] == Oth[0]) && ((*this)[1] == Oth[1]);
        }
        else if constexpr (Dim == 3)
        {
            return ((*this)[0] == Oth[0]) && ((*this)[1] == Oth[1]) && ((*this)[2] == Oth[2]);
        }
        else if constexpr (Dim == 4)
        {
            return ((*this)[0] == Oth[0]) && ((*this)[1] == Oth[1]) && ((*this)[2] == Oth[2]) && ((*this)[3] == Oth[3]);
        }
        ROXY_ASSERT(false && "Unreachable");
    }
    ROXY_NODISCARD ROXY_INLINE constexpr bool operator!=(const FVec& Oth) const noexcept
    {
        return !(*this == Oth);
    }

    ROXY_INLINE constexpr FVec& operator+=(const FVec& Oth) noexcept
    {
        if constexpr (Dim == 2)
        {
            (*this)[0] += Oth[0];
            (*this)[1] += Oth[1];
        }
        else if constexpr (Dim == 3)
        {
            (*this)[0] += Oth[0];
            (*this)[1] += Oth[1];
            (*this)[2] += Oth[2];
        }
        else if constexpr (Dim == 4)
        {
            (*this)[0] += Oth[0];
            (*this)[1] += Oth[1];
            (*this)[2] += Oth[2];
            (*this)[3] += Oth[3];
        }
        return static_cast<FVec&>(*this);
    }
    ROXY_INLINE constexpr FVec& operator-=(const FVec& Oth) noexcept
    {
        if constexpr (Dim == 2)
        {
            (*this)[0] -= Oth[0];
            (*this)[1] -= Oth[1];
        }
        else if constexpr (Dim == 3)
        {
            (*this)[0] -= Oth[0];
            (*this)[1] -= Oth[1];
            (*this)[2] -= Oth[2];
        }
        else if constexpr (Dim == 4)
        {
            (*this)[0] -= Oth[0];
            (*this)[1] -= Oth[1];
            (*this)[2] -= Oth[2];
            (*this)[3] -= Oth[3];
        }
        return static_cast<FVec&>(*this);
    }
    ROXY_INLINE constexpr FVec& operator*=(const FVec& Oth) noexcept
    {
        if constexpr (Dim == 2)
        {
            (*this)[0] *= Oth[0];
            (*this)[1] *= Oth[1];
        }
        else if constexpr (Dim == 3)
        {
            (*this)[0] *= Oth[0];
            (*this)[1] *= Oth[1];
            (*this)[2] *= Oth[2];
        }
        else if constexpr (Dim == 4)
        {
            (*this)[0] *= Oth[0];
            (*this)[1] *= Oth[1];
            (*this)[2] *= Oth[2];
            (*this)[3] *= Oth[3];
        }
        return static_cast<FVec&>(*this);
    }
    ROXY_INLINE constexpr FVec& operator/=(const FVec& Oth) noexcept
    {
        if constexpr (Dim == 2)
        {
            (*this)[0] /= Oth[0];
            (*this)[1] /= Oth[1];
        }
        else if constexpr (Dim == 3)
        {
            (*this)[0] /= Oth[0];
            (*this)[1] /= Oth[1];
            (*this)[2] /= Oth[2];
        }
        else if constexpr (Dim == 4)
        {
            (*this)[0] /= Oth[0];
            (*this)[1] /= Oth[1];
            (*this)[2] /= Oth[2];
            (*this)[3] /= Oth[3];
        }
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator*=(T Scalar) noexcept
    {
        if constexpr (Dim == 2)
        {
            (*this)[0] *= Scalar;
            (*this)[1] *= Scalar;
        }
        else if constexpr (Dim == 3)
        {
            (*this)[0] *= Scalar;
            (*this)[1] *= Scalar;
            (*this)[2] *= Scalar;
        }
        else if constexpr (Dim == 4)
        {
            (*this)[0] *= Scalar;
            (*this)[1] *= Scalar;
            (*this)[2] *= Scalar;
            (*this)[3] *= Scalar;
        }
        return static_cast<FVec&>(*this);
    }
    ROXY_INLINE constexpr FVec& operator/=(T Scalar) noexcept
    {
        const T InvScalar = static_cast<T>(1) / Scalar;
        if constexpr (Dim == 2)
        {
            (*this)[0] *= InvScalar;
            (*this)[1] *= InvScalar;
        }
        else if constexpr (Dim == 3)
        {
            (*this)[0] *= InvScalar;
            (*this)[1] *= InvScalar;
            (*this)[2] *= InvScalar;
        }
        else if constexpr (Dim == 4)
        {
            (*this)[0] *= InvScalar;
            (*this)[1] *= InvScalar;
            (*this)[2] *= InvScalar;
            (*this)[3] *= InvScalar;
        }
        return static_cast<FVec&>(*this);
    }

    ROXY_NODISCARD ROXY_INLINE constexpr FVec Abs() const noexcept
    {
        FVec Temp{};
        if constexpr (Dim == 2)
        {
            Temp[0] = std::abs((*this)[0]);
            Temp[1] = std::abs((*this)[1]);
        }
        else if constexpr (Dim == 3)
        {
            Temp[0] = std::abs((*this)[0]);
            Temp[1] = std::abs((*this)[1]);
            Temp[2] = std::abs((*this)[2]);
        }
        else if constexpr (Dim == 4)
        {
            Temp[0] = std::abs((*this)[0]);
            Temp[1] = std::abs((*this)[1]);
            Temp[2] = std::abs((*this)[2]);
            Temp[3] = std::abs((*this)[3]);
        }
        return Temp;
    }
    ROXY_NODISCARD ROXY_INLINE constexpr T Min() const noexcept
    {
        if constexpr (Dim == 2)
        {
            return std::min((*this)[0], (*this)[1]);
        }
        else if constexpr (Dim == 3)
        {
            return std::min({(*this)[0], (*this)[1], (*this)[2]});
        }
        else if constexpr (Dim == 4)
        {
            return std::min({(*this)[0], (*this)[1], (*this)[2], (*this)[3]});
        }
        ROXY_ASSERT(false && "Unreachable");
    }
    ROXY_NODISCARD ROXY_INLINE constexpr T Max() const noexcept
    {
        if constexpr (Dim == 2)
        {
            return std::max((*this)[0], (*this)[1]);
        }
        else if constexpr (Dim == 3)
        {
            return std::max({(*this)[0], (*this)[1], (*this)[2]});
        }
        else if constexpr (Dim == 4)
        {
            return std::max({(*this)[0], (*this)[1], (*this)[2], (*this)[3]});
        }
        ROXY_ASSERT(false && "Unreachable");
    }
    ROXY_NODISCARD ROXY_INLINE constexpr T Dot(const FVec& Oth) const noexcept
    {
        if constexpr (Dim == 2)
        {
            return (*this)[0] * Oth[0] + (*this)[1] * Oth[1];
        }
        else if constexpr (Dim == 3)
        {
            return (*this)[0] * Oth[0] + (*this)[1] * Oth[1] + (*this)[2] * Oth[2];
        }
        else if constexpr (Dim == 4)
        {
            return (*this)[0] * Oth[0] + (*this)[1] * Oth[1] + (*this)[2] * Oth[2] + (*this)[3] * Oth[3];
        }
        ROXY_ASSERT(false && "Unreachable");
    }
    ROXY_NODISCARD ROXY_INLINE constexpr T SqrLen() const noexcept
    {
        return Dot(static_cast<const FVec&>(*this));
    }
    ROXY_NODISCARD ROXY_INLINE constexpr T Len() const noexcept
    {
        return static_cast<T>(FastSqrt(SqrLen()));
    }
    ROXY_NODISCARD ROXY_INLINE constexpr FVec Clamped(T InMin, T InMax) const noexcept
    {
        FVec Temp;
        if constexpr (Dim == 2)
        {
            Temp[0] = std::clamp((*this)[0], InMin, InMax);
            Temp[1] = std::clamp((*this)[1], InMin, InMax);
        }
        else if constexpr (Dim == 3)
        {
            Temp[0] = std::clamp((*this)[0], InMin, InMax);
            Temp[1] = std::clamp((*this)[1], InMin, InMax);
            Temp[2] = std::clamp((*this)[2], InMin, InMax);
        }
        else if constexpr (Dim == 4)
        {
            Temp[0] = std::clamp((*this)[0], InMin, InMax);
            Temp[1] = std::clamp((*this)[1], InMin, InMax);
            Temp[2] = std::clamp((*this)[2], InMin, InMax);
            Temp[3] = std::clamp((*this)[3], InMin, InMax);
        }
        return Temp;
    }
    ROXY_INLINE constexpr void Clamp(T InMin, T InMax) noexcept
    {
        if constexpr (Dim == 2)
        {
            (*this)[0] = std::clamp((*this)[0], InMin, InMax);
            (*this)[1] = std::clamp((*this)[1], InMin, InMax);
        }
        else if constexpr (Dim == 3)
        {
            (*this)[0] = std::clamp((*this)[0], InMin, InMax);
            (*this)[1] = std::clamp((*this)[1], InMin, InMax);
            (*this)[2] = std::clamp((*this)[2], InMin, InMax);
        }
        else if constexpr (Dim == 4)
        {
            (*this)[0] = std::clamp((*this)[0], InMin, InMax);
            (*this)[1] = std::clamp((*this)[1], InMin, InMax);
            (*this)[2] = std::clamp((*this)[2], InMin, InMax);
            (*this)[3] = std::clamp((*this)[3], InMin, InMax);
        }
    }
    ROXY_NODISCARD ROXY_INLINE FVec Normalized() const noexcept requires std::is_floating_point_v<T>
    {
        if (T InvLen = FastInvSqrt(SqrLen()); std::isfinite(InvLen))
        {
            return static_cast<const FVec&>(*this) * InvLen;
        }
        return Axis(0);
    }
    ROXY_INLINE void Normalize() noexcept requires std::is_floating_point_v<T>
    {
        if (T InvLen = FastInvSqrt(SqrLen()); std::isfinite(InvLen))
        {
            *this *= InvLen;
        }
        else
        {
            *this = Axis(0);
        }
    }
};

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Vec) noexcept
{
    return Vec;
}
template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(const TVec<T, Dim>& Vec) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = -Vec[0];
        Temp[1] = -Vec[1];
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = -Vec[0];
        Temp[1] = -Vec[1];
        Temp[2] = -Vec[2];
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = -Vec[0];
        Temp[1] = -Vec[1];
        Temp[2] = -Vec[2];
        Temp[3] = -Vec[3];
    }
    return Temp;
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = Lhs[0] + Rhs[0];
        Temp[1] = Lhs[1] + Rhs[1];
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = Lhs[0] + Rhs[0];
        Temp[1] = Lhs[1] + Rhs[1];
        Temp[2] = Lhs[2] + Rhs[2];
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = Lhs[0] + Rhs[0];
        Temp[1] = Lhs[1] + Rhs[1];
        Temp[2] = Lhs[2] + Rhs[2];
        Temp[3] = Lhs[3] + Rhs[3];
    }
    return Temp;
}
template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = Lhs[0] - Rhs[0];
        Temp[1] = Lhs[1] - Rhs[1];
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = Lhs[0] - Rhs[0];
        Temp[1] = Lhs[1] - Rhs[1];
        Temp[2] = Lhs[2] - Rhs[2];
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = Lhs[0] - Rhs[0];
        Temp[1] = Lhs[1] - Rhs[1];
        Temp[2] = Lhs[2] - Rhs[2];
        Temp[3] = Lhs[3] - Rhs[3];
    }
    return Temp;
}
template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = Lhs[0] * Rhs[0];
        Temp[1] = Lhs[1] * Rhs[1];
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = Lhs[0] * Rhs[0];
        Temp[1] = Lhs[1] * Rhs[1];
        Temp[2] = Lhs[2] * Rhs[2];
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = Lhs[0] * Rhs[0];
        Temp[1] = Lhs[1] * Rhs[1];
        Temp[2] = Lhs[2] * Rhs[2];
        Temp[3] = Lhs[3] * Rhs[3];
    }
    return Temp;
}
template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = Lhs[0] / Rhs[0];
        Temp[1] = Lhs[1] / Rhs[1];
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = Lhs[0] / Rhs[0];
        Temp[1] = Lhs[1] / Rhs[1];
        Temp[2] = Lhs[2] / Rhs[2];
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = Lhs[0] / Rhs[0];
        Temp[1] = Lhs[1] / Rhs[1];
        Temp[2] = Lhs[2] / Rhs[2];
        Temp[3] = Lhs[3] / Rhs[3];
    }
    return Temp;
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Vec, T scalar) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = Vec[0] + scalar;
        Temp[1] = Vec[1] + scalar;
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = Vec[0] + scalar;
        Temp[1] = Vec[1] + scalar;
        Temp[2] = Vec[2] + scalar;
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = Vec[0] + scalar;
        Temp[1] = Vec[1] + scalar;
        Temp[2] = Vec[2] + scalar;
        Temp[3] = Vec[3] + scalar;
    }
    return Temp;
}
template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(const TVec<T, Dim>& Vec, T scalar) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = Vec[0] - scalar;
        Temp[1] = Vec[1] - scalar;
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = Vec[0] - scalar;
        Temp[1] = Vec[1] - scalar;
        Temp[2] = Vec[2] - scalar;
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = Vec[0] - scalar;
        Temp[1] = Vec[1] - scalar;
        Temp[2] = Vec[2] - scalar;
        Temp[3] = Vec[3] - scalar;
    }
    return Temp;
}
template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(const TVec<T, Dim>& Vec, T scalar) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = Vec[0] * scalar;
        Temp[1] = Vec[1] * scalar;
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = Vec[0] * scalar;
        Temp[1] = Vec[1] * scalar;
        Temp[2] = Vec[2] * scalar;
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = Vec[0] * scalar;
        Temp[1] = Vec[1] * scalar;
        Temp[2] = Vec[2] * scalar;
        Temp[3] = Vec[3] * scalar;
    }
    return Temp;
}
template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(const TVec<T, Dim>& Vec, T scalar) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = Vec[0] / scalar;
        Temp[1] = Vec[1] / scalar;
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = Vec[0] / scalar;
        Temp[1] = Vec[1] / scalar;
        Temp[2] = Vec[2] / scalar;
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = Vec[0] / scalar;
        Temp[1] = Vec[1] / scalar;
        Temp[2] = Vec[2] / scalar;
        Temp[3] = Vec[3] / scalar;
    }
    return Temp;
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(T scalar, const TVec<T, Dim>& Vec) noexcept
{
    return Vec + scalar;
}
template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(T scalar, const TVec<T, Dim>& Vec) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = scalar - Vec[0];
        Temp[1] = scalar - Vec[1];
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = scalar - Vec[0];
        Temp[1] = scalar - Vec[1];
        Temp[2] = scalar - Vec[2];
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = scalar - Vec[0];
        Temp[1] = scalar - Vec[1];
        Temp[2] = scalar - Vec[2];
        Temp[3] = scalar - Vec[3];
    }
    return Temp;
}
template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(T scalar, const TVec<T, Dim>& Vec) noexcept
{
    return Vec * scalar;
}
template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(T scalar, const TVec<T, Dim>& Vec) noexcept
{
    TVec<T, Dim> Temp;
    if constexpr (Dim == 2)
    {
        Temp[0] = scalar / Vec[0];
        Temp[1] = scalar / Vec[1];
    }
    else if constexpr (Dim == 3)
    {
        Temp[0] = scalar / Vec[0];
        Temp[1] = scalar / Vec[1];
        Temp[2] = scalar / Vec[2];
    }
    else if constexpr (Dim == 4)
    {
        Temp[0] = scalar / Vec[0];
        Temp[1] = scalar / Vec[1];
        Temp[2] = scalar / Vec[2];
        Temp[3] = scalar / Vec[3];
    }
    return Temp;
}

template <typename T> requires std::is_arithmetic_v<T>
class TVec<T, 2> : public TVecBase<TVec<T, 2>, T, 2>
{
    friend class TVecBase<TVec, T, 2>;

public:
    static constexpr auto AxisX = TVecBase<TVec, T, 2>::Axis(0);
    static constexpr auto AxisY = TVecBase<TVec, T, 2>::Axis(1);

    ROXY_NODISCARD ROXY_INLINE T& X() noexcept { return Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE const T& X() const noexcept { return Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE T& Y() noexcept { return Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE const T& Y() const noexcept { return Payload[1]; }

private:
    alignas(16) T Payload[2] {};
};

template <typename T> requires std::is_arithmetic_v<T>
class TVec<T, 3> : public TVecBase<TVec<T, 3>, T, 3>
{
    friend class TVecBase<TVec, T, 3>;

public:
    static constexpr auto AxisX = TVecBase<TVec, T, 3>::Axis(0);
    static constexpr auto AxisY = TVecBase<TVec, T, 3>::Axis(1);
    static constexpr auto AxisZ = TVecBase<TVec, T, 3>::Axis(2);

    ROXY_NODISCARD ROXY_INLINE T& X() noexcept { return Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE const T& X() const noexcept { return Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE T& Y() noexcept { return Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE const T& Y() const noexcept { return Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE T& Z() noexcept { return Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE const T& Z() const noexcept { return Payload[2]; }

    ROXY_NODISCARD ROXY_INLINE constexpr TVec Cross(const TVec& Oth) const noexcept
    {
        TVec Temp;
        Temp.X() = Y() * Oth.Z() - Z() * Oth.Y();
        Temp.Y() = Z() * Oth.X() - X() * Oth.Z();
        Temp.Z() = X() * Oth.Y() - Y() * Oth.X();
        return Temp;
    }

private:
    alignas(16) T Payload[4] {};
};

template <typename T> requires std::is_arithmetic_v<T>
class TVec<T, 4> : public TVecBase<TVec<T, 4>, T, 4>
{
    friend class TVecBase<TVec, T, 4>;

public:
    static constexpr auto AxisX = TVecBase<TVec, T, 4>::Axis(0);
    static constexpr auto AxisY = TVecBase<TVec, T, 4>::Axis(1);
    static constexpr auto AxisZ = TVecBase<TVec, T, 4>::Axis(2);
    static constexpr auto AxisW = TVecBase<TVec, T, 4>::Axis(3);

    ROXY_NODISCARD ROXY_INLINE T& X() noexcept { return Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE const T& X() const noexcept { return Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE T& Y() noexcept { return Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE const T& Y() const noexcept { return Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE T& Z() noexcept { return Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE const T& Z() const noexcept { return Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE T& W() noexcept { return Payload[3]; }
    ROXY_NODISCARD ROXY_INLINE const T& W() const noexcept { return Payload[3]; }

private:
    alignas(16) T Payload[4] {};
};

}
