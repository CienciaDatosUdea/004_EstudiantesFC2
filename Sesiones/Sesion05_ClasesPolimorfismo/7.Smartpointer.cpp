#include <iostream>
#include <cmath>  // Para sin()

class FuncionMatematica {
public:
    // Método virtual para evaluar la función en un punto x
    virtual double evaluar(double x) const {
        return 0.0; // por defecto devuelve 0
    }

    // Destructor virtual para limpieza segura
    virtual ~FuncionMatematica() = default;
};

class Seno : public FuncionMatematica {
public:
    double evaluar(double x) const override {
        return std::sin(x);
    }
};

class Cuadrado : public FuncionMatematica {
public:
    double evaluar(double x) const override {
        return x * x;
    }
};

class Constante : public FuncionMatematica {
    double valor;
public:
    Constante(double v) : valor(v) {}

    double evaluar(double x) const override {
        return valor;
    }
};

int main() {
    FuncionMatematica* f1 = new Seno(); //Esta en la pila, es dinamico
    Seno a;                              //Esta en el stack
    FuncionMatematica *f1=&a;

    FuncionMatematica* f2 = new Cuadrado();
    FuncionMatematica* f3 = new Constante(5.0);

    double x = 2.0;

    std::cout << "Seno(" << x << ") = " << f1->evaluar(x) << "\n";
    std::cout << "Cuadrado(" << x << ") = " << f2->evaluar(x) << "\n";
    std::cout << "Constante(" << x << ") = " << f3->evaluar(x) << "\n";

    
    delete f1;
    delete f2;
    delete f3;


 // heap con punteros inteligentes (equivalente a new/delete)
    std::unique_ptr<FuncionMatematica> f2 = std::make_unique<Cuadrado>();
    std::unique_ptr<FuncionMatematica> f3 = std::make_unique<Constante>(5.0);

    double x = 2.0;

    std::cout << "Seno(" << x << ") = " << f1->evaluar(x) << "\n";
    std::cout << "Cuadrado(" << x << ") = " << f2->evaluar(x) << "\n";
    std::cout << "Constante(" << x << ") = " << f3->evaluar(x) << "\n";


    return 0;
}



