#include <cmath>
#include <vector>
#include <ostream>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "../include/fdtd.h"

double c = 1.;

// Funciones de apoyo  --------------------------------------------------------------------------------------
void print_vector(const std::vector<double>& vec) {
    for (const auto& val : vec) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}
void sentofile(const std::string &filename,
               const std::vector<std::vector<double>> &E,
               const std::vector<std::vector<double>> &H,
               int Num_nodes, double Delta,
               int step, double t)
{
    if (filename.empty()) return; // no imprime nada
    static bool first_time = true;
    std::ofstream ofs(filename, std::ios::app);
    if (!ofs.is_open()) {
        std::cerr << "Error: no se pudo abrir " << filename << std::endl;
        return;
    }
    if (first_time) {
        ofs << "step,t,k,x,E,H\n";
        first_time = false;
    }
    ofs << std::fixed << std::setprecision(6);
    for (int k = 0; k < Num_nodes; ++k) {
        double x = k * Delta;
        ofs << step << "," << t << "," << k << "," << x << ","
            << E[0][k] << "," << H[0][k] << "\n"; 
    }
}
// Clases --------------------------------------------------------------------------------------
Linspace::Linspace(double l0 , double lf, int Num_nodes): 
l0(l0) , lf(lf) , Num_nodes(Num_nodes) , Delta((lf - l0) / (Num_nodes - 1)) , pos(std::vector<double>(Num_nodes))
{
    for(int i = 0  ; i < Num_nodes  ; i++){ 
        pos[i] = i * Delta + l0;
    }
}
Linspace::Linspace(double l0 , double lf, double Delta): 
l0(l0) , lf(lf) , Num_nodes(1 + (lf - l0)/Delta), Delta(Delta) ,  pos(std::vector<double>(Num_nodes))
{
    for(int i = 0  ; i < Num_nodes  ; i++){ 
        pos[i] = i * Delta + l0;
    }

}
void Linspace::print(){
    print_vector(pos);
    std::cout << std::endl;
}

//---------------------------------------------------------------------------------------------------------------------------------------------

Lee_Net::Lee_Net(int Num_nodes , double E0 , double H0 ):
Num_nodes(Num_nodes), Delta(1./(Num_nodes - 1.))
{
    E = std::vector<std::vector<double>>(2, std::vector<double>(Num_nodes, E0));
    H = std::vector<std::vector<double>>(2, std::vector<double>(Num_nodes, H0));

    /*for (int i = 0; i < Num_nodes; ++i){ // Inicializa la primera fila
        E[0][i] = E0;
        H[0][i] = H0;
    }*/
}
void Lee_Net::Integrate(double Integration_time, double DeltaT , const std::string &boundary_cond, const std::string &filename ,const bool test){
    //Estabilidad numerica 
    std::cout << "Integrating with DeltaT = " << DeltaT << " and Delta = " << Delta << std::endl;
    double beta = c * DeltaT / Delta;
    if (beta > 0.5){
        std::cout << "Warning: beta = " << beta << " is more than 0.5, which may lead to numerical instability." << std::endl;
    }

    // Minimo numero de puntos
    if (Num_nodes < 3) {
        std::cerr << "Error: Num_nodes must be >= 3. Current Num_nodes = " << Num_nodes << std::endl;
        return;
    }

    int step = 0;
    double t = 0.0;

    // Escribir condición inicial (t=0)
    sentofile(filename, E, H, Num_nodes, Delta, step, t);
    step++;

    // Bucle principal de Integracion temporal: 
    for (double t = 0.; t <= Integration_time + DeltaT; t += DeltaT){

        // Primero campo electrico
        for (int k = 1; k <= Num_nodes - 2; ++k) {
            //E[k][1] = E[k][0] + beta * ( H[k-1][0] - H[k+1][0] )
            E[1][k] = E[0][k] + beta * ( H[0][k-1] - H[0][k+1] );
        }
        // Condiciones periodicas campo electrico
        if (boundary_cond == "periodic") {
            E[1][0] = E[0][0] + beta * ( H[0][Num_nodes - 1] - H[0][1] );
            E[1][Num_nodes - 1] = E[0][Num_nodes - 1] + beta * ( H[0][Num_nodes - 2] - H[0][0] );
        }
        // Condiciones de frontera simples para el campo electrico
        else if (boundary_cond == "simple"){
            E[1][0] = 0.0;
            E[1][Num_nodes - 1] = 0.0;
        }
        // Segundo campo magnetico
        for (int k = 1; k <= Num_nodes - 2; ++k) {
            // H[k][1] = H[k][0] + beta * ( E[k-1][1] - E[k+1][1] )
            H[1][k] = H[0][k] + beta * ( E[1][k-1] - E[1][k+1] );
        }
        // Condiciones periodicas campo magnetico
        if (boundary_cond == "periodic") {
            H[1][0] = H[0][0] + beta * ( E[1][Num_nodes - 1] - E[1][1] );
            H[1][Num_nodes - 1] = H[0][Num_nodes - 1] + beta * ( E[1][Num_nodes - 2] - E[1][0] );
        }
        // Condiciones de frontera simples para el campo magnetico
        else if (boundary_cond == "simple"){
            H[1][0] = 0.0;
            H[1][Num_nodes - 1] = 0.0;
        }

        // Intercambia los punteros para la siguiente iteracion
        std::swap(E[0], E[1]); 
        std::swap(H[0], H[1]);

        sentofile(filename, E, H, Num_nodes, Delta, step, t);

        // Imprime los resultados en cada paso de tiempo si test es true
        if(test){ 
        std::cout << "t=" << t << std::endl;
        std::cout << "E: "; print_vector(E[0]); 
        std::cout << "H: "; print_vector(H[0]);
        std::cout << std::endl;
        }

        step++;
    } // fin loop temporal

    // fin Integrate
}

 