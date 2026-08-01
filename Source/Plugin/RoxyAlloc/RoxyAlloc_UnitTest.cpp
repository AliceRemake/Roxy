#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyAlloc.h>

using namespace Roxy::Alloc;

TEST_CASE("Roxy::Alloc::FStdAllocator")
{
    FStdAllocator Allocator;

    SUBCASE("Allocate/DeAllocate")
    {
        void* Ptr = Allocator.Allocate(64);
        CHECK(Ptr != nullptr);
        Allocator.DeAllocate(Ptr);
    }

    SUBCASE("Allocate(0)/DeAllocate(nullptr)")
    {
        void* Ptr = Allocator.Allocate(0);
        CHECK(Ptr == nullptr);
        Allocator.DeAllocate(Ptr);
    }

    SUBCASE("Alignment")
    {
        for (const auto Align : {8, 16, 32, 64, 128})
        {
            void* Ptr = Allocator.Allocate(Align * 2, Align);
            CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % Align == 0));
            Allocator.DeAllocate(Ptr);
        }
    }

    SUBCASE("Alignment(sizeof(FMaxAlign))")
    {
        void* Ptr = Allocator.Allocate(128);
        CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % alignof(std::max_align_t) == 0));
        Allocator.DeAllocate(Ptr);
    }

    SUBCASE("Multi Allocate/DeAllocate")
    {
        constexpr auto N { 128 };
        TArray<void*> Ptrs {}; Ptrs.reserve(N);
        for (int Idx = 0; Idx < N; ++Idx)
        {
            void* Ptr = Allocator.Allocate((Idx + 1) * 8);
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
        void* Ptr = Allocator.Allocate(BigBytes);
        CHECK(Ptr != nullptr);
        Allocator.DeAllocate(Ptr);
    }

    SUBCASE("Different Bytes/Align")
    {
        {
            void* Ptr = Allocator.Allocate(1, 16);
            CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % 16 == 0));
            Allocator.DeAllocate(Ptr);
        } {
            void* Ptr = Allocator.Allocate(64, 32);
            CHECK((Ptr != nullptr && reinterpret_cast<uintptr_t>(Ptr) % 32 == 0));
            Allocator.DeAllocate(Ptr);
        }
    }
}
