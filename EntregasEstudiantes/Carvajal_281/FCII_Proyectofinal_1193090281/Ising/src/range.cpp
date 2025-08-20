# include "ising_public_interface.h"

# include <vector>
# include <stdexcept>

// Function to create a std::vector similar to a range in python (but containing T_end). Due to the included floating point tolerance, this function is not built to construct ranges with infinitesimal steps.

std::vector<double> range(double T_start, double T_end, double T_step) {
    if (T_step < 0 || T_end - T_start <= 0)
        throw std::invalid_argument("Choose a positive T_step and T_end > T_start.");
    std::vector<double> vec;
    double tracker{T_start};
    while (tracker <= T_end + 1e-12) { // 1e-12 = floating point tolerance so that the last value safely gets included. 
        vec.push_back(tracker);
        tracker += T_step;
    }
    return vec;
}