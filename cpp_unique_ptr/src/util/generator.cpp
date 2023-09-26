#include <cmath>

#include "generator.h"

void MMC::Generator::seed(unsigned seed) {
    this->gen.seed(seed);
}

#define URAND (this->gen() / (double)0xffffffff)

double MMC::Generator::operator()(double rate) {
    return -log(URAND) / rate;
}
