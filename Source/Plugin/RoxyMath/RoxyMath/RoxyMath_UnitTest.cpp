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

// ============================================================
// TVec tests
// ============================================================

TEST_CASE("TVec construction and indexing")
{
    using namespace Roxy::Math;

    // Default constructor -> zero vector
    constexpr TVec<float, 3> v_default;
    static_assert(v_default[0] == 0.0f && v_default[1] == 0.0f && v_default[2] == 0.0f);

    // initializer_list constructor
    constexpr TVec<int, 2> v2{1, 2};
    static_assert(v2[0] == 1 && v2[1] == 2);

    constexpr TVec<float, 4> v4{1.0f, 2.0f, 3.0f, 4.0f};
    static_assert(v4[0] == 1.0f && v4[1] == 2.0f && v4[2] == 3.0f && v4[3] == 4.0f);

    // Accessors X, Y, Z, W
    TVec<double, 3> v{1.5, 2.5, 3.5};
    CHECK(v.X() == doctest::Approx(1.5));
    CHECK(v.Y() == doctest::Approx(2.5));
    CHECK(v.Z() == doctest::Approx(3.5));

    TVec<double, 2> v2d{4.0, 5.0};
    CHECK(v2d.X() == doctest::Approx(4.0));
    CHECK(v2d.Y() == doctest::Approx(5.0));

    TVec<double, 4> v4d{1.0, 2.0, 3.0, 4.0};
    CHECK(v4d.X() == doctest::Approx(1.0));
    CHECK(v4d.Y() == doctest::Approx(2.0));
    CHECK(v4d.Z() == doctest::Approx(3.0));
    CHECK(v4d.W() == doctest::Approx(4.0));
}

TEST_CASE("TVec static factory functions")
{
    using namespace Roxy::Math;

    constexpr TVec<float, 3> zero = TVec<float, 3>::Zero();
    static_assert(zero[0] == 0.0f && zero[1] == 0.0f && zero[2] == 0.0f);

    constexpr TVec<int, 2> one = TVec<int, 2>::One();
    static_assert(one[0] == 1 && one[1] == 1);

    constexpr TVec<float, 4> axis_x = TVec<float, 4>::AxisX();
    static_assert(axis_x[0] == 1.0f && axis_x[1] == 0.0f && axis_x[2] == 0.0f && axis_x[3] == 0.0f);

    constexpr TVec<float, 3> axis_y = TVec<float, 3>::AxisY();
    static_assert(axis_y[0] == 0.0f && axis_y[1] == 1.0f && axis_y[2] == 0.0f);

    constexpr TVec<float, 2> axis_z_2d = TVec<float, 2>::Axis(1); // Y axis
    static_assert(axis_z_2d[0] == 0.0f && axis_z_2d[1] == 1.0f);
}

TEST_CASE("TVec comparison operators")
{
    using namespace Roxy::Math;

    constexpr TVec<int, 3> a{1, 2, 3};
    constexpr TVec<int, 3> b{1, 2, 3};
    constexpr TVec<int, 3> c{1, 2, 4};

    static_assert(a == b);
    static_assert(a != c);
    static_assert(!(a == c));
}

TEST_CASE("TVec arithmetic operators (vector-vector)")
{
    using namespace Roxy::Math;

    constexpr TVec<int, 2> v1{1, 2};
    constexpr TVec<int, 2> v2{3, 4};

    constexpr auto add = v1 + v2;
    static_assert(add[0] == 4 && add[1] == 6);

    constexpr auto sub = v2 - v1;
    static_assert(sub[0] == 2 && sub[1] == 2);

    constexpr auto mul = v1 * v2;
    static_assert(mul[0] == 3 && mul[1] == 8);

    constexpr auto div = v2 / v1;
    static_assert(div[0] == 3 && div[1] == 2);

    // Unary minus
    constexpr auto neg = -v1;
    static_assert(neg[0] == -1 && neg[1] == -2);
}

