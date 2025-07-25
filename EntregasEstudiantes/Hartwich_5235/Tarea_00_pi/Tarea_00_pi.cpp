#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int instructUser();
double calcularPiLeibnitz(int);
double calcularPiSeparado(int);
void displayResults(int, double, double);

int main() {

    // system("clear -x"); // solo funciona en linux (y si tiene clear de Ncurses)
    std::cout << "\033[H\033[J"; // alternativa para system("clear -x") que debería funcionar en MacOS también (más no Windows)
    
    // iniciar variables
    int n {0};
    double sumaLeibnitz {0};
    double sumaSeparado {0};

    // Output describiendo la función del programa
    n = instructUser();

    // calcular resultados
    sumaLeibnitz = calcularPiLeibnitz(n);
    sumaSeparado = calcularPiSeparado(n);

    // Output describiendo los resultados y los errores absolutos
    displayResults(n, sumaLeibnitz, sumaSeparado);

    return 0;

}

int instructUser() {
    int n {0};
    cout << "\n"
         << "Este código va a calcular pi usando la serie de Leibnitz de dos formas diferentes. La primera forma usa la serie normal con denominador (2k+1). La segunda forma calcula las sumas con denominador (4k+1) y (4k+3) de manera separada y las suma después para evitar problemas numéricos.\n\nIngrese la cantidad de términos que quiere incluir."
         << "\n\n\tn = ";
         // input de n
    cin >> n;
    // comprobar que n sea positivo, repetir el input mediante cin si necesario
    while (n <= 0) {
        cout << "\nIngrese un número entero positivo."
             << "\n\n\tn = ";
        cin >> n;
    }
    return n;
}

double calcularPiLeibnitz(int n) {
    // iniciar variables
    double suma {0};
    // calcular la suma
    for (int k = 0; k < n; k++) {
        suma += pow(-1, k) / (2*k + 1);
    }
    suma *= 4;
    return suma;
}

double calcularPiSeparado(int n) {
    // iniciar variables
    double suma {0};
    double sumaPositiva {0};
    double sumaNegativa {0};
    // calcular las sumas (esto es totalmente equivalente a usar como denominadores (4k+1) y (4k+3), solo que opté por esta sintax para que se incluyan automáticamente el mismo número de términos que con la función calcularPiLeibnitz. Al usar un solo for para ambas sumas, habría que diferenciar entre n pares e impares para este fin.)
    for (int k = 0; k < n; k += 2) {
        sumaPositiva += pow((2*k + 1), -1);
    }
    for (int k = 1; k < n; k += 2) {
        sumaNegativa -= pow((2*k + 1), -1);
    }
    suma = 4 * (sumaPositiva + sumaNegativa);
    return suma;
}

void displayResults(int n, double sumaLeibnitz, double sumaSeparado) {
    // calcular Errores
    double errorLeibnitz { abs(sumaLeibnitz - M_PI) };
    double errorSeparado { abs(sumaSeparado - M_PI) };
    // output de los resultados
    cout << "\n"
         << "Según la librería cmath, el valor de pi es "
         << M_PI
         << "."
         << "\n\n"
         << "Los valores de las sumatorias para "
         << n
         << " términos incluidos son:"
         << "\n\n\t"
         << "Forma 1:\t"
         << setprecision(6) << sumaLeibnitz
         << "\t\tcon un error absoluto de\t"
         << setprecision(6) << errorLeibnitz
         << "\n\t"
         << "Forma 2:\t"
         << setprecision(6) << sumaSeparado
         << "\t\tcon un error absoluto de\t"
         << setprecision(6) << errorSeparado
         << "\n"
         << endl;
}