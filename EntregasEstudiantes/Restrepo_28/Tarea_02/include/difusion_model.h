#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <functional>

class Geometry{
    public:
        Geometry(int N,double xmin, double xmax);
        int N;
        double dx, xmin ,xmax;
        std::vector<double> x;//vector de posiciones
};

class Conditions{
    public:
        Conditions(Geometry &G);
        Geometry G;
        std::vector<double> u; //temperatura inicial
        void initialConditions(std::function<double(double)>); //condiciones iniciales definidas por una función
        void boundaryConditions(double DL); //Condiciones de frontera tipo Dirichlet
};

class Writer; //se declara aquí para que Solver pueda referenciarlo

class Solver{
    public:
        Solver(Conditions &C);
        Conditions C;
        double t0,dx;
        std::vector<double> temp;

        void step(double dt,double D);//avanza un paso en la simulación
        void run(double tmax,double dt,double D,Writer* writer = nullptr);//simula hasta un tiempo tmax

};

class Writer{
    public:
        Writer(const std::string &filename);
        std::ofstream file;

        void writeSolution(const Solver &S );


};