#ifndef STACK_HEADER
#define STACK_HEADER

#include "doctest.h"

#include <cstddef>
template <typename T, typename List> class Stack
{
    List s;

public:
    Stack() : s() {}

    bool push(const T& val) {
        return s.push_front(val);
    }
    T pop() {
        return s.pop_front();
    }
    size_t size() const {
        return s.length();
    }
};

#endif
