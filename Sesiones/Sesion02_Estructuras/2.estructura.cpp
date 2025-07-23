# include<iostream>
# include <cmath>
# include <random>
// g++ -std=c++17 -Wall programa.cpp -o programa.out

/*
Simulacion de particulas en una esfera 2d
Crear un programa que permita generar N particulas  distribuidas aleatoriamente en una esfera,
 - Generar una perturbacion para cada una de las particulas dx, dy aleatoria. 
 - Calcular la distancia maxima que hay  entre particulas
 - Suponga que las particulas tiene un vector de fuerza fx, fy, cada uno con valores aleatorios entre 0, 1
 - Cual es la magnitud de la fuerza resultadante del sistema de partículas
 - Implementar la solucion, empleando clases
 
*/

const int N =10;
struct particula{
    double x;
    double y;
};

void init_position(particula *p){
    double theta;
    int i;    
   // std::random_device rd;   // Usa hardware para semilla (si está disponible)
   // std::mt19937 gen(rd());  // Mersenne Twister generator
   // std::uniform_real_distribution<double> dist(0.0, 2.0 * M_PI);    
    for(i=0;i<N;i++){
        theta = (double(rand())/RAND_MAX)*2.0*M_PI; 
        p[i].x=cos(theta);
        p[i].y=sin(theta);
    }
}


int main(int argc, char *argv []){
    particula p[N];
    srand(time(NULL));

    init_position(p);   
    for(int i=0;i<N;i++){        
        std::cout<<p[i].x<<"\t"<<p[i].y<<"\n";
    }
    return 0;
}

