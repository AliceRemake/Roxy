#pragma once

#include <RoxySTD/RoxySTD.h>

namespace Roxy::Chrono
{

enum class ETimeUnit : U8
{
    NaS,
    MuS,
    MiS,
    S,
    M,
    H,
};

class FTimer
{
public:
    template<ETimeUnit TimeUnit>
    ROXY_NODISCARD double Elapsed() const { ROXY_ASSERT_MSG(false, "FTimer: Unsupported ETimeUnit"); }

private:
    std::chrono::high_resolution_clock::time_point Before { std::chrono::high_resolution_clock::now() };
};

template<> ROXY_NODISCARD double FTimer::Elapsed<ETimeUnit::NaS>() const;
template<> ROXY_NODISCARD double FTimer::Elapsed<ETimeUnit::MuS>() const;
template<> ROXY_NODISCARD double FTimer::Elapsed<ETimeUnit::MiS>() const;
template<> ROXY_NODISCARD double FTimer::Elapsed<ETimeUnit::S>  () const;
template<> ROXY_NODISCARD double FTimer::Elapsed<ETimeUnit::M>  () const;
template<> ROXY_NODISCARD double FTimer::Elapsed<ETimeUnit::H>  () const;


template<ETimeUnit TimeUnit> void SleepFor(const double Time ROXY_UNUSED) noexcept { ROXY_ASSERT_MSG(false, "SleepFor: Unsupported ETimeUnit"); }
template<> void SleepFor<ETimeUnit::NaS>(double Time) noexcept;
template<> void SleepFor<ETimeUnit::MuS>(double Time) noexcept;
template<> void SleepFor<ETimeUnit::MiS>(double Time) noexcept;
template<> void SleepFor<ETimeUnit::S>  (double Time) noexcept;
template<> void SleepFor<ETimeUnit::M>  (double Time) noexcept;
template<> void SleepFor<ETimeUnit::H>  (double Time) noexcept;

}
