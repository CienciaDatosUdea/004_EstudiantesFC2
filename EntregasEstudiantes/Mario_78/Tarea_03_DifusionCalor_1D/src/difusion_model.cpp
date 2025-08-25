#include <cstdio>
#include <iostream>
#include "flow.h" 

Geometria::Geometria(int N_,double xmin_, double xmax_ )
    : N(N_), xmin(xmin_), xmax(xmax_)
    {
        x.resize(N);
        dx = (xmax-xmin)/(N-1);
        for(int i=0;i<N;i++){
            x[i]=xmin+i*dx;
        }
};

Condiciones::Condiciones(Geometria &G_):
    G(G_), u(G_.N, 0.0) {
        // Valores físicos 
        double k = 1.0;
        double c = 10.0;
        double p = 30.0;
        double dt = 0.01;

        alpha = (k * dt) / (c * p * (G.dx * G.dx));   // alpha < 0.5 para garantizar estabilidad
    }

void  Condiciones::condicionesIniciales(){
    for(int i=1; i<G.N-1;i++){
        u[i]=0;
        if(i==int(G.N/2))
            u[i]=100;
    }
}

void  Condiciones::condicionesFrontera(){
    u[0]=0;
    u[G.N-1]=0;
}

void Condiciones::evolucionar(int pasosTiempo) {
    
    std::vector<double> u_nueva(G.N, 0.0);
    Flow flujo("resultados.txt");    // Creamos el manejador para guardar datos

    for (int t = 0; t < pasosTiempo; ++t) {
        // Guardar en archivo
        flujo.guardarPaso(t, G, u);

        // Mostrar en consola
        std::cout << "Paso " << t << ":\n";
        std::cout << "x\tTemperatura\n";
        for (int i = 0; i < G.N; ++i)
            std::cout << G.x[i] << "\t" << u[i] << "\n";
        std::cout << "-------------------------\n";

        // Diferencias finitas
        for (int i = 1; i < G.N - 1; ++i) {
            u_nueva[i] = alpha * (u[i + 1] + u[i - 1] - 2 * u[i]) + u[i];
        }

        u = u_nueva;
        condicionesFrontera();
    }
}
