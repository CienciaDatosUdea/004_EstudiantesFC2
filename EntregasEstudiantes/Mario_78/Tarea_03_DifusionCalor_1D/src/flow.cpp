#include "flow.h"
#include <fstream>
#include <filesystem> // Requiere C++17
#include <stdexcept>

Flow::Flow(const std::string &nombreArchivo) {
    // Crear carpeta "datos" si no existe
    std::filesystem::create_directory("datos");
    rutaArchivo = "datos/" + nombreArchivo;

    // Limpiar contenido previo del archivo
    std::ofstream archivo(rutaArchivo, std::ios::trunc);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo crear el archivo de salida");
    }

     // Crear carpeta "graph" si no existe
    std::filesystem::create_directory("graph");

    // Crear archivo .ipynb vacío si no existe
    std::string rutaNotebook = "graph/graficar_difusion.ipynb";
    if (!std::filesystem::exists(rutaNotebook)) {
        std::ofstream nb(rutaNotebook);
        if (!nb.is_open()) {
            throw std::runtime_error("No se pudo crear el archivo graficar_difusion.ipynb");
        }
        nb << ""; // Archivo vacío
    }
}

void Flow::guardarPaso(int paso, const Geometria &G, const std::vector<double> &u) {
    std::ofstream archivo(rutaArchivo, std::ios::app); // Modo append
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para escribir");
    }

    archivo << "Paso " << paso << ":\n";
    archivo << "x\tTemperatura\n";
    for (int i = 0; i < G.N; i++) {
        archivo << G.x[i] << "\t" << u[i] << "\n";
    }
    archivo << "-------------------------\n";
}
