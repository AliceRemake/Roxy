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
    #pragma region Construct
    ROXY_NODISCARD ROXY_INLINE constexpr TQuat() : Payload({T{0}, T{0}, T{0}, T{0}}) {}

    ROXY_NODISCARD ROXY_INLINE constexpr explicit TQuat(T X, T Y, T Z, T W) : Payload({X, Y, Z, W}) {}

    ROXY_NODISCARD ROXY_INLINE constexpr explicit TQuat(const TVec<T, 4>& V) : Payload(V) {}

    ROXY_NODISCARD ROXY_INLINE constexpr explicit TQuat(const TVec<T, 3>& V, T W) : Payload({V.X(), V.Y(), V.Z(), W}) {}

    ROXY_NODISCARD ROXY_INLINE static constexpr TQuat Zero() noexcept
    {
        return TQuat();
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr TQuat Identity() noexcept
    {
        return TQuat(T{0}, T{0}, T{0}, T{1});
    }
    #pragma endregion

    #pragma region Accessor
    ROXY_NODISCARD ROXY_INLINE constexpr T& operator[](FIndex Idx) noexcept
    {
        ROXY_ASSERT((0 <= Idx && Idx < 4) && "Quat Index Out Of Bound");
        return Vec()[Idx];
    }
    ROXY_NODISCARD ROXY_INLINE constexpr T operator[](FIndex Idx) const noexcept
    {
        ROXY_ASSERT((0 <= Idx && Idx < 4) && "Quat Index Out Of Bound");
        return Vec()[Idx];
    }
    ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, 4>& Vec() noexcept { return Payload; }
    ROXY_NODISCARD ROXY_INLINE constexpr const TVec<T, 4>& Vec() const noexcept { return Payload; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& X() noexcept { return Vec()[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& Y() noexcept { return Vec()[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& Z() noexcept { return Vec()[2]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T& W() noexcept { return Vec()[3]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T X() const noexcept { return Vec()[0]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T Y() const noexcept { return Vec()[1]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T Z() const noexcept { return Vec()[2]; }
    ROXY_NODISCARD ROXY_INLINE constexpr T W() const noexcept { return Vec()[3]; }
    #pragma endregion

    #pragma region Operator
    ROXY_INLINE constexpr TQuat& operator+=(const TQuat& Rhs) noexcept
    {
        Vec() += Rhs.Vec();
        return *this;
    }

    ROXY_INLINE constexpr TQuat& operator-=(const TQuat& Rhs) noexcept
    {
        Vec() -= Rhs.Vec();
        return *this;
    }

    ROXY_INLINE constexpr TQuat& operator*=(const TQuat& Rhs) noexcept
    {
        const auto& L_P = Vec();
        const auto& R_P = Rhs.Vec();

        const auto L_W = L_P[3], R_W = R_P[3];
        const TVec<T, 3> L_V{ L_P[0], L_P[1], L_P[2] };
        const TVec<T, 3> R_V{ R_P[0], R_P[1], R_P[2] };

        const auto V = L_W * R_V + R_W * L_V + L_V.Cross(R_V);
        const auto W = L_W * R_W - L_V.Dot(R_V);

        Vec() = TVec<T, 4>{ V[0], V[1], V[2], W };
        return *this;
    }

    ROXY_INLINE constexpr TQuat& operator/=(const TQuat& Rhs) noexcept
    {
        TQuat R = Rhs;
        R.Inverse();
        return *this *= R;
    }
    #pragma endregion

    template <CFloatingPoint U> requires std::is_convertible_v<T, U>
    ROXY_NODISCARD ROXY_INLINE constexpr TQuat<U> As() const noexcept
    {
        return TQuat<U>(Vec().template As<U>());
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T SqrLength() const noexcept
    {
        return Vec().SqrLength();
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T Length() const noexcept
    {
        return Vec().Length();
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T InvSqrLength() const noexcept
    {
        return Vec().InvSqrLength();
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T InvLength() const noexcept
    {
        return Vec().InvLength();
    }

    ROXY_INLINE constexpr TQuat& Normalize() noexcept
    {
        Vec() *= InvLength();
        return *this;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TQuat Normalized() const noexcept
    {
        return TQuat(Vec() * InvLength());
    }

    ROXY_INLINE constexpr TQuat& Conjugate() noexcept
    {
        Vec()[0] = -Vec()[0];
        Vec()[1] = -Vec()[1];
        Vec()[2] = -Vec()[2];
        return *this;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TQuat Conjugated() const noexcept
    {
        return TQuat(-Vec()[0], -Vec()[1], -Vec()[2], Vec()[3]);
    }

    ROXY_INLINE constexpr TQuat& Inverse() noexcept
    {
        Conjugate();
        Vec() *= InvSqrLength();
        return *this;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TQuat Inversed() const noexcept
    {
        return TQuat(TVec<T,4>{-Vec()[0], -Vec()[1], -Vec()[2], Vec()[3]} * InvSqrLength());
    }

    template<FIndex Dim> requires (Dim == 3 || Dim == 4)
    ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> Mat() const noexcept
    {
        const T XVal = X();
        const T YVal = Y();
        const T ZVal = Z();
        const T WVal = W();

        const T X_X = XVal * XVal;
        const T Y_Y = YVal * YVal;
        const T Z_Z = ZVal * ZVal;
        const T X_Y = XVal * YVal;
        const T X_Z = XVal * ZVal;
        const T Y_Z = YVal * ZVal;
        const T W_X = WVal * XVal;
        const T W_Y = WVal * YVal;
        const T W_Z = WVal * ZVal;

        if constexpr (Dim == 3)
        {
            return TMat<T, Dim>(
            {
                T{1} - T{2} * (Y_Y + Z_Z),        T{2} * (X_Y - W_Z),        T{2} * (X_Z + W_Y),
                       T{2} * (X_Y + W_Z), T{1} - T{2} * (X_X + Z_Z),        T{2} * (Y_Z - W_X),
                       T{2} * (X_Z - W_Y),        T{2} * (Y_Z + W_X), T{1} - T{2} * (X_X + Y_Y)
            });
        }
        else
        {
            static_assert(Dim == 4);
            return TMat<T, Dim>(
            {
                T{1} - T{2} * (Y_Y + Z_Z),        T{2} * (X_Y - W_Z),        T{2} * (X_Z + W_Y), T{0},
                       T{2} * (X_Y + W_Z), T{1} - T{2} * (X_X + Z_Z),        T{2} * (Y_Z - W_X), T{0},
                       T{2} * (X_Z - W_Y),        T{2} * (Y_Z + W_X), T{1} - T{2} * (X_X + Y_Y), T{0},
                                     T{0},                      T{0},                      T{0}, T{1}
            });
        }
    }

    template<FIndex Dim> requires (Dim == 3 || Dim == 4)
    ROXY_NODISCARD ROXY_INLINE explicit constexpr operator TMat<T, Dim>() const noexcept
    {
        return Mat<T, Dim>();
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, 3> Rotate(const TVec<T, 3>& V) const noexcept
    {
        ROXY_ASSERT_MSG(Approx(SqrLength(), T{1}), "TQuat: Rotate Called With Non Unit Quat");
        const auto& Q = Vec();
        const TVec<T, 3> Q_V{ Q[0], Q[1], Q[2] };
        const TVec<T, 3> Temp = T{2} * Q_V.Cross(V);
        return V + Q[3] * Temp + Q_V.Cross(Temp);
    }
};

#pragma region Operator
template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator+(const TQuat<T>& Quat) noexcept
{
    return TQuat<T>(Quat.Vec());
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator-(const TQuat<T>& Quat) noexcept
{
    return TQuat<T>(-Quat.Vec());
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr bool operator==(const TQuat<T>& Lhs, const TQuat<T>& Rhs) noexcept
{
    return Lhs.Vec() == Rhs.Vec();
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr bool operator!=(const TQuat<T>& Lhs, const TQuat<T>& Rhs) noexcept
{
    return !(Lhs == Rhs);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator+(const TQuat<T>& Lhs, const TQuat<T>& Rhs) noexcept
{
    return TQuat<T>(Lhs.Vec() + Rhs.Vec());
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator-(const TQuat<T>& Lhs, const TQuat<T>& Rhs) noexcept
{
    return TQuat<T>(Lhs.Vec() - Rhs.Vec());
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator*(const TQuat<T>& Lhs, const TQuat<T>& Rhs) noexcept
{
    const auto& L_P = Lhs.Vec();
    const auto& R_P = Rhs.Vec();

    const auto L_W = L_P[3], R_W = R_P[3];
    const TVec<T, 3> L_V{ L_P[0], L_P[1], L_P[2] };
    const TVec<T, 3> R_V{ R_P[0], R_P[1], R_P[2] };

    const auto V = L_W * R_V + R_W * L_V + L_V.Cross(R_V);
    const auto W = L_W * R_W - L_V.Dot(R_V);

    return TQuat<T>(V, W);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> operator/(const TQuat<T>& Lhs, const TQuat<T>& Rhs) noexcept
{
    return Lhs * Rhs.Inversed();
}
#pragma endregion

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> Lerp(const TQuat<T>& A, const TQuat<T>& B, T Alpha) noexcept
{
    return TQuat((T{1} - Alpha) * A.Vec() + Alpha * B.Vec());
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> NLerp(const TQuat<T>& A, const TQuat<T>& B, T Alpha) noexcept
{
    return Lerp(A, B, Alpha).Normalize();
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr TQuat<T> SLerp(const TQuat<T>& A, const TQuat<T>& B, T Alpha) noexcept
{
    T DotVal = A.Vec().Dot(B.Vec());

    TQuat BAdj = B;
    if (DotVal < T{0})
    {
        BAdj = -B;
        DotVal = -DotVal;
    }

    if (DotVal > T{0.9995})
    {
        return NLerp(A, BAdj, Alpha);
    }

    const T Theta = Acos(DotVal);
    const T InvSinTheta = InvSqrt(T{1} - DotVal * DotVal);

    const T W1 = Sin((T{1} - Alpha) * Theta) * InvSinTheta;
    const T W2 = Sin(Alpha * Theta) * InvSinTheta;

    return TQuat(W1 * A.Vec() + W2 * BAdj.Vec());
}
}

namespace Roxy::Math
{
using FQuat = TQuat<float>;
}
