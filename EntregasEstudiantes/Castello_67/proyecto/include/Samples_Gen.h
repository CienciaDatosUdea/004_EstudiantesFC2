#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <stdexcept>

void print_vector_int(const std::vector<int>& v, std::ofstream& ofs);
class microstate{
    public:
        int L;                                              // Tamaño del sistema
        int N;                                          // Número de partículas (N = L*L)
        double E;                                                 // Energia del microestado
        double M;                                                 // Magnetizacion del microestado
        std::vector<int> S;                                    // Configuracion del microestado

        microstate(int L);
        void calc_E();
        void calc_M();
        void flip(int index);
        void send_to_file(std::ofstream &file);
};
class Samples{
    public:
        int L;                                              // Tamaño del sistema
        int N ;                                          // Número de partículas (N = L*L)
        double T;                                               // Temperatura
        int Num_Samples;                                        // Número de muestras Monte Carlo
        std::vector<double> Energies;                           // Vector de energias
        std::vector<double> Magnetization;                      // Vector de magnetizaciones

        Samples(int L , int Num_Samples);
        void Generate(double T , double Tc_seed);
};  

