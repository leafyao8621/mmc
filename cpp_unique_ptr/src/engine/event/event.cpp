#include "../engine.h"

bool MMC::Engine::EventQueue::Event::Comparator::operator()(
    std::unique_ptr<Event> &a,
    std::unique_ptr<Event> &b) {
    if (a->_timestamp != b->_timestamp) {
        return a->_timestamp > b->_timestamp;
    } else {
        return a->id > b->id;
    }
}
void MMC::Engine::EventQueue::Event::log(std::ostream &os) {
    os <<
    "Event:" << std::endl <<
    "ID: " << this->id << std::endl <<
    "Timestamp: " << this->_timestamp << std::endl;
}

const double &MMC::Engine::EventQueue::Event::timestamp() {
    return this->_timestamp;
}
