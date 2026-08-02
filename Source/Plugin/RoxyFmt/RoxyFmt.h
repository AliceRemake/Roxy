#pragma once

#include <RoxySTD.h>

ROXY_DISABLE_WARNINGS()
//*@Temp: Suppress spdlog Deprecation Warnings.
#ifdef FMT_DEPRECATED
#undef FMT_DEPRECATED
#endif
#define FMT_DEPRECATED
#include <fmt/base.h>
#include <fmt/format.h>
ROXY_RESTORE_WARNINGS()

namespace Roxy::Fmt
{

template <typename... T> using FormatString = fmt::format_string<T...>;

template <typename... T>
ROXY_INLINE void Print(FILE* File, FormatString<T...> FormatString, T&&... Args) noexcept
{
    fmt::print(File, FormatString, std::forward<T>(Args)...);
}

template <typename... T>
ROXY_INLINE void Print(FormatString<T...> FormatString, T&&... Args) noexcept
{
    Print(stdout, FormatString, std::forward<T>(Args)...);
}

template <typename... T>
ROXY_INLINE void Println(FILE* File, FormatString<T...> FormatString, T&&... Args) noexcept
{
    fmt::println(File, FormatString, std::forward<T>(Args)...);
}

template <typename... T>
ROXY_INLINE void Println(FormatString<T...> FormatString, T&&... Args) noexcept
{
    Println(stdout, FormatString, std::forward<T>(Args)...);
}

template <typename... T>
ROXY_NODISCARD ROXY_INLINE FString Format(FormatString<T...> Fmt, T&&... Args) noexcept
{
    return fmt::format(Fmt, std::forward<T>(Args)...);
}

}
