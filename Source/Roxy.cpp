#include <RoxyFmt.h>
#include <RoxyLog.h>

int main(const Int32 Argc, const char** Argv)
{
    (void)Argc;
    (void)Argv;

    Roxy::Fmt::Println("Hello Roxy!");

    Roxy::Log::SetLevel(Roxy::Log::ELogLevel::Info);
    Roxy::Log::SetPattern(Roxy::Log::DefaultPatternWithFileLineFunc);

    for (UInt64 GNrFrame = 0; true; ++GNrFrame)
    {
        ROXY_WARN(Roxy::Log::ELogCategory::Default, "[Frame] {}", GNrFrame);
    }

    // return 0;
}
