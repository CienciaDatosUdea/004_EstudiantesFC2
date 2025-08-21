// Este archivo contiene la declaración de las clases que se utilizan en el fdtd.cpp. 
#include <vector>
#include <string> 

//Clase Grid define la geometría del sistema, en esta clase se construye la malla.
class Grid {
public:
    int N;          // número de nodos 
    double dz;      // paso espacial
    double dt;      // paso temporal
    double beta;    // parámetro de Courant 
    std::vector<double>z;
    Grid(int N_, double dz_, double beta_);
};

//Clase Fields define los campos magnetico y eléctrico
class Fields {
public:
    double dz;
    std::vector<std::vector<double>> Ex;
    std::vector<std::vector<double>> Hy;
	
    enum BoundaryType { PERIODIC, DIRICHLET }; //Opción que permite implementar dos tipos de condiciones de frontera 
    BoundaryType boundaryType; 
    
    Fields(int N, BoundaryType bType = DIRICHLET); //Esta opción debe cambiarse dependiendo de la condición
  

    void initialConditions(int N, double dz);
    void stepFields(double beta, int N);
    void boundaryConditions(double beta, int N);
    void fieldsUpdate(int N);
};

//Clase ComputeFields implementa las formulas de actualización de Maxwell y se implementa el solver de FDTD/
class ComputeFields {
public:
    Grid grid;
    Fields fields;
    double beta;

    ComputeFields(int N, double dz, double beta_);
	
    void run(int steps, int saveEvery);
    void save(const std::string& filename, int step);
};


