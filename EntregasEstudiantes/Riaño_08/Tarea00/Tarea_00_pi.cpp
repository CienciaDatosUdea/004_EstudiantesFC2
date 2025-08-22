#include <iostream>
#include<cmath>
using namespace std;

double calcularPiLeibniz(int n);
double calcularPiSeparado(int n);

int main(){

    int n;
    cout<<"Ingrese el número de términos (entero) de la serie de Leibniz para realizar el cálculo de pi:"<<endl;
    cin>>n;

    //Bucle y condicional para repetir la entrada si se ingresó un valor negativo.

    if (n <= 0){

        do{
            cout<<"\nEl número ingresado no es un número positivo. Inténtelo de nuevo."<<endl;
            cout<<"\nIngrese el número de términos (entero) de la serie de Leibniz para realizar el cálculo de pi:"<<endl;
            cin>>n;
        }
        
        while (n <= 0);

    }  

    cout<<"\n1) Valor de pi con la serie de Leibniz: "<<calcularPiLeibniz(n)<<endl;
    cout<<"2) Valor de pi con la serie de Leibniz, pero separando pares e impares: "<<calcularPiSeparado(n)<<endl;
    cout<<"Valor de real de pi: "<<M_PI<<endl;
    cout<<"\nError absoluto para el primer caso: "<<fabs(M_PI-calcularPiLeibniz(n))<<endl;
    cout<<"Error absoluto para el segundo caso: "<<fabs(M_PI-calcularPiSeparado(n))<<endl;

    return 0;
}

double calcularPiLeibniz(int n) {

    //Función para obtener el valor de pi mediante la serie de Leibniz. 
    //El valor de entrada es la cantidad de términos de la sumatoria.

    int k = 0;
    double suma = 0.0;

    while (k < n) {

        double termino = pow(-1.,k)/(2.*k+1.);  //k-ésmio término.
        suma += termino;
        k++;
    }

    return 4*suma;
}

double calcularPiSeparado(int n) {

    //Función para obtener el valor de pi mediante la serie de Leibniz, pero separando 
    //El valor de entrada es la cantidad de términos de la sumatoria.

    int k_par = 0;
    int k_impar = 0;
    double suma_par = 0.0;
    double suma_impar = 0.0;

    //Se hace la distinción entre dos casos: n par o n impar.
    //Si n es par, la cantidad de términos pares e impares es la misma.
    //Si n es impar, la cantidad de términos pares supera en uno a la cantidad de impares.

    if (n % 2 == 0) {

        while (k_par < n/2) {

            double termino_par = 1./(4.*k_par+1.);
            double termino_impar = 1./(4.*k_impar+3.);
            suma_par += termino_par;
            suma_impar += termino_impar;
            k_par++;
            k_impar++;
        }

        return 4*(suma_par-suma_impar);

    } 
    
    else {


        while (k_impar < (n-1)/2) {
            
            double termino_par = 1./(4.*k_par+1.);
            double termino_impar = 1./(4.*k_impar+3.);
            suma_par += termino_par;
            suma_impar += termino_impar;
            k_par++;
            k_impar++;
        }

        suma_par += 1./(4.*((n-1)/2)+1.);

        return 4*(suma_par-suma_impar);
    
    }

}