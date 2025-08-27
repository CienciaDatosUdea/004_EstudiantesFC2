#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Grid{
    public:
        Grid(double x_min, double x_max, double y_min, 
            double y_max, int nx, int ny);

            double dx, dy;
            double x_min, x_max, y_min, y_max;
            int nx, ny;
            vector<vector<vector<double>>> XY;
};

class CampoVelocidadesPresion{
    public:
        CampoVelocidadesPresion(Grid &G);

        Grid &G;
        vector<vector<double>> U, V, P;

        void CondicionesIniciales();
        void BoundaryCondition();
};

class ComputePresion{
    public:
        ComputePresion(CampoVelocidadesPresion &Campo, 
            double rho, double dt, int nit);

            CampoVelocidadesPresion &Campo;
            double rho, dt;
            int nit;

            void presionUpdate();
};

class ComputeCampo{
    public:
        ComputeCampo(ComputePresion &omega, double F);
        ComputePresion &omega;
        double F;
        void velocidadesUpdate();
};

class FieldWriter{
    public:
        FieldWriter(const string &filename);
        ofstream file;
        void writePosicionCampo(const Grid &G, 
        const CampoVelocidadesPresion &Campo);    
};
