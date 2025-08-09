
//Los archivos de la carpeta Test permiten automatizar el testeo del código

#include <cstdio>
#include <iostream>
#include "difusion_model.h"


int main(){
    //Definir los parámetros de la malla 
    int N=10;
    double xmin=0;
    double xmax=1;   
    
    Geometria G(N, xmin, xmax); //Crear la instancia de la clase con los valores definidos
     
    // Historia 8: Pruebas de testeo sobre la construcción de la malla  
    for(int i=0;i<N;i++){
        std::cout<<G.x[i]<<"\n";  //Imprimir valores de x
    }
    std::cout<<"-----";
    std::cout<<G.dx<<"\n"; //Imprimir el valor de espaciamiento de la malla
    std::cout<<G.N<<"\n";  //Imprimir el número total de nodos 
    std::cout<<G.x.size()<<"\n"; //Imprimir el tamaño de x (igual a N)
    
    // Historia 9: Prueba de condiciones inicial
    Condiciones Condiciones(G);
    Condiciones.condicionesIniciales();
    for(int i=0;i<N;i++){
        std::cout<<"Valores de la temperatura con las condiciones iniciales gaussianas en i="<<i<<"es: " <<Condiciones.u[i]<<"\n"; // Imprimir valores de la temperatura
    }

   // Historia 10: Verificación de condiciones de frontera
    Condiciones.condicionesFronteraDirichlet();
    std::cout<<"Condiciones de Dirichlet: u[0] = "<<Condiciones.u[0]<<"  u[N-1] = "<<Condiciones.u[N-1]<<"\n";
    Condiciones.condicionesIniciales(); // reiniciar
    Condiciones.condicionesFronteraNeumann();
    std::cout<<"Condiciones de Neumann: u[0] = "<<Condiciones.u[0]<<"  u[N-1] = "<<Condiciones.u[N-1]<<"\n";
    
    
    // Historia 11: Validación numérica básica
    double D = 0.1;
    double dt = 0.02;
    double t_max = 0.005;
    DiffusionSolver solver(Condiciones, D, dt, t_max); //correr el diffusionsolver
    solver.run();
    for(int i=0;i<N;i++){
        std::cout<<Condiciones.u[i]<<"\n"; // Imprimir valores después de la evolución
    }


    return 0;
}
