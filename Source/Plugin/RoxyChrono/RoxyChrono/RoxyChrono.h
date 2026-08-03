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
    ROXY_NODISCARD double GetElapsed() const { ROXY_ASSERT(false && "Unsupported ETimeUnit"); }

private:
    std::chrono::high_resolution_clock::time_point Before { std::chrono::high_resolution_clock::now() };
};

template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::NaS>() const;
template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::MuS>() const;
template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::MiS>() const;
template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::S>  () const;
template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::M>  () const;
template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::H>  () const;


template<ETimeUnit TimeUnit> void SleepFor(const double Time ROXY_UNUSED) noexcept { ROXY_ASSERT(false && "Unsupported ETimeUnit"); }
template<> void SleepFor<ETimeUnit::NaS>(double Time) noexcept;
template<> void SleepFor<ETimeUnit::MuS>(double Time) noexcept;
template<> void SleepFor<ETimeUnit::MiS>(double Time) noexcept;
template<> void SleepFor<ETimeUnit::S>  (double Time) noexcept;
template<> void SleepFor<ETimeUnit::M>  (double Time) noexcept;
template<> void SleepFor<ETimeUnit::H>  (double Time) noexcept;

}
