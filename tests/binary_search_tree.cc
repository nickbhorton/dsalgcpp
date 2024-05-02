#include "binary_search_tree.h"
#include "doctest.h"
#include <string>

TEST_CASE("BST insert")
{
    BST<std::string> bst{};
    bst.insert(5, std::string("hello world"));
    CHECK(bst.to_key_string() == "5");
    bst.insert(6, std::string("hello world"));
    CHECK(bst.to_key_string() == "5 6");
    bst.insert(4, std::string("hello world"));
    CHECK(bst.to_key_string() == "4 5 6");
    bst.insert(10, std::string("hello world"));
    bst.insert(-14, std::string("hello world"));
    CHECK(bst.to_key_string() == "-14 4 5 6 10");
}

TEST_CASE("BST search")
{
    BST<std::string> bst{};
    bst.insert(5, std::string("hello world"));
    bst.insert(6, std::string("hello world"));
    bst.insert(4, std::string("hello world"));
    bst.insert(10, std::string("hello world"));
    bst.insert(-14, std::string("hello world"));
    CHECK(bst.to_key_string() == "-14 4 5 6 10");
    REQUIRE(bst.search(-14) != nullptr);
    CHECK(bst.search(-14)->key == -14);
    CHECK(bst.search(-14)->data == "hello world");
    CHECK(bst.search(-14)->parent != nullptr);
}

TEST_CASE("BST min and max")
{
    BST<std::string> bst{};
    bst.insert(5, std::string("hello world"));
    bst.insert(6, std::string("hello world"));
    bst.insert(4, std::string("hello world"));
    bst.insert(10, std::string("hello world"));
    bst.insert(-14, std::string("hello world"));
    CHECK(bst.to_key_string() == "-14 4 5 6 10");
    REQUIRE(bst.minimum() != nullptr);
    REQUIRE(bst.minimum()->key == -14);
    REQUIRE(bst.minimum()->data == "hello world");
    REQUIRE(bst.minimum()->parent != nullptr);

    REQUIRE(bst.maximum() != nullptr);
    REQUIRE(bst.maximum()->key == 10);
    REQUIRE(bst.maximum()->data == "hello world");
    REQUIRE(bst.maximum()->parent != nullptr);
}

TEST_CASE("BST successor")
{
    BST<std::string> bst{};
    bst.insert(5, std::string("hello world"));
    bst.insert(6, std::string("hello world"));
    bst.insert(4, std::string("hello world"));
    bst.insert(10, std::string("hello world"));
    bst.insert(-14, std::string("hello world"));
    CHECK(bst.to_key_string() == "-14 4 5 6 10");
    BSTNode<std::string>* ptr = bst.minimum();
    REQUIRE(ptr != nullptr);
    CHECK(ptr->key == -14);
    CHECK(ptr->height == 2);
    ptr = bst_successor(ptr);
    REQUIRE(ptr != nullptr);
    CHECK(ptr->key == 4);
    CHECK(ptr->height == 1);
    ptr = bst_successor(ptr);
    REQUIRE(ptr != nullptr);
    CHECK(ptr->key == 5);
    CHECK(ptr->height == 0);
    ptr = bst_successor(ptr);
    REQUIRE(ptr != nullptr);
    CHECK(ptr->key == 6);
    CHECK(ptr->height == 1);
    ptr = bst_successor(ptr);
    REQUIRE(ptr != nullptr);
    CHECK(ptr->key == 10);
    CHECK(ptr->height == 2);
    ptr = bst_successor(ptr);
    REQUIRE(ptr == nullptr);
}

