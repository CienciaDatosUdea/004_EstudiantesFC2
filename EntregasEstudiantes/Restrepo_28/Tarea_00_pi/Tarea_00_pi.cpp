#include <iostream>
#include <cmath>
#include <string>

using namespace std;

double calcularPiLeibniz(int);
double calcularPiSeparado(int);

int main(){
    int n;
    do{
    cout<<"cuántos términos a usar? favor usar un número positivo, números decimales serán truncados hacia abajo.\n";
    cin>>n;
    }
    while(n<0);

    double PiLeibniz = calcularPiLeibniz(n);
    double PiSeparado = calcularPiSeparado(n);

    cout<<"Valor PI exacto:"<<M_PI<<endl;
    cout<<"Aproximación Leibniz: "<<PiLeibniz<<", error absoluto: "<<abs(PiLeibniz-M_PI)<<endl;

    cout<<"Aproximación Separado: "<<PiSeparado<<", error absoluto: "<<abs(PiSeparado-M_PI)<<endl;
    return 0;
}

double calcularPiLeibniz(int n){
    /*
    Usa la serie de Leibniz para aproximar Pi
    n: número de terminos a usar, entero.
    */
    double sum = 0;
    for(int i = 0;i<n;i++){
        sum += pow(-1,i) * 1/(2*i + 1);
    }

    return 4.0*sum;
}

double calcularPiSeparado(int n){
    /*
    Usa la serie de Leibniz separando terminos positivos y negativos y luego restandolos
    n: número de terminos a usar, entero.
    
    */
    double positivePart = 0;
    double negativePart = 0;
    for(int i = 0;i<n;i++){
        positivePart += 1/(4*i+1);
        negativePart += 1/(4*i+3);
    }

    return 4.0*(positivePart-negativePart);
}