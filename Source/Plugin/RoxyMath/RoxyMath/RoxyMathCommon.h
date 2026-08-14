#pragma once

#include <RoxySTD/RoxySTD.h>

namespace Roxy::Math // Concept
{
template <typename T>
concept CIntegral = std::is_integral_v<T>;

template <typename T>
concept CFloatingPoint = std::is_floating_point_v<T>;

template <typename T>
concept CArithmetic = CIntegral<T> || CFloatingPoint<T>;
}

namespace Roxy::Math // Constant
{
template<CFloatingPoint T>
inline constexpr T Eps  = std::numeric_limits<T>::epsilon();

template<CFloatingPoint T>
inline constexpr T Pi = std::numbers::pi_v<T>;

template<CFloatingPoint T>
inline constexpr T E = std::numbers::e_v<T>;

template<CFloatingPoint T>
inline constexpr T Ln2 = std::numbers::ln2_v<T>;

template<CFloatingPoint T>
inline constexpr T Ln10 = std::numbers::ln10_v<T>;

template<CFloatingPoint T>
inline constexpr T Log2E = std::numbers::log2e_v<T>;

template<CFloatingPoint T>
inline constexpr T Log10E = std::numbers::log10e_v<T>;

template<CFloatingPoint T>
inline constexpr T Sqrt2 = std::numbers::sqrt2_v<T>;

template<CFloatingPoint T>
inline constexpr T Sqrt3 = std::numbers::sqrt3_v<T>;

template<CFloatingPoint T>
inline constexpr T Sqrt5 = T(2.23606797749978969640917366873127623544061835961152);

template<CFloatingPoint T>
inline constexpr T SqrtPi = T(1) / std::numbers::inv_sqrtpi_v<T>;

template<CFloatingPoint T>
inline constexpr T InvPi = T(1) / std::numbers::pi_v<T>;

template<CFloatingPoint T>
inline constexpr T InvE = T(1) / std::numbers::e_v<T>;

template<CFloatingPoint T>
inline constexpr T InvLn2 = T(1) / std::numbers::ln2_v<T>;

template<CFloatingPoint T>
inline constexpr T InvLn10 = T(1) / std::numbers::ln10_v<T>;

template<CFloatingPoint T>
inline constexpr T InvLog2E = T(1) / std::numbers::log2e_v<T>;

template<CFloatingPoint T>
inline constexpr T InvLog10E = T(1) / std::numbers::log10e_v<T>;

template<CFloatingPoint T>
inline constexpr T InvSqrt2 = T(1) / std::numbers::sqrt2_v<T>;

template<CFloatingPoint T>
inline constexpr T InvSqrt3 = T(1) / std::numbers::sqrt3_v<T>;

template<CFloatingPoint T>
inline constexpr T InvSqrt5 = T(1) / T(2.23606797749978969640917366873127623544061835961152);

template<CFloatingPoint T>
inline constexpr T InvSqrtPi = std::numbers::inv_sqrtpi_v<T>;

template<CFloatingPoint T>
inline constexpr T RadToDegCoeff = T(180) / Pi<T>;

template<CFloatingPoint T>
inline constexpr T DegToRadCoeff = Pi<T> / T(180);
}

