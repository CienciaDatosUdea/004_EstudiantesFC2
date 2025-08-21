#include <iostream>
#include "fdtd.h"   

int main() {
    //Inicializamos los parámetros de la simulación
    int N = 200;        //número de nodos espaciales z=200
    double dz  = 1;   //espaciamiento espacial
    double dt = 0.2;	//espaciamiento temporal 
    int steps  = 200;   //pasos de tiempo para la simulación
    int saveEvery = 10;      //guardar cada 10 pasos
    double beta= 0.01;           //Preservando la condicion de estabilidad de Courant

    ComputeFields simulacion(N, dz, beta);
    //Ejecutar la simulación
    simulacion.run(steps, saveEvery);

    std::cout << "Simulación finalizada. \n Los archivos de texto fueron guardados correctamente." << std::endl;
    return 0;
}

