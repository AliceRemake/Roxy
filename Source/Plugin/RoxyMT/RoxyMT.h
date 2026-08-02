#pragma once

#include <RoxySTD.h>

namespace Roxy::MT
{

template<typename T>
concept CLock = requires(T Lock)
{
    { Lock.Lock()    } -> std::same_as<void>;
    { Lock.UnLock()  } -> std::same_as<void>;
    { Lock.TryLock() } -> std::same_as<bool>;
};

template<CLock TLock>
class FLockGuard
{
public:
    ROXY_NODISCARD ROXY_INLINE explicit FLockGuard(TLock& InLock) noexcept : Lock(InLock)
    {
        Lock.Lock();
    }

    ROXY_INLINE ~FLockGuard() noexcept { Lock.UnLock(); }

    ROXY_NO_COPY_MOVE(FLockGuard)

private:
    TLock& Lock;
};

class FSpinLock
{
public:
    ~FSpinLock() = default;

    ROXY_NO_COPY_MOVE(FSpinLock)

    ROXY_INLINE void Lock() noexcept
    {
        while (AtomicFlag.test_and_set(std::memory_order_acquire))
        {
            std::this_thread::yield();
        }
    }

    ROXY_INLINE void UnLock() noexcept
    {
        AtomicFlag.clear(std::memory_order_release);
    }

    ROXY_NODISCARD ROXY_INLINE bool TryLock() noexcept
    {
        return !AtomicFlag.test_and_set(std::memory_order_acquire);
    }

private:
    std::atomic_flag AtomicFlag {};
};

static_assert(CLock<FSpinLock>);

class FMutexLock
{
public:
    ~FMutexLock() = default;

    ROXY_NO_COPY_MOVE(FMutexLock)

    ROXY_INLINE void Lock() noexcept { Mutex.lock(); }

    ROXY_INLINE void UnLock() noexcept { Mutex.unlock(); }

    ROXY_NODISCARD ROXY_INLINE bool TryLock() noexcept { return Mutex.try_lock(); }

private:
    FMutex Mutex {};
};

static_assert(CLock<FMutexLock>);

}
