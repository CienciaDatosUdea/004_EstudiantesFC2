#include "ml_public_interface.h"
#include "ml_error_management.h"

#include <string>
#include <vector>
#include <Eigen/Dense>

// constructor of the NeuralNetwork class
NeuralNetwork::NeuralNetwork(
    const std::string& system_name,
    size_t amount_of_layers,
    const std::vector<Index>& neurons_per_layer
) {
    // link error manager
    error_manager_.Bind(this);
    // validate parameters
    HANDLE({
        error_manager_.ConstructorParameterValidation(
            system_name,
            amount_of_layers,
            neurons_per_layer
        );
    });
    // assign parameters
    base_ = {
        system_name,
        amount_of_layers,
        neurons_per_layer
    };
}

// Function to permanently load the training data (inputs, targets) into the network class.
// This function expects that the columns of "training_inputs" correspond to the individual input vectors and the columns of "training_targets" correspond to the individual target vectors. 
void NeuralNetwork::LoadTrainingData(
    Index training_set_size,
    const Eigen::MatrixXd& training_inputs,
    const Eigen::MatrixXd& training_targets
) {
    // validate parameters
    HANDLE({
        error_manager_.LoadTrainingDataParameterValidation(
            training_set_size,
            training_inputs,
            training_targets
        );
    });
    // assign parameters and update state bools
    training_set_size_ = training_set_size;
    training_inputs_ = training_inputs;
    training_targets_ = training_targets;
    state_.training_data_loaded_ = true;
}

// Function to permanently load the validation data (inputs, targets) into the network class.
// This function expects that the columns of "validation_inputs" correspond to the individual input vectors and the columns of "validation_targets" correspond to the individual target vectors. 
void NeuralNetwork::LoadValidationData(
    Index validation_set_size,
    const Eigen::MatrixXd& validation_inputs,
    const Eigen::MatrixXd& validation_targets
) {
    // validate parameters
    HANDLE({
        error_manager_.LoadValidationDataParameterValidation(
            validation_set_size,
            validation_inputs,
            validation_targets
        );
    });
    // assign parameters and update state bools
    validation_set_size_ = validation_set_size;
    validation_inputs_ = validation_inputs;
    validation_targets_ = validation_targets;
    state_.validation_data_loaded_ = true;
}
 