TEST_CASE("TVec arithmetic operators (vector-scalar and scalar-vector)")
{
    using namespace Roxy::Math;

    constexpr TVec<int, 3> v{1, 2, 3};

    constexpr auto v_plus_s = v + 10;
    static_assert(v_plus_s[0] == 11 && v_plus_s[1] == 12 && v_plus_s[2] == 13);

    constexpr auto s_plus_v = 10 + v;
    static_assert(s_plus_v[0] == 11 && s_plus_v[1] == 12 && s_plus_v[2] == 13);

    constexpr auto v_minus_s = v - 1;
    static_assert(v_minus_s[0] == 0 && v_minus_s[1] == 1 && v_minus_s[2] == 2);

    constexpr auto s_minus_v = 5 - v;
    static_assert(s_minus_v[0] == 4 && s_minus_v[1] == 3 && s_minus_v[2] == 2);

    constexpr auto v_mul_s = v * 2;
    static_assert(v_mul_s[0] == 2 && v_mul_s[1] == 4 && v_mul_s[2] == 6);

    constexpr auto s_mul_v = 2 * v;
    static_assert(s_mul_v[0] == 2 && s_mul_v[1] == 4 && s_mul_v[2] == 6);

    constexpr auto v_div_s = v / 2;
    static_assert(v_div_s[0] == 0 && v_div_s[1] == 1 && v_div_s[2] == 1); // integer division

    constexpr auto s_div_v = 6 / v;
    static_assert(s_div_v[0] == 6 && s_div_v[1] == 3 && s_div_v[2] == 2);
}

TEST_CASE("TVec compound assignment operators")
{
    using namespace Roxy::Math;

    TVec<double, 3> v{1.0, 2.0, 3.0};
    TVec<double, 3> w{0.5, 0.5, 0.5};

    v += w;
    CHECK(v[0] == doctest::Approx(1.5));
    CHECK(v[1] == doctest::Approx(2.5));
    CHECK(v[2] == doctest::Approx(3.5));

    v -= w;
    CHECK(v[0] == doctest::Approx(1.0));
    CHECK(v[1] == doctest::Approx(2.0));
    CHECK(v[2] == doctest::Approx(3.0));

    v *= w;
    CHECK(v[0] == doctest::Approx(0.5));
    CHECK(v[1] == doctest::Approx(1.0));
    CHECK(v[2] == doctest::Approx(1.5));

    v /= w;
    CHECK(v[0] == doctest::Approx(1.0));
    CHECK(v[1] == doctest::Approx(2.0));
    CHECK(v[2] == doctest::Approx(3.0));

    v += 1.0;
    CHECK(v[0] == doctest::Approx(2.0));
    CHECK(v[1] == doctest::Approx(3.0));
    CHECK(v[2] == doctest::Approx(4.0));

    v -= 1.0;
    CHECK(v[0] == doctest::Approx(1.0));
    CHECK(v[1] == doctest::Approx(2.0));
    CHECK(v[2] == doctest::Approx(3.0));

    v *= 2.0;
    CHECK(v[0] == doctest::Approx(2.0));
    CHECK(v[1] == doctest::Approx(4.0));
    CHECK(v[2] == doctest::Approx(6.0));

    v /= 2.0;
    CHECK(v[0] == doctest::Approx(1.0));
    CHECK(v[1] == doctest::Approx(2.0));
    CHECK(v[2] == doctest::Approx(3.0));
}

TEST_CASE("TVec Dot product")
{
    using namespace Roxy::Math;

    constexpr TVec<int, 3> a{1, 2, 3};
    constexpr TVec<int, 3> b{4, 5, 6};
    static_assert(Dot(a, b) == 32);

    constexpr TVec<double, 2> c{1.5, 2.5};
    constexpr TVec<double, 2> d{3.0, 4.0};
    static_assert(AlmostEqual(Dot(c, d), 14.5));

    TVec<float, 4> e{1.0f, 2.0f, 3.0f, 4.0f};
    TVec<float, 4> f{5.0f, 6.0f, 7.0f, 8.0f};
    CHECK(Dot(e, f) == doctest::Approx(70.0f));
}

