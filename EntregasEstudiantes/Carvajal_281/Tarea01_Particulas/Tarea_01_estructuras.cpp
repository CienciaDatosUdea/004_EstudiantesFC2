#include <iostream>
#include <cmath>
#include <random>
#include <ctime> // para time(NULL)

// g++ -std=c++17 -Wall programa.cpp -o programa.out

/*
Simulacion de particulas en una circunferencia

Diseñe un programa en C++ que simule un sistema de N partículas distribuidas aleatoriamente sobre una circunferencia (esfera en 2D) y que permita realizar las siguientes operaciones físicas: 

 - Genere N partículas distribuidas uniformemente sobre una circunferencia de radio 1, centrada en el origen
 - Generar una perturbacion para cada una de las particulas dx, dy aleatoria. 
 - Calcular la distancia maxima que hay  entre particulas
 - Suponga que las particulas tiene un vector de fuerza fx, fy, cada uno con valores aleatorios entre 0, 1
 - Cual es la magnitud de la fuerza resultadante del sistema de partículas
 - Implementar la solucion, empleando clases
*/


const int N = 10;

struct particula {
    double x, y;    // Posición
    double fx, fy;  // Fuerza
};

// 1- Función para inicializar partículas en un punto aleatorio sobre la circunferencia
void init_position(particula *p) {
    for (int i = 0; i < N; i++) {
        double theta = (double(rand()) / RAND_MAX) * 2.0 * M_PI;
        p[i].x = cos(theta);
        p[i].y = sin(theta);
    }}

// 2- Función para aplicar una perturbación a las partículas 
void perturbacion(particula *p) {
    for (int i = 0; i < N; i++) {
        double dx, dy;
        double delta = 0.1;
        dx = ((double)rand() / RAND_MAX) * 2 * delta - delta;
        dy = ((double)rand() / RAND_MAX) * 2 * delta - delta;
        p[i].x += dx;
        p[i].y += dy;
    }
}


// 3- Calcula la distancia máxima entre cualquier par de partículas luego de la perturbación
double calcular_distancia_maxima(particula *p) {
    double max_dist = 0;
    for (int i = 0; i < N; i++){
        for (int j = i + 1; j < N; j++) {
            double dx = p[i].x - p[j].x;
            double dy = p[i].y - p[j].y;
            //Formula de distancia 
            double dist = sqrt(dx * dx + dy * dy);
            if (dist > max_dist) max_dist = dist;
        }}
    return max_dist;
}

// 4- Función para asignar fuerzas aleatorias a cada partícula
void fuerzas(particula *p) {
    for (int i = 0; i < N; i++) {
        p[i].fx = (double)rand() / RAND_MAX;
        p[i].fy = (double)rand() / RAND_MAX;
    }
}


//5- Calculo de la fuerza total resultante
double calcular_fuerza_total(particula *p) {
    double fx_total = 0;
    double fy_total = 0;
    for (int i = 0; i < N; i++) {
        fx_total += p[i].fx;
        fy_total += p[i].fy;
    }
    return sqrt(fx_total * fx_total + fy_total * fy_total); //Modulo de la fuerza
}

int main() {
    particula p[N];
    srand(time(NULL)); //Inicializar semilla de rand 
    init_position(p);
    perturbacion(p);
    fuerzas(p);

    for (int i = 0; i < N; i++) {
        std::cout << "La partícula " << i << " en posición: (x,y)=(" << p[i].x << ", "<< p[i].y <<")"
                  << " Tiene una fuerza: (" << p[i].fx << ", " << p[i].fy << ") asociada \n";
    }

    double d_max = calcular_distancia_maxima(p);
    double f_total = calcular_fuerza_total(p);

    std::cout << "\nDistancia máxima entre partículas: " << d_max << "\n";
    std::cout << "Magnitud de la fuerza total: " << f_total << "\n";

    return 0;
}













