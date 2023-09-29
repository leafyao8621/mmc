#include "../../engine.h"

MMC::Engine::EventQueue::ArrivalEvent::ArrivalEvent(
    size_t id, double timestamp) {
    this->id = id;
    this->_timestamp = timestamp;
}

void MMC::Engine::EventQueue::ArrivalEvent::execute(Engine &engine) {
    Model &model = engine.model();
    EventQueue &event_queue = engine.event_queue();
    Stats &stats = engine.stats();
    const Model::Entity *entity = model.create_entity(this->_timestamp);
    event_queue.add_arrival_event(
        engine.increment_id(),
        this->_timestamp + model.next_arrival()
    );
    if (this->_timestamp >= engine.warmup()) {
        stats.increment_in();
    }
    if (model.available(0)) {
        event_queue.add_entry_event(
            engine.increment_id(),
            this->_timestamp,
            0,
            entity
        );
    } else {
        event_queue.add_enqueue_event(
            engine.increment_id(), this->_timestamp, 0, entity);
    }
}

void MMC::Engine::EventQueue::ArrivalEvent::execute(
    Engine &engine, std::ostream &os) {
    Event::log(os);
    os << "Type: Arrival" << std::endl;
    Model &model = engine.model();
    EventQueue &event_queue = engine.event_queue();
    Stats &stats = engine.stats();
    const Model::Entity *entity = model.create_entity(this->_timestamp);
    event_queue.add_arrival_event(
        engine.increment_id(),
        this->_timestamp + model.next_arrival()
    );
    if (this->_timestamp >= engine.warmup()) {
        stats.increment_in();
    }
    if (model.available(0)) {
        event_queue.add_entry_event(
            engine.increment_id(),
            this->_timestamp,
            0,
            entity
        );
    } else {
        event_queue.add_enqueue_event(
            engine.increment_id(), this->_timestamp, 0, entity);
    }
}
