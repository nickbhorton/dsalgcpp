#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER
#include <cassert>
#include <memory>
#include <stdexcept>

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

template <typename T> class LinkedList;

template <typename T> class LinkedListNode
{
    friend LinkedList<T>;

    T data_;
    std::unique_ptr<LinkedListNode<T>> next_;

public:
    LinkedListNode(const T& data) : data_(data), next_(nullptr) {}

    T get_data() const { return data_; }
    LinkedListNode<T>* get_next() { return next_.get(); }
};

template <typename T> class LinkedList
{
    size_t length_;
    std::unique_ptr<LinkedListNode<T>> head_;

public:
    LinkedList() : length_(0), head_(nullptr) {}

    size_t get_length() const { return length_; }

    T at(size_t index) const
    {
        if (index >= length_) {
            throw std::out_of_range("linked list index out of range");
        }
        LinkedListNode<T>* p = head_.get();
        for (size_t i = 0; i < index; i++) {
            p = p->get_next();
        };
        return p->data_;
    }

    T& operator[](size_t index)
    {
        LinkedListNode<T>* p = head_.get();
        for (size_t i = 0; i < index; i++) {
            p = p->get_next();
        };
        return p->data_;
    }

    bool push_front(const T& new_data)
    {
        if (head_ != nullptr) {
            std::unique_ptr<LinkedListNode<T>> new_node_ptr =
                std::make_unique<LinkedListNode<T>>(new_data);
            head_.swap(new_node_ptr);
            head_.get()->next_ = std::move(new_node_ptr);
        } else {
            head_ = std::make_unique<LinkedListNode<T>>(new_data);
        }
        length_++;
        return true;
    }
};

#endif
