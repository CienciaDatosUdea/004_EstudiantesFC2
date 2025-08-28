#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <fstream>

struct GridBin;

struct Particle{
    double x,y;
    double vx,vy;
    double fx, fy;
    double m;

    Particle(double x,double y,double vx,double vy,double m = 1.0);
    void update(float dt,GridBin &grid, double r_cut);
    void applyForces(GridBin &grid, double r_cut);
    double getKinetic();
    double getPotential(GridBin &grid,double r_cut);
};

struct GridBin{
    int rows, cols, binSize;
    std::vector<std::vector<std::vector<Particle*>>> bins;

    GridBin(int r, int c, int b);
    void clear();
    void insert(Particle* p);
    std::vector<Particle*> getNeighbors(Particle* p,float radius);

    // GridBin(int r, int c, int b);
};

struct System{
    std::vector<Particle> particles;
    int N;
    GridBin grid;
    double T;
    double m;
    double kb;
    double r_cut;

    System(int N,  GridBin & grid, double T, double m, double kb, double r_cut);
    void update(double dt, std::ofstream *file = nullptr);
    double getEnergy();
    double getTemperature();
    void rescaleTemp();

};

void lennardJones(Particle& p1, Particle& p2, float epsilon, float sigma, float cutoff = 5.0f);
void wcaPotential(Particle& p1, Particle& p2, double epsilon, double sigma);
void lennardJonesWithLimit(Particle& p1, Particle& p2, double epsilon, double sigma, 
                          double cutoff, double max_force = 100.0);
void interact(Particle &p1, Particle &p2);
void gravity(Particle &p1);
void velocity_rescaling(std::vector<Particle>& particles, double target_T,const float KB = 1.0f);

// Usage in main loop:
#endif