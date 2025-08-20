# pragma once

#include "ml_common_types.h"

#include <iostream>

// preprocessor macro that will always be used to call any validation function
#define HANDLE(code) error_manager_.Handle(__func__, [&](){ code; })

// necessary forward declaration (fully declared in its own headfile)
class NeuralNetwork;

// Full ErrorManagement class declaration. This class contains all functions used to validate any external parameters "entering" the NeuralNEtwork class (through functions of the constructor), as well as internal logic of NeuralNetwork processes (e.g. prevent the user from calling methods that depend on prerequisites that have not yet been fulfilled). This class is a friend class of NeuralNetwork and hence has access to all its internal parameters.
class ErrorManagement {
    private:
        // pointer to the NeuralNetwork object
        const NeuralNetwork* net_{nullptr};
    public:
        // link the NeuralNetwork object to the ErrorManagement object
        void Bind(const NeuralNetwork* net) {net_ = net;};
        // This template was adapted from ChatGPT. It acts as a central hub that all calls will go through, which has the advantage that all higher-level error handling can be tuned just here (e.g. how to deal with output of error messages)
        template <typename Func>
        void Handle(const char* func_name, Func&& f) const {    
            try {
                if (!net_)
                    throw std::logic_error("Trying to access ErrorManagement object without having specified the object it refers to. Use Bind method from ErrorManagement to pass \'this\' inside the NeuralNetwork object it refers to.");
                std::forward<Func>(f)();
            } catch (const std::exception& e) {
                std::cerr << "Error in " << func_name << ": " << e.what() << std::endl;
                std::exit(EXIT_FAILURE);
            } /* catch (...) {
                std::cerr << "Unknown error in " << func_name << '\n';
                std::exit(EXIT_FAILURE);
            } */
        };
        // the actual functions checking for individual errors
        // validation of input parameters
        void ConstructorParameterValidation(
                const std::string& system_name,
                size_t amount_of_layers,
                const std::vector<Index>& neurons_per_layer
        ) const;
        void LoadTrainingDataParameterValidation(
            Index training_set_size,
            const Eigen::MatrixXd& training_inputs,
            const Eigen::MatrixXd& training_targets
        ) const;
        void LoadValidationDataParameterValidation(
            Index validation_set_size,
            const Eigen::MatrixXd& validation_inputs,
            const Eigen::MatrixXd& validation_targets
        ) const;
        // validation of training parameters
        void TrainParameterValidation(
            int epochs,
            Index batch_size,
            float learning_rate,
            bool run_validation_during_training,
            Index batches_per_validation
        ) const;
        // validation of object state
        void TrainingDataLoadedValidation() const;
        void ValidationDataLoadedValidation() const;
        void WeightsAndBiasesInitializedValidation() const;
        void TrainingCompleteValidation() const;
        void FinalValidationCompleteValidation() const;
};