namespace Roxy::Math::Detail
{

template<CArithmetic T>
ROXY_NODISCARD consteval T Abs(T X) noexcept
{
    return X < T(0) ? -X : X;
}

template<typename T, T Coeff, T... Coeffs>
ROXY_NODISCARD consteval T Poly(T X) noexcept
{
    if constexpr (sizeof...(Coeffs) == 0)
    {
        return Coeff;
    }
    else
    {
        return Coeff + X * Poly<T, Coeffs...>(X);
    }
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Sqrt(T X) noexcept
{
    ROXY_ASSERT_MSG(X >= T(0), "Sqrt: No Math Definition");

    if (X == T(0)) { return T(0); }

    T Curr = X;
    T Prev = T(0);
    for (FIndex I = 0; I < 128; ++I)
    {
        Prev = Curr;
        Curr = T(0.5) * (Curr + X / Curr);
        if (Abs(Curr - Prev) < Eps<T> * Abs(Curr))
        {
            break;
        }
    }
    return Curr;
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Sin(T X) noexcept
{
    T TwoPi = T(2) * Pi<T>;
    T Q = (X + Pi<T>) / TwoPi;
    long long N = static_cast<long long>(Q);
    N -= static_cast<T>(N) > Q;
    T Y = X - N * TwoPi;

    T X2 = Y * Y;
    return Y * Poly<T,
        T( 1),
        T(-1) / T(6),
        T( 1) / T(120),
        T(-1) / T(5040),
        T( 1) / T(362880),
        T(-1) / T(39916800),
        T( 1) / T(6227020800),
        T(-1) / T(1307674368000),
        T( 1) / T(355687428096000),
        T(-1) / T(121645100408832000)
    >(X2);
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Cos(T X) noexcept
{
    return Sin(T(0.5) * Pi<T> - X);
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Tan(T X) noexcept
{
    T CosX = Cos(X);
    ROXY_ASSERT_MSG(Abs(CosX) > Eps<T>, "Tan: No Math Definition");
    return Sin(X) / CosX;
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Atan(T X) noexcept
{
    if (X <  T(0)) { return -Atan(-X); }
    if (X == T(1)) { return T(0.25) * Pi<T>; }
    if (X >  T(1)) { return T(0.5) * Pi<T> - Atan(T(1) / X); }

    T X2 = X * X;
    return X * Poly<T,
        T( 1),
        T(-1) / T( 3),
        T( 1) / T( 5),
        T(-1) / T( 7),
        T( 1) / T( 9),
        T(-1) / T(11),
        T( 1) / T(13),
        T(-1) / T(15)
    >(X2);
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Atan2(T Y, T X) noexcept
{
    if (X >  T(0)) { return Atan(Y / X); }
    if (X <  T(0) && Y >= T(0)) { return Atan(Y / X) + Pi<T>; }
    if (X <  T(0) && Y <  T(0)) { return Atan(Y / X) - Pi<T>; }
    if (X == T(0) && Y >  T(0)) { return T( 0.5) * Pi<T>; }
    if (X == T(0) && Y <  T(0)) { return T(-0.5) * Pi<T>; }
    return T(0);
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Asin(T X) noexcept
{
    ROXY_ASSERT_MSG(-1 <= X && X <= 1, "Asin: No Math Definition");
    if (X <= T(-1)) { return T(-0.5) * Pi<T>; }
    if (X >= T( 1)) { return T( 0.5) * Pi<T>; }
    return Atan2(X, Sqrt(T(1) - X * X));
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Acos(T X) noexcept
{
    return T(0.5) * Pi<T> - Asin(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Exp(T X) noexcept;

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Log(T X) noexcept
{
    ROXY_ASSERT_MSG(X > T(0), "Log: No Math Definition");

    if (X == T(1)) { return T(0); }

    // Reduce to [1, 2): X = 2^Exp2 * Y
    int Exp2 = 0;
    T Y = X;
    while (Y >= T(2)) { Y /= T(2); ++Exp2; }
    while (Y <  T(1)) { Y *= T(2); --Exp2; }

    // Initial guess via Pade approximant
    T Guess = (Y - T(1)) / (Y + T(1));
    Guess = Guess * (T(2) + Guess * (T(2) / T(3)));
    Guess = Guess + Exp2 * Ln2<T>;

    // Newton's method: Result_{n+1} = Result_n + (X - e^Result_n) / e^Result_n
    T Result = Guess;
    for (int I = 0; I < 128; ++I)
    {
        T ExpY = Exp(Result);
        T Delta = (X - ExpY) / ExpY;
        Result = Result + Delta;
        if (Abs(Delta) < Eps<T> * Abs(Result))
        {
            break;
        }
    }
    return Result;
}

template<CFloatingPoint T, CIntegral U>
ROXY_NODISCARD consteval T Pow(T Base, U Exponent) noexcept
{
    ROXY_ASSERT_MSG(!(Base == T(0) && Exponent <= 0), "Pow: No Math Definition");

    if (Exponent == 0) { return T(1); }

    bool bNegExp = Exponent < 0;
    std::make_unsigned_t<U> N = bNegExp ? -Exponent : Exponent;

    T Result = T(1);
    while (N > 0)
    {
        if (N & 1u)
        {
            Result *= Base;
        }
        Base *= Base;
        N >>= 1u;
    }
    return bNegExp ? T(1) / Result : Result;
}

template<CFloatingPoint T, CFloatingPoint U>
ROXY_NODISCARD consteval auto Pow(T Base, U Exponent) noexcept -> std::common_type_t<T, U>
{
    using R = std::common_type_t<T, U>;
    R B = static_cast<R>(Base);
    R E = static_cast<R>(Exponent);

    if (B == R(0))
    {
        ROXY_ASSERT_MSG(E > R(0), "Pow: No Math Definition");
        return R(0);
    }
    else
    {
        ROXY_ASSERT_MSG(B > R(0), "Pow: No Math Definition");
        return Exp(E * Log(B));
    }
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Exp(T X) noexcept
{
    if (X == T(0)) { return T(1); }

    // Exp(X) = 2^Exp2 * Exp(Exp1)
    T N = X * InvLn2<T>;
    long long Exp2 = static_cast<long long>(N + (N >= T(0) ? T(0.5) : T(-0.5)));
    T Exp1 = X - Exp2 * Ln2<T>;

    return Pow(T(2), Exp2) * (T(1) + Exp1 * Poly<T,
        T(1),
        T(1) / T(2),
        T(1) / T(6),
        T(1) / T(24),
        T(1) / T(120),
        T(1) / T(720),
        T(1) / T(5040),
        T(1) / T(40320),
        T(1) / T(362880),
        T(1) / T(3628800),
        T(1) / T(39916800),
        T(1) / T(479001600)
    >(Exp1));
}

template<CArithmetic T>
ROXY_NODISCARD consteval T Min(T X, T Y) noexcept
{
    return X < Y ? X : Y;
}

template<CArithmetic T>
ROXY_NODISCARD consteval T Max(T X, T Y) noexcept
{
    return X > Y ? X : Y;
}

template<CArithmetic T>
ROXY_NODISCARD consteval T Clamp(T X, T Lo, T Hi) noexcept
{
    if (X < Lo) { return Lo; }
    if (X > Hi) { return Hi; }
    return X;
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Lerp(T X, T Y, T Alpha) noexcept
{
    return (T(1) - Alpha) * X + Alpha * Y;
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Fmod(T X, T Y) noexcept
{
    // Use integer truncation toward zero, matching std::fmod behavior.
    // X and Y are floating-point, we cast the quotient to integral type.
    const long long Quot = static_cast<long long>(X / Y);
    return X - Quot * Y;
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Floor(T X) noexcept
{
    const T IntPart = static_cast<T>(static_cast<long long>(X));
    if (X < T(0) && X != IntPart)
    {
        return IntPart - T(1);
    }
    return IntPart;
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Ceil(T X) noexcept
{
    const T IntPart = static_cast<T>(static_cast<long long>(X));
    if (X > T(0) && X != IntPart)
    {
        return IntPart + T(1);
    }
    return IntPart;
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Round(T X) noexcept
{
    const T IntPart = static_cast<T>(static_cast<long long>(X));
    const T FracPart = X - IntPart;
    if (FracPart >= T(0.5))
    {
        return IntPart + T(1);
    }
    else if (FracPart <= T(-0.5))
    {
        return IntPart - T(1);
    }
    return IntPart;
}

template<CFloatingPoint T>
ROXY_NODISCARD consteval T Trunc(T X) noexcept
{
    return static_cast<T>(static_cast<long long>(X));
}

}

namespace Roxy::Math
{

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Sqrt(T X) noexcept
{
    if consteval { return Detail::Sqrt(X); }
    return std::sqrt(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T InvSqrt(T X) noexcept
{
    if consteval { return static_cast<T>(1) / Detail::Sqrt(X); }
    return static_cast<T>(1) / std::sqrt(X);
}

template<CArithmetic T>
ROXY_NODISCARD ROXY_INLINE constexpr T Abs(T X) noexcept
{
    if consteval { return Detail::Abs(X); }
    return std::abs(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Sin(T X) noexcept
{
    if consteval { return Detail::Sin(X); }
    return std::sin(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Cos(T X) noexcept
{
    if consteval { return Detail::Cos(X); }
    return std::cos(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Tan(T X) noexcept
{
    if consteval { return Detail::Tan(X); }
    return std::tan(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Asin(T X) noexcept
{
    if consteval { return Detail::Asin(X); }
    return std::asin(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Acos(T X) noexcept
{
    if consteval { return Detail::Acos(X); }
    return std::acos(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Atan(T X) noexcept
{
    if consteval { return Detail::Atan(X); }
    return std::atan(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Atan2(T Y, T X) noexcept
{
    if consteval { return Detail::Atan2(Y, X); }
    return std::atan2(Y, X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Sinh(T X) noexcept
{
    if consteval { return (Detail::Exp(X) - Detail::Exp(-X)) / T(2); }
    return std::sinh(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Cosh(T X) noexcept
{
    if consteval { return (Detail::Exp(X) + Detail::Exp(-X)) / T(2); }
    return std::cosh(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Tanh(T X) noexcept
{
    if consteval
    {
        T E2X = Detail::Exp(T(2) * X);
        return (E2X - T(1)) / (E2X + T(1));
    }
    return std::tanh(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Exp(T X) noexcept
{
    if consteval { return Detail::Exp(X); }
    return std::exp(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Log(T X) noexcept
{
    if consteval { return Detail::Log(X); }
    return std::log(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Log2(T X) noexcept
{
    if consteval { return Detail::Log(X) / Detail::Log(T(2)); }
    return std::log2(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Log10(T X) noexcept
{
    if consteval { return Detail::Log(X) / Detail::Log(T(10)); }
    return std::log10(X);
}

template<CFloatingPoint T, CIntegral U>
ROXY_NODISCARD ROXY_INLINE constexpr T Pow(T Base, U Exponent) noexcept
{
    if consteval { return Detail::Pow(Base, Exponent); }
    return std::pow(Base, Exponent);
}

template<CFloatingPoint T, CFloatingPoint U>
ROXY_NODISCARD ROXY_INLINE constexpr auto Pow(T Base, U Exponent) noexcept -> std::common_type_t<T, U>
{
    if consteval { return Detail::Pow(Base, Exponent); }
    return std::pow(Base, Exponent);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Floor(T X) noexcept
{
    if consteval { return Detail::Floor(X); }
    return std::floor(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Ceil(T X) noexcept
{
    if consteval { return Detail::Ceil(X); }
    return std::ceil(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Round(T X) noexcept
{
    if consteval { return Detail::Round(X); }
    return std::round(X);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Trunc(T X) noexcept
{
    if consteval { return Detail::Trunc(X); }
    return std::trunc(X);
}

template<CArithmetic T>
ROXY_NODISCARD ROXY_INLINE constexpr T Min(T X, T Y) noexcept
{
    if consteval { return Detail::Min(X, Y); }
    return std::min(X, Y);
}

template<CArithmetic T>
ROXY_NODISCARD ROXY_INLINE constexpr T Max(T X, T Y) noexcept
{
    if consteval { return Detail::Max(X, Y); }
    return std::max(X, Y);
}

template<CArithmetic T>
ROXY_NODISCARD ROXY_INLINE constexpr T Clamp(T X, T Lo, T Hi) noexcept
{
    if consteval { return Detail::Clamp(X, Lo, Hi); }
    return std::clamp(X, Lo, Hi);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Lerp(T X, T Y, T Alpha) noexcept
{
    if consteval { return Detail::Lerp(X, Y, Alpha); }
    return std::lerp(X, Y, Alpha);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T Fmod(T X, T Y) noexcept
{
    if consteval { return Detail::Fmod(X, Y); }
    return std::fmod(X, Y);
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T ToRadian(T Degrees) noexcept
{
    return Degrees * DegToRadCoeff<T>;
}

template<CFloatingPoint T>
ROXY_NODISCARD ROXY_INLINE constexpr T ToDegree(T Radians) noexcept
{
    return Radians * RadToDegCoeff<T>;
}

}
