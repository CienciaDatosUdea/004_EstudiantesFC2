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


class FileWriter {
    public:
        FileWriter(const std::string &filename);
        std::ofstream file;    
      //  void writePosicionCampo(const Grid &G, const CampoVelocidadesPresion &Campo);
        void writePosicion(const Grid &G);
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