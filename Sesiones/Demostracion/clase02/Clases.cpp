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
        //particula(double x0, double y0): x(x0), y(y0) {};
        void init_configuracion(){
            double theta;
            theta = random_number(0,2* M_PI);  
            x = cos(theta);
            y = sin(theta);
        }
        void update_position(double dx, double dy){
            x=x+dx;
            y=x+dy;
        }
        
        double get_x(){return x; }
        double get_y(){return y; }
       // particula(double x0, double y0): x(x0), y(y0) {};
       
};

int main(int argc,char *argv [] ){
    int a; 
    int b;
    int N=10;
//    particula p[N];
    std::vector<particula> p(N);
    
    for(int i=0;i<N;i++){
        p[i].init_configuracion();
        std::cout <<p[i].get_x()<<"\n";    
    }
     
    for(auto &v:p){
        v.init_configuracion();
        std::cout <<v.get_x()<<"\n";    
    }

    return 0;
}
