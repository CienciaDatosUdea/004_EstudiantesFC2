#include <iostream>
#include <cmath>

using namespace std;


// Funcion para calcular pi con la formula de Leibniz completa
double calcularPiLeibniz(int n){
    double pi = 0;
    int i;
        for (i = 0; i <= n; i++){
            pi += 4*pow(-1,i)/(2*i+1);  // termino general: (-1)^i/(2*i+1)
        }
    return pi;
}

// Funcion para calcular pi separando terminos positivos y negativos de la formula de Leibniz
double calcularPiSeparado(int n){
    int i;
    double T1 = 0;  // Terminos pares (positivos)
    double T2 = 0;  // Terminos impares (negativos)

        // Calculo de terminos pares
        for (i = 0; i <= n; i+=2){
            T1 += 4./(2*i+1);
        }
        // Calculo de terminos impares
        for (i = 1; i <= n; i+=2){
            T2 += 4./(2*i+1);
        }
        return T1 - T2;
}

int main(){
    int n;
    cout << "Ingrese un valor entero positivo para n" << endl;
    cin >> n;

    // Validacion
    
    while (n < 0){
    cout << "El valor de n debe ser positivo, intentelo de nuevo" << endl;
    cin >> n;
    }
    
    // Valores calculados de pi
    double piL = calcularPiLeibniz(n);
    double piS = calcularPiSeparado(n);

    // Errores absolutos
    double epsL = abs(piL - M_PI);
    double epsS = abs(piS - M_PI);

    // Impresion de resultados
    cout << "El valor de pi calculado con la serie de Leibniz es " << piL << endl;
    cout << "Su error absoluto es " << epsL << endl;
    cout << "----------------------------------------------------------------------------" << endl;
    cout << "El valor de pi calculado separando los terminos positivos y negativos es " << piS << endl;
    cout << "Su error absoluto es " << epsS << endl;

    return 0;
}