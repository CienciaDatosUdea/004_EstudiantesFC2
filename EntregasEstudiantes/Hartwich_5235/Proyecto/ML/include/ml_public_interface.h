# pragma once

#include "ml_common_types.h"
#include "ml_error_management.h"

#include <Eigen/Dense>
#include <string>
#include <vector>
#include <array>
#include <random>
#include <iostream>
#include <exception>

// Struct for variables used to determine the neural network's accuracy. All of the following values will be averaged over a validation dataset.
struct ValidationLog {
    double p_0_0; // probability that "ordered" is recognized as "ordered"
    double p_1_1; // probability that "unordered" is recognized as "unordered"
    double p_total; // total probability that any phase is recognized correctly
    double avg_cost; // average cost;
};

// validationlog coupled to a certain batch number
struct BatchValidationLog {
    ValidationLog log;
    Index batch;
};

// base parameters that define the structure of the neural network
struct BaseParameters { 
    std::string system_name_{};
    size_t amount_of_layers_{};
    std::vector<Index> neurons_per_layer_{};
};

// state parameters that define the current state of the neural network
struct StateParameters {
    bool training_data_loaded_{false};
    bool validation_data_loaded_{false};
    bool weights_and_biases_initialized_{false};
    bool training_complete_{false};
    bool final_validation_complete_{false};
};

// the class defining the neural network
class NeuralNetwork {
    // giving ErrorManagement access to all internal variables. This makes sense because the validation functions need access to the whole internal logic.
    friend class ErrorManagement;
    public:
        // constructor
        NeuralNetwork(
            const std::string& system_name,
            size_t amount_of_layers,
            const std::vector<Index>& neurons_per_layer
        );
        // functions for loading datasets
        void LoadTrainingData(
            Index training_set_size,
            const Eigen::MatrixXd& training_inputs,
            const Eigen::MatrixXd& training_targets
        );
        void LoadValidationData(
            Index validation_set_size,
            const Eigen::MatrixXd& validation_inputs,
            const Eigen::MatrixXd& validation_targets
        );
        // function to execute training process
        void Train(
            int epochs,
            Index batch_size,
            float learning_rate,
            bool run_validation_during_training = false,
            Index batches_per_validation = 0
        );
        // Function to validate final result after training. It's only necessary to call it from outside if Train() parameter run_validation_during_training = false.
        void ValidateFinalAccuracy();
        // getter functions
        const BaseParameters& get_base_() const;
        const std::vector<Eigen::MatrixXd>& get_weights_() const;
        const std::vector<Eigen::VectorXd>& get_biases_() const;
        ValidationLog get_final_validation_results_() const;

    private:
        // overall system parameters
        BaseParameters base_;
        // overall state bools
        StateParameters state_;
        // error management
        ErrorManagement error_manager_;
        // weights and biases
        std::vector<Eigen::MatrixXd> weights_; // will hold the weight matrices of the different layers
        std::vector<Eigen::VectorXd> biases_; // will hold the bias vectors of the different layers
        // non-public functions included in Train()
        void InitializeWeightsBiases();
        void TrainBatch(
            const Eigen::MatrixXd& batch_inputs,
            const Eigen::MatrixXd& batch_targets,
            float learning_rate
        );
        ValidationLog ValidateAccuracy() const;
        // training dataset variables
        Index training_set_size_{0};
        Eigen::MatrixXd training_inputs_;
        Eigen::MatrixXd training_targets_;
        // validation dataset variables
        Index validation_set_size_{0};
        Eigen::MatrixXd validation_inputs_;
        Eigen::MatrixXd validation_targets_;
        // variables for results after training
        ValidationLog final_validation_results_;
};

/*
Functions with diverse purposes
*/

std::mt19937_64& GlobalRng();
double UniformNormalNumber();
std::ostream& time_now(std::ostream& os);
std::vector<double> range(double T_start, double T_end, double T_step);
void write_inputs_with_observables_to_txt(
    const std::string& filename,
    const std::vector<std::vector<int>>& configs,
    const std::vector<double>& energies,
    const std::vector<double>& magnetizations,
    const std::vector<double>& specific_heats,
    double T,
    int L, // L is the side length of the magnet
    int amount_of_vectors
);
void write_just_observables_to_txt(
    const std::string& filename,
    const std::vector<double>& energies,
    const std::vector<double>& magnetizations,
    const std::vector<double>& specific_heats,
    double T,
    int L, // L is the side length of the magnet
    int amount_of_configs
);
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
