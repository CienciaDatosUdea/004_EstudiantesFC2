#ifndef FDTD_HPP
#define FDTD_HPP

#include <vector>
#include <string>
#include <fstream>

class FDTDSimulator {
public:
    FDTDSimulator(int n_nodes, double beta);
    void set_boundary_conditions(const std::string& type);
    void run(int num_steps, int plot_every, const std::string& output_filename);

private:
    void initialize_fields();
    void update_step();
    void apply_boundaries();
    void save_data(std::ofstream& file);

    int N;
    double BETA;
    std::vector<std::vector<double>> Ex;
    std::vector<std::vector<double>> Hy;
    std::string boundary_type;
};

#endif // FDTD_HPP