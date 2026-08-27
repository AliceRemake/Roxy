#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyMath/RoxyMath.h>
#include <RoxyChrono/RoxyChrono.h>
#include <RoxyLog/RoxyLog.h>

using namespace Roxy::Math;

TEST_CASE("Roxy::Math")
{
    SUBCASE("Concept")
    {
        static_assert(CIntegral<I32>);
        static_assert(CIntegral<U32>);
        static_assert(!CIntegral<F32>);
        static_assert(!CIntegral<F64>);
        static_assert(!CFloatingPoint<I32>);
        static_assert(!CFloatingPoint<U32>);
        static_assert(CFloatingPoint<F32>);
        static_assert(CFloatingPoint<F64>);
        static_assert(CArithmetic<I32>);
        static_assert(CArithmetic<U32>);
        static_assert(CArithmetic<F32>);
        static_assert(CArithmetic<F64>);
    }

    SUBCASE("Constant")
    {
        CHECK(Approx(Pi<F32>,            std::numbers::pi_v<F32>));
        CHECK(Approx(E<F32>,             std::numbers::e_v<F32>));
        CHECK(Approx(Ln2<F32>,           std::log(2.0f)));
        CHECK(Approx(Ln10<F32>,          std::log(10.0f)));
        CHECK(Approx(Log2E<F32>,         std::log2(std::exp(1.0f))));
        CHECK(Approx(Log10E<F32>,        std::log10(std::exp(1.0f))));
        CHECK(Approx(Sqrt2<F32>,         std::sqrt(2.0f)));
        CHECK(Approx(Sqrt3<F32>,         std::sqrt(3.0f)));
        CHECK(Approx(InvSqrt2<F32>,      1.0f / std::sqrt(2.0f)));
        CHECK(Approx(DegToRadCoeff<F32>, Pi<F32> / 180.0f));
        CHECK(Approx(RadToDegCoeff<F32>, 180.0f / Pi<F32>));

        CHECK(Approx(Pi<F64>,            std::numbers::pi_v<F64>));
        CHECK(Approx(E<F64>,             std::numbers::e_v<F64>));
        CHECK(Approx(Ln2<F64>,           std::log(2.0)));
        CHECK(Approx(Ln10<F64>,          std::log(10.0)));
        CHECK(Approx(Log2E<F64>,         std::log2(std::exp(1.0))));
        CHECK(Approx(Log10E<F64>,        std::log10(std::exp(1.0))));
        CHECK(Approx(Sqrt2<F64>,         std::sqrt(2.0)));
        CHECK(Approx(Sqrt3<F64>,         std::sqrt(3.0)));
        CHECK(Approx(InvSqrt2<F64>,      1.0 / std::sqrt(2.0)));
        CHECK(Approx(DegToRadCoeff<F64>, Pi<F64> / 180.0));
        CHECK(Approx(RadToDegCoeff<F64>, 180.0 / Pi<F64>));
    }

    SUBCASE("Abs::CT")
    {
        static_assert(Abs(-5) == 5);
        static_assert(Abs( 5) == 5);
        static_assert(Approx(Abs(-3.14), 3.14));
        static_assert(Approx(Abs( 3.14), 3.14));
    }

    SUBCASE("Abs::RT")
    {
        CHECK(Abs(-5) == 5);
        CHECK(Abs( 5) == 5);
        CHECK(Approx(Abs(-3.14), 3.14));
        CHECK(Approx(Abs( 3.14), 3.14));
    }

    SUBCASE("(Inv)Sqrt::CT")
    {
        static_assert(Approx(   Sqrt(    0.0),   0.0 ));
        static_assert(Approx(   Sqrt(    1.0),   1.0 ));
        static_assert(Approx(InvSqrt(    1.0),   1.0 ));
        static_assert(Approx(   Sqrt(    4.0),   2.0 ));
        static_assert(Approx(InvSqrt(    4.0),   0.5 ));
        static_assert(Approx(   Sqrt(10000.0), 100.0 ));
        static_assert(Approx(InvSqrt(10000.0),   0.01));
    }

    SUBCASE("(Inv)Sqrt::RT")
    {
        for (volatile const auto X : { 1.0, 2.0, 3.0, 4.0, 9.0, 100.0})
        {
            CHECK(Approx(   Sqrt(X),     std::sqrt(X)));
            CHECK(Approx(InvSqrt(X), 1 / std::sqrt(X)));
        }
    }

    SUBCASE("Trig::CT")
    {
        static_assert(Approx(Sin( 0.0      ),  0.0 ));
        static_assert(Approx(Sin( Pi<F64>/2),  1.0 ));
        static_assert(Approx(Sin( Pi<F64>  ),  0.0 ));
        static_assert(Approx(Sin(-Pi<F64>/2), -1.0 ));
        static_assert(Approx(Cos( 0.0      ),  1.0 ));
        static_assert(Approx(Cos( Pi<F64>/2),  0.0 ));
        static_assert(Approx(Cos( Pi<F64>  ), -1.0 ));
        static_assert(Approx(Tan( 0.0      ),  0.0 ));
        static_assert(Approx(Tan( Pi<F64>/4),  1.0 ));
    }

    SUBCASE("Trig::RT")
    {
        for (volatile const auto X : { -1.0, -0.5, 0.5, 1.0, 2.0 })
        {
            CHECK(Approx(Sin(X), std::sin(X)));
            CHECK(Approx(Cos(X), std::cos(X)));
            CHECK(Approx(Tan(X), std::tan(X)));
        }
    }

    SUBCASE("InvTrig::CT")
    {
        static_assert(Approx(Asin( 0.0),  0.0     ));
        static_assert(Approx(Asin( 1.0),  Pi<F64>/2));
        static_assert(Approx(Asin(-1.0), -Pi<F64>/2));
        static_assert(Approx(Acos( 1.0),  0.0     ));
        static_assert(Approx(Acos( 0.0),  Pi<F64>/2));
        static_assert(Approx(Acos(-1.0),  Pi<F64> ));
        static_assert(Approx(Atan( 0.0),  0.0     ));
        static_assert(Approx(Atan( 1.0),  Pi<F64>/4));
        static_assert(Approx(Atan(-1.0), -Pi<F64>/4));
        static_assert(Approx(Atan2( 0.0,  1.0),  0.0     ));
        static_assert(Approx(Atan2( 1.0,  0.0),  Pi<F64>/2));
        static_assert(Approx(Atan2(-1.0,  0.0), -Pi<F64>/2));
    }

    SUBCASE("InvTrig::RT")
    {
        for (volatile const auto X : { -0.9, -0.5, 0.0, 0.5, 0.9 })
        {
            CHECK(Approx(Asin(X), std::asin(X)));
            CHECK(Approx(Acos(X), std::acos(X)));
            CHECK(Approx(Atan(X), std::atan(X)));
        }
        for (volatile const auto Y : { -1.0, -0.5, 0.5, 1.0 })
        {
            for (volatile const auto X : { -1.0, -0.5, 0.5, 1.0 })
            {
                CHECK(Approx(Atan2(Y, X), std::atan2(Y, X)));
            }
        }
    }

    SUBCASE("Hyp::CT")
    {
        static_assert(Approx(Sinh(0.0), 0.0));
        static_assert(Approx(Cosh(0.0), 1.0));
        static_assert(Approx(Tanh(0.0), 0.0));
    }

    SUBCASE("Hyp::RT")
    {
        for (volatile const auto X : { -2.0, -0.5, 0.5, 2.0 })
        {
            CHECK(Approx(Sinh(X), std::sinh(X)));
            CHECK(Approx(Cosh(X), std::cosh(X)));
            CHECK(Approx(Tanh(X), std::tanh(X)));
        }
    }

    SUBCASE("ExpLog::CT")
    {
        static_assert(Approx(Exp(  0.0),     1.0  ));
        static_assert(Approx(Exp(  1.0),     E<F64>));
        static_assert(Approx(Log(  1.0),     0.0  ));
        static_assert(Approx(Log(  E<F64>),  1.0  ));
        static_assert(Approx(Log2( 8.0),     3.0  ));
        static_assert(Approx(Log10(1000.0),  3.0  ));
    }

    SUBCASE("ExpLog::RT")
    {
        for (volatile const auto X : { -2.0, -1.0, 0.5, 1.0, 2.0 })
        {
            CHECK(Approx(Exp(X), std::exp(X)));
        }
        for (volatile const auto X : { 0.5, 1.0, 2.0, 10.0 })
        {
            CHECK(Approx(Log(X),   std::log(X)));
            CHECK(Approx(Log2(X),  std::log2(X)));
            CHECK(Approx(Log10(X), std::log10(X)));
        }
    }

    SUBCASE("Pow::CT")
    {
        static_assert(Approx(Pow(2.0,  0),  1.0));
        static_assert(Approx(Pow(2.0,  3),  8.0));
        static_assert(Approx(Pow(2.0, -1),  0.5));
        static_assert(Approx(Pow(4.0, 0.5), 2.0));
        static_assert(Approx(Pow(2.0, 0.5), Sqrt2<F64>));
    }

    SUBCASE("Pow::RT")
    {
        volatile F64 B = 2.0;
        volatile int Ei = 3;
        CHECK(Approx(Pow(B, Ei), 8.0));
        CHECK(Approx(Pow(B, -1), 0.5));
        CHECK(Approx(Pow(B, 0.5), std::sqrt(2.0)));
        CHECK(Approx(Pow(3.0, 2.0), 9.0));
    }

    SUBCASE("Utility::CT")
    {
        static_assert(Min(3, 5) == 3);
        static_assert(Max(3, 5) == 5);
        static_assert(Clamp( 7, 0, 10) ==  7);
        static_assert(Clamp(-1, 0, 10) ==  0);
        static_assert(Clamp(15, 0, 10) == 10);
        static_assert(Approx(Lerp(0.0, 10.0, 0.25), 2.5));
        static_assert(Approx(Fmod(5.5, 2.0), 1.5));
        static_assert(Approx(Floor( 3.7),  3.0 ));
        static_assert(Approx(Ceil(  3.2),  4.0 ));
        static_assert(Approx(Round( 3.5),  4.0 ));
        static_assert(Approx(Trunc(-3.7), -3.0 ));
        static_assert(Approx(ToRadian(180.0), Pi<F64>));
        static_assert(Approx(ToDegree(Pi<F64>), 180.0));
    }

    SUBCASE("Utility::RT")
    {
        CHECK(Min(3, 5) == 3);
        CHECK(Max(3, 5) == 5);
        CHECK(Clamp(-1, 0, 10) == 0);
        for (volatile const auto X : { 3.7, -3.7, 0.5, -0.5 })
        {
            CHECK(Approx(Floor(X), std::floor(X)));
            CHECK(Approx(Ceil(X),  std::ceil(X)));
            CHECK(Approx(Round(X), std::round(X)));
            CHECK(Approx(Trunc(X), std::trunc(X)));
        }
        volatile F64 V = 0.25;
        CHECK(Approx(Lerp(0.0, 10.0, V), 2.5));
        V = 2.0;
        CHECK(Approx(Fmod(5.5, V), 1.5));
        CHECK(Approx(ToRadian(180.0), Pi<F64>));
        CHECK(Approx(ToDegree(Pi<F64>), 180.0));
    }
}

