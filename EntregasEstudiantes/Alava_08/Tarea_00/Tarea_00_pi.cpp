#include <iostream>
#include <cmath>    // Para usar M_PI
#include <iomanip>  // Para controlar la precisión de salida

using namespace std;

// Función que calcula pi usando la forma  de la serie de Leibniz
double calcularPiLeibniz(int n) {
    double pi = 0.0;
    for (int k = 0; k < n; ++k) {
        pi += pow(-1, k) / (2 * k + 1);  // Alterna signos
    }
    return 4 * pi;
}

// Función que calcula pi separando términos con denominadores 4k+1 y 4k+3
double calcularPiSeparado(int n) {
    double pi = 0.0;
    for (int k = 0; k < n; ++k) {
        int denominador = 2 * k + 1;
        if (denominador % 4 == 1) {
            pi += 1.0 / denominador;
        } else {
            pi -= 1.0 / denominador;
        }
    }
    return 4 * pi;
}

int main() {
    int n;

    // Solicitamos al usuario el número de términos
    cout << "Ingrese el número de términos para aproximar π: ";
    cin >> n;

    // Validación de la entrada
    if (n <= 0) {
        cerr << "Error: El número de términos debe ser un entero positivo." << endl;
        return 1; // Termina el programa con error
    }

    // Cálculos de pi
    double piLeibniz = calcularPiLeibniz(n);
    double piSeparado = calcularPiSeparado(n);
    double piReal = M_PI;

    // Cálculo de errores absolutos
    double errorLeibniz = fabs(piReal - piLeibniz);
    double errorSeparado = fabs(piReal - piSeparado);

   

    // Mostrar resultados
    cout << "\n--- Resultados ---" << endl;
    cout << "Valor real de π        : " << piReal << endl;
    cout << "Aproximación (Leibniz) : " << piLeibniz << endl;
    cout << "Aproximación (Separado): " << piSeparado << endl;
    cout << "Error absoluto (Leibniz): " << errorLeibniz << endl;
    cout << "Error absoluto (Separado): " << errorSeparado << endl;

    return 0;
}

