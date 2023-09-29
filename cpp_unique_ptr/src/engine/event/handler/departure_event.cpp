#include "../../engine.h"

MMC::Engine::EventQueue::DepartureEvent::DepartureEvent(
    size_t id, double timestamp, size_t slot) {
    this->id = id;
    this->_timestamp = timestamp;
    this->slot = slot;
}

void MMC::Engine::EventQueue::DepartureEvent::execute(Engine &engine) {
    Model &model = engine.model();
    EventQueue &event_queue = engine.event_queue();
    Stats &stats = engine.stats();
    double entry_time = model.depart(this->slot);
    if (entry_time >= engine.warmup()) {
        stats.add_out(this->_timestamp - entry_time);
    }
    const double &last_idx = model.last_idx();
    if (model.queue_length(last_idx)) {
        event_queue.add_dequeue_event(
            engine.increment_id(),
            this->_timestamp,
            last_idx,
            this->slot
        );
    }
}

void MMC::Engine::EventQueue::DepartureEvent::execute(
    Engine &engine, std::ostream &os) {
    Event::log(os);
    os <<
    "Type: Departure" << std::endl <<
    "Slot: " << this->slot << std::endl;
    Model &model = engine.model();
    EventQueue &event_queue = engine.event_queue();
    Stats &stats = engine.stats();
    double entry_time = model.depart(this->slot);
    if (entry_time >= engine.warmup()) {
        stats.add_out(this->_timestamp - entry_time);
    }
    const double &last_idx = model.last_idx();
    if (model.queue_length(last_idx)) {
        event_queue.add_dequeue_event(
            engine.increment_id(),
            this->_timestamp,
            last_idx,
            this->slot
        );
    }
}
