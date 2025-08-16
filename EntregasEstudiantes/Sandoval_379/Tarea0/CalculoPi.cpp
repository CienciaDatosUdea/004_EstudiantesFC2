#include <iostream>
#include <iomanip>   // formato de salida (setprecision, fixed)
#include <cmath>     // acosl, fabsl

// --------------------------------------------------------------
// Programa: Aproximación de π con dos variantes de la serie de Leibniz
// Objetivo: Calcular dos aproximaciones de π y comparar su error absoluto
// Estilo: código y nombres sutilmente diferentes, con comentarios explicativos
// --------------------------------------------------------------

// Devuelve el valor de π sin depender de macros (M_PI), usando identidad trig.
long double valorPiExacto() {
    return acosl(-1.0L);  // arccos(-1) = π
}

// Variante 1: Serie de Leibniz directa
// π ≈ 4 * ∑_{k=0}^{n-1} (-1)^k / (2k + 1)
long double aproximacionLeibniz(std::size_t n) {
    long double acumulado = 0.0L;
    // Señal alternante controlada por paridad (k & 1)
    for (std::size_t k = 0; k < n; ++k) {
        long double termino = 1.0L / static_cast<long double>(2 * k + 1);
        acumulado += ( (k & 1) ? -termino : termino );
    }
    return 4.0L * acumulado;
}

// Variante 2: Misma suma, pero separando la lógica del signo segun (2k+1) mod 4
// Si (2k+1) ≡ 1 (mod 4) → suma; si ≡ 3 (mod 4) → resta.
long double aproximacionSeparada(std::size_t n) {
    long double acumulado = 0.0L;
    for (std::size_t k = 0; k < n; ++k) {
        int denom = static_cast<int>(2 * k + 1);
        // signo en función del residuo módulo 4
        long double signo = (denom % 4 == 1) ? 1.0L : -1.0L;
        acumulado += signo / static_cast<long double>(denom);
    }
    return 4.0L * acumulado;
}

// Utilidad: error absoluto entre dos magnitudes
long double errorAbsoluto(long double estimado, long double referencia) {
    return fabsl(estimado - referencia);
}

int main() {
    std::size_t terminos;

    // Entrada de datos: número de términos a utilizar
    std::cout << "Cantidad de terminos para aproximar pi: ";
    if (!(std::cin >> terminos) || terminos == 0) {
        std::cerr << "Entrada invalida. Proporcione un entero positivo.\n";
        return 1;
    }

    // Cálculos principales
    const long double pi_ref = valorPiExacto();
    const long double pi_v1  = aproximacionLeibniz(terminos);
    const long double pi_v2  = aproximacionSeparada(terminos);

    // Errores absolutos respecto al valor de referencia
    const long double err_v1 = errorAbsoluto(pi_v1, pi_ref);
    const long double err_v2 = errorAbsoluto(pi_v2, pi_ref);

    // Salida con formato: más dígitos para inspección
    std::cout << std::fixed << std::setprecision(15);
    std::cout << "\n=== Resultados ===\n";
    std::cout << "Pi (referencia)        : " << pi_ref << '\n';
    std::cout << "Aprox. Leibniz         : " << pi_v1  << '\n';
    std::cout << "Aprox. separada (mod 4): " << pi_v2  << '\n';
    std::cout << "Error |Leibniz - ref|  : " << err_v1 << '\n';
    std::cout << "Error |Sep - ref|      : " << err_v2 << '\n';

    return 0;
}
