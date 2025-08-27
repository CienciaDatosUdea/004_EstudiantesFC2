#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>

class Grid{
    public:             
        Grid(double x_min, double x_max, 
            double y_min, double y_max, 
            int nx, int ny);

            double dx, dy;
            double x_min, x_max;
            double y_min, y_max;
            int nx, ny;                
            std::vector<std::vector<std::vector<double>>> XY;
};

class CampoVelocidadesPresion{
    public:
        CampoVelocidadesPresion(Grid &G);
        
        Grid &G;        
        std::vector<std::vector<double>> U;
        std::vector<std::vector<double>> V;
        std::vector<std::vector<double>> P;

        void CondicionesIniciales();
        void BoundaryCondition();
};


class ComputePresion{
    public:
        ComputePresion (CampoVelocidadesPresion &Campo, double rho, double dt, int nit);
        
        CampoVelocidadesPresion &Campo;
        double rho;
        double dt;
        int nit;
        void presionUpdate();

}   ;


class ComputeCampo{
    public:
        ComputeCampo (ComputePresion &omega);
        ComputePresion &omega;        
        std::vector<std::vector<double>> f;
        void velocidadesUpdate();

}   ;


class FieldWriter {
    public:
        FieldWriter(const std::string &filename);
        std::ofstream file;    
        void writePosicionCampo(const Grid &G, const CampoVelocidadesPresion &Campo);
};
