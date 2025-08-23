#include<iostream>
#include<string>
#include<cmath>
using namespace std;

double calcularPiLeibniz(int); // Declaro la función que calcula pi completa
double calcularPiSeparado(int); // Declaro la función que calcula pi en dos paquetes.


//------------------------------------- Función principal.
int main(){
int n;
cout << "Este programa calcula el valor aproximado de PI a través de la serie de Leibniz"<< endl;
cout << "Ingrese el número de términos para calcular el valor de PI: "<< endl;
cin >> n;
while (n <= 0) {
    cout << "No es un valor válido, debe ser mayor que cero"<<endl;
    cout << "Ingrese nuevamente el valor"<< endl;
    cin >> n;    
}
   
double pi_leibniz = calcularPiLeibniz(n); // Llamo las funciones.
double pi_separado = calcularPiSeparado(n);

double pi_m =  M_PI;                   // Valor calculado con la librería cmath

double error_leibniz = abs( pi_m - pi_leibniz);
double error_separado = abs(pi_m - pi_separado);

cout << "el valor aproximado de Pi calculando la serie completa es: "<< pi_leibniz<< endl;
cout << "el valor aproximado de Pi calculando la serie en dos partes es: "<< pi_separado<< endl;
cout << "el error absoluto para la serie completa es: "<< error_leibniz<< endl;
cout << "el error absoluto para la serie en dos partes es: "<< error_separado << endl;

return 0;
}

//-------------------------------------- función para calcular la serie completa
double calcularPiLeibniz(int n){

double pi = 0;

   for (int k = 0; k < n; k++){

       pi = pi + (4*((pow(-1,k))/((2.0*k)+1.0) ));  
    }
 return pi;   
}


//----------------------------------- Función para calcular la serie en dos paquetes.
double calcularPiSeparado(int n){
double pi_p= 0, pi_n=0, pi=0;
    for(int k= 0; k <= (n/2); k++){
        pi_p = pi_p + (4/((4.0*k)+1.0)); // Calcula la sumatoria de los elementos positivos de la serie.
        pi_n = pi_n + (4/((4.0*k)+3.0)); // Calcula la sumatoria de los elementos negativos de la serie.
  

    } 
      
    pi = pi_p - pi_n;
    
  return pi;  
}    