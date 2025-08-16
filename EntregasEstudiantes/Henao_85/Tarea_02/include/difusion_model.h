#include <vector>
#include <string>
#include <iostream>


class Geometria {
    public:
        Geometria(int N, double xmin, double xmax);
        int N;
        double dx, xmin, xmax;
        std::vector<double> x; // posiciones espaciales
};


class Condiciones {
    public:
        Condiciones(Geometria &geo);
        Geometria &G; // referencia a la geometría
        std::vector<double> u; // vector de temperaturas

        // Condición inicial 
        void condicionesIniciales(double alpha, double x0);

        // RF3 y RF5: condiciones de frontera Dirichlet
        void condicionesFrontera(double TL, double TR);
};


class DiffusionSolver {
    public:
        DiffusionSolver(double D, double dt, double t_max);

        double D;      // coeficiente de difusión
        double dt;     // paso temporal
        double t_max;  // tiempo máximo de simulación

        // Resolver usando FTCS
        void resolverFTCS(Condiciones &cond, double TL, double TR);

        // Verificar estabilidad
        bool verificarEstabilidad(double dx) const;
};


void guardarResultado(const Geometria &geo, const Condiciones &cond, const std::string &nombreArchivo);






