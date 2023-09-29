#include "../engine.h"

MMC::Engine::Stats::Stats() {
    this->in_cnt = 0;
    this->out_cnt = 0;
    this->tis = 0;
}

void MMC::Engine::Stats::increment_in() {
    ++this->in_cnt;
}

void MMC::Engine::Stats::add_out(double tis) {
    ++this->out_cnt;
    this->tis =
        this->tis * (this->out_cnt - 1) / this->out_cnt + tis / this->out_cnt;
}

void MMC::Engine::Stats::log(std::ostream &os) {
    os <<
    "Stats:" << std::endl <<
    "In Cnt: " << this->in_cnt << std::endl <<
    "Out Cnt: " << this->out_cnt << std::endl <<
    "TIS: " << this->tis << std::endl;
}
