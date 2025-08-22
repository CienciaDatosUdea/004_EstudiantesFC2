#include <vector>
#include <string>

class Campos {
private:
    int xmax;             // número de nodos espaciales
    double c;             // velocidad de la luz
    double dz;            // paso espacial
    double dt;            // paso temporal
    double beta;          // coeficiente de Courant

    double lambda;        // longitud de onda
    double T;             // periodo
    int nsteps;           // pasos temporales
    int decim;            // factor de decimación

    std::vector<std::vector<double>> Ex;
    std::vector<std::vector<double>> Hy;

public:
    Campos(int xmax = 200, double c = 1.0, double dz = 1.0,
           double lambda = 100.0, int decim = 5);

    void inicializar();
    void simular(const std::string &filename);
};


