#include "fdtd.h"
#include <iostream>
#include <cstdlib>



/**
 * @brief Función principal para simulación de ondas electromagnéticas con FDTD
 * @param argc Número de argumentos de línea de comandos
 * @param argv Argumentos de línea de comandos
 */
int main(int argc, char* argv[]) {
    try {
        // Parámetros de la simulación
        int puntos_espaciales = 200;    // Número de puntos en el espacio
        int pasos_temporales = 500;     // Número de pasos de tiempo
        double dz = 0.1;                // Paso espacial [m]
        double dt = 0.05;               // Paso temporal [s]
        
        // Tipo de frontera por defecto
        TipoFrontera tipo_frontera = ABIERTAS;
        
        // Parsear argumentos de línea de comandos
        if (argc > 1) {
            std::string arg = argv[1];
            if (arg == "dirichlet") {
                tipo_frontera = DIRICHLET;
                std::cout << "Usando condiciones de Dirichlet\n";
            }
            else if (arg == "periodicas") {
                tipo_frontera = PERIODICAS;
                std::cout << "Usando condiciones periódicas\n";
            }
            else if (arg == "absorbentes") {
                tipo_frontera = ABSORBENTES;
                std::cout << "Usando condiciones absorbentes\n";
            }
            else if (arg == "abiertas") {
                tipo_frontera = ABIERTAS;
                std::cout << "Usando condiciones abiertas\n";
            }
        }
        
        std::cout << "=== SIMULACIÓN DE ONDAS ELECTROMAGNÉTICAS CON FDTD ===\n";
        std::cout << "Puntos espaciales: " << puntos_espaciales << "\n";
        std::cout << "Pasos temporales: " << pasos_temporales << "\n";
        std::cout << "dz = " << dz << " m, dt = " << dt << " s\n";
        std::cout << "beta = " << dt/dz << "\n";
        
        // Crear geometría
        Geometria geo(puntos_espaciales, pasos_temporales, dz, dt);
        
        // Crear campos con el tipo de frontera seleccionado
        Campos campos(geo, tipo_frontera);
        
        std::cout << "\n=== EVOLUCIÓN TEMPORAL ===\n";
        
        // Evolucionar los campos
        campos.evolucion();
        
        std::cout << "Evolución completada\n";
        
        // Guardar resultados
        Datos datos(campos);
        
        // Generar nombre de archivo basado en el tipo de frontera
        std::string filename;
        switch(tipo_frontera) {
            case DIRICHLET: filename = "resultados_dirichlet.txt"; break;
            case PERIODICAS: filename = "resultados_periodicas.txt"; break;
            case ABSORBENTES: filename = "resultados_absorbentes.txt"; break;
            case ABIERTAS: filename = "resultados_abiertas.txt"; break;
        }
        
        datos.guardar_txt(filename);
        std::cout << "Resultados guardados en: " << filename << "\n";
        
        
        
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}