TEST_CASE("BST predecessor")
{
    BST<std::string> bst{};
    bst.insert(5, std::string("hello world"));
    bst.insert(6, std::string("hello world"));
    bst.insert(4, std::string("hello world"));
    bst.insert(10, std::string("hello world"));
    bst.insert(-14, std::string("hello world"));
    CHECK(bst.to_key_string() == "-14 4 5 6 10");
    BSTNode<std::string>* ptr = bst.maximum();
    REQUIRE(ptr != nullptr);
    CHECK(ptr->key == 10);
    ptr = bst_predecessor(ptr);
    REQUIRE(ptr != nullptr);
    CHECK(ptr->key == 6);
    ptr = bst_predecessor(ptr);
    REQUIRE(ptr != nullptr);
    CHECK(ptr->key == 5);
    ptr = bst_predecessor(ptr);
    REQUIRE(ptr != nullptr);
    CHECK(ptr->key == 4);
    ptr = bst_predecessor(ptr);
    REQUIRE(ptr != nullptr);
    CHECK(ptr->key == -14);
    ptr = bst_predecessor(ptr);
    REQUIRE(ptr == nullptr);
}

TEST_CASE("BST rotations")
{
    BST<std::string> bst{};
    bst.insert(0, std::string("hello world"));
    bst.insert(2, std::string("hello world"));
    bst.insert(-2, std::string("hello world"));
    bst.insert(1, std::string("hello world"));
    bst.insert(3, std::string("hello world"));
    bst.insert(-1, std::string("hello world"));
    bst.insert(-3, std::string("hello world"));
    REQUIRE(bst.to_key_string() == "-3 -2 -1 0 1 2 3");
    auto root = bst.search(0);
    // validating structure and height
    REQUIRE(root != nullptr);
    CHECK(root->key == 0);
    CHECK(root->height == 0);
    REQUIRE(root->left.get() != nullptr);
    CHECK(root->left->key == -2);
    CHECK(root->left->height == 1);
    REQUIRE(root->right.get() != nullptr);
    CHECK(root->right->key == 2);
    CHECK(root->right->height == 1);
    REQUIRE(root->left->left.get() != nullptr);
    CHECK(root->left->left->key == -3);
    CHECK(root->left->left->height == 2);
    REQUIRE(root->left->right.get() != nullptr);
    CHECK(root->left->right->key == -1);
    CHECK(root->left->right->height == 2);
    REQUIRE(root->right->left.get() != nullptr);
    CHECK(root->right->left->key == 1);
    CHECK(root->right->left->height == 2);
    REQUIRE(root->right->right.get() != nullptr);
    CHECK(root->right->right->key == 3);
    CHECK(root->right->right->height == 2);

    SUBCASE("rotate the root to the rigth")
    {
        bst.rotate_right(root);
        root = bst.search(-2);
        REQUIRE(root != nullptr);
        CHECK(root->key == -2);
        REQUIRE(root->left.get() != nullptr);
        CHECK(root->left->key == -3);
        REQUIRE(root->right.get() != nullptr);
        CHECK(root->right->key == 0);
        REQUIRE(root->right->right.get() != nullptr);
        CHECK(root->right->right->key == 2);
        REQUIRE(root->right->left.get() != nullptr);
        CHECK(root->right->left->key == -1);
        REQUIRE(root->right->right->right.get() != nullptr);
        CHECK(root->right->right->right->key == 3);
        REQUIRE(root->right->right->left.get() != nullptr);
        CHECK(root->right->right->left->key == 1);
    }
    SUBCASE("rotate right subtree to the rigth")
    {
        // not done
        /*
        bst.rotate_right(root->right.get());
        root = bst.search(-2);
        REQUIRE(root != nullptr);
        CHECK(root->key == -2);
        REQUIRE(root->left.get() != nullptr);
        CHECK(root->left->key == -3);
        REQUIRE(root->right.get() != nullptr);
        CHECK(root->right->key == 0);
        REQUIRE(root->right->right.get() != nullptr);
        CHECK(root->right->right->key == 2);
        REQUIRE(root->right->left.get() != nullptr);
        CHECK(root->right->left->key == -1);
        REQUIRE(root->right->right->right.get() != nullptr);
        CHECK(root->right->right->right->key == 3);
        REQUIRE(root->right->right->left.get() != nullptr);
        CHECK(root->right->right->left->key == 1);
        */
    }
}
