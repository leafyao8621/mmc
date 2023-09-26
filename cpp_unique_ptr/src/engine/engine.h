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
        uint64_t id;
        MMC::Model _model;
    public:
        class EventQueue {
        public:
            class Event {
            protected:
                uint64_t id;
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
                ArrivalEvent(uint64_t id, double timestamp);
                void execute(Engine &engine);
                void execute(Engine &engine, std::ostream &os);
            };
        private:
            std::vector<std::unique_ptr<Event> > data;
            Event::Comparator comp;
        public:
            void add_arrival_event(uint64_t id, double timestamp);
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
        Stats stats;
    public:
        Engine(
            double time_end,
            double warmup,
            unsigned seed,
            double lambda,
            uint64_t n,
            double *mu,
            uint64_t *c);
        void run();
        void run(std::ostream &os);
        EventQueue &event_queue();
        MMC::Model &model();
        const double &time_end();
        const double &warmup();
        const double &time_now();
        uint64_t increment_id();
        void log(std::ostream &os);
    };
}

#endif
