#include<iostream>
#include<cmath>

using namespace std;

// Este programa realiza el calculo de $\pi$ mediante la fórmula de Leibnitz:
// $\sum_{k=0}^{k=n} \dfrac{ (-1)^k }{ 2k + 1 }
// y lo compara con el valor teórico.

// Cuenta con dos funciones, la primera \verbatim{calcularPiLeibniz} calcula sumatoria término por término
// la segunda \verbatim{calcularPiSeparado} calcula los términos con denominador 4k + 1 y 4k + 3 por aparte y luego los resta.

// Funciona: Para ejecutar el codigo emplea: 
//      verbatim{./Tarea_00_pi.out}
// Parametros entrada: 
//      n: cantidad de términos a calcular
// Parametros de salida: 
//      pi_leibnitz, pi_separado, error_absoluto_leibnitz, error_absoluto_separado


double calcularPiLeibniz(int);
double calcularPiSeparado(int);

int main(){
    int n;
    double pi;
    cout<<"Ingrese la cantidad de términos para sumar: ";
    cin>>n;
    cout.precision(15); // Para mostrar más decimales
    if(n>0){ // Verifica que n sea mayor que 0 
        pi = calcularPiLeibniz(n); // calcula pi usando la serie de Leibniz
        cout<<"Primer método: "<<pi<<endl;
        cout<<"Error absoluto: "<<abs(pi-M_PI)<<endl<<endl;

        pi = calcularPiSeparado(n); // calcula pi usando la serie separada
        cout<<"Segundo método: "<<pi<<endl;
        cout<<"Error absoluto: "<<abs(pi-M_PI)<<endl;
    }
    else{
        cout<<"Ingrese n mayor que 0";
    }

    return 0;
};

double calcularPiLeibniz(int n){
    double pi = 0;
    for(double k=0; k<=n; k++){ 
        pi += pow(-1, k)/(2*k+1); // Suma los términos de la serie de Leibniz
    }
    return 4*pi;
}

double calcularPiSeparado(int n){
    double pi;
    double pos = 0; // Suma de términos con denominador 4k + 1
    double neg = 0; // Suma de términos con denominador 4k + 3
    for(double k=0; k<=n; k++){
        pos += 1/(4*k+1); // Suma los términos con denominador 4k + 1
        neg += 1/(4*k+3); // Suma los términos con denominador 4k + 3
    }

    pi = pos - neg; // Resta las dos sumas para obtener pi/4
    return 4*pi; // Multiplica por 4 para obtener el valor final de pi
}