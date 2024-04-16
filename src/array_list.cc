#include "array_list.h"
#include <stdexcept>

#include "doctest.h"

TEST_SUITE("ArrayList")
{
    TEST_CASE("array list can be default constructed")
    {
        ArrayList<int> ll{};
        REQUIRE(ll.get_length() == 0);
    }

    TEST_CASE("push_front adds an element at the front")
    {
        ArrayList<int> ll{};
        CHECK(ll.push_front(1));
        REQUIRE(ll.get_length() == 1);
        CHECK(ll.at(0) == 1);
        CHECK(ll.push_front(97));
        REQUIRE(ll.get_length() == 2);
        CHECK(ll.at(0) == 97);
        CHECK(ll.at(1) == 1);
        CHECK(ll.push_front(131));
        REQUIRE(ll.get_length() == 3);
        CHECK(ll.at(0) == 131);
        CHECK(ll.at(1) == 97);
        CHECK(ll.at(2) == 1);
    }

    TEST_CASE("at accesor is bounds checked and it will throw")
    {
        ArrayList<int> ll{};
        CHECK_THROWS_AS(ll.at(3), std::out_of_range);
    }

    TEST_CASE("operator[] can also be used for access")
    {
        ArrayList<int> ll{};
        CHECK(ll.push_front(1));
        CHECK(ll.push_front(97));
        CHECK(ll.push_front(131));
        REQUIRE(ll.get_length() == 3);
        CHECK(ll[0] == 131);
        CHECK(ll[1] == 97);
        CHECK(ll[2] == 1);
    }

    TEST_CASE("operator[] can mutate list")
    {
        ArrayList<int> ll{};
        CHECK(ll.push_front(1));
        CHECK(ll.push_front(97));
        CHECK(ll.push_front(131));
        REQUIRE(ll.get_length() == 3);
        CHECK(ll[0] == 131);
        ll[0] = -101;
        CHECK(ll[0] == -101);

        CHECK(ll[1] == 97);
        ll[1] = -102;
        CHECK(ll[1] == -102);

        CHECK(ll[2] == 1);
        ll[2] = -100;
        CHECK(ll[2] == -100);
    }

    TEST_CASE("push_back adds an element at the back")
    {
        ArrayList<int> ll{};
        CHECK(ll.push_back(1));
        REQUIRE(ll.get_length() == 1);
        CHECK(ll.at(0) == 1);
        CHECK(ll.push_back(97));
        REQUIRE(ll.get_length() == 2);
        CHECK(ll.at(0) == 1);
        CHECK(ll.at(1) == 97);
        CHECK(ll.push_back(131));
        REQUIRE(ll.get_length() == 3);
        CHECK(ll.at(0) == 1);
        CHECK(ll.at(1) == 97);
        CHECK(ll.at(2) == 131);
    }

    TEST_CASE("pop_front removes and return element from the front")
    {
        ArrayList<int> ll{};
        CHECK(ll.push_back(1));
        CHECK(ll.push_back(97));
        CHECK(ll.push_back(131));
        REQUIRE(ll.get_length() == 3);
        CHECK(ll.at(0) == 1);
        CHECK(ll.at(1) == 97);
        CHECK(ll.at(2) == 131);
        int current = ll.pop_front();
        CHECK(current == 1);
        REQUIRE(ll.get_length() == 2);
        CHECK(ll.at(0) == 97);
        CHECK(ll.at(1) == 131);
        current = ll.pop_front();
        CHECK(current == 97);
        REQUIRE(ll.get_length() == 1);
        CHECK(ll.at(0) == 131);
        current = ll.pop_front();
        CHECK(current == 131);
        REQUIRE(ll.get_length() == 0);
        SUBCASE("pop_front will throw if length is zero")
        {
            CHECK_THROWS_AS(ll.pop_front(), std::out_of_range);
        }
    }

    TEST_CASE("pop_back removes and return element from the back")
    {
        ArrayList<int> ll{};
        CHECK(ll.push_back(1));
        CHECK(ll.push_back(97));
        CHECK(ll.push_back(131));
        REQUIRE(ll.get_length() == 3);
        CHECK(ll.at(0) == 1);
        CHECK(ll.at(1) == 97);
        CHECK(ll.at(2) == 131);
        int current = ll.pop_back();
        CHECK(current == 131);
        REQUIRE(ll.get_length() == 2);
        CHECK(ll.at(0) == 1);
        CHECK(ll.at(1) == 97);
        current = ll.pop_back();
        CHECK(current == 97);
        REQUIRE(ll.get_length() == 1);
        CHECK(ll.at(0) == 1);
        current = ll.pop_back();
        CHECK(current == 1);
        REQUIRE(ll.get_length() == 0);
        SUBCASE("pop_back will throw if length is zero")
        {
            CHECK_THROWS_AS(ll.pop_front(), std::out_of_range);
        }
    }

    TEST_CASE("constains returns true if element is in list")
    {
        ArrayList<int> ll{};
        for (int i = 0; i < 10; i += 2) {
            ll.push_back(i);
        }
        REQUIRE(ll.get_length() == 5);
        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0) {
                CHECK(ll.contains(i));
            } else {
                CHECK(!ll.contains(i));
            }
        }
    }

    TEST_CASE("index_of returns and optinal index")
    {
        ArrayList<int> ll{};
        for (int i = 0; i < 10; i += 2) {
            ll.push_back(i);
        }
        REQUIRE(ll.get_length() == 5);
        for (int i = 0; i < 10; i++) {
            if (i % 2 == 0) {
                auto opt = ll.index_of(i);
                REQUIRE(opt);
                CHECK(opt.value() * 2 == i);
            } else {
                auto opt = ll.index_of(i);
                CHECK(!opt);
            }
        }
    }

    TEST_CASE("delete_at removes and return element at index")
    {
        ArrayList<int> ll{};
        CHECK(ll.push_back(1));
        CHECK(ll.push_back(97));
        CHECK(ll.push_back(131));
        CHECK(ll.push_back(235));
        CHECK(ll.push_back(400));
        REQUIRE(ll.get_length() == 5);
        int current = ll.delete_at(4);
        REQUIRE(ll.get_length() == 4);
        CHECK(current == 400);
        CHECK(ll.at(0) == 1);
        CHECK(ll.at(1) == 97);
        CHECK(ll.at(2) == 131);
        CHECK(ll.at(3) == 235);

        current = ll.delete_at(2);
        REQUIRE(ll.get_length() == 3);
        CHECK(current == 131);
        CHECK(ll.at(0) == 1);
        CHECK(ll.at(1) == 97);
        CHECK(ll.at(2) == 235);

        current = ll.delete_at(1);
        REQUIRE(ll.get_length() == 2);
        CHECK(current == 97);
        CHECK(ll.at(0) == 1);
        CHECK(ll.at(1) == 235);

        current = ll.delete_at(0);
        REQUIRE(ll.get_length() == 1);
        CHECK(current == 1);
        CHECK(ll.at(0) == 235);

        current = ll.delete_at(0);
        REQUIRE(ll.get_length() == 0);
        CHECK(current == 235);

        SUBCASE("delete_at will throw if index is out of range")
        {
            CHECK_THROWS_AS(ll.delete_at(100), std::out_of_range);
        }
    }

    TEST_CASE("the to_string function allows seperator specification")
    {
        ArrayList<int> ll{};
        ll.push_back(1);
        ll.push_back(2);
        ll.push_back(3);
        ll.push_back(4);
        CHECK(std::string("1 2 3 4") == ll.to_string());
        CHECK(std::string("1;2;3;4") == ll.to_string(";"));
        CHECK(std::string("1 SEP 2 SEP 3 SEP 4") == ll.to_string(" SEP "));
    }

    TEST_CASE("move constructor and move operator are defined")
    {
        ArrayList<int> ll1{};
        ll1.push_back(1);
        ll1.push_back(2);
        ll1.push_back(3);
        ll1.push_back(4);
        CHECK(ll1.get_length() == 4);
        CHECK(std::string("1 2 3 4") == ll1.to_string());

        ArrayList<int> ll2(std::move(ll1));
        CHECK(ll2.get_length() == 4);
        CHECK(ll1.get_length() == 0);
        CHECK(std::string("") == ll1.to_string());
        CHECK(std::string("1 2 3 4") == ll2.to_string());

        ArrayList<int> ll3{};
        ll3 = std::move(ll2);
        CHECK(ll2.get_length() == 0);
        CHECK(ll3.get_length() == 4);
        CHECK(std::string("") == ll2.to_string());
        CHECK(std::string("1 2 3 4") == ll3.to_string());
    }

    TEST_CASE("insert adds an element at index")
    {
        ArrayList<int> ll{};
        ll.push_back(0);
        ll.push_back(2);
        ll.push_back(3);
        CHECK(std::string("0 2 3") == ll.to_string());
        ll.insert(1, 1);
        CHECK(ll.get_length() == 4);
        CHECK(std::string("0 1 2 3") == ll.to_string());

        ll.insert(0, -1);
        CHECK(ll.get_length() == 5);
        CHECK(std::string("-1 0 1 2 3") == ll.to_string());

        ll.insert(5, 4);
        CHECK(ll.get_length() == 6);
        CHECK(std::string("-1 0 1 2 3 4") == ll.to_string());

        SUBCASE("insert will throw if index is out of range")
        {
            CHECK_THROWS_AS(ll.insert(100, 1), std::out_of_range);
        }
    }
}
