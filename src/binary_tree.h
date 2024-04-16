#ifndef BINARY_TREE_HEADER
#define BINARY_TREE_HEADER

#include <iostream>
#include <memory>
#include <optional>
#include <sstream>

template <typename T> class BinaryTreeNodeNC
{
    T value_;
    std::unique_ptr<BinaryTreeNodeNC<T>> left_;
    std::unique_ptr<BinaryTreeNodeNC<T>> right_;

public:
    T value() const { return value_; }

    const BinaryTreeNodeNC<T>& get_left() const { return *left_.get(); }
    const BinaryTreeNodeNC<T>& get_right() const { return *right_.get(); }
    BinaryTreeNodeNC<T>* get_left_ptr() { return left_.get(); }
    BinaryTreeNodeNC<T>* get_right_ptr() { return right_.get(); }

    void set_left(const T& val)
    {
        left_ = std::make_unique<BinaryTreeNodeNC<T>>(val);
    }

    void set_right(const T& val)
    {
        right_ = std::make_unique<BinaryTreeNodeNC<T>>(val);
    }

    BinaryTreeNodeNC(const T& value)
        : value_(value), left_(nullptr), right_(nullptr)
    {
    }

    std::string to_string() const
    {
        std::stringstream ss;
        ss << value_;
        if (left_ || right_) {
            ss << "(";
            if (left_) {
                ss << left_->to_string();
            } else {
                ss << "null";
            }
            ss << ",";
            if (right_) {
                ss << right_->to_string();
            } else {
                ss << "null";
            }
            ss << ")";
        }
        return ss.str();
    }
};

template <typename T, typename Node> class BinaryTree
{
    size_t length_;
    std::unique_ptr<Node> root_;

public:
    BinaryTree() : root_(nullptr) {}

    void insert(const T& val)
    {
        if (root_ == nullptr) {
            root_ = std::make_unique<Node>(val);
            return;
        }
        Node* ptr = root_.get();
        while (true) {
            if (val < ptr->value()) {
                if (ptr->get_left_ptr() == nullptr) {
                    ptr->set_left(val);
                    break;
                } else {
                    ptr = ptr->get_left_ptr();
                }
            } else if (val > ptr->value()){
                if (ptr->get_right_ptr() == nullptr) {
                    ptr->set_right(val);
                    break;
                } else {
                    ptr = ptr->get_right_ptr();
                }
            }
            else {
                return;
            }
        }
    }

    std::optional<Node*> search(const T& key)
    {
        Node* ptr = root_.get();
        while (ptr != nullptr) {
            if (key == ptr->value()) {
                return ptr;
            } else if (key < ptr->value()) {
                ptr = ptr->get_left_ptr();
            } else {
                ptr = ptr->get_right_ptr();
            }
        }
        return {};
    }

    std::string to_string()
    {
        std::stringstream ss;
        if (root_) {
            ss << root_->to_string();
        }
        return ss.str();
    }
};

#endif // !BINARY_TREE_HEADER
