#pragma once

#include <RoxyMath/RoxyMathCommon.h>

namespace Roxy::Math
{
template <typename T, FIndex Dim> requires std::is_arithmetic_v<T> && (2 <= Dim && Dim <= 4) class TVec;

template <typename FVec, typename T, FIndex Dim> requires std::is_arithmetic_v<T> && (2 <= Dim && Dim <= 4)
class TVecBase
{
public:
    ROXY_NODISCARD ROXY_INLINE constexpr TVecBase() noexcept = default;

    ROXY_NODISCARD ROXY_INLINE constexpr TVecBase(TInitList<T> InitList) noexcept
    {
        auto It = InitList.begin();
        const auto Num = InitList.size();
        if constexpr (Dim >= 2)
        {
            Payload[0] = (Num > 0) ? *It++ : T{};
            Payload[1] = (Num > 1) ? *It++ : T{};
        }
        if constexpr (Dim >= 3)
        {
            Payload[2] = (Num > 2) ? *It++ : T{};
        }
        if constexpr (Dim >= 4)
        {
            Payload[3] = (Num > 3) ? *It++ : T{};
        }
    }

    ROXY_NODISCARD ROXY_INLINE T& operator[](FIndex Idx) noexcept
    {
        ROXY_ASSERT((0 <= Idx && Idx < Dim) && "Vec Index Out Of Bound");
        return Payload[Idx];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr const T& operator[](FIndex Idx) const noexcept
    {
        ROXY_ASSERT((0 <= Idx && Idx < Dim) && "Vec Index Out Of Bound");
        return Payload[Idx];
    }

    template <typename U> requires std::is_convertible_v<T, U>
    ROXY_NODISCARD ROXY_INLINE constexpr TVec<U, Dim> As() const noexcept
    {
        if constexpr (Dim == 2)
        {
            return TVec<U, Dim>{ static_cast<U>(Payload[0]), static_cast<U>(Payload[1]) };
        }
        else if constexpr (Dim == 3)
        {
            return TVec<U, Dim>{ static_cast<U>(Payload[0]), static_cast<U>(Payload[1]), static_cast<U>(Payload[2]) };
        }
        else
        {
            static_assert(Dim == 4 && "Vec Dim Out Of Bound");
            return TVec<U, Dim>{ static_cast<U>(Payload[0]), static_cast<U>(Payload[1]), static_cast<U>(Payload[2]), static_cast<U>(Payload[3]) };
        }
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FVec Zero() noexcept
    {
        return FVec{};
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FVec One() noexcept
    {
        if constexpr (Dim == 2)
        {
            return FVec{static_cast<T>(1), static_cast<T>(1)};
        }
        else if constexpr (Dim == 3)
        {
            return FVec{static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)};
        }
        else
        {
            static_assert(Dim == 4 && "Vec Dim Out Of Bound");
            return FVec{static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)};
        }
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FVec Axis(FIndex Idx) noexcept
    {
        FVec Temp{};
        Temp[Idx] = static_cast<T>(1);
        return Temp;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr bool operator==(const FVec& Oth) const noexcept
    {
        bool Equal{true};
        if constexpr (Dim >= 2)
        {
            Equal = Equal && (Payload[0] == Oth[0]) && (Payload[1] == Oth[1]);
        }
        if constexpr (Dim >= 3)
        {
            Equal = Equal && (Payload[2] == Oth[2]);
        }
        if constexpr (Dim >= 4)
        {
            Equal = Equal && (Payload[3] == Oth[3]);
        }
        return Equal;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr bool operator!=(const FVec& Oth) const noexcept
    {
        return !(*this == Oth);
    }

    ROXY_INLINE constexpr FVec& operator+=(const FVec& Oth) noexcept
    {
        if constexpr (Dim >= 1) { Payload[0] += Oth[0]; }
        if constexpr (Dim >= 2) { Payload[1] += Oth[1]; }
        if constexpr (Dim >= 3) { Payload[2] += Oth[2]; }
        if constexpr (Dim >= 4) { Payload[3] += Oth[3]; }
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator-=(const FVec& Oth) noexcept
    {
        if constexpr (Dim >= 1) { Payload[0] -= Oth[0]; }
        if constexpr (Dim >= 2) { Payload[1] -= Oth[1]; }
        if constexpr (Dim >= 3) { Payload[2] -= Oth[2]; }
        if constexpr (Dim >= 4) { Payload[3] -= Oth[3]; }
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator*=(const FVec& Oth) noexcept
    {
        if constexpr (Dim >= 1) { Payload[0] *= Oth[0]; }
        if constexpr (Dim >= 2) { Payload[1] *= Oth[1]; }
        if constexpr (Dim >= 3) { Payload[2] *= Oth[2]; }
        if constexpr (Dim >= 4) { Payload[3] *= Oth[3]; }
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator/=(const FVec& Oth) noexcept
    {
        if constexpr (Dim >= 1) { Payload[0] /= Oth[0]; }
        if constexpr (Dim >= 2) { Payload[1] /= Oth[1]; }
        if constexpr (Dim >= 3) { Payload[2] /= Oth[2]; }
        if constexpr (Dim >= 4) { Payload[3] /= Oth[3]; }
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator+=(T Scalar) noexcept
    {
        if constexpr (Dim >= 1) { Payload[0] += Scalar; }
        if constexpr (Dim >= 2) { Payload[1] += Scalar; }
        if constexpr (Dim >= 3) { Payload[2] += Scalar; }
        if constexpr (Dim >= 4) { Payload[3] += Scalar; }
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator-=(T Scalar) noexcept
    {
        if constexpr (Dim >= 1) { Payload[0] -= Scalar; }
        if constexpr (Dim >= 2) { Payload[1] -= Scalar; }
        if constexpr (Dim >= 3) { Payload[2] -= Scalar; }
        if constexpr (Dim >= 4) { Payload[3] -= Scalar; }
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator*=(T Scalar) noexcept
    {
        if constexpr (Dim >= 1) { Payload[0] *= Scalar; }
        if constexpr (Dim >= 2) { Payload[1] *= Scalar; }
        if constexpr (Dim >= 3) { Payload[2] *= Scalar; }
        if constexpr (Dim >= 4) { Payload[3] *= Scalar; }
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator/=(T Scalar) noexcept
    {
        const T InvScalar = static_cast<T>(1) / Scalar;
        return *this *= InvScalar;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T Min() const noexcept
    {
        if constexpr (Dim == 2)
        {
            return std::min(Payload[0], Payload[1]);
        }
        else if constexpr (Dim == 3)
        {
            return std::min(Payload[0], Payload[1], Payload[2]);
        }
        else
        {
            static_assert(Dim == 4 && "Vec Dim Out Of Bound");
            return std::min(Payload[0], Payload[1], Payload[2], Payload[3]);
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T Max() const noexcept
    {
        if constexpr (Dim == 2)
        {
            return std::max(Payload[0], Payload[1]);
        }
        else if constexpr (Dim == 3)
        {
            return std::max(Payload[0], Payload[1], Payload[2]);
        }
        else
        {
            static_assert(Dim == 4 && "Vec Dim Out Of Bound");
            return std::max(Payload[0], Payload[1], Payload[2], Payload[3]);
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T SqrLen() const noexcept
    {
        return Dot(static_cast<const FVec&>(*this));
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T Len() const noexcept requires std::is_floating_point_v<T>
    {
        return static_cast<T>(Sqrt(SqrLen()));
    }

protected:
    alignas(16) T Payload[(Dim == 3) ? 4 : Dim] {};
};

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr T Dot(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    T Result = 0;
    if constexpr (Dim >= 2) { Result += Lhs[0] * Rhs[0] + Lhs[1] * Rhs[1]; }
    if constexpr (Dim >= 3) { Result += Lhs[2] * Rhs[2]; }
    if constexpr (Dim >= 4) { Result += Lhs[3] * Rhs[3]; }
    return Result;
}

template <typename T, FIndex Dim> requires (Dim == 3)
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> Cross(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    return TVec<T, Dim>
    {
        Lhs[1] * Rhs[2] - Lhs[2] * Rhs[1],
        Lhs[2] * Rhs[0] - Lhs[0] * Rhs[2],
        Lhs[0] * Rhs[1] - Lhs[1] * Rhs[0]
    };
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Vec) noexcept
{
    return Vec;
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(const TVec<T, Dim>& Vec) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{-Vec[0], -Vec[1]};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{-Vec[0], -Vec[1], -Vec[2]};
    }
    else
    {
        return TVec<T, Dim>{-Vec[0], -Vec[1], -Vec[2], -Vec[3]};
    }
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Lhs[0] + Rhs[0], Lhs[1] + Rhs[1]};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Lhs[0] + Rhs[0], Lhs[1] + Rhs[1], Lhs[2] + Rhs[2]};
    }
    else
    {
        return TVec<T, Dim>{Lhs[0] + Rhs[0], Lhs[1] + Rhs[1], Lhs[2] + Rhs[2], Lhs[3] + Rhs[3]};
    }
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Lhs[0] - Rhs[0], Lhs[1] - Rhs[1]};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Lhs[0] - Rhs[0], Lhs[1] - Rhs[1], Lhs[2] - Rhs[2]};
    }
    else
    {
        return TVec<T, Dim>{Lhs[0] - Rhs[0], Lhs[1] - Rhs[1], Lhs[2] - Rhs[2], Lhs[3] - Rhs[3]};
    }
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Lhs[0] * Rhs[0], Lhs[1] * Rhs[1]};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Lhs[0] * Rhs[0], Lhs[1] * Rhs[1], Lhs[2] * Rhs[2]};
    }
    else
    {
        return TVec<T, Dim>{Lhs[0] * Rhs[0], Lhs[1] * Rhs[1], Lhs[2] * Rhs[2], Lhs[3] * Rhs[3]};
    }
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Lhs[0] / Rhs[0], Lhs[1] / Rhs[1]};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Lhs[0] / Rhs[0], Lhs[1] / Rhs[1], Lhs[2] / Rhs[2]};
    }
    else
    {
        return TVec<T, Dim>{Lhs[0] / Rhs[0], Lhs[1] / Rhs[1], Lhs[2] / Rhs[2], Lhs[3] / Rhs[3]};
    }
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Vec, T scalar) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Vec[0] + scalar, Vec[1] + scalar};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Vec[0] + scalar, Vec[1] + scalar, Vec[2] + scalar};
    }
    else
    {
        return TVec<T, Dim>{Vec[0] + scalar, Vec[1] + scalar, Vec[2] + scalar, Vec[3] + scalar};
    }
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(const TVec<T, Dim>& Vec, T scalar) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Vec[0] - scalar, Vec[1] - scalar};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Vec[0] - scalar, Vec[1] - scalar, Vec[2] - scalar};
    }
    else
    {
        return TVec<T, Dim>{Vec[0] - scalar, Vec[1] - scalar, Vec[2] - scalar, Vec[3] - scalar};
    }
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(const TVec<T, Dim>& Vec, T scalar) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Vec[0] * scalar, Vec[1] * scalar};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Vec[0] * scalar, Vec[1] * scalar, Vec[2] * scalar};
    }
    else
    {
        return TVec<T, Dim>{Vec[0] * scalar, Vec[1] * scalar, Vec[2] * scalar, Vec[3] * scalar};
    }
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(const TVec<T, Dim>& Vec, T scalar) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Vec[0] / scalar, Vec[1] / scalar};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Vec[0] / scalar, Vec[1] / scalar, Vec[2] / scalar};
    }
    else
    {
        return TVec<T, Dim>{Vec[0] / scalar, Vec[1] / scalar, Vec[2] / scalar, Vec[3] / scalar};
    }
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(T scalar, const TVec<T, Dim>& Vec) noexcept
{
    return Vec + scalar;
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(T scalar, const TVec<T, Dim>& Vec) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{scalar - Vec[0], scalar - Vec[1]};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{scalar - Vec[0], scalar - Vec[1], scalar - Vec[2]};
    }
    else
    {
        return TVec<T, Dim>{scalar - Vec[0], scalar - Vec[1], scalar - Vec[2], scalar - Vec[3]};
    }
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(T scalar, const TVec<T, Dim>& Vec) noexcept
{
    return Vec * scalar;
}

