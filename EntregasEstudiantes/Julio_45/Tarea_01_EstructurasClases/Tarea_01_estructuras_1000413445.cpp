# include<iostream>
# include <cmath>
# include <cstdlib>
# include <random>
# include <time.h>
# include <iomanip>


/*
Simulacion de particulas en una esfera 2d
Crear un programa que permita generar N particulas  distribuidas aleatoriamente en una esfera,
 - Generar una perturbacion para cada una de las particulas dx, dy aleatoria. 
 - Calcular la distancia maxima que hay  entre particulas
 - Suponga que las particulas tiene un vector de fuerza fx, fy, cada uno con valores aleatorios entre 0, 1
 - Cual es la magnitud de la fuerza resultante del sistema de partículas
 
*/


// Constantes
const int N = 10;
const double R = 1.0L;
const double DELTA = 0.1L;

// Estructura de partículas
struct particle{
    // Posición
    double x;
    double y;
    // Fuerza
    double Fx;
    double Fy;
};

// Función para inicializar la posición aleatoria
void initPosition(particle *p){
    srand (time(NULL));
    long double theta;
    for (int i=0;i<N;i++){
        theta = (double(rand())/RAND_MAX)*2.0*M_PI;
        p[i].x = R*cos(theta);
        p[i].y = R*sin(theta);
    }
}

// Función para introducir una perturbación aleatoria
void pertPosition(particle *p){
    srand (time(NULL));
    for (int i=0;i<N;i++){
        p[i].x += (double(rand())/RAND_MAX)*2.0*DELTA-DELTA;
        p[i].y += (double(rand())/RAND_MAX)*2.0*DELTA-DELTA;
    }
}

// Función para calcular la distancia máxima entre dos partículas del sistema
void distMax(particle *p){
    int i,j,I,J;
    double dmax = 0.0;
    for(i=0;i<N;i++){
            for(j=i+1;j<N;j++){
                double dx = p[i].x - p[j].x;
                double dy = p[i].y - p[j].y;
                double dist = sqrt(dx*dx+dy*dy);
                if (dist > dmax){
                    dmax=dist;
                    I = i;
                    J = j;
                }
            }
        }
    std::cout<<"La distancia máxima es "<<dmax<<" y se da entre las partículas "<<I<<" y "<<J<<std::endl;
}

// Función que inicializa las fuerzas aleatorias
void initForces(particle *p){
    srand (time(NULL));
    for (int i=0;i<N;i++){
        p[i].Fx = (double(rand())/RAND_MAX);
        p[i].Fy = (double(rand())/RAND_MAX);
    } 
}

// Función que calcula la fuerza neta
void netForce(particle *p){
    double Fxnet = 0.0;
    double Fynet = 0.0;
    double Fnet;
    for (int i=0;i<N;i++){
        Fxnet += p[i].Fx;
        Fynet += p[i].Fy;
    }
    Fnet = sqrt(Fxnet*Fxnet+Fynet*Fynet);
    std::cout<<"La magnitud de la fuerza resultante es "<<Fnet<<std::endl;
}

int main(){
    std::cout<<std::setprecision(6)<<std::fixed;
    particle parts[N];
    int i;
    initPosition(parts);
    std::cout<<"1. Posiciones iniciales"<<std::endl;
    std::cout<<"---------------------------"<<std::endl;
    std::cout<<"i"<<"\t"<<"x"<<"\t\t"<<"y"<<std::endl;
    for (i=0;i<N;i++){
        std::cout<<i<<"\t"<<parts[i].x<<"\t"<<parts[i].y<<std::endl;
    }
    std::cout<<"---------------------------"<<std::endl;

    std::cout<<"2. Posiciones perturbadas"<<std::endl;
    pertPosition(parts);
    std::cout<<"---------------------------"<<std::endl;
    std::cout<<"i"<<"\t"<<"x"<<"\t\t"<<"y"<<std::endl;
    for (i=0;i<N;i++){
        std::cout<<i<<"\t"<<parts[i].x<<"\t"<<parts[i].y<<std::endl;
    }
    std::cout<<"---------------------------"<<std::endl;

    std::cout<<"3. Distancia máxima"<<std::endl;
    distMax(parts);
    std::cout<<"---------------------------"<<std::endl;

    std::cout<<"4. Fuerzas"<<std::endl;
    initForces(parts);
    std::cout<<"---------------------------"<<std::endl;
    std::cout<<"i"<<"\t"<<"Fx"<<"\t\t"<<"Fy"<<std::endl;
    for (i=0;i<N;i++){
        std::cout<<i<<"\t"<<parts[i].Fx<<"\t"<<parts[i].Fy<<std::endl;
    }
    std::cout<<"---------------------------"<<std::endl;

    std::cout<<"5. Magnitud de la fuerza neta"<<std::endl;
    netForce(parts);

    return 0;
}
