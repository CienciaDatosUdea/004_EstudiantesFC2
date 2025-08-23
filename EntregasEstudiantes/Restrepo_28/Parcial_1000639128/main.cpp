#include <iostream>
#include <cmath>
#include <string>
#include "fdtd.hpp"

using namespace std;

int main(int argc,char* argv[]){
    //procesamiento del input
    std::string output_filename = "data.txt";
    std::string bc_type = "periodic"; // Default boundary condition
    bool visualize = false;
    double dz = 0.005;
    double dt = .02;
    int K = 200;
    int N = 250; //Correspondiente a 5seg con dt default
    double C = 0.1;
    for(int i=1;i<argc;i++){
        std::string arg = argv[i];
        if(arg == "-o"||arg=="--output"){
            if(i+1<argc){
                output_filename = argv[++i];
            }
            else{
                std::cerr << "Error: " << arg << " requiere un nombre de archivo.\n";
                return 1; // Indicate an error
            }
        }
        else if(arg == "-p"||arg=="--params"){
            if(i+5<argc){
                dz = std::stod(argv[i+1]);
                dt = std::stod(argv[i+2]);
                K = std::stoi(argv[i+3]);
                N = std::stoi(argv[i+4]);
                C = std::stod(argv[i+5]);
            }
            else{
                std::cerr << "Error: " << arg << " requiere cinco parámetros.\n";
                return 1; // Indicate an error
            }
        }
        else if(arg == "-bc"||arg=="--boundary-condition"){
            if(i+1<argc){
                bc_type = argv[++i];
            }
            else{
                std::cerr << "Error: " << arg << " requiere un tipo de frontera.\n";
                return 1; // Indicate an error
            }
        }
        else if(arg == "-v"||arg=="--visualize"){
            visualize = true;
        }
    }

    Grid G(dz,dt,K,N);
    Fields F(G,C,bc_type);
    Writer w(output_filename);
    F.run_simulation(&w);
    w.file.close();

    //Graficado
    if(visualize){
        std::string command = "python3 python/sim_fdtd.py " + output_filename + " " + std::to_string(dz) + " " + std::to_string(dt) + " " + std::to_string(K); //el script de python sólo requiere estos parámetros
        system(command.c_str());
        std::cout<<"gif guardado en EMWave.gif\n";
    }

    return 0;
}