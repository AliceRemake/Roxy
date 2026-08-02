#define DOCTEST_CONFIG_NO_EXCEPTIONS_BUT_WITH_ALL_ASSERTS
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

#include <RoxySTD/RoxySTD.h>

using namespace Roxy;

TEST_CASE("Roxy::TQueue (UnSafe) – full interface")
{
    SUBCASE("IsEmpty on new queue returns true")
    {
        TQueue<int> Queue;
        CHECK(Queue.IsEmpty() == true);
    }

    SUBCASE("Num on new queue returns 0")
    {
        TQueue<int> Queue;
        CHECK(Queue.Num() == 0);
    }

    SUBCASE("EnQueue increases Num and IsEmpty becomes false")
    {
        TQueue<int> Queue;
        Queue.EnQueue(42);
        CHECK(Queue.IsEmpty() == false);
        CHECK(Queue.Num() == 1);
    }

    SUBCASE("DeQueue returns true and retrieves the element, then Num decreases")
    {
        TQueue<int> Queue;
        Queue.EnQueue(10);
        int val = 0;
        bool success = Queue.DeQueue(val);
        CHECK(success == true);
        CHECK(val == 10);
        CHECK(Queue.IsEmpty() == true);
        CHECK(Queue.Num() == 0);
    }

    SUBCASE("FIFO order is preserved with DeQueue")
    {
        TQueue<int> Queue;
        Queue.EnQueue(1);
        Queue.EnQueue(2);
        Queue.EnQueue(3);
        CHECK(Queue.Num() == 3);

        int val;
        REQUIRE(Queue.DeQueue(val));
        CHECK(val == 1);
        REQUIRE(Queue.DeQueue(val));
        CHECK(val == 2);
        REQUIRE(Queue.DeQueue(val));
        CHECK(val == 3);
        CHECK(Queue.IsEmpty());
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

        std::string out;
        REQUIRE(Queue.DeQueue(out));
        CHECK(out == "movable");
    }

    SUBCASE("Copy semantics on EnQueue")
    {
        TQueue<std::string> Queue;
        std::string s = "copy me";
        Queue.EnQueue(s);
        CHECK(!s.empty());

        std::string out;
        REQUIRE(Queue.DeQueue(out));
        CHECK(out == "copy me");
        CHECK(s == "copy me");
    }

    SUBCASE("Interleaved EnQueue and DeQueue")
    {
        TQueue<int> Queue;
        Queue.EnQueue(10);
        Queue.EnQueue(20);
        CHECK(Queue.Num() == 2);

        int val;
        REQUIRE(Queue.DeQueue(val));
        CHECK(val == 10);

        Queue.EnQueue(30);
        CHECK(Queue.First() == 20);
        CHECK(Queue.Last() == 30);
        CHECK(Queue.Num() == 2);

        REQUIRE(Queue.DeQueue(val));
        CHECK(val == 20);
        REQUIRE(Queue.DeQueue(val));
        CHECK(val == 30);
        CHECK(Queue.IsEmpty());
    }

    SUBCASE("Safe usage pattern: check IsEmpty before DeQueue/First/Last")
    {
        TQueue<int> Queue;
        if (!Queue.IsEmpty())
        {
            int dummy;
            Queue.DeQueue(dummy);
            (void)Queue.First();
            (void)Queue.Last();
        }
        CHECK(Queue.IsEmpty());
    }

    SUBCASE("DeQueue on empty queue returns false")
    {
        TQueue<int> Queue;
        int val = 0;
        bool success = Queue.DeQueue(val);
        CHECK(success == false);
        CHECK(val == 0);
    }
}