TEST_CASE("Roxy::Math::TVec")
{
    SUBCASE("Construct::CT")
    {
        constexpr auto V0 = FVec3{};
        static_assert(V0[0] == 0.0f && V0[2] == 0.0f);

        constexpr auto V2 = FVec2{1.0f, 2.0f};
        static_assert(Approx(V2[0], 1.0f) && Approx(V2[1], 2.0f));

        constexpr auto V3 = FVec3{1.0f, 2.0f, 3.0f};
        static_assert(Approx(V3.X(), 1.0f) && Approx(V3.Y(), 2.0f) && Approx(V3.Z(), 3.0f));

        constexpr auto V4 = FVec4{1.0f, 2.0f, 3.0f, 4.0f};
        static_assert(Approx(V4.X(), 1.0f) && Approx(V4.W(), 4.0f));
    }

    SUBCASE("Factory::CT")
    {
        constexpr auto Zero = FVec3::Zero();
        static_assert(Zero[0] == 0.0f && Zero[1] == 0.0f && Zero[2] == 0.0f);

        constexpr auto One = FVec3::One();
        static_assert(Approx(One[0], 1.0f) && Approx(One[2], 1.0f));

        constexpr auto Axis = FVec3::AxisX();
        static_assert(Axis[0] == 1.0f && Axis[1] == 0.0f);
    }

    SUBCASE("Compare::CT")
    {
        constexpr auto A = FVec3{1.0f, 2.0f, 3.0f};
        constexpr auto B = FVec3{1.0f, 2.0f, 3.0f};
        constexpr auto C = FVec3{1.0f, 2.0f, 4.0f};
        static_assert(A == B);
        static_assert(A != C);
    }

    SUBCASE("Arith::CT")
    {
        constexpr auto A = FVec2{1.0f, 2.0f};
        constexpr auto B = FVec2{3.0f, 4.0f};

        constexpr auto Add = A + B;
        static_assert(Approx(Add[0], 4.0f) && Approx(Add[1], 6.0f));

        constexpr auto Sub = B - A;
        static_assert(Approx(Sub[0], 2.0f) && Approx(Sub[1], 2.0f));

        constexpr auto Mul = A * B;
        static_assert(Approx(Mul[0], 3.0f) && Approx(Mul[1], 8.0f));

        constexpr auto Div = B / A;
        static_assert(Approx(Div[0], 3.0f) && Approx(Div[1], 2.0f));

        constexpr auto Neg = -A;
        static_assert(Approx(Neg[0], -1.0f) && Approx(Neg[1], -2.0f));

        constexpr auto V  = FVec3{1.0f, 2.0f, 3.0f};
        constexpr auto VS = V + 10.0f;
        static_assert(Approx(VS[0], 11.0f) && Approx(VS[2], 13.0f));
        constexpr auto SV = 10.0f - V;
        static_assert(Approx(SV[0],  9.0f) && Approx(SV[2],  7.0f));
        constexpr auto MS = V * 2.0f;
        static_assert(Approx(MS[0],  2.0f) && Approx(MS[2],  6.0f));
        constexpr auto DS = V / 2.0f;
        static_assert(Approx(DS[0],  0.5f) && Approx(DS[2],  1.5f));
    }

    SUBCASE("Arith::RT")
    {
        for (volatile const auto X : { 1.5f, 2.5f })
        {
            const auto A = FVec2{X, 2.0f};
            const auto B = FVec2{3.0f, 4.0f};
            CHECK(Approx((A + B)[0], X + 3.0f));
            CHECK(Approx((A - B)[1], -2.0f));
            CHECK(Approx((A * B)[0], X * 3.0f));
            CHECK(Approx((A / B)[1], 0.5f));
            CHECK(Approx((-A)[0], -X));
        }
    }

    SUBCASE("Compound::RT")
    {
        volatile const auto W = 0.5f;
        auto V = FVec3{1.0f, 2.0f, 3.0f};
        auto U = FVec3{W, W, W};

        V += U;
        CHECK(Approx(V[0], 1.5f));
        V -= U;
        CHECK(Approx(V[0], 1.0f));
        V *= U;
        CHECK(Approx(V[0], 0.5f));
        V /= U;
        CHECK(Approx(V[0], 1.0f));
        V += 1.0f;
        CHECK(Approx(V[2], 4.0f));
        V -= 1.0f;
        V *= 2.0f;
        CHECK(Approx(V[2], 6.0f));
        V /= 2.0f;
        CHECK(Approx(V[2], 3.0f));
    }

    SUBCASE("Dot::CT")
    {
        constexpr auto A = FVec3{1.0f, 2.0f, 3.0f};
        constexpr auto B = FVec3{4.0f, 5.0f, 6.0f};
        static_assert(Approx(A.Dot(B), 32.0f));

        constexpr auto C = FVec2{1.5f, 2.5f};
        constexpr auto D = FVec2{3.0f, 4.0f};
        static_assert(Approx(C.Dot(D), 14.5f));
    }

    SUBCASE("Dot::RT")
    {
        for (volatile const auto X : { 1.0f, 2.0f })
        {
            const auto A = FVec4{X, 2.0f, 3.0f, 4.0f};
            const auto B = FVec4{5.0f, 6.0f, 7.0f, 8.0f};
            CHECK(Approx(A.Dot(B), X * 5.0f + 65.0f));
        }
    }

    SUBCASE("Cross::CT")
    {
        constexpr auto X = FVec3{1.0f, 0.0f, 0.0f};
        constexpr auto Y = FVec3{0.0f, 1.0f, 0.0f};
        constexpr auto Z = X.Cross(Y);
        static_assert(Approx(Z[0], 0.0f) && Approx(Z[1], 0.0f) && Approx(Z[2], 1.0f));
        static_assert(Approx(Y.Cross(X)[2], -1.0f));
    }

    SUBCASE("Cross::RT")
    {
        for (volatile const auto X : { 1.0f, 2.0f })
        {
            const auto A = FVec3{X, 2.0f, 3.0f};
            const auto B = FVec3{4.0f, 5.0f, 6.0f};
            const auto C = A.Cross(B);
            CHECK(Approx(C[0], 2.0f * 6.0f - 3.0f * 5.0f));
            CHECK(Approx(C[1], 3.0f * 4.0f - X * 6.0f));
            CHECK(Approx(C[2], X * 5.0f - 2.0f * 4.0f));
        }
    }

    SUBCASE("Length::CT")
    {
        constexpr auto V = FVec3{3.0f, 4.0f, 0.0f};
        static_assert(Approx(V.SqrLength(), 25.0f));
        static_assert(Approx(V.Length(), 5.0f));
        static_assert(Approx(V.InvSqrLength(), 1.0f / 25.0f));
        static_assert(Approx(V.InvLength(), 0.2f));

        constexpr auto N = V.Normalized();
        static_assert(Approx(N.Length(), 1.0f));
        static_assert(Approx(N[0], 0.6f) && Approx(N[1], 0.8f) && Approx(N[2], 0.0f));
    }

    SUBCASE("Length::RT")
    {
        for (volatile const auto X : { 1.0f, 2.0f })
        {
            const auto V = FVec2{X, 1.0f};
            CHECK(Approx(V.SqrLength(), X * X + 1.0f));
            CHECK(Approx(V.Length(), std::sqrt(X * X + 1.0f)));
            CHECK(Approx(V.InvSqrLength(), 1.0f / (X * X + 1.0f)));
            CHECK(Approx(V.InvLength(), 1.0f / std::sqrt(X * X + 1.0f)));
            auto N = V.Normalized();
            CHECK(Approx(N.Length(), 1.0f));
        }
    }

    SUBCASE("As::CT")
    {
        constexpr auto V = FVec3{1.0f, 2.0f, 3.0f};
        constexpr auto D = V.As<F64>();
        static_assert(std::is_same_v<decltype(D), const TVec<F64, 3>>);
        static_assert(Approx(D[0], 1.0) && Approx(D[1], 2.0) && Approx(D[2], 3.0));
    }

    SUBCASE("MinMax::CT")
    {
        constexpr auto V = FVec3{5.0f, 2.0f, 8.0f};
        static_assert(Approx(V.Min(), 2.0f));
        static_assert(Approx(V.Max(), 8.0f));

        constexpr auto W = FVec2{-1.5f, 3.5f};
        static_assert(Approx(W.Min(), -1.5f));
        static_assert(Approx(W.Max(), 3.5f));
    }
}

