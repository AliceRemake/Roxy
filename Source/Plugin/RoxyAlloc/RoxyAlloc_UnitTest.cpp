#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyLog.h>
#include <RoxyAlloc.h>
#include <RoxyChrono.h>

using namespace Roxy::Alloc;

TEST_CASE("Roxy::Alloc::FAlignAllocator")
{
    FAlignAllocator Allocator;

    SUBCASE("Allocate/DeAllocate")
    {
        Byte* Ptr = Allocator.Allocate(64);
        CHECK(Ptr != nullptr);
        Allocator.DeAllocate(Ptr);
    }

    SUBCASE("Alignment")
    {
        for (const auto Align : {8, 16, 32, 64, 128})
        {
            Byte* Ptr = Allocator.Allocate(Align * 2, Align);
            CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % Align == 0));
            Allocator.DeAllocate(Ptr);
        }
    }

    SUBCASE("Alignment(sizeof(FMaxAlign))")
    {
        Byte* Ptr = Allocator.Allocate(128);
        CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % alignof(std::max_align_t) == 0));
        Allocator.DeAllocate(Ptr);
    }

    SUBCASE("Multi Allocate/DeAllocate")
    {
        constexpr auto N { 128 };
        TArray<Byte*> Ptrs {}; Ptrs.reserve(N);
        for (int Idx = 0; Idx < N; ++Idx)
        {
            Byte* Ptr = Allocator.Allocate((Idx + 1) * 8);
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
        Byte* Ptr = Allocator.Allocate(BigBytes);
        CHECK(Ptr != nullptr);
        Allocator.DeAllocate(Ptr);
    }

    SUBCASE("Different Bytes/Align")
    {
        {
            Byte* Ptr = Allocator.Allocate(1, 16);
            CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % 16 == 0));
            Allocator.DeAllocate(Ptr);
        } {
            Byte* Ptr = Allocator.Allocate(64, 32);
            CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % 32 == 0));
            Allocator.DeAllocate(Ptr);
        }
    }
}

TEST_CASE("Roxy::Alloc::FArenaAllocator")
{
    Roxy::Log::SetPattern(Roxy::Log::DefaultPattern);

    constexpr auto Capacity = 1024 * 1024;

    SUBCASE("Allocate/Rewind")
    {
        FArenaAllocator Arena(Capacity);
        Byte* Ptr1 = Arena.Allocate(64);
        REQUIRE(Ptr1 != nullptr);
        Byte* Ptr2 = Arena.Allocate(128);
        REQUIRE(Ptr2 != nullptr);
        CHECK(Ptr1 != Ptr2);

        Arena.Rewind();
        Byte* Ptr3 = Arena.Allocate(64);
        REQUIRE(Ptr3 != nullptr);
        CHECK(Ptr3 == Ptr1);
    }

    SUBCASE("Allocate Failed")
    {
        constexpr auto SmallCapacity = 1024;
        FArenaAllocator Arena(SmallCapacity);

        Byte* Ptr1 = Arena.Allocate(1000);
        REQUIRE(Ptr1 != nullptr);

        Byte* Ptr2 = Arena.Allocate(100);
        CHECK(Ptr2 == nullptr);

        Arena.Rewind();
        Byte* Ptr3 = Arena.Allocate(1000);
        REQUIRE(Ptr3 != nullptr);
    }

    SUBCASE("Alignment")
    {
        FArenaAllocator Arena(Capacity);

        for (const auto Align : {8, 16, 32, 64, 128})
        {
            Byte* Ptr = Arena.Allocate(Align * 2, Align);
            REQUIRE(Ptr != nullptr);
            CHECK(reinterpret_cast<uintptr_t>(Ptr) % Align == 0);
        }

        Byte* Ptr = Arena.Allocate(128);
        REQUIRE(Ptr != nullptr);
        CHECK(reinterpret_cast<uintptr_t>(Ptr) % alignof(std::max_align_t) == 0);
    }

    SUBCASE("Rewind")
    {
        constexpr auto ArenaSize = 2048;
        FArenaAllocator Arena(ArenaSize);

        Byte* Ptr1 = Arena.Allocate(200);
        REQUIRE(Ptr1 != nullptr);
        Byte* Ptr2 = Arena.Allocate(300);
        REQUIRE(Ptr2 != nullptr);
        Byte* Ptr3 = Arena.Allocate(400);
        REQUIRE(Ptr3 != nullptr);

        Arena.Rewind(Ptr2);
        Byte* Ptr4 = Arena.Allocate(300);
        REQUIRE(Ptr4 != nullptr);
        CHECK(Ptr4 == Ptr2);

        Byte* Ptr5 = Arena.Allocate(400);
        REQUIRE(Ptr5 != nullptr);
        CHECK(Ptr5 == Ptr3);
    }

    SUBCASE("DeAllocate(no-op)")
    {
        FArenaAllocator Arena(1024);
        Byte* Ptr1 = Arena.Allocate(100);
        REQUIRE(Ptr1 != nullptr);
        Byte* Ptr2 = Arena.Allocate(100);
        REQUIRE(Ptr2 != nullptr);

        Arena.DeAllocate(Ptr1);
        Byte* Ptr3 = Arena.Allocate(100);
        REQUIRE(Ptr3 != nullptr);
        CHECK(Ptr3 > Ptr2);

        Arena.DeAllocate(nullptr);
    }

    SUBCASE("Move")
    {
        FArenaAllocator Arena1(1024);
        Byte* Ptr1 = Arena1.Allocate(100);
        REQUIRE(Ptr1 != nullptr);

        FArenaAllocator Arena2(std::move(Arena1));
        Byte* Ptr2 = Arena2.Allocate(200);
        REQUIRE(Ptr2 != nullptr);
        CHECK(Ptr2 > Ptr1);

        FArenaAllocator Arena3(512);
        Arena3 = std::move(Arena2);
        Byte* Ptr3 = Arena3.Allocate(300);
        REQUIRE(Ptr3 != nullptr);
        CHECK(Ptr3 > Ptr2);
    }

    SUBCASE("Multiple Allocate")
    {
        FArenaAllocator Arena(Capacity);
        constexpr auto N { 256 };
        TArray<Byte*> Ptrs {};
        Ptrs.reserve(N);

        for (int Idx = 0; Idx < N; ++Idx)
        {
            UIntPtr Size = (Idx + 1) * 16;
            Byte* Ptr = Arena.Allocate(Size);
            REQUIRE(Ptr != nullptr);
            Ptrs.push_back(Ptr);
        }

        for (int Idx = 1; Idx < N; ++Idx)
        {
            CHECK(Ptrs[Idx] > Ptrs[Idx - 1]);
        }

        Arena.Rewind();
        Byte* NewPtr = Arena.Allocate(64);
        REQUIRE(NewPtr != nullptr);
        CHECK(NewPtr == Ptrs[0]);
    }
}

