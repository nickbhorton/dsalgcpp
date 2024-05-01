#ifndef BINARY_SEARCH_TREE_HEADER
#define BINARY_SEARCH_TREE_HEADER

#include <memory>
#include <sstream>
#include <string>

template <typename Data, typename Key = int> struct BSTNode {
    Key key;
    Data data;
    size_t height;
    BSTNode<Data, Key>* parent;
    std::unique_ptr<BSTNode<Data, Key>> left;
    std::unique_ptr<BSTNode<Data, Key>> right;
    BSTNode(const Key& key, const Data& data)
        : key(key), data(data), height(), parent(nullptr), left(nullptr),
          right(nullptr){};
    BSTNode(const Key& key, const Data& data, BSTNode* parent)
        : key(key), data(data), height(), parent(parent), left(nullptr),
          right(nullptr){};
};

template <typename Data, typename Key = int>
BSTNode<Data, Key>* bst_successor(BSTNode<Data, Key>* x)
{
    if (x->right != nullptr) {
        return bst_minimum(x->right.get());
    }
    BSTNode<Data, Key>* y = x->parent;
    while (y != nullptr and x == y->right.get()) {
        x = y;
        y = y->parent;
    }
    return y;
}

template <typename Data, typename Key = int>
BSTNode<Data, Key>* bst_predecessor(BSTNode<Data, Key>* x)
{
    if (x->left != nullptr) {
        return bst_maximum(x->left.get());
    }
    BSTNode<Data, Key>* y = x->parent;
    while (y != nullptr and x == y->left.get()) {
        x = y;
        y = y->parent;
    }
    return y;
}

template <typename Data, typename Key = int>
BSTNode<Data, Key>* bst_search(BSTNode<Data, Key>* x, const Key& key)
{
    if (x == nullptr or key == x->key) {
        return x;
    }
    if (key < x->key) {
        return bst_search(x->left.get(), key);
    } else {
        return bst_search(x->right.get(), key);
    }
}
// this is faster
template <typename Data, typename Key = int>
BSTNode<Data, Key>* bst_search_iterative(BSTNode<Data, Key>* x, const Key& key)
{
    while (x != nullptr and key != x->key) {
        if (key < x->key) {
            x = x->left.get();
        } else {
            x = x->right.get();
        }
    }
    return x;
}
template <typename Data, typename Key = int>
BSTNode<Data, Key>* bst_minimum(BSTNode<Data, Key>* ptr)
{
    while (ptr->left) {
        ptr = ptr->left.get();
    }
    return ptr;
}
template <typename Data, typename Key = int>
BSTNode<Data, Key>* bst_maximum(BSTNode<Data, Key>* ptr)
{
    while (ptr->right) {
        ptr = ptr->right.get();
    }
    return ptr;
}

template <typename Data, typename Key = int> class BST
{
    std::unique_ptr<BSTNode<Data, Key>> root;

    std::stringstream& to_key_string_helper(
        std::stringstream& ss,
        const BSTNode<Data, Key>* ptr
    ) const
    {
        if (ptr == nullptr) {
            return ss;
        }
        to_key_string_helper(ss, ptr->left.get());
        ss << ptr->key << " ";
        to_key_string_helper(ss, ptr->right.get());
        return ss;
    }

public:
    bool empty() const { return !root; }
    void rotate_right(BSTNode<Data, Key>* y)
    {
        std::unique_ptr<BSTNode<Data, Key>> x = std::move(y->left);
        y->left = std::move(x->right);
        if (y->parent != nullptr) {
            // y is a left child of its parent
            if (y->parent->left.get() == y) {
                y->parent->left = std::move(x);
            }
            // y is a right child of its parent
            else {
                y->parent->right = std::move(x);
            }
        } else {
            x->right = std::move(root);
            root = std::move(x);
        }
    }
    BSTNode<Data, Key>* search(const Key& key) const
    {
        return bst_search_iterative(root.get(), key);
    }
    BSTNode<Data, Key>* minimum() const { return bst_minimum(root.get()); }
    BSTNode<Data, Key>* maximum() const { return bst_maximum(root.get()); }
    void insert(const Key& key, const Data& data)
    {
        if (empty()) {
            root = std::make_unique<BSTNode<Data, Key>>(key, data);
            return;
        }
        BSTNode<Data, Key>* ptr = root.get();
        BSTNode<Data, Key>* parent_ptr = nullptr;
        size_t height = 0;
        while (ptr != nullptr) {
            if (key < ptr->key) {
                parent_ptr = ptr;
                ptr = ptr->left.get();
                height++;
            } else {
                parent_ptr = ptr;
                ptr = ptr->right.get();
                height++;
            }
        }
        if (key < parent_ptr->key) {
            parent_ptr->left =
                std::make_unique<BSTNode<Data, Key>>(key, data, parent_ptr);
            parent_ptr->left->height = height;
        } else {
            parent_ptr->right =
                std::make_unique<BSTNode<Data, Key>>(key, data, parent_ptr);
            parent_ptr->right->height = height;
        }
    }
    std::string to_key_string() const
    {
        std::stringstream ss;
        to_key_string_helper(ss, root.get());
        std::string s = ss.str();
        if (s.empty()) {
            return s;
        }
        // removing the last space
        return s.substr(0, s.length() - 1);
    }
};

#endif
