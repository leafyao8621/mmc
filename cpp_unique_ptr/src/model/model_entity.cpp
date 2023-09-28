#include "model.h"

size_t MMC::Model::Entity::Hash::operator()(const Entity &a) const {
    size_t *x = (size_t*)&a.entry_time;
    return *x ^ a.id;
}

bool MMC::Model::Entity::Equal::operator()(
    const Entity &a, const Entity &b) const {
    return a.id == b.id && a.entry_time == b.entry_time;
}

void MMC::Model::Entity::log(std::ostream &os) const {
    os <<
    "Entity:" << std::endl <<
    "ID: " << this->id << std::endl <<
    "Entry Time: " << this->entry_time << std::endl;
}
