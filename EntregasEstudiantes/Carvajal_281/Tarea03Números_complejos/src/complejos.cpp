//Cómo estamos aplicando estructura modular, en este documento .cpp se incluye la construcción de la clase complejos definida en el .h 

#include "complejos.h"
#include <iostream>
using namespace std;

//Inicializamos el constructor de la clase
Complejos::Complejos(double x, double y) {
    //solo se requiere conocer el valor del número
    real=x;     
    imag=y; }

//SUMA: Toma como parámetro de entrada los datos ingresados en Complejos (Constantes ya que este número no se modifica)
Complejos Complejos::suma(const Complejos &c) const //Const al final indica que no se modifica el objeto en esta clase
{ 
    double suma_real=real + c.real;
    double suma_imag=imag + c.imag;
    return Complejos(suma_real, suma_imag); }

//Resta
Complejos Complejos::resta(const Complejos &c) const {
    double resta_real =real-c.real;
    double resta_imag= imag-c.imag;
    return Complejos(resta_real,resta_imag);
}

//Multiplicación
Complejos Complejos::multiplicar(const Complejos &c) const {
    double multiplicacion_real = real*c.real-imag*c.imag;
    double multiplicacion_imag = real*c.imag+imag*c.real;
    return Complejos(multiplicacion_real, multiplicacion_imag);
}

//División: definicion z1/z2 = (a+ bi)(c-di) / c² + d²
Complejos Complejos::dividir(const Complejos &c) const {
    double denominador = c.real*c.real+c.imag *c.imag;
    if (denominador == 0) {
        std::cout << "Error: No es posible la división por cero" << std::endl;
        return Complejos(0,0);
    }
    double div_real=(real*c.real+imag*c.imag) / denominador;
    double div_imag=(imag*c.real-real* c.imag) / denominador;
    return Complejos(div_real, div_imag);
}


//Imprimir los resultados de las operaciones
void Complejos::imprimirResultados(const Complejos &suma, const Complejos &resta,
const Complejos &multiplicacion, const Complejos &division)

{
    cout << "\nResultados de las operaciones para C1 y C2 \n" << endl;

    cout << "El resultado de la suma C1+C2 es: ";
    if (suma.imag >= 0)
        cout<<suma.real << " +" <<suma.imag << "i" <<endl;
    else
        cout<<suma.real << " - " <<-suma.imag << "i" <<endl;

    cout << "El resultado de la resta C1-C2 es: ";
    if (resta.imag >= 0)
        cout<< resta.real<< " + " <<resta.imag<< "i"<<endl;
    else
        cout<< resta.real << " - " <<-resta.imag << "i"<<endl;

    cout << "El resultado de la multiplicación C1*C2 es: ";
    if (multiplicacion.imag >= 0)
        cout<< multiplicacion.real << " + " <<multiplicacion.imag << "i" << endl;
    else
        cout<< multiplicacion.real << " - " <<-multiplicacion.imag << "i" << endl;

    cout << "El resultado de la división C1/C2 es: ";
    if (division.imag >= 0)
        cout << division.real << " + " <<division.imag<< "i" <<endl;
    else
        cout << division.real << " - " <<-division.imag<< "i" <<endl;
}

