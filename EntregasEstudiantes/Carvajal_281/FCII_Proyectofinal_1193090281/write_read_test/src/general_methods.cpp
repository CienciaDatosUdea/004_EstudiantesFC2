# include "ising_public_interface.h"

# include <random>

/*
Random number generator. Here, using a fixed seed (like 42) eliminates that variable during the testing phase; however, the sequence is still pseudo-random with a period of 2^19937 - 1, so this does not compromise the implementation in any way.
Alternatively,    static std::mt19937_64 rng{ std::random_device{}() };    uses the current state of the OS if possible.
*/

std::mt19937_64& GlobalRng() {
    static std::mt19937_64 rng{ std::random_device{}() };
    return rng;
}


    


