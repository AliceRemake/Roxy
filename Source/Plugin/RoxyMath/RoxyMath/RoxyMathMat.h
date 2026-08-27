#pragma once

#include <RoxyMath/RoxyMathVec.h>

namespace Roxy::Math
{
template <CFloatingPoint T, FIndex Dim> requires (2 <= Dim && Dim <= 4)
class TMatBase
{
protected:
    using FVec = TVec<T, Dim>;
    using FMat = TMat<T, Dim>;
    FVec Payload[Dim]{};

public:
    #pragma region Construct
    ROXY_NODISCARD ROXY_INLINE constexpr TMatBase() noexcept = default;

    ROXY_NODISCARD ROXY_INLINE constexpr TMatBase(TInitList<T> InitList) noexcept
    {
        ROXY_ASSERT_MSG(InitList.size() <= Dim * Dim, "InitList Size Out Of Bound");
        auto It = InitList.begin();
        for (FIndex Row = 0; Row < Dim; ++Row)
        {
            for (FIndex Col = 0; Col < Dim; ++Col)
            {
                Payload[Row].Payload[Col] = It == InitList.end() ? T{0} : *(It++);
            }
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMatBase(TInitList<TVec<T, Dim>> InitList) noexcept
    {
        ROXY_ASSERT_MSG(InitList.size() <= Dim, "InitList Size Out Of Bound");
        auto It = InitList.begin();
        for (FIndex Row = 0; Row < Dim; ++Row)
        {
            Payload[Row] = It == InitList.end() ? FVec::Zero() : *(It++);
        }
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FMat Zero() noexcept
    {
        return FMat();
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FMat Identity() noexcept
    {
        if constexpr (Dim == 2)
        {
            return FMat
            {
                T{1}, T{0},
                T{0}, T{1}
            };
        }
        else if constexpr (Dim == 3) {
            return FMat
            {
                T{1}, T{0}, T{0},
                T{0}, T{1}, T{0},
                T{0}, T{0}, T{1},
            };
        }
        else {
            static_assert(Dim == 4);
            return FMat
            {
                T{1}, T{0}, T{0}, T{0},
                T{0}, T{1}, T{0}, T{0},
                T{0}, T{0}, T{1}, T{0},
                T{0}, T{0}, T{0}, T{1},
            };
        }
    }
    #pragma endregion

    #pragma region Accessor
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

    ROXY_NODISCARD ROXY_INLINE constexpr T operator[](FIndex Row, FIndex Col) const noexcept
    {
        ROXY_ASSERT_MSG(0 <= Row && Row < Dim && 0 <= Col && Col < Dim, "Mat Index Out Of Bound");
        return Payload[Row][Col];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr FVec Row(FIndex Idx) const noexcept
    {
        ROXY_ASSERT_MSG(0 <= Idx && Idx < Dim, "Row Index Out Of Bound");
        return Payload[Idx];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr FVec Col(FIndex Idx) const noexcept
    {
        ROXY_ASSERT_MSG(0 <= Idx && Idx < Dim, "Col Index Out Of Bound");
        if constexpr (Dim == 2)
        {
            return FVec{ Payload[0].Payload[Idx], Payload[1].Payload[Idx] };
        }
        else if constexpr (Dim == 3) {
            return FVec{ Payload[0].Payload[Idx], Payload[1].Payload[Idx], Payload[2].Payload[Idx] };
        }
        else {
            static_assert(Dim == 4);
            return FVec{ Payload[0].Payload[Idx], Payload[1].Payload[Idx], Payload[2].Payload[Idx], Payload[3].Payload[Idx] };
        }
    }
    #pragma endregion

    ROXY_NODISCARD ROXY_INLINE constexpr T Determinant() const noexcept
    {
        if constexpr (Dim == 2)
        {
            const T A00 = Payload[0][0], A01 = Payload[0][1];
            const T A10 = Payload[1][0], A11 = Payload[1][1];

            return A00 * A11 - A01 * A10;
        }
        else if constexpr (Dim == 3)
        {
            const T A00 = Payload[0][0], A01 = Payload[0][1], A02 = Payload[0][2];
            const T A10 = Payload[1][0], A11 = Payload[1][1], A12 = Payload[1][2];
            const T A20 = Payload[2][0], A21 = Payload[2][1], A22 = Payload[2][2];

            return   A00 * (A11 * A22 - A12 * A21)
                   - A01 * (A10 * A22 - A12 * A20)
                   + A02 * (A10 * A21 - A11 * A20);
        }
        else
        {
            static_assert(Dim == 4);
            const T A00 = Payload[0][0], A01 = Payload[0][1], A02 = Payload[0][2], A03 = Payload[0][3];
            const T A10 = Payload[1][0], A11 = Payload[1][1], A12 = Payload[1][2], A13 = Payload[1][3];
            const T A20 = Payload[2][0], A21 = Payload[2][1], A22 = Payload[2][2], A23 = Payload[2][3];
            const T A30 = Payload[3][0], A31 = Payload[3][1], A32 = Payload[3][2], A33 = Payload[3][3];

            return   A00 * (A11 * (A22 * A33 - A23 * A32) - A12 * (A21 * A33 - A23 * A31) + A13 * (A21 * A32 - A22 * A31))
                   - A01 * (A10 * (A22 * A33 - A23 * A32) - A12 * (A20 * A33 - A23 * A30) + A13 * (A20 * A32 - A22 * A30))
                   + A02 * (A10 * (A21 * A33 - A23 * A31) - A11 * (A20 * A33 - A23 * A30) + A13 * (A20 * A31 - A21 * A30))
                   - A03 * (A10 * (A21 * A32 - A22 * A31) - A11 * (A20 * A32 - A22 * A30) + A12 * (A20 * A31 - A21 * A30));
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T InvDeterminant() const noexcept
    {
        const T Det = Determinant();
        ROXY_ASSERT_MSG(Abs(Det) > Eps<T>, "TMat: Singular Matrix");
        return T{1} / Det;
    }
};

template <CFloatingPoint T>
class TMat<T, 2> : public TMatBase<T, 2>
{
public:
    friend class TMatBase<T, 2>;
    using TMatBase<T, 2>::TMatBase;

    ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, 2> Mul(const TVec<T, 2>& Vec) const noexcept
    {
        return TVec<T, 2>
        {
            this->Payload[0].Dot(Vec),
            this->Payload[1].Dot(Vec),
        };
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Mul(const TMat& Rhs) const noexcept
    {
        const auto R0 = this->Payload[0];
        const auto R1 = this->Payload[1];
        return TMat
        {
            R0.Dot(Rhs.Col(0)),
            R0.Dot(Rhs.Col(1)),
            R1.Dot(Rhs.Col(0)),
            R1.Dot(Rhs.Col(1)),
        };
    }

    ROXY_INLINE constexpr TMat& Transpose() noexcept
    {
        std::swap(this->Payload[0][1], this->Payload[1][0]);
        return *this;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Transposed() const noexcept
    {
        return TMat
        {
            this->Payload[0][0], this->Payload[1][0],
            this->Payload[0][1], this->Payload[1][1]
        };
    }

    ROXY_INLINE constexpr TMat& Inverse() noexcept
    {
        const T InvDet = this->InvDeterminant();

        const T A00 = (*this)[0,0], A01 = (*this)[0,1];
        const T A10 = (*this)[1,0], A11 = (*this)[1,1];

        this->Payload[0][0] =   A11 * InvDet;
        this->Payload[0][1] = - A01 * InvDet;
        this->Payload[1][0] = - A10 * InvDet;
        this->Payload[1][1] =   A00 * InvDet;
        return *this;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Inversed() const noexcept
    {
        const T InvDet = this->InvDeterminant();

        const T A00 = (*this)[0,0], A01 = (*this)[0,1];
        const T A10 = (*this)[1,0], A11 = (*this)[1,1];

        TMat Cof_T;
        Cof_T[0,0] =   A11;
        Cof_T[0,1] = - A01;
        Cof_T[1,0] = - A10;
        Cof_T[1,1] =   A00;
        return InvDet * Cof_T;
    }
};

template <CFloatingPoint T>
class TMat<T, 3> : public TMatBase<T, 3>
{
public:
    friend class TMatBase<T, 3>;
    using TMatBase<T, 3>::TMatBase;

    ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, 3> Mul(const TVec<T, 3>& Vec) const noexcept
    {
        return TVec<T, 3>
        {
            this->Payload[0].Dot(Vec),
            this->Payload[1].Dot(Vec),
            this->Payload[2].Dot(Vec),
        };
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Mul(const TMat& Rhs) const noexcept
    {
        const auto R0 = this->Payload[0];
        const auto R1 = this->Payload[1];
        const auto R2 = this->Payload[2];
        return TMat
        {
            R0.Dot(Rhs.Col(0)),
            R0.Dot(Rhs.Col(1)),
            R0.Dot(Rhs.Col(2)),
            R1.Dot(Rhs.Col(0)),
            R1.Dot(Rhs.Col(1)),
            R1.Dot(Rhs.Col(2)),
            R2.Dot(Rhs.Col(0)),
            R2.Dot(Rhs.Col(1)),
            R2.Dot(Rhs.Col(2)),
        };
    }

    ROXY_INLINE constexpr TMat& Transpose() noexcept
    {
        std::swap(this->Payload[0][1], this->Payload[1][0]);
        std::swap(this->Payload[0][2], this->Payload[2][0]);
        std::swap(this->Payload[1][2], this->Payload[2][1]);
        return *this;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Transposed() const noexcept
    {
        return TMat
        {
            this->Payload[0][0], this->Payload[1][0], this->Payload[2][0],
            this->Payload[0][1], this->Payload[1][1], this->Payload[2][1],
            this->Payload[0][2], this->Payload[1][2], this->Payload[2][2]
        };
    }

    ROXY_INLINE constexpr TMat& Inverse() noexcept
    {
        const T InvDet = this->InvDeterminant();

        const T A00 = (*this)[0,0], A01 = (*this)[0,1], A02 = (*this)[0,2];
        const T A10 = (*this)[1,0], A11 = (*this)[1,1], A12 = (*this)[1,2];
        const T A20 = (*this)[2,0], A21 = (*this)[2,1], A22 = (*this)[2,2];

        this->Payload[0][0] = (A11 * A22 - A12 * A21) * InvDet;
        this->Payload[0][1] = (A02 * A21 - A01 * A22) * InvDet;
        this->Payload[0][2] = (A01 * A12 - A02 * A11) * InvDet;
        this->Payload[1][0] = (A12 * A20 - A10 * A22) * InvDet;
        this->Payload[1][1] = (A00 * A22 - A02 * A20) * InvDet;
        this->Payload[1][2] = (A02 * A10 - A00 * A12) * InvDet;
        this->Payload[2][0] = (A10 * A21 - A11 * A20) * InvDet;
        this->Payload[2][1] = (A01 * A20 - A00 * A21) * InvDet;
        this->Payload[2][2] = (A00 * A11 - A01 * A10) * InvDet;
        return *this;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Inversed() const noexcept
    {
        const T InvDet = this->InvDeterminant();

        const T A00 = (*this)[0,0], A01 = (*this)[0,1], A02 = (*this)[0,2];
        const T A10 = (*this)[1,0], A11 = (*this)[1,1], A12 = (*this)[1,2];
        const T A20 = (*this)[2,0], A21 = (*this)[2,1], A22 = (*this)[2,2];

        TMat Cof_T;
        Cof_T[0,0] = A11 * A22 - A12 * A21;
        Cof_T[0,1] = A02 * A21 - A01 * A22;
        Cof_T[0,2] = A01 * A12 - A02 * A11;
        Cof_T[1,0] = A12 * A20 - A10 * A22;
        Cof_T[1,1] = A00 * A22 - A02 * A20;
        Cof_T[1,2] = A02 * A10 - A00 * A12;
        Cof_T[2,0] = A10 * A21 - A11 * A20;
        Cof_T[2,1] = A01 * A20 - A00 * A21;
        Cof_T[2,2] = A00 * A11 - A01 * A10;

        return InvDet * Cof_T;
    }
};

template <CFloatingPoint T>
class TMat<T, 4> : public TMatBase<T, 4>
{
public:
    friend class TMatBase<T, 4>;
    using TMatBase<T, 4>::TMatBase;

    ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, 4> Mul(const TVec<T, 4>& Vec) const noexcept
    {
        return TVec<T, 4>
        {
            this->Payload[0].Dot(Vec),
            this->Payload[1].Dot(Vec),
            this->Payload[2].Dot(Vec),
            this->Payload[3].Dot(Vec),
        };
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Mul(const TMat& Rhs) const noexcept
    {
        const auto R0 = this->Payload[0];
        const auto R1 = this->Payload[1];
        const auto R2 = this->Payload[2];
        const auto R3 = this->Payload[3];
        return TMat
        {
            R0.Dot(Rhs.Col(0)),
            R0.Dot(Rhs.Col(1)),
            R0.Dot(Rhs.Col(2)),
            R0.Dot(Rhs.Col(3)),
            R1.Dot(Rhs.Col(0)),
            R1.Dot(Rhs.Col(1)),
            R1.Dot(Rhs.Col(2)),
            R1.Dot(Rhs.Col(3)),
            R2.Dot(Rhs.Col(0)),
            R2.Dot(Rhs.Col(1)),
            R2.Dot(Rhs.Col(2)),
            R2.Dot(Rhs.Col(3)),
            R3.Dot(Rhs.Col(0)),
            R3.Dot(Rhs.Col(1)),
            R3.Dot(Rhs.Col(2)),
            R3.Dot(Rhs.Col(3)),
        };
    }

    ROXY_INLINE constexpr TMat& Transpose() noexcept
    {
        std::swap(this->Payload[0][1], this->Payload[1][0]);
        std::swap(this->Payload[0][2], this->Payload[2][0]);
        std::swap(this->Payload[0][3], this->Payload[3][0]);
        std::swap(this->Payload[1][2], this->Payload[2][1]);
        std::swap(this->Payload[1][3], this->Payload[3][1]);
        std::swap(this->Payload[2][3], this->Payload[3][2]);
        return *this;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Transposed() const noexcept
    {
        return TMat
        {
            this->Payload[0][0], this->Payload[1][0], this->Payload[2][0], this->Payload[3][0],
            this->Payload[0][1], this->Payload[1][1], this->Payload[2][1], this->Payload[3][1],
            this->Payload[0][2], this->Payload[1][2], this->Payload[2][2], this->Payload[3][2],
            this->Payload[0][3], this->Payload[1][3], this->Payload[2][3], this->Payload[3][3]
        };
    }

    ROXY_INLINE constexpr TMat& Inverse() noexcept
    {
        const T InvDet = this->InvDeterminant();

        const T A00 = (*this)[0,0], A01 = (*this)[0,1], A02 = (*this)[0,2], A03 = (*this)[0,3];
        const T A10 = (*this)[1,0], A11 = (*this)[1,1], A12 = (*this)[1,2], A13 = (*this)[1,3];
        const T A20 = (*this)[2,0], A21 = (*this)[2,1], A22 = (*this)[2,2], A23 = (*this)[2,3];
        const T A30 = (*this)[3,0], A31 = (*this)[3,1], A32 = (*this)[3,2], A33 = (*this)[3,3];

        this->Payload[0][0] = (A11 * (A22 * A33 - A23 * A32)
                             - A12 * (A21 * A33 - A23 * A31)
                             + A13 * (A21 * A32 - A22 * A31)) * InvDet;
        this->Payload[0][1] = (- A01 * (A22 * A33 - A23 * A32)
                             + A02 * (A21 * A33 - A23 * A31)
                             - A03 * (A21 * A32 - A22 * A31)) * InvDet;
        this->Payload[0][2] = (A01 * (A12 * A33 - A13 * A32)
                             - A02 * (A11 * A33 - A13 * A31)
                             + A03 * (A11 * A32 - A12 * A31)) * InvDet;
        this->Payload[0][3] = (- A01 * (A12 * A23 - A13 * A22)
                             + A02 * (A11 * A23 - A13 * A21)
                             - A03 * (A11 * A22 - A12 * A21)) * InvDet;

        this->Payload[1][0] = (- A10 * (A22 * A33 - A23 * A32)
                             + A12 * (A20 * A33 - A23 * A30)
                             - A13 * (A20 * A32 - A22 * A30)) * InvDet;
        this->Payload[1][1] = (A00 * (A22 * A33 - A23 * A32)
                             - A02 * (A20 * A33 - A23 * A30)
                             + A03 * (A20 * A32 - A22 * A30)) * InvDet;
        this->Payload[1][2] = (- A00 * (A12 * A33 - A13 * A32)
                             + A02 * (A10 * A33 - A13 * A30)
                             - A03 * (A10 * A32 - A12 * A30)) * InvDet;
        this->Payload[1][3] = (A00 * (A12 * A23 - A13 * A22)
                             - A02 * (A10 * A23 - A13 * A20)
                             + A03 * (A10 * A22 - A12 * A20)) * InvDet;

        this->Payload[2][0] = (A10 * (A21 * A33 - A23 * A31)
                             - A11 * (A20 * A33 - A23 * A30)
                             + A13 * (A20 * A31 - A21 * A30)) * InvDet;
        this->Payload[2][1] = (- A00 * (A21 * A33 - A23 * A31)
                             + A01 * (A20 * A33 - A23 * A30)
                             - A03 * (A20 * A31 - A21 * A30)) * InvDet;
        this->Payload[2][2] = (A00 * (A11 * A33 - A13 * A31)
                             - A01 * (A10 * A33 - A13 * A30)
                             + A03 * (A10 * A31 - A11 * A30)) * InvDet;
        this->Payload[2][3] = (- A00 * (A11 * A23 - A13 * A21)
                             + A01 * (A10 * A23 - A13 * A20)
                             - A03 * (A10 * A21 - A11 * A20)) * InvDet;

        this->Payload[3][0] = (- A10 * (A21 * A32 - A22 * A31)
                             + A11 * (A20 * A32 - A22 * A30)
                             - A12 * (A20 * A31 - A21 * A30)) * InvDet;
        this->Payload[3][1] = (A00 * (A21 * A32 - A22 * A31)
                             - A01 * (A20 * A32 - A22 * A30)
                             + A02 * (A20 * A31 - A21 * A30)) * InvDet;
        this->Payload[3][2] = (- A00 * (A11 * A32 - A12 * A31)
                             + A01 * (A10 * A32 - A12 * A30)
                             - A02 * (A10 * A31 - A11 * A30)) * InvDet;
        this->Payload[3][3] = (A00 * (A11 * A22 - A12 * A21)
                             - A01 * (A10 * A22 - A12 * A20)
                             + A02 * (A10 * A21 - A11 * A20)) * InvDet;
        return *this;
    }

    ROXY_NODISCARD ROXY_INLINE constexpr TMat Inversed() const noexcept
    {
        const T InvDet = this->InvDeterminant();

        const T A00 = (*this)[0,0], A01 = (*this)[0,1], A02 = (*this)[0,2], A03 = (*this)[0,3];
        const T A10 = (*this)[1,0], A11 = (*this)[1,1], A12 = (*this)[1,2], A13 = (*this)[1,3];
        const T A20 = (*this)[2,0], A21 = (*this)[2,1], A22 = (*this)[2,2], A23 = (*this)[2,3];
        const T A30 = (*this)[3,0], A31 = (*this)[3,1], A32 = (*this)[3,2], A33 = (*this)[3,3];

        TMat Cof_T;
        Cof_T[0,0] =   A11 * (A22 * A33 - A23 * A32)
                     - A12 * (A21 * A33 - A23 * A31)
                     + A13 * (A21 * A32 - A22 * A31);
        Cof_T[0,1] = - A01 * (A22 * A33 - A23 * A32)
                     + A02 * (A21 * A33 - A23 * A31)
                     - A03 * (A21 * A32 - A22 * A31);
        Cof_T[0,2] =   A01 * (A12 * A33 - A13 * A32)
                     - A02 * (A11 * A33 - A13 * A31)
                     + A03 * (A11 * A32 - A12 * A31);
        Cof_T[0,3] = - A01 * (A12 * A23 - A13 * A22)
                     + A02 * (A11 * A23 - A13 * A21)
                     - A03 * (A11 * A22 - A12 * A21);

        Cof_T[1,0] = - A10 * (A22 * A33 - A23 * A32)
                     + A12 * (A20 * A33 - A23 * A30)
                     - A13 * (A20 * A32 - A22 * A30);
        Cof_T[1,1] =   A00 * (A22 * A33 - A23 * A32)
                     - A02 * (A20 * A33 - A23 * A30)
                     + A03 * (A20 * A32 - A22 * A30);
        Cof_T[1,2] = - A00 * (A12 * A33 - A13 * A32)
                     + A02 * (A10 * A33 - A13 * A30)
                     - A03 * (A10 * A32 - A12 * A30);
        Cof_T[1,3] =   A00 * (A12 * A23 - A13 * A22)
                     - A02 * (A10 * A23 - A13 * A20)
                     + A03 * (A10 * A22 - A12 * A20);

        Cof_T[2,0] =   A10 * (A21 * A33 - A23 * A31)
                     - A11 * (A20 * A33 - A23 * A30)
                     + A13 * (A20 * A31 - A21 * A30);
        Cof_T[2,1] = - A00 * (A21 * A33 - A23 * A31)
                     + A01 * (A20 * A33 - A23 * A30)
                     - A03 * (A20 * A31 - A21 * A30);
        Cof_T[2,2] =   A00 * (A11 * A33 - A13 * A31)
                     - A01 * (A10 * A33 - A13 * A30)
                     + A03 * (A10 * A31 - A11 * A30);
        Cof_T[2,3] = - A00 * (A11 * A23 - A13 * A21)
                     + A01 * (A10 * A23 - A13 * A20)
                     - A03 * (A10 * A21 - A11 * A20);

        Cof_T[3,0] = - A10 * (A21 * A32 - A22 * A31)
                     + A11 * (A20 * A32 - A22 * A30)
                     - A12 * (A20 * A31 - A21 * A30);
        Cof_T[3,1] =   A00 * (A21 * A32 - A22 * A31)
                     - A01 * (A20 * A32 - A22 * A30)
                     + A02 * (A20 * A31 - A21 * A30);
        Cof_T[3,2] = - A00 * (A11 * A32 - A12 * A31)
                     + A01 * (A10 * A32 - A12 * A30)
                     - A02 * (A10 * A31 - A11 * A30);
        Cof_T[3,3] =   A00 * (A11 * A22 - A12 * A21)
                     - A01 * (A10 * A22 - A12 * A20)
                     + A02 * (A10 * A21 - A11 * A20);

        return InvDet * Cof_T;
    }
};

#pragma region Operator
template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator+(const TMat<T, Dim>& Mat) noexcept
{
    if constexpr (Dim == 2)
    {
        return TMat<T, Dim>{ Mat[0], Mat[1] };
    }
    else if constexpr (Dim == 3)
    {
        return TMat<T, Dim>{ Mat[0], Mat[1], Mat[2] };
    }
    else
    {
        static_assert(Dim == 4);
        return TMat<T, Dim>{ Mat[0], Mat[1], Mat[2], Mat[3] };
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator-(const TMat<T, Dim>& Mat) noexcept
{
    if constexpr (Dim == 2)
    {
        return TMat<T, Dim>{ -Mat[0], -Mat[1] };
    }
    else if constexpr (Dim == 3)
    {
        return TMat<T, Dim>{ -Mat[0], -Mat[1], -Mat[2] };
    }
    else
    {
        static_assert(Dim == 4);
        return TMat<T, Dim>{ -Mat[0], -Mat[1], -Mat[2], -Mat[3] };
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr bool operator==(const TMat<T, Dim>& Lhs, const TMat<T, Dim>& Rhs) noexcept
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
ROXY_NODISCARD ROXY_INLINE constexpr bool operator!=(const TMat<T, Dim>& Lhs, const TMat<T, Dim>& Rhs) noexcept
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
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator+(const TMat<T, Dim>& Mat, T Scalar) noexcept
{
    if constexpr (Dim == 2)
    {
        return TMat<T, Dim>{ Mat[0] + Scalar, Mat[1] + Scalar };
    }
    else if constexpr (Dim == 3)
    {
        return TMat<T, Dim>{ Mat[0] + Scalar, Mat[1] + Scalar, Mat[2] + Scalar };
    }
    else
    {
        static_assert(Dim == 4);
        return TMat<T, Dim>{ Mat[0] + Scalar, Mat[1] + Scalar, Mat[2] + Scalar, Mat[3] + Scalar };
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator-(const TMat<T, Dim>& Mat, T Scalar) noexcept
{
    if constexpr (Dim == 2)
    {
        return TMat<T, Dim>{ Mat[0] - Scalar, Mat[1] - Scalar };
    }
    else if constexpr (Dim == 3)
    {
        return TMat<T, Dim>{ Mat[0] - Scalar, Mat[1] - Scalar, Mat[2] - Scalar };
    }
    else
    {
        static_assert(Dim == 4);
        return TMat<T, Dim>{ Mat[0] - Scalar, Mat[1] - Scalar, Mat[2] - Scalar, Mat[3] - Scalar };
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator*(const TMat<T, Dim>& Mat, T Scalar) noexcept
{
    if constexpr (Dim == 2)
    {
        return TMat<T, Dim>{ Mat[0] * Scalar, Mat[1] * Scalar };
    }
    else if constexpr (Dim == 3)
    {
        return TMat<T, Dim>{ Mat[0] * Scalar, Mat[1] * Scalar, Mat[2] * Scalar };
    }
    else
    {
        static_assert(Dim == 4);
        return TMat<T, Dim>{ Mat[0] * Scalar, Mat[1] * Scalar, Mat[2] * Scalar, Mat[3] * Scalar };
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator/(const TMat<T, Dim>& Mat, T Scalar) noexcept
{
    return Mat * (T{1} / Scalar);
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator+(T Scalar, const TMat<T, Dim>& Mat) noexcept
{
    return Mat + Scalar;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator-(T Scalar, const TMat<T, Dim>& Mat) noexcept
{
    return -Mat + Scalar;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator*(T Scalar, const TMat<T, Dim>& Mat) noexcept
{
    return Mat * Scalar;
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator/(T Scalar, const TMat<T, Dim>& Mat) noexcept
{
    if constexpr (Dim == 2)
    {
        return TMat<T, Dim>{ Scalar / Mat[0], Scalar / Mat[1] };
    }
    else if constexpr (Dim == 3)
    {
        return TMat<T, Dim>{ Scalar / Mat[0], Scalar / Mat[1], Scalar / Mat[2] };
    }
    else
    {
        static_assert(Dim == 4);
        return TMat<T, Dim>{ Scalar / Mat[0], Scalar / Mat[1], Scalar / Mat[2], Scalar / Mat[3] };
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator+(const TMat<T, Dim>& Lhs, const TMat<T, Dim>& Rhs) noexcept
{
    if constexpr (Dim == 2)
    {
        return TMat<T, Dim>{ Lhs[0] + Rhs[0], Lhs[1] + Rhs[1] };
    }
    else if constexpr (Dim == 3)
    {
        return TMat<T, Dim>{ Lhs[0] + Rhs[0], Lhs[1] + Rhs[1], Lhs[2] + Rhs[2] };
    }
    else
    {
        static_assert(Dim == 4);
        return TMat<T, Dim>{ Lhs[0] + Rhs[0], Lhs[1] + Rhs[1], Lhs[2] + Rhs[2], Lhs[3] + Rhs[3] };
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator-(const TMat<T, Dim>& Lhs, const TMat<T, Dim>& Rhs) noexcept
{
    if constexpr (Dim == 2)
    {
        return TMat<T, Dim>{ Lhs[0] - Rhs[0], Lhs[1] - Rhs[1] };
    }
    else if constexpr (Dim == 3)
    {
        return TMat<T, Dim>{ Lhs[0] - Rhs[0], Lhs[1] - Rhs[1], Lhs[2] - Rhs[2] };
    }
    else
    {
        static_assert(Dim == 4);
        return TMat<T, Dim>{ Lhs[0] - Rhs[0], Lhs[1] - Rhs[1], Lhs[2] - Rhs[2], Lhs[3] - Rhs[3] };
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator*(const TMat<T, Dim>& Lhs, const TMat<T, Dim>& Rhs) noexcept
{
    if constexpr (Dim == 2)
    {
        return TMat<T, Dim>{ Lhs[0] * Rhs[0], Lhs[1] * Rhs[1] };
    }
    else if constexpr (Dim == 3)
    {
        return TMat<T, Dim>{ Lhs[0] * Rhs[0], Lhs[1] * Rhs[1], Lhs[2] * Rhs[2] };
    }
    else
    {
        static_assert(Dim == 4);
        return TMat<T, Dim>{ Lhs[0] * Rhs[0], Lhs[1] * Rhs[1], Lhs[2] * Rhs[2], Lhs[3] * Rhs[3] };
    }
}

template <CFloatingPoint T, FIndex Dim>
ROXY_NODISCARD ROXY_INLINE constexpr TMat<T, Dim> operator/(const TMat<T, Dim>& Lhs, const TMat<T, Dim>& Rhs) noexcept
{
    if constexpr (Dim == 2)
    {
        return TMat<T, Dim>{ Lhs[0] / Rhs[0], Lhs[1] / Rhs[1] };
    }
    else if constexpr (Dim == 3)
    {
        return TMat<T, Dim>{ Lhs[0] / Rhs[0], Lhs[1] / Rhs[1], Lhs[2] / Rhs[2] };
    }
    else
    {
        static_assert(Dim == 4);
        return TMat<T, Dim>{ Lhs[0] / Rhs[0], Lhs[1] / Rhs[1], Lhs[2] / Rhs[2], Lhs[3] / Rhs[3] };
    }
}
#pragma endregion
}

namespace Roxy::Math
{
using FMat2 = TMat<float, 2>;
using FMat3 = TMat<float, 3>;
using FMat4 = TMat<float, 4>;
}
