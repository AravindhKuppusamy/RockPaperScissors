#include "rng.h"

using std::random_device;

RNG::RNG() :
        RNG{random_device{}()} {
}

RNG::RNG(unsigned int seed) :
        gen_{seed},
        dis_{0, 2} {
}

unsigned int RNG::rand() {
    return dis_(gen_);
}
