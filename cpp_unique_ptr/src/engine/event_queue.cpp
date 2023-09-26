#include "engine.h"

void MMC::Engine::EventQueue::log(std::ostream &os) {
    os << "Event Queue:" << std::endl;
    for (auto &i : this->data) {
        i->log(os);
    }
}

MMC::Engine::EventQueue::Event &MMC::Engine::EventQueue::get_event() {
    return *this->data.front();
}

void MMC::Engine::EventQueue::remove_event() {
    std::pop_heap(this->data.begin(), this->data.end());
    this->data.pop_back();
}

size_t MMC::Engine::EventQueue::size() {
    return this->data.size();
}

void MMC::Engine::EventQueue::add_arrival_event(
    uint64_t id, double timestamp) {
    this->data.push_back(std::make_unique<ArrivalEvent>(id, timestamp));
    std::push_heap(this->data.begin(), this->data.end(), this->comp);
}
