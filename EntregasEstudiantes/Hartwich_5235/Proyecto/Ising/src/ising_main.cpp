# include "ising_public_interface.h"
# include <iostream>
# include <vector>
# include <array>

// The main() function that organizes the generation of all data and writing it to the output files

int main() {

    std::cout << "\nSTATUS\t\t\t\t\t TIMESTAMP" << "\n__________________________________________________\n" << std::endl;
    std::cout << "  Benchmark: 14k configs @ L=12 -> 28 min (-O3).\n" << std::endl;
    std::cout << "\nStarting compilation of Ising main.\t" << time_now << std::endl;

    // Ising parameters used for everything going forward
    const double L{12}; // square ising paramagnet with sides L, i.e. L^2 individual spins.
    const double J{1}; // coupling constant, determines sign and magnitude of energy per interaction
    const double input_vector_size{L*L}; // amount of spins per square system with sides L
    const int n_sweeps{10000}; // amount of sweeps used to thermalize every single configuration
    
    // The two temperatures for which we consider the configurations to be ordered resp. unordered. (The analytical critical temperature 2.29 would be more or less at the midpoint of 1 and 3.5, but we don't want to bias the system toward simply regognizing the midpoint of the two types of training data we give it; instead we want to see if it recognizes the correct critical temperature even if it's not centered.)
    const double T0{1.8};
    const double T1{3.2};
    const std::vector<double> training_temperatures{T0, T1};

    std::cout << "\nStarting generation of all Ising Data.\t" << time_now << std::endl;
    std::cout << "\n...configs for basic visualization" << "\t" << time_now << std::endl;

    /* BASIC VISUALIZATION DATASET GENERATION PART */

    {
        // data for basic visualization of an ising magnet
        const size_t visualization_configs{18}; // 9 per temperature
        const size_t visualization_configs_per_temperature{visualization_configs/2};

        const std::vector<std::string> visualization_filenames{
            "visualization_magnets_T0.txt",
            "visualization_magnets_T1.txt"
        };

        // the main loop sets the temperature, creates the objects to hold the data and later writes it to files.
        for (size_t i{0}; i < training_temperatures.size(); ++i) {
            double T{training_temperatures[i]};
            const std::string filename{visualization_filenames[i]};
            std::vector<std::vector<int>> visualization_set(visualization_configs_per_temperature);  // will be written to txt
            std::vector<double> visualization_set_energies(visualization_configs_per_temperature);                      // txt
            std::vector<double> visualization_set_magnetizations(visualization_configs_per_temperature);                // txt
            std::vector<double> visualization_set_specific_heats(visualization_configs_per_temperature);                // txt
            std::cout << "   ...T = " << T << "\t\t\t\t" << time_now << std::endl;
            // this loop creates as many Ising objects for every temperature as determined, and saves the relevant data in the corresponding containers 
            for (size_t j{0}; j < visualization_configs_per_temperature; ++j) {
                Ising obj(L, T, J, n_sweeps);
                visualization_set[j]                   = obj.get_spins_();
                visualization_set_energies[j]          = obj.get_energy_();
                visualization_set_magnetizations[j]    = obj.get_magnetization_();
                visualization_set_specific_heats[j]    = obj.get_specific_heat_();
            }
            // write relevant data to file
            write_inputs_with_observables_to_txt(
                filename,
                visualization_set,
                visualization_set_energies,
                visualization_set_magnetizations,
                visualization_set_specific_heats,
                T,
                L,
                visualization_configs_per_temperature
            );
        }
    }

    std::cout << "   ...all written to .txt" << "\t\t" << time_now << std::endl;
    std::cout << "\n...training dataset" << "\t\t\t" << time_now << std::endl;

    // ML training and validation data parameters
    const size_t training_set_size{10000};                                    // final: 10.000
    const size_t training_set_size_per_temperature{training_set_size/2};      // final: 5.000
    const size_t validation_set_size{1000};                                   // final: 1.000
    const size_t validation_set_size_per_temperature{validation_set_size/2};  // final: 500

    /* TRAINING DATASET GENERATION PART */

    {
        // ML training data containers
        std::vector<std::vector<int>> training_inputs(training_set_size, std::vector<int>(input_vector_size));    // binary
        std::vector<double> training_set_energies(training_set_size_per_temperature);           // txt
        std::vector<double> training_set_magnetizations(training_set_size_per_temperature);     // txt
        std::vector<double> training_set_specific_heats(training_set_size_per_temperature);     // txt

        const std::vector<std::string> training_observables_filenames{
            "training_inputs_T0.txt",
            "training_inputs_T1.txt",
        };

        // the main loop sets the temperature later writes the observables to files.
        for (size_t i{0}; i < training_temperatures.size(); ++i) {
            double T{training_temperatures[i]};
            std::cout << "   ...T = " << T << "\t\t\t\t" << time_now << std::endl;
            // this loop creates as many Ising objects for every temperature as determined, and saves the relevant data in the corresponding containers 
            for (size_t j{0}; j < training_set_size_per_temperature; ++j) {
                Ising obj(L, T, J, n_sweeps);
                training_inputs[i*training_set_size_per_temperature + j] = obj.get_spins_();  // will save all configs for all temperatures
                training_set_energies[j]                                 = obj.get_energy_(); // will only save data for the current temperature, which will be written to txt before the same vector gets overwritten with the data for the next temperature.
                training_set_magnetizations[j]                           = obj.get_magnetization_();
                training_set_specific_heats[j]                           = obj.get_specific_heat_();
                if ((j+1) % 1000 == 0)
                    std::cout << "      ...i = " << j+1 << "\t\t\t" << time_now << std::endl;
            }
            // save the observables of all configurations to .txt
            write_just_observables_to_txt(
                training_observables_filenames[i],
                training_set_energies,
                training_set_magnetizations,
                training_set_specific_heats,
                T,
                L,
                training_set_size_per_temperature
            );
            std::cout << "      ...params written to .txt\t\t" << time_now << std::endl;
        }
        // finally save the configurations themselves to binary
        write_inputs_with_parameters_to_binary(
            "training_inputs_bin",
            training_inputs,
            T0,
            T1,
            L,
            training_set_size_per_temperature
        );
    }

    std::cout << "   ...vectors written to binary\t\t" << time_now << std::endl;
    std::cout << "\n...validation dataset" << "\t\t\t" << time_now << std::endl;

    /* VALIDATION DATASET GENERATION PART */

    {
        // ML validation data containers
        std::vector<std::vector<int>> validation_inputs(validation_set_size, std::vector<int>(input_vector_size));    // binary
        std::vector<double> validation_set_energies(validation_set_size_per_temperature);           // txt
        std::vector<double> validation_set_magnetizations(validation_set_size_per_temperature);     // txt
        std::vector<double> validation_set_specific_heats(validation_set_size_per_temperature);     // txt

        const std::vector<std::string> validation_observables_filenames{
            "validation_inputs_T0.txt",
            "validation_inputs_T1.txt",
        };

        // the main loop sets the temperature later writes the observables to files.
        for (size_t i{0}; i < training_temperatures.size(); ++i) {
            double T{training_temperatures[i]};
            std::cout << "   ...T = " << T << "\t\t\t\t" << time_now << std::endl;
            // this loop creates as many Ising objects for every temperature as determined, and saves the relevant data in the corresponding containers 
            for (size_t j{0}; j < validation_set_size_per_temperature; ++j) {
                Ising obj(L, T, J, n_sweeps);
                validation_inputs[i*validation_set_size_per_temperature + j] = obj.get_spins_(); // will save all configs for all temperatures
                validation_set_energies[j]                                   = obj.get_energy_(); // will only save data for the current temperature, which will be written to txt before the same vector gets overwritten with the data for the next temperature.
                validation_set_magnetizations[j]                             = obj.get_magnetization_();
                validation_set_specific_heats[j]                             = obj.get_specific_heat_();
                if ((j+1) % 1000 == 0)
                    std::cout << "      ...i = " << j+1 << "\t\t\t" << time_now << std::endl;
            }
            // save the observables of all configurations to .txt
            write_just_observables_to_txt(
                validation_observables_filenames[i],
                validation_set_energies,
                validation_set_magnetizations,
                validation_set_specific_heats,
                T,
                L,
                validation_set_size_per_temperature
            );
            std::cout << "      ...params written to .txt\t\t" << time_now << std::endl;
        }
        // finally save the configurations themselves to binary
        write_inputs_with_parameters_to_binary(
            "validation_inputs_bin",
            validation_inputs,
            T0,
            T1,
            L,
            validation_set_size_per_temperature
        );
    }
    
    std::cout << "   ...vectors written to binary\t\t" << time_now << std::endl;
    std::cout << "\n...continuous dataset" << "\t\t\t" << time_now << std::endl;

    /* CONTINUOUS DATASET GENERATION PART */

    {    
        // parameters for the continuous-temperature dataset
        const double T_start{1.0};
        const double T_end{3.5};
        const double T_step{0.01};
        const size_t vectors_per_temperature{10}; // when searching for the point of maximum confusion, the predictions of the neural network will be averaged over this amount of inputs per temperature
        const std::vector<double> T_range{range(T_start, T_end, T_step)};

        // data container
        std::vector<std::vector<int>> continuous_inputs(T_range.size() * vectors_per_temperature, std::vector<int>(input_vector_size));

        // this main loop sets the temperature
        for (size_t i{0}; i < T_range.size(); ++i) {
            double T{T_range[i]};
            // this loop creates as many Ising objects for every temperature as determined, and saves the relevant data in the corresponding containers 
            for (size_t j{0}; j < vectors_per_temperature; ++j) {
                Ising obj(L, T, J, n_sweeps);
                continuous_inputs[i*vectors_per_temperature + j] = obj.get_spins_();
                if ((i*vectors_per_temperature + j + 1) % 1000 == 0)
                    std::cout << "   ...i = " << i*vectors_per_temperature+j+1 << "\t\t\t\t" << time_now << std::endl;
            }
        }    

        // save the configurations to binary
        write_continuous_with_parameters_to_binary(
            "continuous_inputs_bin",
            continuous_inputs,
            T_start,
            T_step,
            T_range.size(),
            L,
            vectors_per_temperature
        );
    }

    std::cout << "   ...vectors written to binary\t\t" << time_now << std::endl;
    std::cout << "\nCompilation of main successful.\t\t" << time_now << "\n" << std::endl;

    return 0;

}
