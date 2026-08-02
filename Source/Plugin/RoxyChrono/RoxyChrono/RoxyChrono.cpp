#include "RoxyChrono.h"

namespace Roxy::Chrono
{

template<> double FTimer::GetElapsed<ETimeUnit::NaS>() const
{
    const auto Now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::nano>(Now - Before).count();
}

template<> double FTimer::GetElapsed<ETimeUnit::MuS>() const
{
    const auto Now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::micro>(Now - Before).count();
}

template<> double FTimer::GetElapsed<ETimeUnit::MiS>() const
{
    const auto Now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::milli>(Now - Before).count();
}

template<> double FTimer::GetElapsed<ETimeUnit::S>() const
{
    const auto Now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(Now - Before).count();
}

template<> double FTimer::GetElapsed<ETimeUnit::M>() const
{
    const auto Now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::ratio<60>>(Now - Before).count();
}

template<> double FTimer::GetElapsed<ETimeUnit::H>() const
{
    const auto Now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double, std::ratio<3600>>(Now - Before).count();
}

}
