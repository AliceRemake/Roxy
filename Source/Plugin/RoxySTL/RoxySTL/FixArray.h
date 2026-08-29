#pragma once

#include <RoxySTD/RoxySTD.h>

namespace Roxy
{

template<typename T, FIndex TSize> requires (TSize > 0)
class FixArray
{
public:
    ROXY_NODISCARD ROXY_INLINE constexpr FixArray() noexcept(std::is_nothrow_default_constructible_v<T>) = default;

    ROXY_NODISCARD ROXY_INLINE constexpr FixArray(const TInitList<T> InitList) noexcept
    (
        std::is_nothrow_copy_assignable_v<T> && std::is_nothrow_default_constructible_v<T>
    )
    {
        ROXY_ASSERT_MSG(InitList.size() <= TSize, "FixArray: Too Many Element In InitList");
        auto It = InitList.begin();
        for (FIndex Idx = 0; Idx < TSize; ++Idx)
        {
            Payload[Idx] = It != InitList.end() ? *(It++) : T{};
        }
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T& operator[](const FIndex Idx) noexcept
    {
        ROXY_ASSERT_MSG(0 <= Idx && Idx < TSize, "FixArray: Index Out Of Bound");
        return Payload[Idx];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr const T& operator[](const FIndex Idx) const noexcept
    {
        ROXY_ASSERT_MSG(0 <= Idx && Idx < TSize, "FixArray: Index Out Of Bound");
        return Payload[Idx];
    }

    ROXY_NODISCARD ROXY_INLINE constexpr T operator[](const FIndex Idx) const noexcept requires (std::is_trivial_v<T> && sizeof(T) <= sizeof(T*))
    {
        ROXY_ASSERT_MSG(0 <= Idx && Idx < TSize, "FixArray: Index Out Of Bound");
        return Payload[Idx];
    }

    ROXY_NODISCARD ROXY_INLINE static constexpr FIndex Size() noexcept
    {
        return TSize;
    }

    #pragma region For Loop
    ROXY_NODISCARD ROXY_INLINE constexpr T* begin() noexcept { return Payload; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T* begin() const noexcept { return Payload; }
    ROXY_NODISCARD ROXY_INLINE constexpr T* end() noexcept { return Payload + TSize; }
    ROXY_NODISCARD ROXY_INLINE constexpr const T* end() const noexcept { return Payload + TSize; }
    #pragma endregion

private:
    T Payload[TSize];
};

static_assert(std::is_trivial_v<FixArray<F32, 4>>);
static_assert(std::is_trivial_v<FixArray<F64, 4>>);

}
