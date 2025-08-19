#pragma once

#include <array>
#include <vector>
#include <string>

class Geometry {
    public:
        Geometry(double x_start, double x_end, size_t N_x);
        const double& operator[](size_t) const;
        const std::vector<double>& get_grid() const;
        const double get_dx() const;
    private:
        std::vector<double> grid; // This vector should never change after being assigned values, but is not marked const due to being assigned values in the constructor body. Using a wrapper within the initializer list seemed counterproductive for code legibility. In any case, the class does not have any non-const functions that could accidentally change it.
        const double dx;
};

class Diffusion_1D {
    public:
        Diffusion_1D(double D, double x_start, double x_end, size_t N_x, double t_end, double dt);
        const std::vector<double>& get_x_vals() const;
        const std::vector<double>& get_T_vals() const;
        const double get_D() const;
        const double get_x_start() const;
        const double get_x_end() const;
        const size_t get_N_x() const;
        const double get_t_end() const;
        const double get_dt() const;
    private:
        const Geometry x_vals;
        std::vector<double> T_vals;
        const double D{};
        const double x_start{};
        const double x_end{};
        const size_t N_x{};
        const double t_end{};
        const double dt{};
        double t{0};
        std::array<double, 2> boundaries{{}}; // This array can hold either the constant values of T at the boundaries (Dirichlet condition) or the constant derivatives of T at the boundaries (Neumann condition). In either case: This array should never change after being assigned values, but is not marked const due to being assigned values in the constructor body. Using a wrapper within the initializer list seemed counterproductive for code legibility.
        void parameter_check() const;
        void apply_initial_condition(Diffusion_1D& obj);
        void save_dirichlet_condition();
        void evolution();
};

class InitialCondition {
    public:
        InitialCondition(Diffusion_1D& obj);
        double operator()(double x) const;
    private:
        const double a{};
        const double x_0{};
        double a_wrapper(Diffusion_1D& obj) const;
        double x_0_wrapper(Diffusion_1D& obj) const;
        double initial_condition_function(double x) const;
};

void write_to_txt(const Diffusion_1D& obj, std::string filename);