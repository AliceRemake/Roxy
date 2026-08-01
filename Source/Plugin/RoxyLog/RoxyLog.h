#pragma once

#define ROXY_LOG_LEVEL_TRACE (0)
#define ROXY_LOG_LEVEL_DEBUG (1)
#define ROXY_LOG_LEVEL_INFO  (2)
#define ROXY_LOG_LEVEL_WARN  (3)
#define ROXY_LOG_LEVEL_ERROR (4)
#define ROXY_LOG_LEVEL_FATAL (5)
#define ROXY_LOG_LEVEL_OFF   (6)

#ifndef ROXY_LOG_LEVEL
#define ROXY_LOG_LEVEL ROXY_LOG_LEVEL_TRACE
#endif

#if ROXY_LOG_LEVEL == ROXY_LOG_LEVEL_TRACE
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#elif ROXY_LOG_LEVEL == ROXY_LOG_LEVEL_DEBUG
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#elif ROXY_LOG_LEVEL == ROXY_LOG_LEVEL_INFO
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#elif ROXY_LOG_LEVEL == ROXY_LOG_LEVEL_WARN
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_WARN
#elif ROXY_LOG_LEVEL == ROXY_LOG_LEVEL_ERROR
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_ERROR
#elif ROXY_LOG_LEVEL == ROXY_LOG_LEVEL_FATAL
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_CRITICAL
#endif

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#pragma warning(pop)

#include <RoxySTD.h>
#include <RoxyFmt.h>

namespace Roxy::Log
{

constexpr auto DefaultPattern                 = "[%Y-%m-%d][%H:%M:%S][%^%L%$]%v";
constexpr auto DefaultPatternWithFileLineFunc = "[%Y-%m-%d][%H:%M:%S][%^%L%$][%@][%!]%v";

enum class ELogCategory : UInt8
{
    Default
};

enum class ELogLevel : UInt8
{
    Trace,
    Debug,
    Info,
    Warn,
    Error,
    Fatal,
    Off,
};

enum class ELogTime : UInt8
{
    Local,
    UTC,
};

namespace Detail
{

ROXY_NODISCARD ROXY_INLINE constexpr const char* GetEnumName(const ELogCategory LogCategory)
{
    switch (LogCategory)
    {
    case ELogCategory::Default: return "Default";
    }
    return "Unknown";
}

ROXY_NODISCARD ROXY_INLINE constexpr const char* GetEnumName(const ELogLevel LogLevel)
{
    switch (LogLevel)
    {
    case ELogLevel::Trace: return "TRACE";
    case ELogLevel::Info:  return "INFO";
    case ELogLevel::Debug: return "DEBUG";
    case ELogLevel::Warn:  return "WARN";
    case ELogLevel::Error: return "ERROR";
    case ELogLevel::Fatal: return "FATAL";
    case ELogLevel::Off:   return "OFF";
    }
    return "UNKNOWN";
}

}

void SetLevel(ELogLevel LogLevel) noexcept;

void SetPattern(FString Pattern, ELogTime LogTime = ELogTime::Local) noexcept;

template <typename... T>
ROXY_INLINE void Trace(const ELogCategory LogCategory, Fmt::FormatString<T...> Fmt, T&&...Args) noexcept
{
    const auto LogMsg = Fmt::Format(Fmt, std::forward<T>(Args)...);
    spdlog::trace("[{}] {}", Detail::GetEnumName(LogCategory), LogMsg);
}

template <typename... T>
ROXY_INLINE void Debug(const ELogCategory LogCategory, Fmt::FormatString<T...> Fmt, T&&...Args) noexcept
{
    const auto LogMsg = Fmt::Format(Fmt, std::forward<T>(Args)...);
    spdlog::debug("[{}] {}", Detail::GetEnumName(LogCategory), LogMsg);
}

template <typename... T>
ROXY_INLINE void Info(const ELogCategory LogCategory, Fmt::FormatString<T...> Fmt, T&&...Args) noexcept
{
    const auto LogMsg = Fmt::Format(Fmt, std::forward<T>(Args)...);
    spdlog::info("[{}] {}", Detail::GetEnumName(LogCategory), LogMsg);
}

template <typename... T>
ROXY_INLINE void Warn(const ELogCategory LogCategory, Fmt::FormatString<T...> Fmt, T&&...Args) noexcept
{
    const auto LogMsg = Fmt::Format(Fmt, std::forward<T>(Args)...);
    spdlog::warn("[{}] {}", Detail::GetEnumName(LogCategory), LogMsg);
}

template <typename... T>
ROXY_INLINE void Error(const ELogCategory LogCategory, Fmt::FormatString<T...> Fmt, T&&...Args) noexcept
{
    const auto LogMsg = Fmt::Format(Fmt, std::forward<T>(Args)...);
    spdlog::error("[{}] {}", Detail::GetEnumName(LogCategory), LogMsg);
}

template <typename... T>
ROXY_INLINE void Fatal(const ELogCategory LogCategory, Fmt::FormatString<T...> Fmt, T&&...Args) noexcept
{
    const auto LogMsg = Fmt::Format(Fmt, std::forward<T>(Args)...);
    spdlog::critical("[{}] {}", Detail::GetEnumName(LogCategory), LogMsg);
}

}

#define ROXY_TRACE(LogCategory, Fmt_, ...) do \
    { \
        const auto LogMsg = Roxy::Fmt::Format(Fmt_, __VA_ARGS__); \
        SPDLOG_TRACE("[{}] {}", Roxy::Log::Detail::GetEnumName(LogCategory), LogMsg); \
    } while(0)

#define ROXY_DEBUG(LogCategory, Fmt_, ...) do \
    { \
        const auto LogMsg = Roxy::Fmt::Format(Fmt_, __VA_ARGS__); \
        SPDLOG_DEBUG("[{}] {}", Roxy::Log::Detail::GetEnumName(LogCategory), LogMsg); \
    } while(0)

#define ROXY_INFO(LogCategory, Fmt_, ...) do \
    { \
        const auto LogMsg = Roxy::Fmt::Format(Fmt_, __VA_ARGS__); \
        SPDLOG_INFO("[{}] {}", Roxy::Log::Detail::GetEnumName(LogCategory), LogMsg); \
    } while(0)

#define ROXY_WARN(LogCategory, Fmt_, ...) do \
    { \
        const auto LogMsg = Roxy::Fmt::Format(Fmt_, __VA_ARGS__); \
        SPDLOG_WARN("[{}] {}", Roxy::Log::Detail::GetEnumName(LogCategory), LogMsg); \
    } while(0)

#define ROXY_ERROR(LogCategory, Fmt_, ...) do \
    { \
        const auto LogMsg = Roxy::Fmt::Format(Fmt_, __VA_ARGS__); \
        SPDLOG_ERROR("[{}] {}", Roxy::Log::Detail::GetEnumName(LogCategory), LogMsg); \
    } while(0)

#define ROXY_FATAL(LogCategory, Fmt_, ...) do \
    { \
        const auto LogMsg = Roxy::Fmt::Format(Fmt_, __VA_ARGS__); \
        SPDLOG_CRITICAL("[{}] {}", Roxy::Log::Detail::GetEnumName(LogCategory), LogMsg); \
    } while(0)
