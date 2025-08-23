#include<iostream>
#include<cmath>
#include<vector>
#include "include/Heat1d.h"

// Main -------------------------------------------------------------------------------------------------------------------------------------
int main(){
    double alpha = 1;
    int N = 100;
    double L = 1;
    double Max_U  = 100;
    double sigma = 0.1;
    double t_f = 0.5;
     
    Heat1d MyHeat(alpha , N ,  L ,  Max_U ,  sigma ,  true);
    MyHeat.Integrate(t_f , "Gaussian_Solution.txt");
    return 0;
}