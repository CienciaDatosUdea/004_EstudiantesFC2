

#include "campo_velocidades.h"
#include <iostream>





int main() {
    // Crear malla 
    Grid malla(0.0, 2, 0.0, 2,51, 51);  // Domini
    
    // Elegir tipo de problema y fuerza
    ProblemType problema = ProblemType::CAVITY_FLOW;
    ForceType fuerza = ForceType::NONE;
    
    // Crear condiciones con configuración elegida
    Condiciones campo(malla, problema, fuerza);
    campo.CondicionesIniciales();
    campo.CondicionesFrontera();
    
    // PARÁMETROS CRÍTICOS - AJUSTAR ESTOS:
    double rho = 1.0;
    //double nu = 0.01;           // Viscosidad 
    double dt = 0.001;          // Paso de tiempo más grande (10x)
    int nit = 100;             // iteraciones para presión
    int nt = 1000;             //pasos de tiempo
    
     // Crear objetos para cálculo
    Presion presion(campo, rho, dt, nit);
    Velocidades velocidades(presion);
    EscribirCampo escritor("Cavityflow.txt");
    
    for(int n=0; n<nt; n++) {
        presion.calcularPresion();
        velocidades.calcularVelocidades();
        
        if(n % 100 == 0) {     // Guardar cada 100 pasos
            escritor.PosicionCampo(malla, campo, n*dt);
            std::cout << "Paso: " << n << ", Tiempo: " << n*dt << std::endl;
                 
        }
    }
    
    return 0;
}

