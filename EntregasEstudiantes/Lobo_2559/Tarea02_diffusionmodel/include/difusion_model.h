#include<iostream>
#include<cmath>
#include<cstdio>
#include<vector>
#include<fstream>

using namespace std;

class Geometria{
    // Clase para definir la geometría del problema
    public:
        int N;
        double dx, xmin, xmax;
        vector<double> x;
        Geometria(int N, double xmin, double xmax);
};

class CampoInicial{
    // Clase para definir el campo de temperatura inicial
    public:
        vector<double> u;
        double TL, TR;
        CampoInicial(double TL, double TR, double x0, double alpha, Geometria &geom);
};

class DiffusionSolver{
    // Clase para resolver la ecuación de difusión
    public:
        Geometria& geom;
        CampoInicial& temp;
        double D;
        double dt;
        double alpha;
        int Nsteps;
        DiffusionSolver(Geometria& g, CampoInicial& u, double D_, double dt_);
        void step();
        void evolucion(double tmax);
        void save(string filename = "../solucion_final.csv", bool is_first = true, int n= 0);

};