template <typename T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(T scalar, const TVec<T, Dim>& Vec) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{scalar / Vec[0], scalar / Vec[1]};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{scalar / Vec[0], scalar / Vec[1], scalar / Vec[2]};
    }
    else
    {
        return TVec<T, Dim>{scalar / Vec[0], scalar / Vec[1], scalar / Vec[2], scalar / Vec[3]};
    }
}

template <typename T> requires std::is_arithmetic_v<T>
class TVec<T, 2> : public TVecBase<TVec<T, 2>, T, 2>
{
    friend class TVecBase<TVec, T, 2>;

public:
    using TVecBase<TVec, T, 2>::TVecBase;

    static constexpr TVec AxisX() noexcept { return TVecBase<TVec, T, 2>::Axis(0); }
    static constexpr TVec AxisY() noexcept { return TVecBase<TVec, T, 2>::Axis(1); }

    ROXY_NODISCARD ROXY_INLINE T& X() noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE const T& X() const noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE T& Y() noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE const T& Y() const noexcept { return this->Payload[1]; }
};

template <typename T> requires std::is_arithmetic_v<T>
class TVec<T, 3> : public TVecBase<TVec<T, 3>, T, 3>
{
    friend class TVecBase<TVec, T, 3>;

public:
    using TVecBase<TVec, T, 3>::TVecBase;

