#include "sorting.h"

#include "doctest.h"

TEST_CASE("insertion sort")
{
    std::vector<int> v = {4, 2, 10, -32, 4, 1, 42};
    v = insertion_sort(v);
    CHECK_EQ(v[0], -32);
    CHECK_EQ(v[1], 1);
    CHECK_EQ(v[2], 2);
    CHECK_EQ(v[3], 4);
    CHECK_EQ(v[4], 4);
    CHECK_EQ(v[5], 10);
    CHECK_EQ(v[6], 42);
}
