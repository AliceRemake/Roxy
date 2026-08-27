#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyLog/RoxyLog.h>
#include <RoxyAlloc/RoxyAlloc.h>
#include <RoxyChrono/RoxyChrono.h>

using namespace Roxy::Alloc;

TEST_CASE("Roxy::Alloc::FAlignAllocator")
{
    FAlignAllocator Allocator;

    SUBCASE("Allocate/DeAllocate")
    {
        FByte* Ptr = Allocator.Allocate(64);
        CHECK(Ptr != nullptr);
        Allocator.DeAllocate(Ptr);
    }

    SUBCASE("Alignment")
    {
        for (const auto Align : {8, 16, 32, 64, 128})
        {
            FByte* Ptr = Allocator.Allocate(Align * 2, Align);
            CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % Align == 0));
            Allocator.DeAllocate(Ptr);
        }
    }

    SUBCASE("Alignment(sizeof(FMaxAlign))")
    {
        FByte* Ptr = Allocator.Allocate(128);
        CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % alignof(std::max_align_t) == 0));
        Allocator.DeAllocate(Ptr);
    }

    SUBCASE("Multi Allocate/DeAllocate")
    {
        constexpr auto N { 128 };
        TArray<FByte*> Ptrs {}; Ptrs.reserve(N);
        for (int Idx = 0; Idx < N; ++Idx)
        {
            FByte* Ptr = Allocator.Allocate((Idx + 1) * 8);
            CHECK(Ptr != nullptr);
            Ptrs.push_back(Ptr);
        }
        for (auto* p : Ptrs)
        {
            Allocator.DeAllocate(p);
        }
    }

    SUBCASE("Big Allocate/DeAllocate")
    {
        constexpr auto BigBytes { 1024 * 1024 };
        FByte* Ptr = Allocator.Allocate(BigBytes);
        CHECK(Ptr != nullptr);
        Allocator.DeAllocate(Ptr);
    }

    SUBCASE("Different Bytes/Align")
    {
        {
            FByte* Ptr = Allocator.Allocate(1, 16);
            CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % 16 == 0));
            Allocator.DeAllocate(Ptr);
        } {
            FByte* Ptr = Allocator.Allocate(64, 32);
            CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % 32 == 0));
            Allocator.DeAllocate(Ptr);
        }
    }

    SUBCASE("Performance Benchmark")
    {
    }
}

TEST_CASE("Roxy::Alloc::FArenaAllocator")
{
    Roxy::Log::SetPattern(Roxy::Log::DefaultPattern);

    constexpr auto Capacity = 1024 * 1024;

    SUBCASE("Allocate/Rewind")
    {
        FArenaAllocator Arena(Capacity);
        FByte* Ptr1 = Arena.Allocate(64);
        REQUIRE(Ptr1 != nullptr);
        FByte* Ptr2 = Arena.Allocate(128);
        REQUIRE(Ptr2 != nullptr);
        CHECK(Ptr1 != Ptr2);

        Arena.Rewind();
        FByte* Ptr3 = Arena.Allocate(64);
        REQUIRE(Ptr3 != nullptr);
        CHECK(Ptr3 == Ptr1);
    }

    SUBCASE("Allocate Failed")
    {
        constexpr auto SmallCapacity = 1024;
        FArenaAllocator Arena(SmallCapacity);

        FByte* Ptr1 = Arena.Allocate(1000);
        REQUIRE(Ptr1 != nullptr);

        FByte* Ptr2 = Arena.Allocate(100);
        CHECK(Ptr2 == nullptr);

        Arena.Rewind();
        FByte* Ptr3 = Arena.Allocate(1000);
        REQUIRE(Ptr3 != nullptr);
    }

    SUBCASE("Alignment")
    {
        FArenaAllocator Arena(Capacity);

        for (const auto Align : {8, 16, 32, 64, 128})
        {
            FByte* Ptr = Arena.Allocate(Align * 2, Align);
            REQUIRE(Ptr != nullptr);
            CHECK(reinterpret_cast<uintptr_t>(Ptr) % Align == 0);
        }

        FByte* Ptr = Arena.Allocate(128);
        REQUIRE(Ptr != nullptr);
        CHECK(reinterpret_cast<uintptr_t>(Ptr) % alignof(std::max_align_t) == 0);
    }

    SUBCASE("Rewind")
    {
        constexpr auto ArenaSize = 2048;
        FArenaAllocator Arena(ArenaSize);

        FByte* Ptr1 = Arena.Allocate(200);
        REQUIRE(Ptr1 != nullptr);
        FByte* Ptr2 = Arena.Allocate(300);
        REQUIRE(Ptr2 != nullptr);
        FByte* Ptr3 = Arena.Allocate(400);
        REQUIRE(Ptr3 != nullptr);

        Arena.Rewind(Ptr2);
        FByte* Ptr4 = Arena.Allocate(300);
        REQUIRE(Ptr4 != nullptr);
        CHECK(Ptr4 == Ptr2);

        FByte* Ptr5 = Arena.Allocate(400);
        REQUIRE(Ptr5 != nullptr);
        CHECK(Ptr5 == Ptr3);
    }

    SUBCASE("DeAllocate(no-op)")
    {
        FArenaAllocator Arena(1024);
        FByte* Ptr1 = Arena.Allocate(100);
        REQUIRE(Ptr1 != nullptr);
        FByte* Ptr2 = Arena.Allocate(100);
        REQUIRE(Ptr2 != nullptr);

        Arena.DeAllocate(Ptr1);
        FByte* Ptr3 = Arena.Allocate(100);
        REQUIRE(Ptr3 != nullptr);
        CHECK(Ptr3 > Ptr2);

        Arena.DeAllocate(nullptr);
    }

    SUBCASE("Move")
    {
        FArenaAllocator Arena1(1024);
        FByte* Ptr1 = Arena1.Allocate(100);
        REQUIRE(Ptr1 != nullptr);

        FArenaAllocator Arena2(std::move(Arena1));
        FByte* Ptr2 = Arena2.Allocate(200);
        REQUIRE(Ptr2 != nullptr);
        CHECK(Ptr2 > Ptr1);

        FArenaAllocator Arena3(512);
        Arena3 = std::move(Arena2);
        FByte* Ptr3 = Arena3.Allocate(300);
        REQUIRE(Ptr3 != nullptr);
        CHECK(Ptr3 > Ptr2);
    }

    SUBCASE("Multiple Allocate")
    {
        FArenaAllocator Arena(Capacity);
        constexpr auto N { 256 };
        TArray<FByte*> Ptrs {};
        Ptrs.reserve(N);

        for (int Idx = 0; Idx < N; ++Idx)
        {
            UIntPtr Size = (Idx + 1) * 16;
            FByte* Ptr = Arena.Allocate(Size);
            REQUIRE(Ptr != nullptr);
            Ptrs.push_back(Ptr);
        }

        for (int Idx = 1; Idx < N; ++Idx)
        {
            CHECK(Ptrs[Idx] > Ptrs[Idx - 1]);
        }

        Arena.Rewind();
        FByte* NewPtr = Arena.Allocate(64);
        REQUIRE(NewPtr != nullptr);
        CHECK(NewPtr == Ptrs[0]);
    }

    SUBCASE("Performance Benchmark")
    {
    }
}
