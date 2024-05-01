#include <cstdlib>
#include <matplot/matplot.h>

int main()
{
    std::vector<double> x;
    for (size_t i = 0; i < 1'000'000; i++) {
        x.push_back(
            static_cast<double>(rand()) / static_cast<double>(RAND_MAX)
        );
    }
    auto h = matplot::hist(x, 100);
    std::cout << "Histogram with " << h->num_bins() << " bins" << std::endl;

    matplot::show();
}
