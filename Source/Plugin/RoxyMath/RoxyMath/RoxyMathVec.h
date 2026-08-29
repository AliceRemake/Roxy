#pragma once

#include <RoxyMath/RoxyMathCommon.h>

namespace Roxy::Math
{
template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4) class TVecBase;
template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4) class TVec;
template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4) class TMatBase;
template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4) class TMat;
template <CFloatingPoint T> class TQuat;

template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4)
class TVecBase
{
protected:
    using FVec = TVec<T, Dim>;
    using FMat = TMat<T, Dim>;
    alignas(16) T Payload[Dim == 3 ? 4 : Dim];

public:
    #pragma region Construct
    ROXY_NODISCARD ROXY_INLINE constexpr TVecBase() noexcept = default;

    ROXY_NODISCARD ROXY_INLINE constexpr TVecBase(TInitList<T> InitList) noexcept
    {
        auto It = InitList.begin();
        const auto Num = InitList.size();
        if constexpr (Dim >= 2)
        {
            Payload[0] = (Num > 0) ? *It++ : T{0};
            Payload[1] = (Num > 1) ? *It++ : T{0};
        }
        if constexpr (Dim >= 3)
        {
            Payload[2] = (Num > 2) ? *It++ : T{0};
        }
        if constexpr (Dim >= 4)
        {
            Payload[3] = (Num > 3) ? *It++ : T{0};
        }
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FVec Zero() noexcept
    {
        return FVec();
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FVec One() noexcept
    {
        if constexpr (Dim == 2)
        {
            return FVec{T{1}, T{1}};
        }
        else if constexpr (Dim == 3)
        {
            return FVec{T{1}, T{1}, T{1}};
        }
        else
        {
            static_assert(Dim == 4);
            return FVec{T{1}, T{1}, T{1}, T{1}};
        }
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FVec Axis(FIndex Idx) noexcept
    {
        ROXY_ASSERT_MSG(0 <= Idx && Idx < Dim, "TVec: Index Out Of Bound");
        FVec Temp{};
        Temp.Payload[Idx] = T{1};
        return Temp;
    }
    #pragma endregion

    #pragma region Accessor
    ROXY_NODISCARD ROXY_INLINE constexpr T& operator[](FIndex Idx) noexcept
    {
        ROXY_ASSERT_MSG(0 <= Idx && Idx < Dim, "TVec: Index Out Of Bound");
        return Payload[Idx];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T operator[](FIndex Idx) const noexcept
    {
        ROXY_ASSERT_MSG(0 <= Idx && Idx < Dim, "TVec: Index Out Of Bound");
        return Payload[Idx];
    }
    #pragma endregion

    #pragma region Operators
    ROXY_INLINE constexpr FVec& operator+=(T Scalar) noexcept
    {
        if constexpr (Dim >= 1) {Payload[0] += Scalar;}
        if constexpr (Dim >= 2) {Payload[1] += Scalar;}
        if constexpr (Dim >= 3) {Payload[2] += Scalar;}
        if constexpr (Dim >= 4) {Payload[3] += Scalar;}
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator-=(T Scalar) noexcept
    {
        if constexpr (Dim >= 1) {Payload[0] -= Scalar;}
        if constexpr (Dim >= 2) {Payload[1] -= Scalar;}
        if constexpr (Dim >= 3) {Payload[2] -= Scalar;}
        if constexpr (Dim >= 4) {Payload[3] -= Scalar;}
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator*=(T Scalar) noexcept
    {
        if constexpr (Dim >= 1) {Payload[0] *= Scalar;}
        if constexpr (Dim >= 2) {Payload[1] *= Scalar;}
        if constexpr (Dim >= 3) {Payload[2] *= Scalar;}
        if constexpr (Dim >= 4) {Payload[3] *= Scalar;}
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator/=(T Scalar) noexcept
    {
        return *this *= T{1} / Scalar;
    }

    ROXY_INLINE constexpr FVec& operator+=(const FVec& Oth) noexcept
    {
        if constexpr (Dim >= 1) {Payload[0] += Oth[0];}
        if constexpr (Dim >= 2) {Payload[1] += Oth[1];}
        if constexpr (Dim >= 3) {Payload[2] += Oth[2];}
        if constexpr (Dim >= 4) {Payload[3] += Oth[3];}
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator-=(const FVec& Oth) noexcept
    {
        if constexpr (Dim >= 1) {Payload[0] -= Oth[0];}
        if constexpr (Dim >= 2) {Payload[1] -= Oth[1];}
        if constexpr (Dim >= 3) {Payload[2] -= Oth[2];}
        if constexpr (Dim >= 4) {Payload[3] -= Oth[3];}
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator*=(const FVec& Oth) noexcept
    {
        if constexpr (Dim >= 1) {Payload[0] *= Oth[0];}
        if constexpr (Dim >= 2) {Payload[1] *= Oth[1];}
        if constexpr (Dim >= 3) {Payload[2] *= Oth[2];}
        if constexpr (Dim >= 4) {Payload[3] *= Oth[3];}
        return static_cast<FVec&>(*this);
    }

    ROXY_INLINE constexpr FVec& operator/=(const FVec& Oth) noexcept
    {
        if constexpr (Dim >= 1) {Payload[0] /= Oth[0];}
        if constexpr (Dim >= 2) {Payload[1] /= Oth[1];}
        if constexpr (Dim >= 3) {Payload[2] /= Oth[2];}
        if constexpr (Dim >= 4) {Payload[3] /= Oth[3];}
        return static_cast<FVec&>(*this);
    }
    #pragma endregion

    template <CFloatingPoint U> requires std::is_convertible_v<T, U>
    ROXY_NODISCARD ROXY_INLINE constexpr TVec<U, Dim> As() const noexcept
    {
        if constexpr (Dim == 2)
        {
            return TVec<U, Dim>{static_cast<U>(Payload[0]), static_cast<U>(Payload[1])};
        }
        else if constexpr (Dim == 3)
        {
            return TVec<U, Dim>{static_cast<U>(Payload[0]), static_cast<U>(Payload[1]), static_cast<U>(Payload[2])};
        }
        else
        {
            static_assert(Dim == 4);
            return TVec<U, Dim>{static_cast<U>(Payload[0]), static_cast<U>(Payload[1]), static_cast<U>(Payload[2]), static_cast<U>(Payload[3])};
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T Min() const noexcept
    {
        if constexpr (Dim == 2)
        {
            return std::min(Payload[0], Payload[1]);
        }
        else if constexpr (Dim == 3)
        {
            return std::min({Payload[0], Payload[1], Payload[2]});
        }
        else
        {
            static_assert(Dim == 4);
            return std::min({Payload[0], Payload[1], Payload[2], Payload[3]});
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
            return std::max({Payload[0], Payload[1], Payload[2]});
        }
        else
        {
            static_assert(Dim == 4);
            return std::max({Payload[0], Payload[1], Payload[2], Payload[3]});
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T Dot(const TVecBase& Oth) const noexcept
    {
        if constexpr (Dim == 2)
        {
            return Payload[0] * Oth[0] + Payload[1] * Oth[1];
        }
        else if constexpr (Dim == 3)
        {
            return Payload[0] * Oth[0] + Payload[1] * Oth[1] + Payload[2] * Oth[2];
        }
        else
        {
            static_assert(Dim == 4);
            return Payload[0] * Oth[0] + Payload[1] * Oth[1] + Payload[2] * Oth[2] + Payload[3] * Oth[3];
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T SqrLength() const noexcept
    {
        return this->Dot(*this);
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T Length() const noexcept
    {
        return static_cast<T>(Sqrt(SqrLength()));
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T InvSqrLength() const noexcept
    {
        ROXY_ASSERT_MSG(SqrLength() > Eps<T>, "TVec: 0 Vec");
        return static_cast<T>(T{1} / SqrLength());
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T InvLength() const noexcept
    {
        return static_cast<T>(InvSqrt(SqrLength()));
    }

    ROXY_INLINE constexpr FVec& Normalize() noexcept
    {
        const auto InvLen = InvLength();
        if constexpr (Dim >= 1) {Payload[0] *= InvLen;}
        if constexpr (Dim >= 2) {Payload[1] *= InvLen;}
        if constexpr (Dim >= 3) {Payload[2] *= InvLen;}
        if constexpr (Dim >= 4) {Payload[3] *= InvLen;}
        return static_cast<FVec>(*this);
    }

    ROXY_NODISCARD ROXY_INLINE constexpr FVec Normalized() const noexcept
    {
        const auto InvLen = InvLength();
        if constexpr (Dim == 2)
        {
            return FVec{Payload[0] * InvLen, Payload[1] * InvLen};
        }
        else if constexpr (Dim == 3)
        {
            return FVec{Payload[0] * InvLen, Payload[1] * InvLen, Payload[2] * InvLen};
        }
        else
        {
            static_assert(Dim == 4);
            return FVec{Payload[0] * InvLen, Payload[1] * InvLen, Payload[2] * InvLen, Payload[3] * InvLen};
        }
    }
};

template <CFloatingPoint T>
class TVec<T, 2> : public TVecBase<T, 2>
{
public:
    friend class TVecBase<T, 2>;
    friend class TMatBase<T, 2>;
    using TVecBase<T, 2>::TVecBase;

    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisX() noexcept { return TVecBase<T, 2>::Axis(0); }
    ROXY_NODISCARD ROXY_INLINE static constexpr TVec AxisY() noexcept { return TVecBase<T, 2>::Axis(1); }
    ROXY_NODISCARD ROXY_INLINE constexpr T& X() noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& Y() noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T X() const noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T Y() const noexcept { return this->Payload[1]; }
};

template <CFloatingPoint T>
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
    ROXY_NODISCARD ROXY_INLINE constexpr T& Y() noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& Z() noexcept { return this->Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T X() const noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T Y() const noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T Z() const noexcept { return this->Payload[2]; }

    ROXY_NODISCARD ROXY_INLINE constexpr TVec Cross(const TVec& Oth) const noexcept
    {
        return TVec
        {
            this->Payload[1] * Oth[2] - this->Payload[2] * Oth[1],
            this->Payload[2] * Oth[0] - this->Payload[0] * Oth[2],
            this->Payload[0] * Oth[1] - this->Payload[1] * Oth[0]
        };
    }
};

template <CFloatingPoint T>
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
    ROXY_NODISCARD ROXY_INLINE constexpr T& Y() noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& Z() noexcept { return this->Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& W() noexcept { return this->Payload[3]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T X() const noexcept { return this->Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T Y() const noexcept { return this->Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T Z() const noexcept { return this->Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T W() const noexcept { return this->Payload[3]; }
};

#pragma region Operator
template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Vec) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Vec[0], Vec[1]};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Vec[0], Vec[1], Vec[2]};
    }
    else
    {
        static_assert(Dim == 4);
        return TVec<T, Dim>{Vec[0], Vec[1], Vec[2], Vec[3]};
    }
}

template <CFloatingPoint T, FIndex Dim>
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
        static_assert(Dim == 4);
        return TVec<T, Dim>{-Vec[0], -Vec[1], -Vec[2], -Vec[3]};
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr bool operator==(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    if constexpr (Dim == 2)
    {
        return (Lhs[0] == Rhs[0]) && (Lhs[1] == Rhs[1]);
    }
    else if constexpr (Dim == 3)
    {
        return (Lhs[0] == Rhs[0]) && (Lhs[1] == Rhs[1]) && (Lhs[2] == Rhs[2]);
    }
    else
    {
        static_assert(Dim == 4);
        return (Lhs[0] == Rhs[0]) && (Lhs[1] == Rhs[1]) && (Lhs[2] == Rhs[2]) && (Lhs[3] == Rhs[3]);
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr bool operator!=(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
{
    if constexpr (Dim == 2)
    {
        return (Lhs[0] != Rhs[0]) || (Lhs[1] != Rhs[1]);
    }
    else if constexpr (Dim == 3)
    {
        return (Lhs[0] != Rhs[0]) || (Lhs[1] != Rhs[1]) || (Lhs[2] != Rhs[2]);
    }
    else
    {
        static_assert(Dim == 4);
        return (Lhs[0] != Rhs[0]) || (Lhs[1] != Rhs[1]) || (Lhs[2] != Rhs[2]) || (Lhs[3] != Rhs[3]);
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Vec, T Scalar) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Vec[0] + Scalar, Vec[1] + Scalar};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Vec[0] + Scalar, Vec[1] + Scalar, Vec[2] + Scalar};
    }
    else
    {
        return TVec<T, Dim>{Vec[0] + Scalar, Vec[1] + Scalar, Vec[2] + Scalar, Vec[3] + Scalar};
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(const TVec<T, Dim>& Vec, T Scalar) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Vec[0] - Scalar, Vec[1] - Scalar};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Vec[0] - Scalar, Vec[1] - Scalar, Vec[2] - Scalar};
    }
    else
    {
        return TVec<T, Dim>{Vec[0] - Scalar, Vec[1] - Scalar, Vec[2] - Scalar, Vec[3] - Scalar};
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(const TVec<T, Dim>& Vec, T Scalar) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Vec[0] * Scalar, Vec[1] * Scalar};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Vec[0] * Scalar, Vec[1] * Scalar, Vec[2] * Scalar};
    }
    else
    {
        return TVec<T, Dim>{Vec[0] * Scalar, Vec[1] * Scalar, Vec[2] * Scalar, Vec[3] * Scalar};
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(const TVec<T, Dim>& Vec, T Scalar) noexcept
{
    return Vec * (T{1} / Scalar);
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(T Scalar, const TVec<T, Dim>& Vec) noexcept
{
    return Vec + Scalar;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(T Scalar, const TVec<T, Dim>& Vec) noexcept
{
    return -Vec + Scalar;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(T Scalar, const TVec<T, Dim>& Vec) noexcept
{
    return Vec * Scalar;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(T Scalar, const TVec<T, Dim>& Vec) noexcept
{
    if constexpr (Dim == 2)
    {
        return TVec<T, Dim>{Scalar / Vec[0], Scalar / Vec[1]};
    }
    else if constexpr (Dim == 3)
    {
        return TVec<T, Dim>{Scalar / Vec[0], Scalar / Vec[1], Scalar / Vec[2]};
    }
    else
    {
        return TVec<T, Dim>{Scalar / Vec[0], Scalar / Vec[1], Scalar / Vec[2], Scalar / Vec[3]};
    }
}

template <CFloatingPoint T, FIndex Dim>
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

template <CFloatingPoint T, FIndex Dim>
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

template <CFloatingPoint T, FIndex Dim>
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

template <CFloatingPoint T, FIndex Dim>
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
#pragma endregion
}

namespace Roxy::Math
{
using FVec2 = TVec<F32, 2>;
using FVec3 = TVec<F32, 3>;
using FVec4 = TVec<F32, 4>;
static_assert(std::is_trivial_v<FVec2>);
static_assert(std::is_trivial_v<FVec3>);
static_assert(std::is_trivial_v<FVec4>);
}
