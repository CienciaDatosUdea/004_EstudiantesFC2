#include <iostream>


const int N=100;

struct particula{
    double x;
    double y;
    double masa;
    double espin;
    double carga;
};

void init_particle(particula *p){
double r1,r2;

    for (int i=0;i<N;i++){
        r1 = (double(rand()) / RAND_MAX);
        r2 = (double(rand()) / RAND_MAX);
        p[i].x = r1;
        p[i].y = r2;
    }

}

int main(){
    srand(time(NULL));

    particula part[N];

    init_particle(part);

    for (int i=0;i<N;i++){
        std::cout<<part[i].x<<"\n";
    }

    return 0;
}