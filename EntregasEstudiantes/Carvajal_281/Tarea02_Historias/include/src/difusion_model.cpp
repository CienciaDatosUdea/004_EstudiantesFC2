/*Este .cpp trabaja con las funciones declaradas en el .h que tiene el mismo nombre - tarea 02 Historias */


# include <cstdio>
# include <iostream>
#include <cmath>
# include "difusion_model.h"

/* Historia 1: Construcción de la clase Grid 
se define una malla 1D uniforme con N puntos. 
Se calcula un espaciamiento dx, y con base en este se llena el vector x[i] con las posiciones espaciales desde xmin hasta xmax.*/
Geometria::Geometria(int N_,double xmin_, double xmax_ )
    : N(N_), xmin(xmin_), xmax(xmax_)
    {
        x.resize(N);
        dx = (xmax-xmin)/(N-1);
        for(int i=0;i<N;i++){
            x[i]=xmin+i*dx;
        }
};

// Historia 2: Aplicar las condiciones iniciales y de frontera de la malla
Condiciones::Condiciones(Geometria &G_):
    G(G_), u(G_.N, 0.0) {};

// Implementación de condición inicial de tipo gaussiana centrada en el dominio
void  Condiciones::condicionesIniciales(){
	 double alpha = 50.0;         // Ancho de la gaussiana
    	double L = G.xmax - G.xmin;  // longitud total del dominio
    	double x0 = L / 2.0;        // centro del dominio 

   	for (int i = 0; i < G.N; i++) {
        	double x = i * G.dx;  // posición en la malla
        	u[i] = exp(-alpha * pow(x - x0, 2));   //valor de la gaussiana en esa posición
    }
}

//Historia 3 : Condiciones de frontera de Dirichlet, donde los extremos están en contacto con un baño térmico a 0K
void  Condiciones::condicionesFronteraDirichlet(){
    u[0]=0;
    u[G.N-1]=0;
}


// Historia 4 (Opcional):  Condiciones de frontera de Neumann donde los bordes son aislados térmicamente
void Condiciones::condicionesFronteraNeumann() {
    /* Igualar el valor de cada borde al de su vecino interior inmediato
       , esto impone que no haya flujo de calor en los extremos */
    u[0] = u[1];
    u[G.N - 1] = u[G.N - 2];
}


/* Historia 5: Implementación del esquema FTCS: Implementación del método explicito FTCS en una clase para calcular la evolución temporal de la temperatura 


En este caso se cumple tambien la historia 6, que indica que solver debe implementar la geometría y condiciones de entrada ya definidas*/ 

DiffusionSolver::DiffusionSolver(Condiciones &field_, double D_, double dt_, double t_max_)
    : field(field_), D(D_), dt(dt_), t_max(t_max_) {}

// Ejecutar el solver
void DiffusionSolver::run() {

    double alpha = D * dt / (field.G.dx * field.G.dx);

    // Historia RF10:  Verificar condición de estabilidad FTCS
    if (alpha > 0.5) {
     std::cerr << "Importante: El esquema FTCS puede ser inestable (alpha ="<<alpha << " > 0.5)" << std::endl;
    }
 
    int steps = static_cast<int>(t_max / dt);
    for (int n = 0; n < steps; ++n) {
        field.condicionesFronteraDirichlet(); //Historia 7.
        step(); //Historia 5 
    }
}

void DiffusionSolver::step() {
    //Creamos un vector que almacena las evoluciones temporales de la temperatura
    std::vector<double> u_new(field.G.N);
    //Calculamos el número de Courant que controla la estabilidad del método FTCS
    double alpha = D * dt / (field.G.dx * field.G.dx);


    /* Hacemos un ciclo para aplicar la formúla explicita FTCS de la ecuación de difusión, en este paso se calcula la evolución temporal de la temperatura*/ 
    for (int i = 1; i < field.G.N - 1; ++i) {
        u_new[i] = field.u[i] + alpha * (field.u[i + 1] - 2 * field.u[i] + field.u[i - 1]);
    }
    
    //Actualizamos el campo de temperatura con los valores recien calculados	
    field.u = u_new;

    // Aplicar condiciones de frontera ya definidas en Condiciones 
    field.condicionesFronteraDirichlet();

    
}