    static constexpr TVec AxisX() noexcept { return TVecBase<TVec, T, 3>::Axis(0); }
    static constexpr TVec AxisY() noexcept { return TVecBase<TVec, T, 3>::Axis(1); }
    static constexpr TVec AxisZ() noexcept { return TVecBase<TVec, T, 3>::Axis(2); }

    ROXY_NODISCARD ROXY_INLINE T& X() noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE const T& X() const noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE T& Y() noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE const T& Y() const noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE T& Z() noexcept { return this->Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE const T& Z() const noexcept { return this->Payload[2]; }

    ROXY_NODISCARD ROXY_INLINE constexpr TVec Cross(const TVec& Oth) const noexcept
    {
        return Math::Cross(*this, Oth);
    }
};

template <typename T> requires std::is_arithmetic_v<T>
class TVec<T, 4> : public TVecBase<TVec<T, 4>, T, 4>
{
    friend class TVecBase<TVec, T, 4>;

public:
    using TVecBase<TVec, T, 4>::TVecBase;

    static constexpr TVec AxisX() noexcept { return TVecBase<TVec, T, 4>::Axis(0); }
    static constexpr TVec AxisY() noexcept { return TVecBase<TVec, T, 4>::Axis(1); }
    static constexpr TVec AxisZ() noexcept { return TVecBase<TVec, T, 4>::Axis(2); }
    static constexpr TVec AxisW() noexcept { return TVecBase<TVec, T, 4>::Axis(3); }

