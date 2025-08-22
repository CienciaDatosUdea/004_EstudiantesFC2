# include "ml_public_interface.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <stdexcept>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable" // this flag triggered warnings about code from the Eigen header when run with -march=native
#include <Eigen/Dense>
#pragma GCC diagnostic pop

// function to write the following data to .txt: 2D Ising configurations, their common parameters (side length L and temperature T), and their individual observable quantities (energies, magnetizations and specific heats)
void write_inputs_with_observables_to_txt(
    const std::string& filename,
    const std::vector<std::vector<int>>& configs,
    const std::vector<double>& energies,
    const std::vector<double>& magnetizations,
    const std::vector<double>& specific_heats,
    const double T,
    const int L, // note that L is the length of the magnet, NOT the amount of components per vector, which is L^2.
    const int amount_of_configs
) {
    // modulate filename
    std::string name{filename};
    name = "data/basic_visualization/" + name; // directory. has to exist beforehand.

    if (name.size() < 4 || name.substr(name.size() - 4) != ".txt")
        name += ".txt";

    // write the 2D matrices in one file and close it afterwards
    std::ofstream file_configs(name.substr(0, name.size() - 4) + "_configs.txt");
    if (!file_configs.is_open()) {
        throw std::runtime_error("Failed to open file_configs for writing.");
    }
    file_configs << "# THE FOLLOWING MATRICES CORRESPOND TO  " << amount_of_configs << " configs of  L^2 = " << L*L << " COMPONENTS EACH\n#\n# TEMPERATURE  T = " << T << "\n\n";
    for (const std::vector<int>& vec : configs) {
        if (vec.size() != static_cast<size_t>(L * L)) {
            throw std::runtime_error("Vector size does not match L^2.");
        }
        file_configs << "\n";
        // print one row at a time
        for (int i{0}; i < L; ++i) {
            for (int j{0}; j < L; ++j) {
                file_configs << vec[i*L+j] << " ";
            }
            file_configs << "\n";
        }
    }
    file_configs.close();

    // write the energies in one file and close it afterwards
    std::ofstream file_energies(name.substr(0, name.size() - 4) + "_energies.txt");
    if (!file_energies.is_open()) {
        throw std::runtime_error("Failed to open file_energies for writing.");
    }
    file_energies << "# THE FOLLOWING  NUMBERS CORRESPONDS TO THE ENERGIES OF THE  " << amount_of_configs << " configs of  L^2 = " << L*L << " COMPONENTS EACH\n#\n# TEMPERATURE  T = " << T << "\n#\n# Note that for J=1 and a par L, the theoretical maximum energy is 2*L^2 and the miminum energy is -2*L^2. For low temperatures, E->E_min is expected; for high temperatures, E->0 is expected" << "\n\n";
    for (double E : energies) {
        file_energies << E << "\n";
    }
    file_energies.close();

    // write the magnetizations in one file and close it afterwards
    std::ofstream file_magnetizations(name.substr(0, name.size() - 4) + "_magnetizations.txt");
    if (!file_magnetizations.is_open()) {
        throw std::runtime_error("Failed to open file_magnetizations for writing.");
    }
    file_magnetizations << "# THE FOLLOWING  NUMBERS CORRESPONDS TO THE MAGNETIZATIONS OF THE  " << amount_of_configs << " configs of  L^2 = " << L*L << " COMPONENTS EACH\n#\n# TEMPERATURE  T = " << T << "\n#\n# Note that for J=1, the theoretical maximum magnetization is L^2 and the miminum magnetization is -L^2. For low temperatures, abs(M)->L^2 is expected, while for high temperatures, M->0 is expected."  << "\n\n";
    for (double M : magnetizations) {
        file_magnetizations << M << "\n";
    }
    file_magnetizations.close();
    
    // write the specific heats in one file and close it afterwards
    std::ofstream file_specific_heats(name.substr(0, name.size() - 4) + "_specific_heats.txt");
    if (!file_specific_heats.is_open()) {
        throw std::runtime_error("Failed to open file_specific_heats for writing.");
    }
    file_specific_heats << "# THE FOLLOWING  NUMBERS CORRESPONDS TO THE SPECIFIC HEATS OF THE  " << amount_of_configs << " configs of  L^2 = " << L*L << " COMPONENTS EACH\n#\n# TEMPERATURE  T = " << T << "\n#\n# Note that it is expected that C is largest around the phase transition and lowest for T->0/inf."   << "\n\n";
    for (double C : specific_heats) {
        file_specific_heats << C << "\n";
    }
    file_specific_heats.close();

}

