#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyMath/RoxyMath.h>

namespace
{
constexpr double PiValue = Roxy::Math::Pi<double>;
constexpr double EValue = Roxy::Math::E<double>;
}

TEST_CASE("Math concepts")
{
    static_assert(Roxy::Math::CIntegral<int>);
    static_assert(Roxy::Math::CFloatingPoint<double>);
    static_assert(Roxy::Math::CArithmetic<float>);
    static_assert(!Roxy::Math::CIntegral<float>);
}

TEST_CASE("Math constants")
{
    using namespace Roxy::Math;

    static_assert(Pi<double> > 3.141592 && Pi<double> < 3.141593);
    static_assert(E<double> > 2.71828 && E<double> < 2.71829);

    CHECK(Pi<double> == doctest::Approx(3.14159265358979323846));
    CHECK(E<double> == doctest::Approx(2.71828182845904523536));
    CHECK(Ln2<double> == doctest::Approx(std::log(2.0)));
    CHECK(Ln10<double> == doctest::Approx(std::log(10.0)));
    CHECK(Log2E<double> == doctest::Approx(std::log2(std::exp(1.0))));
    CHECK(Log10E<double> == doctest::Approx(std::log10(std::exp(1.0))));
    CHECK(Sqrt2<double> == doctest::Approx(std::sqrt(2.0)));
    CHECK(Sqrt3<double> == doctest::Approx(std::sqrt(3.0)));
    CHECK(InvSqrt2<double> == doctest::Approx(1.0 / std::sqrt(2.0)));
    CHECK(DegToRadCoeff<double> == doctest::Approx(Pi<double> / 180.0));
    CHECK(RadToDegCoeff<double> == doctest::Approx(180.0 / Pi<double>));
}

TEST_CASE("Abs")
{
    CHECK(Roxy::Math::Abs(-5) == 5);
    CHECK(Roxy::Math::Abs(5) == 5);
    CHECK(Roxy::Math::Abs(-3.14) == doctest::Approx(3.14));
    CHECK(Roxy::Math::Abs(3.14) == doctest::Approx(3.14));
}

TEST_CASE("Sqrt and InvSqrt")
{
    CHECK(Roxy::Math::Sqrt(0.0) == 0.0);
    CHECK(Roxy::Math::Sqrt(1.0) == 1.0);
    CHECK(Roxy::Math::Sqrt(4.0) == 2.0);
    CHECK(Roxy::Math::Sqrt(2.0) == doctest::Approx(std::sqrt(2.0)));
    CHECK(Roxy::Math::Sqrt(10000.0) == doctest::Approx(100.0));

    constexpr double Sqrt4 = Roxy::Math::Sqrt(4.0);
    CHECK(Sqrt4 == doctest::Approx(2.0));

    CHECK(Roxy::Math::InvSqrt(4.0) == doctest::Approx(0.5));
    CHECK(Roxy::Math::InvSqrt(2.0) == doctest::Approx(1.0 / std::sqrt(2.0)));
}

TEST_CASE("Trigonometric functions")
{
    for (constexpr double Angles[] = {-10.0, -1.0, 0.0, 0.5, 1.0, 10.0}; const auto& X : Angles)
    {
        CHECK(Roxy::Math::Sin(X) == doctest::Approx(std::sin(X)));
        CHECK(Roxy::Math::Cos(X) == doctest::Approx(std::cos(X)));
        CHECK(Roxy::Math::Tan(X) == doctest::Approx(std::tan(X)));
    }
}

TEST_CASE("Inverse trigonometric functions")
{
    for (constexpr double Values[] = {-1.0, -0.5, 0.0, 0.5, 1.0}; const auto& X : Values)
    {
        CHECK(Roxy::Math::Asin(X) == doctest::Approx(std::asin(X)));
        CHECK(Roxy::Math::Acos(X) == doctest::Approx(std::acos(X)));
    }

    for (constexpr double Values[] = {-10.0, -1.0, -0.5, 0.0, 0.5, 1.0, 10.0}; const auto& X : Values)
    {
        CHECK(Roxy::Math::Atan(X) == doctest::Approx(std::atan(X)));
    }

    CHECK(Roxy::Math::Atan2(1.0, 0.0) == doctest::Approx(std::atan2(1.0, 0.0)));
    CHECK(Roxy::Math::Atan2(1.0, 1.0) == doctest::Approx(std::atan2(1.0, 1.0)));
    CHECK(Roxy::Math::Atan2(-1.0, 1.0) == doctest::Approx(std::atan2(-1.0, 1.0)));
    CHECK(Roxy::Math::Atan2(1.0, -1.0) == doctest::Approx(std::atan2(1.0, -1.0)));
    CHECK(Roxy::Math::Atan2(-1.0, -1.0) == doctest::Approx(std::atan2(-1.0, -1.0)));
}

TEST_CASE("Hyperbolic functions")
{
    for (constexpr double Values[] = {-2.0, -0.5, 0.0, 0.5, 2.0}; const auto& X : Values)
    {
        CHECK(Roxy::Math::Sinh(X) == doctest::Approx(std::sinh(X)));
        CHECK(Roxy::Math::Cosh(X) == doctest::Approx(std::cosh(X)));
        CHECK(Roxy::Math::Tanh(X) == doctest::Approx(std::tanh(X)));
    }
}

TEST_CASE("Exp and Log")
{
    CHECK(Roxy::Math::Exp(0.0) == 1.0);
    CHECK(Roxy::Math::Exp(1.0) == doctest::Approx(std::exp(1.0)));

    CHECK(Roxy::Math::Log(1.0) == 0.0);
    CHECK(Roxy::Math::Log(EValue) == doctest::Approx(1.0));
    CHECK(Roxy::Math::Log(10.0) == doctest::Approx(std::log(10.0)));

    CHECK(Roxy::Math::Log2(8.0) == doctest::Approx(3.0));
    CHECK(Roxy::Math::Log10(1000.0) == doctest::Approx(3.0));
}

TEST_CASE("Pow")
{
    constexpr auto Pow8 = Roxy::Math::Pow(2., 3.);
    CHECK(Pow8 == 8);

    CHECK(Roxy::Math::Pow(2., 3.) == 8);
    CHECK(Roxy::Math::Pow(2.0, 3) == doctest::Approx(8.0));
    CHECK(Roxy::Math::Pow(2.0, 0.5) == doctest::Approx(std::sqrt(2.0)));
    CHECK(Roxy::Math::Pow(2.0, -1) == doctest::Approx(0.5));
    CHECK(Roxy::Math::Pow(3.0, 2.0) == doctest::Approx(9.0));
}

TEST_CASE("Utility functions")
{
    CHECK(Roxy::Math::Min(3, 5) == 3);
    CHECK(Roxy::Math::Max(3, 5) == 5);
    CHECK(Roxy::Math::Clamp(7, 0, 10) == 7);
    CHECK(Roxy::Math::Clamp(-1, 0, 10) == 0);

    CHECK(Roxy::Math::Lerp(0.0, 10.0, 0.25) == doctest::Approx(2.5));
    CHECK(Roxy::Math::Fmod(5.5, 2.0) == doctest::Approx(1.5));

    CHECK(Roxy::Math::Floor(3.7) == 3.0);
    CHECK(Roxy::Math::Ceil(3.2) == 4.0);
    CHECK(Roxy::Math::Round(3.5) == 4.0);
    CHECK(Roxy::Math::Trunc(-3.7) == -3.0);

    CHECK(Roxy::Math::ToRadian(180.0) == doctest::Approx(PiValue));
    CHECK(Roxy::Math::ToDegree(PiValue) == doctest::Approx(180.0));
}
