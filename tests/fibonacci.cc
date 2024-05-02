#include <chrono>
#include <iostream>
#include <vector>

int fibonacci_recursive(int n)
{
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    return fibonacci_recursive(n - 1) + fibonacci_recursive(n - 2);
}

int fibonacci_recursive_memoized_aux(int n, std::vector<int>& saved)
{
    if (saved[n] >= 0) {
        return saved[n];
    }
    int n1 = fibonacci_recursive_memoized_aux(n - 1, saved);
    int n2 = fibonacci_recursive_memoized_aux(n - 2, saved);
    saved[n] = n1 + n2;
    return saved[n];
}

int fibonacci_recursive_memoized(int n)
{
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }
    std::vector<int> saved(n + 1, -1);
    saved[0] = 0;
    saved[1] = 1;
    return fibonacci_recursive_memoized_aux(n, saved);
}

int main(int argc, char** argv)
{
    int n = 10;
    if (argc >= 2) {
        n = std::stoi(argv[1]);
    }
    auto start = std::chrono::high_resolution_clock::now();
    std::cout << "base n=" << n << ", " << fibonacci_recursive(n) << "\n";
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << " ms\n";

    start = std::chrono::high_resolution_clock::now();
    std::cout << "mem n=" << n << ", " << fibonacci_recursive_memoized(n)
              << "\n";
    stop = std::chrono::high_resolution_clock::now();
    duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << duration.count() << " ms\n";
}
