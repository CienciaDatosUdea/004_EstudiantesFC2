// Cálculo de pi con la serie de Leibniz

#include <iostream>  // Biblioteca para entrada/salida estándar
#include <cmath>     // Biblioteca para funciones matemáticas (como pow y M_PI)

using namespace std;

// Declaración de funciones
float serie(int);   // Aproxima pi usando la fórmula clásica de la serie de Leibniz
float serie2(int);  // Aproxima pi usando una versión optimizada agrupando términos

int main() {
    int n;  // Variable para almacenar cuántos términos quiere el usuario

    // Solicita al usuario la cantidad de términos a usar
    cout << "Introduzca cuantos términos quiere para la aproximación de pi" << endl;
    cin >> n;

    // Imprime el valor aproximado de pi usando el primer método
    cout << "Con el método 1, pi es igual a: " << serie(n) << endl;

    // Imprime el valor aproximado de pi usando el segundo método
    cout << "Con el método 2, pi es igual a: " << serie2(n) << endl;

    // Imprime el valor real de pi desde la constante M_PI de la librería cmath
    cout << "El valor de la librería cmath es: " << M_PI << endl;

    return 0;  // Fin del programa
}

// Función que calcula pi usando la serie de Leibniz clásica
float serie(int n) {
    float s = 0;  // Variable para acumular la suma de los términos

    // Bucle que suma n+1 términos de la serie de Leibniz
    for (int i = 0; i <= n; i++) {
        s += pow(-1, i) / (2 * i + 1);  // Alterna signo con pow(-1, i)
    }

    return 4 * s;  // Multiplica por 4 según la fórmula de la serie
}

// Función alternativa para calcular pi agrupando términos
float serie2(int n) {
    float s, t1 = 0, t2 = 0;  // s es el resultado, t1 y t2 son sumas parciales

    // Agrupa términos positivos y negativos (ej: 1/1 - 1/3, 1/5 - 1/7, ...)
    for (int i = 1; i <= (n + 1) / 2; i = i + 4) {
        t1 += 1.0 / i;        // Acumula los términos positivos: 1/1, 1/5, ...
        t2 += 1.0 / (i + 2);  // Acumula los términos negativos: 1/3, 1/7, ...
    }

    s = t1 - t2;  // Calcula la suma total agrupada

    return 4 * s;  // Multiplica por 4 para obtener pi
}