TEST_CASE("TVec Cross product (3D only)")
{
    using namespace Roxy::Math;

    constexpr TVec<int, 3> x{1, 0, 0};
    constexpr TVec<int, 3> y{0, 1, 0};
    constexpr auto z = Cross(x, y);
    static_assert(z[0] == 0 && z[1] == 0 && z[2] == 1);

    constexpr auto z2 = Cross(y, x);
    static_assert(z2[0] == 0 && z2[1] == 0 && z2[2] == -1);

    // Member version
    TVec<double, 3> a{2.0, 3.0, 4.0};
    TVec<double, 3> b{5.0, 6.0, 7.0};
    auto res = a.Cross(b);
    CHECK(res[0] == doctest::Approx(-3.0));
    CHECK(res[1] == doctest::Approx(6.0));
    CHECK(res[2] == doctest::Approx(-3.0));
}

TEST_CASE("TVec length and squared length")
{
    using namespace Roxy::Math;

    constexpr TVec<float, 3> v{3.0f, 4.0f, 0.0f};
    static_assert(AlmostEqual(v.SqrLen(), 25.0f));
    static_assert(AlmostEqual(v.Len(), 5.0f));

    TVec<double, 2> w{1.0, 1.0};
    CHECK(w.SqrLen() == doctest::Approx(2.0));
    CHECK(w.Len() == doctest::Approx(std::sqrt(2.0)));
}

TEST_CASE("TVec As<U> conversion")
{
    using namespace Roxy::Math;

    constexpr TVec<int, 3> vi{1, 2, 3};
    constexpr auto vf = vi.template As<float>();
    static_assert(std::is_same_v<decltype(vf), const TVec<float, 3>>);
    static_assert(AlmostEqual(vf[0], 1.0f));
    static_assert(AlmostEqual(vf[1], 2.0f));
    static_assert(AlmostEqual(vf[2], 3.0f));
}

TEST_CASE("TVec Min and Max")
{
    using namespace Roxy::Math;

    constexpr TVec<int, 3> v{5, 2, 8};
    static_assert(v.Min() == 2);
    static_assert(v.Max() == 8);

    constexpr TVec<double, 2> w{-1.5, 3.5};
    static_assert(AlmostEqual(w.Min(), -1.5));
    static_assert(AlmostEqual(w.Max(), 3.5));
}

// ============================================================
// TMat tests
// ============================================================

TEST_CASE("TMat construction and indexing")
{
    using namespace Roxy::Math;

    // Default constructor -> zero matrix
    constexpr TMat<float, 3> m_default;
    static_assert(m_default[0][0] == 0.0f && m_default[0][1] == 0.0f && m_default[0][2] == 0.0f);
    static_assert(m_default[1][0] == 0.0f && m_default[1][1] == 0.0f && m_default[1][2] == 0.0f);
    static_assert(m_default[2][0] == 0.0f && m_default[2][1] == 0.0f && m_default[2][2] == 0.0f);

    // Scalar constructor -> identity * scalar
    constexpr TMat<int, 2> m_ident(1);
    static_assert(m_ident[0][0] == 1 && m_ident[0][1] == 0);
    static_assert(m_ident[1][0] == 0 && m_ident[1][1] == 1);

    // initializer_list<T> constructor (row-major)
    constexpr TMat<int, 2> m2{1, 2, 3, 4};
    static_assert(m2[0][0] == 1 && m2[0][1] == 2);
    static_assert(m2[1][0] == 3 && m2[1][1] == 4);

    constexpr TMat<float, 3> m3{1.0f, 2.0f, 3.0f,
                                4.0f, 5.0f, 6.0f,
                                7.0f, 8.0f, 9.0f};
    static_assert(AlmostEqual(m3[0][0], 1.0f) && AlmostEqual(m3[0][1], 2.0f) && AlmostEqual(m3[0][2], 3.0f));
    static_assert(AlmostEqual(m3[1][0], 4.0f) && AlmostEqual(m3[1][1], 5.0f) && AlmostEqual(m3[1][2], 6.0f));
    static_assert(AlmostEqual(m3[2][0], 7.0f) && AlmostEqual(m3[2][1], 8.0f) && AlmostEqual(m3[2][2], 9.0f));

    // initializer_list<TVec<T,Dim>> constructor (rows as vectors)
    constexpr TVec<int, 2> row0{1, 2};
    constexpr TVec<int, 2> row1{3, 4};
    constexpr TMat<int, 2> m_rows{row0, row1};
    static_assert(m_rows[0] == row0 && m_rows[1] == row1);
}

