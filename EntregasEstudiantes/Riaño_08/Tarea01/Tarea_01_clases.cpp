# include<iostream> 
# include <cmath>    
# include <random>  

// Definición de constantes globales
const int N = 10;     // Número de partículas a simular.
const double R = 1.0;   // Radio inicial para la posición de las partículas.
const double DELTA = 0.1; // Rango de la perturbación aplicada a las posiciones de las partículas.

// La clase Particle encapsula los datos y el comportamiento de una sola partícula.
// Esto sigue un enfoque de programación orientada a objetos (POO).
class Particle{

    public:
        // Variables miembro que almacenan los datos de la partícula.
        double x,y,fx,fy;
        double xdx,ydy; // xdx y ydy almacenan las posiciones perturbadas.
        
        // Declaración de los métodos (funciones miembro) de la clase.
        Particle(); // Constructor para inicializar la partícula.
        void Initialization();
        void Perturbation();
        void Forces();

};

// Definición del constructor de la clase.
// Inicializa todas las variables a cero.
Particle::Particle (){
    x = 0;
    y = 0;
    fx = 0;
    fy = 0;
    xdx = 0;
    ydy = 0;
}

// Método para inicializar la posición de la partícula en un círculo de radio R.
void Particle::Initialization(){
    double theta;
    // Genera un ángulo aleatorio entre 0 y 2*pi.
    theta = (double(rand())/RAND_MAX)*2.0*M_PI;
    // Calcula las coordenadas (x, y) usando las ecuaciones paramétricas de un círculo.
    x = R * cos(theta);
    y = R * sin(theta);

}

// Método para perturbar la posición de la partícula.
// Genera nuevos valores de posición (xdx, ydy) dentro de un rango +/- DELTA.
void Particle::Perturbation(){

    xdx = x -DELTA + (double(rand())/RAND_MAX) * (2.0 * DELTA);
    ydy = y -DELTA + (double(rand())/RAND_MAX) * (2.0 * DELTA);

}

// Método para asignar fuerzas aleatorias a la partícula.
// Los valores de fx y fy se asignan aleatoriamente entre 0 y 1.
void Particle::Forces(){

    fx = (double(rand())/RAND_MAX);
    fy = (double(rand())/RAND_MAX);
}


// Función principal del programa.
int main(){

    // Crea un arreglo dinámico de objetos Particle en el heap.
    Particle* P = new Particle[N];
    
    std::cout<<"Posiciones Iniciales:\n";
    // Bucle para inicializar cada partícula e imprimir su posición inicial.
    for(int i = 0; i < N; i++){
        P[i].Initialization();
        std::cout << "P[" << i << "].x = " << P[i].x << "\t" << "P[" << i << "].y = " << P[i].y << "\n";
    };

    std::cout<<"\nPosiciones Perturbadas:\n";
    // Bucle para perturbar cada partícula e imprimir su nueva posición.
    for(int i = 0; i < N; i++){
        P[i].Perturbation();
        std::cout << "P[" << i << "].x+dx = " << P[i].xdx << "\t" << "P[" << i << "].y+dy = " << P[i].ydy << "\n";
    };
    
    double d_max = 0; // Variable para almacenar la distancia máxima.
    double d_new;     // Variable temporal para la distancia entre dos partículas.

    // Bucle anidado para calcular la distancia máxima entre todas las parejas de partículas perturbadas.
    for(int i=0;i<N;i++){
        for(int j=i+1;j<N;j++){ 
            // Calcula la distancia euclidiana entre las partículas i y j.
            d_new = sqrt((P[i].xdx-P[j].xdx)*(P[i].xdx-P[j].xdx)+(P[i].ydy-P[j].ydy)*(P[i].ydy-P[j].ydy));
            // Actualiza d_max si la distancia actual es mayor.
            if(d_new > d_max){
                d_max = d_new;
            }
        }
    }

    std::cout << "\nDistancia Máxima:\n" << "d_max = " << d_max << "\n\nFuerzas:\n";

    // Bucle para asignar fuerzas aleatorias a cada partícula e imprimirlas.
    for(int i = 0; i < N; i++){
        P[i].Forces();
        std::cout << "P[" << i << "].fx = " << P[i].fx << "\t" << "P[" << i << "].fy = " << P[i].fy << "\n";
    };

    double Fx = 0, Fy = 0; // Variables para la fuerza total.
    // Bucle para sumar las componentes de fuerza de todas las partículas.
    for(int i=0;i<N;i++){
        Fx += P[i].fx;
        Fy += P[i].fy;
    };

    // Imprime la fuerza total y su magnitud.
    std::cout << "\nFuerza total:\nFx = " << Fx << "\nFy = " << Fy << "\n|F| = " << sqrt(Fx*Fx + Fy*Fy) << "\n";

    // Falta liberar la memoria del arreglo dinámico P: delete[] P;
    // Esto es una fuga de memoria.

    return 0;
}