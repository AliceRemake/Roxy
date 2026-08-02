#pragma once

#include <queue>

#include <RoxySTD/RoxyThreadSafety.h>

namespace Roxy
{

template<typename T, EThreadSafety ThreadSafety = EThreadSafety::UnSafe, EThreadSafetyImpl ThreadSafetyImpl = EThreadSafetyImpl::LockFree>
class TQueue;

template<typename T, EThreadSafetyImpl ThreadSafetyImpl>
class TQueue<T, EThreadSafety::UnSafe, ThreadSafetyImpl>
{
public:
    TQueue() = default;
    ~TQueue() = default;

    ROXY_NO_COPY_MOVE(TQueue)

    ROXY_INLINE void EnQueue(T Element) noexcept
    {
        Queue.emplace(std::move(Element));
    }

    ROXY_INLINE T DeQueue() noexcept
    {
        ROXY_ASSERT(!Queue.empty());
        T Element = Queue.front();
        Queue.pop();
        return Element;
    }

    ROXY_NODISCARD ROXY_INLINE bool IsEmpy() const noexcept
    {
        return Queue.empty();
    }

    ROXY_NODISCARD ROXY_INLINE FIndex Num() const noexcept
    {
        return static_cast<FIndex>(Queue.size());
    }

    ROXY_NODISCARD ROXY_INLINE T& First() noexcept
    {
        ROXY_ASSERT(!IsEmpy());
        return Queue.front();
    }

    ROXY_NODISCARD ROXY_INLINE const T& First() const noexcept
    {
        ROXY_ASSERT(!IsEmpy());
        return Queue.front();
    }

    ROXY_NODISCARD ROXY_INLINE T& Last() noexcept
    {
        ROXY_ASSERT(!IsEmpy());
        return Queue.back();
    }

    ROXY_NODISCARD ROXY_INLINE const T& Last() const noexcept
    {
        ROXY_ASSERT(!IsEmpy());
        return Queue.back();
    }

private:
    std::queue<T> Queue {};
};

}
