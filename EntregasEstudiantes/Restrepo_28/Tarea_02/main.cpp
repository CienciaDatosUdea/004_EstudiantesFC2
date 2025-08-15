#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>
#include "difusion_model.h"

using std::cout;
using std::cin;

int main(int argc,char* argv[]){
    //Flag processing
    bool returnGif = false;
    std::string output_filename = "solution.txt";
    for(int i=1;i<argc;i++){
        std::string arg = argv[i];
        if(arg == "-g" || arg=="--gif"){
            returnGif = true;
            continue;
        }
        else if(arg == "-o"||arg=="--output"){
            if(i+1<argc){
                output_filename = argv[++i];
            }
            else{
                std::cerr << "Error: " << arg << " requiere un nombre de archivo.\n";
                return 1; // Indicate an error
            }
        }
    }

    size_t lastindex = output_filename.find_last_of("."); 
    std::string noextension_output = output_filename.substr(0, lastindex); 

    int N;
    double xmin,xmax,dt,tmax,D;
    double a;
    do{
        cout<<"Digite: Número de puntos espaciales (N),  x inicial,  x final,  tiempo de simulación (tmax),  espaciado temporal infinitesimal (dt)   y coeficiente de difusión (D)\n";
        cin>>N>>xmin>>xmax>>tmax>>dt>>D;

        double dx = (xmax-xmin)/(N-1);
        a = D*dt/(dx*dx);
        if(a>0.5){
            cout<<"D*dt/dx^2="<<a<<". Asegurese que D*dt/dx^2 <= 0.5\n";
        }
    }
    while(a>0.5);
    cout<<"Resolviendo...\n";

    //Parámetros para la gaussiana como condición inicial
    double x0 = (xmax-xmin)/2; //centro
    double sigma = 1.0;
    
    Writer defaultSave("final_"+output_filename);
    Geometry G(N,xmin,xmax);
    Conditions C(G);
    C.initialConditions([x0,sigma](double x){return exp(-pow((x-x0),2)/(sigma*sigma));});

    C.boundaryConditions(0.0);
    
    Solver S(C);

    if(returnGif){
        Writer gifSave("full_"+output_filename);

        S.run(tmax,dt,D,&gifSave);

        std::string command = "gnuplot -e \"set terminal gif animate delay 4 font 'arial' 14 size 800,600;set output '"+noextension_output+".gif';stats 'full_"+output_filename+"' name 'STATS' nooutput;set yrange[0:STATS_max_y];set xlabel 'x';set ylabel 'Temp';set xtics nomirror;do for [i=0:int(STATS_blocks)-2]{plot 'full_"+output_filename+"' index i w lines lc 7 lw 2 notitle};unset output\"";

        system(command.c_str());
        cout<<"gif guardado como "<<noextension_output<<".gif\n";
        cout<<"Datos de la simulación completa en full_"<<output_filename<<"\n";
    }
    else{
        S.run(tmax,dt,D);
    }

    defaultSave.writeSolution(S);
    cout<<"Solución final guardada en final_"<<output_filename<<"\n";

    return 0;
}