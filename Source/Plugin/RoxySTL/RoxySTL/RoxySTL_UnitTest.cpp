#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <algorithm>
#include <type_traits>
#include <utility>

#include <RoxySTL/RoxySTL.h>
#include <RoxyMath/RoxyMath.h>

using namespace Roxy;
using namespace Roxy::Math;

TEST_CASE("Roxy::STL")
{
    SUBCASE("FixArray")
    {
        {
            constexpr FixArray<F32, 4> Array{};
            static_assert(Array.Size() == 4);
            static_assert(Array[0] == 0);
            static_assert(Array[1] == 0);
            static_assert(Array[2] == 0);
            static_assert(Array[3] == 0);
            CHECK(Array.Size() == 4);
            CHECK(Array[0] == 0);
            CHECK(Array[1] == 0);
            CHECK(Array[2] == 0);
            CHECK(Array[3] == 0);
        }
        {
            constexpr FixArray<F64, 4> Array{};
            static_assert(Array.Size() == 4);
            static_assert(Array[0] == 0);
            static_assert(Array[1] == 0);
            static_assert(Array[2] == 0);
            static_assert(Array[3] == 0);
            CHECK(Array.Size() == 4);
            CHECK(Array[0] == 0);
            CHECK(Array[1] == 0);
            CHECK(Array[2] == 0);
            CHECK(Array[3] == 0);
        }
        {
            constexpr FixArray<FVec4, 4> Array{};
            static_assert(Array.Size() == 4);
            static_assert(Array[0] == FVec4{});
            static_assert(Array[1] == FVec4{});
            static_assert(Array[2] == FVec4{});
            static_assert(Array[3] == FVec4{});
            CHECK(Array.Size() == 4);
            CHECK(Array[0] == FVec4{});
            CHECK(Array[1] == FVec4{});
            CHECK(Array[2] == FVec4{});
            CHECK(Array[3] == FVec4{});
        }
        {
            constexpr FixArray<F32, 4> Array{1.f, 2.f, 3.f};
            static_assert(Array[0] == 1.f);
            static_assert(Array[1] == 2.f);
            static_assert(Array[2] == 3.f);
            static_assert(Array[3] == 0.f);
            CHECK(Array[0] == 1.f);
            CHECK(Array[1] == 2.f);
            CHECK(Array[2] == 3.f);
            CHECK(Array[3] == 0.f);
        }
        {
            constexpr FixArray<F32, 4> Array{1.f, 2.f, 3.f, 4.f};
            static_assert(Array[0] + Array[1] + Array[2] + Array[3] == 10.f);
            CHECK(Array[3] == 4.f);
        }
        {
            constexpr FixArray<F64, 3> Array{1.5, 2.5, 3.5};
            static_assert(Array[0] + Array[1] + Array[2] == 7.5);
            CHECK(Array[0] == 1.5);
            CHECK(Array[2] == 3.5);
        }
        {
            constexpr FixArray<FVec4, 2> Array{FVec4{1.f, 2.f, 3.f, 4.f}, FVec4{5.f, 6.f, 7.f, 8.f}};
            static_assert(Array[0] == FVec4{1.f, 2.f, 3.f, 4.f});
            static_assert(Array[1] == FVec4{5.f, 6.f, 7.f, 8.f});
            CHECK(Array[0] == FVec4{1.f, 2.f, 3.f, 4.f});
            CHECK(Array[1] == FVec4{5.f, 6.f, 7.f, 8.f});
        }
        {
            FixArray<F32, 4> Array{};
            Array[0] = 5.f;
            Array[1] = 6.f;
            CHECK(Array[0] == 5.f);
            CHECK(Array[1] == 6.f);
            CHECK(Array[2] == 0.f);
            Array[2] = Array[0] + Array[1];
            CHECK(Array[2] == 11.f);
        }
        {
            static_assert(std::is_same_v<decltype(std::declval<FixArray<F32, 4>&>()[0]), F32&>);
            static_assert(std::is_same_v<decltype(std::declval<const FixArray<F32, 4>&>()[0]), F32>);
            static_assert(std::is_same_v<decltype(std::declval<const FixArray<F64, 4>&>()[0]), F64>);
            static_assert(std::is_same_v<decltype(std::declval<const FixArray<FVec4, 2>&>()[0]), const FVec4&>);
            static_assert(std::is_same_v<decltype(std::declval<const FixArray<FString, 2>&>()[0]), const FString&>);
        }
        {
            constexpr FixArray<F32, 4> Array{1.f, 2.f, 3.f, 4.f};
            F32 Sum = 0.f;
            for (const auto& V : Array) { Sum += V; }
            CHECK(Sum == 10.f);
        }
        {
            FixArray<F32, 4> Array{1.f, 2.f, 3.f, 4.f};
            for (auto& V : Array) { V *= 2.f; }
            CHECK(Array[0] == 2.f);
            CHECK(Array[1] == 4.f);
            CHECK(Array[2] == 6.f);
            CHECK(Array[3] == 8.f);
        }
        {
            FixArray<F32, 4> Array{4.f, 2.f, 3.f, 1.f};
            std::ranges::sort(Array);
            CHECK(Array[0] == 1.f);
            CHECK(Array[1] == 2.f);
            CHECK(Array[2] == 3.f);
            CHECK(Array[3] == 4.f);
        }
        {
            FixArray<F32, 4> A{1.f, 2.f, 3.f, 4.f};
            FixArray<F32, 4> B = A;
            CHECK(B[0] == 1.f);
            B[0] = 9.f;
            CHECK(A[0] == 1.f);
            FixArray<F32, 4> C = std::move(B);
            CHECK(C[0] == 9.f);
            A = C;
            CHECK(A[0] == 9.f);
        }
        {
            FixArray<FString, 2> Array{"hello", "world"};
            CHECK(Array[0] == "hello");
            CHECK(Array[1] == "world");
            FString Concat;
            for (const auto& S : Array) { Concat += S; }
            CHECK(Concat == "helloworld");
        }
        {
            static_assert(std::is_trivial_v<FixArray<F32, 4>>);
            static_assert(std::is_trivial_v<FixArray<F64, 4>>);
            static_assert(std::is_trivial_v<FixArray<FVec4, 4>>);
        }
    }
}
