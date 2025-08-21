# include "ising_public_interface.h"
# include <iostream>
# include <vector>
# include <array>

/* 
This test makes sure whether the functions writing to and reading from binary files work as intended (i.e. the reloaded data corresponds to the original data as expected). The results of the functions writing to .txt were easily checked visually.
*/

int main() {

    // define general Ising parameters used throughout the script
    const double L{12};
    const double J{1};
    const double input_vector_size{L*L};
    const int n_sweeps{10000};

    // define training temperatures
    const double T0{1.8};
    const double T1{3.2};
    const std::vector<double> training_temperatures{T0, T1};

    /* FIRST WRITE-READ PAIR OF BINARY FUNCTIONS (inputs with known targets) */
    
    // (note that it is not necessary to repeat the same test for validation data as the structure and used functions are exactly the same as for the training data)

    // define training set size
    const size_t training_set_size{4};
    const size_t training_set_size_per_temperature{training_set_size/2};

    // create container for training inputs
    std::vector<std::vector<int>> training_inputs(training_set_size, std::vector<int>(input_vector_size)); 

    // loop over training temperatures
    for (size_t i{0}; i < training_temperatures.size(); ++i) {
        const double T{training_temperatures[i]};
        // create Ising objects and assign them to the container
        for (size_t j{0}; j < training_set_size_per_temperature; ++j) {
            Ising obj(L, T, J, n_sweeps);
            training_inputs[i * training_set_size_per_temperature + j] = obj.get_spins_();
        }
    }

    // write the training inputs and their parameters to a binary file
    write_inputs_with_parameters_to_binary(
        "training_inputs_bin",
        training_inputs,
        T0,
        T1,
        L,
        training_set_size_per_temperature
    );

    // re-load the data from that same file (output is a struct)
    const InputData data_reloaded = interpret_inputs_and_targets_from_binary(
        "training_inputs_bin"
    );

    // assign inputs and targets from the struct
    const Eigen::MatrixXd inputs_reloaded = data_reloaded.inputs;
    const Eigen::MatrixXd targets_reloaded = data_reloaded.targets;

    std::cout << "\nTEST 1/2: here, input and output should coincide exactly, and ordered inputs should have targes (1,0) while unordered inputs should have target (0,1)." << std::endl;

    // NOTE: the first half of all vectors are for the ordered temperature, the second half for the unordered temperature.

    // loop over training temperatures
    for (size_t i{0}; i < training_inputs.size(); i++) {
        std::cout << "\ninput vector " << i << ":\n  before write >> after read\n";
        // assign corresponding input vector (this is the original data)
        const std::vector<int> vec = training_inputs[i];
        // print out comparison of original and re-loaded data to see if they match
        for (size_t j{0}; j < vec.size(); j++) {
            std::cout << "    " << vec[j] << "    " << inputs_reloaded(j, i) << "\n";
        }
        std::cout << " corresponding target after read:\n";
        // print out target to see if its correct
        for (Eigen::Index j{0}; j < targets_reloaded.rows(); j++) {
        std::cout << "    " << targets_reloaded(j,i) << "\n";
        }
    }

    /* SECOND WRITE-READ PAIR OF BINARY FUNCTIONS (inputs without targets) */
    
    // define continuous temperatures, step size and ammount of vectors per temperature
    const double T_start{2.0};
    const double T_end{2.3};
    const double T_step{0.1};
    const size_t vectors_per_temperature{2};

    // create temperature range
    const std::vector<double> T_range{range(T_start, T_end, T_step)};

    // create container for input data
    std::vector<std::vector<int>> continuous_inputs(T_range.size() * vectors_per_temperature, std::vector<int>(input_vector_size));

    // loop over temperatures
    for (size_t i{0}; i < T_range.size(); ++i) {
        const double T{T_range[i]};
        // create Ising objects and assign them to the container
        for (size_t j{0}; j < vectors_per_temperature; ++j) {
            Ising obj(L, T, J, n_sweeps);
            continuous_inputs[i*vectors_per_temperature + j] = obj.get_spins_();
        }
    }    

    // write the continuous inputs and their parameters to a binary file
    write_continuous_with_parameters_to_binary(
        "continuous_inputs_bin",
        continuous_inputs,
        T_start,
        T_step,
        T_range.size(),
        L,
        vectors_per_temperature
    );

    // re-load the data from that same file (output is a struct)
    const ContinuousData continuous_data_reloaded = interpret_continuous_from_binary(
        "continuous_inputs_bin"
    );

    // assign inputs, targets and parameter from the struct
    const Eigen::MatrixXd continuous_inputs_reloaded = continuous_data_reloaded.inputs;
    const Eigen::VectorXd T_range_reloaded = continuous_data_reloaded.temperatures;
    const int vectors_per_temperature_reloaded = continuous_data_reloaded.vectors_per_temperature;

    std::cout << "\nTEST 2/2: here, both the vectors and the temperatures of input and output should coincide exactly." << std::endl;
    std::cout << "\nVectors per temperature before / after: " << vectors_per_temperature << " / " << vectors_per_temperature_reloaded << std::endl;
    std::cout << "\nT range size before / after: " << T_range.size() << " / " << T_range_reloaded.size() << std::endl;

    // loop over temperature range
    for (size_t i{0}; i < T_range.size(); i++) {
        for (size_t j{0}; j < vectors_per_temperature; ++j) {
            // print out comparison of original and re-loaded temperatures to see if they match
            std::cout << "\nTemperature before / after: " << T_range[i] << " / " << T_range_reloaded[i] << std::endl;
            // assign corresponding input vector (this is the original data)
            const std::vector<int> vec = continuous_inputs[i*vectors_per_temperature + j];
            std::cout << "\ninput vector " << i*vectors_per_temperature + j << ":\n  before write >> after read\n";
            // print out comparison of original and re-loaded vector components to see if they match
            for (size_t k{0}; k < vec.size(); k++) {
                std::cout << "    " << vec[k] << "    " << continuous_inputs_reloaded(k, i*vectors_per_temperature + j) << "\n";
            }
        }
    }

    return 0;
}

