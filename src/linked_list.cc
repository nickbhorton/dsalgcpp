#include "linked_list.h"
#include <stdexcept>

TEST_CASE("linked list node constructor and accessors")
{
    LinkedListNode<int> l(3);
    CHECK(l.get_data() == 3);
    CHECK(l.get_next() == nullptr);
}

TEST_CASE("linked list can be default constructed")
{
    LinkedList<int> ll{};

    REQUIRE(ll.get_length() == 0);
    ll.push_front(1);
    REQUIRE(ll.get_length() == 1);
    CHECK(ll.at(0) == 1);
    ll.push_front(97);
    REQUIRE(ll.get_length() == 2);
    CHECK(ll.at(0) == 97);
    CHECK(ll.at(1) == 1);
    ll.push_front(131);
    REQUIRE(ll.get_length() == 3);
    CHECK(ll.at(0) == 131);
    CHECK(ll.at(1) == 97);
    CHECK(ll.at(2) == 1);
    SUBCASE("at throws") {
        CHECK_THROWS_AS(ll.at(3), std::out_of_range);
    }
    SUBCASE("operator[] can also be used for access")
    {
        CHECK(ll[0] == 131);
        CHECK(ll[1] == 97);
        CHECK(ll[2] == 1);
    }
    SUBCASE("operator[] can mutate list")
    {
        ll[2] = -100;
        CHECK(ll[2] == -100);
    }
}
