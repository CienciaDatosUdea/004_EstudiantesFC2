# include<iostream>

// g++ -std=c++17 -Wall programa.cpp -o programa.out
struct particula{
    double x;
    double y;
};


class PuntoClass{

    public:
        double x, y;
        PuntoClass(double x0, double y0){
        x=x0;
        y=y0;
        }
        void imprimir(){
            std::cout<<x;
        }
        
    };


int main(){
    system("clear");
    
    particula p;
    p.x=1;
    p.y=2;
    std::cout<<p.x<<"\n";

    PuntoClass pp(1.0,11.0);
    std::cout<<pp.x;

    return 0;
}

