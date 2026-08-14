#pragma once

#include <RoxyMath/RoxyMathMat.h>

namespace Roxy::Math
{

template<CFloatingPoint T>
class TQuat
{
protected:
    TVec<T, 4> Payload{};

public:
    ROXY_NODISCARD ROXY_INLINE constexpr explicit TQuat() : Payload({T{0}, T{0}, T{0}, T{1}}) {}

    ROXY_NODISCARD ROXY_INLINE constexpr explicit TQuat(T X, T Y, T Z, T W) : Payload({X, Y, Z, W}) {}

    ROXY_NODISCARD ROXY_INLINE constexpr explicit TQuat(const TVec<T, 4>& V) : Payload(V) {}

    ROXY_NODISCARD ROXY_INLINE constexpr explicit TQuat(const TVec<T, 3>& V, T W) : Payload({V.X(), V.Y(), V.Z(), W}) {}

    ROXY_NODISCARD ROXY_INLINE static constexpr TQuat Identity() noexcept
    {
        return TQuat(T{0}, T{0}, T{0}, T{1});
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr TQuat Zero() noexcept
    {
        return TQuat(T{0}, T{0}, T{0}, T{0});
    }

    ROXY_NODISCARD ROXY_INLINE constexpr const T& X() const noexcept { return Payload[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& Y() const noexcept { return Payload[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& Z() const noexcept { return Payload[2]; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T& W() const noexcept { return Payload[3]; }

    template <CFloatingPoint U> requires std::is_convertible_v<T, U>
    ROXY_NODISCARD ROXY_INLINE constexpr TQuat<U> As() const noexcept
    {
        return TQuat<U>(Payload.template As<U>());
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T SqrLength() const noexcept
    {
        return Payload.SqrLength();
    }

    ROXY_NODISCARD ROXY_INLINE T constexpr Length() const noexcept
    {
        return Payload.Length();
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TQuat Conjugate() const noexcept
    {
        return TQuat(TVec<T,4>{-Payload[0], -Payload[1], -Payload[2], Payload[3]});
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TQuat Inverse() const noexcept
    {
        const T _SqrLength = SqrLength();
        ROXY_ASSERT_MSG(_SqrLength > Eps<T>, "Quaternion Inverse: zero quaternion");

        const T InvSqrLen = T{1} / _SqrLength;
        return TQuat(TVec<T,4>{-Payload[0], -Payload[1], -Payload[2], Payload[3]} * InvSqrLen);
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TQuat Normalize() const noexcept
    {
        const T _Length = Length();
        ROXY_ASSERT_MSG(_Length > Eps<T>, "Quaternion Normalize: zero quaternion");

        const T InvLength = T{1} / _Length;
        return TQuat(Payload * InvLength);
    }

    template<FIndex Dim> requires (Dim == 3 || Dim == 4)
    ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> ToMat() const noexcept
    {
        const T _X = X();
        const T _Y = Y();
        const T _Z = Z();
        const T _W = W();

        const T XX = _X * _X;
        const T YY = _Y * _Y;
        const T ZZ = _Z * _Z;
        const T XY = _X * _Y;
        const T XZ = _X * _Z;
        const T YZ = _Y * _Z;
        const T WX = _W * _X;
        const T WY = _W * _Y;
        const T WZ = _W * _Z;

        if constexpr (Dim == 3)
        {
            return TMat<T, Dim>(
            {
                T{1} - T{2} * (YY + ZZ), T{2} * (XY - WZ),        T{2} * (XZ + WY),
                T{2} * (XY + WZ),        T{1} - T{2} * (XX + ZZ), T{2} * (YZ - WX),
                T{2} * (XZ - WY),        T{2} * (YZ + WX),        T{1} - T{2} * (XX + YY)
            });
        }
        else
        {
            static_assert(Dim == 4);
            return TMat<T, Dim>(
            {
                T{1} - T{2} * (YY + ZZ), T{2} * (XY - WZ),        T{2} * (XZ + WY),        T{0},
                T{2} * (XY + WZ),        T{1} - T{2} * (XX + ZZ), T{2} * (YZ - WX),        T{0},
                T{2} * (XZ - WY),        T{2} * (YZ + WX),        T{1} - T{2} * (XX + YY), T{0},
                T{0},                    T{0},                    T{0},                    T{1}
            });
        }
    }

    template<FIndex Dim> requires (Dim == 3 || Dim == 4)
    ROXY_NODISCARD ROXY_INLINE explicit constexpr operator TMat<T, Dim>() const noexcept
    {
        return ToMat<T, Dim>();
    }

    ROXY_NODISCARD ROXY_INLINE constexpr bool operator==(const TQuat& Rhs) const noexcept
    {
        return Payload == Rhs.Payload;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr bool operator!=(const TQuat& Rhs) const noexcept
    {
        return !(*this == Rhs);
    }

    ROXY_INLINE constexpr TQuat& operator+=(const TQuat& Rhs) noexcept
    {
        Payload += Rhs.Payload;
        return *this;
    }

    ROXY_INLINE constexpr TQuat& operator-=(const TQuat& Rhs) noexcept
    {
        Payload -= Rhs.Payload;
        return *this;
    }

    ROXY_INLINE constexpr TQuat& operator*=(const TQuat& Rhs) noexcept
    {
        const auto& LP = Payload;
        const auto& RP = Rhs.Payload;

        const auto LW = LP[3], RW = RP[3];
        const TVec<T, 3> LV{LP[0], LP[1], LP[2]};
        const TVec<T, 3> RV{RP[0], RP[1], RP[2]};

        const auto W = LW * RW - Dot(LV, RV);
        const auto V = LW * RV + RW * LV + Cross(LV, RV);

        Payload = TVec<T, 4>{ V[0], V[1], V[2], W};
        return *this;
    }

    ROXY_INLINE constexpr TQuat& operator/=(const TQuat& Rhs) noexcept
    {
        *this = *this * Rhs.Inverse();
        return *this;
    }

    ROXY_INLINE constexpr TQuat& operator*=(T Scalar) noexcept
    {
        Payload *= Scalar;
        return *this;
    }

    ROXY_INLINE constexpr TQuat& operator/=(T Scalar) noexcept
    {
        Payload /= Scalar;
        return *this;
    }

    template<CFloatingPoint U> ROXY_INLINE friend constexpr TQuat<U> operator+(const TQuat<U>& Quat) noexcept;
    template<CFloatingPoint U> ROXY_INLINE friend constexpr TQuat<U> operator-(const TQuat<U>& Quat) noexcept;
    template<CFloatingPoint U> ROXY_INLINE friend constexpr TQuat<U> operator+(const TQuat<U>& Lhs, const TQuat<U>& Rhs) noexcept;
    template<CFloatingPoint U> ROXY_INLINE friend constexpr TQuat<U> operator-(const TQuat<U>& Lhs, const TQuat<U>& Rhs) noexcept;
    template<CFloatingPoint U> ROXY_INLINE friend constexpr TQuat<U> operator*(const TQuat<U>& Lhs, const TQuat<U>& Rhs) noexcept;
    template<CFloatingPoint U> ROXY_INLINE friend constexpr TQuat<U> operator/(const TQuat<U>& Lhs, const TQuat<U>& Rhs) noexcept;
    template<CFloatingPoint U> ROXY_INLINE friend constexpr TQuat<U> operator*(const TQuat<U>& Quat, U Scalar) noexcept;
    template<CFloatingPoint U> ROXY_INLINE friend constexpr TQuat<U> operator*(U Scalar, const TQuat<U>& Quat) noexcept;
    template<CFloatingPoint U> ROXY_INLINE friend constexpr TQuat<U> operator/(const TQuat<U>& Quat, U Scalar) noexcept;

    ROXY_NODISCARD ROXY_INLINE static constexpr TQuat Lerp(const TQuat& A, const TQuat& B, T Alpha) noexcept
    {
        return (T{1} - Alpha) * A + Alpha * B;
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr TQuat NLerp(const TQuat& A, const TQuat& B, T Alpha) noexcept
    {
        return Lerp(A, B, Alpha).Normalize();
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr TQuat SLerp(const TQuat& A, const TQuat& B, T Alpha) noexcept
    {
        T _Dot = Dot(A.Payload, B.Payload);

        TQuat BAdj = B;
        if (_Dot < T{0})
        {
            BAdj = -B;
            _Dot = -_Dot;
        }

        constexpr T DotThreshold = T{0.9995};
        if (_Dot > DotThreshold)
        {
            return NLerp(A, BAdj, Alpha);
        }

        const T Theta = Acos(_Dot);
        const T SinTheta = Sin(Theta);

        const T W1 = Sin((T{1} - Alpha) * Theta) / SinTheta;
        const T W2 = Sin(Alpha * Theta) / SinTheta;

        return W1 * A + W2 * BAdj;
    }

    ROXY_NODISCARD ROXY_INLINE TVec<T, 3> Rotate(const TVec<T, 3>& V) const noexcept
    {
        const TQuat P(V, T{0});
        const TQuat R = (*this) * P * Inverse();
        return TVec<T, 3>{R.X(), R.Y(), R.Z()};
    }
};

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator+(const TQuat<T>& Quat) noexcept
{
    return Quat;
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator-(const TQuat<T>& Quat) noexcept
{
    return TQuat<T>(-Quat.Payload);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator+(const TQuat<T>& Lhs, const TQuat<T>& Rhs) noexcept
{
    return TQuat<T>(Lhs.Payload + Rhs.Payload);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator-(const TQuat<T>& Lhs, const TQuat<T>& Rhs) noexcept
{
    return TQuat<T>(Lhs.Payload - Rhs.Payload);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator*(const TQuat<T>& Lhs, const TQuat<T>& Rhs) noexcept
{
    const auto& LP = Lhs.Payload;
    const auto& RP = Rhs.Payload;

    const auto LW = LP[3], RW = RP[3];
    const TVec<T, 3> LV{LP[0], LP[1], LP[2]};
    const TVec<T, 3> RV{RP[0], RP[1], RP[2]};

    const auto W = LW * RW - Dot(LV, RV);
    const auto V = LW * RV + RW * LV + Cross(LV, RV);

    return TQuat<T>(V, W);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator/(const TQuat<T>& Lhs, const TQuat<T>& Rhs) noexcept
{
    return Lhs * Rhs.Inverse();
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator*(const TQuat<T>& Quat, T Scalar) noexcept
{
    return TQuat<T>(Quat.Payload * Scalar);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator*(T Scalar, const TQuat<T>& Quat) noexcept
{
    return TQuat<T>(Scalar * Quat.Payload);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator/(const TQuat<T>& Quat, T Scalar) noexcept
{
    return TQuat<T>(Quat.Payload / Scalar);
}

}
