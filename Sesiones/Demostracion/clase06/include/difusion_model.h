#include <cstdio>
#include <iostream>

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
        std::vector <double> u;      //Inicializar
        void condicionesIniciales(); //Metodo
        void condicionesFrontera(); //Metodo

};



