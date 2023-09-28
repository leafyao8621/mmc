#include "../../engine.h"

MMC::Engine::EventQueue::DepartureEvent::DepartureEvent(
    size_t id, double timestamp, size_t slot) {
    this->id = id;
    this->_timestamp = timestamp;
    this->slot = slot;
}

void MMC::Engine::EventQueue::DepartureEvent::execute(Engine &engine) {
    Model &model = engine.model();
    Stats &stats = engine.stats();
    double entry_time = model.depart(this->slot);
    stats.add_out(this->_timestamp - entry_time);
}

void MMC::Engine::EventQueue::DepartureEvent::execute(
    Engine &engine, std::ostream &os) {
    Event::log(os);
    os <<
    "Type: Departure" << std::endl <<
    "Slot: " << this->slot << std::endl;
    Model &model = engine.model();
    Stats &stats = engine.stats();
    double entry_time = model.depart(this->slot);
    stats.add_out(this->_timestamp - entry_time);
}
