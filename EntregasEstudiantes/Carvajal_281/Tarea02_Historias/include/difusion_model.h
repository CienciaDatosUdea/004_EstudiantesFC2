/*Este .h permite declarar las funciones de la implementación del modelo de difusión en la tarea 02 de Historias */


#include <cstdio>
#include <iostream>
#include <vector>


/*Historia 1: Construcción del dominio espacial: 
Esta es la clase que construye la malla 1D desde xmin a xmax.
Calcula el espaciamiento dx y almacena x[i] */ 
class Geometria{
    public:
        Geometria(int N,double xmin, double xmax );
        int N; //N es el numero de puntos espaciales en la malla uniforme
        double dx, xmin, xmax;       //Espaciado de la malla y limites del dominio
        std::vector<double> x;
};


//Historias 2,3 y 4: Clase para las condiciones iniciales
class Condiciones{
    public:  
        Condiciones(Geometria &G);
        Geometria G; 
        std::vector <double> u;      //Inicializar un vector con las temperaturas
        void condicionesIniciales(); //Metodo que aplica las condiciones iniciales gaussianas
        void condicionesFronteraDirichlet(); //Metodo que aplica las condiciones de Frontera de Dirichlet
        void condicionesFronteraNeumann(); //Método opcional que aplica las condiciones de frontera de Neumann 

};

/*Historias 5,6 y 7: Clase que resuelve la ecuación de difusión 1D usando el método FTCS  
* Se implementa el esquema de FTCS 
* Se hace uso de la clase Geometría y las condiciones como entradas de la clase 
* Se aplican las condiciones de frontera en cada paso 
*/
class DiffusionSolver {
public:
    Condiciones& field;  //referenciamos las condiciones y geometria
    double D, dt, t_max;

    DiffusionSolver(Condiciones& field, double D, double dt, double t_max);

    void run();  //Historia 7: aplica las condiciones de frontera en cada paso 
    void step(); //Ejecuta el esquema FTCS
};
