#include <iostream>
#include <cmath>
#include <random>
#include <ctime> //para time(NULL)
#include <vector>

//g++ -std=c++17 -Wall programa.cpp -o programa.out

/*
Simulacion de particulas en una circunferencia - aplicado en Clases
*/


const int N = 10;


//Clase para -UNA SOLA- partícula
class Particula {
public: 
    double x, y;    // Posición
    double fx, fy;  // Fuerza

    Particula() : x(0), y(0), fx(0), fy(0) {} //definimos el constructor inicializando todo en cero (estado base)

    //Inicializar partículas aleatoriamente sobre la circunferencia
    void init_position() {
        double theta = (double(rand()) / RAND_MAX) * 2.0 * M_PI;
        x = cos(theta);
        y = sin(theta);
    }

    //Implementar perturbación a las partículas 
    void perturbacion(double delta = 0.1) {
        double dx, dy;
        dx = ((double)rand() / RAND_MAX) * 2 * delta - delta;
        dy = ((double)rand() / RAND_MAX) * 2 * delta - delta;
        x+= dx;
        y+= dy;
    }

    //Función para asignar fuerzas aleatorias a cada partícula
    void fuerzas() {
        fx = (double)rand() / RAND_MAX;
        fy = (double)rand() / RAND_MAX;
    }};


class Sistema_total {
public:
    std::vector<Particula> particulas; //vector que almacena objetos de tipo particula

    Sistema_total(int n) {
        particulas.resize(n);  //Tamaño de las n partículas
    }

    void inicializar(double delta=0.1) {
        for (auto& p : particulas) {
            p.init_position();
            p.perturbacion(delta);
            p.fuerzas();
        }
    }

    void imprimir() {
        for (int i = 0; i < particulas.size(); ++i) {
            std::cout << "La partícula " << i << " esta en posición: (x,y)=("
                      << particulas[i].x << ", " << particulas[i].y << ")"
                      << " y tiene una fuerza: (" << particulas[i].fx << ", "
                      << particulas[i].fy << ") asociada \n";
        }
    }

    //Calculo de la distancia máxima entre cualquier par de partículas luego de la perturbación
    double distancia_maxima() {
        double max_dist = 0;
        for (int i = 0; i < particulas.size(); i++) {
            for (int j = i + 1; j < particulas.size(); j++) {
                double dx = particulas[i].x - particulas[j].x;
                double dy = particulas[i].y - particulas[j].y;
                //Formula de distancia 
                double dist = sqrt(dx * dx + dy * dy);
                if (dist > max_dist) max_dist = dist;
            }
        }
        return max_dist;
    }

    //Calculo de la fuerza total resultante
    double fuerza_total() {
        double fx_total = 0;
        double fy_total = 0;
        for (const auto& p : particulas) {
            fx_total+= p.fx;
            fy_total+= p.fy;
        }
        return sqrt(fx_total * fx_total + fy_total * fy_total); //Modulo de la fuerza
    }
};

int main() {
    srand(time(NULL)); //Inicializar semilla de rand 

    Sistema_total sistema(N);
    sistema.inicializar();
    sistema.imprimir();

    double d_max = sistema.distancia_maxima();
    double f_total = sistema.fuerza_total();

    std::cout << "\nDistancia máxima entre partículas: " << d_max << "\n";
    std::cout << "Magnitud de la fuerza total: " << f_total << "\n";

    return 0;
}





