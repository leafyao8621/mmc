#ifndef UTIL_GENERATOR_H_
#define UTIL_GENERATOR_H_

#include <random>

namespace MMC {
    class Generator {
        std::mt19937 gen;
    public:
        void seed(unsigned seed);
        double operator()(double rate);
    };
}

#endif