TEST_CASE("Roxy::Alloc::Benchmark FAlignAllocator vs FArenaAllocator")
{
    Roxy::Log::SetPattern(Roxy::Log::DefaultPattern);

    constexpr int NumAllocs    = 100000;
    constexpr UIntPtr AllocSize = 64;
    constexpr UIntPtr ArenaCap  = AllocSize * NumAllocs + 4096;
    constexpr int WarmupRounds  = 3;
    constexpr int MeasureRounds = 5;

    #define PRINT_TIME(Label, ValueMs) \
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "{:<40}: {:.3f} ms", Label, (ValueMs))

    ROXY_INFO(Roxy::Log::ELogCategory::Default, "{}", "=== Allocator Benchmark ===");
    ROXY_INFO(Roxy::Log::ELogCategory::Default, "Allocations: {} x {} bytes each", NumAllocs, AllocSize);

    FAlignAllocator AlignAlloc;
    FArenaAllocator ArenaAlloc(ArenaCap);

    // ---- FAlignAllocator: Allocate + DeAllocate ----
    {
        double TotalMs = 0.0;
        for (int round = 0; round < WarmupRounds + MeasureRounds; ++round)
        {
            Roxy::Chrono::FTimer Timer;
            for (int i = 0; i < NumAllocs; ++i)
            {
                Byte* p = AlignAlloc.Allocate(AllocSize);
                AlignAlloc.DeAllocate(p);
            }
            const double Ms = Timer.GetElapsed<Roxy::Chrono::ETimeUnit::MiS>();
            if (round >= WarmupRounds) TotalMs += Ms;
        }
        PRINT_TIME("FAlignAllocator (alloc+dealloc)", TotalMs / MeasureRounds);
    }

    // ---- FArenaAllocator: Allocate only (no dealloc, use Rewind) ----
    {
        double TotalMs = 0.0;
        for (int round = 0; round < WarmupRounds + MeasureRounds; ++round)
        {
            ArenaAlloc.Rewind();
            Roxy::Chrono::FTimer Timer;
            for (int i = 0; i < NumAllocs; ++i)
            {
                Byte* p = ArenaAlloc.Allocate(AllocSize);
                REQUIRE(p != nullptr);
            }
            const double Ms = Timer.GetElapsed<Roxy::Chrono::ETimeUnit::MiS>();
            if (round >= WarmupRounds) TotalMs += Ms;
        }
        PRINT_TIME("FArenaAllocator (alloc only)", TotalMs / MeasureRounds);
    }

    // ---- FArenaAllocator: Allocate + Rewind each iteration ----
    {
        // Ensure arena starts empty (fix: previous subcase may have left it exhausted)
        ArenaAlloc.Rewind();
        double TotalMs = 0.0;
        for (int round = 0; round < WarmupRounds + MeasureRounds; ++round)
        {
            Roxy::Chrono::FTimer Timer;
            for (int i = 0; i < NumAllocs; ++i)
            {
                Byte* p = ArenaAlloc.Allocate(AllocSize);
                REQUIRE(p != nullptr);
            }
            ArenaAlloc.Rewind();
            const double Ms = Timer.GetElapsed<Roxy::Chrono::ETimeUnit::MiS>();
            if (round >= WarmupRounds) TotalMs += Ms;
        }
        PRINT_TIME("FArenaAllocator (alloc+rewind loop)", TotalMs / MeasureRounds);
    }

    SUBCASE("Large allocation stress")
    {
        constexpr UIntPtr LargeSize = 10 * 1024 * 1024; // 10 MiB
        {
            Roxy::Chrono::FTimer Timer;
            Byte* p = AlignAlloc.Allocate(LargeSize);
            REQUIRE(p != nullptr);
            AlignAlloc.DeAllocate(p);
            PRINT_TIME("FAlignAllocator (10 MiB single)", Timer.GetElapsed<Roxy::Chrono::ETimeUnit::MiS>());
        }
        FArenaAllocator LargeArena(LargeSize + 1024);
        {
            Roxy::Chrono::FTimer Timer;
            Byte* p = LargeArena.Allocate(LargeSize);
            REQUIRE(p != nullptr);
            PRINT_TIME("FArenaAllocator (10 MiB single)", Timer.GetElapsed<Roxy::Chrono::ETimeUnit::MiS>());
        }
    }

    #undef PRINT_TIME
}
