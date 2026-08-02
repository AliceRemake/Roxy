#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxyLog/RoxyLog.h>
#include <RoxyChrono/RoxyChrono.h>
#include <RoxyMT/RoxyMT.h>

using namespace Roxy;

template<typename T>
using MutexQueue = TQueue<T, EThreadSafety::Safe, EThreadSafetyImpl::MutexLock>;
template<typename T>
using SpinQueue  = TQueue<T, EThreadSafety::Safe, EThreadSafetyImpl::SpinLock>;

template<typename QueueType>
void RunProducerConsumerTest(const int NumProducers, const int ItemsPerProducer)
{
    QueueType Queue;
    std::vector<std::thread> Producers;

    for (int p = 0; p < NumProducers; ++p)
    {
        Producers.emplace_back([&](int Offset) {
            for (int i = 0; i < ItemsPerProducer; ++i)
            {
                int Value = Offset * ItemsPerProducer + i;
                Queue.Enqueue(Value);
            }
        }, p);
    }

    for (auto& Thread : Producers) Thread.join();

    std::vector<int> Consumed;
    while (!Queue.IsEmpy())
        Consumed.push_back(Queue.Dequeue());

    REQUIRE(Consumed.size() == static_cast<size_t>(NumProducers * ItemsPerProducer));
    std::sort(Consumed.begin(), Consumed.end());
    std::vector<int> Expected(NumProducers * ItemsPerProducer);
    std::iota(Expected.begin(), Expected.end(), 0);
    CHECK(Consumed == Expected);
}

TEST_CASE("MutexLock Queue – correctness")
{
    RunProducerConsumerTest<MutexQueue<int>>(4, 250);
}

TEST_CASE("SpinLock Queue – correctness")
{
    RunProducerConsumerTest<SpinQueue<int>>(4, 250);
}

TEST_CASE("Benchmark: MutexLock vs SpinLock queue throughput")
{
    Log::SetLevel(Log::ELogLevel::Info);
    Log::SetPattern(Log::DefaultPattern);

    constexpr int TotalItems = 1000000;
    constexpr int NumThreads = 4;
    constexpr int ItemsPerThread = TotalItems / NumThreads;

    auto RunBenchmark = [&](auto& Queue, const char* Name) {
        std::vector<std::thread> Threads;
        Chrono::FTimer Timer;

        for (int t = 0; t < NumThreads; ++t)
        {
            Threads.emplace_back([&](int Start) {
                for (int i = 0; i < ItemsPerThread; ++i)
                    Queue.Enqueue(Start + i);
            }, t * ItemsPerThread);
        }
        for (auto& Thread : Threads) Thread.join();

        int Remaining = TotalItems;
        while (Remaining > 0)
        {
            if (!Queue.IsEmpy())
            {
                Queue.Dequeue();
                --Remaining;
            }
            else
                std::this_thread::yield();
        }
        double Ms = Timer.GetElapsed<Chrono::ETimeUnit::MiS>();
        ROXY_INFO(Log::ELogCategory::Default, "{} elapsed: {:.3f} ms", Name, Ms);
    };

    MutexQueue<int> MQ;
    SpinQueue<int>  SQ;
    RunBenchmark(MQ, "MutexLock");
    RunBenchmark(SQ, "SpinLock");
}