TEST_CASE("TMat static Zero and Identity")
{
    using namespace Roxy::Math;

    constexpr auto zero = TMat<float, 3>::Zero();
    static_assert(zero[0][0] == 0.0f && zero[0][1] == 0.0f && zero[0][2] == 0.0f);
    static_assert(zero[1][0] == 0.0f && zero[1][1] == 0.0f && zero[1][2] == 0.0f);
    static_assert(zero[2][0] == 0.0f && zero[2][1] == 0.0f && zero[2][2] == 0.0f);

    constexpr auto ident = TMat<float, 3>::Identity();
    static_assert(ident[0][0] == 1.0f && ident[0][1] == 0.0f && ident[0][2] == 0.0f);
    static_assert(ident[1][0] == 0.0f && ident[1][1] == 1.0f && ident[1][2] == 0.0f);
    static_assert(ident[2][0] == 0.0f && ident[2][1] == 0.0f && ident[2][2] == 1.0f);
}

TEST_CASE("TMat comparison operators")
{
    using namespace Roxy::Math;

    constexpr TMat<int, 2> a{1, 2, 3, 4};
    constexpr TMat<int, 2> b{1, 2, 3, 4};
    constexpr TMat<int, 2> c{1, 2, 3, 5};

    static_assert(a == b);
    static_assert(a != c);
    static_assert(!(a == c));
}

TEST_CASE("TMat Row and Col access")
{
    using namespace Roxy::Math;

    constexpr TMat<int, 2> m{1, 2, 3, 4};
    constexpr auto row0 = m.Row(0);
    constexpr auto row1 = m.Row(1);
    static_assert(row0[0] == 1 && row0[1] == 2);
    static_assert(row1[0] == 3 && row1[1] == 4);

    constexpr auto col0 = m.Col(0);
    constexpr auto col1 = m.Col(1);
    static_assert(col0[0] == 1 && col0[1] == 3);
    static_assert(col1[0] == 2 && col1[1] == 4);
}

TEST_CASE("TMat arithmetic operators (matrix-matrix)")
{
    using namespace Roxy::Math;

    constexpr TMat<int, 2> a{1, 2, 3, 4};
    constexpr TMat<int, 2> b{5, 6, 7, 8};

    constexpr auto add = a + b;
    static_assert(add[0][0] == 6 && add[0][1] == 8);
    static_assert(add[1][0] == 10 && add[1][1] == 12);

    constexpr auto sub = b - a;
    static_assert(sub[0][0] == 4 && sub[0][1] == 4);
    static_assert(sub[1][0] == 4 && sub[1][1] == 4);

    // Matrix multiplication (requires corrected Dot in implementation)
    // Assuming fix: R[Row][Col] = Dot(Lhs[Row], Rhs.Col(Col));
    constexpr auto mul = a * b;
    static_assert(mul[0][0] == 19 && mul[0][1] == 22);
    static_assert(mul[1][0] == 43 && mul[1][1] == 50);

    // Unary minus
    constexpr auto neg = -a;
    static_assert(neg[0][0] == -1 && neg[0][1] == -2);
    static_assert(neg[1][0] == -3 && neg[1][1] == -4);
}

