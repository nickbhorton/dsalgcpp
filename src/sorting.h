#ifndef SORTING_HEADER
#define SORTING_HEADER

#include <vector>

template <typename T> auto insertion_sort(std::vector<T> A) -> std::vector<T>
{
    for (size_t i = 1; i < A.size(); i++) {
        T key = A[i];
        int j = i - 1;
        while (j > -1 and A[j] > key) {
            A[j + 1] = A[j];
            j = j - 1;
        }
        A[j + 1] = key;
    }
    return A;
}

#endif
