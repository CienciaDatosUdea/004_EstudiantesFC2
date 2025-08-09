/* Tarea 1:
Sara Alejandra Carvajal Ramírez
  Cálculo de sumas parciales de series geométricas
  
  Objetivo:
  Escribir un programa en C++ que aproxime el valor de pi utilizando la serie de 			Leibniz 
  * Crear una función que reciba el número de terminos y devuelva el valor de pi 
  * Crear una función que calcule pi sumando los términos con denominadores de la forma 4k+1 y restando los de 4k+3, como se muestra en la segunda fórmula.

*/


#include <iostream>
#include <cmath>  
using namespace std;

double calcularPiLeibniz(int n);
double calcularPiSeparado(int n);

int main() {
  int n;
  double resultado_f1, resultado_f2; 

  /* Solicita al usuario el número de términos que quiere usar*/
  cout << "Ingrese el número de términos que quiere usar:" << endl;
  cin >> n;

  if (n < 0) {
        cout << "Este número es negativo, intente denuevo:" << endl;
    } 
  else {
  resultado_f1 = calcularPiLeibniz(n);  /* Llamamos a la función */
  cout << "El valor teorico por suma de Leibniz es:"<< resultado_f1 << endl;
  
  resultado_f2 = calcularPiSeparado(n);  /* Llamamos a la función */
  cout << resultado_f2 << endl;
    }

  cout << "El valor reportado en CMATH para pi es:"<<M_PI<<endl;
  return 0;
}

/* Definición de la serie de Leibniz*/
double calcularPiLeibniz(int n){
  float a = 1;        		/* Primer término de la serie */
  float i = 0, suma1= 0;   

  cout << "\n Programa para calcular el valor de Pi a partír de la serie \n de Leibniz" << endl;

  /* Bucle que suma los primeros n términos de la serie */
 for (i = 0; i <= n; i ++) {
    suma1 += 4*(pow(-1,i)/((2*i)+1));
  }
  return suma1;
}

/* Definición de la serie de Leibniz Separada*/
double calcularPiSeparado(int n){
  float a = 1;        		/* Primer término de la serie */
  float i = 0, suma2 = 0;  
  float termsum=0, termresta=0;
  cout << "Programa para calcular el valor de Pi a partír de la serie \n de Leibniz" << endl;

  /* Bucle que suma los primeros n términos de la serie */
  while (i <= n) {
    termsum += 1./(4*i+1);
    termresta += -1./(4*i+3);
    i++;
  }
  suma2 = 4* (termsum + termresta);  
  cout << "Valor teórico de Pi a través del método separado es: " << suma2 << endl;
  return 0;
}



