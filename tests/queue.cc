#include "queue.h"
#include "array_list.h"
#include "linked_list.h"

#include "doctest.h"

TEST_SUITE("Queue")
{
    TEST_CASE("push and dequeue are the standard functions")
    {
        Queue<int, LinkedList<int>> q1{};
        CHECK(q1.enqueue(1));
        CHECK(q1.enqueue(2));
        CHECK(q1.enqueue(3));
        CHECK(q1.enqueue(4));
        CHECK(q1.enqueue(5));
        CHECK(q1.size() == 5);
        CHECK(q1.dequeue() == 1);
        CHECK(q1.dequeue() == 2);
        CHECK(q1.dequeue() == 3);
        CHECK(q1.dequeue() == 4);
        CHECK(q1.dequeue() == 5);
        CHECK(q1.size() == 0);

        Queue<int, LinkedList<int>> q2{};
        CHECK(q2.enqueue(1));
        CHECK(q2.enqueue(2));
        CHECK(q2.enqueue(3));
        CHECK(q2.enqueue(4));
        CHECK(q2.enqueue(5));
        CHECK(q2.size() == 5);
        CHECK(q2.dequeue() == 1);
        CHECK(q2.dequeue() == 2);
        CHECK(q2.dequeue() == 3);
        CHECK(q2.dequeue() == 4);
        CHECK(q2.dequeue() == 5);
        CHECK(q2.size() == 0);
    }
}
