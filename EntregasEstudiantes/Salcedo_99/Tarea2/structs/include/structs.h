#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <vector>
#include <random>
#include <cmath>

// Constants
const int N = 10;
const double R = 1.0;
const double DELTA = 0.1;

// Global random number generator
extern std::mt19937 gen;

// Partícula (como estructura)
struct Particula {
    double x, y;   // Posición
    double Fx, Fy; // Fuerzas

    Particula();

    void initPosition(double R);
    void pertPosition(double dx, double dy);
};

// Sistema (como estructura)
struct Sistema {
    std::vector<Particula> p;

    Sistema(int N);

    void initAll(double R);
    void pertAll(double delta);
    void distMax() const;
    void initForces();
    void netForce() const;

    Particula& operator[](int i);
};

#endif
