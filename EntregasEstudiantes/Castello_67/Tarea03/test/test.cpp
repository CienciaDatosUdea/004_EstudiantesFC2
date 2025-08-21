#include<iostream>
#include<cmath>
#include<vector>
#include "../include/Heat1d.h"

// Main -------------------------------------------------------------------------------------------------------------------------------------
int main(){
    double alpha , N , L , U0_x0  , U0_xf , t_f;
    std::cout << "Ingrese la constante de difusion alpha: " << std::endl ; std::cin >> alpha;
    std::cout << "Ingrese la cantidad de puntos N en la barra : " << std::endl ; std::cin >> N;
    std::cout << "Ingrese la longitud de la barra : " << std::endl ; std::cin >> L;
    std::cout << "Ingrese la temperatura inicial en el extremo izquierdo : " << std::endl ; std::cin >> U0_x0;
    std::cout << "Ingrese la temperatura inicial en el extremo derecho : " << std::endl ; std::cin >> U0_xf;
    std::cout << "Ingrese el tiempo de integracion final" << std::endl ; std::cin >> t_f;
     
    Heat1d MyHeat(alpha,N,L,U0_x0,U0_xf );
    MyHeat.Integrate(t_f , "test.txt");
    return 0;
}