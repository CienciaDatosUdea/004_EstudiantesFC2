#ifndef SAMPLES_GEN_H
#define SAMPLES_GEN_H

#define _USE_MATH_DEFINES
#include "../include/Samples_Gen.h"
#include "../include/Canonical.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>
#include <random>
#include <chrono>
#include <iomanip> 
#include <omp.h>

// Semillas --------------------------------------------------------------------------------------------------------------------------------
std::random_device rd;
std::mt19937 gen(rd());

// Definir la distribución uniforme en un rango [min, max]:
std::uniform_int_distribution<int> dist_01(0,1);
std::uniform_real_distribution<double> probability_distribution(0.0, 1.0);

// Archivo donde se guardan los microestados para el modelo 6x6
std::string microstates_file = "Ising6_Data.txt";

//Funcion para imprimir:
void print_vector_int(const std::vector<int>& v, std::ofstream& ofs) {
    for (size_t i = 0; i < v.size(); ++i) {
        ofs << std::setw(2) << v[i];
        if (i + 1 < v.size()) ofs << " ";
    }
}
// Implementacion de la clase microstate ----------------------------------------------------------------------------------------------------------------
microstate::microstate(int L):
L(L),N(L*L)
{
    S.resize(N);
    for(int i = 0; i < N; ++i){
        int val = dist_01(gen);
        S[i] = (val == 0) ? -1 : +1; // Asignar -1 o +1
    }
    calc_E();
    calc_M();   
}
void microstate::calc_E()
{
    double sum = 0.; // Calculamos energia del microestado con condiciones de frontera periodicas
        for (int k = 0 ; k < N ; k++){ 
            int row_start = (k / L) * L;
            int col = k % L;
            int right = row_start + (col + 1) % L;
            int left  = row_start + (col - 1 + L) % L;
            int down  = (k + L) % (L*L);
            int up    = (k - L + L*L) % (L*L);

            sum += - S[k] * (S[left] + S[up] + S[right] + S[down]);
        }
    E = sum * 0.5;
}
void microstate::calc_M()
{
    double sum = 0.;
    for(int i = 0; i < N; ++i){
        sum += S[i];
    }
    M = sum;
}   
void microstate::flip(int index) {
    int old_spin = S[index];
    
    // Calcular vecinos con condiciones periodicas
    int row = index / L;
    int col = index % L;
    
    int left = row * L + (col - 1 + L) % L;
    int right = row * L + (col + 1) % L;
    int up = ((row - 1 + L) % L) * L + col;
    int down = ((row + 1) % L) * L + col;
    
    // Calcular suma de vecinos
    int neighbor_sum = S[left] + S[right] + S[up] + S[down];
    
    // Calcular cambio de energia 
    double deltaE = 2 * old_spin * neighbor_sum;
    
    // Actualizar energia y magnetizacion
    E += deltaE;
    M -= 2 * old_spin;
    
    // Voltear el espin
    S[index] = -old_spin;
}
void microstate::send_to_file(std::ofstream &file)
{
    // Configurar el formato de salida
    file << std::fixed << std::setprecision(6);
    
    // Imprimir el arreglo de spines
    print_vector_int(S,file);
    
    // Imprimir energia y magnetizacion 
    file << " " 
         << std::setw(12) << E  
         << " " 
         << std::setw(12) << M; 
    
    file << "\n";
}
// Implementacion de la clase Samples ----------------------------------------------------------------------------------------------------------------
Samples::Samples(int L , int Num_Samples):
L(L) , N(L*L) , Num_Samples(Num_Samples)
{
    Energies.resize(Num_Samples);
    Magnetization.resize(Num_Samples);
}
void Samples::Generate(double T ,  double Tc_seed) {
    
    std::uniform_int_distribution<int> site_distribution(0, N - 1);

    if (T <= 0) {
        throw std::invalid_argument("La temperatura debe ser mayor que 0");
    }
    
    double beta = 1.0 / (Kb*T);  // Kb = 1
    
    // Inicializar microestado aleatorio
    microstate current_state(L);
    
    // Parametros del algoritmo de Metropolis
    int thermalization_steps = 1000 * N; 
    int steps_between_samples = 100 * N;  
  
    // Burnit
    for (int step = 0; step < thermalization_steps; ++step) {
        int site = site_distribution(gen);
        int old_spin = current_state.S[site];
        
        // Calcular vecinos
        int row = site / L;
        int col = site % L;
        int left = row * L + (col - 1 + L) % L;
        int right = row * L + (col + 1) % L;
        int up = ((row - 1 + L) % L) * L + col;
        int down = ((row + 1) % L) * L + col;
        
        int neighbor_sum = current_state.S[left] + current_state.S[right] + 
                           current_state.S[up] + current_state.S[down];
        
        // Calcular cambio de energia
        double deltaE = 2 * old_spin * neighbor_sum;
        
        // Criterio de Metropolis
        if (deltaE <= 0 || probability_distribution(gen) < std::exp(-beta * deltaE)) {
            current_state.flip(site);
        }
    }
    
    // Muestreo de estados
    std::string dataset_file = "Dataset" + std::to_string(T) +  ".txt";
    std::string output_file = "Ising" + std::to_string(L) + "_T" + std::to_string(T) + "_Samples.txt";

    std::ofstream outfile(output_file);
    std::ofstream outfile2(dataset_file);

    for (int sample = 0; sample < Num_Samples; ++sample) {
        // reducir correlaciones
        for (int step = 0; step < steps_between_samples; ++step) {
            int site = site_distribution(gen);
            int old_spin = current_state.S[site];
            
            // Calcular vecinos
            int row = site / L;
            int col = site % L;
            int left = row * L + (col - 1 + L) % L;
            int right = row * L + (col + 1) % L;
            int up = ((row - 1 + L) % L) * L + col;
            int down = ((row + 1) % L) * L + col;
            
            int neighbor_sum = current_state.S[left] + current_state.S[right] + 
                               current_state.S[up] + current_state.S[down];
            
            // Calcular cambio de energia
            double deltaE = 2 * old_spin * neighbor_sum;
            
            // Criterio de Metropolis
            if (deltaE <= 0 || probability_distribution(gen) < std::exp(-beta * deltaE)) {
                current_state.flip(site);
            }
        }
        
        // Guardar el estado actual
        Energies[sample] = current_state.E;
        Magnetization[sample] = current_state.M;
        current_state.send_to_file(outfile);

        int label = (T < Tc_seed) ? 0 : 1; 
        print_vector_int(current_state.S , outfile2);
        outfile2 << " " << std::setw(12) << std::setw(12) << label; 
        outfile2 << "\n";
    }    
    outfile.close();
    outfile2.close();
}

#endif