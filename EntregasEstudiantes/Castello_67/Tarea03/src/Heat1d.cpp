#include<iostream>
#include<cmath>
#include<vector>
#include "../include/Heat1d.h"

// Implementacion ----------------------------------------------------------------------------------------------------------------------------
Heat1d::Heat1d(double alpha , int N , double L , double U0_x0 , double U0_xf ): //constructor constante
alpha(alpha),
N(N), 
L(L), 
h(L/N), 
U0_x0(U0_x0), 
U0_xf(U0_xf), 
Sol(N,0)
{
    // Poner condiciones de frontera
    Sol[0] = U0_x0;
    Sol[N - 1] = U0_xf;
}
Heat1d::Heat1d(double alpha , int N , double L , double Max_U , double sigma ,  bool gaussian): //constructor gaussiano (polimorfismo)
alpha(alpha),
N(N), 
L(L), 
h(L/N),
U0_x0(0.),
U0_xf(0.),
Sol(N , 0) 
{
    std::cout << "Inicializacion Gaussiana:" << gaussian << std::endl;
    // Poner condiciones gaussianas
    double middle_point = L/2.;
    for(int i = 0 ; i < N ; i++){
        double x_i = i*h;
        this->Sol[i] = Max_U * pow(M_E , - 0.5 * (x_i - middle_point) * (x_i - middle_point) /(sigma * sigma) ); 
    }
}
void Heat1d::Integrate(double t_f , const std::string &filename){
    
    // Limpiar el archivo antes de empezar
    std::ofstream clear_file(filename, std::ios::trunc);
    clear_file.close();

    double dt = h*h/(2*alpha);
    std::cout << "Comenzando Integrador: -----------------------------------" << std::endl;
    std::cout << "Valor del paso del tiempo dt = " << dt << std::endl;
    double r = alpha * dt /(h*h);
    int N_steps = t_f/dt;

    if (r > 0.5){
        std::cout << "El metodo no es estable numericamente! " << std::endl;
        exit(1);
    }

    //std::cout << "solucion en t = 0" << std::endl;
    //    print_sol();

    for (int j = 1 ; j <= N_steps ; j++){
        double t = j *dt;
        for (int i = 1 ; i < N -1  ; i++){
            Sol[i] = r*Sol[i+1] + (1 - 2*r)*Sol[i] + r*Sol[i-1];
        }
        //std::cout << "solucion en t = " << t << std::endl;
        //print_sol();
        save_sol(filename);
    }  
    
}
void Heat1d::print_sol(){
    for (int i = 0 ; i < N ; i++){
            std::cout << Sol[i] << " ";
        }
    std::cout << std:: endl;
}
void Heat1d::save_sol(const std::string &filename){
    std::ofstream file;
    file.open(filename, std::ios::app);
    if (file.is_open()){
        for (int i = 0 ; i < N ; i++){
            file << Sol[i] << " ";
        }
        file << std::endl;
    } else {
        std::cout << "No se pudo abrir el archivo " << filename << " para escribir." << std::endl;
    } 
} 