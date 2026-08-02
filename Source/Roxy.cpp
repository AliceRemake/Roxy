#include <RoxySTD/RoxySTD.h>

ROXY_DISABLE_WARNINGS()
#define RGFW_IMPLEMENTATION
#include <RGFW.h>
ROXY_RESTORE_WARNINGS()

#include <RoxyFmt/RoxyFmt.h>
#include <RoxyLog/RoxyLog.h>
#include <RoxyChrono/RoxyChrono.h>

static constexpr U8  TargetFPS       = 60;
static constexpr double TargetFrameTime = 1000.0 / TargetFPS;

int main(const I32 Argc, const char** Argv)
{
    (void)Argc;
    (void)Argv;

    Roxy::Fmt::Println("Hello Roxy!");

    Roxy::Log::SetLevel(Roxy::Log::ELogLevel::Info);
    Roxy::Log::SetPattern(Roxy::Log::DefaultPatternWithFileLineFunc);

    RGFW_init();
    RGFW_window* Window = RGFW_createWindow("Roxy", 0, 0, 800, 600, RGFW_windowCenter | RGFW_windowNoResize);
    for (U64 GNrFrame = 0; RGFW_window_shouldClose(Window) == RGFW_FALSE; ++GNrFrame)
    {
        Roxy::Chrono::FTimer FrameTimer {};
        ROXY_WARN(Roxy::Log::ELogCategory::Default, "[Frame] {}", GNrFrame);
        RGFW_event Event;
        while (RGFW_window_checkEvent(Window, &Event))
        {
            if (Event.type == RGFW_quit || Event.type == RGFW_escape)
            {
                RGFW_window_setShouldClose(Window, true);
            }
        }
        const auto Elapsed = FrameTimer.GetElapsed<Roxy::Chrono::ETimeUnit::MiS>();
        if (const auto SleepTime = TargetFrameTime - Elapsed; SleepTime > 0.0)
        {
            std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(SleepTime));
        }
    }
    RGFW_window_close(Window);
    RGFW_deinit();

    return 0;
}
