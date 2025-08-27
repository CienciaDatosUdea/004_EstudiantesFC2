#include <iostream>
#include<cmath>
#include<random>
#include <ctime>
using namespace std;

const int N = 10;         // Número de partículas
const double R = 1.0;     // Radio de la circunferencia
const double DELTA = 0.1; // Rango de perturbación aleatoria

mt19937_64& global_rng() {
    static mt19937_64 rng{ 0 /*semilla*/ };
    return rng;
}


double random_number(double a, double b) {
    uniform_real_distribution<double> dist(a, b); // Distribución uniforme en el rango [a, b]
    return dist(global_rng()); // Genera un número aleatorio en el rango [a, b]
}

struct particula{
    // Estructura que representa una partícula con coordenadas x e y
    double x;
    double y;
};

void init_configuracion(particula &p){
    // Inicializa la posición de la partícula en una circunferencia de radio R
    double theta;
    theta = random_number(0, 2*M_PI); // Genera un ángulo aleatorio entre 0 y 2π
    p.x = R*cos(theta);
    p.y = R*sin(theta); // Calcula las coordenadas x, y en la circunferencia de radio R
};

void update_posicion(particula &p, double dx, double dy){
    // Actualiza la posición de la partícula con un desplazamiento aleatorio
    // dx y dy son números aleatorios en el rango [-DELTA, DELTA] 
    p.x = p.x + dx;
    p.y = p.y + dy;
};

struct sistema{
    // Estructura que representa un sistema de partículas
    // Contiene un vector de partículas, el número de partículas y una fuerza neta
    int n = N; // Número de partículas
    vector<particula> p;
    double Fnet=0.0;
};

void init_all_particles(sistema &s){
    s.p.resize(s.n); // Redimensiona el vector de partículas a N
    for(auto &v:s.p){
        // Inicializa cada partícula en una posición aleatoria dentro de la circunferencia
        // y luego la actualiza con un desplazamiento aleatorio
        init_configuracion(v); 
        update_posicion(v, random_number(-DELTA, DELTA), random_number(-DELTA, DELTA));
    }
}

void distancia_minima(sistema &s){
    double D=10.0; // Inicializa D con un valor grande para encontrar la distancia mínima
    double dx, dy, dij; // Variables para calcular la distancia entre partículas
    for(int i=0; i<s.n; i++){ // Recorre todas las partículas
        for(int j=i+1; j<s.n; j++){ // Inicia el bucle desde i+1 para evitar comparar la misma partícula
            dx = (s.p)[i].x-(s.p)[j].x;
            dy = (s.p)[i].y-(s.p)[j].y;
            dij = sqrt(dx*dx+dy*dy); // Calcula la distancia entre las partículas i y j
            if(dij<D){
                D = dij; // Si la distancia calculada es menor que D, actualiza D
            }
        }
    }
    cout<<"Distancia mínima: "<<D<<" m"<<endl;
}

void fuerzas(sistema &s){
    // Asigna aleatoriamente fuerzas entre [0 y 1] sobre cada partícula, 
    // y calcula la fuerza neta sobre el sistema de partículas
    double fx, fy; // Fuerzas en x e y
    for(int i=0; i<N; i++){
        fx = random_number(0, 1); // Genera una fuerza aleatoria en x
        fy = random_number(0, 1); // Genera una fuerza aleatoria en y
        s.Fnet += sqrt(fx*fx + fy*fy); // Calcula la magnitud de la fuerza y la suma a la fuerza neta
    }
    cout<<"Fuerza neta: "<<s.Fnet<<" N"<<endl; // Imprime la fuerza neta total del sistema
}

int main(){

    sistema s;

    init_all_particles(s);
    distancia_minima(s);
    fuerzas(s);

    return 0;
}