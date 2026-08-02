#pragma once

#include <RoxySTD/RoxyAlias.h>

namespace Roxy
{

enum class EMTModelFlags : UInt8
{
    MC = 1 << 0,
    MP = 1 << 1,
};

enum class EMTModel : UInt8
{
    SPSC, /* Single Producer Single Consumer */
    SPMC, /* Single Producer Multi  Consumer */
    MPSC, /* Multi  Producer Single Consumer */
    MPMC, /* Multi  Producer Multi  Consumer */
};

enum class EMTImpl : UInt8
{
    None,
    MutexLock,
    SpinLock,
    LockFree,
};

}
