#pragma once

#include <RoxySTD.h>

namespace Roxy::Alloc
{

ROXY_INLINE constexpr UIntPtr AlignTo(UIntPtr Addr, UIntPtr Align)
{
    ROXY_ASSERT((Align & (Align - 1)) == 0 && "Align Must Be A Power Of 2");
    return (Addr + (Align - 1)) & (~(Align - 1));
}

ROXY_INLINE Byte* AlignTo(Byte* Addr, UIntPtr Align)
{
    return reinterpret_cast<Byte*>(AlignTo(reinterpret_cast<UIntPtr>(Addr), Align));
}

template<typename T>
concept CAllocator = requires (T Allocator, Byte* Ptr, UIntPtr Bytes, UIntPtr Align)
{
    { Allocator.Allocate(Bytes, Align) } noexcept -> std::same_as<Byte*>;
    { Allocator.DeAllocate(Ptr)        } noexcept -> std::same_as<void>;
};

template<typename T, typename TAllocator> requires CAllocator<std::remove_cvref_t<TAllocator>>
ROXY_NODISCARD ROXY_INLINE T* Allocate(TAllocator&& Allocator, UIntPtr Bytes, UIntPtr Align = alignof(FMaxAlign)) noexcept
{
    ROXY_ASSERT(!!Bytes);
    Byte* Ptr = Allocator.Allocate(Bytes, Align);
    return Ptr ? reinterpret_cast<T*>(Ptr) : nullptr;
}

template<typename T, typename TAllocator> requires CAllocator<std::remove_cvref_t<TAllocator>>
ROXY_INLINE void DeAllocate(TAllocator&& Allocator, T* Ptr) noexcept  // NOLINT(cppcoreguidelines-missing-std-forward)
{
    Allocator.DeAllocate(reinterpret_cast<Byte*>(Ptr));
}

class FAlignAllocator
{
public:
    FAlignAllocator() = default; /* EBO */

    ROXY_NODISCARD Byte* Allocate(UIntPtr Bytes, UIntPtr Align = alignof(FMaxAlign)) const noexcept;

    void DeAllocate(Byte* Ptr) const noexcept;
};

static_assert(CAllocator<FAlignAllocator>);

class FArenaAllocator
{
public:
    ROXY_NODISCARD explicit FArenaAllocator(UIntPtr InCapacity) noexcept;
    ~FArenaAllocator();

    FArenaAllocator(const FArenaAllocator&) = delete;
    FArenaAllocator& operator=(const FArenaAllocator&) = delete;

    FArenaAllocator(FArenaAllocator&&) noexcept;
    FArenaAllocator& operator=(FArenaAllocator&&) noexcept;

    ROXY_NODISCARD Byte* Allocate(UIntPtr Bytes, UIntPtr Align = alignof(FMaxAlign)) noexcept;

    void DeAllocate(Byte* Ptr) noexcept;

    void Rewind() noexcept;

    void Rewind(Byte* RewindPtr) noexcept;

private:
    void Clear() noexcept;

    Byte*   Buffer   {};
    Byte*   Current  {};
    UIntPtr Capacity {};
};

static_assert(CAllocator<FArenaAllocator>);

}
