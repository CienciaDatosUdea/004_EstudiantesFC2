#include <iostream>
#include "fdtd.h"   

int main() {
    //Inicializamos los parámetros de la simulación
    int N = 200;        //número de nodos espaciales z=200
    double dz  = 0.2;   //espaciamiento espacial
    //double dt = 0.1;	//espaciamiento temporal 
    int steps  = 2000;   //pasos de tiempo para la simulación
    int saveEvery = 15;      //guardar cada 1 pasos
    double beta= 0.04;           //Preservando la condicion de estabilidad de Courant

    ComputeFields simulacion(N, dz, beta);
    //Ejecutar la simulación
    simulacion.run(steps, saveEvery);

    std::cout << "Simulación finalizada. \n Los archivos de texto fueron guardados correctamente." << std::endl;
    return 0;
}

