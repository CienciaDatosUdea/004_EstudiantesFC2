#include "ml_public_interface.h"
#include "ml_error_management.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>

// The chosen Structure is to have NeuralNetwork and ErrorManagement be different classes, declare ErrorManagement a friend class inside NeuralNetwork, create an ErrorManagement object inside NeuralNetwork and finally pass the this-pointer of the NeuralNetwork object to the ErrorManagement object.
// In summary, this means that here, all variables already existing inside the NeuralNetwork object are called with net_->, while all variables being passed into any function for the first time are passed on as normal arguments.

// The following functions validate parameters passed to NeuralNetwork's member functions, and whether all prerequisites for calling them are met.

void ErrorManagement::ConstructorParameterValidation(
    const std::string& system_name,
    size_t amount_of_layers,
    const std::vector<Index>& neurons_per_layer
) const {
    if (system_name == "")
        throw std::invalid_argument("system_name can not be an empty string.");
    if (amount_of_layers < 1)
        throw std::invalid_argument("amount_of_layers has to be at least 1 (that corresponds to 0 hidden layers + the output layer).");
    if (neurons_per_layer.size() != amount_of_layers + 1)
        throw std::invalid_argument("neurons_per_layer has to be a vector whose size corresponds to amount_of_layers + 1 (amount_of_layers does not count the input layer).");
    for (auto& n : neurons_per_layer)
        if (n < 1)
            throw std::invalid_argument("Every component of neurons_per_layer must be at least 1.");
}

void ErrorManagement::LoadTrainingDataParameterValidation(
    Index training_set_size,
    const Eigen::MatrixXd& training_inputs,
    const Eigen::MatrixXd& training_targets
) const {
    if (net_->base_.neurons_per_layer_.front() != training_inputs.rows())
        throw std::invalid_argument("The columns of training_inputs must correspond to the input vectors. The amount of rows, i.e. components per input vector, must therefore be equivalent to the amount of neurons in the input layer. Check that neurons_per_layer[0] and training_inputs.rows() match.");
    if (net_->base_.neurons_per_layer_.back() != training_targets.rows())
        throw std::invalid_argument("The columns of training_targets must correspond to the target vectors. The amount of rows is therefore equivalent to the amount of neurons in the output layer. Check that neurons_per_layer.back() and training_targets.rows() match.");
    if (training_inputs.cols() != training_set_size)
        throw std::invalid_argument("The columns of training_inputs must correspond to the input vectors. The amount of columns is therefore equivalent to the training set size. Check that training_set_size and training_inputs_.cols() match.");
    if (training_set_size < 1)
        throw std::invalid_argument("training_set_size must be a positive integer.");
    if (training_set_size < 1000)
        std::cout << "Warning: attempting to train a neural network with only " << training_set_size << " datasets. Proceeding." << std::endl;
}

void ErrorManagement::LoadValidationDataParameterValidation(
    Index validation_set_size,
    const Eigen::MatrixXd& validation_inputs,
    const Eigen::MatrixXd& validation_targets
) const {
    if (net_->base_.neurons_per_layer_.front() != validation_inputs.rows())
        throw std::invalid_argument("The columns of training_inputs must correspond to the input vectors. The amount of rows is therefore equivalent to the amount of neurons in the input layer. Check that neurons_per_layer[0] and training_inputs.rows() match.");
    if (net_->base_.neurons_per_layer_.back() != validation_targets.rows())
        throw std::invalid_argument("The columns of training_targets must correspond to the target vectors. The amount of rows is therefore equivalent to the amount of neurons in the output layer. Check that neurons_per_layer.back() and training_targets.rows() match.");
    if (validation_inputs.cols() != validation_set_size)
        throw std::invalid_argument("The columns of training_inputs must correspond to the input vectors. The amount of columns is therefore equivalent to the training set size. Check that training_set_size and training_inputs_.cols() match.");
    if (validation_set_size < 1)
        throw std::invalid_argument("training_set_size must be a positive integer.");
    if (static_cast<float>(validation_set_size)/static_cast<float>(net_->training_set_size_) < .00999)
        std::cout << "Warning: attempting to validate a neural network with a validation dataset size that's only " << std::fixed << std::setprecision(2) << 100*static_cast<float>(validation_set_size)/static_cast<float>(net_->training_set_size_) << "\% of the training dataset size. Could not be representative. Proceeding." << std::endl;
}

void ErrorManagement::TrainParameterValidation(
    int epochs,
    Index batch_size,
    float learning_rate,
    bool run_validation_during_training,
    Index batches_per_validation
) const {
    if (epochs < 1)
        throw std::invalid_argument("epochs must be a positive integer.");
    if (batch_size < 1)
        throw std::invalid_argument("batch_size must be a positive integer (batch_size = 1 corresponds to online learning)");
    if (batch_size > net_->training_set_size_)
        throw std::invalid_argument("batch_size can not be larger than training_set_size");
    if (net_->training_set_size_ % batch_size != 0)
        throw std::invalid_argument("batch_size is no factor of training_set_size (i.e. modulo != 0). This is necessary to ensure that every epoch contains the whole training set exactly once.");
    if (learning_rate <= 0)
        throw std::invalid_argument("learning_rate must be positive.");
    if (run_validation_during_training)
        ValidationDataLoadedValidation();
    if (run_validation_during_training && batches_per_validation < 1)
        throw std::invalid_argument("If run_validation_during_training = true, the optional batches_per_validation argument has to be a positive integer. (\"Every how-many batches will the systems progress be evaluated?\")");
}

void ErrorManagement::TrainingDataLoadedValidation() const {
    if (!net_->state_.training_data_loaded_)
        throw std::logic_error("Trying to train neural network without having loaded training data. Use LoadTrainingData().");
}

void ErrorManagement::ValidationDataLoadedValidation() const {
    if (!net_->state_.validation_data_loaded_)
        throw std::logic_error("Trying to validate neural network without having loaded validation data. Use LoadValidationData().");
}

void ErrorManagement::WeightsAndBiasesInitializedValidation() const {
    if (!net_->state_.weights_and_biases_initialized_)
        throw std::logic_error("Trying to get weights or biases before they have been initialized");
    if (!net_->state_.training_complete_)
        std::cout << "Warning: returning weights or biases even though training has not been completed." << std::endl;   
}

void ErrorManagement::TrainingCompleteValidation() const {
    if (!net_->state_.training_complete_)
        throw std::logic_error("Requesting final neural network validation parameters before training has been completed."); 
}

void ErrorManagement::FinalValidationCompleteValidation() const {
    if (!net_->state_.final_validation_complete_)
        throw std::logic_error("Requesting final neural network validation parameters before training has been validated."); 
}