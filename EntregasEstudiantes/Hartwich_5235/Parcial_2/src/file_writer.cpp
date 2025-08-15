#include <interface.h>

#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<vector>
#include<stdexcept>

// Función que escribe los pares de valores (z, E_x, H_y) a un archivo .txt
void WriteFieldsToTxt(
    const std::string& filename,
    const Fields& f
) {
    std::string name = filename;
    if (name.size() < 4 || name.substr(name.size() - 4) != ".txt")
        name += ".txt";
    name = "data_and_visualization/" + name;
    std::ofstream file(name);
    if (!file.is_open())
        throw std::runtime_error("Could not open file \"" + name + "\".");
    file << "#" << " " << "REMEMBER THAT  E[i] = E(z[i])  BUT  H[i] = H(z[i] + dz/2)" << "\n";
    file << "#" << " " << "z" << " " << "E" << " " << "H" << "\n";
    file << std::fixed << std::setprecision(5);
    for (size_t i{0}; i < f.g_.z_.size() - 1; ++i) {
        file << f.g_.z_[i] << " " << f.e_[i] << " " << f.h_[i] << "\n";
    }
    file << f.g_.z_.back() << " " << f.e_.back();
    file.close();
}