#include "engine.h"

MMC::Engine::Engine(
    double time_end,
    double warmup,
    unsigned seed,
    double lambda,
    uint64_t n,
    double *mu,
    uint64_t *c) {
    this->_time_end = time_end;
    this->_warmup = warmup;
    this->_time_now = 0;
    this->id = 0;
    this->_model.initialize(seed, lambda, n, mu, c);
}

void MMC::Engine::log(std::ostream &os) {
    os <<
    "Time End: " << this->_time_end << std::endl <<
    "Warmup: " << this->_warmup << std::endl <<
    "Time Now: " << this->_time_now << std::endl;
    this->_stats.log(os);
    this->_event_queue.log(os);
    this->_model.log(os);
}

MMC::Engine::EventQueue &MMC::Engine::event_queue() {
    return this->_event_queue;
}

MMC::Model &MMC::Engine::model() {
    return this->_model;
}

MMC::Engine::Stats &MMC::Engine::stats() {
    return this->_stats;
}

const double &MMC::Engine::time_end() {
    return this->_time_end;
}

const double &MMC::Engine::warmup() {
    return this->_warmup;
}

const double &MMC::Engine::time_now() {
    return this->_time_now;
}

uint64_t MMC::Engine::increment_id() {
    return this->id++;
}

void MMC::Engine::run() {
    this->event_queue().add_arrival_event(
        this->id++, this->model().next_arrival());
    for (
        ;
        this->_time_now <= this->_time_end &&
        this->event_queue().size();) {
        EventQueue::Event &event = this->event_queue().get_event();
        this->_time_now = event.timestamp();
        event.execute(*this);
        this->event_queue().remove_event();
    }
}

void MMC::Engine::run(std::ostream &os) {
    this->event_queue().add_arrival_event(
        this->id++, this->model().next_arrival());
    this->log(os);
    for (
        ;
        this->_time_now <= this->_time_end &&
        this->event_queue().size();) {
        EventQueue::Event &event = this->event_queue().get_event();
        this->_time_now = event.timestamp();
        event.execute(*this, os);
        this->event_queue().remove_event();
        this->log(os);
    }
}
