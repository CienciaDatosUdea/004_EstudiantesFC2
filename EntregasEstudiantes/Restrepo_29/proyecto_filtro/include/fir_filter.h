#include <iostream>   // Entrada y salida estándar (cout, cin, etc.)
#include <vector>     // Contenedor dinámico tipo array (std::vector)
#include <cmath>      // Funciones matemáticas (sin, cos, pow, M_PI, etc.)
#include <fstream>    // Manejo de archivos (ifstream, ofstream)
#include <complex>    // Números complejos (std::complex)
#include <string>     // Cadenas de texto (std::string)

#define M_PI 3.14159265358979323846

// Tipos de filtros FIR
enum class FilterType {
    LOWPASS,
    HIGHPASS,
    BANDPASS,
    BANDSTOP
};

/* Clase que implementa un filtro FIR (Finite Impulse Response).
   Permite diseñar filtros digitales de tipo pasa-bajas, pasa-altas,
   pasa-banda y rechaza-banda, calculando sus coeficientes y 
   ofreciendo métodos para exportarlos o mostrarlos.    */

class FIRFilter {
private:
    int numtaps;                    // Número de coeficientes (en la implementación se generan numtaps + 1 coeficientes )
    double fs;                      // Frecuencia de muestreo
    double cutoff1;                 // Frecuencia de corte baja
    double cutoff2;                 // Frecuencia de corte alta
    FilterType type;                // Tipo de filtro
    std::vector<double> coeffs;     // Coeficientes del filtro

    void designFilter();            // Método para diseñar el filtro

public:
    // =========================================================
    // Constructores
    // =========================================================

    // Constructor para filtros pasa-bajas o pasa-altas
    FIRFilter(int numtaps, double fs, double cutoff, FilterType type); 

    // Constructor para filtros pasa-banda o rechaza-banda 
    FIRFilter(int numtaps, double fs, double cutoffLow, double cutoffHigh, FilterType type);

    // =========================================================
    // Métodos públicos
    // =========================================================

    // Imprime en consola los coeficientes calculados del filtro FIR
    void printCoefficients() const;

    // Calcula la respuesta en frecuencia del filtro
    // Nfft: número de puntos de la FFTN <<Fast Fourier Transform con N puntos>> (por defecto 8000)
    // Devuelve un vector de pares (frecuencia en Hz, magnitud en dB)
    std::vector<std::pair<double, double>> frequencyResponse(int Nfft = 8000) const;

    // Exporta los coeficientes y la respuesta en frecuencia a un archivo de texto
    // filename: ruta del archivo de salida
    void exportData(const std::string &filename) const;
};

