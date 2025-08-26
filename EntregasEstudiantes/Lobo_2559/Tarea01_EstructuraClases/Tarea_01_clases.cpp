#include <cmath>
#include <iostream>

const int N=10; // Número de partículas
using namespace std;

class Particula {
    public:
        double x; //posición en x
        double y; //posición en y
        double fx; //fuerza en x
        double fy; //fuerza en y

        Particula() : x(0), y(0), fx(0), fy(0) {} // Constructor por defecto

        void init_particule(double r) {   
            // Metodo que inicializa la partícula con una posición aleatoria dentro de un círculo de radio r
            double theta;
            double r1, r2;

            theta = 2 * M_PI * (double)rand() / RAND_MAX; // Ángulo aleatorio
            // Radios aleatorios dentro de un círculo de radio r
            r1 = r * (double(rand()) / RAND_MAX);
            r2 = r * (double(rand()) / RAND_MAX);
            // Posición en coordenadas cartesianas
            x = r1 * cos(theta);    
            y = r2 * sin(theta);
            // Fuerzas aleatorias
            fx = (double(rand()) / RAND_MAX);
            fy = (double(rand()) / RAND_MAX);
        }

        void perturbation(double delta) {
            // Método que perturba la posición de la partícula aleatoriamente
            double dx = ((double)rand() / RAND_MAX) * 2 * delta - delta;
            double dy = ((double)rand() / RAND_MAX) * 2 * delta - delta;
            x += dx;
            y += dy;
        }

        double max_distance(Particula& other) {
            // Método que calcula la distancia entre esta partícula y otra
            return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
        }
        
};

class Sistema {
 //class que representa un sistema de partículas
private:
    Particula particulas[N];

public:
    // Método para inicializar todas las partículas
    void inicializar_particulas(double radio) {
        for (int i = 0; i < N; ++i) {
            particulas[i].init_particule(radio);
        }
    }

    //Imprime las posiciones de todas las partículas
    void mostrar_posiciones() const {
        cout << "Posiciones: " << endl;
        for (int i = 0; i < N; ++i) {
            cout << particulas[i].x << " , " << particulas[i].y << endl;
        }
    }

    //aplica una perturbación a todas las partículas
    void perturbar_todas(double delta) {
        cout << "Sistema perturbado..... " << endl;
        for (int i = 0; i < N; ++i) {
            particulas[i].perturbation(delta);
        }
    }

    // Calcula la distancia máxima entre todas las partículas
    double distancia_maxima(){
        double max_dist = 0.0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                double dist = particulas[i].max_distance(particulas[j]);
                if (dist > max_dist) {
                    max_dist = dist;
                }
            }
        }
        return max_dist;
    }

    // Calcula la magnitud de la fuerza total sobre el sistema
    double fuerza_total() const {
        double fx_total = 0.0, fy_total = 0.0;
        for (int i = 0; i < N; ++i) {
            fx_total += particulas[i].fx;
            fy_total += particulas[i].fy;
        }
        return sqrt(fx_total * fx_total + fy_total * fy_total);
    }
};

int main() {
    srand(0); // Semilla para reproducibilidad

    double radio = 1.0;
    double delta = 0.1;

    Sistema sistema; // Crear una instancia del sistema de partículas
    sistema.inicializar_particulas(radio); // Inicializar las partículas
    sistema.mostrar_posiciones(); // Mostrar posiciones iniciales
    sistema.perturbar_todas(delta); // Perturbar todas las partículas
    sistema.mostrar_posiciones(); // Mostrar posiciones perturbadas

    double d_max = sistema.distancia_maxima();
    double f_total = sistema.fuerza_total();

    cout << "La distancia máxima entre partículas es: " << d_max << endl;
    cout << "La magnitud de la fuerza total sobre el sistema es: " << f_total << endl;

    return 0;
}