// function to write the following data associated with a set of ising vectors to .txt: their common parameters (side length L and temperature T), their individual observable quantities (energies, magnetizations and specific heats)
void write_just_observables_to_txt(
    const std::string& filename,
    const std::vector<double>& energies,
    const std::vector<double>& magnetizations,
    const std::vector<double>& specific_heats,
    const double T,
    const int L, // note that L is the length of the magnet, NOT the amount of components per vector, which is L^2.
    const int amount_of_configs
) {
    // modulate filename
    std::string name{filename};
    name = "data/ml_datasets/" + name; // directory. has to exist beforehand.

    if (name.size() < 4 || name.substr(name.size() - 4) != ".txt")
        name += ".txt";

    // write the energies in one file and close it afterwards
    std::ofstream file_energies(name.substr(0, name.size() - 4) + "_energies.txt");
    if (!file_energies.is_open()) {
        throw std::runtime_error("Failed to open file_energies for writing.");
    }
    file_energies << "# THE FOLLOWING  NUMBERS CORRESPONDS TO THE ENERGIES OF THE  " << amount_of_configs << " configs of  L^2 = " << L*L << " COMPONENTS EACH\n#\n# TEMPERATURE  T = " << T << "\n#\n# Note that for J=1 and a par L, the theoretical maximum energy is 2*L^2 and the miminum energy is -2*L^2. For low temperatures, E->E_min is expected; for high temperatures, E->0 is expected" << "\n\n";
    for (double E : energies) {
        file_energies << E << "\n";
    }
    file_energies.close();

    // write the magnetizations in one file and close it afterwards
    std::ofstream file_magnetizations(name.substr(0, name.size() - 4) + "_magnetizations.txt");
    if (!file_magnetizations.is_open()) {
        throw std::runtime_error("Failed to open file_magnetizations for writing.");
    }
    file_magnetizations << "# THE FOLLOWING  NUMBERS CORRESPONDS TO THE MAGNETIZATIONS OF THE  " << amount_of_configs << " configs of  L^2 = " << L*L << " COMPONENTS EACH\n#\n# TEMPERATURE  T = " << T << "\n#\n# Note that for J=1, the theoretical maximum magnetization is L^2 and the miminum magnetization is -L^2. For low temperatures, abs(M)->L^2 is expected, while for high temperatures, M->0 is expected."  << "\n\n";
    for (double M : magnetizations) {
        file_magnetizations << M << "\n";
    }
    file_magnetizations.close();
    
    // write the specific heats in one file and close it afterwards
    std::ofstream file_specific_heats(name.substr(0, name.size() - 4) + "_specific_heats.txt");
    if (!file_specific_heats.is_open()) {
        throw std::runtime_error("Failed to open file_specific_heats for writing.");
    }
    file_specific_heats << "# THE FOLLOWING  NUMBERS CORRESPONDS TO THE SPECIFIC HEATS OF THE  " << amount_of_configs << " configs of  L^2 = " << L*L << " COMPONENTS EACH\n#\n# TEMPERATURE  T = " << T << "\n#\n# Note that it is expected that C is largest around the phase transition and lowest for T->0/inf."   << "\n\n";
    for (double C : specific_heats) {
        file_specific_heats << C << "\n";
    }
    file_specific_heats.close();

}


// The two following functions, write_inputs_with_parameters_to_binary() and interpret_inputs_and_targets_from_binary(), are adapted from ChatGPT. This means ChatGPT was used to generate a general structure and we then further adapted it to our specific needs and preferences.