    ROXY_NODISCARD ROXY_INLINE T& X() noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE const T& X() const noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE T& Y() noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE const T& Y() const noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE T& Z() noexcept { return this->Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE const T& Z() const noexcept { return this->Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE T& W() noexcept { return this->Payload[3]; }
    ROXY_NODISCARD ROXY_INLINE const T& W() const noexcept { return this->Payload[3]; }
};

}


// ROXY_NODISCARD ROXY_INLINE constexpr T Dot(const FVec& Oth) const noexcept
// {
//     return Math::Dot(static_cast<const FVec&>(*this), Oth);
// }
// ROXY_NODISCARD ROXY_INLINE constexpr FVec Abs() const noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return FVec{ std::abs(Payload[0]), std::abs(Payload[1]) };
//     }
//     else if constexpr (Dim == 3)
//     {
//         return FVec{ std::abs(Payload[0]), std::abs(Payload[1]), std::abs(Payload[2]) };
//     }
//     else
//     {
//         static_assert(Dim == 4 && "Vec Dim Out Of Bound");
//         return FVec{ std::abs(Payload[0]), std::abs(Payload[1]), std::abs(Payload[2]), std::abs(Payload[3]) };
//     }
// }
// ROXY_NODISCARD ROXY_INLINE constexpr FVec Clamped(T InMin, T InMax) const noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return FVec{ std::clamp(Payload[0], InMin, InMax), std::clamp(Payload[1], InMin, InMax) };
//     }
//     else if constexpr (Dim == 3)
//     {
//         return FVec{ std::clamp(Payload[0], InMin, InMax), std::clamp(Payload[1], InMin, InMax), std::clamp(Payload[2], InMin, InMax) };
//     }
//     else
//     {
//         static_assert(Dim == 4);
//         return FVec{ std::clamp(Payload[0], InMin, InMax), std::clamp(Payload[1], InMin, InMax), std::clamp(Payload[2], InMin, InMax), std::clamp(Payload[3], InMin, InMax) };
//     }
// }
// ROXY_INLINE constexpr void Clamp(T InMin, T InMax) noexcept
// {
//     if constexpr (Dim >= 1) { Payload[0] = std::clamp(Payload[0], InMin, InMax); }
//     if constexpr (Dim >= 2) { Payload[1] = std::clamp(Payload[1], InMin, InMax); }
//     if constexpr (Dim >= 3) { Payload[2] = std::clamp(Payload[2], InMin, InMax); }
//     if constexpr (Dim >= 4) { Payload[3] = std::clamp(Payload[3], InMin, InMax); }
// }
// ROXY_NODISCARD ROXY_INLINE FVec Normalized() const noexcept requires std::is_floating_point_v<T>
// {
//     const auto InvLen = InvSqrt(SqrLen());
//     return static_cast<const FVec&>(*this) * InvLen;
// }
//
// ROXY_INLINE void Normalize() noexcept requires std::is_floating_point_v<T>
// {
//     const auto InvLen = InvSqrt(SqrLen());
//     *this *= InvLen;
// }
