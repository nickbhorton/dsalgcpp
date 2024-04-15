#ifndef STACK_HEADER
#define STACK_HEADER
#include "linked_list.h"

template <typename T> class Stack
{
    LinkedList<T> ll;

public:
    Stack() : ll() {}

    bool push(const T& val) {
        return ll.push_front(val);
    }
    T pop() {
        return ll.pop_front();
    }
    size_t size() const {
        return ll.get_length();
    }
};

#endif
