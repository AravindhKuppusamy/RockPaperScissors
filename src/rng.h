#ifndef ROCKPAPERSCISSORS_RNG_H
#define ROCKPAPERSCISSORS_RNG_H

#include <random>

/**
 * A random number generator suitable for generating 64 bit id's for the
 * Destler Dubloon.
 *
 * @author Sean Strout @ RIT CS
 */
class RNG {
public:
    /**
     * Creates the random number generator with a random seed.
     */
    RNG();

    /**
     * Create a seeded random number generator.
     *
     * @param seed the seed
     */
    RNG(unsigned int seed);

    /**
     * Get the next pseudo-random number.
     *
     * @return next number
     */
    unsigned int rand();

private:
    /** the mersenne twister generator */
    std::mt19937_64 gen_;

    /** produces random numbers that are uniformly distributed */
    std::uniform_int_distribution<unsigned int> dis_;
};


#endif //ROCKPAPERSCISSORS_RNG_H
