#include "ml_public_interface.h"
#include "ml_error_management.h"

#include <Eigen/Dense>
#include <vector>
#include <array>
#include <numeric> // for std::iota()
#include <random> // for std::shuffle()
#include <optional>

// Initializes the weight matrices of all layers using random number from the standard gaussian distribution, and the bias vectors of all layers in 0
void NeuralNetwork::InitializeWeightsBiases() {
    weights_.reserve(base_.amount_of_layers_);
    biases_.reserve(base_.amount_of_layers_);
    // remember that neurons_per_layer_[0] is the amount of input neurons and amount_of_layers_ does NOT count the input layer
    for (size_t layer{1}; layer <= base_.amount_of_layers_; ++layer) {
        Index m = base_.neurons_per_layer_[layer-1];
        Index n = base_.neurons_per_layer_[layer];
        weights_.emplace_back(Eigen::MatrixXd::NullaryExpr(n, m, []() { return UniformNormalNumber(); } )); // NullaryExpr fills the matrix with numbers distributed normally around 0 (standard gaussian). []() is a lambda that takes no argument.
        biases_.emplace_back(Eigen::VectorXd::Zero(n));
    }
    // update network state bools
    state_.weights_and_biases_initialized_ = true;
}


/* 
Function that does training for one batch with batchnumber >=1 (1 = online learning). Computes the outputs for all input vectors, averages over the cost and back-propagates the error (once, for the averaged cost).

This function is incomplete. In its final state, it would implement the linear algebra of a (batch-wise) forward pass and the resulting backpropagation. This also requires defining a sigmoid function (applied element-wise to matrices) and its derivative. It would also include softmax activation at the last layer.
*/
void NeuralNetwork::TrainBatch(
    const Eigen::MatrixXd& batch_inputs,
    const Eigen::MatrixXd& batch_targets,
    float learning_rate
) {
    Index batch_size = batch_inputs.cols();
    // Initialize output matrices of all layers needed for back propagation.
    std::vector<Eigen::MatrixXd> outputs;
    outputs.reserve(base_.amount_of_layers_);
    // remember that neurons_per_layer_[0] is the amount of input neurons and amount_of_layers_ does NOT count the input layer
    for (size_t layer{1}; layer <= base_.amount_of_layers_; ++layer) {
        Index n = base_.neurons_per_layer_[layer];
        outputs.emplace_back(Eigen::MatrixXd::Zero(n, batch_size));
    }
    /* INCOMPLETE */
}

/*
This function is incomplete. Currently, it returns a hard-coded validation log (to allow the code to run without throwing). In its final state, it would calculate the validation log by doing one forward pass of the whole validation dataset, comparing it to its targets and calculating the cost and the probabilities of asserting the right results.
*/
ValidationLog NeuralNetwork::ValidateAccuracy() const {
    // validate whether prerequisites for calling this function are met
    HANDLE({
        error_manager_.ValidationDataLoadedValidation();
    });
    /* INCOMPLETE */
    ValidationLog log{0,0,0,0};
    return log;
}

// validate the final accuracy after training has been completed
void NeuralNetwork::ValidateFinalAccuracy() {
    final_validation_results_ = ValidateAccuracy();
    state_.final_validation_complete_ = true;
}

/*
This function is incomplete. In its final state, it would write the validationlogs to a .txt file (if run_validation_during_training=true).
*/
void NeuralNetwork::Train(
    int epochs,
    Index batch_size,
    float learning_rate,
    bool run_validation_during_training,
    Index batches_per_validation
) {
    // validate whether prerequisites for calling this function are met and validate the parameters passed to the function
    HANDLE({
        error_manager_.TrainingDataLoadedValidation();
        error_manager_.TrainParameterValidation(
            epochs,
            batch_size,
            learning_rate,
            run_validation_during_training,
            batches_per_validation
        );
    });
    InitializeWeightsBiases();
    // optional vector for validation results (will be filled if run_validation_during_training=true)
    std::optional<std::vector<BatchValidationLog>> validation_results;
    if (run_validation_during_training) {
        Index training_sets_per_validation = training_set_size_ / (batch_size*batches_per_validation); // all three parameters are of type Index and enforced to be positive by now, so division is equivalent to rounding down if necessary.  
        validation_results.emplace(); // creates the object
        validation_results->reserve(training_sets_per_validation); // allocates memory for the validation data generated during training
    }
    // train the network one epoch at a time
    for (int i{0}; i < epochs; ++i) {
        // Randomize whole dataset newly every epoch. iota() fills the vector with indices 0, 1, 2, ... and shuffle() shuffles them. Then the randomized indices are used to fill the columns of batch_inputs matrix with (random) columns aka. input vectors from the training_inputs_ matrix. Same for the corresponding target vectors.
        std::vector<Index> indices(training_set_size_);
        std::iota(indices.begin(), indices.end(), 0);
        std::shuffle(indices.begin(), indices.end(), GlobalRng());
        Index batch_number = training_set_size_ / batch_size;
        Eigen::MatrixXd batch_inputs(training_inputs_.rows(), batch_size);
        Eigen::MatrixXd batch_targets(training_targets_.rows(), batch_size);
        // iterate over all the batches of this epoch
        for (Index j{0}; j < batch_number; ++j) {
            // assign input vectors for this batch by taking them from the complete dataset as determined by the randomized indices
            for (Index k{0}; k < batch_size; ++k) {
                batch_inputs.col(k) = training_inputs_.col(indices[j*batch_size + k]);
                batch_targets.col(k) = training_targets_.col(indices[j*batch_size + k]);
            }
            // train the network one batch
            TrainBatch(
                batch_inputs,
                batch_targets,
                learning_rate
            );
            // if run_validation_during_training=true, validate and save current accuracy every batches_per_validation batches
            if (run_validation_during_training && (j % batches_per_validation == 0)) {
                BatchValidationLog batch_log{ValidateAccuracy(), i*batch_number + j};
                validation_results->push_back(batch_log);
            }
        }
    }
    if (run_validation_during_training) {
        /* INCOMPLETE */
        // WRITE VALIDATION RESULTS TO .TXT
        // in first row: save all (ALL) relevant variables (including batch_size, batches_per_validation etc so that while visualizing, everything can be shown as wished and differences between epochs can be visualized (if there are any))
    }
    if (run_validation_during_training) {
        ValidateFinalAccuracy();
    }
    // update internal state bools
    state_.training_complete_ = true;
}






























