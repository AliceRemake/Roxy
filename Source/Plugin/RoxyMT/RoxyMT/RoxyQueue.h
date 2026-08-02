#pragma once

#include <RoxyMT/RoxyLock.h>

namespace Roxy
{

template<typename T, EMTModel MTModel, EMTImpl MTImpl> requires
(
    MTModel != EMTModel::SPSC
    && (MTImpl == EMTImpl::MutexLock
    || MTImpl == EMTImpl::SpinLock)
)
class TQueue<T, MTModel, MTImpl>
{
public:
    TQueue() = default;
    ~TQueue() = default;

    ROXY_NO_COPY_MOVE(TQueue)

    ROXY_INLINE void EnQueue(T Element) noexcept
    {
        MT::FLockGuard LockGuard(Lock);
        Queue.EnQueue(Element);
    }

    ROXY_INLINE bool DeQueue(T& OutElement) noexcept
    {
        MT::FLockGuard LockGuard(Lock);
        return Queue.DeQueue(OutElement);
    }

private:
    using FLock = std::conditional_t<MTImpl == EMTImpl::MutexLock, MT::FMutexLock, MT::FSpinLock>;

    mutable FLock Lock  {};
    TQueue<T>     Queue {};
};

template<typename T, EMTModel MTModel> requires
(
    MTModel != EMTModel::SPSC
)
class TQueue<T, MTModel, EMTImpl::LockFree>
{
    //@TODO
};

}
