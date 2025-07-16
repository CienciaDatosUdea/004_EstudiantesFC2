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

class sistema{
    private :
        std::vector<particula> p ;
         
    public:
        double valor_minimo;    
        sistema (int N):p(N){};
        
    void init_all_particles(){
        for(auto &v:p){
            v.init_configuracion();
            std::cout <<v.get_x()<<"\n";    
        }
    }

    double posicion_i_esima_x(int i){
        return p[i].get_x();
    }

    particula &operator[](int i){
            return p[i];
    }

    void distancia_minima(){
        double dx,dy, dij;
        double R=10000000.0;
        for(int i=0;i<N;i++){
          for(int j=0;j<N;j++){
            if(i==j)
                continue;
            dx = p[i].get_x()-p[j].get_x();
            dy = p[i].get_y()-p[j].get_y();
            dij=sqrt(dx*dx+dy*dy);
            if(dij<R)
                R=dij;
          }  
        }
        valor_minimo=R;
    }

};

int main(int argc,char *argv [] ){
    int a; 
    int b;
    int N=10;
    sistema s(N);
    s.init_all_particles();    
    s.distancia_minima(10);
    std::cout<<s.valor_minimo;
    //std::vector<particula> p(N);
    //std::cout<<"---";
    
    // for(int i=0;i<N;i++){
    //     p[i].init_configuracion();
    //     std::cout <<p[i].get_x()<<"\n";    
    // }
    s.posicion_i_esima_x(1);
    s[10].get_x();
    return 0;
}
