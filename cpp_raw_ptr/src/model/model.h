#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <iostream>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <list>

#include "../util/generator.h"

namespace MMC {
    class Model {
        size_t id;
        double lambda;
        size_t _last_idx;
        Generator gen;
    public:
        class Entity {
        public:
            size_t id;
            double entry_time;
            class Hash {
            public:
                size_t operator()(const Entity &a) const;
            };
            class Equal {
            public:
                bool operator()(const Entity &a, const Entity &b) const;
            };
            void log(std::ostream &os) const;
        };
        class Server {
            double _mu;
            size_t c;
            size_t _available;
            bool _is_last;
            std::list<const Entity*> queue;
            std::vector<const Entity*> slots;
        public:
            Server(double mu, size_t c, bool is_last);
            const bool &is_last() const;
            const double &mu() const;
            const size_t &available() const;
            size_t queue_length() const;
            void enqueue(const Entity *entity);
            void dequeue(size_t slot);
            size_t enter(const Entity *entity);
            const Entity *remove(size_t slot);
            void log(std::ostream &os) const;
        };
    private:
        std::vector<Server> servers;
        std::unordered_set<Entity, Entity::Hash, Entity::Equal> entities;
    public:
        void initialize(
            unsigned seed, double lambda, size_t n, double *mu, size_t *c);
        const size_t &last_idx() const;
        double next_arrival();
        double next_service(size_t idx);
        const Entity *create_entity(double timestamp);
        const size_t &available(size_t idx) const;
        const bool &is_last(size_t idx) const;
        size_t queue_length(size_t idx) const;
        void enqueue(size_t idx, const Entity *entity);
        void dequeue(size_t idx, size_t slot);
        size_t enter(size_t idx, const Entity *entity);
        double depart(size_t slot);
        const Entity *remove(size_t idx, size_t slot);
        void log(std::ostream &os) const;
    };
}

#endif
