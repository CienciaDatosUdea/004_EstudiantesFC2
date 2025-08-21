#define _USE_MATH_DEFINES
#include <iostream> 
#include <cmath>    
#include <iomanip>  
#include <limits>   

using namespace std;

double calcularPiLeibniz(int n) {
    double suma = 0.0;
    for (int k = 0; k < n; ++k) {
        // pow(-1, k) genera la alternancia de signos (+1, -1, +1, -1, ...)
        // (2.0 * k + 1.0) genera los denominadores (1, 3, 5, 7, ...)
        suma += pow(-1, k) / (2.0 * k + 1.0);
    }
    return 4.0 * suma;
}


double calcularPiSeparado(int n) {
    double suma = 0.0;
    for (int k = 0; k < n; ++k) {
        if (k % 2 == 0) { // Término positivo
            suma += 1.0 / (2.0 * k + 1.0);
        } else { // Término negativo
            suma -= 1.0 / (2.0 * k + 1.0);
        }
    }
    return 4.0 * suma;
}

int main() {
    int n;

    // 1. Solicitar y validar la entrada del usuario
    cout << "Programa de aproximacion de PI" << endl;
    cout << "--------------------------------" << endl;
    cout << "Ingrese el numero de terminos a usar (debe ser un entero positivo): ";

    // Bucle para asegurar que la entrada sea un número positivo
    while (!(cin >> n) || n <= 0) {
        cout << "Entrada invalida. Por favor, ingrese un numero entero positivo: ";
        cin.clear(); // Limpia el estado de error de cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Descarta la entrada incorrecta
    }

    // 2. Definir el valor real de PI para la comparación
    const double pi_real = M_PI;

    // 3. Calcular las aproximaciones llamando a las funciones
    double pi_aprox_leibniz = calcularPiLeibniz(n);
    double pi_aprox_separado = calcularPiSeparado(n);

    // 4. Calcular los errores absolutos
    double error_leibniz = fabs(pi_real - pi_aprox_leibniz);
    double error_separado = fabs(pi_real - pi_aprox_separado);

    // 5. Imprimir los resultados de forma clara y formateada
    cout << "\n--- Resultados con " << n << " terminos ---" << endl;
    // fixed y setprecision(10) para mostrar 10 decimales
    cout << fixed << setprecision(10);
    cout << "Valor real de PI (M_PI):     " << pi_real << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Aproximacion con Leibniz:      " << pi_aprox_leibniz << endl;
    cout << "Error absoluto (Leibniz):      " << error_leibniz << endl;
    cout << "-----------------------------------------------------" << endl;
    cout << "Aproximacion con Suma/Resta:   " << pi_aprox_separado << endl;
    cout << "Error absoluto (Suma/Resta):   " << error_separado << endl;

    return 0;
}