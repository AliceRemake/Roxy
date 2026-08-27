#pragma once

#include <RoxyMath/RoxyMathVec.h>

namespace Roxy::Math
{
template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4) class TVecBase;
template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4) class TVec;
template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4) class TMatBase;
template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4) class TMat;
template <CFloatingPoint T> class TQuat;

template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4)
class TMatBase
{
protected:
    using FVec = TVec<T, Dim>;
    using FMat = TMat<T, Dim>;
    FVec Payload[Dim]{};

public:
    ROXY_NODISCARD ROXY_INLINE constexpr TMatBase() noexcept = default;

    ROXY_NODISCARD ROXY_INLINE constexpr explicit TMatBase(T Scalar) noexcept
    {
        for (FIndex Row = 0; Row < Dim; ++Row)
        {
            for (FIndex Col = 0; Col < Dim; ++Col)
            {
                Payload[Row].Payload[Col] = (Row == Col) ? Scalar : T{0};
            }
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMatBase(TInitList<T> InitList) noexcept
    {
        ROXY_ASSERT(InitList.size() <= Dim * Dim);
        auto It = InitList.begin();
        for (FIndex Row = 0; Row < Dim; ++Row)
        {
            for (FIndex Col = 0; Col < Dim; ++Col)
            {
                Payload[Row].Payload[Col] = It == InitList.end() ? T(0) : *(It++);
            }
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMatBase(TInitList<TVec<T, Dim>> InitList) noexcept
    {
        ROXY_ASSERT(InitList.size() <= Dim);
        auto It = InitList.begin();
        for (FIndex Row = 0; Row < Dim; ++Row)
        {
            Payload[Row] = It == InitList.end() ? FVec::Zero() : *(It++);
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr FVec& operator[](FIndex Row) noexcept
    {
        ROXY_ASSERT_MSG(0 <= Row && Row < Dim, "Mat Index Out Of Bound");
        return Payload[Row];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr const FVec& operator[](FIndex Row) const noexcept
    {
        ROXY_ASSERT_MSG(0 <= Row && Row < Dim, "Mat Index Out Of Bound");
        return Payload[Row];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T& operator[](FIndex Row, FIndex Col) noexcept
    {
        ROXY_ASSERT_MSG(0 <= Row && Row < Dim && 0 <= Col && Col < Dim, "Mat Index Out Of Bound");
        return Payload[Row][Col];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr const T& operator[](FIndex Row, FIndex Col) const noexcept
    {
        ROXY_ASSERT_MSG(0 <= Row && Row < Dim && 0 <= Col && Col < Dim, "Mat Index Out Of Bound");
        return Payload[Row][Col];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> Row(FIndex Idx) const noexcept
    {
        ROXY_ASSERT_MSG(0 <= Idx && Idx < Dim, "Row Index Out Of Bound");
        return Payload[Idx];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> Col(FIndex Idx) const noexcept
    {
        ROXY_ASSERT_MSG(0 <= Idx && Idx < Dim, "Col Index Out Of Bound");
        TVec<T, Dim> Result;
        for (FIndex Row = 0; Row < Dim; ++Row)
        {
            Result.Payload[Row] = Payload[Row][Idx];
        }
        return Result;
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FMat Zero() noexcept
    {
        return FMat(T{0});
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FMat Identity() noexcept
    {
        return FMat(T{1});
    }

    ROXY_NODISCARD ROXY_INLINE constexpr bool operator==(const FMat& Oth) const noexcept
    {
        for (FIndex Row = 0; Row < Dim; ++Row)
        {
            if (Payload[Row] != Oth.Payload[Row])
            {
                return false;
            }
        }
        return true;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr bool operator!=(const FMat& Oth) const noexcept
    {
        return !(*this == Oth);
    }

    ROXY_NODISCARD ROXY_INLINE constexpr FMat Trans() const noexcept
    {
        FMat Result;
        for (FIndex Row = 0; Row < Dim; ++Row)
        {
            for (FIndex Col = 0; Col < Dim; ++Col)
            {
                Result.Payload[Col][Row] = Payload[Row][Col];
            }
        }
        return Result;
    }
};

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator+(const TMat<T, Dim>& Mat) noexcept
{
    return Mat;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator-(const TMat<T, Dim>& Mat) noexcept
{
    TMat<T, Dim> R;
    for (FIndex i = 0; i < Dim; ++i)
    {
        R[i] = -Mat[i];
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator+(const TMat<T, Dim>& Lhs, const TMat<T, Dim>& Rhs) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Lhs[Row] + Rhs[Row];
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator-(const TMat<T, Dim>& Lhs, const TMat<T, Dim>& Rhs) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Lhs[Row] - Rhs[Row];
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator*(const TMat<T, Dim>& Lhs, const TMat<T, Dim>& Rhs) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        for (FIndex Col = 0; Col < Dim; ++Col)
        {
            for (FIndex I = 0; I < Dim; ++I)
            {
                R[Row][Col] += Lhs[Row][I] * Rhs[I][Col];
            }
        }
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(const TMat<T, Dim>& Mat, const TVec<T, Dim>& Vec) noexcept
{
    TVec<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Dot(Mat[Row], Vec);
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator+(const TMat<T, Dim>& Mat, T Scalar) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Mat[Row] + Scalar;
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator+(T Scalar, const TMat<T, Dim>& Mat) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Scalar + Mat[Row];
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator-(const TMat<T, Dim>& Mat, T Scalar) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Mat[Row] - Scalar;
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator-(T Scalar, const TMat<T, Dim>& Mat) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Scalar - Mat[Row];
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator*(const TMat<T, Dim>& Mat, T Scalar) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Mat[Row] * Scalar;
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator*(T Scalar, const TMat<T, Dim>& Mat) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Scalar * Mat[Row];
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator/(const TMat<T, Dim>& Mat, T Scalar) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Mat[Row] / Scalar;
    }
    return R;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator/(T Scalar, const TMat<T, Dim>& Mat) noexcept
{
    TMat<T, Dim> R;
    for (FIndex Row = 0; Row < Dim; ++Row)
    {
        R[Row] = Scalar / Mat[Row];
    }
    return R;
}

template <CFloatingPoint T> requires std::is_arithmetic_v<T>
class TMat<T, 2> : public TMatBase<T, 2>
{
public:
    friend class TMatBase<T, 2>;
    using TMatBase<T, 2>::TMatBase;

    ROXY_NODISCARD ROXY_INLINE constexpr T Determinant() const noexcept
    {
        return (*this)[0,0] * (*this)[1,1] - (*this)[0,1] * (*this)[1,0];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Inverse() const noexcept requires std::is_floating_point_v<T>
    {
        const T Det = Determinant();
        ROXY_ASSERT_MSG(Abs(Det) > Eps<T>, "Inverse: Singular Matrix");
        const T InvDet = T{1} / Det;

        TMat Result;
        Result[0,0] =  (*this)[1,1] * InvDet;
        Result[0,1] = -(*this)[0,1] * InvDet;
        Result[1,0] = -(*this)[1,0] * InvDet;
        Result[1,1] =  (*this)[0,0] * InvDet;
        return Result;
    }
};

template <CFloatingPoint T> requires std::is_arithmetic_v<T>
class TMat<T, 3> : public TMatBase<T, 3>
{
public:
    friend class TMatBase<T, 3>;
    using TMatBase<T, 3>::TMatBase;

    ROXY_NODISCARD ROXY_INLINE constexpr T Det() const noexcept
    {
        const T A = (*this)[0,0], B = (*this)[0,1], C = (*this)[0,2];
        const T D = (*this)[1,0], E = (*this)[1,1], F = (*this)[1,2];
        const T G = (*this)[2,0], H = (*this)[2,1], I = (*this)[2,2];
        return A * (E * I - F * H)
             - B * (D * I - F * G)
             + C * (D * H - E * G);
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Inv() const noexcept requires std::is_floating_point_v<T>
    {
        const T _Det = Det();
        ROXY_ASSERT_MSG(Abs(_Det) > Eps<T>, "Inverse: Singular Matrix");
        const T InvDet = T{1} / _Det;

        TMat Cof;
        Cof[0,0] = (*this)[1,1] * (*this)[2,2] - (*this)[1,2] * (*this)[2,1];
        Cof[0,1] = (*this)[1,2] * (*this)[2,0] - (*this)[1,0] * (*this)[2,2];
        Cof[0,2] = (*this)[1,0] * (*this)[2,1] - (*this)[1,1] * (*this)[2,0];
        Cof[1,0] = (*this)[0,2] * (*this)[2,1] - (*this)[0,1] * (*this)[2,2];
        Cof[1,1] = (*this)[0,0] * (*this)[2,2] - (*this)[0,2] * (*this)[2,0];
        Cof[1,2] = (*this)[0,1] * (*this)[2,0] - (*this)[0,0] * (*this)[2,1];
        Cof[2,0] = (*this)[0,1] * (*this)[1,2] - (*this)[0,2] * (*this)[1,1];
        Cof[2,1] = (*this)[0,2] * (*this)[1,0] - (*this)[0,0] * (*this)[1,2];
        Cof[2,2] = (*this)[0,0] * (*this)[1,1] - (*this)[0,1] * (*this)[1,0];

        return InvDet * Cof.Trans();
    }
};

template <CFloatingPoint T> requires std::is_arithmetic_v<T>
class TMat<T, 4> : public TMatBase<T, 4>
{
public:
    friend class TMatBase<T, 4>;
    using TMatBase<T, 4>::TMatBase;

    ROXY_NODISCARD ROXY_INLINE constexpr T Det() const noexcept
    {
        const T A = (*this)[0,0], B = (*this)[0,1], C = (*this)[0,2], D = (*this)[0,3];
        const T E = (*this)[1,0], F = (*this)[1,1], G = (*this)[1,2], H = (*this)[1,3];
        const T I = (*this)[2,0], J = (*this)[2,1], K = (*this)[2,2], L = (*this)[2,3];
        const T M = (*this)[3,0], N = (*this)[3,1], O = (*this)[3,2], P = (*this)[3,3];

        return A * (F * (K * P - L * O) - G * (J * P - L * N) + H * (J * O - K * N))
             - B * (E * (K * P - L * O) - G * (I * P - L * M) + H * (I * O - K * M))
             + C * (E * (J * P - L * N) - F * (I * P - L * M) + H * (I * N - J * M))
             - D * (E * (J * O - K * N) - F * (I * O - K * M) + G * (I * N - J * M));
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Inv() const noexcept requires std::is_floating_point_v<T>
    {
        const T _Det = Det();
        ROXY_ASSERT_MSG(Abs(_Det) > Eps<T>, "Inverse: Singular Matrix");
        const T InvDet = T{1} / _Det;

        TMat Cof;
        Cof[0,0] = (*this)[1,1] * ((*this)[2,2] * (*this)[3,3] - (*this)[2,3] * (*this)[3,2])
                 - (*this)[1,2] * ((*this)[2,1] * (*this)[3,3] - (*this)[2,3] * (*this)[3,1])
                 + (*this)[1,3] * ((*this)[2,1] * (*this)[3,2] - (*this)[2,2] * (*this)[3,1]);
        Cof[0,1] = -(*this)[1,0] * ((*this)[2,2] * (*this)[3,3] - (*this)[2,3] * (*this)[3,2])
                 + (*this)[1,2] * ((*this)[2,0] * (*this)[3,3] - (*this)[2,3] * (*this)[3,0])
                 - (*this)[1,3] * ((*this)[2,0] * (*this)[3,2] - (*this)[2,2] * (*this)[3,0]);
        Cof[0,2] = (*this)[1,0] * ((*this)[2,1] * (*this)[3,3] - (*this)[2,3] * (*this)[3,1])
                 - (*this)[1,1] * ((*this)[2,0] * (*this)[3,3] - (*this)[2,3] * (*this)[3,0])
                 + (*this)[1,3] * ((*this)[2,0] * (*this)[3,1] - (*this)[2,1] * (*this)[3,0]);
        Cof[0,3] = -(*this)[1,0] * ((*this)[2,1] * (*this)[3,2] - (*this)[2,2] * (*this)[3,1])
                 + (*this)[1,1] * ((*this)[2,0] * (*this)[3,2] - (*this)[2,2] * (*this)[3,0])
                 - (*this)[1,2] * ((*this)[2,0] * (*this)[3,1] - (*this)[2,1] * (*this)[3,0]);
        Cof[1,0] = -(*this)[0,1] * ((*this)[2,2] * (*this)[3,3] - (*this)[2,3] * (*this)[3,2])
                 + (*this)[0,2] * ((*this)[2,1] * (*this)[3,3] - (*this)[2,3] * (*this)[3,1])
                 - (*this)[0,3] * ((*this)[2,1] * (*this)[3,2] - (*this)[2,2] * (*this)[3,1]);
        Cof[1,1] = (*this)[0,0] * ((*this)[2,2] * (*this)[3,3] - (*this)[2,3] * (*this)[3,2])
                 - (*this)[0,2] * ((*this)[2,0] * (*this)[3,3] - (*this)[2,3] * (*this)[3,0])
                 + (*this)[0,3] * ((*this)[2,0] * (*this)[3,2] - (*this)[2,2] * (*this)[3,0]);
        Cof[1,2] = -(*this)[0,0] * ((*this)[2,1] * (*this)[3,3] - (*this)[2,3] * (*this)[3,1])
                 + (*this)[0,1] * ((*this)[2,0] * (*this)[3,3] - (*this)[2,3] * (*this)[3,0])
                 - (*this)[0,3] * ((*this)[2,0] * (*this)[3,1] - (*this)[2,1] * (*this)[3,0]);
        Cof[1,3] = (*this)[0,0] * ((*this)[2,1] * (*this)[3,2] - (*this)[2,2] * (*this)[3,1])
                 - (*this)[0,1] * ((*this)[2,0] * (*this)[3,2] - (*this)[2,2] * (*this)[3,0])
                 + (*this)[0,2] * ((*this)[2,0] * (*this)[3,1] - (*this)[2,1] * (*this)[3,0]);
        Cof[2,0] = (*this)[0,1] * ((*this)[1,2] * (*this)[3,3] - (*this)[1,3] * (*this)[3,2])
                 - (*this)[0,2] * ((*this)[1,1] * (*this)[3,3] - (*this)[1,3] * (*this)[3,1])
                 + (*this)[0,3] * ((*this)[1,1] * (*this)[3,2] - (*this)[1,2] * (*this)[3,1]);
        Cof[2,1] = -(*this)[0,0] * ((*this)[1,2] * (*this)[3,3] - (*this)[1,3] * (*this)[3,2])
                 + (*this)[0,2] * ((*this)[1,0] * (*this)[3,3] - (*this)[1,3] * (*this)[3,0])
                 - (*this)[0,3] * ((*this)[1,0] * (*this)[3,2] - (*this)[1,2] * (*this)[3,0]);
        Cof[2,2] = (*this)[0,0] * ((*this)[1,1] * (*this)[3,3] - (*this)[1,3] * (*this)[3,1])
                 - (*this)[0,1] * ((*this)[1,0] * (*this)[3,3] - (*this)[1,3] * (*this)[3,0])
                 + (*this)[0,3] * ((*this)[1,0] * (*this)[3,1] - (*this)[1,1] * (*this)[3,0]);
        Cof[2,3] = -(*this)[0,0] * ((*this)[1,1] * (*this)[3,2] - (*this)[1,2] * (*this)[3,1])
                 + (*this)[0,1] * ((*this)[1,0] * (*this)[3,2] - (*this)[1,2] * (*this)[3,0])
                 - (*this)[0,2] * ((*this)[1,0] * (*this)[3,1] - (*this)[1,1] * (*this)[3,0]);
        Cof[3,0] = -(*this)[0,1] * ((*this)[1,2] * (*this)[2,3] - (*this)[1,3] * (*this)[2,2])
                 + (*this)[0,2] * ((*this)[1,1] * (*this)[2,3] - (*this)[1,3] * (*this)[2,1])
                 - (*this)[0,3] * ((*this)[1,1] * (*this)[2,2] - (*this)[1,2] * (*this)[2,1]);
        Cof[3,1] = (*this)[0,0] * ((*this)[1,2] * (*this)[2,3] - (*this)[1,3] * (*this)[2,2])
                 - (*this)[0,2] * ((*this)[1,0] * (*this)[2,3] - (*this)[1,3] * (*this)[2,0])
                 + (*this)[0,3] * ((*this)[1,0] * (*this)[2,2] - (*this)[1,2] * (*this)[2,0]);
        Cof[3,2] = -(*this)[0,0] * ((*this)[1,1] * (*this)[2,3] - (*this)[1,3] * (*this)[2,1])
                 + (*this)[0,1] * ((*this)[1,0] * (*this)[2,3] - (*this)[1,3] * (*this)[2,0])
                 - (*this)[0,3] * ((*this)[1,0] * (*this)[2,1] - (*this)[1,1] * (*this)[2,0]);
        Cof[3,3] = (*this)[0,0] * ((*this)[1,1] * (*this)[2,2] - (*this)[1,2] * (*this)[2,1])
                 - (*this)[0,1] * ((*this)[1,0] * (*this)[2,2] - (*this)[1,2] * (*this)[2,0])
                 + (*this)[0,2] * ((*this)[1,0] * (*this)[2,1] - (*this)[1,1] * (*this)[2,0]);

        return InvDet * Cof.Trans();
    }
};

}
