// #define _USE_MATH_DEFINES
# include <iostream>
# include <cmath>
# include <vector>
# include <stdexcept> // to throw std::out_of_range()
# include <random>
# include <cstdlib>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable" // this flag triggered warnings about code from the Eigen header when run with -march=native
#include <Eigen/Dense>
#pragma GCC diagnostic pop

/*
As we're going to compute "next neighbor sums" inside our 2D system, a one-dimensional vector is a better choice than vector<vector<int>>. Apart from that, this is the form that we're going to train the neural network with anyways, so thats another reason to implement it from the start.
The operator[] implements a way to access the elements of the 1D vector using the 2D indices intuitively associated with our physical system. There's one version that allows writing and a const version only for reading.
Note that both the elements of the vector "data" as well as the return type of operator() are int, as we know that we will only use it for ising spins here.
*/

class Grid {
    public:
        Grid(int n_rows, int n_cols) : n_rows_(n_rows), n_cols_(n_cols), data_(n_rows * n_cols) {};
        const int n_rows_{};
        const int n_cols_{};
        std::vector<int> data_;
        int& operator()(int i, int j, char mode = 'n', char check_bounds = 'n');
        int operator()(int i, int j, char mode = 'n', char check_bounds = 'n') const;
};

/*
The class Ising is the class that actually contains all the information and methods for the 2D Ising magnet. 
*/

class Ising { 
    public:
        Ising(int L, double T, double J, int initial_sweeps = 0);    // Constructor 
        void Sweep(int n_sweeps = 1);
        std::vector<int> get_spins_() const;    // Store the current spin configuration in a vector                 
        double get_energy_() const;          // Calculate the total energy  
        double get_magnetization_() const;         // Calulate the magnetization 
        double get_specific_heat_(int n_samples = 500);         // Calculate the specific heat 
    private:
        Grid spins_;
        const int L_{};
        const double T_{};
        const double J_{};
        void InitializeSpins();     // Assign random spin values to all sites on the grid
        int RandomSpin() const;
        int RandomIndex() const;
        int GetNNSum(int i, int j) const;             // Calculate the sum over the neighbors
        double LocalEnergy(int i, int j) const;            // Calculate the energy of the spin
        double IsingUniform() const;
};

/*
Functions with diverse purposes.
*/

std::mt19937_64& GlobalRng();
std::ostream& time_now(std::ostream& os);
std::vector<double> range(double T_start, double T_end, double T_step);
void write_inputs_with_parameters_to_binary(
    const std::string& filename,
    const std::vector<std::vector<int>>& data,
    double T0,
    double T1,
    int L, // L is the side length of the magnet
    int vectors_per_temperature
);
struct InputData {
    Eigen::MatrixXd inputs;
    Eigen::MatrixXd targets;
};
InputData interpret_inputs_and_targets_from_binary(
    const std::string& filename
);
void write_continuous_with_parameters_to_binary(
    const std::string& filename,
    const std::vector<std::vector<int>>& data,
    double T_start,
    double T_step,
    int T_range_size,
    int L, // L is the side length of the magnet
    int vectors_per_temperature
);
struct ContinuousData {
    Eigen::MatrixXd inputs;
    Eigen::VectorXd temperatures;
    int vectors_per_temperature;
};
ContinuousData interpret_continuous_from_binary(
    const std::string& filename
);