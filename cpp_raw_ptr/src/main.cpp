#include "engine/engine.h"

int main() {
    double mu[3] =
        {
            2, 3, 4
        };
    uint64_t c[3] =
        {
            4, 3, 2
        };
    for (size_t i = 0; i < 100; ++i) {
        MMC::Engine engine(
            10000,
            2000,
            20,
            5,
            3,
            mu,
            c
        );
        engine.run();
        engine.stats().log(std::cout);
    }
    return 0;
}
