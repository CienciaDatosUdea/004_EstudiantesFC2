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

class particula{
    private:
        double x;
        double y;
    public:
        particula(): x(0), y(0) {}; // Constructor por defecto que inicializa x, y en 0
        void init_configuracion(){
            double theta;
            theta = random_number(0, 2*M_PI); // Genera un ángulo aleatorio entre 0 y 2π
            x = R*cos(theta);
            y = R*sin(theta); // Calcula las coordenadas x, y en la circunferencia de radio R
        }
        void update_posicion(double dx, double dy){
            // Actualiza la posición de la partícula con un desplazamiento aleatorio
            // dx y dy son números aleatorios en el rango [-DELTA, DELTA] 
            x = x + dx;
            y = y + dy;
        }
        const double get_x(){return x;}; // Método para obtener la coordenada x de la partícula
        const double get_y(){return y;};
};

class sistema{
    private:
        vector<particula> p;
    public:
        sistema(int N):p(N){};  // Defino las dimensiones que debe tener p con este constructor
        void init_all_particles(){
            for(auto &v:p){
                // Inicializa cada partícula en una posición aleatoria dentro de la circunferencia
                // y luego la actualiza con un desplazamiento aleatorio
                v.init_configuracion(); 
                v.update_posicion( random_number(-DELTA, DELTA), random_number(-DELTA, DELTA) );
            }
        }

        void distancia_minima(){
            double D=10.0; // Inicializa D con un valor grande para encontrar la distancia mínima
            double dx, dy, dij; // Variables para calcular la distancia entre partículas
            for(int i=0; i<N; i++){ // Recorre todas las partículas
                for(int j=i+1; j<N; j++){ // Inicia el bucle desde i+1 para evitar comparar la misma partícula
                    dx = p[i].get_x()-p[j].get_x();
                    dy = p[i].get_y()-p[j].get_y();
                    dij = sqrt(dx*dx+dy*dy); // Calcula la distancia entre las partículas i y j
                    if(dij<D){
                        D = dij; // Si la distancia calculada es menor que D, actualiza D
                    }
                }
            }
            cout<<"Distancia mínima: "<<D<<" m"<<endl;
        }

        void fuerzas(){
            // Asigna aleatoriamente fuerzas entre [0 y 1] sobre cada partícula, 
            // y calcula la fuerza neta sobre el sistema de partículas
            double fx, fy; // Fuerzas en x e y
            double Fnet = 0.0; // Fuerza neta inicializada en 0
            for(int i=0; i<N; i++){
                fx = random_number(0, 1); // Genera una fuerza aleatoria en x
                fy = random_number(0, 1); // Genera una fuerza aleatoria en y
                Fnet += sqrt(fx*fx + fy*fy); // Calcula la magnitud de la fuerza y la suma a la fuerza neta
            }
            cout<<"Fuerza neta: "<<Fnet<<" N"<<endl; // Imprime la fuerza neta total del sistema
        }

};


int main(){

    sistema s(N);
    s.init_all_particles();
    s.distancia_minima();
    s.fuerzas();

    return 0;
}