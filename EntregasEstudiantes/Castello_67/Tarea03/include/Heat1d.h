#include<iostream>
#include<fstream>
#include<string>
#include<cmath>
#include<vector>

class Heat1d{
    private:
        double alpha;                    // Constate difusion calor
        int N;                          // Numero de particion del intervalo
        double L;                      // Longitud de la barra
        double h;                     // Elemento de incremento longitudinal
        double U0_x0;                // Valor de la Temperatura, en t = 0  en el extremo inicial del hilo
        double U0_xf;               // Valor de la Temperatura, en t = 0  en el extremo final del hilo
        std::vector<double> Sol;   // Arreglo donde se guardara la solucion en cada punto

    public:
        Heat1d(double alpha , int N , double L , double U0_x0 , double U0_xf);
        Heat1d(double alpha , int N , double L , double Max_U , double sigma ,  bool gaussian );
        void Integrate(double t_f , const std::string &filename);
        void print_sol();
    
    private:
        void save_sol(const std::string &filename);   
};