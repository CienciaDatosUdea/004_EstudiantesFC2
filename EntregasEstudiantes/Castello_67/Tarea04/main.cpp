#include "flow.h"
#include <iostream>

int main(){ 
    // --- PARÁMETROS AJUSTADOS PARA RAPIDEZ ---
    int nx = 41; 
    int ny = 21; 
    int nit = 50; 
    int nt = 5000; 
    double dt = 0.001; 
    
    char filename[64];
    double xmin=0, xmax=2;
    double ymin=0, ymax=1;
    double rho=1.;
    
    Grid G(xmin, xmax, ymin, ymax, nx, ny);        
    CampoVelocidadesPresion Campo(G);
    ComputePresion presion(Campo, rho, dt, nit);
    ComputeCampo omega(presion);        
    Campo.CondicionesIniciales();
    
    std::cout << "Iniciando simulacion rapida..." << std::endl;
    
    // --- BUCLE PRINCIPAL ---
    for (int i = 0; i < nt; ++i) {
        
        // Indicador de progreso.
        if (i % 250 == 0) {
            std::cout << "Procesando paso: " << i << " de " << nt << std::endl;
        }

        Campo.BoundaryCondition();
        presion.presionUpdate();        
        omega.velocidadesUpdate();    
        
        // Condición de guardado para tener archivos rápidamente.
        if (i % 100 == 0 && i > 0) {
            std::snprintf(filename, sizeof(filename), "data/canal_flow_%04d.txt", i);        
            FieldWriter writer(filename);
            writer.writePosicionCampo(G, Campo);
        }
    }

    std::cout << "\nSimulacion terminada. Archivos guardados en la carpeta 'data'." << std::endl;
    return 0;
}