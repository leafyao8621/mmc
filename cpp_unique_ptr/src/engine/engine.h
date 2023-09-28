#ifndef ENGINE_ENGINE_H_
#define ENGINE_ENGINE_H_

#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

#include "../model/model.h"

namespace MMC {
    class Engine {
        double _time_end;
        double _warmup;
        double _time_now;
        size_t id;
        MMC::Model _model;
    public:
        class EventQueue {
        public:
            class Event {
            protected:
                size_t id;
                double _timestamp;
            public:
                class Comparator {
                public:
                    bool operator()(
                        std::unique_ptr<Event> &a,
                        std::unique_ptr<Event> &b);
                };
                void log(std::ostream &os);
                virtual void execute(Engine &engine) = 0;
                virtual void execute(Engine &engine, std::ostream &os) = 0;
                const double &timestamp();
            };
            class ArrivalEvent : public Event {
            public:
                ArrivalEvent(size_t id, double timestamp);
                void execute(Engine &engine);
                void execute(Engine &engine, std::ostream &os);
            };
            class EnqueueEvent : public Event {
                size_t idx;
                const Model::Entity *entity;
            public:
                EnqueueEvent(
                    size_t id,
                    double timestamp,
                    size_t idx,
                    const Model::Entity *entity);
                void execute(Engine &engine);
                void execute(Engine &engine, std::ostream &os);
            };
            class DequeueEvent : public Event {
                size_t idx, slot;
            public:
                DequeueEvent(
                    size_t id, double timestamp, size_t idx, size_t slot);
                void execute(Engine &engine);
                void execute(Engine &engine, std::ostream &os);
            };
            class EntryEvent : public Event {
                size_t idx;
                const Model::Entity *entity;
            public:
                EntryEvent(
                    size_t id,
                    double timestamp,
                    size_t idx,
                    const Model::Entity *entity);
                void execute(Engine &engine);
                void execute(Engine &engine, std::ostream &os);
            };
            class TransferEvent : public Event {
                size_t from, slot, to;
            public:
                TransferEvent(
                    size_t id,
                    double timestamp,
                    size_t from,
                    size_t slot,
                    size_t to);
                void execute(Engine &engine);
                void execute(Engine &engine, std::ostream &os);
            };
            class DepartureEvent : public Event {
                size_t slot;
            public:
                DepartureEvent(size_t id, double timestamp, size_t slot);
                void execute(Engine &engine);
                void execute(Engine &engine, std::ostream &os);
            };
        private:
            std::vector<std::unique_ptr<Event> > data;
            Event::Comparator comp;
        public:
            void add_arrival_event(size_t id, double timestamp);
            void add_enqueue_event(
                size_t id,
                double timestamp,
                size_t idx,
                const Model::Entity *entity);
            void add_dequeue_event(
                size_t id,
                double timestamp,
                size_t idx,
                size_t slot);
            void add_entry_event(
                size_t id,
                double timestamp,
                size_t idx,
                const Model::Entity *entity);
            void add_transfer_event(
                size_t id,
                double timestamp,
                size_t from,
                size_t slot,
                size_t to);
            void add_departure_event(
                size_t id,
                double timestamp,
                size_t slot);
            Event &get_event();
            void remove_event();
            size_t size();
            void log(std::ostream &os);
        };
    private:
        EventQueue _event_queue;
    public:
        class Stats {
            uint64_t in_cnt;
            uint64_t out_cnt;
            double tis;
        public:
            Stats();
            void increment_in();
            void add_out(double tis);
            void log(std::ostream &os);
        };
    private:
        Stats _stats;
    public:
        Engine(
            double time_end,
            double warmup,
            unsigned seed,
            double lambda,
            size_t n,
            double *mu,
            size_t *c);
        EventQueue &event_queue();
        MMC::Model &model();
        Stats &stats();
        const double &time_end();
        const double &warmup();
        const double &time_now();
        void run();
        void run(std::ostream &os);
        uint64_t increment_id();
        void log(std::ostream &os);
    };
}

#endif
