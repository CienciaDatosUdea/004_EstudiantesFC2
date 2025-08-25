#include "functions.h"

void save_to_csv_1d(const std::string& filename,
                    const VectorXd& x_values,
                    const VectorXd& T_values,
                    const std::vector<VectorXd>& wavefunctions) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    file << "x";
    for (int i = 0; i < T_values.size(); ++i) {
        file << ",T=" << T_values[i];
    }
    file << "\n";

    for (int j = 0; j < x_values.size(); ++j) {
        file << x_values[j];
        for (int k = 0; k < T_values.size(); ++k) {
            file << "," << wavefunctions[k][j];
        }
        file << "\n";
    }
}

void save_to_csv(const VectorXd& x1_values,
                 const VectorXd& x2_values,
                 const std::vector<std::tuple<double, double, double, double>>& energies,
                 bool spin,
                 const std::vector<MatrixXd>& wavefunctions,
                 const std::string& filename) {
    std::ofstream file(filename);

    file << "x1,x2";
    for (const auto& energy_tuple : energies) {
        double E1 = std::get<0>(energy_tuple);
        double E2 = std::get<1>(energy_tuple);
        file << ",(E1=" << E1 << " E2=" << E2 << ")";
    }
    file << "\n";

    for(int i = 0; i < x1_values.size(); ++i) {
        for(int j = 0; j < x2_values.size(); ++j) {
            file << x1_values[i] << "," << x2_values[j];
            for(size_t k = 0; k < wavefunctions.size(); ++k) {
                file << "," << wavefunctions[k](i,j);
            }
            file << "\n";
        }
    }
}
