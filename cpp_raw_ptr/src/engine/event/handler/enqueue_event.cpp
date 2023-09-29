#include "../../engine.h"

MMC::Engine::EventQueue::EnqueueEvent::EnqueueEvent(
    size_t id, double timestamp, size_t idx, const Model::Entity *entity) {
    this->id = id;
    this->_timestamp = timestamp;
    this->idx = idx;
    this->entity = entity;
}

void MMC::Engine::EventQueue::EnqueueEvent::execute(Engine &engine) {
    engine.model().enqueue(this->idx, this->entity);
}

void MMC::Engine::EventQueue::EnqueueEvent::execute(
    Engine &engine, std::ostream &os) {
    Event::log(os);
    os << "Type: Enqueue" << std::endl;
    this->entity->log(os);
    engine.model().enqueue(this->idx, this->entity);
}
