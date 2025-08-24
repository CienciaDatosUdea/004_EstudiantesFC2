#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cmath>
#include <functional>
#include <iomanip>

class Cosmology{
    private:
        std::vector<long double> geffvec,heffvec,Tvec,dlngeffdlnTvec,dlnheffdlnTvec;
    public:
        long double T;
        Cosmology(long double T);
        void readDegreesOfFreedom(const std::string& path);
        void calculate(const std::string& path);
        long double geff,heff,dlngeffdlnT,dlnheffdlnT;
        long double entropyDensity,energyDensity,hubbleRate;
};

class DarkMatterModel{
    public:
        DarkMatterModel(std::string name,int DMini,int DMfin,int SMfin);
        std::string name;
        int DMini;
        int DMfin;
        int SMfin;
        void printProcess();
};

class BoltzmannEquation{        
    public:
        BoltzmannEquation(long double x,long double MS,int g,long double sigmav,DarkMatterModel model,const std::string& path);
        long double x;
        long double MS;
        int g;
        long double sigmav;
        std::string modelname;
        const std::string path;
        Cosmology C;
        int DMini, DMfin, SMfin;
        long double Yeq();
        long double dYdx(long double Y);
        void setX(long double new_x);
};

class Secante {
public:
    // Constructor
    Secante(double tol, int maxIter);

    // Método para encontrar la raíz
    double encontrarRaiz(const std::function<double(double)>& f, double x0, double x1);

private:
    double tolerancia;
    int maxIteraciones;
};

class BEqSolver{
    public:
        BEqSolver(long double xi0,long double xif,int nxi,long double Y0,BoltzmannEquation BEQ);
        long double x0;
        int nxi;
        long double Y0;
        BoltzmannEquation BEQ;
        long double Omegah2,delta;
        std::vector<long double> xis,xs,Ys;
        void solve();        
};

class FieldWriter {
    public:
        FieldWriter();
        std::ofstream solution, params;    
        void write(BEqSolver sol);
};