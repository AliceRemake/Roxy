#pragma once

#include <RoxySTD/RoxySTD.h>

namespace Roxy::Chrono
{

enum class ETimeUnit : UInt8
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
    ROXY_NODISCARD double GetElapsed() const { ROXY_ASSERT(false && "Unsupported ETimeUnit"); return {}; }

private:
    std::chrono::high_resolution_clock::time_point Before { std::chrono::high_resolution_clock::now() };
};

template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::NaS>() const;
template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::MuS>() const;
template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::MiS>() const;
template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::S>  () const;
template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::M>  () const;
template<> ROXY_NODISCARD double FTimer::GetElapsed<ETimeUnit::H>  () const;

}
