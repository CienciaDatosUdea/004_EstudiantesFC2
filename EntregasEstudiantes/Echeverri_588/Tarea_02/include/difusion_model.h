#include <vector>
#include <string>

// Clase que define la geometría del problema
class Geometria {
public:
    Geometria(int N, double xmin, double xmax);
    int N;              // número de puntos en la malla
    double dx;          // tamaño de paso espacial
    double xmin, xmax;  // límites del dominio
    std::vector<double> x; // posiciones espaciales
};

// Clase que define las condiciones iniciales y de frontera
class Condiciones {
public:
    Condiciones(Geometria &geo);
    Geometria &G;           // referencia a la geometría
    std::vector<double> u;  // vector de temperaturas

    // Condición inicial gaussiana
    void condicionesIniciales(double alpha, double x0);

    // Condiciones de frontera Dirichlet
    void condicionesFrontera(double TL, double TR);
};

// Clase que implementa el solucionador de difusión
class DiffusionSolver {
public:
    DiffusionSolver(double D, double dt, double t_max);

    double D;      // coeficiente de difusión
    double dt;     // paso temporal
    double t_max;  // tiempo máximo de simulación

    // Resolver con FTCS
    void resolverFTCS(Condiciones &cond, double TL, double TR);

    // Verificar criterio de estabilidad
    bool verificarEstabilidad(double dx) const;
};

// Guardar resultados en archivo
void guardarResultado(const Geometria &geo, const Condiciones &cond, const std::string &nombreArchivo);
