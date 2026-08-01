#include "RoxyLog.h"

namespace Roxy::Log
{

void SetLevel(const ELogLevel LogLevel) noexcept
{
    if (LogLevel == ELogLevel::Trace)
    {
        spdlog::set_level(spdlog::level::trace);
    }
    else if (LogLevel == ELogLevel::Info)
    {
        spdlog::set_level(spdlog::level::info);
    }
    else if (LogLevel == ELogLevel::Debug)
    {
        spdlog::set_level(spdlog::level::debug);
    }
    else if (LogLevel == ELogLevel::Warn)
    {
        spdlog::set_level(spdlog::level::warn);
    }
    else if (LogLevel == ELogLevel::Error)
    {
        spdlog::set_level(spdlog::level::err);
    }
    else if (LogLevel == ELogLevel::Fatal)
    {
        spdlog::set_level(spdlog::level::critical);
    }
    else if (LogLevel == ELogLevel::Off)
    {
        spdlog::set_level(spdlog::level::off);
    }
}

void SetPattern(FString Pattern, const ELogTime LogTime) noexcept
{
    if (LogTime == ELogTime::Local)
    {
        spdlog::set_pattern(std::move(Pattern), spdlog::pattern_time_type::local);
    }
    else if (LogTime == ELogTime::UTC)
    {
        spdlog::set_pattern(std::move(Pattern), spdlog::pattern_time_type::utc);
    }
}

}
