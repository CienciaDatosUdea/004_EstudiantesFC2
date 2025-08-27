#include <cstdio>
#include <iostream>
#include <vector>

//Que?
class Geometria{
    public:
        Geometria(int N,double xmin, double xmax );
        int N;
        double dx, xmin, xmax;       
        std::vector<double> x;
};

class Condiciones{
    public:  
        Condiciones(Geometria &G);
        Geometria G; 
        std::vector <double> u;              // Inicializar temperaturas
        double alpha;                        // Coeficiente de difusión

        void condicionesIniciales();         // Metodo
        void condicionesFrontera();          // Metodo
        void evolucionar(int pasosTiempo);   // Evolución temporal de la temperatura

};



