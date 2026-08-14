#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyMath/RoxyMath.h>

#include <array>

namespace
{
constexpr double PiValue = Roxy::Math::Pi<double>;
constexpr double EValue  = Roxy::Math::E<double>;

template<typename T>
constexpr bool AlmostEqual(T A, T B, T Epsilon = T(1e-9))
{
    return Roxy::Math::Abs(A - B) <= Epsilon;
}
} // namespace

// ============================================================
// Concepts and constants
// ============================================================
TEST_CASE("Math concepts")
{
    static_assert(Roxy::Math::CIntegral<int>);
    static_assert(Roxy::Math::CFloatingPoint<double>);
    static_assert(Roxy::Math::CArithmetic<float>);
    static_assert(!Roxy::Math::CIntegral<float>);
    static_assert(Roxy::Math::CArithmetic<int>);
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

// ============================================================
// Abs
// ============================================================
TEST_CASE("Abs")
{
    static_assert(Roxy::Math::Abs(-5) == 5);
    static_assert(Roxy::Math::Abs(5) == 5);
    static_assert(Roxy::Math::Abs(-3.14) == 3.14);
    static_assert(Roxy::Math::Abs(3.14) == 3.14);

    CHECK(Roxy::Math::Abs(-5) == 5);
    CHECK(Roxy::Math::Abs(5) == 5);
    CHECK(Roxy::Math::Abs(-3.14) == doctest::Approx(3.14));
    CHECK(Roxy::Math::Abs(3.14) == doctest::Approx(3.14));
}

// ============================================================
// Sqrt / InvSqrt
// ============================================================
TEST_CASE("Sqrt and InvSqrt")
{
    static_assert(Roxy::Math::Sqrt(0.0) == 0.0);
    static_assert(Roxy::Math::Sqrt(1.0) == 1.0);
    static_assert(Roxy::Math::Sqrt(4.0) == 2.0);
    static_assert(Roxy::Math::Sqrt(10000.0) == 100.0);
    static_assert(Roxy::Math::InvSqrt(4.0) == 0.5);

    constexpr double SqrtInputs[] = {0.0, 1.0, 2.0, 3.0, 4.0, 9.0, 100.0};
    constexpr auto SqrtResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Sqrt(SqrtInputs[Is])... };
    }(std::make_index_sequence<std::size(SqrtInputs)>{});

    for (std::size_t i = 0; i < std::size(SqrtInputs); ++i) {
        CHECK(SqrtResults[i] == doctest::Approx(std::sqrt(SqrtInputs[i])));
    }

    volatile double x = 0.0;
    CHECK(Roxy::Math::Sqrt(x) == doctest::Approx(0.0));
    x = 2.0;
    CHECK(Roxy::Math::Sqrt(x) == doctest::Approx(std::sqrt(2.0)));
    x = 0.25;
    CHECK(Roxy::Math::Sqrt(x) == doctest::Approx(0.5));
    x = 1e6;
    CHECK(Roxy::Math::Sqrt(x) == doctest::Approx(1000.0));

    CHECK(Roxy::Math::InvSqrt(4.0) == doctest::Approx(0.5));
    CHECK(Roxy::Math::InvSqrt(2.0) == doctest::Approx(1.0 / std::sqrt(2.0)));
}

// ============================================================
// Trigonometric functions (Sin, Cos, Tan)
// ============================================================
TEST_CASE("Trigonometric functions")
{
    static_assert(Roxy::Math::Sin(0.0) == 0.0);
    static_assert(Roxy::Math::Tan(0.0) == 0.0);
    static_assert(AlmostEqual(Roxy::Math::Cos(0.0), 1.0));

    static_assert(AlmostEqual(Roxy::Math::Sin(PiValue / 2), 1.0));
    static_assert(AlmostEqual(Roxy::Math::Sin(PiValue), 0.0));
    static_assert(AlmostEqual(Roxy::Math::Sin(-PiValue / 2), -1.0));
    static_assert(AlmostEqual(Roxy::Math::Cos(PiValue / 2), 0.0));
    static_assert(AlmostEqual(Roxy::Math::Cos(PiValue), -1.0));
    static_assert(AlmostEqual(Roxy::Math::Tan(PiValue / 4), 1.0));

    constexpr double TrigInputs[] = {-10.0, -1.0, 0.0, 0.5, 1.0, 10.0};
    constexpr auto SinResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Sin(TrigInputs[Is])... };
    }(std::make_index_sequence<std::size(TrigInputs)>{});
    constexpr auto CosResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Cos(TrigInputs[Is])... };
    }(std::make_index_sequence<std::size(TrigInputs)>{});
    constexpr auto TanResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Tan(TrigInputs[Is])... };
    }(std::make_index_sequence<std::size(TrigInputs)>{});

    for (std::size_t i = 0; i < std::size(TrigInputs); ++i) {
        CHECK(SinResults[i] == doctest::Approx(std::sin(TrigInputs[i])));
        CHECK(CosResults[i] == doctest::Approx(std::cos(TrigInputs[i])));
        CHECK(TanResults[i] == doctest::Approx(std::tan(TrigInputs[i])));
    }

    volatile double x = 0.5;
    CHECK(Roxy::Math::Sin(x) == doctest::Approx(std::sin(x)));
    CHECK(Roxy::Math::Cos(x) == doctest::Approx(std::cos(x)));
    CHECK(Roxy::Math::Tan(x) == doctest::Approx(std::tan(x)));
    x = 1.0;
    CHECK(Roxy::Math::Sin(x) == doctest::Approx(std::sin(x)));
    x = -0.5;
    CHECK(Roxy::Math::Sin(x) == doctest::Approx(std::sin(x)));
}