// The following function writes the following information about a set of Ising configurations to a binary file:
// [T0] [T1] [L] [amount of input vectors per temperature] [all T0 vectors one by one] [all T1 vectors one by one]
void write_inputs_with_parameters_to_binary(
    const std::string& filename,
    const std::vector<std::vector<int>>& data,
    const double T0,
    const double T1,
    const int L, // note that L is the length of the magnet, NOT the amount of components per vector, which is L^2. We pass it like this because it's the original ising system parameter. It will be re-interpreted when loading and re-using the data later.
    const int vectors_per_temperature
) {
    // modulate name
    std::string name{filename};
    name = "data/ml_datasets/" + name; // directory. has to exist beforehand.

    std::ofstream out(name, std::ios::binary);

    if (!out) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    // Write header: T0, T1 (doubles), L, vectors_per_temperature (integers)
    out.write(reinterpret_cast<const char*>(&T0), sizeof(T0));
    out.write(reinterpret_cast<const char*>(&T1), sizeof(T1));
    out.write(reinterpret_cast<const char*>(&L), sizeof(L));
    out.write(reinterpret_cast<const char*>(&vectors_per_temperature), sizeof(vectors_per_temperature));

    // Write all vector<int> contents in order
    for (const auto& vec : data) {
        out.write(reinterpret_cast<const char*>(vec.data()), vec.size() * sizeof(int));
    }

    out.close();
}

// The following function interprets the following information about a set of Ising configurations from a binary file:
// [T0] [T1] [L] [amount of input vectors per temperature] [all T0 vectors one by one] [all T1 vectors one by one]
// and then creates the right target vectors by interpreting T0->(0,1) and T1->(1,0).
InputData interpret_inputs_and_targets_from_binary(
    const std::string& filename
) {
    // modulate name
    std::string name{filename};
    name = "ml_input_datasets/" + name;

    std::ifstream in(name, std::ios::binary);

    if (!in) {
        throw std::runtime_error("Failed to open file for reading.");
    }
    double T0;
    double T1;
    int L; // note that L is the length of the magnet, not the amount of components per vector, which is L^2. 
    int vectors_per_temperature;

    // Read header: T0, T1 (doubles), L, vectors_per_temperature (integers)
    in.read(reinterpret_cast<char*>(&T0), sizeof(T0));
    in.read(reinterpret_cast<char*>(&T1), sizeof(T1));
    in.read(reinterpret_cast<char*>(&L), sizeof(L));
    in.read(reinterpret_cast<char*>(&vectors_per_temperature), sizeof(vectors_per_temperature));

    if (!in) {
        throw std::runtime_error("Failed to read header from file.");
    }

    int input_vector_size{L*L};
    int input_set_size{2*vectors_per_temperature};

    // create matrix whose columns will contain the inputs, and buffer that will first hold the read-in data temporarily
    Eigen::MatrixXd inputs(input_vector_size, input_set_size);
    std::vector<int> buffer(input_vector_size);

    // fill every column of inputs with one input vector
    for (int col{0}; col < input_set_size; ++col) {
        in.read(reinterpret_cast<char*>(buffer.data()), input_vector_size * sizeof(int));
        if (!in) {
            throw std::runtime_error("Failed to read input vector number " + std::to_string(col));
        }
        // values from the buffer vector are interpreted as integers, cast to doubles, and then copied into the col-th column of inputs
        Eigen::Map<Eigen::VectorXd>(inputs.col(col).data(), input_vector_size) = Eigen::Map<Eigen::VectorXi>(buffer.data(), input_vector_size).cast<double>();
    }

    in.close();

    // create target matrix
    Eigen::MatrixXd targets(2, input_set_size);

    // interpret target from the fact that we know that the first half of inputs are from T0 and the second half are from T1
    for (int col{0}; col < vectors_per_temperature; ++col) {
        targets.col(col) << 1, 0; // the target for the ordered temperature T0 configurations is [1,0] 
    }
    for (int col{vectors_per_temperature}; col < 2 * vectors_per_temperature; ++col) {
        targets.col(col) << 0, 1; // the target for the unordered temperature T1 configurations is [0,1] 
    }

    // create output struct
    InputData matrices;
    matrices.inputs = std::move(inputs);
    matrices.targets = std::move(targets);

    return matrices;
}

// The two following functions, write_continuous_with_parameters_to_binary() and interpret_continuous_from_binary(), are adapted from the two preceding functions, write_inputs_with_parameters_to_binary() and interpret_inputs_and_targets_from_binary(), which were adapted from ChatGPT.

