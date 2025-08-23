#include <iostream>
#include <cmath>

using namespace std;

// Cálculo de pi mediante la serie de Leibniz directamente
double piLeibniz(int n) {
    double suma = 0.0;
    for (int k = 0; k <= n; k++) {
        suma += 4.0 * pow(-1, k) / (2 * k + 1);  // término general
    }
    return suma;
}

// Cálculo de pi separando contribuciones positivas y negativas
double piSeparado(int n) {
    double positivos = 0.0;
    double negativos = 0.0;

    // Términos con índice par → positivos
    for (int k = 0; k <= n; k += 2) {
        positivos += 4.0 / (2 * k + 1);
    }

    // Términos con índice impar → negativos
    for (int k = 1; k <= n; k += 2) {
        negativos += 4.0 / (2 * k + 1);
    }

    return positivos - negativos;
}

int main() {
    int n;
    cout << "Ingrese un número entero positivo para n: ";
    cin >> n;

    // Validación de entrada
    while (n < 0) {
        cout << "Error: n debe ser un número positivo. Intente de nuevo: ";
        cin >> n;
    }

    // Cálculo de aproximaciones
    double pi1 = piLeibniz(n);
    double pi2 = piSeparado(n);

    // Cálculo de errores absolutos
    double error1 = fabs(pi1 - M_PI);
    double error2 = fabs(pi2 - M_PI);

    // Mostrar resultados
    cout << "\n--- Resultados ---\n";
    cout << "Serie de Leibniz: " << pi1 << "\n";
    cout << "Error absoluto:   " << error1 << "\n";
    cout << "--------------------------------------\n";
    cout << "Método separado:  " << pi2 << "\n";
    cout << "Error absoluto:   " << error2 << "\n";

    return 0;
}