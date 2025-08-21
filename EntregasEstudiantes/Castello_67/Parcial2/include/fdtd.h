#ifndef FDTD_H
#define FDTD_H

#include <vector>
#include <string>

class Linspace{
    public:
        double l0;
        double lf;
        int Num_nodes;
        double Delta;
        std::vector<double> pos;

        Linspace(double l0 , double lf, int Num_nodes);
        Linspace(double l0 , double lf, double Delta);
        void print(); 
};
// ---------------------------------------------------------------------------------
class Lee_Net{
    public:
        int Num_nodes;
        double Delta;
  

        std::vector<std::vector<double>> E;
        std::vector<std::vector<double>> H;

        Lee_Net(int Num_nodes, double E0 , double H0 );  
        void Integrate(double Integration_time, double DeltaT , const std::string &boundary_cond, const std::string &filename ,const bool test); 
        void print();
};



#endif // FDTD_H