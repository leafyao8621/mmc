#include "model.h"

MMC::Model::Server::Server(double mu, uint64_t c) {
    this->mu = mu;
    this->c = c;
    this->slots.resize(c, nullptr);
}
