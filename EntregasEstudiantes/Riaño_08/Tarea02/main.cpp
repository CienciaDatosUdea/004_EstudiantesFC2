#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <string>
#include <filesystem>
#include "difusion_model.h"

namespace fs = std::filesystem;

// Función para guardar los resultados en un archivo de texto
void exportarResultados(const std::vector<double>& x, const std::vector<double>& u, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo para exportar los resultados.");
    }
    file << "# x\t u" << std::endl;
    for (size_t i = 0; i < x.size(); ++i) {
        file << x[i] << "\t" << u[i] << std::endl;
    }
    file.close();
}

int main() {
    // Parámetros del sistema
    int N = 100;         // Número de nodos
    double xmin = 0.0;     // Límite izquierdo
    double xmax = 10.0;    // Límite derecho
    double D = 0.1;        // Coeficiente de difusión
    double dt = 0.01;      // Paso de tiempo
    double t_max = 100.0;    // Tiempo máximo de simulación
    double TL = 0.0;       // Temperatura en la frontera izquierda
    double TR = 0.0;       // Temperatura en la frontera derecha

    try {
        // Crear las instancias de las clases
        Geometria G(N, xmin, xmax);
        Condiciones C(G);
        
        // Parámetros para la evolución temporal
        double alpha = D * dt / (G.dx * G.dx);
        int Nsteps = static_cast<int>(t_max / dt);
        
        if (alpha > 0.5 + EPSILON) {
            std::cerr << "ADVERTENCIA: La condición de estabilidad no se cumple (alpha > 0.5)." << std::endl;
            std::cerr << "Alpha = " << alpha << ". Se recomienda disminuir dt o D, o aumentar dx." << std::endl;
            return 1;
        }

        // Crear la nueva subcarpeta para los datos si no existe
        fs::create_directories("display/datos");

        // Aplicar condiciones iniciales y de frontera
        C.condicionesIniciales();
        C.condicionesFrontera(TL, TR);

        // Guardar el estado inicial
        exportarResultados(G.x, C.u, "display/datos/datos_paso_0.txt");

        // Copia del vector u para los cálculos
        std::vector<double> u_n = C.u;

        // Ciclo de evolución temporal y guardado de datos
        for (int n = 0; n < Nsteps; ++n) {
            // Recorrer los nodos internos para el cálculo FTCS
            for (int i = 1; i < G.N - 1; ++i) {
                C.u[i] = u_n[i] + alpha * (u_n[i + 1] - 2 * u_n[i] + u_n[i - 1]);
            }
            
            // Re-aplicar condiciones de frontera en cada paso
            C.condicionesFrontera(TL, TR);
            
            // Actualizar el vector u_n para el siguiente paso de tiempo
            u_n = C.u;
            
            // Guardar el estado actual
            exportarResultados(G.x, C.u, "display/datos/datos_paso_" + std::to_string(n + 1) + ".txt");
        }

        std::cout << "Simulación completada y resultados guardados en display/datos/" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}