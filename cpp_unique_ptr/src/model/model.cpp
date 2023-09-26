#include "model.h"

void MMC::Model::initialize(
    unsigned seed, double lambda, uint64_t n, double *mu, uint64_t *c) {
    this->gen.seed(seed);
    this->lambda = lambda;
    this->servers.reserve(n);
    double *iter_mu = mu;
    uint64_t *iter_c = c;
    for (size_t i = 0; i < n; ++i, ++iter_mu, ++iter_c) {
        this->servers.push_back(
            MMC::Model::Server(*iter_mu, *iter_c, i == n - 1));
    }
}

double MMC::Model::next_arrival() {
    return this->gen(this->lambda);
}
