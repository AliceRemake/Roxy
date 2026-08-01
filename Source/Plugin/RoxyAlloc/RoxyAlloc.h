#pragma once

#include <RoxySTD.h>

namespace Roxy::Alloc
{

template<typename T>
concept CAllocator = requires (T Allocator, void* Ptr, UInt64 Bytes, UInt64 Align)
{
    { Allocator.Allocate(Bytes, Align) } noexcept -> std::same_as<void*>;
    { Allocator.DeAllocate(Ptr)        } noexcept -> std::same_as<void>;
};

class FStdAllocator
{
public:
    static void* Allocate(UInt64 Bytes, UInt64 Align = alignof(FMaxAlign)) noexcept;

    static void DeAllocate(void* Ptr) noexcept;
};

static_assert(CAllocator<FStdAllocator>);

}
