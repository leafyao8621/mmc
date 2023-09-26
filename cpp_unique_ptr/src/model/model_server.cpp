#include "model.h"

MMC::Model::Server::Server(double mu, size_t c, bool is_last) {
    this->mu = mu;
    this->c = c;
    this->is_last = is_last;
    this->slots.resize(c, nullptr);
}

void MMC::Model::Server::enqueue(Entity *entity) {
    this->queue.push_back(entity);
}

std::tuple<double, bool> MMC::Model::Server::dequeue(size_t slot) {
    Entity *temp = this->queue.front();
    this->queue.pop_front();
    this->slots[slot] = temp;
    return std::make_tuple(this->mu, this->is_last);
}

MMC::Model::Entity *MMC::Model::Server::remove(size_t slot) {
    Entity *temp = this->slots[slot];
    this->slots[slot] = nullptr;
    return temp;
}
