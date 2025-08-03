#include "diffusion_model.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

// The following function was adapted from ChatGPT.

// This whole script is only designed to save one final result for T. A possible future adaption would be to make it save the x_values and then all t-values (after every step). For this, either the class would have to hold all of this information, or it would have to be saved (appended, not truncated) after every iteration step.

void write_to_txt(const Diffusion_1D& obj, std::string filename) {

    const auto& x = obj.get_x_vals();
    const auto& T = obj.get_T_vals();

    if (filename.size() < 4 || filename.substr(filename.size() - 4) != ".txt")
        filename += ".txt";

    if (x.size() != T.size()) {
        std::cerr << "Input vectors have different sizes." << std::endl;
        exit(EXIT_FAILURE);
    }

    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    file << std::fixed << std::setprecision(10);

    file << "x_start " << obj.get_x_start() << "\nx_end " << obj.get_x_end() << "\nN_x " << obj.get_N_x() << "\nD " << obj.get_D() << "\ndt " << obj.get_dt() << "\nt_end " << obj.get_t_end() << "\n\n";
    file << "x T" << "\n";
    for (size_t i{0}; i < x.size(); ++i) {
        file << x[i] << " " << T[i] << "\n";
    }

    file.close();
}