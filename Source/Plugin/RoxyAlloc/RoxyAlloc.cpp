#include "RoxyAlloc.h"

namespace Roxy::Alloc
{

void* FStdAllocator::Allocate(const UInt64 Bytes, const UInt64 Align) noexcept
{
#if ROXY_IS_MSVC
    return Bytes == 0 ? nullptr : _aligned_malloc(Bytes, Align);
#else
    return Bytes == 0 ? nullptr : std::aligned_alloc(Align, Bytes);
#endif
}

void FStdAllocator::DeAllocate(void* Ptr) noexcept
{
#if ROXY_IS_MSVC
    if (Ptr != nullptr) { _aligned_free(Ptr); }
#else
    if (Ptr != nullptr) { free(Ptr); }
#endif
}

}
