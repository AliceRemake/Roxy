// ReSharper disable CppUnusedIncludeDirective
#pragma once

#include <cstdlib>

#include <type_traits>
#include <utility>

#pragma region Alias

#include <cstdint>
using Int8   = std::int8_t;
using UInt8  = std::uint8_t;
using Int16  = std::int16_t;
using UInt16 = std::uint16_t;
using Int32  = std::int32_t;
using UInt32 = std::uint32_t;
using Int64  = std::int64_t;
using UInt64 = std::uint64_t;
using FMaxAlign = std::max_align_t;

#include <limits>
template<typename T> using TLimits = std::numeric_limits<T>;

#include <memory>
template<typename T> using TUnique = std::unique_ptr<T>;
template<typename T> using TShared = std::shared_ptr<T>;

#include <initializer_list>
template<typename T> using TInitList = std::initializer_list<T>;

#include <vector>
template<typename T> using TArray = std::vector<T>;

#include <string>
using FString     = std::string;
using FStringView = std::string_view;

#include <unordered_set>
template<typename TValue> using TSet = std::unordered_set<TValue>;

#include <unordered_map>
template<typename TKey, typename TValue> using TMap = std::unordered_map<TKey, TValue>;

#pragma endregion

#pragma region Macro

#if ROXY_ENABLE_ASSERT
#include <cassert>
#define ROXY_ASSERT(Expr) do { assert(Expr); } while(0)
#else
#define ROXY_ASSERT(Expr)
#endif

#if ROXY_ENABLE_NODISCARD
#define ROXY_NODISCARD [[nodiscard]]
#else
#define ROXY_NODISCARD
#endif

#if ROXY_ENABLE_INLINE
#define ROXY_INLINE __forceinline
#else
#define ROXY_INLINE
#endif

#pragma endregion

using FIndex = Int32;
constexpr FIndex INVALID_INDEX { -1 };
