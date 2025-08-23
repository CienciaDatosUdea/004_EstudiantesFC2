#include <iostream>

class Complejos{
private:
    double real; //parte real
    double imag; //parte imaginaria
public:
    Complejos(double r, double i);
    //Métodos que definen las operaciones
    Complejos suma(const Complejos &c) const;
    Complejos resta(const Complejos &c) const;
    Complejos multiplicar(const Complejos &c) const;
    Complejos dividir(const Complejos &c) const;
    
    //Método para imprimir resultados
    static void imprimirResultados(const Complejos &suma,const Complejos &resta,
                                   const Complejos &multiplicacion,const Complejos &division);
};
