/*Este cpp contiene la implementación de los constructores y métodos declarados en fdtd.h*/

#include <fstream> //Para guardar la información en archivos de texto 
# include <iostream>
#include <cmath>
# include "fdtd.h"


/*Construcción de la clase Grid:
- Se define la malla 1D uniforme con N puntos.
- El espaciamiento entre nodos se define a partir de dz.
- Se calcula el paso temporal dt a partir de la condición de estabilidad de Courant .
- Se llena el vector z[i] con las posiciones espaciales desde 0 hasta (N-1)dz.}

Anotación: Se deja beta explicito como un parámetro que debe definirse, este se espera menor o igual a 0.5 por la condición de estabilidad */
Grid::Grid(int N_, double dz_, double beta_)
    : N(N_), dz(dz_), beta(beta_) 
    {
    dt=beta*dz;  
    z.resize(N); //Construcción del vector para posiciones
    for (int i = 0; i<N; i++){
        z[i] = i * dz;  // malla uniforme desde 0 hasta (N-1)*dz
    }
};

/* Construcción de la clase Fields: 
- Se crean las matrices para definir el campo eléctrico y el campo magnético
- Se definen las condiciones iniciales*/
Fields::Fields(int N, BoundaryType bType): boundaryType(bType) {
    /*La inicialización del campo eléctrico y magnético corresponde a matrices.
   Para cada posición espacial k se guardan dos estados temporales
   - Estado n (0) 
   - Estado n+1 (1) */
    Ex.resize(N, std::vector<double>(2, 0.0));
    Hy.resize(N, std::vector<double>(2, 0.0));
}


void Fields::initialConditions(int N, double dz) {
    /*Para las condiciones iniciales se recorren todos los nodos espaciales y se asigna a todos los valores de las posiciones k en t=0 el valor de campo eléctrico y magnético inicial*/
    for (int k=0; k<N; k++){
        double z= k;
        Ex[k][0]= 0.1*sin(2.0*M_PI*z/100.0); //Campo eléctrico inicial
        Hy[k][0]= 0.1*sin(2.0*M_PI*z/100.0); //Campo magnético inicial
    }
}

void Fields::stepFields(double beta, int N){
    /* En este paso se calculan los valores en n+1 (el estado siguiente) a partir de la relación de actualización. Estas ecuaciones son las que aparecen en el enunciado del parcial. */
	for (int k = 1; k < N-1; k++) {
            Ex[k][1]=Ex[k][0]+beta*(Hy[k-1][0]-Hy[k+1][0]); }

	for (int k = 1; k < N-1; k++) {
            Hy[k][1]=Hy[k][0]+beta *(Ex[k-1][0]-Ex[k+1][0]);
	}}
	    

void Fields::boundaryConditions(double beta, int N) {
    /*Se definen condiciones de frontera periódicas  partir del enunciado del parcial X_max= N (número total de nodos en la malla)*/
      if (boundaryType == PERIODIC) {
        Ex[0][1] = Ex[0][0] + beta*(Hy[N-2][0] - Hy[1][0]);
        Ex[N-1][1] = Ex[N-1][0] + beta*(Hy[N-2][0] - Hy[1][0]);
        Hy[0][1] = Hy[0][0] + beta*(Ex[N-2][0] - Ex[1][0]);
        Hy[N-1][1] = Hy[N-1][0] + beta*(Ex[N-2][0] - Ex[1][0]);
    } else if (boundaryType == DIRICHLET) {
    	//La condición de Dirichlet obliga a que se anule en los extremos
        Ex[0][1] = 0.0;
        Ex[N-1][1] = 0.0;
        Hy[0][1] = 0.0;
        Hy[N-1][1] = 0.0;
    }
}

void Fields::fieldsUpdate(int N){
    /*Esta función actualiza los estados de tal manera que el estado que en el primer ciclo es el nuevo (n+1), se guarde como el estado inicial, esto puede entenderse como el avance temporal, ya que los estados de los campos están evolucionando*/
    for (int k = 0; k < N; k++){
        Ex[k][0] = Ex[k][1];
        Hy[k][0] = Hy[k][1];
    }
}

/*Construcción de la clase ComputeFields: En esta clase se implementa todo lo que armamos en las clases anteriores y tiene como objetivo correr la simulación. 
- Se inicializan la malla y los campos.
- Luego ejecuta la evolución del sistema durante el número de pasos dado.
- Cada cierto número de iteraciones (que fijdamos en cada 10) se genera un archivo de texto con los valores de los campos en ese instante.
   - El método guardar (saveData) se encarga de escribir esos estados y almacenarlos en el equipo para tener un registro de la evolución.
*/
ComputeFields::ComputeFields(int N, double dz, double beta)
    : grid(N, dz, beta), fields(N) {    
    fields.initialConditions(grid.N, grid.dz);}

void ComputeFields::run(int steps, int saveEvery) {

     {std::ofstream clearFile("campos.txt", std::ios::trunc);
     clearFile.close();
    }

    for (int n = 0; n < steps; n++) {
        fields.stepFields(grid.beta, grid.N);
        fields.boundaryConditions(grid.beta, grid.N);
        
        fields.fieldsUpdate(grid.N);
        if (n % saveEvery == 0) {
            save("campos_B0.01Dirichlet.txt", n); //Aqui se define el filename
        }
    }
}

void ComputeFields::save(const std::string& filename, int step) {
    std::ofstream file(filename, std::ios::app); // modo append

	
    for (int k = 0; k < grid.N; k++) {
	file << step << " " << k << " " << fields.Ex[k][0] << " "
	<<fields.Hy[k][0] << "\n";
    }
    file << "\n";
    file.close();
}





