#include <vector>
#include <string>
#include <cmath>

using namespace std;

class OndaEM {
private:
    int nz;                 // Número de puntos en la dirección z
    int nz_hy; 
    double dz;              // Espaciado espacial
    double dt;              // Paso temporal
    double nt;              // Número total de pasos temporales
    double beta;            // Parámetro de estabilidad (c*dt/dz)
    vector<vector<double>> Ex; // Ex[z][t]
    vector<vector<double>> Hy; // Hy[z][t]
    int boundary_type;      // Tipo de condición de frontera (0: periódica, 1: fija)

public:
    OndaEM(int nz, double dz, double dt, double nt, int boundary_type = 0);
    void Inicialization();
    void update();
    void outputToFile(const string& filename) const;
};
