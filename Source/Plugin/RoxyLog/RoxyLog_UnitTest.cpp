#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyLog.h>

constexpr FStringView PluginName = "RoxyLog";

TEST_CASE("Log")
{
    RoxyLog::SetLevel(RoxyLog::ELogLevel::Trace);
    RoxyLog::SetPattern("[%Y-%m-%d][%H:%M:%S][%^%L%$][%@][%!]%v");

    RoxyLog::Trace(RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Trace");
    RoxyLog::Debug(RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Debug");
    RoxyLog::Info (RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Info" );
    RoxyLog::Warn (RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Warn" );
    RoxyLog::Error(RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Error");
    RoxyLog::Fatal(RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Fatal");

    ROXY_TRACE(RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Trace");
    ROXY_DEBUG(RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Debug");
    ROXY_INFO (RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Info" );
    ROXY_WARN (RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Warn" );
    ROXY_ERROR(RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Error");
    ROXY_FATAL(RoxyLog::ELogCategory::Default, "Hello {}! This Is {}", PluginName, "Fatal");
}
