// ReSharper disable CppMemberFunctionMayBeStatic
// ReSharper disable CppClangTidyMiscUseInternalLinkage
#include "RoxyAlloc.h"

#include <RoxyLog/RoxyLog.h>

namespace Roxy::Alloc
{

FByte* FAlignAllocator::Allocate(const UIntPtr Bytes, const UIntPtr Align) const noexcept
{
    ROXY_ASSERT(!!Bytes && "Can Not Allocate 0 Bytes Of Memory");
#if ROXY_IS_MSVC
    auto* Allocated = static_cast<FByte*>(_aligned_malloc(AlignTo(Bytes, Align), Align));
#else
    auto* Allocated = static_cast<FByte*>(std::aligned_alloc(Align, AlignTo(Bytes, Align)));
#endif
    ROXY_ASSERT(Allocated);
    return Allocated;
}

void FAlignAllocator::DeAllocate(FByte* Ptr) const noexcept
{
    if (!Ptr) { return; }
#if ROXY_IS_MSVC
    _aligned_free(static_cast<void*>(Ptr));
#else
    free(static_cast<void*>(Ptr));
#endif
}

FArenaAllocator::FArenaAllocator(const UIntPtr InCapacity) noexcept
    : Buffer   (Roxy::Alloc::Allocate<FByte>(FAlignAllocator{}, InCapacity, DefaultAlign))
    , Current  (Buffer)
    , Capacity (AlignTo(InCapacity, DefaultAlign))
{
}

FArenaAllocator::~FArenaAllocator()
{
    Roxy::Alloc::DeAllocate<FByte>(FAlignAllocator{}, Buffer);
}

FArenaAllocator::FArenaAllocator(FArenaAllocator&& Oth) noexcept
    : Buffer   (Oth.Buffer)
    , Current  (Oth.Current)
    , Capacity (Oth.Capacity)
{
    Oth.Clear();
}

FArenaAllocator& FArenaAllocator::operator=(FArenaAllocator&& Oth) noexcept
{
    if (this == &Oth) { return *this; }
    Roxy::Alloc::DeAllocate<FByte>(FAlignAllocator{}, Buffer);
    Buffer   = Oth.Buffer;
    Current  = Oth.Current;
    Capacity = Oth.Capacity;
    Oth.Clear();
    return *this;
}

FByte* FArenaAllocator::Allocate(UIntPtr Bytes, UIntPtr Align) noexcept
{
    const auto Aligned = AlignTo(Current, Align);
    if (Aligned + Bytes > Buffer + Capacity)
    {
        ROXY_WARN
        (
            Roxy::Log::ELogCategory::Alloc,
            "Can Not Allocate Memory."
            "\n\tCurrent  = {}"
            "\n\tBuffer   = {}"
            "\n\tCapacity = {}"
            "\n\tAligned  = {}"
            "\n\tBytes    = {}",
            static_cast<void*>(Current),
            static_cast<void*>(Buffer),
            Capacity,
            static_cast<void*>(Aligned),
            Bytes
        );
        return nullptr;
    }
    Current = Aligned + Bytes;
    return Aligned;
}

void FArenaAllocator::DeAllocate(FByte* Ptr ROXY_UNUSED) noexcept
{
    ROXY_WARN(Roxy::Log::ELogCategory::Alloc, "{}", "Can Not Call DeAllocate On FArenaAllocator. Use `Rewind` Instead.");
}

void FArenaAllocator::Rewind() noexcept
{
    Current = Buffer;
}

void FArenaAllocator::Rewind(FByte* RewindPtr) noexcept
{
    ROXY_ASSERT(Buffer <= RewindPtr && RewindPtr <= Current);
    Current = RewindPtr;
}

void FArenaAllocator::Clear() noexcept
{
    Buffer   = {};
    Current  = {};
    Capacity = {};
}

}
