#include "src/fdtd.cpp"
#include <iostream>

using namespace std;

int main() {

    // Parámetros de la simulación (Varibles normalizadas c= 1)
    int nz = 100;           // Número de puntos en z para Ex
    double z_max = 200.0;   // Longitud del dominio
    double dz = z_max / (nz - 1); // Espaciado espacial
    
    // Parámetros de tiempo
    double beta = 0.05;      // Parámetro de estabilidad (c*dt/dz)
    double dt = beta * dz;  // Paso temporal (c=1)
    int nt;          // Número de pasos temporales

    cout << "Ingrese el numero total de pasos temporales (nt): ";
    cin >> nt;
    
 
    //Parametros de la simulacion
    cout << "Parametros de la simulacion:" << endl;
    cout << "Paso espacial dz: " << dz << endl;
    cout << "Paso temporal dt: " << dt << endl;
    cout << "Beta: " << beta << endl;
    
    // Simulación con condiciones periódicas
    OndaEM ondaPeriodic(nz, dz, dt, nt, 0);
    ondaPeriodic.Inicialization();
    ondaPeriodic.update();
    ondaPeriodic.outputToFile("data/EM_periodic.txt");
    
    //Simulación con condiciones fijas

    OndaEM ondaFixed(nz, dz, dt, nt, 1);
    ondaFixed.Inicialization();
    ondaFixed.update();
    ondaFixed.outputToFile("data/EM_fixed.txt");
    cout <<" Simulaciones Yee completadas. Los resultados se guardaron en la carpeta data_yee/." <<endl;


    //Variacion del parametro beta
    for (double beta_var = 0.1; beta_var <= 0.9; beta_var += 0.1) {
        double dt_var = beta_var * dz;
        
        cout << "Simulacion con beta = " << beta_var << " y dt = " << dt_var << endl;
        OndaEM ondaperiodVar(nz, dz, dt_var, nt, 0);
        ondaperiodVar.Inicialization();
        ondaperiodVar.update();
        
        string filename = "data/EM_periodic_beta_" + to_string(static_cast<int>(round(beta_var * 100))) + ".txt";
        ondaperiodVar.outputToFile(filename);

        OndaEM ondaFixedVar(nz, dz, dt_var, nt, 1);
        ondaFixedVar.Inicialization();  
        ondaFixedVar.update();
        string filenameFixed = "data/EM_fixed_beta_" + to_string(static_cast<int>(round(beta_var * 100))) + ".txt";
        ondaFixedVar.outputToFile(filenameFixed);
    }
    return 0;
}