// ============================================================
// Inverse trigonometric functions (Asin, Acos, Atan, Atan2)
// ============================================================
TEST_CASE("Inverse trigonometric functions")
{
    static_assert(Roxy::Math::Asin(0.0) == 0.0);
    static_assert(Roxy::Math::Asin(1.0) == PiValue / 2);
    static_assert(Roxy::Math::Asin(-1.0) == -PiValue / 2);

    static_assert(Roxy::Math::Acos(1.0) == 0.0);
    static_assert(Roxy::Math::Acos(0.0) == PiValue / 2);
    static_assert(Roxy::Math::Acos(-1.0) == PiValue);

    static_assert(Roxy::Math::Atan(0.0) == 0.0);
    static_assert(Roxy::Math::Atan(1.0) == PiValue / 4);
    static_assert(Roxy::Math::Atan(-1.0) == -PiValue / 4);

    static_assert(Roxy::Math::Atan2(0.0, 1.0) == 0.0);
    static_assert(Roxy::Math::Atan2(1.0, 0.0) == PiValue / 2);
    static_assert(Roxy::Math::Atan2(-1.0, 0.0) == -PiValue / 2);

    constexpr double InvTrigInputs[] = {-1.0, -0.5, 0.0, 0.5, 1.0};
    constexpr auto AsinResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Asin(InvTrigInputs[Is])... };
    }(std::make_index_sequence<std::size(InvTrigInputs)>{});
    constexpr auto AcosResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Acos(InvTrigInputs[Is])... };
    }(std::make_index_sequence<std::size(InvTrigInputs)>{});
    constexpr double AtanInputs[] = {-10.0, -1.0, -0.5, 0.0, 0.5, 1.0, 10.0};
    constexpr auto AtanResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Atan(AtanInputs[Is])... };
    }(std::make_index_sequence<std::size(AtanInputs)>{});

    for (std::size_t i = 0; i < std::size(InvTrigInputs); ++i) {
        CHECK(AsinResults[i] == doctest::Approx(std::asin(InvTrigInputs[i])));
        CHECK(AcosResults[i] == doctest::Approx(std::acos(InvTrigInputs[i])));
    }
    for (std::size_t i = 0; i < std::size(AtanInputs); ++i) {
        CHECK(AtanResults[i] == doctest::Approx(std::atan(AtanInputs[i])));
    }

    volatile double y = 1.0;
    volatile double x = 0.0;
    CHECK(Roxy::Math::Atan2(y, x) == doctest::Approx(std::atan2(y, x)));
    y = 1.0;
    x = 1.0;
    CHECK(Roxy::Math::Atan2(y, x) == doctest::Approx(std::atan2(y, x)));
    y = -1.0;
    x = 1.0;
    CHECK(Roxy::Math::Atan2(y, x) == doctest::Approx(std::atan2(y, x)));
    y = 1.0;
    x = -1.0;
    CHECK(Roxy::Math::Atan2(y, x) == doctest::Approx(std::atan2(y, x)));
    y = -1.0;
    x = -1.0;
    CHECK(Roxy::Math::Atan2(y, x) == doctest::Approx(std::atan2(y, x)));

    volatile double v = 0.5;
    CHECK(Roxy::Math::Asin(v) == doctest::Approx(std::asin(v)));
    CHECK(Roxy::Math::Acos(v) == doctest::Approx(std::acos(v)));
    CHECK(Roxy::Math::Atan(v) == doctest::Approx(std::atan(v)));
}

