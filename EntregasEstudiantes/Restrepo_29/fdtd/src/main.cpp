#include "fdtd.h"
#include <iostream>
using namespace std;

int main() {
    cout << "Elija condiciones de frontera:1 => periodicas, 2 => nulas): ";
    int opcion;
    cin >> opcion;

    if (opcion == 1) {
        simular("campos.csv", true);
    } else {
        simular("campos.csv", false);
    }

    return 0;
}