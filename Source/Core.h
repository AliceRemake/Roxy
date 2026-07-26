// ReSharper disable CppUnusedIncludeDirective
#pragma once

#include <cstdint>
#include <cassert>

#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template<typename T> using TUnique = std::unique_ptr<T>;
template<typename T> using TShared = std::shared_ptr<T>;
template<typename T> using TArray = std::vector<T>;
template<typename T> using TFunction = std::function<T>;
template<typename TValue> using TSet = std::unordered_set<TValue>;
template<typename TKey, typename TValue> using TMap = std::unordered_map<TKey, TValue>;

using  Int8  = std::int8_t;
using UInt8  = std::uint8_t;
using  Int16 = std::int16_t;
using UInt16 = std::uint16_t;
using  Int32 = std::int32_t;
using UInt32 = std::uint32_t;
using  Int64 = std::int64_t;
using UInt64 = std::uint64_t;

using FIndex = Int32;
constexpr FIndex INVALID_INDEX { -1 };
