#include <iostream>     // Libreria para la entrada y salida de datos por consola 
#include <cmath>        // Libreria para usar funciones matemáticas 

using namespace std;


double calcularPiLeibniz(int n);    // Función que calcula pi con la serie de Leibniz
double calcularPiSeparado(int n);  // Función que calcula pi usando la diferencia de dos series
double errorabsoluto(double m);   // Función que calcula el error absoluto comparado con M_PI

int main() {
    // Declaración de variables
    int n;                                  
    double pi, pi_separado;                 
    double error_pi, error_pi_separado;    

    // Solicita al usuario el número de términos a usar en la serie 
    cout << "Ingrese el número de términos que quiere usar en la serie para el cálculo de pi: ";
    cin >> n;

    // Valida que el número sea positivo
    while (n < 0) {
        cout << "Recuerda que el número de términos debe ser un número positivo. Inténtalo nuevamente: ";
        cin >> n;
    }

    // Calcula pi por ambos métodos
    pi = calcularPiLeibniz(n);
    pi_separado = calcularPiSeparado(n);

    // Calcula errores absolutos en ambos casos
    error_pi = errorabsoluto(pi);
    error_pi_separado = errorabsoluto(pi_separado);

    // Muestra resultados
    cout << "El valor teórico de pi es: " << M_PI << endl;
    cout << "El valor aproximado de pi con la serie de Leibniz es: " << pi << " y su error absoluto es " << error_pi << endl;
    cout << "El valor aproximado de pi con la resta de series es: " << pi_separado << " y su error absoluto es " << error_pi_separado << endl;

    return 0;
}

// Función que calcula pi usando la serie de Leibniz
double calcularPiLeibniz(int n) {
    double suma = 0;
    int i = 0;

    while (i < n) {
        double termino = pow(-1.0, i) / (2 * i + 1);
        suma += termino;
        i++;
    }

    return 4 * suma; // Multiplica la suma por 4 para aproximar pi
}

// Función que calcula pi separando los términos 1/(4i+1) y 1/(4i+3)
double calcularPiSeparado(int n) {
    double suma1 = 0, suma2 = 0;
    int i = 0;

    // Suma n términos a cada parte de la serie
    while (i < n) {
        double termino1 = 1.0 / (4 * i + 1);
        suma1 += termino1;

        double termino2 = 1.0 / (4 * i + 3);
        suma2 += termino2;

        i++;
    }

    return 4 * (suma1 - suma2); 
}

// Función que calcula el error absoluto entre pi teórico y aproximado
double errorabsoluto(double m) {
    double Teorico = M_PI;    // Valor teórico de pi
    return abs(Teorico - m); // Error absoluto
}







