#include "../../engine.h"

MMC::Engine::EventQueue::EntryEvent::EntryEvent(
    size_t id,
    double timestamp,
    size_t idx,
    const Model::Entity *entity) {
    this->id = id;
    this->_timestamp = timestamp;
    this->idx = idx;
    this->entity = entity;
}

void MMC::Engine::EventQueue::EntryEvent::execute(Engine &engine) {
    Model &model = engine.model();
    EventQueue &event_queue = engine.event_queue();
    size_t slot = model.enter(this->idx, this->entity);
    double timestamp = model.next_service(this->idx);
    if (model.is_last(this->idx)) {
        event_queue.add_departure_event(
            engine.increment_id(),
            timestamp,
            slot
        );
    } else {
        event_queue.add_transfer_event(
            engine.increment_id(),
            timestamp,
            this->idx,
            slot,
            this->idx + 1
        );
    }
}

void MMC::Engine::EventQueue::EntryEvent::execute(
    Engine &engine, std::ostream &os) {
    Event::log(os);
    os <<
    "Type: Entry" << std::endl <<
    "IDX: " << this->idx << std::endl;
    this->entity->log(os);
    Model &model = engine.model();
    EventQueue &event_queue = engine.event_queue();
    size_t slot = model.enter(this->idx, this->entity);
    double timestamp = this->_timestamp + model.next_service(this->idx);
    if (model.is_last(this->idx)) {
        event_queue.add_departure_event(
            engine.increment_id(),
            timestamp,
            slot
        );
    } else {
        event_queue.add_transfer_event(
            engine.increment_id(),
            timestamp,
            this->idx,
            slot,
            this->idx + 1
        );
    }
}
