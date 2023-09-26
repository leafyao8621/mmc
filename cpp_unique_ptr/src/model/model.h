#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <cstdint>
#include <vector>

#include "../util/generator.h"

namespace MMC {
    class Model {
        double lambda;
        MMC::Generator gen;
    public:
        struct Entity {
            double entry_time;
        };
        class Server {
            double mu;
            uint64_t c;
            std::vector<Entity*> queue;
            std::vector<Entity*> slots;
        public:
            Server(double mu, uint64_t c);
            void enqueue(Entity *entity);
            double dequeue(uint64_t slot);
        };
    private:
        std::vector<Server> servers;
    public:
        void initialize(
            unsigned seed, double lambda, uint64_t n, double *mu, uint64_t *c);
        double next_arrival();
    };
}

#endif
