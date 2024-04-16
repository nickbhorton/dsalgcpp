#ifndef QUEUE_HEADER
#define QUEUE_HEADER

#include <cstddef>

template <typename T, typename Storage> class Queue {
    Storage s;
    
public:
    Queue() : s() {}

    bool enqueue(const T& val) {
        return s.push_front(val);
    }
    T dequeue() {
        return s.pop_back();
    }
    size_t size() const {
        return s.length();
    }
};

#endif // !QUEUE_HEADER

