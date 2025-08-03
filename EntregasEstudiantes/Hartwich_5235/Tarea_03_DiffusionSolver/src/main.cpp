#include "diffusion_model.h"
#include <iostream>
#include <string>

/* I opted for not passing the Geometry object and the Condition object to the constructor of the solver, but implement them within. This is also scalable in the future (e.g. the constructor could be overloaded to also accept y_start and y_end and initialize a different Geometry accordingly). */

int main() {

    double x_start{0};
    double x_end{1};
    size_t N_x{101};
    double D{1};
    double dt{0.00001};
    double t_end{.1};
    std::string filename{"tests/default_output_textfile"};

    Diffusion_1D sol(D, x_start, x_end, N_x, t_end, dt);    
    write_to_txt(sol, filename);
    std::cout << "Compilation successful, result saved to file." << std::endl;

    return 0;

}