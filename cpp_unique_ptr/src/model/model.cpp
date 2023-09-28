#include "model.h"

void MMC::Model::initialize(
    unsigned seed, double lambda, size_t n, double *mu, size_t *c) {
    this->id = 0;
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

double MMC::Model::next_service(size_t idx) {
    return this->gen(this->servers[idx].mu());
}

const MMC::Model::Entity *MMC::Model::create_entity(double timestamp) {
    Entity entity {this->id++, timestamp};
    this->entities.insert(entity);
    auto ret = this->entities.find(entity);
    return &(*ret);
}

const size_t &MMC::Model::available(size_t idx) {
    return this->servers[idx].available();
}

const bool &MMC::Model::is_last(size_t idx) {
    return this->servers[idx].is_last();
}

void MMC::Model::enqueue(size_t idx, const Entity *entity) {
    this->servers[idx].enqueue(entity);
}

void MMC::Model::dequeue(size_t idx, size_t slot) {
    this->servers[idx].dequeue(slot);
}

size_t MMC::Model::enter(size_t idx, const Entity *entity) {
    return this->servers[idx].enter(entity);
}

const MMC::Model::Entity *MMC::Model::remove(size_t idx, size_t slot) {
    return this->servers[idx].remove(slot);
}

double MMC::Model::depart(size_t slot) {
    const Entity *entity = this->servers.back().remove(slot);
    this->entities.erase(*entity);
    return entity->entry_time;
}

void MMC::Model::log(std::ostream &os) const {
    os <<
    "Model:" << std::endl <<
    "lambda: " << this->lambda << std::endl;
    os << "Entities:" << std::endl;
    for (const auto &i : this->entities) {
        i.log(os);
    }
    os << "Servers:" << std::endl;
    for (const auto &i : this->servers) {
        i.log(os);
    }
}
