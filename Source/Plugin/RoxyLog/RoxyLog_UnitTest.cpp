#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyLog.h>

constexpr FStringView PluginName = "RoxyLog";

TEST_CASE("Log")
{
    Roxy::Log::SetLevel(Roxy::Log::ELogLevel::Trace);
    Roxy::Log::SetPattern("[%Y-%m-%d][%H:%M:%S][%^%L%$][%@][%!]%v");

    Roxy::Log::Trace(Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Trace");
    Roxy::Log::Debug(Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Debug");
    Roxy::Log::Info (Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Info" );
    Roxy::Log::Warn (Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Warn" );
    Roxy::Log::Error(Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Error");
    Roxy::Log::Fatal(Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Fatal");

    ROXY_TRACE(Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Trace");
    ROXY_DEBUG(Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Debug");
    ROXY_INFO (Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Info" );
    ROXY_WARN (Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Warn" );
    ROXY_ERROR(Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Error");
    ROXY_FATAL(Roxy::Log::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Fatal");
}
