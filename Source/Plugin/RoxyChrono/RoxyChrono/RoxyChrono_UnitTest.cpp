#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyLog/RoxyLog.h>
#include <RoxyChrono/RoxyChrono.h>

using namespace Roxy::Chrono;

TEST_CASE("Roxy::Chrono")
{
    SUBCASE("FTimer/SleepFor")
    {
        FTimer Timer;
        SleepFor<ETimeUnit::MiS>(50);

        const auto NaS = Timer.Elapsed<ETimeUnit::NaS>();
        const auto MuS = Timer.Elapsed<ETimeUnit::MuS>();
        const auto MiS = Timer.Elapsed<ETimeUnit::MiS>();
        const auto S   = Timer.Elapsed<ETimeUnit::S>();
        const auto M   = Timer.Elapsed<ETimeUnit::M>();
        const auto H   = Timer.Elapsed<ETimeUnit::H>();

        CHECK(NaS > 0.0);
        CHECK(MuS > 0.0);
        CHECK(MiS > 0.0);
        CHECK(S   > 0.0);
        CHECK(M   > 0.0);
        CHECK(H   > 0.0);

        CHECK(NaS > MuS);
        CHECK(MuS > MiS);
        CHECK(MiS > S);
        CHECK(S   > M);
        CHECK(M   > H);
    }

    SUBCASE("Log Elapsed Time")
    {
        FTimer Timer;
        std::this_thread::sleep_for(std::chrono::milliseconds(123));

        const auto NaS = Timer.Elapsed<ETimeUnit::NaS>();
        const auto MuS = Timer.Elapsed<ETimeUnit::MuS>();
        const auto MiS = Timer.Elapsed<ETimeUnit::MiS>();
        const auto S   = Timer.Elapsed<ETimeUnit::S>  ();
        const auto M   = Timer.Elapsed<ETimeUnit::M>  ();
        const auto H   = Timer.Elapsed<ETimeUnit::H>  ();

        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} ns ", NaS);
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} us ", MuS);
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} ms ", MiS);
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} s  ", S  );
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} min", M  );
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} h  ", H  );

        CHECK(NaS > 0.0);
        CHECK(MuS > 0.0);
        CHECK(MiS > 0.0);
        CHECK(S   > 0.0);
        CHECK(M   > 0.0);
        CHECK(H   > 0.0);
        CHECK(NaS > MuS);
        CHECK(MuS > MiS);
        CHECK(MiS > S  );
        CHECK(S   > M  );
        CHECK(M   > H  );
    }
}
