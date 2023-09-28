#include "../../engine.h"

MMC::Engine::EventQueue::TransferEvent::TransferEvent(
    size_t id,
    double timestamp,
    size_t from,
    size_t slot,
    size_t to) {
    this->id = id;
    this->_timestamp = timestamp;
    this->from = from;
    this->slot = slot;
    this->to = to;
}

void MMC::Engine::EventQueue::TransferEvent::execute(Engine &engine) {
    Model &model = engine.model();
    EventQueue &event_queue = engine.event_queue();
    const Model::Entity *entity = model.remove(this->from, this->slot);
    if (model.available(this->to)) {
        event_queue.add_entry_event(
            engine.increment_id(),
            this->_timestamp,
            this->to,
            entity
        );
    } else {
        event_queue.add_enqueue_event(
            engine.increment_id(), this->_timestamp, this->to, entity);
    }

}

void MMC::Engine::EventQueue::TransferEvent::execute(
    Engine &engine, std::ostream &os) {
    Event::log(os);
    os <<
    "Type: Transfer" << std::endl <<
    "From: " << this->from << std::endl <<
    "Slot: " << this->slot << std::endl <<
    "To: " << this->to << std::endl;
    Model &model = engine.model();
    EventQueue &event_queue = engine.event_queue();
    const Model::Entity *entity = model.remove(this->from, this->slot);
    if (model.available(this->to)) {
        event_queue.add_entry_event(
            engine.increment_id(),
            this->_timestamp,
            this->to,
            entity
        );
    } else {
        event_queue.add_enqueue_event(
            engine.increment_id(), this->_timestamp, this->to, entity);
    }
}
