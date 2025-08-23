#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "fdtd.h"

// Implementación de Geometria
Geometria::Geometria(int K_, int N_, double dz_, double dt_):K(K_),N(N_),dz(dz_),dt(dt_){}

// Implementación de Campos
Campos::Campos(Geometria const & G_, TipoFrontera tipo):G(G_), tipoFrontera(tipo){
    // Inicializar los vectores primero
    E.resize(G.N, std::vector<double>(G.K, 0.0));
    H.resize(G.N, std::vector<double>(G.K, 0.0));
    
    condiciones_iniciales();

    beta = G.dt/G.dz;
    if(beta >= 1.0){
        std::cout << "ADVERTENCIA: beta = " << beta << " >= 1.0, la simulación será inestable\n";
    }
    else if(beta >= 0.5){
        std::cout << "ADVERTENCIA: beta = " << beta << " >= 0.5, puede haber inestabilidad\n";
    }
}




void Campos::evolucion(){
    for(int n =1; n < G.N; n++){
        // Evolucionar campo H
        for(int k = 1; k < G.K - 1; k++){
            H[n][k] = H[n-1][k] + beta * (E[n-1][k] - E[n-1][k+1]);
        }
        
        // Evolucionar campo E
        for(int k = 1; k < G.K - 1; k++){
            E[n][k] = E[n-1][k] + beta * (H[n][k-1] - H[n][k]);
        }
        
        // Aplicar condiciones de frontera nuevamente
        aplicar_fronteras(n);
    }
}




void Campos::condiciones_iniciales(){
     //Pulso gaussiano como condición inicial
    double centro = G.K / 2.0;
    double ancho = G.K / 10.0;
    
    for(int k = 0; k < G.K; k++){
        double x = (k - centro) / ancho;
        E[0][k] = exp(-x * x);
        H[0][k] = 0.0;
    }


    //for(int k= 0;k<G.K;k++){
     //   E[0][k] = 0.1*sin(2*M_PI*k/100.0);
      //  H[0][k] = 0.1*sin(2*M_PI*k/100.0);
    //}
}


/*
void Campos::condiciones_iniciales() {
    double amplitud = 0.1;
    double lambda = 100.0;        // Longitud de onda
    double k_onda = 2*M_PI/lambda;
    
    for(int k = 0; k < G.K; k++) {
        
        E[0][k] = amplitud * sin(k_onda * k);
        H[0][k] = (amplitud / 377.0) * sin(k_onda * k);  // E = Z₀ * H
    }
}

*/


void Campos::aplicar_fronteras(int n){
    switch(tipoFrontera){
        case DIRICHLET:
            fronteras_dirichlet(n);
            break;
        case PERIODICAS:
            fronteras_periodicas(n);
            break;
        case ABSORBENTES:
            fronteras_absorbentes(n);
            break;
        case ABIERTAS:
            fronteras_abiertas(n);
            break;
    }
}

void Campos::fronteras_dirichlet(int n){
    // 0 en fronteras
    E[n][0] = 0.0;
    E[n][G.K-1] = 0.0;
    
    // Para H: condiciones naturales (derivada normal cero)
    H[n][0] = H[n][1];
    H[n][G.K-1] = H[n][G.K-2];
}




void Campos::fronteras_periodicas(int n){
    // Ambos campos son periódicos
    E[n][0] = E[n][G.K-2];
    E[n][G.K-1] = E[n][1];
    H[n][0] = H[n][G.K-2];
    H[n][G.K-1] = H[n][1];
}



/*

void Campos::fronteras_periodicas(int n) {
    // Condiciones periódicas COMPLETAS para FDTD
    
    // Campo eléctrico - condiciones periódicas
    E[n][0] = E[n][G.K-2];    // Primer punto = penúltimo punto
    E[n][G.K-1] = E[n][1];    // Último punto = segundo punto
    
    // Campo magnético - condiciones periódicas  
    H[n][0] = H[n][G.K-2];    // Primer punto = penúltimo punto
    H[n][G.K-1] = H[n][1];    // Último punto = segundo punto
    
    // Actualización adicional para consistencia FDTD
    if (n > 0) {
        H[n][G.K-1] = H[n-1][G.K-1] + beta * (E[n-1][G.K-2] - E[n-1][0]);
        E[n][0] = E[n-1][0] + beta * (H[n][G.K-1] - H[n][1]);
    }
}
*/
void Campos::fronteras_absorbentes(int n){
    // ABC de primer orden para ambos campos
    if(n > 1){
        // Frontera derecha
        double factor = (beta - 1.0) / (beta + 1.0);
        E[n][G.K-1] = E[n-2][G.K-2] + factor * (E[n][G.K-2] - E[n-1][G.K-1]);
        H[n][G.K-1] = H[n-2][G.K-2] + factor * (H[n][G.K-2] - H[n-1][G.K-1]);
        
        // Frontera izquierda
        E[n][0] = E[n-2][1] + factor * (E[n][1] - E[n-1][0]);
        H[n][0] = H[n-2][1] + factor * (H[n][1] - H[n-1][0]);
    }
}

void Campos::fronteras_abiertas(int n){
    // Condiciones abiertas (derivada cero) para ambos campos
    E[n][0] = E[n][1];
    E[n][G.K-1] = E[n][G.K-2];
    H[n][0] = H[n][1];
    H[n][G.K-1] = H[n][G.K-2];
}

void Campos::set_tipo_frontera(TipoFrontera nuevo_tipo){
    tipoFrontera = nuevo_tipo;
}

// Implementación de Datos (sin cambios)
Datos::Datos(Campos const & C_):C(C_){}

void Datos::guardar_txt(std::string filename){
    file.open(filename);
    
    if (!file.is_open()) 
        throw std::runtime_error("No se pudo abrir el archivo: " + filename);
    
    file << "Campo_Electrico:\n";
    for(int n = 0; n < C.G.N; n++){
        for(int k = 0; k < C.G.K; k++){
            file << C.E[n][k] << " ";
        }
        file << "\n";
    }
    
    file << "---\n";
    
    file << "Campo_Magnetico:\n";
    for(int n = 0; n < C.G.N; n++){
        for(int k = 0; k < C.G.K; k++){
            file << C.H[n][k] << " ";
        }
        file << "\n";
    }
    
    file.close();
}

void Datos::imprimir(){
    std::cout << "Campo Electrico (ultimo paso temporal):\n";
    for(int k = 0; k < C.G.K; k++){
        std::cout << C.E[C.G.N-1][k] << " ";
    }
    std::cout << "\n\n";
    
    std::cout << "Campo Magnetico (ultimo paso temporal):\n";
    for(int k = 0; k < C.G.K; k++){
        std::cout << C.H[C.G.N-1][k] << " ";
    }
    std::cout << "\n";
}