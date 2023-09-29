#include "engine.h"

MMC::Engine::EventQueue::~EventQueue() {
    for (auto &i : this->data) {
        delete i;
    }
}

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
    std::pop_heap(this->data.begin(), this->data.end(), this->comp);
    delete this->data.back();
    this->data.pop_back();
}

size_t MMC::Engine::EventQueue::size() {
    return this->data.size();
}

void MMC::Engine::EventQueue::add_arrival_event(
    size_t id, double timestamp) {
    this->data.push_back(new ArrivalEvent(id, timestamp));
    std::push_heap(this->data.begin(), this->data.end(), this->comp);
}

void MMC::Engine::EventQueue::add_enqueue_event(
    size_t id, double timestamp, size_t idx, const Model::Entity *entity) {
    this->data.push_back(
        new EnqueueEvent(id, timestamp, idx, entity)
    );
    std::push_heap(this->data.begin(), this->data.end(), this->comp);
}

void MMC::Engine::EventQueue::add_dequeue_event(
    size_t id, double timestamp, size_t idx, size_t slot) {
    this->data.push_back(
        new DequeueEvent(id, timestamp, idx, slot)
    );
    std::push_heap(this->data.begin(), this->data.end(), this->comp);
}

void MMC::Engine::EventQueue::add_entry_event(
    size_t id, double timestamp, size_t idx, const Model::Entity *entity) {
    this->data.push_back(
        new EntryEvent(id, timestamp, idx, entity)
    );
    std::push_heap(this->data.begin(), this->data.end(), this->comp);
}

void MMC::Engine::EventQueue::add_transfer_event(
    size_t id, double timestamp, size_t from, size_t slot, size_t to) {
    this->data.push_back(
        new TransferEvent(id, timestamp, from, slot, to)
    );
    std::push_heap(this->data.begin(), this->data.end(), this->comp);
}

void MMC::Engine::EventQueue::add_departure_event(
    size_t id, double timestamp, size_t slot) {
    this->data.push_back(
        new DepartureEvent(id, timestamp, slot)
    );
    std::push_heap(this->data.begin(), this->data.end(), this->comp);
}
