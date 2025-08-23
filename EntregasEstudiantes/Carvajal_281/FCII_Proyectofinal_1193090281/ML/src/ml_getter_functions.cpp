#include "ml_public_interface.h"
#include "ml_error_management.h"

#include <Eigen/Dense>
#include <vector>

// getter functions

const BaseParameters& NeuralNetwork::get_base_() const {
    return base_;
}

ValidationLog NeuralNetwork::get_final_validation_results_() const {
    // validate whether the requested member variable exists
    HANDLE({
        error_manager_.TrainingCompleteValidation();
        error_manager_.FinalValidationCompleteValidation();
    });

    return final_validation_results_;        
}

const std::vector<Eigen::MatrixXd>& NeuralNetwork::get_weights_() const {
    // validate whether the requested member variable exists
    HANDLE({
        error_manager_.WeightsAndBiasesInitializedValidation();
    });
    return weights_;
}

const std::vector<Eigen::VectorXd>& NeuralNetwork::get_biases_() const {
    // validate whether the requested member variable exists
    HANDLE({
        error_manager_.WeightsAndBiasesInitializedValidation();
    });
    return biases_;
}