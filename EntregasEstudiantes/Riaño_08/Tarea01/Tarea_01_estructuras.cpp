# include<iostream> 
# include <cmath>    
# include <random>  
# include <ctime>    // Necesario para la función time()

// Definición de constantes globales
const int N = 10;     // Número de partículas a simular.
const double R = 1.0;   // Radio inicial para la posición de las partículas.
const double DELTA = 0.1; // Rango de la perturbación aplicada a las posiciones de las partículas.

// Definición de la estructura 'particula'
// Representa una partícula con sus coordenadas de posición (x, y) y componentes de fuerza (fx, fy).
// Este enfoque es un ejemplo de programación estructurada.
struct particula{
    double x;
    double y;
    double fx;
    double fy;
};

// Función para inicializar la posición de las partículas
// Las partículas se colocan en un círculo de radio R.
void init_position(particula *p){
    double theta; // Variable para almacenar el ángulo.
    int i;        // Variable de contador para el bucle.

    // Itera sobre cada partícula para inicializar su posición.
    for(i=0;i<N;i++){
        // Genera un ángulo aleatorio entre 0 y 2*PI.
        theta = (double(rand())/RAND_MAX)*2.0*M_PI;
        // Calcula las coordenadas x e y usando el radio R y el ángulo theta.
        p[i].x = R * cos(theta);
        p[i].y = R * sin(theta);
    }
}

// Función para perturbar la posición de las partículas
// Añade un pequeño desplazamiento aleatorio a cada coordenada de la partícula.
void perturbation(particula *p){
    int i; // Variable de contador para el bucle.

    // Itera sobre cada partícula para aplicar la perturbación.
    for(i=0;i<N;i++){
        // Añade un valor aleatorio entre -DELTA y DELTA a la coordenada x.
        p[i].x += -DELTA + (double(rand())/RAND_MAX) * (2.0 * DELTA);
        // Añade un valor aleatorio entre -DELTA y DELTA a la coordenada y.
        p[i].y += -DELTA + (double(rand())/RAND_MAX) * (2.0 * DELTA);
    }
}

// Función para asignar fuerzas aleatorias a las partículas
// Asigna componentes de fuerza (fx, fy) aleatorias entre 0 y 1 a cada partícula.
void forces(particula *p) {
    int i; // Variable de contador para el bucle.
    for(i=0;i<N;i++){
        // Asigna un valor aleatorio entre 0 y 1 a la componente fx.
        p[i].fx = (double(rand())/RAND_MAX);
        // Asigna un valor aleatorio entre 0 y 1 a la componente fy.
        p[i].fy = (double(rand())/RAND_MAX);
    }
}

// Función principal del programa
int main(){
    particula p[N]; // Declara un arreglo estático de N partículas.

    // Inicializa la semilla del generador de números aleatorios con la hora actual.
    // Esto asegura que los resultados sean diferentes en cada ejecución.
    srand(time(NULL)); 

    // Inicializa las posiciones de las partículas.
    init_position(p);
    std::cout << "Posiciones Iniciales:\n";
    // Imprime las posiciones iniciales de cada partícula.
    for(int i=0;i<N;i++){
        std::cout << "p[" << i << "].x = " << p[i].x << "\t" << "p[" << i << "].y = " << p[i].y << "\n";
    }

    std::cout << "\nPosiciones Perturbadas:\n";

    // Aplica la perturbación a las posiciones de las partículas.
    // En este enfoque, las posiciones originales se sobrescriben.
    perturbation(p);
    // Imprime las posiciones de las partículas después de la perturbación.
    for(int i=0;i<N;i++){
        std::cout << "p[" << i << "].x+dx = " << p[i].x << "\t" << "p[" << i << "].y+dy = " << p[i].y << "\n";
    }

    double d_max = 0; // Variable para almacenar la distancia máxima entre partículas.
    double d_new;     // Variable temporal para almacenar la distancia entre un par de partículas.

    // Calcula la distancia máxima entre todas las parejas de partículas.
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){ // Se empieza desde i+1 para evitar duplicados y la distancia de una partícula consigo misma.
            // Calcula la distancia euclidiana entre la partícula i y la partícula j.
            d_new = sqrt((p[i].x-p[j].x)*(p[i].x-p[j].x)+(p[i].y-p[j].y)*(p[i].y-p[j].y));
            // Actualiza d_max si se encuentra una distancia mayor.
            if(d_new > d_max){
                d_max = d_new;
            }
        }
    }

    std::cout << "\nDistancia Máxima:\n" << "d_max = " << d_max << "\n";

    // Asigna fuerzas aleatorias a las partículas.
    forces(p);

    std::cout << "\nFuerzas:\n";
    // Imprime las componentes de fuerza de cada partícula.
    for(int i=0;i<N;i++){
        std::cout << "p[" << i << "].fx = " << p[i].fx << "\t" << "p[i].fy = " << p[i].fy << "\n";
    }

    double Fx = 0, Fy = 0; // Variables para almacenar la suma total de las componentes de fuerza.

    // Calcula la fuerza total sumando las componentes de fuerza de todas las partículas.
    for(int i=0;i<N;i++){
        Fx += p[i].fx;
        Fy += p[i].fy;
    }

    // Imprime la fuerza total (componentes Fx, Fy y magnitud |F|).
    std::cout << "\nFuerza total:\nFx = " << Fx << "\nFy = " << Fy << "\n|F| = " << sqrt(Fx*Fx + Fy*Fy) << "\n";

    return 0; // Indica que el programa finalizó correctamente.
}