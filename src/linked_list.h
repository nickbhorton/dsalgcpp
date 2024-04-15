#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER
#include <algorithm>
#include <cassert>
#include <memory>
#include <optional>
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
        // don't know why this will fail atm. but leaving option open.
        return true;
    }

    bool push_back(const T& new_data)
    {
        if (head_ == nullptr) {
            head_ = std::make_unique<LinkedListNode<T>>(new_data);
            length_++;
            return true;
        }
        LinkedListNode<T>* pf = head_.get();
        LinkedListNode<T>* pb = head_.get();

        while (pf != nullptr) {
            pb = pf;
            pf = pf->get_next();
        }
        pb->next_ = std::make_unique<LinkedListNode<T>>(new_data);
        length_++;
        return true;
    }

    T pop_front()
    {
        if (length_ == 0) {
            throw std::out_of_range("linked list index out of range");
        }
        std::unique_ptr<LinkedListNode<T>> e = std::move(head_);
        head_ = std::move(e.get()->next_);
        length_--;
        return e.get()->get_data();
    }

    T pop_back()
    {
        if (length_ == 0) {
            throw std::out_of_range("linked list index out of range");
        } else if (length_ == 1) {
            std::unique_ptr<LinkedListNode<T>> p = std::move(head_);
            length_--;
            return p.get()->get_data();
        }
        LinkedListNode<T>* pf = head_.get();
        LinkedListNode<T>* pb = head_.get();

        while (pf->get_next() != nullptr) {
            pb = pf;
            pf = pf->get_next();
        }
        std::unique_ptr<LinkedListNode<T>> p = std::move(pb->next_);
        length_--;
        return p.get()->get_data();
    }

    T delete_at(size_t index)
    {
        if (index >= length_) {
            throw std::out_of_range("linked list index out of range");
        }
        if (index == 0) {
            std::unique_ptr<LinkedListNode<T>> p = std::move(head_);
            head_ = std::move(p.get()->next_);
            length_--;
            return p.get()->get_data();
        }
        LinkedListNode<T>* b = head_.get();
        LinkedListNode<T>* f = head_.get()->next_.get();
        for (size_t i = 1; i < index; i++) {
            b = f;
            f = f->next_.get();
        }
        if (f->next_ == nullptr) {
            T val = f->get_data();
            // this line invalidates f which is why we copied it above. See
            // explination below.
            b->next_ = nullptr;
            length_--;
            return val;
        }

        T val = f->get_data();
        // With god as my witness. b->next_ is a
        // std::unique_ptr<LinkedListNode<T> that is owned by *b (which is a
        // LinkedListNode<T>). While f is a LinkedListNode<T>* that has the
        // value &(b->next_.get()) therefore f->next_ is owned by *f. So we are
        // giving ownership of f->next_ (b->next_.get()->next_) to b->next_ but
        // b->next_ already owns something so that something is deallocated. I
        // have 85% convidence in this explination. My two other lines of
        // evidence are: it tests correctly and the test executable passes
        // valgrind.
        b->next_ = std::move(f->next_);
        length_--;
        return val;
    }

    bool contains(const T& value) const
    {
        LinkedListNode<T>* p = head_.get();
        while (p != nullptr) {
            if (p->get_data() == value) {
                return true;
            }
            p = p->get_next();
        }
        return false;
    }

    std::optional<size_t> index_of(const T& value) const
    {
        LinkedListNode<T>* p = head_.get();
        size_t counter = 0;
        while (p != nullptr) {
            if (p->get_data() == value) {
                return counter;
            }
            p = p->get_next();
            counter++;
        }
        return {};
    }

    /// accessors
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

    /// @breif Does not perform range checks. Will segfault if index is wrong.
    T& operator[](size_t index)
    {
        LinkedListNode<T>* p = head_.get();
        for (size_t i = 0; i < index; i++) {
            p = p->get_next();
        };
        return p->data_;
    }
};

#endif
