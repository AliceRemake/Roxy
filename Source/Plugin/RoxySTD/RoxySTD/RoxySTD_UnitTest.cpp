#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxySTD/RoxySTD.h>

using namespace Roxy;

TEST_CASE("Roxy::TQueue (UnSafe) – full interface")
{
    SUBCASE("IsEmpy on new queue returns true")
    {
        TQueue<int> Queue;
        CHECK(Queue.IsEmpy() == true);
    }

    SUBCASE("Num on new queue returns 0")
    {
        TQueue<int> Queue;
        CHECK(Queue.Num() == 0);
    }

    SUBCASE("EnQueue increases Num and IsEmpy becomes false")
    {
        TQueue<int> Queue;
        Queue.EnQueue(42);
        CHECK(Queue.IsEmpy() == false);
        CHECK(Queue.Num() == 1);
    }

    SUBCASE("DeQueue returns the element and reduces Num")
    {
        TQueue<int> Queue;
        Queue.EnQueue(10);
        int val = Queue.DeQueue();
        CHECK(val == 10);
        CHECK(Queue.IsEmpy() == true);
        CHECK(Queue.Num() == 0);
    }

    SUBCASE("FIFO order is preserved")
    {
        TQueue<int> Queue;
        Queue.EnQueue(1);
        Queue.EnQueue(2);
        Queue.EnQueue(3);
        CHECK(Queue.Num() == 3);
        CHECK(Queue.DeQueue() == 1);
        CHECK(Queue.DeQueue() == 2);
        CHECK(Queue.DeQueue() == 3);
        CHECK(Queue.IsEmpy());
    }

    SUBCASE("First and Last (non‑const)")
    {
        TQueue<int> Queue;
        Queue.EnQueue(5);
        Queue.EnQueue(10);
        Queue.EnQueue(15);

        CHECK(Queue.First() == 5);
        CHECK(Queue.Last() == 15);

        Queue.First() = 100;
        CHECK(Queue.First() == 100);
        Queue.Last() = 200;
        CHECK(Queue.Last() == 200);
    }

    SUBCASE("First and Last on const queue")
    {
        TQueue<std::string> Queue;
        Queue.EnQueue("alpha");
        Queue.EnQueue("beta");

        const auto& cq = Queue;
        CHECK(cq.First() == "alpha");
        CHECK(cq.Last() == "beta");
    }

    SUBCASE("Move semantics on EnQueue")
    {
        TQueue<std::string> Queue;
        std::string s = "movable";
        Queue.EnQueue(std::move(s));
        CHECK(s.empty());
        std::string out = Queue.DeQueue();
        CHECK(out == "movable");
    }

    SUBCASE("Copy semantics on EnQueue")
    {
        TQueue<std::string> Queue;
        std::string s = "copy me";
        Queue.EnQueue(s);
        CHECK(!s.empty());
        std::string out = Queue.DeQueue();
        CHECK(out == "copy me");
        CHECK(s == "copy me");
    }

    SUBCASE("Interleaved EnQueue and DeQueue")
    {
        TQueue<int> Queue;
        Queue.EnQueue(10);
        Queue.EnQueue(20);
        CHECK(Queue.Num() == 2);
        CHECK(Queue.DeQueue() == 10);
        Queue.EnQueue(30);
        CHECK(Queue.First() == 20);
        CHECK(Queue.Last() == 30);
        CHECK(Queue.Num() == 2);
        CHECK(Queue.DeQueue() == 20);
        CHECK(Queue.DeQueue() == 30);
        CHECK(Queue.IsEmpy());
    }

    SUBCASE("Safe usage pattern: check IsEmpy before DeQueue/First/Last")
    {
        TQueue<int> Queue;
        if (!Queue.IsEmpy())
        {
            Queue.DeQueue();
            (void)Queue.First();
            (void)Queue.Last();
        }
        CHECK(Queue.IsEmpy());
    }
}