// ============================================================
// Hyperbolic functions (Sinh, Cosh, Tanh)
// ============================================================
TEST_CASE("Hyperbolic functions")
{
    static_assert(Roxy::Math::Sinh(0.0) == 0.0);
    static_assert(Roxy::Math::Cosh(0.0) == 1.0);
    static_assert(Roxy::Math::Tanh(0.0) == 0.0);

    constexpr double HypInputs[] = {-2.0, -0.5, 0.0, 0.5, 2.0};
    constexpr auto SinhResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Sinh(HypInputs[Is])... };
    }(std::make_index_sequence<std::size(HypInputs)>{});
    constexpr auto CoshResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Cosh(HypInputs[Is])... };
    }(std::make_index_sequence<std::size(HypInputs)>{});
    constexpr auto TanhResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Tanh(HypInputs[Is])... };
    }(std::make_index_sequence<std::size(HypInputs)>{});

    for (std::size_t i = 0; i < std::size(HypInputs); ++i) {
        CHECK(SinhResults[i] == doctest::Approx(std::sinh(HypInputs[i])));
        CHECK(CoshResults[i] == doctest::Approx(std::cosh(HypInputs[i])));
        CHECK(TanhResults[i] == doctest::Approx(std::tanh(HypInputs[i])));
    }

    volatile double x = 0.5;
    CHECK(Roxy::Math::Sinh(x) == doctest::Approx(std::sinh(x)));
    CHECK(Roxy::Math::Cosh(x) == doctest::Approx(std::cosh(x)));
    CHECK(Roxy::Math::Tanh(x) == doctest::Approx(std::tanh(x)));
    x = -0.5;
    CHECK(Roxy::Math::Sinh(x) == doctest::Approx(std::sinh(x)));
    x = 2.0;
    CHECK(Roxy::Math::Sinh(x) == doctest::Approx(std::sinh(x)));
}

// ============================================================
// Exp and Log (including Log2, Log10)
// ============================================================
TEST_CASE("Exp and Log")
{
    static_assert(Roxy::Math::Exp(0.0) == 1.0);
    static_assert(AlmostEqual(Roxy::Math::Exp(1.0), EValue));
    static_assert(Roxy::Math::Log(1.0) == 0.0);
    static_assert(AlmostEqual(Roxy::Math::Log(EValue), 1.0));
    static_assert(Roxy::Math::Log2(8.0) == 3.0);
    static_assert(Roxy::Math::Log10(1000.0) == 3.0);

    constexpr double ExpInputs[] = {-2.0, -1.0, 0.0, 0.5, 1.0, 2.0};
    constexpr auto ExpResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Exp(ExpInputs[Is])... };
    }(std::make_index_sequence<std::size(ExpInputs)>{});
    for (std::size_t i = 0; i < std::size(ExpInputs); ++i) {
        CHECK(ExpResults[i] == doctest::Approx(std::exp(ExpInputs[i])));
    }

    constexpr double LogInputs[] = {0.5, 1.0, 2.0, EValue, 10.0};
    constexpr auto LogResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Log(LogInputs[Is])... };
    }(std::make_index_sequence<std::size(LogInputs)>{});
    for (std::size_t i = 0; i < std::size(LogInputs); ++i) {
        CHECK(LogResults[i] == doctest::Approx(std::log(LogInputs[i])));
    }

    volatile double x = 1.0;
    CHECK(Roxy::Math::Exp(x) == doctest::Approx(std::exp(x)));
    x = 2.0;
    CHECK(Roxy::Math::Exp(x) == doctest::Approx(std::exp(x)));
    x = 0.5;
    CHECK(Roxy::Math::Exp(x) == doctest::Approx(std::exp(x)));

    x = 2.0;
    CHECK(Roxy::Math::Log(x) == doctest::Approx(std::log(x)));
    CHECK(Roxy::Math::Log2(x) == doctest::Approx(std::log2(x)));
    CHECK(Roxy::Math::Log10(x) == doctest::Approx(std::log10(x)));
    x = 10.0;
    CHECK(Roxy::Math::Log(x) == doctest::Approx(std::log(x)));
    CHECK(Roxy::Math::Log2(x) == doctest::Approx(std::log2(x)));
    CHECK(Roxy::Math::Log10(x) == doctest::Approx(std::log10(x)));
}

