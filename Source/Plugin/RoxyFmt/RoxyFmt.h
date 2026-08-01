#pragma once

#pragma warning(push, 0)
#include <fmt/base.h>
#include <fmt/format.h>
#pragma warning(pop)

#include <RoxySTD.h>

namespace RoxyFmt
{

template <typename... T> using FormatString = fmt::format_string<T...>;

template <typename... T>
void Print(FILE* File, FormatString<T...> FormatString, T&&... Args)
{
    fmt::print(File, FormatString, std::forward<T>(Args)...);
}

template <typename... T>
void Print(FormatString<T...> FormatString, T&&... Args)
{
    Print(stdout, FormatString, std::forward<T>(Args)...);
}

template <typename... T>
void Println(FILE* File, FormatString<T...> FormatString, T&&... Args)
{
    fmt::println(File, FormatString, std::forward<T>(Args)...);
}

template <typename... T>
void Println(FormatString<T...> FormatString, T&&... Args)
{
    Println(stdout, FormatString, std::forward<T>(Args)...);
}

template <typename... T>
ROXY_NODISCARD ROXY_INLINE FString Format(FormatString<T...> Fmt, T&&... Args)
{
    return fmt::format(Fmt, std::forward<T>(Args)...);
}

}
