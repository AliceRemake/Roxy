#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyLog.h>
#include <RoxyChrono.h>

using namespace Roxy::Chrono;

TEST_CASE("Roxy::Chrono::FTimer")
{
    SUBCASE("All time units return positive values after a short sleep")
    {
        FTimer Timer;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

        CHECK(Timer.GetElapsed<ETimeUnit::NaS>() > 0.0);
        CHECK(Timer.GetElapsed<ETimeUnit::MuS>() > 0.0);
        CHECK(Timer.GetElapsed<ETimeUnit::MiS>() > 0.0);
        CHECK(Timer.GetElapsed<ETimeUnit::S>()   > 0.0);
        CHECK(Timer.GetElapsed<ETimeUnit::M>()   > 0.0);
        CHECK(Timer.GetElapsed<ETimeUnit::H>()   > 0.0);
    }

    SUBCASE("Larger time units yield numerically smaller values for the same interval")
    {
        FTimer Timer;
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        const double NaS = Timer.GetElapsed<ETimeUnit::NaS>();
        const double MuS = Timer.GetElapsed<ETimeUnit::MuS>();
        const double MiS = Timer.GetElapsed<ETimeUnit::MiS>();
        const double S   = Timer.GetElapsed<ETimeUnit::S>();
        const double M   = Timer.GetElapsed<ETimeUnit::M>();
        const double H   = Timer.GetElapsed<ETimeUnit::H>();

        CHECK(NaS > MuS);
        CHECK(MuS > MiS);
        CHECK(MiS > S);
        CHECK(S   > M);
        CHECK(M   > H);
    }

    SUBCASE("Timer can be reused by creating a new instance")
    {
        FTimer Timer1;
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        const double First = Timer1.GetElapsed<ETimeUnit::MiS>();

        FTimer Timer2;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        const double Second = Timer2.GetElapsed<ETimeUnit::MiS>();

        CHECK(Second > First);
    }

    SUBCASE("Timer Log With RoxyLog")
    {
        FTimer Timer;
        std::this_thread::sleep_for(std::chrono::milliseconds(123));

        const double NaS = Timer.GetElapsed<ETimeUnit::NaS>();
        const double MuS = Timer.GetElapsed<ETimeUnit::MuS>();
        const double MiS = Timer.GetElapsed<ETimeUnit::MiS>();
        const double S   = Timer.GetElapsed<ETimeUnit::S>  ();
        const double M   = Timer.GetElapsed<ETimeUnit::M>  ();
        const double H   = Timer.GetElapsed<ETimeUnit::H>  ();

        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} ns" , NaS);
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} us" , MuS);
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} ms" , MiS);
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} s"  , S  );
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} min", M  );
        ROXY_INFO(Roxy::Log::ELogCategory::Default, "Elapsed: {:>15.3f} h"  , H  );

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
