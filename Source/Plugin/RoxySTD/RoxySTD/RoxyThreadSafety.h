#pragma once

#include <RoxySTD/RoxyAlias.h>

namespace Roxy
{

enum class EMTModelFlags : U8
{
    MC = 1 << 0,
    MP = 1 << 1,
};

enum class EMTModel : U8
{
    SPSC, /* Single Producer Single Consumer */
    SPMC, /* Single Producer Multi  Consumer */
    MPSC, /* Multi  Producer Single Consumer */
    MPMC, /* Multi  Producer Multi  Consumer */
};

enum class EMTImpl : U8
{
    None,
    MutexLock,
    SpinLock,
    LockFree,
};

}
