#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>
#include <unordered_set>
#include <tuple>
#include <list>

#include "../util/generator.h"

namespace MMC {
    class Model {
        size_t id;
        double lambda;
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
        };
        class Server {
            double _mu;
            size_t c;
            bool _is_last;
            std::list<const Entity*> queue;
            std::vector<const Entity*> slots;
        public:
            Server(double mu, size_t c, bool is_last);
            const bool &is_last();
            const double &mu();
            void enqueue(const Entity *entity);
            void dequeue(size_t slot);
            const Entity *remove(size_t slot);
        };
    private:
        std::vector<Server> servers;
        std::unordered_set<Entity, Entity::Hash, Entity::Equal> entities;
    public:
        void initialize(
            unsigned seed, double lambda, size_t n, double *mu, size_t *c);
        double next_arrival();
        const Entity *create_entity(double timestamp);
    };
}

#endif
