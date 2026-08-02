#pragma once

#include <RoxyMT/RoxyLock.h>

namespace Roxy
{

template<typename T, EThreadSafetyImpl ThreadSafetyImpl>
class TQueue<T, EThreadSafety::Safe, ThreadSafetyImpl>
{
public:
    TQueue() = default;
    ~TQueue() = default;

    ROXY_NO_COPY_MOVE(TQueue)

    void Enqueue(T Element)
    {
        MT::FLockGuard LockGuard(Lock);
        Queue.emplace(std::move(Element));
    }

    T Dequeue()
    {
        MT::FLockGuard LockGuard(Lock);
        ROXY_ASSERT(!Queue.empty());
        T Element = Queue.front();
        Queue.pop();
        return Element;
    }

    ROXY_NODISCARD ROXY_INLINE bool IsEmpy() const noexcept
    {
        MT::FLockGuard LockGuard(Lock);
        return Queue.empty();
    }

    ROXY_NODISCARD ROXY_INLINE FIndex Num() const noexcept
    {
        MT::FLockGuard LockGuard(Lock);
        return static_cast<FIndex>(Queue.size());
    }

    ROXY_NODISCARD ROXY_INLINE T PeekFirst() const noexcept
    {
        ROXY_ASSERT(!IsEmpy());
        return Queue.front();
    }

    ROXY_NODISCARD ROXY_INLINE T PeekLast() const noexcept
    {
        ROXY_ASSERT(!IsEmpy());
        return Queue.back();
    }

private:

    using FLock = std::conditional_t
    <
        ThreadSafetyImpl == EThreadSafetyImpl::MutexLock, MT::FMutexLock, std::conditional_t<
        ThreadSafetyImpl == EThreadSafetyImpl::SpinLock,  MT::FSpinLock,
        MT::FMutexLock
    >>;

    mutable FLock Lock  {};
    std::queue<T> Queue {};
};

template<typename T>
class TQueue<T, EThreadSafety::Safe, EThreadSafetyImpl::LockFree>
{
    // @TODO
};

}