TEST_CASE("TMat arithmetic operators (matrix-scalar and scalar-matrix)")
{
    using namespace Roxy::Math;

    constexpr TMat<int, 2> m{1, 2, 3, 4};

    constexpr auto m_plus_s = m + 10;
    static_assert(m_plus_s[0][0] == 11 && m_plus_s[0][1] == 12);
    static_assert(m_plus_s[1][0] == 13 && m_plus_s[1][1] == 14);

    constexpr auto s_plus_m = 10 + m;
    static_assert(s_plus_m[0][0] == 11 && s_plus_m[0][1] == 12);
    static_assert(s_plus_m[1][0] == 13 && s_plus_m[1][1] == 14);

    constexpr auto m_minus_s = m - 1;
    static_assert(m_minus_s[0][0] == 0 && m_minus_s[0][1] == 1);
    static_assert(m_minus_s[1][0] == 2 && m_minus_s[1][1] == 3);

    constexpr auto s_minus_m = 5 - m;
    static_assert(s_minus_m[0][0] == 4 && s_minus_m[0][1] == 3);
    static_assert(s_minus_m[1][0] == 2 && s_minus_m[1][1] == 1);

    constexpr auto m_mul_s = m * 2;
    static_assert(m_mul_s[0][0] == 2 && m_mul_s[0][1] == 4);
    static_assert(m_mul_s[1][0] == 6 && m_mul_s[1][1] == 8);

    constexpr auto s_mul_m = 2 * m;
    static_assert(s_mul_m[0][0] == 2 && s_mul_m[0][1] == 4);
    static_assert(s_mul_m[1][0] == 6 && s_mul_m[1][1] == 8);

    constexpr auto m_div_s = m / 2;
    static_assert(m_div_s[0][0] == 0 && m_div_s[0][1] == 1);
    static_assert(m_div_s[1][0] == 1 && m_div_s[1][1] == 2);

    constexpr auto s_div_m = 10 / m;
    static_assert(s_div_m[0][0] == 10 && s_div_m[0][1] == 5);
    static_assert(s_div_m[1][0] == 3 && s_div_m[1][1] == 2); // integer division truncates
}

TEST_CASE("TMat vector multiplication")
{
    using namespace Roxy::Math;

    constexpr TMat<int, 2> m{1, 2, 3, 4};
    constexpr TVec<int, 2> v{5, 6};

    constexpr auto res = m * v;
    static_assert(res[0] == 17 && res[1] == 39);
}

TEST_CASE("TMat transpose")
{
    using namespace Roxy::Math;

    constexpr TMat<int, 2> m{1, 2, 3, 4};
    constexpr auto t = m.Transpose();
    static_assert(t[0][0] == 1 && t[0][1] == 3);
    static_assert(t[1][0] == 2 && t[1][1] == 4);

    constexpr TMat<float, 3> m3{1.0f, 2.0f, 3.0f,
                                4.0f, 5.0f, 6.0f,
                                7.0f, 8.0f, 9.0f};
    constexpr auto t3 = m3.Transpose();
    static_assert(AlmostEqual(t3[0][0], 1.0f) && AlmostEqual(t3[0][1], 4.0f) && AlmostEqual(t3[0][2], 7.0f));
    static_assert(AlmostEqual(t3[1][0], 2.0f) && AlmostEqual(t3[1][1], 5.0f) && AlmostEqual(t3[1][2], 8.0f));
    static_assert(AlmostEqual(t3[2][0], 3.0f) && AlmostEqual(t3[2][1], 6.0f) && AlmostEqual(t3[2][2], 9.0f));
}

