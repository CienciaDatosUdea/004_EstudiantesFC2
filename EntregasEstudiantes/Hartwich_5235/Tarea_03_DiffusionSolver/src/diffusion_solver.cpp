#include "diffusion_model.h"
#include <stdexcept>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <utility> // for std::swap

/*
During the construction of a Diffusion_1D object,
    first,
        the parameters are checked for viability,
    second,
        the initial condition is immediately applied to the T_vals object after its initialization.
        Since the function defining the initial condition is usually taylored to the object in some way, I opted for passing it a reference to the Diffusion_1D object in creation. This way, the object cond has access to the x_vals object and can, in this specific case, fix x_0 accordingly. This structure is general and re-useable in many ways. For example, if a new boundary condition was to depend on D, N_x or dt, this could easily be implemented through additional getter functions.
    and finally,
        the system is evolved until t_end,
so that the user can instantly get the solution through object.get_T_vals() (as well as the x grid through object.get_x_vals()).
*/

Diffusion_1D::Diffusion_1D(double D, double x_start, double x_end, size_t N_x, double t_end, double dt) : x_vals(x_start, x_end, N_x), T_vals(N_x), D(D), x_start(x_start), x_end(x_end), N_x(N_x), t_end(t_end), dt(dt) {
    parameter_check();
    apply_initial_condition(*this);
    evolution();
}

const std::vector<double>& Diffusion_1D::get_x_vals() const {
    return x_vals.get_grid();
}

const std::vector<double>& Diffusion_1D::get_T_vals() const {
    return T_vals;
}

const double Diffusion_1D::get_D() const {
    return D;
}

const double Diffusion_1D::get_x_start() const {
    return x_start;
}

const double Diffusion_1D::get_x_end() const {
    return x_end;
}

const size_t Diffusion_1D::get_N_x() const {
    return N_x;
}

const double Diffusion_1D::get_t_end() const {
    return t; // note that this returns t, not t_end, since t is the right evolution time after evolution() (and that only coincides with the theoretical t_end if t_end/dt is an integer). 
}

const double Diffusion_1D::get_dt() const {
    return dt;
}

/* Argument testing. Content of the tests is self-explanatory. try-catch is just for displaying the error messages nicely. */
void Diffusion_1D::parameter_check() const {
    try {
        if (x_start == x_end)
            throw std::invalid_argument("x_start and x_end can not be the same. Aborting.");
        if (x_start > x_end)
            std::cout << "Warning: x_start > x_end. Proceeding with calculations, but this has not been tested and could thus lead to undefined behavior." << std::endl;
        if (N_x < 3)
            throw std::invalid_argument("N_x can not be smaller than 3 (two endpoints to which to apply boundary conditions + 1 middle point).");
        if (t_end <= 0)
            throw std::invalid_argument("t_end can not be negative or zero.");
        if (dt < 0)
            throw std::invalid_argument("dt can not be negative or zero.");
        if (dt > t_end)
            throw std::invalid_argument("dt can not be greater than t_end. (In this case, the solver would evolve the system zero steps in time).");
        if (D * dt / pow(x_vals.get_dx(), 2) > .5) {
            double dt_proposal{0.5 * pow(x_vals.get_dx(), 2) / D};
            double dx_proposal{sqrt(D * dt / .5)};
            std::ostringstream oss;
            oss << "D*dt/dx^2 must be smaller than than 0.5. Adapt parameters. Examples that would work:\n\t1. keep D, x_start, x_end and N_x but choose dt < " << dt_proposal << ". Currently, you've chosen dt = " << dt << ".\n\t2. keep D and dt but choose x_start, x_end and N_x so that dx > " << dx_proposal << ". Currently, dx = " << x_vals.get_dx() << ".";
            throw std::invalid_argument(oss.str());
        }
    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << "\nAborting compilation." << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

void Diffusion_1D::apply_initial_condition(Diffusion_1D& obj) {
    InitialCondition cond(obj);
    for (size_t i{0}; i < N_x; ++i) {
        T_vals[i] = cond(x_vals[i]);
    }
    save_dirichlet_condition();
}

void Diffusion_1D::save_dirichlet_condition() {
    boundaries[0] = T_vals[0];
    boundaries[N_x-1] = T_vals[N_x-1];
}

/* For the iteration, it's always necessary to have one whole array that contains the old values and one that contains the new ones (as its not possible to overwrite the same array without losing information still needed later). To do this efficiently, two vectors the size of T_vals are created (one holding the initial values, the other one initialized to hold zeros). Then, two pointers are assigned the references to the vectors. First, the values for the first step are calculated based on the initial values; then, the pointers are switched (i.e. they exchange the adresses they hold), so that in the next iteration, the older vector is overwritten with the values for the next step based on the newer vector. This is repeated in every iteration step, finally assigning the then newest vector to the class member T_vals that can be returned through a getter function. */

void Diffusion_1D::evolution() {

    std::vector<double> T_old(T_vals); // copy of initial condition
    std::vector<double> T_new(N_x); // only initialized to hold N_x values, no whole copy needed
    std::vector<double>* ptr_o = &T_old;
    std::vector<double>* ptr_n = &T_new;
    double a{D*dt/pow(x_vals.get_dx(),2)};

    // Set Dirichlet boundaries once. This step would be unnecessary if it were Neumann conditions (see below)
    (*ptr_n).front() = (*ptr_o).front();
    (*ptr_n).back() = (*ptr_o).back();

    while (t < t_end - dt) {
        t += dt;
        /*
        For dirichlet conditions, it is not necessary to update the margins in every step (as they simply do not change per definition). Neumann conditions would have to be implemented here (dT/dx = f(t) -> the values of t and T_old[1] resp. T_old[N-2] dictate the value of T_new[0] resp. T_new[N-1].) The function apply_neumann_condition() is not implemented, this is merely a comment for future reference.
        (*ptr_n).front() = apply_neumann_condition("front");
        (*ptr_n).back() = apply_neumann_condition("back");
        */

        // FTCS for the non-border components
        for (size_t i{1}; i < N_x-1; ++i) {
            (*ptr_n)[i] = (*ptr_o)[i] + a * ( (*ptr_o)[i+1] - 2 * (*ptr_o)[i] + (*ptr_o)[i-1] );
        }
        std::swap(ptr_o, ptr_n); // very cheap operations that makes switches the objects ptr_o and ptr_n point to (therefore, ptr_o always points to the object updated in the last iteration, i.e. the newest values for T, and ptr_n always points to the object where the values for T of the next step can be written)
    }
    T_vals = *ptr_o;
}