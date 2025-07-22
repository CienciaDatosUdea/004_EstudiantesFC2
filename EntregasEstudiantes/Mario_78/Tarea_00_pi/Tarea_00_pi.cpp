/*
  En este código, se utiliza la Serie de leibniz para calcular el valor de π por medio de dos métodos:

  1. Se calcula el número π utilizando directamente la serie.
  2. Se calcula el número π  separando explícitamente los téminos positivos y negativos

*/ 

// Librerías
#include<iostream>
#include<cmath>
#include<iomanip>
#include<string>

using namespace std;

// Declaramos las funciones
bool esEntero(string);               // Verifica si una cadena de entrada representa un número entero no negativo
double calcularPiLeibniz(int);       // Calcula π  usando la serie de Leibniz  π = 4Σ(-1)^n/(2n+1)
double calcularPiSeparado(int);      // Calcula π separando la serie en términos positivos y negativos

int main(){
  
  string entrada;                      // Variable para leer la entrada como cadena
  int n;                               // Número de términos 
  double π = M_PI;                     // Valor real de pi

  cout<<"\n### Calculo del nümero π usando la Serie de Leibniz ### \n"<<endl; 
 
  // Validar que la entrada sea mayor o igual a cero
  do 
  {
    cout << "Número de términos --->  n = ";
    cin >> entrada;                       // Leer entrada como cadena
    if (!esEntero(entrada)) {             // Verifica si es entero no negativo
    cout << "¡Error! n debe ser un número entero mayor o igual que cero, sin comas ni puntos.\n";
    cout<<endl;
    }
  } 
  while (!esEntero(entrada));             // Repite mientras sea inválido
  n = stoi(entrada);                      // Convierte la entrada validada a entero y se la asigna a la variable n
    
  // LLamada de las funciones (ejecución)
  double resultado1 = calcularPiLeibniz(n);          
  double resultado2 = calcularPiSeparado(n);          
    
  // Resultados
  cout<<"\nPrimera aproximación de π: "<<fixed<<setprecision(10)<<resultado1<<endl;
  cout<<"Segunda aproximación de π: "<<fixed<<setprecision(10)<<resultado2<<endl;
  cout<<"valor real de π: "<<fixed<<setprecision(10)<<π<<endl;
  cout<<"El error absoluto para la primera aproximación es = "<<abs(π - resultado1)<<endl;  // Error = |valor aproximado - valor exacto|
  cout<<"El error absoluto para la segunda aproximación es = "<<abs(π - resultado2)<<endl;
  cout<<endl; 

  return 0;
}

// Función para comprobar si la entrada es un número entero no negativo
bool esEntero(string entrada) {
  if (entrada.empty()) return false;                        // Rechaza si la cadena está vacía
  for (char c : entrada) {                                  // Recorre cada carácter
    if (!isdigit(c)) return false;                          // Rechaza si algún carácter no es dígito
  }
  return true;                                              // Acepta si todos los caracteres son dígitos (de 0 a 9)
}

// Función para calcular π por serie de Libniz
double calcularPiLeibniz(int n){                       
  int i = 0;                                          // Contador para las sumas parciales
  double sum = 0;                                     // Acumulador de las sumas parciales
  while (i < n)
    {  
      double sum1 = pow(-1, i)/(2*i + 1);             // Término i-ésimo
      sum += sum1;                                    // sum = sum + sum1                                                     
      i++;
    } 
    return 4*sum;                                     // retorna valor aproximado de π
}

// Función para calcular π con la serie de Leibniz  separando en sumas positivas y negativas 
double calcularPiSeparado(int n){                     
  int i = 0;                                          // Contador para las sumas parciales
  double T1 = 0;                                      // Acumulador de las sumas parciales para denominadores 4k+1
  double T2 = 0;                                      // Acumulador de las sumas parciales para denominadores 4k+3
  while (i < n)
    {  
      double sum1 = 1.0/(4*i + 1);                    // Término i-ésimo
      double sum2 = 1.0/(4*i + 3);                    // Término i-ésimo 
      T1 += sum1;                                     // T1 = T1 + sum1 (suma de términos positivos)
      T2 += sum2;                                     // T1 = T1 + sum2 (sumas de términos negativos)    
      i++;
    } 
    return 4*(T1 - T2);                               // retorna valor aproximado de π
}
    
       
   
 
 