TEST_CASE("TMat determinant")
{
    using namespace Roxy::Math;

    constexpr TMat<float, 2> m2{1.0f, 2.0f, 3.0f, 4.0f};
    static_assert(AlmostEqual(m2.Determinant(), -2.0f));

    constexpr TMat<float, 3> m3{6.0f, 1.0f, 1.0f,
                                4.0f, -2.0f, 5.0f,
                                2.0f, 8.0f, 7.0f};
    static_assert(AlmostEqual(m3.Determinant(), -306.0f));

    // 4x4 determinant test (use a known value)
    constexpr TMat<double, 4> m4{1.0, 0.0, 0.0, 0.0,
                                 0.0, 2.0, 0.0, 0.0,
                                 0.0, 0.0, 3.0, 0.0,
                                 0.0, 0.0, 0.0, 4.0};
    static_assert(AlmostEqual(m4.Determinant(), 24.0));
}

TEST_CASE("TMat inverse (floating point only)")
{
    using namespace Roxy::Math;

    // 2x2 inverse
    constexpr TMat<double, 2> m2{4.0, 7.0, 2.0, 6.0};
    constexpr auto inv2 = m2.Inverse();
    static_assert(AlmostEqual(inv2[0][0], 0.6));
    static_assert(AlmostEqual(inv2[0][1], -0.7));
    static_assert(AlmostEqual(inv2[1][0], -0.2));
    static_assert(AlmostEqual(inv2[1][1], 0.4));

    // Verify inverse by multiplying with original (should be identity)
    constexpr auto ident2 = m2 * inv2;
    static_assert(AlmostEqual(ident2[0][0], 1.0));
    static_assert(AlmostEqual(ident2[0][1], 0.0));
    static_assert(AlmostEqual(ident2[1][0], 0.0));
    static_assert(AlmostEqual(ident2[1][1], 1.0));

    // 3x3 inverse
    constexpr TMat<double, 3> m3{1.0, 2.0, 3.0,
                                 0.0, 1.0, 4.0,
                                 5.0, 6.0, 0.0};
    constexpr auto inv3 = m3.Inverse();
    constexpr auto ident3 = m3 * inv3;
    static_assert(AlmostEqual(ident3[0][0], 1.0) && AlmostEqual(ident3[0][1], 0.0) && AlmostEqual(ident3[0][2], 0.0));
    static_assert(AlmostEqual(ident3[1][0], 0.0) && AlmostEqual(ident3[1][1], 1.0) && AlmostEqual(ident3[1][2], 0.0));
    static_assert(AlmostEqual(ident3[2][0], 0.0) && AlmostEqual(ident3[2][1], 0.0) && AlmostEqual(ident3[2][2], 1.0));

    // 4x4 inverse (diagonal matrix)
    constexpr TMat<double, 4> m4{2.0, 0.0, 0.0, 0.0,
                                 0.0, 4.0, 0.0, 0.0,
                                 0.0, 0.0, 8.0, 0.0,
                                 0.0, 0.0, 0.0, 16.0};
    constexpr auto inv4 = m4.Inverse();
    constexpr auto ident4 = m4 * inv4;
    static_assert(AlmostEqual(ident4[0][0], 1.0) && AlmostEqual(ident4[0][1], 0.0) && AlmostEqual(ident4[0][2], 0.0) && AlmostEqual(ident4[0][3], 0.0));
    static_assert(AlmostEqual(ident4[1][0], 0.0) && AlmostEqual(ident4[1][1], 1.0) && AlmostEqual(ident4[1][2], 0.0) && AlmostEqual(ident4[1][3], 0.0));
    static_assert(AlmostEqual(ident4[2][0], 0.0) && AlmostEqual(ident4[2][1], 0.0) && AlmostEqual(ident4[2][2], 1.0) && AlmostEqual(ident4[2][3], 0.0));
    static_assert(AlmostEqual(ident4[3][0], 0.0) && AlmostEqual(ident4[3][1], 0.0) && AlmostEqual(ident4[3][2], 0.0) && AlmostEqual(ident4[3][3], 1.0));
}
