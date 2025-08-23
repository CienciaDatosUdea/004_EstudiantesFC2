#include <cmath>
#include <vector>
#include <ostream>
#include <iostream>
#include "../include/fdtd.h"

int main(){
    double l0 = 0.0;
    double lf = 1.0;
    int Num_nodes_1 = 13;
    double Delta_1 = 0.1;

    Linspace linspace1(l0, lf, Num_nodes_1);
    Linspace linspace2(l0, lf, Delta_1);

    linspace1.print();
    linspace2.print();


    return 0;
}
