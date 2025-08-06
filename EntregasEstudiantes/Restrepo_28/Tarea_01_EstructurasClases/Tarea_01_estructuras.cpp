#include <iostream>
#include <cmath>
#include <random>
#include <vector>


const int N= 100;
const double DELTA = 0.1;
const double R = 1.0;

std::mt19937_64& global_rng(){
    static std::mt19937_64 rng{1}; //Definimos un seed para verificar que ambos ejemplos den lo mismo
    return rng;
}

double random_number(float a,float b){
    std::uniform_real_distribution<double> dist(a, b);

    return dist(global_rng());

}

struct Particle{
    double x,y;
    std::vector<double> force;

    Particle(): x(0),y(0), force(2,0.0){};

    void init_configuration(){
        double theta;
        theta = random_number(0,2*M_PI);
        x = R*cos(theta);
        y = R*sin(theta);
        init_forces();
    }

    void init_forces(){
        double fx = random_number(0,1);
        double fy = random_number(0,1);
        force[0] = fx;
        force[1] = fy;
    }

    void update(double dx, double dy){
        x = x+dx;
        y = y+dy;
    }
};

struct System{
    std::vector<Particle> p;

    System(int N): p(N){};

    void init_all_particles(){
        for(auto &v:p){
            v.init_configuration();
        }
    }

    double max_distance(){
        double M = 0.01;
        double dx,dy,dij;
        for(auto &pi:p){
            for(auto &pj:p){
                if(&pi == &pj) continue;
                dx = pi.x - pj.x;
                dy = pi.y - pj.y;
                dij = sqrt(dx*dx+dy*dy);
                if (dij>M) M = dij;
            }
        }
        return M;
    }

    std::vector<double> get_total_force(){
        double total_fx = 0.0;
        double total_fy = 0.0;
        for(auto &v:p){
            std::vector<double> f = v.force;
            total_fx += f[0];
            total_fy += f[1];
        }
        return {total_fx,total_fy};
    }

    double get_total_force_mag(){
        std::vector<double> f = get_total_force();
        return sqrt(f[0]*f[0] + f[1]*f[1]);
    }

    void perturb(double delta){
        for(auto &v:p){
            double dx = random_number(-delta,delta);
            double dy = random_number(-delta,delta);
            v.update(dx,dy);
        }
    }

    void cout_particle_pos(){
        system("clear");
        for(auto &v:p){
            std::cout<<v.x<<"\t"<<v.y<<std::endl;
        }
    }
};

int main(){
    System s(N);
    s.init_all_particles();
    s.perturb(DELTA);
    s.cout_particle_pos();
    std::cout <<"Distancia máxima entre partículas: "<<s.max_distance()<<"\n";
    std::cout<<"Componentes fuerza total: ("<<s.get_total_force()[0]<<","
    <<s.get_total_force()[1]<<")\t";
    std::cout <<"magnitud fuerza total: "<<s.get_total_force_mag()<<"\n";

    return 0;
}