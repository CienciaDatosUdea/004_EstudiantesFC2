#include "diffusion_model.h"
#include <cmath>

/* a and x_0 have to be initialized through initializer list in order to be const. a = 1 is hard coded, x_0 is always centered in the chosen x range. */

InitialCondition::InitialCondition(Diffusion_1D& obj) : a(a_wrapper(obj)), x_0(x_0_wrapper(obj)) {}

double InitialCondition::a_wrapper(Diffusion_1D& obj) const { // passing a ref to obj here is unnecessary, but it's cheap and expresses the possibility to arbitrarily taylor this variable to the object in the future
    return 5;
}

double InitialCondition::x_0_wrapper(Diffusion_1D& obj) const {
    return (obj.get_x_vals().back() - obj.get_x_vals().front()) / 2;
}

double InitialCondition::initial_condition_function(double x) const {
    return exp(- a * pow(x - x_0, 2));
}

double InitialCondition::operator()(double x) const { // calling the object as a shorthand for calling the function
    return initial_condition_function(x);
}