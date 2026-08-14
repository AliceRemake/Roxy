#pragma once

#include <RoxyMath/RoxyMathCommon.h>

namespace Roxy::Math
{
template <typename T, FIndex Dim> requires std::is_arithmetic_v<T> && (2 <= Dim && Dim <= 4) class TVec;

template <typename T, FIndex Dim> requires std::is_arithmetic_v<T> && (2 <= Dim && Dim <= 4) class TMatBase;
template <typename T, FIndex Dim> requires std::is_arithmetic_v<T> && (2 <= Dim && Dim <= 4) class TMat;

template <typename T, FIndex Dim> requires std::is_arithmetic_v<T> && (2 <= Dim && Dim <= 4)
class TVecBase
{
protected:
    using FVec = TVec<T, Dim>;
    using FMat = TMat<T, Dim>;
    alignas(16) T Payload[(Dim == 3) ? 4 : Dim] {};

public:
    ROXY_NODISCARD ROXY_INLINE constexpr TVecBase() noexcept = default;

    ROXY_NODISCARD ROXY_INLINE constexpr explicit TVecBase(T Scalar) noexcept
    {
        if constexpr (Dim >= 2)
        {
            Payload[0] = T(Scalar);
            Payload[1] = T(Scalar);
        }
        if constexpr (Dim >= 3)
        {
            Payload[2] = T(Scalar);
        }
        if constexpr (Dim >= 4)
        {
            Payload[3] = T(Scalar);
        }
    }

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

    ROXY_NODISCARD ROXY_INLINE constexpr T& operator[](FIndex Idx) noexcept
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
        Temp.Payload[Idx] = static_cast<T>(1);
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
            return std::min({ Payload[0], Payload[1], Payload[2] });
        }
        else
        {
            static_assert(Dim == 4 && "Vec Dim Out Of Bound");
            return std::min({ Payload[0], Payload[1], Payload[2], Payload[3] });
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
            return std::max({ Payload[0], Payload[1], Payload[2] });
        }
        else
        {
            static_assert(Dim == 4 && "Vec Dim Out Of Bound");
            return std::max({ Payload[0], Payload[1], Payload[2], Payload[3] });
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T SqrLen() const noexcept
    {
        return Dot(static_cast<const FVec&>(*this), static_cast<const FVec&>(*this));
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T Len() const noexcept requires std::is_floating_point_v<T>
    {
        return static_cast<T>(Sqrt(SqrLen()));
    }
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
class TVec<T, 2> : public TVecBase<T, 2>
{
public:
    friend class TVecBase<T, 2>;
    friend class TMatBase<T, 2>;
    using TVecBase<T, 2>::TVecBase;

    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisX() noexcept { return TVecBase<T, 2>::Axis(0); }
    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisY() noexcept { return TVecBase<T, 2>::Axis(1); }

    ROXY_NODISCARD ROXY_INLINE constexpr T& X() noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& X() const noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& Y() noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& Y() const noexcept { return this->Payload[1]; }
};

template <typename T> requires std::is_arithmetic_v<T>
class TVec<T, 3> : public TVecBase<T, 3>
{
public:
    friend class TVecBase<T, 3>;
    friend class TMatBase<T, 3>;
    using TVecBase<T, 3>::TVecBase;

    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisX() noexcept { return TVecBase<T, 3>::Axis(0); }
    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisY() noexcept { return TVecBase<T, 3>::Axis(1); }
    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisZ() noexcept { return TVecBase<T, 3>::Axis(2); }

    ROXY_NODISCARD ROXY_INLINE constexpr T& X() noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& X() const noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& Y() noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& Y() const noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& Z() noexcept { return this->Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& Z() const noexcept { return this->Payload[2]; }
};

template <typename T> requires std::is_arithmetic_v<T>
class TVec<T, 4> : public TVecBase<T, 4>
{
public:
    friend class TVecBase<T, 4>;
    friend class TMatBase<T, 4>;
    using TVecBase<T, 4>::TVecBase;

    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisX() noexcept { return TVecBase<T, 4>::Axis(0); }
    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisY() noexcept { return TVecBase<T, 4>::Axis(1); }
    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisZ() noexcept { return TVecBase<T, 4>::Axis(2); }
    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisW() noexcept { return TVecBase<T, 4>::Axis(3); }

    ROXY_NODISCARD ROXY_INLINE constexpr T& X() noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& X() const noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& Y() noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& Y() const noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& Z() noexcept { return this->Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& Z() const noexcept { return this->Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& W() noexcept { return this->Payload[3]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& W() const noexcept { return this->Payload[3]; }
};

}
