#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <functional>
#include <string>
#include <iomanip>

using namespace std;

class Grid{
    public:             
        Grid(double z_max, 
            double t_max, 
            double beta);

            double dz, dt;
            double z_max, t_max, beta;
            int nz, nt;                
            std::vector<std::vector<std::vector<double>>> ZT;
};

class CampoEM{
    private:
        int nz2, nt2;
    public:
        CampoEM(Grid &g);
        Grid g;
        std::vector<std::vector<double>> E,H;
        void applyInitialCondition(function<double(double)> f);};

class Evolution{
    public:
        Evolution(CampoEM &field);
        CampoEM field;
        void run(bool periodic);
};

class FieldWriter {
    public:
        FieldWriter(const std::string &filename);
        std::ofstream file;    
        void writeInitial(const Grid &G, const CampoEM &field);
        void writeField(const Grid &G, const CampoEM &field);
              
};