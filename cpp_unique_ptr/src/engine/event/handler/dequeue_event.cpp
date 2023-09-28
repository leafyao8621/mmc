#include "../../engine.h"

MMC::Engine::EventQueue::DequeueEvent::DequeueEvent(
    size_t id, double timestamp, size_t idx, size_t slot) {
    this->id = id;
    this->_timestamp = timestamp;
    this->idx = idx;
    this->slot = slot;
}

void MMC::Engine::EventQueue::DequeueEvent::execute(Engine &engine) {
    Model &model = engine.model();
    EventQueue &event_queue = engine.event_queue();
    model.dequeue(this->idx, this->slot);
    double timestamp = this->_timestamp + model.next_service(this->idx);
    if (model.is_last(this->idx)) {
        event_queue.add_departure_event(
            engine.increment_id(),
            timestamp,
            this->slot
        );
    } else {
        event_queue.add_transfer_event(
            engine.increment_id(),
            timestamp,
            this->idx,
            this->slot,
            this->idx + 1
        );
    }
}

void MMC::Engine::EventQueue::DequeueEvent::execute(
    Engine &engine, std::ostream &os) {
    Event::log(os);
    os <<
    "Type: Dequeue" << std::endl <<
    "IDX: " << this->idx << std::endl <<
    "Slot: " << this->slot << std::endl;
    Model &model = engine.model();
    EventQueue &event_queue = engine.event_queue();
    model.dequeue(this->idx, this->slot);
    double timestamp = this->_timestamp + model.next_service(this->idx);
    if (model.is_last(this->idx)) {
        event_queue.add_departure_event(
            engine.increment_id(),
            timestamp,
            this->slot
        );
    } else {
        event_queue.add_transfer_event(
            engine.increment_id(),
            timestamp,
            this->idx,
            this->slot,
            this->idx + 1
        );
    }
}
