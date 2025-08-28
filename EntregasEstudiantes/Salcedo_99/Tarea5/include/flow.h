#ifndef FLOW_H
#define FLOW_H

#include <vector>
#include <string>

class Grid {
public:
    int nx, ny;
    double xmin, xmax, ymin, ymax;
    double dx, dy;

    Grid(double xmin_, double xmax_, double ymin_, double ymax_, int nx_, int ny_);
};

class CampoVelocidadesPresion {
public:
    Grid &G;
    std::vector<std::vector<double>> u, v, p, b;

    CampoVelocidadesPresion(Grid &grid);

    void CondicionesIniciales();
    void BoundaryCondition();
};

class ComputePresion {
public:
    CampoVelocidadesPresion &Campo;
    double rho, dt;
    int nit;

    ComputePresion(CampoVelocidadesPresion &campo, double rho_, double dt_, int nit_);

    void buildUpB();
    void presionUpdate();
};

class ComputeCampo {
public:
    ComputePresion &Presion;

    ComputeCampo(ComputePresion &presion);

    void velocidadesUpdate();
};

class FieldWriter {
    std::string filename;

public:
    FieldWriter(const std::string &fname);
    void writePosicionCampo(const Grid &G, const CampoVelocidadesPresion &Campo);
};

#endif
