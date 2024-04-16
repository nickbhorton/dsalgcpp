#include "stack.h"
#include "array_list.h"
#include "linked_list.h"

TEST_SUITE("Stack")
{
    TEST_CASE("push and pop are the standard functions")
    {
        Stack<int, LinkedList<int>> s1{};
        CHECK(s1.push(1));
        CHECK(s1.size() == 1);
        CHECK(s1.pop() == 1);
        CHECK(s1.size() == 0);

        Stack<int, ArrayList<int>> s2{};
        CHECK(s2.push(1));
        CHECK(s2.size() == 1);
        CHECK(s2.pop() == 1);
        CHECK(s2.size() == 0);
    }
}
