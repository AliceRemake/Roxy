#pragma once

#include <RoxySTD/RoxyAlias.h>

namespace Roxy
{

enum class EThreadSafety : UInt8
{
    UnSafe,
    Safe,
};

enum class EThreadSafetyImpl : UInt8
{
    MutexLock,
    SpinLock,
    LockFree,
};

}
