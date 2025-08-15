#define _USE_MATH_DEFINES
#include <cstdlib> 
#include <iostream>
#include <cmath>
#include <random>
using namespace std;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<double> dist_r(0., 1.);
std::uniform_real_distribution<double> dist_F(0., 1.);
std::uniform_real_distribution<double> dist_theta(0., 2.*M_PI);

struct Particles{
    int N;
    double** r;
    double** F;

    double Get_Distance(int i , int j);
    double Get_FMod(int i);
    double* Get_i(int i);
    double* GetF_i(int i);
    void Perturbate(double Delta);
    double Get_Min();
    double Get_Ftotal();
};


//Main---------------------------------------------------------------------------------------------
int main(){
    int N;
    double Delta;
    cout << "Ingrese el numero de particulas: " << endl; cin >> N;
    if (N <= 1 || floor(N)!=N){
        cout << "Ingreso un valor invalido!! Saliendo del programa " << endl;
        exit(1);
    }
    cout << "Ingrese el tamano del intervalo de perturbacion del sistema: " << endl; cin >> Delta;

    //Inicializacion de la estructura
    double** r = new double *[N];           // Reservar espacio para las filas
    for (int i = 0 ; i < N ; i++){
        r[i] = new double[2];            // Reservar espacio para las columnas
    }
    double** F = new double *[N];       // Reservar espacio para las filas
    for (int i = 0 ; i < N ; i++){
        F[i] = new double[2];        // Reservar espacio para las columnas
    }  
    //Generar particulas
    for (int i = 0; i < N; ++i){
        r[i][0] = dist_r(gen)*cos(dist_theta(gen));
        r[i][1] = dist_r(gen)*sin(dist_theta(gen));       
    }
    //Generar Fuerzas
    for (int i = 0; i < N; ++i){
        F[i][0] = dist_F(gen);
        F[i][1] = dist_F(gen);       
    }

    Particles MyParticles{N,r,F};

    cout << "Ejectuando perturbacion: " << endl;
    MyParticles.Perturbate(Delta);
    cout << "Distancia minima entre particulas: " << MyParticles.Get_Min() << endl;
    cout << "La fuerza total en el sistema es: " << MyParticles.Get_Ftotal() << endl;
    cout << "FIN---------------------------------" << endl;
    
    return 0;
}

//Implementations-----------------------------------------------------------------------------------
double Particles::Get_Distance(int i , int j){
    double x_i = Get_i(i)[0];
    double y_i = Get_i(i)[1];
    double x_j = Get_i(j)[0];
    double y_j = Get_i(j)[1];
    return sqrt(pow(x_i-x_j,2) + pow(y_i-y_j,2));
}
double Particles::Get_FMod(int i){
    double F0 = GetF_i(i)[0];
    double F1 = GetF_i(i)[1];
    return sqrt(F0*F0 + F1*F1);
}
double* Particles::Get_i(int i){
    if(i >= N || i < 0 || floor(i) != i){
        cout << "Indice no valido!" << endl;
        exit(1);
    }
    //cout << "[" << *r[0] << "," <<  *r[1] <<"]"<< endl;
    return r[i];
}
double* Particles::GetF_i(int i){
    if(i >= N || i < 0 || floor(i) != i){
        cout << "Indice no valido!" << endl;
        exit(1);
    }
    //cout << "[" << *F[0] << "," <<  *F[1] <<"]"<< endl;
    return F[i];
}
void Particles::Perturbate(double Delta){
    std::uniform_real_distribution<double> dist_Delta(-Delta, Delta);
    for (int i = 0; i < N; ++i){
        r[i][0] += dist_Delta(gen);
        r[i][1] += dist_Delta(gen);       
    }
}
double Particles::Get_Min(){
    if(N < 2) return 0.;
    double min_d = Get_Distance(0,1);
    int p1,p2 = 0;
    for(int i = 0; i < N; ++i){
        for(int j = i+1; j < N; ++j){
            double d = Get_Distance(i,j);
            if(d < min_d){ min_d = d; p1 = i ; p2 = j;}
        }
    }
    cout << "Las particulas: " << "[" << p1 << "] y " << "[" << p2 << "] , tienen distancia minima:" << endl;
    return min_d;
}
double Particles::Get_Ftotal(){
    double sum = 0.;
    for(int i = 0 ; i<N ; i++){
        sum += Get_FMod(i);
    }
    return sum;
}