// ============================================================
// Pow (integer and floating point exponents)
// ============================================================
TEST_CASE("Pow")
{
    static_assert(Roxy::Math::Pow(2.0, 0) == 1.0);
    static_assert(Roxy::Math::Pow(2.0, 3) == 8.0);
    static_assert(Roxy::Math::Pow(2.0, -1) == 0.5);
    static_assert(Roxy::Math::Pow(3.0, 2) == 9.0);

    static_assert(AlmostEqual(Roxy::Math::Pow(4.0, 0.5), 2.0));
    static_assert(AlmostEqual(Roxy::Math::Pow(2.0, 0.5), Roxy::Math::Sqrt2<double>));

    constexpr double BaseInt = 3.0;
    constexpr int IntExponents[] = {-2, -1, 0, 1, 2, 3};
    constexpr auto PowIntResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Pow(BaseInt, IntExponents[Is])... };
    }(std::make_index_sequence<std::size(IntExponents)>{});
    for (std::size_t i = 0; i < std::size(IntExponents); ++i) {
        CHECK(PowIntResults[i] == doctest::Approx(std::pow(BaseInt, static_cast<double>(IntExponents[i]))));
    }

    constexpr double BaseFloat = 4.0;
    constexpr double FloatExponents[] = {-1.0, -0.5, 0.0, 0.5, 1.0, 2.0};
    constexpr auto PowFloatResults = [&]<std::size_t... Is>(std::index_sequence<Is...>) constexpr {
        return std::array<double, sizeof...(Is)>{ Roxy::Math::Pow(BaseFloat, FloatExponents[Is])... };
    }(std::make_index_sequence<std::size(FloatExponents)>{});
    for (std::size_t i = 0; i < std::size(FloatExponents); ++i) {
        CHECK(PowFloatResults[i] == doctest::Approx(std::pow(BaseFloat, FloatExponents[i])));
    }

    volatile double b = 2.0;
    volatile int ei = 3;
    CHECK(Roxy::Math::Pow(b, ei) == doctest::Approx(8.0));
    volatile double ef = 0.5;
    CHECK(Roxy::Math::Pow(b, ef) == doctest::Approx(std::sqrt(2.0)));

    CHECK(Roxy::Math::Pow(2.0, 3) == doctest::Approx(8.0));
    CHECK(Roxy::Math::Pow(2.0, -1) == doctest::Approx(0.5));
    CHECK(Roxy::Math::Pow(3.0, 2.0) == doctest::Approx(9.0));
}

// ============================================================
// Utility functions (Min, Max, Clamp, Lerp, Fmod, Floor, Ceil, Round, Trunc, ToRadian, ToDegree)
// ============================================================
TEST_CASE("Utility functions")
{
    static_assert(Roxy::Math::Min(3, 5) == 3);
    static_assert(Roxy::Math::Max(3, 5) == 5);
    static_assert(Roxy::Math::Clamp(7, 0, 10) == 7);
    static_assert(Roxy::Math::Clamp(-1, 0, 10) == 0);
    static_assert(Roxy::Math::Clamp(15, 0, 10) == 10);

    static_assert(Roxy::Math::Lerp(0.0, 10.0, 0.25) == 2.5);
    static_assert(Roxy::Math::Fmod(5.5, 2.0) == 1.5);
    static_assert(Roxy::Math::Floor(3.7) == 3.0);
    static_assert(Roxy::Math::Ceil(3.2) == 4.0);
    static_assert(Roxy::Math::Round(3.5) == 4.0);
    static_assert(Roxy::Math::Trunc(-3.7) == -3.0);

    static_assert(Roxy::Math::ToRadian(180.0) == PiValue);
    static_assert(Roxy::Math::ToDegree(PiValue) == 180.0);

    CHECK(Roxy::Math::Min(3, 5) == 3);
    CHECK(Roxy::Math::Max(3, 5) == 5);
    CHECK(Roxy::Math::Clamp(7, 0, 10) == 7);
    CHECK(Roxy::Math::Clamp(-1, 0, 10) == 0);
    CHECK(Roxy::Math::Clamp(15, 0, 10) == 10);

    CHECK(Roxy::Math::Lerp(0.0, 10.0, 0.25) == doctest::Approx(2.5));
    CHECK(Roxy::Math::Fmod(5.5, 2.0) == doctest::Approx(1.5));

    CHECK(Roxy::Math::Floor(3.7) == 3.0);
    CHECK(Roxy::Math::Ceil(3.2) == 4.0);
    CHECK(Roxy::Math::Round(3.5) == 4.0);
    CHECK(Roxy::Math::Trunc(-3.7) == -3.0);

    CHECK(Roxy::Math::ToRadian(180.0) == doctest::Approx(PiValue));
    CHECK(Roxy::Math::ToDegree(PiValue) == doctest::Approx(180.0));
}
