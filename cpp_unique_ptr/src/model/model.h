#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <vector>
#include <unordered_set>
#include <tuple>
#include <list>

#include "../util/generator.h"

namespace MMC {
    class Model {
        double lambda;
        Generator gen;
    public:
        class Entity {
        public:
            double entry_time;
            class Hash {
            public:
                size_t operator()(const Entity &a) const;
            };
        };
        class Server {
            double mu;
            size_t c;
            bool _is_last;
            std::list<Entity*> queue;
            std::vector<Entity*> slots;
        public:
            Server(double mu, size_t c, bool is_last);
            const bool &is_last();
            void enqueue(Entity *entity);
            double dequeue(size_t slot);
            Entity *remove(size_t slot);
        };
    private:
        std::vector<Server> servers;
        std::unordered_set<Entity, Entity::Hash> entities;
    public:
        void initialize(
            unsigned seed, double lambda, size_t n, double *mu, size_t *c);
        double next_arrival();
    };
}

#endif
