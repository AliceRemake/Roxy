#pragma once

#include <RoxyMath/RoxyMathCommon.h>
#include <RoxyMath/RoxyMathVec.h>
#include <RoxyMath/RoxyMathMat.h>

#ifdef ROXY_ENABLE_SIMD
#include <RoxyMath/SIMD/RoxyMathVecSIMD.h>
#include <RoxyMath/SIMD/RoxyMathMatSIMD.h>
#endif


//
// #include <RoxySTD/RoxySTD.h>
//
//
//
// namespace Roxy::Math
// {
//
// #pragma region Utils
//
// // ============================================================================
// // 数学常量（<numbers> 全量 + 扩展）
// // ============================================================================
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T Pi = T(3.14159265358979323846264338327950288419716939937510);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T TwoPi = Pi<T> * T(2);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T Tau = Pi<T> * T(2);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T HalfPi = Pi<T> / T(2);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T QuarterPi = Pi<T> / T(4);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T InvPi = T(1) / Pi<T>;
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T E = T(2.71828182845904523536028747135266249775724709369995);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T Sqrt2 = T(1.41421356237309504880168872420969807856967187537694);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T Sqrt3 = T(1.73205080756887729352744634150587236694280525381038);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T Sqrt5 = T(2.23606797749978969640917366873127623544061835961152);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T InvSqrt2 = T(1) / Sqrt2<T>;
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T InvSqrt3 = T(1) / Sqrt3<T>;
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T Ln2 = T(0.69314718055994530941723212145817656807550013436025);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T Ln10 = T(2.30258509299404568401799145468436420760110148862877);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T Log2E = T(1) / Ln2<T>;
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T Log10E = T(1) / Ln10<T>;
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T EulerGamma = T(0.57721566490153286060651209008240243104215933593992);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T Phi = T(1.61803398874989484820458683436563811772030917980576);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T DegToRad = Pi<T> / T(180);
//
// template<typename T> requires std::is_floating_point_v<T>
// inline constexpr T RadToDeg = T(180) / Pi<T>;
//
// // ============================================================================
// // 编译期实现 (Impl)
// // ============================================================================
// namespace Detail
// {
//     template<typename T>
//     constexpr T Sqrt(T X) noexcept
//     {
//         if (X <= T(0)) return T(0);
//         T Curr = X, Prev = T(0);
//         while (Curr != Prev)
//         {
//             Prev = Curr;
//             Curr = (Curr + X / Curr) * T(0.5);
//         }
//         return Curr;
//     }
//
//     template<typename T>
//     constexpr T Sin(T X) noexcept
//     {
//         T Y = X;
//         while (Y > Pi<T>) Y -= TwoPi<T>;
//         while (Y < -Pi<T>) Y += TwoPi<T>;
//         T Term = Y, Sum = Y;
//         for (int N = 3; N < 20; N += 2)
//         {
//             Term = -Term * Y * Y / T(N * (N - 1));
//             Sum += Term;
//         }
//         return Sum;
//     }
//
//     template<typename T>
//     constexpr T Cos(T X) noexcept
//     {
//         return Sin(HalfPi<T> - X);
//     }
//
//     template<typename T>
//     constexpr T Tan(T X) noexcept
//     {
//         return Sin(X) / Cos(X);
//     }
//
//     template<typename T>
//     constexpr T Atan(T X) noexcept
//     {
//         if (X < T(0)) return -Atan(-X);
//         if (X > T(1)) return HalfPi<T> - Atan(T(1) / X);
//         T X2 = X * X;
//         T Term = X, Sum = X;
//         for (int N = 3; N < 30; N += 2)
//         {
//             Term = -Term * X2;
//             Sum += Term / T(N);
//         }
//         return Sum;
//     }
//
//     template<typename T>
//     constexpr T Atan2(T Y, T X) noexcept
//     {
//         if (X > T(0)) return Atan(Y / X);
//         if (X < T(0) && Y >= T(0)) return Atan(Y / X) + Pi<T>;
//         if (X < T(0) && Y < T(0)) return Atan(Y / X) - Pi<T>;
//         if (X == T(0) && Y > T(0)) return HalfPi<T>;
//         if (X == T(0) && Y < T(0)) return -HalfPi<T>;
//         return T(0);
//     }
//
//     template<typename T>
//     constexpr T Asin(T X) noexcept
//     {
//         if (X <= T(-1)) return -HalfPi<T>;
//         if (X >= T(1)) return HalfPi<T>;
//         return Atan2(X, Sqrt(T(1) - X * X));
//     }
//
//     template<typename T>
//     constexpr T Acos(T X) noexcept
//     {
//         return HalfPi<T> - Asin(X);
//     }
//
//     template<typename T>
//     constexpr T Exp(T X) noexcept
//     {
//         T Sum = T(1), Term = T(1);
//         for (int N = 1; N < 30; ++N)
//         {
//             Term *= X / T(N);
//             Sum += Term;
//         }
//         return Sum;
//     }
//
//     template<typename T>
//     constexpr T Log(T X) noexcept
//     {
//         if (X <= T(0)) return -T(1) / T(0);
//         T Y = X - T(1);
//         for (int I = 0; I < 10; ++I)
//             Y = Y + (X - Exp(Y)) / Exp(Y);
//         return Y;
//     }
//
//     template<typename T>
//     constexpr T Pow(T Base, T Exp) noexcept
//     {
//         return Detail::Exp(Exp * Detail::Log(Base));
//     }
// } // namespace Impl
//
// // ============================================================================
// // 基础函数
// // ============================================================================
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Sqrt(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Sqrt(X);
//     }
//     return std::sqrt(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T InvSqrt(T X) noexcept
// {
//     if consteval
//     {
//         return static_cast<T>(1) / Detail::Sqrt(X);
//     }
//     return static_cast<T>(1) / std::sqrt(X);
// }
//
// template<typename T> requires std::is_arithmetic_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Abs(T X) noexcept
// {
//     return std::abs(X);
// }
//
// // ============================================================================
// // 三角函数
// // ============================================================================
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Sin(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Sin(X);
//     }
//     return std::sin(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Cos(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Cos(X);
//     }
//     return std::cos(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Tan(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Tan(X);
//     }
//     return std::tan(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Asin(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Asin(X);
//     }
//     return std::asin(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Acos(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Acos(X);
//     }
//     return std::acos(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Atan(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Atan(X);
//     }
//     return std::atan(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Atan2(T Y, T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Atan2(Y, X);
//     }
//     return std::atan2(Y, X);
// }
//
// // ============================================================================
// // 双曲函数
// // ============================================================================
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Sinh(T X) noexcept
// {
//     if consteval
//     {
//         return (Detail::Exp(X) - Detail::Exp(-X)) / T(2);
//     }
//     return std::sinh(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Cosh(T X) noexcept
// {
//     if consteval
//     {
//         return (Detail::Exp(X) + Detail::Exp(-X)) / T(2);
//     }
//     return std::cosh(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Tanh(T X) noexcept
// {
//     if consteval
//     {
//         T E2X = Detail::Exp(T(2) * X);
//         return (E2X - T(1)) / (E2X + T(1));
//     }
//     return std::tanh(X);
// }
//
// // ============================================================================
// // 指数与对数
// // ============================================================================
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Exp(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Exp(X);
//     }
//     return std::exp(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Log(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Log(X);
//     }
//     return std::log(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Log2(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Log(X) / Detail::Log(T(2));
//     }
//     return std::log2(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Log10(T X) noexcept
// {
//     if consteval
//     {
//         return Detail::Log(X) / Detail::Log(T(10));
//     }
//     return std::log10(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Pow(T Base, T Exp) noexcept
// {
//     if consteval
//     {
//         return Detail::Pow(Base, Exp);
//     }
//     return std::pow(Base, Exp);
// }
//
// // ============================================================================
// // 取整函数
// // ============================================================================
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Floor(T X) noexcept
// {
//     return std::floor(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Ceil(T X) noexcept
// {
//     return std::ceil(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Round(T X) noexcept
// {
//     return std::round(X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Trunc(T X) noexcept
// {
//     return std::trunc(X);
// }
//
// // ============================================================================
// // 常用数值运算
// // ============================================================================
// template<typename T> requires std::is_arithmetic_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Min(T X, T Y) noexcept
// {
//     return (X < Y) ? X : Y;
// }
//
// template<typename T> requires std::is_arithmetic_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Max(T X, T Y) noexcept
// {
//     return (X > Y) ? X : Y;
// }
//
// template<typename T> requires std::is_arithmetic_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Clamp(T X, T Lo, T Hi) noexcept
// {
//     return Min(Max(X, Lo), Hi);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Lerp(T X, T Y, T Alpha) noexcept
// {
//     return X + Alpha * (Y - X);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Fmod(T X, T Y) noexcept
// {
//     return std::fmod(X, Y);
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T CopySign(T Magnitude, T Sign) noexcept
// {
//     return std::copysign(Magnitude, Sign);
// }
//
// template<typename T> requires std::is_arithmetic_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T Sign(T X) noexcept
// {
//     return (X > T(0)) ? T(1) : ((X < T(0)) ? T(-1) : T(0));
// }
//
// // ============================================================================
// // 角度与弧度转换
// // ============================================================================
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T ToRadian(T Degrees) noexcept
// {
//     return Degrees * DegToRad<T>;
// }
//
// template<typename T> requires std::is_floating_point_v<T>
// ROXY_NODISCARD ROXY_INLINE constexpr T ToDegree(T Radians) noexcept
// {
//     return Radians * RadToDeg<T>;
// }
//
// #pragma endregion
//
// #pragma region VecBase
//
// template <typename T, FIndex Dim> requires std::is_arithmetic_v<T> && (2 <= Dim && Dim <= 4) class TVec;
//
// template <typename FVec, typename T, FIndex Dim> requires std::is_arithmetic_v<T> && (2 <= Dim && Dim <= 4)
// class TVecBase
// {
// public:
//     ROXY_NODISCARD ROXY_INLINE constexpr TVecBase() noexcept = default;
//
//     ROXY_NODISCARD ROXY_INLINE constexpr TVecBase(TInitList<T> InitList) noexcept
//     {
//         auto It = InitList.begin();
//         const auto Num = InitList.size();
//         if constexpr (Dim >= 2)
//         {
//             Payload[0] = (Num > 0) ? *It++ : T{};
//             Payload[1] = (Num > 1) ? *It++ : T{};
//         }
//         if constexpr (Dim >= 3)
//         {
//             Payload[2] = (Num > 2) ? *It++ : T{};
//         }
//         if constexpr (Dim >= 4)
//         {
//             Payload[3] = (Num > 3) ? *It++ : T{};
//         }
//     }
//
//     ROXY_NODISCARD ROXY_INLINE T& operator[](FIndex Idx) noexcept
//     {
//         ROXY_ASSERT((0 <= Idx && Idx < Dim) && "Vec Index Out Of Bound");
//         return Payload[Idx];
//     }
//
//     ROXY_NODISCARD ROXY_INLINE constexpr const T& operator[](FIndex Idx) const noexcept
//     {
//         ROXY_ASSERT((0 <= Idx && Idx < Dim) && "Vec Index Out Of Bound");
//         return Payload[Idx];
//     }
//
//     template <typename U> requires std::is_convertible_v<T, U>
//     ROXY_NODISCARD ROXY_INLINE constexpr TVec<U, Dim> As() const noexcept
//     {
//         if constexpr (Dim == 2)
//         {
//             return TVec<U, Dim>{ static_cast<U>(Payload[0]), static_cast<U>(Payload[1]) };
//         }
//         else if constexpr (Dim == 3)
//         {
//             return TVec<U, Dim>{ static_cast<U>(Payload[0]), static_cast<U>(Payload[1]), static_cast<U>(Payload[2]) };
//         }
//         else
//         {
//             static_assert(Dim == 4 && "Vec Dim Out Of Bound");
//             return TVec<U, Dim>{ static_cast<U>(Payload[0]), static_cast<U>(Payload[1]), static_cast<U>(Payload[2]), static_cast<U>(Payload[3]) };
//         }
//     }
//
//     ROXY_NODISCARD ROXY_INLINE static constexpr FVec Zero() noexcept
//     {
//         return FVec{};
//     }
//
//     ROXY_NODISCARD ROXY_INLINE static constexpr FVec One() noexcept
//     {
//         if constexpr (Dim == 2)
//         {
//             return FVec{static_cast<T>(1), static_cast<T>(1)};
//         }
//         else if constexpr (Dim == 3)
//         {
//             return FVec{static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)};
//         }
//         else
//         {
//             static_assert(Dim == 4 && "Vec Dim Out Of Bound");
//             return FVec{static_cast<T>(1), static_cast<T>(1), static_cast<T>(1), static_cast<T>(1)};
//         }
//     }
//
//     ROXY_NODISCARD ROXY_INLINE static constexpr FVec Axis(FIndex Idx) noexcept
//     {
//         FVec Temp{};
//         Temp[Idx] = static_cast<T>(1);
//         return Temp;
//     }
//
//     ROXY_NODISCARD ROXY_INLINE constexpr bool operator==(const FVec& Oth) const noexcept
//     {
//         bool Equal{true};
//         if constexpr (Dim >= 2)
//         {
//             Equal = Equal && (Payload[0] == Oth[0]) && (Payload[1] == Oth[1]);
//         }
//         if constexpr (Dim >= 3)
//         {
//             Equal = Equal && (Payload[2] == Oth[2]);
//         }
//         if constexpr (Dim >= 4)
//         {
//             Equal = Equal && (Payload[3] == Oth[3]);
//         }
//         return Equal;
//     }
//
//     ROXY_NODISCARD ROXY_INLINE constexpr bool operator!=(const FVec& Oth) const noexcept
//     {
//         return !(*this == Oth);
//     }
//
//     ROXY_INLINE constexpr FVec& operator+=(const FVec& Oth) noexcept
//     {
//         if constexpr (Dim >= 1) { Payload[0] += Oth[0]; }
//         if constexpr (Dim >= 2) { Payload[1] += Oth[1]; }
//         if constexpr (Dim >= 3) { Payload[2] += Oth[2]; }
//         if constexpr (Dim >= 4) { Payload[3] += Oth[3]; }
//         return static_cast<FVec&>(*this);
//     }
//
//     ROXY_INLINE constexpr FVec& operator-=(const FVec& Oth) noexcept
//     {
//         if constexpr (Dim >= 1) { Payload[0] -= Oth[0]; }
//         if constexpr (Dim >= 2) { Payload[1] -= Oth[1]; }
//         if constexpr (Dim >= 3) { Payload[2] -= Oth[2]; }
//         if constexpr (Dim >= 4) { Payload[3] -= Oth[3]; }
//         return static_cast<FVec&>(*this);
//     }
//
//     ROXY_INLINE constexpr FVec& operator*=(const FVec& Oth) noexcept
//     {
//         if constexpr (Dim >= 1) { Payload[0] *= Oth[0]; }
//         if constexpr (Dim >= 2) { Payload[1] *= Oth[1]; }
//         if constexpr (Dim >= 3) { Payload[2] *= Oth[2]; }
//         if constexpr (Dim >= 4) { Payload[3] *= Oth[3]; }
//         return static_cast<FVec&>(*this);
//     }
//
//     ROXY_INLINE constexpr FVec& operator/=(const FVec& Oth) noexcept
//     {
//         if constexpr (Dim >= 1) { Payload[0] /= Oth[0]; }
//         if constexpr (Dim >= 2) { Payload[1] /= Oth[1]; }
//         if constexpr (Dim >= 3) { Payload[2] /= Oth[2]; }
//         if constexpr (Dim >= 4) { Payload[3] /= Oth[3]; }
//         return static_cast<FVec&>(*this);
//     }
//
//     ROXY_INLINE constexpr FVec& operator*=(T Scalar) noexcept
//     {
//         if constexpr (Dim >= 1) { Payload[0] *= Scalar; }
//         if constexpr (Dim >= 2) { Payload[1] *= Scalar; }
//         if constexpr (Dim >= 3) { Payload[2] *= Scalar; }
//         if constexpr (Dim >= 4) { Payload[3] *= Scalar; }
//         return static_cast<FVec&>(*this);
//     }
//
//     ROXY_INLINE constexpr FVec& operator/=(T Scalar) noexcept
//     {
//         const T InvScalar = static_cast<T>(1) / Scalar;
//         return *this *= InvScalar;
//     }
//
//     // ROXY_NODISCARD ROXY_INLINE constexpr FVec Abs() const noexcept
//     // {
//     //     if constexpr (Dim == 2)
//     //     {
//     //         return FVec{ std::abs(Payload[0]), std::abs(Payload[1]) };
//     //     }
//     //     else if constexpr (Dim == 3)
//     //     {
//     //         return FVec{ std::abs(Payload[0]), std::abs(Payload[1]), std::abs(Payload[2]) };
//     //     }
//     //     else
//     //     {
//     //         static_assert(Dim == 4 && "Vec Dim Out Of Bound");
//     //         return FVec{ std::abs(Payload[0]), std::abs(Payload[1]), std::abs(Payload[2]), std::abs(Payload[3]) };
//     //     }
//     // }
//
//     ROXY_NODISCARD ROXY_INLINE constexpr T Min() const noexcept
//     {
//         if constexpr (Dim == 2)
//         {
//             return std::min(Payload[0], Payload[1]);
//         }
//         else if constexpr (Dim == 3)
//         {
//             return std::min(Payload[0], Payload[1], Payload[2]);
//         }
//         else
//         {
//             static_assert(Dim == 4 && "Vec Dim Out Of Bound");
//             return std::min(Payload[0], Payload[1], Payload[2], Payload[3]);
//         }
//     }
//
//     ROXY_NODISCARD ROXY_INLINE constexpr T Max() const noexcept
//     {
//         if constexpr (Dim == 2)
//         {
//             return std::max(Payload[0], Payload[1]);
//         }
//         else if constexpr (Dim == 3)
//         {
//             return std::max(Payload[0], Payload[1], Payload[2]);
//         }
//         else
//         {
//             static_assert(Dim == 4 && "Vec Dim Out Of Bound");
//             return std::max(Payload[0], Payload[1], Payload[2], Payload[3]);
//         }
//     }
//
//     // ROXY_NODISCARD ROXY_INLINE constexpr T Dot(const FVec& Oth) const noexcept
//     // {
//     //     return Math::Dot(static_cast<const FVec&>(*this), Oth);
//     // }
//
//     ROXY_NODISCARD ROXY_INLINE constexpr T SqrLen() const noexcept
//     {
//         return Dot(static_cast<const FVec&>(*this));
//     }
//
//     ROXY_NODISCARD ROXY_INLINE constexpr T Len() const noexcept requires std::is_floating_point_v<T>
//     {
//         return static_cast<T>(Sqrt(SqrLen()));
//     }
//
//     // ROXY_NODISCARD ROXY_INLINE constexpr FVec Clamped(T InMin, T InMax) const noexcept
//     // {
//     //     if constexpr (Dim == 2)
//     //     {
//     //         return FVec{ std::clamp(Payload[0], InMin, InMax), std::clamp(Payload[1], InMin, InMax) };
//     //     }
//     //     else if constexpr (Dim == 3)
//     //     {
//     //         return FVec{ std::clamp(Payload[0], InMin, InMax), std::clamp(Payload[1], InMin, InMax), std::clamp(Payload[2], InMin, InMax) };
//     //     }
//     //     else
//     //     {
//     //         static_assert(Dim == 4);
//     //         return FVec{ std::clamp(Payload[0], InMin, InMax), std::clamp(Payload[1], InMin, InMax), std::clamp(Payload[2], InMin, InMax), std::clamp(Payload[3], InMin, InMax) };
//     //     }
//     // }
//
//     // ROXY_INLINE constexpr void Clamp(T InMin, T InMax) noexcept
//     // {
//     //     if constexpr (Dim >= 1) { Payload[0] = std::clamp(Payload[0], InMin, InMax); }
//     //     if constexpr (Dim >= 2) { Payload[1] = std::clamp(Payload[1], InMin, InMax); }
//     //     if constexpr (Dim >= 3) { Payload[2] = std::clamp(Payload[2], InMin, InMax); }
//     //     if constexpr (Dim >= 4) { Payload[3] = std::clamp(Payload[3], InMin, InMax); }
//     // }
//
//     // ROXY_NODISCARD ROXY_INLINE FVec Normalized() const noexcept requires std::is_floating_point_v<T>
//     // {
//     //     const auto InvLen = InvSqrt(SqrLen());
//     //     return static_cast<const FVec&>(*this) * InvLen;
//     // }
//     //
//     // ROXY_INLINE void Normalize() noexcept requires std::is_floating_point_v<T>
//     // {
//     //     const auto InvLen = InvSqrt(SqrLen());
//     //     *this *= InvLen;
//     // }
//
// protected:
//     alignas(16) T Payload[(Dim == 3) ? 4 : Dim] {};
// };
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr T Dot(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
// {
//     T Result = 0;
//     if constexpr (Dim >= 2) { Result += Lhs[0] * Rhs[0] + Lhs[1] * Rhs[1]; }
//     if constexpr (Dim >= 3) { Result += Lhs[2] * Rhs[2]; }
//     if constexpr (Dim >= 4) { Result += Lhs[3] * Rhs[3]; }
//     return Result;
// }
//
// template <typename T, FIndex Dim> requires (Dim == 3)
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> Cross(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
// {
//     return TVec<T, Dim>
//     {
//         Lhs[1] * Rhs[2] - Lhs[2] * Rhs[1],
//         Lhs[2] * Rhs[0] - Lhs[0] * Rhs[2],
//         Lhs[0] * Rhs[1] - Lhs[1] * Rhs[0]
//     };
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Vec) noexcept
// {
//     return Vec;
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(const TVec<T, Dim>& Vec) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{-Vec[0], -Vec[1]};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{-Vec[0], -Vec[1], -Vec[2]};
//     }
//     else
//     {
//         return TVec<T, Dim>{-Vec[0], -Vec[1], -Vec[2], -Vec[3]};
//     }
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{Lhs[0] + Rhs[0], Lhs[1] + Rhs[1]};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{Lhs[0] + Rhs[0], Lhs[1] + Rhs[1], Lhs[2] + Rhs[2]};
//     }
//     else
//     {
//         return TVec<T, Dim>{Lhs[0] + Rhs[0], Lhs[1] + Rhs[1], Lhs[2] + Rhs[2], Lhs[3] + Rhs[3]};
//     }
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{Lhs[0] - Rhs[0], Lhs[1] - Rhs[1]};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{Lhs[0] - Rhs[0], Lhs[1] - Rhs[1], Lhs[2] - Rhs[2]};
//     }
//     else
//     {
//         return TVec<T, Dim>{Lhs[0] - Rhs[0], Lhs[1] - Rhs[1], Lhs[2] - Rhs[2], Lhs[3] - Rhs[3]};
//     }
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{Lhs[0] * Rhs[0], Lhs[1] * Rhs[1]};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{Lhs[0] * Rhs[0], Lhs[1] * Rhs[1], Lhs[2] * Rhs[2]};
//     }
//     else
//     {
//         return TVec<T, Dim>{Lhs[0] * Rhs[0], Lhs[1] * Rhs[1], Lhs[2] * Rhs[2], Lhs[3] * Rhs[3]};
//     }
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(const TVec<T, Dim>& Lhs, const TVec<T, Dim>& Rhs) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{Lhs[0] / Rhs[0], Lhs[1] / Rhs[1]};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{Lhs[0] / Rhs[0], Lhs[1] / Rhs[1], Lhs[2] / Rhs[2]};
//     }
//     else
//     {
//         return TVec<T, Dim>{Lhs[0] / Rhs[0], Lhs[1] / Rhs[1], Lhs[2] / Rhs[2], Lhs[3] / Rhs[3]};
//     }
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(const TVec<T, Dim>& Vec, T scalar) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{Vec[0] + scalar, Vec[1] + scalar};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{Vec[0] + scalar, Vec[1] + scalar, Vec[2] + scalar};
//     }
//     else
//     {
//         return TVec<T, Dim>{Vec[0] + scalar, Vec[1] + scalar, Vec[2] + scalar, Vec[3] + scalar};
//     }
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(const TVec<T, Dim>& Vec, T scalar) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{Vec[0] - scalar, Vec[1] - scalar};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{Vec[0] - scalar, Vec[1] - scalar, Vec[2] - scalar};
//     }
//     else
//     {
//         return TVec<T, Dim>{Vec[0] - scalar, Vec[1] - scalar, Vec[2] - scalar, Vec[3] - scalar};
//     }
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(const TVec<T, Dim>& Vec, T scalar) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{Vec[0] * scalar, Vec[1] * scalar};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{Vec[0] * scalar, Vec[1] * scalar, Vec[2] * scalar};
//     }
//     else
//     {
//         return TVec<T, Dim>{Vec[0] * scalar, Vec[1] * scalar, Vec[2] * scalar, Vec[3] * scalar};
//     }
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(const TVec<T, Dim>& Vec, T scalar) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{Vec[0] / scalar, Vec[1] / scalar};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{Vec[0] / scalar, Vec[1] / scalar, Vec[2] / scalar};
//     }
//     else
//     {
//         return TVec<T, Dim>{Vec[0] / scalar, Vec[1] / scalar, Vec[2] / scalar, Vec[3] / scalar};
//     }
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator+(T scalar, const TVec<T, Dim>& Vec) noexcept
// {
//     return Vec + scalar;
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator-(T scalar, const TVec<T, Dim>& Vec) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{scalar - Vec[0], scalar - Vec[1]};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{scalar - Vec[0], scalar - Vec[1], scalar - Vec[2]};
//     }
//     else
//     {
//         return TVec<T, Dim>{scalar - Vec[0], scalar - Vec[1], scalar - Vec[2], scalar - Vec[3]};
//     }
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator*(T scalar, const TVec<T, Dim>& Vec) noexcept
// {
//     return Vec * scalar;
// }
//
// template <typename T, FIndex Dim>
// ROXY_NODISCARD ROXY_INLINE constexpr TVec<T, Dim> operator/(T scalar, const TVec<T, Dim>& Vec) noexcept
// {
//     if constexpr (Dim == 2)
//     {
//         return TVec<T, Dim>{scalar / Vec[0], scalar / Vec[1]};
//     }
//     else if constexpr (Dim == 3)
//     {
//         return TVec<T, Dim>{scalar / Vec[0], scalar / Vec[1], scalar / Vec[2]};
//     }
//     else
//     {
//         return TVec<T, Dim>{scalar / Vec[0], scalar / Vec[1], scalar / Vec[2], scalar / Vec[3]};
//     }
// }
//
// #pragma endregion
//
// #pragma region Vec
//
// template <typename T> requires std::is_arithmetic_v<T>
// class TVec<T, 2> : public TVecBase<TVec<T, 2>, T, 2>
// {
//     friend class TVecBase<TVec, T, 2>;
//
// public:
//     using TVecBase<TVec, T, 2>::TVecBase;
//
//     static constexpr TVec AxisX() noexcept { return TVecBase<TVec, T, 2>::Axis(0); }
//     static constexpr TVec AxisY() noexcept { return TVecBase<TVec, T, 2>::Axis(1); }
//
//     ROXY_NODISCARD ROXY_INLINE T& X() noexcept { return this->Payload[0]; }
//     ROXY_NODISCARD ROXY_INLINE const T& X() const noexcept { return this->Payload[0]; }
//     ROXY_NODISCARD ROXY_INLINE T& Y() noexcept { return this->Payload[1]; }
//     ROXY_NODISCARD ROXY_INLINE const T& Y() const noexcept { return this->Payload[1]; }
// };
//
// template <typename T> requires std::is_arithmetic_v<T>
// class TVec<T, 3> : public TVecBase<TVec<T, 3>, T, 3>
// {
//     friend class TVecBase<TVec, T, 3>;
//
// public:
//     using TVecBase<TVec, T, 3>::TVecBase;
//
//     static constexpr TVec AxisX() noexcept { return TVecBase<TVec, T, 3>::Axis(0); }
//     static constexpr TVec AxisY() noexcept { return TVecBase<TVec, T, 3>::Axis(1); }
//     static constexpr TVec AxisZ() noexcept { return TVecBase<TVec, T, 3>::Axis(2); }
//
//     ROXY_NODISCARD ROXY_INLINE T& X() noexcept { return this->Payload[0]; }
//     ROXY_NODISCARD ROXY_INLINE const T& X() const noexcept { return this->Payload[0]; }
//     ROXY_NODISCARD ROXY_INLINE T& Y() noexcept { return this->Payload[1]; }
//     ROXY_NODISCARD ROXY_INLINE const T& Y() const noexcept { return this->Payload[1]; }
//     ROXY_NODISCARD ROXY_INLINE T& Z() noexcept { return this->Payload[2]; }
//     ROXY_NODISCARD ROXY_INLINE const T& Z() const noexcept { return this->Payload[2]; }
//
//     ROXY_NODISCARD ROXY_INLINE constexpr TVec Cross(const TVec& Oth) const noexcept
//     {
//         return Math::Cross(*this, Oth);
//     }
// };
//
// template <typename T> requires std::is_arithmetic_v<T>
// class TVec<T, 4> : public TVecBase<TVec<T, 4>, T, 4>
// {
//     friend class TVecBase<TVec, T, 4>;
//
// public:
//     using TVecBase<TVec, T, 4>::TVecBase;
//
//     static constexpr TVec AxisX() noexcept { return TVecBase<TVec, T, 4>::Axis(0); }
//     static constexpr TVec AxisY() noexcept { return TVecBase<TVec, T, 4>::Axis(1); }
//     static constexpr TVec AxisZ() noexcept { return TVecBase<TVec, T, 4>::Axis(2); }
//     static constexpr TVec AxisW() noexcept { return TVecBase<TVec, T, 4>::Axis(3); }
//
//     ROXY_NODISCARD ROXY_INLINE T& X() noexcept { return this->Payload[0]; }
//     ROXY_NODISCARD ROXY_INLINE const T& X() const noexcept { return this->Payload[0]; }
//     ROXY_NODISCARD ROXY_INLINE T& Y() noexcept { return this->Payload[1]; }
//     ROXY_NODISCARD ROXY_INLINE const T& Y() const noexcept { return this->Payload[1]; }
//     ROXY_NODISCARD ROXY_INLINE T& Z() noexcept { return this->Payload[2]; }
//     ROXY_NODISCARD ROXY_INLINE const T& Z() const noexcept { return this->Payload[2]; }
//     ROXY_NODISCARD ROXY_INLINE T& W() noexcept { return this->Payload[3]; }
//     ROXY_NODISCARD ROXY_INLINE const T& W() const noexcept { return this->Payload[3]; }
// };
//
// #pragma endregion
//
// #if ROXY_ENABLE_SIMD
//
// #pragma region SIMD
//
// // float3 add
// ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator+(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
// {
//     TVec<float, 3> Temp;
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
//     const __m128 C = _mm_add_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // float3 sub
// ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator-(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
// {
//     TVec<float, 3> Temp;
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
//     const __m128 C = _mm_sub_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // float3 Mul
// ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator*(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
// {
//     TVec<float, 3> Temp;
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
//     const __m128 C = _mm_mul_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // float3 div
// ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator/(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
// {
//     TVec<float, 3> Temp;
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
//     const __m128 C = _mm_div_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // float4 add
// ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator+(const TVec<float, 4>& Lhs, const TVec<float, 4>& Rhs) noexcept
// {
//     TVec<float, 4> Temp;
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
//     const __m128 C = _mm_add_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // float4 sub
// ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator-(const TVec<float, 4>& Lhs, const TVec<float, 4>& Rhs) noexcept
// {
//     TVec<float, 4> Temp;
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
//     const __m128 C = _mm_sub_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // float4 Mul
// ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator*(const TVec<float, 4>& Lhs, const TVec<float, 4>& Rhs) noexcept
// {
//     TVec<float, 4> Temp;
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
//     const __m128 C = _mm_mul_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // float4 div
// ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator/(const TVec<float, 4>& Lhs, const TVec<float, 4>& Rhs) noexcept
// {
//     TVec<float, 4> Temp;
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
//     const __m128 C = _mm_div_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // double2 add
// ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator+(const TVec<double, 2>& Lhs, const TVec<double, 2>& Rhs) noexcept
// {
//     TVec<double, 2> Temp;
//     const __m128d A = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C = _mm_add_pd(A, B);
//     _mm_storeu_pd(&Temp[0], C);
//     return Temp;
// }
//
// // double2 sub
// ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator-(const TVec<double, 2>& Lhs, const TVec<double, 2>& Rhs) noexcept
// {
//     TVec<double, 2> Temp;
//     const __m128d A = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C = _mm_sub_pd(A, B);
//     _mm_storeu_pd(&Temp[0], C);
//     return Temp;
// }
//
// // double2 Mul
// ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator*(const TVec<double, 2>& Lhs, const TVec<double, 2>& Rhs) noexcept
// {
//     TVec<double, 2> Temp;
//     const __m128d A = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C = _mm_mul_pd(A, B);
//     _mm_storeu_pd(&Temp[0], C);
//     return Temp;
// }
//
// // double2 div
// ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator/(const TVec<double, 2>& Lhs, const TVec<double, 2>& Rhs) noexcept
// {
//     TVec<double, 2> Temp;
//     const __m128d A = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C = _mm_div_pd(A, B);
//     _mm_storeu_pd(&Temp[0], C);
//     return Temp;
// }
//
// // double3 add
// ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator+(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
// {
//     TVec<double, 3> Temp;
//     const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C0 = _mm_add_pd(A0, B0);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
//     const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
//     const __m128d C1 = _mm_add_pd(A1, B1);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // double3 sub
// ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator-(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
// {
//     TVec<double, 3> Temp;
//     const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C0 = _mm_sub_pd(A0, B0);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
//     const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
//     const __m128d C1 = _mm_sub_pd(A1, B1);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // double3 Mul
// ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator*(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
// {
//     TVec<double, 3> Temp;
//     const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C0 = _mm_mul_pd(A0, B0);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
//     const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
//     const __m128d C1 = _mm_mul_pd(A1, B1);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // double3 div
// ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator/(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
// {
//     TVec<double, 3> Temp;
//     const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C0 = _mm_div_pd(A0, B0);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
//     const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
//     const __m128d C1 = _mm_div_pd(A1, B1);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // double4 add
// ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator+(const TVec<double, 4>& Lhs, const TVec<double, 4>& Rhs) noexcept
// {
//     TVec<double, 4> Temp;
//     const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C0 = _mm_add_pd(A0, B0);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
//     const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
//     const __m128d C1 = _mm_add_pd(A1, B1);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // double4 sub
// ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator-(const TVec<double, 4>& Lhs, const TVec<double, 4>& Rhs) noexcept
// {
//     TVec<double, 4> Temp;
//     const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C0 = _mm_sub_pd(A0, B0);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
//     const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
//     const __m128d C1 = _mm_sub_pd(A1, B1);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // double4 Mul
// ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator*(const TVec<double, 4>& Lhs, const TVec<double, 4>& Rhs) noexcept
// {
//     TVec<double, 4> Temp;
//     const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C0 = _mm_mul_pd(A0, B0);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
//     const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
//     const __m128d C1 = _mm_mul_pd(A1, B1);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // double4 div
// ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator/(const TVec<double, 4>& Lhs, const TVec<double, 4>& Rhs) noexcept
// {
//     TVec<double, 4> Temp;
//     const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
//     const __m128d C0 = _mm_div_pd(A0, B0);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
//     const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
//     const __m128d C1 = _mm_div_pd(A1, B1);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // float3 dot
// ROXY_NODISCARD ROXY_INLINE float Dot(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
// {
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
// #if defined(__FMA__) || defined(__AVX2__)
//     const __m128 Mul   = _mm_mul_ps(A, B);
//     const __m128 Mask  = _mm_insert_ps(Mul, _mm_setzero_ps(), 0x30);
//     const __m128 Shuf  = _mm_permute_ps(Mask, _MM_SHUFFLE(1, 0, 3, 2));
//     const __m128 Sum   = _mm_add_ps(Mask, Shuf);
//     const __m128 Shuf2 = _mm_permute_ps(Sum, _MM_SHUFFLE(2, 3, 0, 1));
//     return _mm_cvtss_f32(_mm_add_ps(Sum, Shuf2));
// #else
//     const __m128 Mul  = _mm_mul_ps(A, B);
//     const __m128 Mask = _mm_insert_ps(Mul, _mm_setzero_ps(), 0x30);
//     const __m128 HAdd = _mm_hadd_ps(Mask, Mask);
//     const __m128 Sum  = _mm_hadd_ps(HAdd, HAdd);
//     return _mm_cvtss_f32(Sum);
// #endif
// }
//
// // float4 dot
// ROXY_NODISCARD ROXY_INLINE float Dot(const TVec<float, 4>& Lhs, const TVec<float, 4>& Rhs) noexcept
// {
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
// #if defined(__FMA__) || defined(__AVX2__)
//     const __m128 Mul = _mm_mul_ps(A, B);
//     const __m128 Shuf = _mm_permute_ps(Mul, _MM_SHUFFLE(1, 0, 3, 2));
//     __m128 Sum = _mm_add_ps(Mul, Shuf);
//     const __m128 Shuf2 = _mm_permute_ps(Sum, _MM_SHUFFLE(2, 3, 0, 1));
//     Sum = _mm_add_ps(Sum, Shuf2);
//     return _mm_cvtss_f32(Sum);
// #else
//     const __m128 Mul = _mm_mul_ps(A, B);
//     const __m128 HAdd = _mm_hadd_ps(Mul, Mul);
//     const __m128 Sum = _mm_hadd_ps(HAdd, HAdd);
//     return _mm_cvtss_f32(Sum);
// #endif
// }
//
// // double2 dot
// ROXY_NODISCARD ROXY_INLINE double Dot(const TVec<double, 2>& Lhs, const TVec<double, 2>& Rhs) noexcept
// {
//     const __m128d A    = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B    = _mm_loadu_pd(&Rhs[0]);
//     const __m128d Mul  = _mm_mul_pd(A, B);
//     const __m128d HAdd = _mm_hadd_pd(Mul, Mul);
//     return _mm_cvtsd_f64(HAdd);
// }
//
// // double3 dot
// ROXY_NODISCARD ROXY_INLINE double Dot(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
// {
//     const __m128d A0  = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B0  = _mm_loadu_pd(&Rhs[0]);
//     const __m128d Mul = _mm_mul_pd(A0, B0);
//     const __m128d Sum = _mm_add_sd(Mul, _mm_unpackhi_pd(Mul, Mul));
//     return _mm_cvtsd_f64(Sum) + Lhs[2] * Rhs[2];
// }
//
// // double4 dot
// ROXY_NODISCARD ROXY_INLINE double Dot(const TVec<double, 4>& Lhs, const TVec<double, 4>& Rhs) noexcept
// {
//     const __m128d A0   = _mm_loadu_pd(&Lhs[0]);
//     const __m128d B0   = _mm_loadu_pd(&Rhs[0]);
//     const __m128d Mul0 = _mm_mul_pd(A0, B0);
//     const __m128d A1   = _mm_loadu_pd(&Lhs[2]);
//     const __m128d B1   = _mm_loadu_pd(&Rhs[2]);
//     const __m128d Mul1 = _mm_mul_pd(A1, B1);
//     const __m128d Sum  = _mm_add_pd(Mul0, Mul1);
//     const __m128d HAdd = _mm_hadd_pd(Sum, Sum);
//     return _mm_cvtsd_f64(HAdd);
// }
//
// // float3 cross
// ROXY_NODISCARD ROXY_INLINE TVec<float, 3> Cross(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
// {
//     const __m128 A = _mm_loadu_ps(&Lhs[0]);
//     const __m128 B = _mm_loadu_ps(&Rhs[0]);
//     const __m128 A_YZX = _mm_shuffle_ps(A, A, _MM_SHUFFLE(3, 0, 2, 1));
//     const __m128 B_YZX = _mm_shuffle_ps(B, B, _MM_SHUFFLE(3, 0, 2, 1));
//     const __m128 A_ZXY = _mm_shuffle_ps(A, A, _MM_SHUFFLE(3, 1, 0, 2));
//     const __m128 B_ZXY = _mm_shuffle_ps(B, B, _MM_SHUFFLE(3, 1, 0, 2));
// #if defined(__FMA__) || defined(__AVX2__)
//     const __m128 Cross = _mm_fmsub_ps(A_YZX, B_ZXY, _mm_mul_ps(A_ZXY, B_YZX));
// #else
//     const __m128 Cross = _mm_sub_ps(_mm_mul_ps(A_YZX, B_ZXY), _mm_mul_ps(A_ZXY, B_YZX));
// #endif
//     const __m128 Result = _mm_insert_ps(Cross, _mm_setzero_ps(), 0x30);
//     TVec<float, 3> Temp;
//     _mm_storeu_ps(&Temp[0], Result);
//     return Temp;
// }
//
// // double3 cross
// ROXY_NODISCARD ROXY_INLINE TVec<double, 3> Cross(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
// {
//     const double A0 = Lhs[0], A1 = Lhs[1], A2 = Lhs[2];
//     const double B0 = Rhs[0], B1 = Rhs[1], B2 = Rhs[2];
//     TVec<double, 3> Temp;
//     Temp[0] = A1 * B2 - A2 * B1;
//     Temp[1] = A2 * B0 - A0 * B2;
//     Temp[2] = A0 * B1 - A1 * B0;
//     return Temp;
// }
//
// // float3 * scalar
// ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator*(const TVec<float, 3>& Vec, float Scalar) noexcept
// {
//     TVec<float, 3> Temp;
//     const __m128 A = _mm_loadu_ps(&Vec[0]);
//     const __m128 B = _mm_set1_ps(Scalar);
//     const __m128 C = _mm_mul_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // float3 / scalar
// ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator/(const TVec<float, 3>& Vec, float Scalar) noexcept
// {
//     TVec<float, 3> Temp;
//     const __m128 A = _mm_loadu_ps(&Vec[0]);
//     const __m128 B = _mm_set1_ps(Scalar);
//     const __m128 C = _mm_div_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // float4 * scalar
// ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator*(const TVec<float, 4>& Vec, float Scalar) noexcept
// {
//     TVec<float, 4> Temp;
//     const __m128 A = _mm_loadu_ps(&Vec[0]);
//     const __m128 B = _mm_set1_ps(Scalar);
//     const __m128 C = _mm_mul_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // float4 / scalar
// ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator/(const TVec<float, 4>& Vec, float Scalar) noexcept
// {
//     TVec<float, 4> Temp;
//     const __m128 A = _mm_loadu_ps(&Vec[0]);
//     const __m128 B = _mm_set1_ps(Scalar);
//     const __m128 C = _mm_div_ps(A, B);
//     _mm_storeu_ps(&Temp[0], C);
//     return Temp;
// }
//
// // double2 * scalar
// ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator*(const TVec<double, 2>& Vec, double Scalar) noexcept
// {
//     TVec<double, 2> Temp;
//     const __m128d A = _mm_loadu_pd(&Vec[0]);
//     const __m128d B = _mm_set1_pd(Scalar);
//     const __m128d C = _mm_mul_pd(A, B);
//     _mm_storeu_pd(&Temp[0], C);
//     return Temp;
// }
//
// // double2 / scalar
// ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator/(const TVec<double, 2>& Vec, double Scalar) noexcept
// {
//     TVec<double, 2> Temp;
//     const __m128d A = _mm_loadu_pd(&Vec[0]);
//     const __m128d B = _mm_set1_pd(Scalar);
//     const __m128d C = _mm_div_pd(A, B);
//     _mm_storeu_pd(&Temp[0], C);
//     return Temp;
// }
//
// // double3 * scalar
// ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator*(const TVec<double, 3>& Vec, double Scalar) noexcept
// {
//     TVec<double, 3> Temp;
//     const __m128d S = _mm_set1_pd(Scalar);
//     const __m128d A0 = _mm_loadu_pd(&Vec[0]);
//     const __m128d C0 = _mm_mul_pd(A0, S);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Vec[2]);
//     const __m128d C1 = _mm_mul_pd(A1, S);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // double3 / scalar
// ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator/(const TVec<double, 3>& Vec, double Scalar) noexcept
// {
//     TVec<double, 3> Temp;
//     const __m128d S = _mm_set1_pd(Scalar);
//     const __m128d A0 = _mm_loadu_pd(&Vec[0]);
//     const __m128d C0 = _mm_div_pd(A0, S);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Vec[2]);
//     const __m128d C1 = _mm_div_pd(A1, S);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // double4 * scalar
// ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator*(const TVec<double, 4>& Vec, double Scalar) noexcept
// {
//     TVec<double, 4> Temp;
//     const __m128d S = _mm_set1_pd(Scalar);
//     const __m128d A0 = _mm_loadu_pd(&Vec[0]);
//     const __m128d C0 = _mm_mul_pd(A0, S);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Vec[2]);
//     const __m128d C1 = _mm_mul_pd(A1, S);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// // double4 / scalar
// ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator/(const TVec<double, 4>& Vec, double Scalar) noexcept
// {
//     TVec<double, 4> Temp;
//     const __m128d S = _mm_set1_pd(Scalar);
//     const __m128d A0 = _mm_loadu_pd(&Vec[0]);
//     const __m128d C0 = _mm_div_pd(A0, S);
//     _mm_storeu_pd(&Temp[0], C0);
//
//     const __m128d A1 = _mm_loadu_pd(&Vec[2]);
//     const __m128d C1 = _mm_div_pd(A1, S);
//     _mm_storeu_pd(&Temp[2], C1);
//     return Temp;
// }
//
// #pragma endregion
//
// #endif
//
// }
