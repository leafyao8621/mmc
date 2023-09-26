#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <cstdint>
#include <vector>
#include <unordered_set>

#include "../util/generator.h"

namespace MMC {
    class Model {
        double lambda;
        MMC::Generator gen;
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
            uint64_t c;
            bool is_last;
            std::vector<Entity*> queue;
            std::vector<Entity*> slots;
        public:
            Server(double mu, uint64_t c, bool is_last);
            void enqueue(Entity *entity);
            double dequeue(uint64_t slot);
        };
    private:
        std::vector<Server> servers;
        std::unordered_set<Entity, Entity::Hash> entities;
    public:
        void initialize(
            unsigned seed, double lambda, uint64_t n, double *mu, uint64_t *c);
        double next_arrival();
    };
}

#endif
