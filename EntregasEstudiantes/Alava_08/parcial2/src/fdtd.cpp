#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include "fdtd.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

// Constructor
WavePropagator::WavePropagator(int cantidadNodos, double factorBeta) 
    : numPuntos(cantidadNodos), BETA_FACTOR(factorBeta) {
    
    // Redimensionamos los vectores para los campos
    campoE.assign(numPuntos, std::vector<double>(2, 0.0));
    campoH.assign(numPuntos, std::vector<double>(2, 0.0));
    tipoDeCondicionDeBorde = "periodic"; // Por defecto
    inicializarVectores();
}

void WavePropagator::inicializarVectores() {
    for (int i = 0; i < numPuntos; ++i) {
        double posicion = i;
        campoE[i][0] = 0.1 * sin(2.0 * M_PI * posicion / 100.0);
        campoH[i][0] = 0.1 * sin(2.0 * M_PI * posicion / 100.0);
    }
}

void WavePropagator::definirLimites(const std::string& tipoDeBorde) {
    if (tipoDeBorde == "periodic" || tipoDeBorde == "absorbing") {
        tipoDeCondicionDeBorde = tipoDeBorde;
    } else {
        throw std::invalid_argument("Tipo de frontera no válido. Use 'periodic' o 'absorbing'.");
    }
}

void WavePropagator::avanzarEnElTiempo() {
    // Calcular los nuevos valores 
    for (int i = 1; i < numPuntos - 1; ++i) {
        campoE[i][1] = campoE[i][0] + BETA_FACTOR * (campoH[i - 1][0] - campoH[i + 1][0]);
        campoH[i][1] = campoH[i][0] + BETA_FACTOR * (campoE[i - 1][0] - campoE[i + 1][0]);
    }
    aplicarCondicionesDeBorde();

    // Filtro de promedio para suprimir la inestabilidad
    std::vector<double> campoE_suavizado(numPuntos);
    std::vector<double> campoH_suavizado(numPuntos);

    // Aplicar filtro a los puntos interiores
    for (int i = 1; i < numPuntos - 1; ++i) {
        // Promedio simple de 3 puntos para suavizar el ruido
        campoE_suavizado[i] = (campoE[i - 1][1] + campoE[i][1] + campoE[i + 1][1]) / 3.0;
        campoH_suavizado[i] = (campoH[i - 1][1] + campoH[i][1] + campoH[i + 1][1]) / 3.0;
    }
    
    // Para los bordes, simplemente copiamos el valor sin filtrar 
    campoE_suavizado[0] = campoE[0][1];
    campoE_suavizado[numPuntos - 1] = campoE[numPuntos - 1][1];
    campoH_suavizado[0] = campoH[0][1];
    campoH_suavizado[numPuntos - 1] = campoH[numPuntos - 1][1];

    // Copiar los valores FILTRADOS para el siguiente paso de tiempo
    for (int i = 0; i < numPuntos; ++i) {
        campoE[i][0] = campoE_suavizado[i];
        campoH[i][0] = campoH_suavizado[i];
    }
}

void WavePropagator::aplicarCondicionesDeBorde() {
    if (tipoDeCondicionDeBorde == "periodic") {
        // Usamos las condiciones de frontera periódicas 
        campoE[0][1] = campoE[0][0] + BETA_FACTOR * (campoH[numPuntos - 1][0] - campoH[1][0]);
        campoE[numPuntos - 1][1] = campoE[numPuntos - 1][0] + BETA_FACTOR * (campoH[numPuntos - 2][0] - campoH[0][0]);
        campoH[0][1] = campoH[0][0] + BETA_FACTOR * (campoE[numPuntos - 1][0] - campoE[1][0]);
        campoH[numPuntos - 1][1] = campoH[numPuntos - 1][0] + BETA_FACTOR * (campoE[numPuntos - 2][0] - campoE[0][0]);
    } else { // absorbing
        campoE[0][1] = 0.0;
        campoH[0][1] = 0.0;
        campoE[numPuntos - 1][1] = 0.0;
        campoH[numPuntos - 1][1] = 0.0;
    }
}

void WavePropagator::guardarDatos(std::ofstream& flujoDeArchivo) {
    for (int i = 0; i < numPuntos; ++i) {
        flujoDeArchivo << campoE[i][0] << (i == numPuntos - 1 ? "" : " ");
    }
    flujoDeArchivo << "\n";
}

void WavePropagator::iniciarSimulacion(int pasosTemporales, int intervaloDeGuardado, const std::string& archivoDeSalida) {
    std::ofstream archivo_resultados(archivoDeSalida);
    for (int paso = 0; paso < pasosTemporales; ++paso) {
        avanzarEnElTiempo();
        if (paso % intervaloDeGuardado == 0) {
            guardarDatos(archivo_resultados);
        }
    }
    archivo_resultados.close();
    std::cout << "Simulación para '" << archivoDeSalida << "' completada." << std::endl;
}
