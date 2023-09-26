#include "model.h"

size_t MMC::Model::Entity::Hash::operator()(const Entity &a) const {
    size_t *x = (size_t*)&a;
    return *x;
}

void MMC::Model::initialize(
    unsigned seed, double lambda, size_t n, double *mu, size_t *c) {
    this->gen.seed(seed);
    this->lambda = lambda;
    this->servers.reserve(n);
    double *iter_mu = mu;
    size_t *iter_c = c;
    for (size_t i = 0; i < n; ++i, ++iter_mu, ++iter_c) {
        this->servers.push_back(Server(*iter_mu, *iter_c, i == n - 1));
    }
}

double MMC::Model::next_arrival() {
    return this->gen(this->lambda);
}
