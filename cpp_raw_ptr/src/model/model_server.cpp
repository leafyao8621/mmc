#include "model.h"

MMC::Model::Server::Server(double mu, size_t c, bool is_last) {
    this->_mu = mu;
    this->c = c;
    this->_available = c;
    this->_is_last = is_last;
    this->slots.resize(c, nullptr);
}

const bool &MMC::Model::Server::is_last() const {
    return this->_is_last;
}

const double &MMC::Model::Server::mu() const {
    return this->_mu;
}

const size_t &MMC::Model::Server::available() const {
    return this->_available;
}

size_t MMC::Model::Server::queue_length() const {
    return this->queue.size();
}

void MMC::Model::Server::enqueue(const Entity *entity) {
    this->queue.push_back(entity);
}

void MMC::Model::Server::dequeue(size_t slot) {
    const Entity *temp = this->queue.front();
    this->queue.pop_front();
    this->slots[slot] = temp;
    --this->_available;
}

size_t MMC::Model::Server::enter(const Entity *entity) {
    size_t idx = 0;
    for (auto &i : this->slots) {
        if (!i) {
            i = entity;
            break;
        }
        ++idx;
    }
    --this->_available;
    return idx;
}

const MMC::Model::Entity *MMC::Model::Server::remove(size_t slot) {
    const Entity *temp = this->slots[slot];
    this->slots[slot] = nullptr;
    ++this->_available;
    return temp;
}

void MMC::Model::Server::log(std::ostream &os) const {
    os <<
    "Server:" << std::endl <<
    "lambda: " << this->_mu << std::endl <<
    "c: " << this->c << std::endl <<
    "Available: " << this->_available << std::endl;
    os << "Queue:" << std::endl;
    for (const auto &i : this->queue) {
        i->log(os);
    }
    os << "Slots:" << std::endl;
    for (const auto &i : this->slots) {
        if (i) {
            i->log(os);
        } else {
            os << "EMPTY" << std::endl;
        }
    }
}
