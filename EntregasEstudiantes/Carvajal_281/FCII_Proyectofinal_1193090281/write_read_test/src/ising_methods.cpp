# include "ising_public_interface.h"

// constructor: initializes the vector spins with L_^2 components (all the spins of the 2D grid) and assigns L_, T_, J_ and n_sweeps.
// Immediately initializes spins and sweeps the system in the constructor body.
Ising::Ising(int L, double T, double J, int initial_sweeps) : spins_(L, L), L_(L), T_(T), J_(J) {
    InitializeSpins();
    Sweep(initial_sweeps);
}

// outputs -1 or 1 randomly
int Ising::RandomSpin() const {
    static std::uniform_int_distribution<int> dist(0, 1);
    return dist(GlobalRng()) ? 1 : -1; // dist(global_rng()) outputs 0 or 1. The ternary operator maps 1 -> 1, 0 -> -1.
}

// returns a random real number from [0,1)
double Ising::IsingUniform() const {
    static std::uniform_real_distribution<double> dist(0.0, 1.0);
    return dist(GlobalRng());
}

// outputs an int from [0, L_-1] randomly
int Ising::RandomIndex() const {
    static std::uniform_int_distribution<int> dist(0, L_-1);
    return dist(GlobalRng());
}

// assigns -1 or 1 randomly to every spin
void Ising::InitializeSpins() {
    for (int i{0}; i < L_; ++i) {
        for (int j{0}; j < L_; ++j) {
            spins_(i,j) = RandomSpin();
        }
    }
}

int Ising::GetNNSum(int i, int j) const {   
    // Periodic boundary conditions are implemented by Grid class (when calling with 'p')
    int up    = spins_(i+1, j, 'p');  
    int down  = spins_(i-1, j, 'p');
    int left  = spins_(i, j-1, 'p');
    int right = spins_(i, j+1, 'p');
    return up + down + left + right;
}

double Ising::LocalEnergy(int i, int j) const {
    return -J_ * spins_(i,j) * GetNNSum(i,j);
}

/* 
- Executes the Metropolis algorithm:
- Iterates over all spins in the lattice, proposes a spin flip at each site,
- calculates the energy difference, and accepts or rejects the flip based on the Metropolis probability rule using temperature T_.
- in every step: if the local energy is currently positive, then flipping the spin makes it negative and therefore reduces the total energy of the system -> instantly accept. If the local energy is currently negative, then flipping the spin makes it positive and therefore augments the total energy of the system -> only accept with probability exp(-dE/T_). Note that dE = -2E_before (dE = E_flip - E_before = -J/2 (-1)*spin_before * NN_sum - (-J/2)* spin_before * NN_sum = 2 * current_spin * NN_sum = -2 * E_before).
*/
void Ising::Sweep(int n_sweeps) {      
    for (int step{0}; step < n_sweeps; ++step) {
        for (int count{0}; count < L_ * L_; ++count) {
            int i{RandomIndex()};
            int j{RandomIndex()};
            double dE{-2*LocalEnergy(i,j)};
            if (dE <= 0 || IsingUniform() < std::exp(-dE/T_)) {
                spins_(i,j) *= -1;
            }
        }
    }
}

std::vector<int> Ising::get_spins_() const {
    return spins_.data_;
}

double Ising::get_energy_() const {
    double total_energy{0};
    for (int i{0}; i < L_; ++i) {
        for (int j{0}; j < L_; ++j) {
            total_energy += LocalEnergy(i, j);
        }
    }
    return total_energy/2;
}

double Ising::get_magnetization_() const {
    int total_spin{0};
    for (int i{0}; i < L_; ++i) {
        for (int j{0}; j < L_; ++j) {
            total_spin += spins_(i, j);
        }
    }
    return total_spin; 
}

/*
The following function calculates the specific heat C_v = (<E>^2 - <E^2>)/(T^2*N) and therefore needs to average the Energy of the System over different states. For this, the array has to be evolved using Sweep(), saving the total (square) energy from every step.
This would, in principle, change the array permanently. However, although the function is not marked as const, it does not change the state of the object permanently: it first copies the current state of the system, then evolves it to measure its fluctuations, and then assigns the copy back, leaving the original unchanged. This is to avoid users accidentally changing the object (for example, if one would first call get_energy_(), then get_specific_heat_() and finally get_magnetization_(), then the magnetization and the total energy would not relate to the same configuration since getting the specific heat would have changed it in the meantime).
*/
double Ising::get_specific_heat_(int n_samples) {
    // creating copy
    Grid spins_copy(L_, L_);
    spins_copy.data_ = spins_.data_;
    // initializing parameters
    double E_sum{0};
    double E2_sum{0};
    int N{L_*L_};
    // taking samples
    for (int i{0}; i < n_samples; ++i) {
        Sweep(); // one sweep (default argument)
        double E{get_energy_()};  // calculate current total energy 
        E_sum += E;
        E2_sum += E * E;
    }
    // re-assign old values to spins_ in order to leave it unchanged
    spins_.data_ = spins_copy.data_;
    // average over sample size
    double E_avg = E_sum / n_samples;
    double E2_avg = E2_sum / n_samples;
    // Calculate the specific heat (per spin)
    double C{(E2_avg - E_avg * E_avg) / (T_ * T_ * N)};
    return C;
}








