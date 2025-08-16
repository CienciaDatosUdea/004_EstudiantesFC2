#include <iostream>
#include <vector>

class Grid{
    public:         
    
        Grid(double x_min, double x_max, int N);
        double dx;
        double x_min, x_max;
        int N;         
        std::vector<double> x;        
};

class  Temperature{
    public: 
        Temperature(Grid &grid);        
        Grid &grid;   
        std::vector<double> u;
        void applyInitialCondition();
        void applyBoundaryCondition();
    
};

class DiffusionSolver {
public:
    Temperature& field;
    double D, dt, t_max;

    DiffusionSolver(Temperature& field, double D, double dt, double t_max);
    void run();
    void step();
};
