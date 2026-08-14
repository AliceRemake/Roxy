// ReSharper disable CppUnusedIncludeDirective
// ReSharper disable CppClangTidyBugproneMacroParentheses
#pragma once

#include <cstdlib>

#include <algorithm>
#include <array>
#include <bit>
#include <chrono>
#include <cmath>
#include <numbers>
#include <numeric>
#include <random>
#include <thread>
#include <type_traits>
#include <utility>

#pragma region Alias

#include <cstdint>
#include <cstddef>
using I8        = std::int8_t;
using U8        = std::uint8_t;
using I16       = std::int16_t;
using U16       = std::uint16_t;
using I32       = std::int32_t;
using U32       = std::uint32_t;
using I64       = std::int64_t;
using U64       = std::uint64_t;
using FByte     = std::byte;
using UIntPtr   = std::uintptr_t;
using FMaxAlign = std::max_align_t;
constexpr UIntPtr DefaultAlign = alignof(FMaxAlign);

#include <atomic>
template<typename T> using TAtomic = std::atomic<T>;

#include <condition_variable>
using FCV = std::condition_variable;

#include <initializer_list>
template<typename T> using TInitList = std::initializer_list<T>;

#include <limits>
template<typename T> using TLimits = std::numeric_limits<T>;

#include <memory>
template<typename T> using TUnique = std::unique_ptr<T>;
template<typename T> using TShared = std::shared_ptr<T>;

#include <mutex>
using FMutex = std::mutex;

#include <string>
using FString     = std::string;
using FStringView = std::string_view;

#include <unordered_set>
template<typename TValue> using TSet = std::unordered_set<TValue>;

#include <unordered_map>
template<typename TKey, typename TValue> using TMap = std::unordered_map<TKey, TValue>;

#include <vector>
template<typename T> using TArray = std::vector<T>;

#pragma endregion

#pragma region Macro

#if ROXY_IS_MSVC
#define ROXY_DEBUG_BREAK() do { __debugbreak(); } while(false)
#else
#define ROXY_DEBUG_BREAK() do { __builtin_trap(); } while(false)
#endif

#if ROXY_ENABLE_ASSERT
#define ROXY_ASSERT(Expr) do { if (!(Expr)) { if (std::is_constant_evaluated()) { std::abort(); } else { ROXY_DEBUG_BREAK(); std::abort(); } } } while(false)
#define ROXY_ASSERT_MSG(Expr, Msg) ROXY_ASSERT(Expr)
#else
#define ROXY_ASSERT(Expr) do { if (!(Expr)) { std::abort(); } } while(false)
#define ROXY_ASSERT_MSG(Expr, Msg) ROXY_ASSERT(Expr)
#endif

#if ROXY_ENABLE_NODISCARD
#define ROXY_NODISCARD [[nodiscard]]
#else
#define ROXY_NODISCARD
#endif

#if ROXY_ENABLE_INLINE
#if ROXY_IS_MSVC
#define ROXY_INLINE __forceinline
#else
#define ROXY_INLINE __attribute__((always_inline)) inline
#endif
#else
#define ROXY_INLINE
#endif

#if ROXY_IS_MSVC
#define ROXY_DISABLE_WARNINGS() __pragma(warning(push, 0))
#define ROXY_RESTORE_WARNINGS() __pragma(warning(pop))
#else
#define ROXY_DISABLE_WARNINGS() \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wunused-parameter\"") \
    _Pragma("GCC diagnostic ignored \"-Wunused-function\"")
#define ROXY_RESTORE_WARNINGS() _Pragma("GCC diagnostic pop")
#endif

#define ROXY_UNUSED [[maybe_unused]]

#define ROXY_NO_COPY(ClassName) \
    ClassName(const ClassName&) = delete; \
    ClassName& operator=(const ClassName&) = delete; \

#define ROXY_NO_MOVE(ClassName) \
    ClassName(ClassName&&) = delete; \
    ClassName& operator=(ClassName&&) = delete; \

#define ROXY_NO_COPY_MOVE(ClassName) \
    ROXY_NO_COPY(ClassName) \
    ROXY_NO_MOVE(ClassName)

#pragma endregion

using FIndex = I32;
constexpr FIndex INVALID_INDEX { -1 };
