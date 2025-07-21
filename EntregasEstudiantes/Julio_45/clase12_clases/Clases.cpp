#include <iostream>
#include <cmath>
#include<random>
#include <cstdlib>
#include <ctime>
#include <vector>

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

        void init_configuration(){
            double theta;
            theta = random_number(0,2*M_PI);
            x = cos(theta);
            y = sin(theta);
        }

        void update_position(double dx, double dy){
            x += dx;
            y += dy;

        }
        
        // particula(double x0,double y0): x(x0), y(y0) {};
        double get_x(){return x;}
        double get_y(){return y;}

};

class sistema{
    private:
        std::vector<particula> p;
    public:
        sistema (int N): p(N) {};
        double min_val;

    void init_all_particles(){
        for(auto &v:p){
        v.init_configuration();
        // std::cout<<v.get_x()<<std::endl;
    }
    }
    void min_dist(){
        double R = 100000000.;
        for(int i=0;i<N;i++){
            for(int j=i+1;j<N;j++){
                double dx = p[i].get_x() - p[j].get_x();
                double dy = p[i].get_y() - p[j].get_y();
                double dist = sqrt(dx*dx+dy*dy);
                if (dist < R){R=dist;}
            }
        }
        min_val = R;
    }
    double position_xi(int i){
        return p[i].get_x();
    }
    double position_yi(int i){
        return p[i].get_y();
    }
};

int main(int argc,char *argv [] ){

    int N=10;

    sistema s(N);
    s.init_all_particles();
    s.min_dist();
    std::cout<<s.min_val<<std::endl;
    return 0;
}
