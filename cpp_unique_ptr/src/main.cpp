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
    MMC::Engine engine(
        100,
        20,
        20,
        5,
        3,
        mu,
        c
    );
    engine.run(std::cout);
    return 0;
}
