#include "stack.h"

TEST_CASE("push and pop are the standard functions") {
    Stack<int> s{};
    CHECK(s.push(1));
    CHECK(s.size() == 1);
    CHECK(s.pop() == 1);
    CHECK(s.size() == 0);
}
