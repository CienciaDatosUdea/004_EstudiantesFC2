#include <iostream>
#include <cmath>
#include<random>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>

const int N = 10;
const double R = 1.0;
const double DELTA = 0.1;

// Clase partícula
class particula{

    public:
        particula(): x(0), y(0), Fx(0), Fy(0) {}; // Constructor
        // Posición
        double x;
        double y;
        // Fuerzas
        double Fx;
        double Fy;

        // Método para inicializar la posición aleatoria
        void initPosition(double R){
            double theta;
            theta = (double(rand())/RAND_MAX)*2.0*M_PI;
            x = R*cos(theta);
            y = R*sin(theta);
        }

        // Método para perturbar la posición
        void pertPosition(double dx, double dy){
            x += dx;
            y += dy;

        }
};

// Clase sistema, inicializa N partículas
class sistema{
    private:
        std::vector<particula> p;  // vector de partículas
    public:
        sistema (int N): p(N) {};

    // Método que inicializa las posiciones aleatorias de todas las partículas
    void initAll(double R){
        for(auto &v:p){
        v.initPosition(R);
    }

    // Método que perturba las posiciones aleatorias de todas las partículas
    }
    void pertAll(double delta){
        srand (time(NULL));
        for (auto &v:p){
            double dx = (double(rand())/RAND_MAX)*2.0*delta-delta;
            double dy = (double(rand())/RAND_MAX)*2.0*delta-delta;
            v.pertPosition(dx,dy);
        }
    }

    // Método para calcular la distancia máxima entre dos partículas del sistema
    void distMax(){
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

    // Método que inicializa las fuerzas aleatorias de todas las partículas
    void initForces(){
    srand (time(NULL));
    for (int i=0;i<N;i++){
        p[i].Fx = (double(rand())/RAND_MAX);
        p[i].Fy = (double(rand())/RAND_MAX);
    }
    }

    // Sobrecarga del operador [] para acceder a la iésima partícula
    particula& operator[] (int i){
        return p[i];
    }

    // Método que calcula la magnitud de la fuerza neta sobre el sistema
void netForce(){
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


};

int main(){

    std::cout<<std::setprecision(6)<<std::fixed;
    sistema s(N);
    int i;
    s.initAll(R);
    std::cout<<"1. Posiciones iniciales"<<std::endl;
    std::cout<<"---------------------------"<<std::endl;
    std::cout<<"i"<<"\t"<<"x"<<"\t\t"<<"y"<<std::endl;
    for (i=0;i<N;i++){
        std::cout<<i<<"\t"<<s[i].x<<"\t"<<s[i].y<<std::endl;
    }
    std::cout<<"---------------------------"<<std::endl;

    std::cout<<"2. Posiciones perturbadas"<<std::endl;
    s.pertAll(DELTA);
    std::cout<<"---------------------------"<<std::endl;
    std::cout<<"i"<<"\t"<<"x"<<"\t\t"<<"y"<<std::endl;
    for (i=0;i<N;i++){
        std::cout<<i<<"\t"<<s[i].x<<"\t"<<s[i].y<<std::endl;
    }
    std::cout<<"---------------------------"<<std::endl;

    std::cout<<"3. Distancia máxima"<<std::endl;
    s.distMax();
    std::cout<<"---------------------------"<<std::endl;

    std::cout<<"4. Fuerzas"<<std::endl;
    s.initForces();
    std::cout<<"---------------------------"<<std::endl;
    std::cout<<"i"<<"\t"<<"Fx"<<"\t\t"<<"Fy"<<std::endl;
    for (i=0;i<N;i++){
        std::cout<<i<<"\t"<<s[i].Fx<<"\t"<<s[i].Fy<<std::endl;
    }
    std::cout<<"---------------------------"<<std::endl;

    std::cout<<"5. Magnitud de la fuerza neta"<<std::endl;
    s.netForce();
    return 0;
}