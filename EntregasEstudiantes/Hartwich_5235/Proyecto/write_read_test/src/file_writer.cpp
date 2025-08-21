# include "ising_public_interface.h"

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

// The two following functions are adapted from ChatGPT.

// The following function writes the following information to a binary file:
// [T0] [T1] [L] [amount of input vectors per temperature] [all T0 vectors] [all T1 vectors]
void write_inputs_with_parameters_to_binary(
    const std::string& filename,
    const std::vector<std::vector<int>>& data,
    double T0,
    double T1,
    int L, // note that L is the length of the magnet, NOT the amount of components per vector, which is L^2. We pass it like this because it's the original ising system parameter. It will be re-interpreted when loading and re-using the data later.
    int vectors_per_temperature
) {
    std::string name{filename};
    name = "ml_datasets/" + name; // directory. has to exist beforehand.

    std::ofstream out(name, std::ios::binary);

    if (!out) {
        throw std::runtime_error("Failed to open file for writing.");
    }

    // Write header: T0, T1 (doubles), L, n (ints)
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

// The following function interprets the following information from a binary file:
// [T0] [T1] [L] [amount of input vectors per temperature] [all T0 vectors] [all T1 vectors]
// and then creates the right target vectors by interpreting T0->(0,1) and T1->(1,0).

InputData interpret_inputs_and_targets_from_binary(
    const std::string& filename
) {
    
    std::string name{filename};
    name = "ml_datasets/" + name;

    std::ifstream in(name, std::ios::binary);

    if (!in) {
        throw std::runtime_error("Failed to open file for reading.");
    }
    double T0;
    double T1;
    int L; // note that L is the length of the magnet, NOT the amount of components per vector, which is L^2. 
    int vectors_per_temperature;

    in.read(reinterpret_cast<char*>(&T0), sizeof(T0));
    in.read(reinterpret_cast<char*>(&T1), sizeof(T1));
    in.read(reinterpret_cast<char*>(&L), sizeof(L));
    in.read(reinterpret_cast<char*>(&vectors_per_temperature), sizeof(vectors_per_temperature));

    if (!in) {
        throw std::runtime_error("Failed to read header from file.");
    }

    int input_vector_size{L*L};
    int input_set_size{2*vectors_per_temperature};

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

    Eigen::MatrixXd targets(2, input_set_size);

    for (int col{0}; col < vectors_per_temperature; ++col) {
        targets.col(col) << 1, 0; // the target for the ordered temperature T0 configurations is [1,0] 
    }
    for (int col{vectors_per_temperature}; col < 2 * vectors_per_temperature; ++col) {
        targets.col(col) << 0, 1; // the target for the unordered temperature T1 configurations is [0,1] 
    }

    InputData matrices;
    matrices.inputs = std::move(inputs);
    matrices.targets = std::move(targets);

    return matrices;
}

void write_continuous_with_parameters_to_binary(
    const std::string& filename,
    const std::vector<std::vector<int>>& data,
    double T_start,
    double T_step,
    int T_range_size,
    int L, // L is the side length of the magnet
    int vectors_per_temperature
) {
    std::string name{filename};
    name = "ml_datasets/" + name; // directory. has to exist beforehand.

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

ContinuousData interpret_continuous_from_binary(
    const std::string& filename
) {
    std::string name{filename};
    name = "ml_datasets/" + name;

    std::ifstream in(name, std::ios::binary);

    if (!in) {
        throw std::runtime_error("Failed to open file for reading.");
    }
    double T_start;
    double T_step;
    int T_range_size;
    int L; // note that L is the length of the magnet, NOT the amount of components per vector, which is L^2. 
    int vectors_per_temperature;

    in.read(reinterpret_cast<char*>(&L), sizeof(L));
    in.read(reinterpret_cast<char*>(&T_start), sizeof(T_start));
    in.read(reinterpret_cast<char*>(&T_step), sizeof(T_step));
    in.read(reinterpret_cast<char*>(&T_range_size), sizeof(T_range_size));
    in.read(reinterpret_cast<char*>(&vectors_per_temperature), sizeof(vectors_per_temperature));

    if (!in) {
        throw std::runtime_error("Failed to read header from file.");
    }

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

    ContinuousData data;
    data.inputs = std::move(inputs);
    data.temperatures = T_range_eigen;
    data.vectors_per_temperature = vectors_per_temperature;

    return data;
}