// The following function writes the following information about a set of Ising configurations for continuous temperatures to a binary file:
// [L][T_tart][T_step][amount of input vectors per temperature] [all vectors one by one]
void write_continuous_with_parameters_to_binary(
    const std::string& filename,
    const std::vector<std::vector<int>>& data,
    const double T_start,
    const double T_step,
    const int T_range_size,
    const int L, // L is the side length of the magnet
    const int vectors_per_temperature
) {
    // modulate name
    std::string name{filename};
    name = "data/ml_datasets/" + name; // directory. has to exist beforehand.

    std::ofstream out(name, std::ios::binary);

    if (!out) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    // Write header: [L][T_tart][T_step][vectors_per_temperature]
    out.write(reinterpret_cast<const char*>(&L), sizeof(L));
    out.write(reinterpret_cast<const char*>(&T_start), sizeof(T_start));
    out.write(reinterpret_cast<const char*>(&T_step), sizeof(T_step));
    out.write(reinterpret_cast<const char*>(&T_range_size), sizeof(T_range_size));
    out.write(reinterpret_cast<const char*>(&vectors_per_temperature), sizeof(vectors_per_temperature));

    // Write all vectors 
    for (const auto& vec : data) {
        out.write(reinterpret_cast<const char*>(vec.data()), vec.size() * sizeof(int));
    }

    out.close();
}

// The following function interprets the following information about a set of Ising configurations for continuous temperatures from a binary file:
// [L][T_tart][T_step][amount of input vectors per temperature] [all vectors one by one]
ContinuousData interpret_continuous_from_binary(
    const std::string& filename
) {
    std::string name{filename};
    name = "ml_input_datasets/" + name;

    std::ifstream in(name, std::ios::binary);

    if (!in) {
        throw std::runtime_error("Failed to open file for reading.");
    }
    
    // variables that will be read read in
    double T_start;
    double T_step;
    int T_range_size;
    int L; // note that L is the length of the magnet, NOT the amount of components per vector, which is L^2. 
    int vectors_per_temperature;

    // Read header: [L][T_tart][T_step][vectors_per_temperature]
    in.read(reinterpret_cast<char*>(&L), sizeof(L));
    in.read(reinterpret_cast<char*>(&T_start), sizeof(T_start));
    in.read(reinterpret_cast<char*>(&T_step), sizeof(T_step));
    in.read(reinterpret_cast<char*>(&T_range_size), sizeof(T_range_size));
    in.read(reinterpret_cast<char*>(&vectors_per_temperature), sizeof(vectors_per_temperature));

    if (!in) {
        throw std::runtime_error("Failed to read header from file.");
    }

    // create matrix whose columns will contain the inputs, and buffer that will first hold the read-in data temporarily
    int input_vector_size{L*L};
    int input_set_size{vectors_per_temperature*T_range_size};
    Eigen::MatrixXd inputs(input_vector_size, input_set_size);
    std::vector<int> buffer(input_vector_size);

    // fill every column of inputs with one input vector
    for (int col{0}; col < input_set_size; ++col) {
        in.read(reinterpret_cast<char*>(buffer.data()), input_vector_size * sizeof(int));
        if (!in) {
            throw std::runtime_error("Failed to read input vector number " + std::to_string(col));
        }
        // values from the buffer vector are interpreted as integers, cast to doubles, and then copied into the col-th column of inputs
        Eigen::Map<Eigen::VectorXd>(inputs.col(col).data(), input_vector_size) = Eigen::Map<Eigen::VectorXi>(buffer.data(), input_vector_size).cast<double>();
    }

    in.close();

    // reconstruct T_range and convert it from std::vector<double> to Eigen::VectorXd
    double T_end = T_start + (T_range_size - 1) * T_step;
    std::vector<double> T_range{range(T_start, T_end, T_step)};
    Eigen::VectorXd T_range_eigen = Eigen::VectorXd::Map(T_range.data(), T_range.size());

    // create output struct
    ContinuousData data;
    data.inputs = std::move(inputs);
    data.temperatures = T_range_eigen;
    data.vectors_per_temperature = vectors_per_temperature;

    return data;
}