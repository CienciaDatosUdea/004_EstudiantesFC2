#include "../include/fir_filter.h"

// Constructor pasa-bajas / pasa-altas
FIRFilter::FIRFilter(int numtaps, double fs, double cutoff, FilterType type)
    : numtaps(numtaps), fs(fs), cutoff1(cutoff), cutoff2(0), type(type) {
    designFilter();
}

// Constructor pasa-banda / rechaza-banda
FIRFilter::FIRFilter(int numtaps, double fs, double cutoffLow, double cutoffHigh, FilterType type)
    : numtaps(numtaps), fs(fs), cutoff1(cutoffLow), cutoff2(cutoffHigh), type(type) {
    designFilter();
}

// Diseño del filtro FIR con ventana de Hamming
void FIRFilter::designFilter() {
    coeffs.resize(numtaps);          // Se reserva espacio para los coeficientes
    int M = numtaps - 1;             // Orden del filtro

    // Bucle para calcular cada coeficiente
    for (int n = 0; n < numtaps; n++) {
        double val = 0.0;            // Valor base del coeficiente antes de aplicar ventana
        int k = n - M / 2;           // Índice centrado respecto al medio

        // Selección del tipo de filtro
        if (type == FilterType::LOWPASS) {
            double fc = cutoff1 / fs;             // Frecuencia de corte normalizada
            if (k == 0) val = 2.0 * fc;           // Caso especial en k=0
            else val = sin(2.0 * M_PI * fc * k) / (M_PI * k);
        }
        else if (type == FilterType::HIGHPASS) {
            double fc = cutoff1 / fs;
            if (k == 0) val = 1.0 - 2.0 * fc;
            else val = -sin(2.0 * M_PI * fc * k) / (M_PI * k);
        }
        else if (type == FilterType::BANDPASS) {
            double f1 = cutoff1 / fs;
            double f2 = cutoff2 / fs;
            if (k == 0) val = 2.0 * (f2 - f1);
            else val = (sin(2.0 * M_PI * f2 * k) - sin(2.0 * M_PI * f1 * k)) / (M_PI * k);
        }
        else if (type == FilterType::BANDSTOP) {
            double f1 = cutoff1 / fs;
            double f2 = cutoff2 / fs;
            if (k == 0) val = 1.0 - 2.0 * (f2 - f1);
            else val = (sin(2.0 * M_PI * f1 * k) - sin(2.0 * M_PI * f2 * k)) / (M_PI * k);
        }

        // Ventana de Hamming
        coeffs[n] = val * (0.54 - 0.46 * cos(2.0 * M_PI * n / M));
    }
}

// Mostrar coeficientes en consola
void FIRFilter::printCoefficients() const {
    std::cout << "\nCoeficientes FIR:\n";
    for (double c : coeffs) {
        std::cout << c << std::endl;
    }
}

// Cálculo de la respuesta en frecuencia del filtro
std::vector<std::pair<double, double>> FIRFilter::frequencyResponse(int Nfft) const {
    std::vector<std::pair<double, double>> response;
    response.reserve(Nfft/2 + 1);   // Solo se necesita hasta Nyquist (fs/2)
    
    // Cálculo de la DFT (Discrete Fourier Transform / Transformada Discreta de Fourier) para cada frecuencia
    for (int k = 0; k <= Nfft/2; k++) {
        std::complex<double> H(0.0, 0.0);      // Respuesta compleja en frecuencia
        double omega = 2.0 * M_PI * k / Nfft;  // Frecuencia angular normalizada

        // Evaluación de la DTFT(Discrete-Time Fourier Transform / Transformada de Fourier en tiempo discreto) en omega
        for (int n = 0; n < numtaps; n++) {
            H += coeffs[n] * std::exp(std::complex<double>(0, -omega * n));
        }
        double freq = (k / (double)Nfft) * fs;            // Frecuencia en Hz
        double magnitude = 20.0 * log10(std::abs(H));     // Magnitud en dB
        response.emplace_back(freq, magnitude);           // Se guarda el par (frecuencia, magnitud)
    }
    return response;
}

// Exportar coeficientes y respuesta en frecuencia a un archivo
void FIRFilter::exportData(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error al abrir archivo para exportar.\n";
        return;
    }
    
    // Escribir coeficientes
    file << "# Coeficientes FIR\n";
    for (double c : coeffs) {
        file << c << "\n";
    }
    
    // Escribir respuesta en frecuencia
    file << "\n# Frecuencia (Hz)\tMagnitud (dB)\n";
    auto response = frequencyResponse();
    for (auto &r : response) {
        file << r.first << "\t" << r.second << "\n";
    }

    file.close();
    std::cout << "Datos exportados a: " << filename << std::endl;
}
