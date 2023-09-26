#include "../../engine.h"

MMC::Engine::EventQueue::ArrivalEvent::ArrivalEvent(
    size_t id, double timestamp) {
    this->id = id;
    this->_timestamp = timestamp;
}

void MMC::Engine::EventQueue::ArrivalEvent::execute(Engine &engine) {
    engine.event_queue().add_arrival_event(
        engine.increment_id(),
        this->_timestamp + engine.model().next_arrival()
    );
}

void MMC::Engine::EventQueue::ArrivalEvent::execute(
    Engine &engine, std::ostream &os) {
    Event::log(os);
    os << "Type: Arrival" << std::endl;
    engine.event_queue().add_arrival_event(
        engine.increment_id(),
        this->_timestamp + engine.model().next_arrival()
    );
}
