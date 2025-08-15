#include <random>

/*
Random number generator. Here, using a fixed seed (like 42) would eliminate that variable during the testing phase; however, the sequence would still be pseudo-random with a period of 2^19937 - 1, so this would not compromise the implementation in any way. Alternatively, static std::mt19937_64 rng{ std::random_device{}() }; tries using the current state of the computer to seed the rng, if possible.
*/
std::mt19937_64& GlobalRng() {
    static std::mt19937_64 rng{ std::random_device{}() };
    return rng;
}
  
// returns a random number from the standard gaussian distribution
double UniformNormalNumber() {
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(GlobalRng());
}