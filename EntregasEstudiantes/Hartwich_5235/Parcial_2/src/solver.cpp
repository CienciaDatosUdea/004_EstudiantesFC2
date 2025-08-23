#include <interface.h>

#include <vector>
#include <iostream>
#include <utility> // para std::swap
#include <cmath>

// constructor de la clase: asigna los parámetros a los miembros y automáticamente evoluciona el sistema, así que el objeto construido está listo de una vez.
Solver::Solver(
    const Fields& f,
    double t_end,
    double dt,
    bool reflective_boundaries,
    bool log_full_evolution,
    int logs
) : t_end_(t_end),
    dt_(dt),
    reflective_boundaries_(reflective_boundaries),
    log_full_evolution_(log_full_evolution),
    logs_(logs)
{
    Run(f);
}

// getter para los campos finales; revisa si existen
const Fields& Solver::get_fields_() const {
    if (final_fields_)
        return *final_fields_;
    else
        throw std::logic_error("trying to return final_fields_ before it exists");
}

// función para evolucionar el sistema según FDTD
// Note que, análogamente al ejemplo en el libro, el primer semi-paso del campo eléctrico se calcula con los valores del campo eléctrico en t=0 (ya que no hay valores para t=-dt/2 .) Otra manera de verlo sería de decir que las condiciones iniciales se refieren a H(t=0) y E(t=-dt/2).
void Solver::Run(const Fields& f) {

    // velocidad de la luz
    constexpr double c{299792458};

    // parámetro Courant
    const double beta{c/(f.g_.dz_/dt_)};

    // condición de Courant
    if (beta > .5) {
        std::cout << "\nWarning: Courant stability condition  c/(dz/dt) < .5  not met. Unstable behavior possible.\n" << std::endl;
    }

    // crear objetas que siempre contienen los campos viejos y actualizados
    Fields f_old{f}; // va a contener E(t-dt/2) y H(t)
    Fields f_new{f}; // va a contener E(t+dt/2) y H(t+dt)
    Fields* ptr_o = &f_old;
    Fields* ptr_n = &f_new;

    // para implementar en el futuro según lo anotado en main():
    // if (log_full_evolution_) {...}

    std::cout << "\nStarting evolution.\n" << std::endl;
    
    // para imprimir progreso
    int current_threshold_percentage{10};

    // iniciar tiempo
    double t{0};

    // evolucionar el sistema hasta t_end_
    while (t < t_end_ - dt_) {

        t += dt_;

        // actualizar campo eléctrico primero (corresponde a t+dt/2). El bucle no contiene las condiciones periódicas.
        for (size_t i{1}; i < f.e_.size()-1; ++i) {
            ptr_n->e_[i] = ptr_o->e_[i] + beta * ( ptr_o->h_[i-1] - ptr_o->h_[i] );
        }

        // aplicar condiciones periódicas o reaplicar condiciones de frontera (campo eléctrico)
        if (reflective_boundaries_)
            ptr_n->ApplyEBoundaryCondition();
        else {
            ptr_n->e_.front() = ptr_o->e_.front() + beta * ( ptr_o->h_.back() - ptr_o->h_.front() );
            ptr_n->e_.back()  = ptr_o->e_.back() + beta * ( ptr_o->h_.back() - ptr_o->h_.front() );
        }

        // actualizar campo magnético segundo (corresponde a t+dt). Ya estamos usando el campo eléctrico actualizado (ptr_n).
        for (size_t i{0}; i < f.h_.size(); ++i) {
            ptr_n->h_[i] = ptr_o->h_[i] + beta * ( ptr_n->e_[i] - ptr_n->e_[i+1] );
        }

        // reaplicar condiciones de frontera (campo magnético)
        if (reflective_boundaries_)
            ptr_n->ApplyHBoundaryCondition();

        // intercambiar (punteros para los) campos viejos y nuevos
        std::swap(ptr_o, ptr_n);

        // imprimir progreso cada 10%
        if ( t / t_end_ >= current_threshold_percentage/100. ) {
            std::cout << "   ..." << current_threshold_percentage << "%" << std::endl;
            current_threshold_percentage += 10;
        }
    }

    // para que final_fields_ contenga los campos finales
    final_fields_.emplace(*ptr_o);

    // para implementar en el futuro según lo anotado en main():
    // if (log_full_evolution_) {...}
}