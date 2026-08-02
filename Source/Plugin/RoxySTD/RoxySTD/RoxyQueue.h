#pragma once

#include <queue>

#include <RoxySTD/RoxyThreadSafety.h>

namespace Roxy
{

template<typename T, EMTModel MTModel = EMTModel::SPSC, EMTImpl MTImpl = EMTImpl::None>
class TQueue;

template<typename T>
class TQueue<T, EMTModel::SPSC, EMTImpl::None>
{
public:
    TQueue() = default;
    ~TQueue() = default;

    ROXY_NO_COPY_MOVE(TQueue)

    ROXY_INLINE void EnQueue(T Element) noexcept
    {
        Queue.emplace(std::move(Element));
    }

    ROXY_INLINE bool DeQueue(T& OutElement) noexcept
    {
        if (IsEmpty()) { return false; }
        OutElement = std::move(Queue.front());
        Queue.pop();
        return true;
    }

    ROXY_NODISCARD ROXY_INLINE bool IsEmpty() const noexcept
    {
        return Queue.empty();
    }

    ROXY_NODISCARD ROXY_INLINE FIndex Num() const noexcept
    {
        return static_cast<FIndex>(Queue.size());
    }

    ROXY_NODISCARD ROXY_INLINE T& First() noexcept
    {
        ROXY_ASSERT(!IsEmpty());
        return Queue.front();
    }

    ROXY_NODISCARD ROXY_INLINE const T& First() const noexcept
    {
        ROXY_ASSERT(!IsEmpty());
        return Queue.front();
    }

    ROXY_NODISCARD ROXY_INLINE T& Last() noexcept
    {
        ROXY_ASSERT(!IsEmpty());
        return Queue.back();
    }

    ROXY_NODISCARD ROXY_INLINE const T& Last() const noexcept
    {
        ROXY_ASSERT(!IsEmpty());
        return Queue.back();
    }

private:
    std::queue<T> Queue {};
};

}
