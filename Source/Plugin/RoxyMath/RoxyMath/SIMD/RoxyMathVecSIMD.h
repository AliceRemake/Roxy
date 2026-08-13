#pragma once

#if ROXY_IS_MSVC
#include <intrin.h>
#else
#include <xmmintrin.h>
#endif

#include <RoxyMath/RoxyMathVec.h>

namespace Roxy::Math
{
#if ROXY_ENABLE_SIMD

// float3 add
ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator+(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
{
    TVec<float, 3> Temp;
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
    const __m128 C = _mm_add_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// float3 sub
ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator-(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
{
    TVec<float, 3> Temp;
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
    const __m128 C = _mm_sub_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// float3 Mul
ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator*(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
{
    TVec<float, 3> Temp;
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
    const __m128 C = _mm_mul_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// float3 div
ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator/(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
{
    TVec<float, 3> Temp;
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
    const __m128 C = _mm_div_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// float4 add
ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator+(const TVec<float, 4>& Lhs, const TVec<float, 4>& Rhs) noexcept
{
    TVec<float, 4> Temp;
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
    const __m128 C = _mm_add_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// float4 sub
ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator-(const TVec<float, 4>& Lhs, const TVec<float, 4>& Rhs) noexcept
{
    TVec<float, 4> Temp;
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
    const __m128 C = _mm_sub_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// float4 Mul
ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator*(const TVec<float, 4>& Lhs, const TVec<float, 4>& Rhs) noexcept
{
    TVec<float, 4> Temp;
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
    const __m128 C = _mm_mul_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// float4 div
ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator/(const TVec<float, 4>& Lhs, const TVec<float, 4>& Rhs) noexcept
{
    TVec<float, 4> Temp;
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
    const __m128 C = _mm_div_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// double2 add
ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator+(const TVec<double, 2>& Lhs, const TVec<double, 2>& Rhs) noexcept
{
    TVec<double, 2> Temp;
    const __m128d A = _mm_loadu_pd(&Lhs[0]);
    const __m128d B = _mm_loadu_pd(&Rhs[0]);
    const __m128d C = _mm_add_pd(A, B);
    _mm_storeu_pd(&Temp[0], C);
    return Temp;
}

// double2 sub
ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator-(const TVec<double, 2>& Lhs, const TVec<double, 2>& Rhs) noexcept
{
    TVec<double, 2> Temp;
    const __m128d A = _mm_loadu_pd(&Lhs[0]);
    const __m128d B = _mm_loadu_pd(&Rhs[0]);
    const __m128d C = _mm_sub_pd(A, B);
    _mm_storeu_pd(&Temp[0], C);
    return Temp;
}

// double2 Mul
ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator*(const TVec<double, 2>& Lhs, const TVec<double, 2>& Rhs) noexcept
{
    TVec<double, 2> Temp;
    const __m128d A = _mm_loadu_pd(&Lhs[0]);
    const __m128d B = _mm_loadu_pd(&Rhs[0]);
    const __m128d C = _mm_mul_pd(A, B);
    _mm_storeu_pd(&Temp[0], C);
    return Temp;
}

// double2 div
ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator/(const TVec<double, 2>& Lhs, const TVec<double, 2>& Rhs) noexcept
{
    TVec<double, 2> Temp;
    const __m128d A = _mm_loadu_pd(&Lhs[0]);
    const __m128d B = _mm_loadu_pd(&Rhs[0]);
    const __m128d C = _mm_div_pd(A, B);
    _mm_storeu_pd(&Temp[0], C);
    return Temp;
}

// double3 add
ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator+(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
{
    TVec<double, 3> Temp;
    const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
    const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
    const __m128d C0 = _mm_add_pd(A0, B0);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
    const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
    const __m128d C1 = _mm_add_pd(A1, B1);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// double3 sub
ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator-(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
{
    TVec<double, 3> Temp;
    const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
    const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
    const __m128d C0 = _mm_sub_pd(A0, B0);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
    const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
    const __m128d C1 = _mm_sub_pd(A1, B1);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// double3 Mul
ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator*(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
{
    TVec<double, 3> Temp;
    const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
    const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
    const __m128d C0 = _mm_mul_pd(A0, B0);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
    const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
    const __m128d C1 = _mm_mul_pd(A1, B1);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// double3 div
ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator/(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
{
    TVec<double, 3> Temp;
    const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
    const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
    const __m128d C0 = _mm_div_pd(A0, B0);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
    const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
    const __m128d C1 = _mm_div_pd(A1, B1);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// double4 add
ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator+(const TVec<double, 4>& Lhs, const TVec<double, 4>& Rhs) noexcept
{
    TVec<double, 4> Temp;
    const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
    const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
    const __m128d C0 = _mm_add_pd(A0, B0);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
    const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
    const __m128d C1 = _mm_add_pd(A1, B1);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// double4 sub
ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator-(const TVec<double, 4>& Lhs, const TVec<double, 4>& Rhs) noexcept
{
    TVec<double, 4> Temp;
    const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
    const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
    const __m128d C0 = _mm_sub_pd(A0, B0);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
    const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
    const __m128d C1 = _mm_sub_pd(A1, B1);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// double4 Mul
ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator*(const TVec<double, 4>& Lhs, const TVec<double, 4>& Rhs) noexcept
{
    TVec<double, 4> Temp;
    const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
    const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
    const __m128d C0 = _mm_mul_pd(A0, B0);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
    const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
    const __m128d C1 = _mm_mul_pd(A1, B1);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// double4 div
ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator/(const TVec<double, 4>& Lhs, const TVec<double, 4>& Rhs) noexcept
{
    TVec<double, 4> Temp;
    const __m128d A0 = _mm_loadu_pd(&Lhs[0]);
    const __m128d B0 = _mm_loadu_pd(&Rhs[0]);
    const __m128d C0 = _mm_div_pd(A0, B0);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Lhs[2]);
    const __m128d B1 = _mm_loadu_pd(&Rhs[2]);
    const __m128d C1 = _mm_div_pd(A1, B1);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// float3 dot
ROXY_NODISCARD ROXY_INLINE float Dot(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
{
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
#if defined(__FMA__) || defined(__AVX2__)
    const __m128 Mul   = _mm_mul_ps(A, B);
    const __m128 Mask  = _mm_insert_ps(Mul, _mm_setzero_ps(), 0x30);
    const __m128 Shuf  = _mm_permute_ps(Mask, _MM_SHUFFLE(1, 0, 3, 2));
    const __m128 Sum   = _mm_add_ps(Mask, Shuf);
    const __m128 Shuf2 = _mm_permute_ps(Sum, _MM_SHUFFLE(2, 3, 0, 1));
    return _mm_cvtss_f32(_mm_add_ps(Sum, Shuf2));
#else
    const __m128 Mul  = _mm_mul_ps(A, B);
    const __m128 Mask = _mm_insert_ps(Mul, _mm_setzero_ps(), 0x30);
    const __m128 HAdd = _mm_hadd_ps(Mask, Mask);
    const __m128 Sum  = _mm_hadd_ps(HAdd, HAdd);
    return _mm_cvtss_f32(Sum);
#endif
}

// float4 dot
ROXY_NODISCARD ROXY_INLINE float Dot(const TVec<float, 4>& Lhs, const TVec<float, 4>& Rhs) noexcept
{
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
#if defined(__FMA__) || defined(__AVX2__)
    const __m128 Mul = _mm_mul_ps(A, B);
    const __m128 Shuf = _mm_permute_ps(Mul, _MM_SHUFFLE(1, 0, 3, 2));
    __m128 Sum = _mm_add_ps(Mul, Shuf);
    const __m128 Shuf2 = _mm_permute_ps(Sum, _MM_SHUFFLE(2, 3, 0, 1));
    Sum = _mm_add_ps(Sum, Shuf2);
    return _mm_cvtss_f32(Sum);
#else
    const __m128 Mul = _mm_mul_ps(A, B);
    const __m128 HAdd = _mm_hadd_ps(Mul, Mul);
    const __m128 Sum = _mm_hadd_ps(HAdd, HAdd);
    return _mm_cvtss_f32(Sum);
#endif
}

// double2 dot
ROXY_NODISCARD ROXY_INLINE double Dot(const TVec<double, 2>& Lhs, const TVec<double, 2>& Rhs) noexcept
{
    const __m128d A    = _mm_loadu_pd(&Lhs[0]);
    const __m128d B    = _mm_loadu_pd(&Rhs[0]);
    const __m128d Mul  = _mm_mul_pd(A, B);
    const __m128d HAdd = _mm_hadd_pd(Mul, Mul);
    return _mm_cvtsd_f64(HAdd);
}

// double3 dot
ROXY_NODISCARD ROXY_INLINE double Dot(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
{
    const __m128d A0  = _mm_loadu_pd(&Lhs[0]);
    const __m128d B0  = _mm_loadu_pd(&Rhs[0]);
    const __m128d Mul = _mm_mul_pd(A0, B0);
    const __m128d Sum = _mm_add_sd(Mul, _mm_unpackhi_pd(Mul, Mul));
    return _mm_cvtsd_f64(Sum) + Lhs[2] * Rhs[2];
}

// double4 dot
ROXY_NODISCARD ROXY_INLINE double Dot(const TVec<double, 4>& Lhs, const TVec<double, 4>& Rhs) noexcept
{
    const __m128d A0   = _mm_loadu_pd(&Lhs[0]);
    const __m128d B0   = _mm_loadu_pd(&Rhs[0]);
    const __m128d Mul0 = _mm_mul_pd(A0, B0);
    const __m128d A1   = _mm_loadu_pd(&Lhs[2]);
    const __m128d B1   = _mm_loadu_pd(&Rhs[2]);
    const __m128d Mul1 = _mm_mul_pd(A1, B1);
    const __m128d Sum  = _mm_add_pd(Mul0, Mul1);
    const __m128d HAdd = _mm_hadd_pd(Sum, Sum);
    return _mm_cvtsd_f64(HAdd);
}

// float3 cross
ROXY_NODISCARD ROXY_INLINE TVec<float, 3> Cross(const TVec<float, 3>& Lhs, const TVec<float, 3>& Rhs) noexcept
{
    const __m128 A = _mm_loadu_ps(&Lhs[0]);
    const __m128 B = _mm_loadu_ps(&Rhs[0]);
    const __m128 A_YZX = _mm_shuffle_ps(A, A, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 B_YZX = _mm_shuffle_ps(B, B, _MM_SHUFFLE(3, 0, 2, 1));
    const __m128 A_ZXY = _mm_shuffle_ps(A, A, _MM_SHUFFLE(3, 1, 0, 2));
    const __m128 B_ZXY = _mm_shuffle_ps(B, B, _MM_SHUFFLE(3, 1, 0, 2));
#if defined(__FMA__) || defined(__AVX2__)
    const __m128 Cross = _mm_fmsub_ps(A_YZX, B_ZXY, _mm_mul_ps(A_ZXY, B_YZX));
#else
    const __m128 Cross = _mm_sub_ps(_mm_mul_ps(A_YZX, B_ZXY), _mm_mul_ps(A_ZXY, B_YZX));
#endif
    const __m128 Result = _mm_insert_ps(Cross, _mm_setzero_ps(), 0x30);
    TVec<float, 3> Temp;
    _mm_storeu_ps(&Temp[0], Result);
    return Temp;
}

// double3 cross
ROXY_NODISCARD ROXY_INLINE TVec<double, 3> Cross(const TVec<double, 3>& Lhs, const TVec<double, 3>& Rhs) noexcept
{
    const double A0 = Lhs[0], A1 = Lhs[1], A2 = Lhs[2];
    const double B0 = Rhs[0], B1 = Rhs[1], B2 = Rhs[2];
    TVec<double, 3> Temp;
    Temp[0] = A1 * B2 - A2 * B1;
    Temp[1] = A2 * B0 - A0 * B2;
    Temp[2] = A0 * B1 - A1 * B0;
    return Temp;
}

// float3 * scalar
ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator*(const TVec<float, 3>& Vec, float Scalar) noexcept
{
    TVec<float, 3> Temp;
    const __m128 A = _mm_loadu_ps(&Vec[0]);
    const __m128 B = _mm_set1_ps(Scalar);
    const __m128 C = _mm_mul_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// float3 / scalar
ROXY_NODISCARD ROXY_INLINE TVec<float, 3> operator/(const TVec<float, 3>& Vec, float Scalar) noexcept
{
    TVec<float, 3> Temp;
    const __m128 A = _mm_loadu_ps(&Vec[0]);
    const __m128 B = _mm_set1_ps(Scalar);
    const __m128 C = _mm_div_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// float4 * scalar
ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator*(const TVec<float, 4>& Vec, float Scalar) noexcept
{
    TVec<float, 4> Temp;
    const __m128 A = _mm_loadu_ps(&Vec[0]);
    const __m128 B = _mm_set1_ps(Scalar);
    const __m128 C = _mm_mul_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// float4 / scalar
ROXY_NODISCARD ROXY_INLINE TVec<float, 4> operator/(const TVec<float, 4>& Vec, float Scalar) noexcept
{
    TVec<float, 4> Temp;
    const __m128 A = _mm_loadu_ps(&Vec[0]);
    const __m128 B = _mm_set1_ps(Scalar);
    const __m128 C = _mm_div_ps(A, B);
    _mm_storeu_ps(&Temp[0], C);
    return Temp;
}

// double2 * scalar
ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator*(const TVec<double, 2>& Vec, double Scalar) noexcept
{
    TVec<double, 2> Temp;
    const __m128d A = _mm_loadu_pd(&Vec[0]);
    const __m128d B = _mm_set1_pd(Scalar);
    const __m128d C = _mm_mul_pd(A, B);
    _mm_storeu_pd(&Temp[0], C);
    return Temp;
}

// double2 / scalar
ROXY_NODISCARD ROXY_INLINE TVec<double, 2> operator/(const TVec<double, 2>& Vec, double Scalar) noexcept
{
    TVec<double, 2> Temp;
    const __m128d A = _mm_loadu_pd(&Vec[0]);
    const __m128d B = _mm_set1_pd(Scalar);
    const __m128d C = _mm_div_pd(A, B);
    _mm_storeu_pd(&Temp[0], C);
    return Temp;
}

// double3 * scalar
ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator*(const TVec<double, 3>& Vec, double Scalar) noexcept
{
    TVec<double, 3> Temp;
    const __m128d S = _mm_set1_pd(Scalar);
    const __m128d A0 = _mm_loadu_pd(&Vec[0]);
    const __m128d C0 = _mm_mul_pd(A0, S);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Vec[2]);
    const __m128d C1 = _mm_mul_pd(A1, S);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// double3 / scalar
ROXY_NODISCARD ROXY_INLINE TVec<double, 3> operator/(const TVec<double, 3>& Vec, double Scalar) noexcept
{
    TVec<double, 3> Temp;
    const __m128d S = _mm_set1_pd(Scalar);
    const __m128d A0 = _mm_loadu_pd(&Vec[0]);
    const __m128d C0 = _mm_div_pd(A0, S);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Vec[2]);
    const __m128d C1 = _mm_div_pd(A1, S);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// double4 * scalar
ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator*(const TVec<double, 4>& Vec, double Scalar) noexcept
{
    TVec<double, 4> Temp;
    const __m128d S = _mm_set1_pd(Scalar);
    const __m128d A0 = _mm_loadu_pd(&Vec[0]);
    const __m128d C0 = _mm_mul_pd(A0, S);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Vec[2]);
    const __m128d C1 = _mm_mul_pd(A1, S);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

// double4 / scalar
ROXY_NODISCARD ROXY_INLINE TVec<double, 4> operator/(const TVec<double, 4>& Vec, double Scalar) noexcept
{
    TVec<double, 4> Temp;
    const __m128d S = _mm_set1_pd(Scalar);
    const __m128d A0 = _mm_loadu_pd(&Vec[0]);
    const __m128d C0 = _mm_div_pd(A0, S);
    _mm_storeu_pd(&Temp[0], C0);

    const __m128d A1 = _mm_loadu_pd(&Vec[2]);
    const __m128d C1 = _mm_div_pd(A1, S);
    _mm_storeu_pd(&Temp[2], C1);
    return Temp;
}

#endif
}
