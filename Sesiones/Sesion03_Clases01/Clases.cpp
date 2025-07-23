#include <iostream>
#include <cmath>
#include<random>
#include <cstdlib>
#include <ctime>

const int N=10;

std::mt19937_64& global_rng() {
    static std::mt19937_64 rng{ /*semilla*/ };
    return rng;
}

double random_number(double a, double b) {
    std::uniform_real_distribution<double> dist(a, b);
    return dist(global_rng());
}


class particula{
    private:
        double x;
        double y;
    public:
        particula(): x(0), y(0) {};

       // particula(double x0, double y0): x(x0), y(y0) {};
       
};

class sistema{

};

int main(int argc,char *argv [] ){
    int a; 
    int b;

    a=std::atoi(argv[1]);
    b=std::atoi(argv[2]);

    std::cout<<"Cantidad de argumentos "<<argc<<"\n";
    std::cout<<" Elemtnos 0 "<<argv[0]<<"\n";
    std::cout<<" Elemtnos 1 "<<argv[1]<<"\n";
    std::cout<<" Elemtnos 2 "<<argv[2]<<"\n";
    std::cout<<random_number(a, b);
    return 0;
}
