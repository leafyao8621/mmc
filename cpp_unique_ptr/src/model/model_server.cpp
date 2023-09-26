#include "model.h"

MMC::Model::Server::Server(double mu, uint64_t c, bool is_last) {
    this->mu = mu;
    this->c = c;
    this->is_last = is_last;
    this->slots.resize(c, nullptr);
}

void MMC::Model::Server::enqueue(Entity *entity) {
    this->queue.push_back(entity);
}
