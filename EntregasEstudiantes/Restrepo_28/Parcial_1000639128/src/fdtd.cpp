#include <cmath>
#include <vector>
#include <iostream>
#include "fdtd.hpp"

Grid::Grid(double dz_, double dt_, int K_, int N_):dz(dz_),dt(dt_), K(K_),N(N_){}


Fields::Fields(Grid &G_,double C_,std::string bc_type_):G(G_),C(C_),bc_type(bc_type_),t0(0.0){
	if(bc_type != "periodic" && bc_type != "dirichlet" && bc_type != "absorbtion"){
		throw std::invalid_argument("Tipo de frontera no soportado: " + bc_type + ". Use: periodic, dirichlet, absorbtion");
	}
	beta = C*G.dt/(G.dz);
	if(beta>=0.5){
		std::cout<<"WARNING: Inestabilidad potencial detectada (beta = "<<beta<<" >= 0.5)"<<std::endl;
	}
	H.resize(G.K,0.0);
	E.resize(G.K,0.0);
	initial_conditions();
}

void Fields::initial_conditions(){
	for(int k =0;k<G.K;k++){
		E[k] = 0.1 * sin(2*M_PI*k/100.0);
		H[k] = 0.1 * sin(2*M_PI*k/100.0);
		//centered gaussian
		// E[k] = 0.2*exp(- pow(k * G.dz - 1.0, 2));
		// H[k] = 0.1*exp(- pow(k * G.dz - 1.0, 2));
	}
}

void Fields::boundary_conditions(std::vector<double> oldE, std::vector<double> oldH){
	//Esto no es óptimo porque está chequeando el condicional cada step
	if(bc_type == "periodic"){
		E[0] = oldE[0] + beta*(H[0] - H[G.K-1]);
		H[G.K-1] = oldH[G.K-1] + beta*(E[0] - E[G.K-1]);
	}
	else if (bc_type == "dirichlet")
	{
		E[0] = 0;
		E[G.K-1] = 0;
		H[G.K -1 ] = 0;
		// H[0] = 0;
	}
	else if (bc_type == "absorbtion")
	{
		E[0] = oldE[1];
		H[G.K-1] = oldH[G.K-2];
	}
	
}

void Fields::update_fields(){
	std::vector<double> oldE = E;
	std::vector<double> oldH = H;
	// for(int k=1;k<G.K-1;k++){ Esta forma presenta inestabilidades
	// 	E[k] = oldE[k] + beta*(oldH[k-1] - oldH[k+1]);
	// 	H[k] = oldH[k] + beta*(oldE[k-1] - oldE[k+1]);
	// }
	boundary_conditions(oldE,oldH);
	    // Update H field (half step)
    for(int k=0; k<G.K-1; k++){
        H[k] = oldH[k] + beta * (E[k+1] - E[k]);
    }
    // Update E field (full step)
    for(int k=1; k<G.K; k++){
        E[k] = oldE[k] + beta * (H[k] - H[k-1]);
    }
	t0 += G.dt; //actualiza el tiempo actual
}

void Fields::run_simulation(Writer* writer){
	for(int i = 0;i<G.N;i++){
		if (writer){
			writer->writeFields(*this);
		}
		update_fields();
	}
}

Writer::Writer(const std::string &filename_){
    file.open(filename_);
    if (!file.is_open()){
        throw std::runtime_error("No se pudo abrir el archivo: " + filename_);}
        // file << std::fixed << std::setprecision(6);
        file << "# z\t E\t H\n";

};

void Writer::writeFields(const Fields &F){
    file<<"#t = "<<F.t0<<"\n";
    for(int i=0;i<F.G.K;i++){
        file<<i*F.G.dz<<"\t"<<F.E[i]<<"\t"<<F.H[i]<<"\n";
    }
    file<<"\n\n";//Dos espacios en blanco para poder ser leído correcctamente por gnuplot
};


