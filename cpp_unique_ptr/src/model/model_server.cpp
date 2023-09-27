#include "model.h"

MMC::Model::Server::Server(double mu, size_t c, bool is_last) {
    this->_mu = mu;
    this->c = c;
    this->_is_last = is_last;
    this->slots.resize(c, nullptr);
}

const bool &MMC::Model::Server::is_last() {
    return this->_is_last;
}

const double &MMC::Model::Server::mu() {
    return this->_mu;
}

void MMC::Model::Server::enqueue(const Entity *entity) {
    this->queue.push_back(entity);
}

void MMC::Model::Server::dequeue(size_t slot) {
    const Entity *temp = this->queue.front();
    this->queue.pop_front();
    this->slots[slot] = temp;
}

const MMC::Model::Entity *MMC::Model::Server::remove(size_t slot) {
    const Entity *temp = this->slots[slot];
    this->slots[slot] = nullptr;
    return temp;
}