TEST_CASE("Roxy::Math::TMat")
{
    SUBCASE("Construct::CT")
    {
        constexpr auto M0 = FMat3{};
        static_assert(M0[0][0] == 0.0f && M0[2][2] == 0.0f);

        constexpr auto M2 = FMat2{1.0f, 2.0f, 3.0f, 4.0f};
        static_assert(Approx(M2[0][0], 1.0f) && Approx(M2[0][1], 2.0f));
        static_assert(Approx(M2[1][0], 3.0f) && Approx(M2[1][1], 4.0f));

        constexpr auto R0 = FVec2{1.0f, 2.0f};
        constexpr auto R1 = FVec2{3.0f, 4.0f};
        constexpr auto MR = FMat2{R0, R1};
        static_assert(MR[0] == R0 && MR[1] == R1);
    }

    SUBCASE("Factory::CT")
    {
        constexpr auto Zero = FMat2::Zero();
        static_assert(Zero[0][0] == 0.0f && Zero[1][1] == 0.0f);

        constexpr auto Ident = FMat2::Identity();
        static_assert(Ident[0][0] == 1.0f && Ident[0][1] == 0.0f);
        static_assert(Ident[1][0] == 0.0f && Ident[1][1] == 1.0f);
    }

    SUBCASE("Compare::CT")
    {
        constexpr auto A = FMat2{1.0f, 2.0f, 3.0f, 4.0f};
        constexpr auto B = FMat2{1.0f, 2.0f, 3.0f, 4.0f};
        constexpr auto C = FMat2{1.0f, 2.0f, 3.0f, 5.0f};
        static_assert(A == B);
        static_assert(A != C);
    }

    SUBCASE("RowCol::CT")
    {
        constexpr auto M = FMat2{1.0f, 2.0f, 3.0f, 4.0f};
        static_assert(Approx(M.Row(0)[0], 1.0f) && Approx(M.Row(1)[1], 4.0f));
        static_assert(Approx(M.Col(0)[1], 3.0f) && Approx(M.Col(1)[0], 2.0f));
    }

    SUBCASE("Arith::CT")
    {
        constexpr auto A = FMat2{1.0f, 2.0f, 3.0f, 4.0f};
        constexpr auto B = FMat2{5.0f, 6.0f, 7.0f, 8.0f};

        constexpr auto Add = A + B;
        static_assert(Approx(Add[0][0], 6.0f) && Approx(Add[1][1], 12.0f));

        constexpr auto Sub = B - A;
        static_assert(Approx(Sub[0][0], 4.0f) && Approx(Sub[1][1], 4.0f));

        constexpr auto Mul = A.Mul(B);
        static_assert(Approx(Mul[0][0], 19.0f) && Approx(Mul[0][1], 22.0f));
        static_assert(Approx(Mul[1][0], 43.0f) && Approx(Mul[1][1], 50.0f));

        constexpr auto Neg = -A;
        static_assert(Approx(Neg[0][0], -1.0f) && Approx(Neg[1][1], -4.0f));

        constexpr auto MS = A + 10.0f;
        static_assert(Approx(MS[0][0], 11.0f) && Approx(MS[1][1], 14.0f));

        constexpr auto SM = 10.0f - A;
        static_assert(Approx(SM[0][0],  9.0f) && Approx(SM[1][1],  6.0f));

        constexpr auto AS = A * 2.0f;
        static_assert(Approx(AS[0][0],  2.0f) && Approx(AS[1][1],  8.0f));

        constexpr auto AD = A / 2.0f;
        static_assert(Approx(AD[0][0],  0.5f) && Approx(AD[1][1],  2.0f));
    }

    SUBCASE("Arith::RT")
    {
        for (volatile const auto X : { 1.0f, 2.0f })
        {
            const auto A = FMat2{X, 2.0f, 3.0f, 4.0f};
            const auto B = FMat2{5.0f, 6.0f, 7.0f, 8.0f};

            CHECK(Approx((A + B)[0][0], X + 5.0f));
            CHECK(Approx((B - A)[1][1], 4.0f));
            CHECK(Approx(A.Mul(B)[0][0], X * 5.0f + 14.0f));
            CHECK(Approx((A * 2.0f)[1][1], 8.0f));
            CHECK(Approx((10.0f / A)[0][0], 10.0f / X));
        }
    }

    SUBCASE("MulVec::CT")
    {
        constexpr auto M = FMat2{1.0f, 2.0f, 3.0f, 4.0f};
        constexpr auto V = FVec2{5.0f, 6.0f};
        constexpr auto Res = M.Mul(V);
        static_assert(Approx(Res[0], 17.0f) && Approx(Res[1], 39.0f));
    }

    SUBCASE("Transpose::CT")
    {
        constexpr auto M  = FMat2{1.0f, 2.0f, 3.0f, 4.0f};
        constexpr auto T  = M.Transposed();
        static_assert(Approx(T[0][1], 3.0f) && Approx(T[1][0], 2.0f));

        constexpr auto M3 = FMat3{1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
        constexpr auto T3 = M3.Transposed();
        static_assert(Approx(T3[0][1], 4.0f) && Approx(T3[2][0], 3.0f));
    }

    SUBCASE("Transpose::RT")
    {
        for (volatile const auto X : { 1.0f, 2.0f })
        {
            auto M = FMat2{X, 2.0f, 3.0f, 4.0f};
            M.Transpose();
            CHECK(Approx(M[0][1], 3.0f));
            CHECK(Approx(M[1][0], 2.0f));
        }
    }

    SUBCASE("Determinant::CT")
    {
        constexpr auto M2 = FMat2{1.0f, 2.0f, 3.0f, 4.0f};
        static_assert(Approx(M2.Determinant(), -2.0f));
        static_assert(Approx(M2.InvDeterminant(), -0.5f));

        constexpr auto M3 = FMat3{6.0f, 1.0f, 1.0f, 4.0f, -2.0f, 5.0f, 2.0f, 8.0f, 7.0f};
        static_assert(Approx(M3.Determinant(), -306.0f));

        constexpr auto M4 = FMat4{1.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 2.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 3.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 4.0f};
        static_assert(Approx(M4.Determinant(), 24.0f));
        static_assert(Approx(M4.InvDeterminant(), 1.0f / 24.0f));
    }

    SUBCASE("Inverse::CT")
    {
        constexpr auto M2 = FMat2{4.0f, 7.0f, 2.0f, 6.0f};
        constexpr auto Inv = M2.Inversed();
        static_assert(Approx(Inv[0][0], 0.6f) && Approx(Inv[0][1], -0.7f));
        static_assert(Approx(Inv[1][0], -0.2f) && Approx(Inv[1][1], 0.4f));

        constexpr auto Id2 = M2.Mul(Inv);
        static_assert(Approx(Id2[0][0], 1.0f) && Approx(Id2[1][1], 1.0f));

        constexpr auto M3 = FMat3{1.0f, 2.0f, 3.0f, 0.0f, 1.0f, 4.0f, 5.0f, 6.0f, 0.0f};
        constexpr auto Id3 = M3.Mul(M3.Inversed());
        static_assert(Approx(Id3[0][0], 1.0f) && Approx(Id3[0][1], 0.0f) && Approx(Id3[2][2], 1.0f));

        constexpr auto M4 = FMat4{2.0f, 0.0f, 0.0f, 0.0f,
                                  0.0f, 4.0f, 0.0f, 0.0f,
                                  0.0f, 0.0f, 8.0f, 0.0f,
                                  0.0f, 0.0f, 0.0f, 16.0f};
        constexpr auto Id4 = M4.Mul(M4.Inversed());
        static_assert(Approx(Id4[0][0], 1.0f) && Approx(Id4[3][3], 1.0f));
    }

    SUBCASE("Inverse::RT")
    {
        for (volatile const auto X : { 1.0f, 2.0f })
        {
            auto M = FMat2{X, 2.0f, 3.0f, 4.0f};
            M.Inverse();
            CHECK(Approx(M[0][0],  4.0f / (4.0f * X - 6.0f)));
            CHECK(Approx(M[0][1], -2.0f / (4.0f * X - 6.0f)));
        }
    }
}

TEST_CASE("Roxy::Math::TQuat")
{
    SUBCASE("Construct::CT")
    {
        constexpr auto Q0 = FQuat();
        static_assert(Q0.X() == 0.0f && Q0.W() == 0.0f);

        constexpr auto Q1 = FQuat{1.0f, 2.0f, 3.0f, 4.0f};
        static_assert(Approx(Q1.X(), 1.0f) && Approx(Q1.W(), 4.0f));

        constexpr auto Q2 = FQuat{FVec3{1.0f, 2.0f, 3.0f}, 4.0f};
        static_assert(Approx(Q2.Y(), 2.0f) && Approx(Q2.W(), 4.0f));

        constexpr auto Ident = FQuat::Identity();
        static_assert(Ident.X() == 0.0f && Ident.W() == 1.0f);
    }

    SUBCASE("Compare::CT")
    {
        constexpr auto A = FQuat{1.0f, 2.0f, 3.0f, 4.0f};
        constexpr auto B = FQuat{1.0f, 2.0f, 3.0f, 4.0f};
        constexpr auto C = FQuat{1.0f, 2.0f, 3.0f, 5.0f};
        static_assert(A == B);
        static_assert(A != C);
    }

    SUBCASE("Arith::CT")
    {
        constexpr auto A = FQuat{1.0f, 2.0f, 3.0f, 4.0f};
        constexpr auto B = FQuat{5.0f, 6.0f, 7.0f, 8.0f};

        constexpr auto Sum = A + B;
        static_assert(Approx(Sum.X(), 6.0f) && Approx(Sum.W(), 12.0f));

        constexpr auto Diff = B - A;
        static_assert(Approx(Diff.X(), 4.0f) && Approx(Diff.W(), 4.0f));

        constexpr auto Prod = A * B;
        static_assert(Approx(Prod.X(), 24.0f) && Approx(Prod.Y(), 48.0f));
        static_assert(Approx(Prod.Z(), 48.0f) && Approx(Prod.W(), -6.0f));

        constexpr auto Div = A / B;
        constexpr auto Inv = B.Inversed();
        constexpr auto Expected = A * Inv;
        static_assert(Approx(Div.X(), Expected.X()) && Approx(Div.W(), Expected.W()));

        constexpr auto Neg = -A;
        static_assert(Approx(Neg.X(), -1.0f) && Approx(Neg.W(), -4.0f));
    }

    SUBCASE("Arith::RT")
    {
        volatile const auto X = 1.0f;
        auto Q = FQuat{X, 2.0f, 3.0f, 4.0f};
        auto R = FQuat{5.0f, 6.0f, 7.0f, 8.0f};

        Q += R;
        CHECK(Approx(Q.X(), X + 5.0f));
        CHECK(Approx(Q.W(), 12.0f));
        Q -= R;
        CHECK(Approx(Q.X(), X));
        CHECK(Approx(Q.W(), 4.0f));
    }

    SUBCASE("Length::CT")
    {
        constexpr auto Q = FQuat{1.0f, 2.0f, 3.0f, 4.0f};
        static_assert(Approx(Q.SqrLength(), 30.0f));
        static_assert(Approx(Q.Length(), Sqrt(30.0f)));

        constexpr auto Conj = Q.Conjugated();
        static_assert(Approx(Conj.X(), -1.0f) && Approx(Conj.W(), 4.0f));

        constexpr auto Inv = Q.Inversed();
        static_assert(Approx(Inv.X(), -1.0f / 30.0f) && Approx(Inv.W(), 4.0f / 30.0f));

        constexpr auto Norm = Q.Normalized();
        static_assert(Approx(Norm.Length(), 1.0f));
        static_assert(Approx(Norm.X(), 1.0f / Sqrt(30.0f)));

        constexpr auto Ident = FQuat::Identity();
        static_assert(Ident.Inversed() == Ident);
        static_assert(Ident.Conjugated() == Ident);
    }

    SUBCASE("Length::RT")
    {
        auto Q = FQuat{1.0f, 2.0f, 3.0f, 4.0f};

        Q.Conjugate();
        CHECK(Approx(Q.X(), -1.0f));
        CHECK(Approx(Q.W(), 4.0f));

        Q = FQuat{1.0f, 2.0f, 3.0f, 4.0f};
        Q.Normalize();
        CHECK(Approx(Q.Length(), 1.0f));

        Q = FQuat{1.0f, 2.0f, 3.0f, 4.0f};
        Q.Inverse();
        CHECK(Approx(Q.X(), -1.0f / 30.0f));
        CHECK(Approx(Q.W(), 4.0f / 30.0f));
    }

    SUBCASE("Mat::CT")
    {
        constexpr auto Ident = FQuat::Identity();
        constexpr auto M3 = Ident.Mat<3>();
        static_assert(Approx(M3[0][0], 1.0f) && Approx(M3[1][1], 1.0f) && Approx(M3[2][2], 1.0f));

        constexpr auto S  = Sqrt(2.0f) / 2.0f;
        constexpr auto Qz = FQuat{0.0f, 0.0f, S, S};   // 90° around Z
        constexpr auto Mz = Qz.Mat<3>();
        static_assert(Approx(Mz[0][0], 0.0f) && Approx(Mz[0][1], -1.0f));
        static_assert(Approx(Mz[1][0], 1.0f) && Approx(Mz[2][2], 1.0f));
    }

    SUBCASE("Rotate::CT")
    {
        constexpr auto S  = Sqrt(2.0f) / 2.0f;
        constexpr auto Qz = FQuat{0.0f, 0.0f, S, S};
        constexpr auto V  = FVec3{1.0f, 0.0f, 0.0f};
        constexpr auto Rotated = Qz.Rotate(V);
        static_assert(Approx(Rotated[0], 0.0f, 1e-5f) && Approx(Rotated[1], 1.0f, 1e-5f) && Approx(Rotated[2], 0.0f, 1e-5f));
    }

    SUBCASE("Rotate::RT")
    {
        for (volatile const auto X : { 1.0f, 2.0f })
        {
            const auto Qz = FQuat{0.0f, 0.0f, Sqrt(2.0f) / 2.0f, Sqrt(2.0f) / 2.0f};
            const auto V  = FVec3{X, 0.0f, 0.0f};
            const auto Rotated = Qz.Rotate(V);
            CHECK(Approx(Rotated[0], 0.0f, 1e-5f));
            CHECK(Approx(Rotated[1], X, 1e-5f));
            CHECK(Approx(Rotated[2], 0.0f, 1e-5f));
        }
    }

    SUBCASE("Interp::CT")
    {
        constexpr auto A = FQuat::Identity();
        constexpr auto S = Sqrt(2.0f) / 2.0f;
        constexpr auto B = FQuat{0.0f, 0.0f, S, S};

        static_assert(Approx(Lerp(A, B, 0.5f).Z(), S / 2.0f));
        static_assert(Approx(NLerp(A, B, 0.5f).Length(), 1.0f));

        constexpr auto Slerp = SLerp(A, B, 0.5f);   // 45° around Z
        static_assert(Approx(Slerp.Length(), 1.0f, 1e-5f));
        static_assert(Approx(Slerp.Z(), Sin(Pi<F32> / 8.0f), 1e-5f));
        static_assert(Approx(Slerp.W(), Cos(Pi<F32> / 8.0f), 1e-5f));
    }

    SUBCASE("Interp::RT")
    {
        volatile const auto T = 0.5f;
        const auto A = FQuat::Identity();
        const auto B = FQuat{0.0f, 0.0f, Sqrt(2.0f) / 2.0f, Sqrt(2.0f) / 2.0f};
        const auto Slerp = SLerp(A, B, T);
        CHECK(Approx(Slerp.Length(), 1.0f, 1e-5f));
        CHECK(Approx(Slerp.Z(), std::sin(Pi<F32> / 8.0f), 1e-5f));
    }

    SUBCASE("As::CT")
    {
        constexpr auto Q = FQuat{1.0f, 2.0f, 3.0f, 4.0f};
        constexpr auto D = Q.As<F64>();
        static_assert(std::is_same_v<decltype(D), const TQuat<F64>>);
        static_assert(Approx(D.X(), 1.0) && Approx(D.W(), 4.0));
    }
}

// ============================================================
// Performance benchmark (informational — no pass/fail criteria)
// ============================================================
TEST_CASE("Performance benchmark (informational)")
{
    constexpr int Iterations = 2'000'000;
    volatile F32 Sink = 0.0f;
    volatile F32 Seed = 0.123456789f;

    const F32 S = Seed;
    auto V3 = FVec3{S, 2.0f * S, 3.0f * S};
    auto W3 = FVec3{4.0f * S, 5.0f * S, 6.0f * S};
    auto V4 = FVec4{S, 2.0f * S, 3.0f * S, 4.0f * S};
    // Upper-triangular, invertible: det = S * 5S * 8S * 10S != 0
    auto M4 = FMat4{S, 2.0f * S, 3.0f * S, 4.0f * S,
                    0.0f, 5.0f * S, 6.0f * S, 7.0f * S,
                    0.0f, 0.0f, 8.0f * S, 9.0f * S,
                    0.0f, 0.0f, 0.0f, 10.0f * S};
    auto Q  = FQuat{0.0f, 0.0f, S, 1.0f}.Normalized();
    auto Q2 = FQuat{0.0f, S, 0.0f, 1.0f}.Normalized();

    // Each Fn takes a per-iteration varying Tweak injected into its operand:
    // the loop-carried dependency (Tweak -> Sink -> Tweak) forces the work to
    // genuinely run every iteration — nothing can be folded or hoisted.
    auto Bench = [&](const char* Name, auto&& Fn)
    {
        F32 Tweak = Seed;
        Roxy::Chrono::FTimer Timer;
        for (int I = 0; I < Iterations; ++I)
        {
            Sink += Fn(Tweak);
            Tweak = Sink * 1e-7f;
        }
        const auto Ms = Timer.Elapsed<Roxy::Chrono::ETimeUnit::MiS>();
        Roxy::Log::Info(Roxy::Log::ELogCategory::Default, "Bench {:<16s} {:9.3f} ms  ({:7.2f} ns/op)", Name, Ms, Ms * 1e6 / Iterations);
    };

    Bench("Vec3 Add",         [&](F32 X) { return (V3 + W3 * X)[0]; });
    Bench("Vec3 Dot",         [&](F32 X) { return V3.Dot(W3 * X); });
    Bench("Vec3 Cross",       [&](F32 X) { return V3.Cross(W3 * X)[0]; });
    Bench("Vec3 Normalized",  [&](F32 X) { return (V3 * X).Normalized()[0]; });
    Bench("Mat4 Mul",         [&](F32 X) { return M4.Mul(M4 * X)[0][0]; });
    Bench("Mat4 MulVec",      [&](F32 X) { return M4.Mul(V4 * X)[0]; });
    Bench("Mat4 Transposed",  [&](F32 X) { return (M4 * X).Transposed()[0][0]; });
    Bench("Mat4 Determinant", [&](F32 X) { return (M4 * X).Determinant(); });
    Bench("Mat4 Inversed",    [&](F32 X) { return (M4 * X).Inversed()[0][0]; });
    Bench("Quat Mul",         [&](F32 X) { return (Q * FQuat{Q2.Vec() * X}).W(); });
    Bench("Quat Rotate",      [&](F32 X) { return Q.Rotate(V3 * X)[0]; });
    Bench("Quat Normalized",  [&](F32 X) { return FQuat{Q.Vec() * X}.Normalized().W(); });
    Bench("Quat SLerp",       [&](F32 X) { return SLerp(Q, FQuat{Q2.Vec() * X}, 0.5f).W(); });

    CHECK(Sink != 0.0f);  // keep the sink alive (anti-optimization)
}
