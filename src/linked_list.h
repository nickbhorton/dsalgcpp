#ifndef LINKED_LIST_HEADER
#define LINKED_LIST_HEADER
#include <algorithm>
#include <memory>
#include <optional>
#include <stdexcept>
#include <sstream>

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
    LinkedList(LinkedList&& other)
        : length_(other.length_), head_(std::move(other.head_))
    {
        other.length_ = 0;
    }
    LinkedList& operator=(LinkedList&& other)
    {
        std::swap(head_, other.head_);
        length_ = other.length_;
        other.length_ = 0;
        return *this;
    };

    // Deleted copy stuff for now
    LinkedList(const LinkedList& other) = delete;
    LinkedList& operator=(const LinkedList& other) = delete;

    bool insert(size_t index, const T& new_data)
    {
        auto new_node = std::make_unique<LinkedListNode<T>>(new_data);
        if (index > length_) {
            throw std::out_of_range("linked list index out of range");
        } else if (index == 0) {
            // seems like this is a generic thing that should have a function
            new_node.get()->next_ = std::move(head_);
            head_ = std::move(new_node);
        } else {
            LinkedListNode<T>* pb = head_.get();
            for (size_t i = 0; i < index - 1; i++) {
                pb = pb->get_next();
            }
            new_node.get()->next_ = std::move(pb->next_);
            pb->next_ = std::move(new_node);
        }

        length_++;
        return true;
    }

    bool push_front(const T& new_data)
    {
        return insert(0, new_data);
    }

    bool push_back(const T& new_data)
    {
        return insert(length_, new_data);
    }

    T delete_at(size_t index)
    {
        if (index >= length_ || length_ == 0) {
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

    T pop_front()
    {
        return delete_at(0);
    }

    T pop_back()
    {
        return delete_at(length_ - 1);
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
    size_t length() const { return length_; }

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

    std::string to_string(std::string_view sep = " ") const
    {
        std::stringstream ss;
        LinkedListNode<T>* p = head_.get();
        while (p != nullptr) {
            if (p->get_next() == nullptr) {
                ss << p->get_data();
            } else {
                ss << p->get_data() << sep;
            }
            p = p->get_next();
        }
        return ss.str();
    }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const LinkedList<T>& ll)
{
    os << ll.to_string(" ");
    return os;
}
#endif
