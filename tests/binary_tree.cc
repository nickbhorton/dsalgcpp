#include "binary_tree.h"
#include "doctest.h"

TEST_CASE("binary tree can be default constructed")
{
    BinaryTree<int, BinaryTreeNodeNC<int>> bt{};
}

TEST_CASE("insert is used to add an element")
{
    BinaryTree<int, BinaryTreeNodeNC<int>> bt{};
    bt.insert(5);
    CHECK(bt.to_string() == std::string("5"));
    bt.insert(10);
    CHECK(bt.to_string() == std::string("5(null,10)"));
    bt.insert(4);
    CHECK(bt.to_string() == std::string("5(4,10)"));
    SUBCASE("inserting same element will not change the tree")
    {
        bt.insert(4);
        CHECK(bt.to_string() == std::string("5(4,10)"));
    }
}

TEST_CASE("search can be used to get an element")
{
    BinaryTree<int, BinaryTreeNodeNC<int>> bt{};
    bt.insert(5);
    CHECK(bt.search(5).has_value());
    bt.insert(10);
    CHECK(bt.search(5).has_value());
    bt.insert(4);
    CHECK(bt.search(5).has_value());
}
