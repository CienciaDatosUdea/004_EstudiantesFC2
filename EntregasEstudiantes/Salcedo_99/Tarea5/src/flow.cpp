#include "../include/flow.h"
#include <fstream>
#include <iomanip>
#include <cmath>
#include <iostream>

// ---------------- GRID ----------------
Grid::Grid(double xmin_, double xmax_, double ymin_, double ymax_, int nx_, int ny_)
    : nx(nx_), ny(ny_), xmin(xmin_), xmax(xmax_), ymin(ymin_), ymax(ymax_) {
    dx = (xmax - xmin) / (nx - 1);
    dy = (ymax - ymin) / (ny - 1);
}

// ---------------- CAMPOS ----------------
CampoVelocidadesPresion::CampoVelocidadesPresion(Grid &grid) : G(grid) {
    u.assign(G.ny, std::vector<double>(G.nx, 0.0));
    v.assign(G.ny, std::vector<double>(G.nx, 0.0));
    p.assign(G.ny, std::vector<double>(G.nx, 0.0));
    b.assign(G.ny, std::vector<double>(G.nx, 0.0));
}

void CampoVelocidadesPresion::CondicionesIniciales() {
    for (int j = 0; j < G.ny; j++) {
        for (int i = 0; i < G.nx; i++) {
            u[j][i] = 0.0;
            v[j][i] = 0.0;
            p[j][i] = 0.0;
            b[j][i] = 0.0;
        }
    }
}

void CampoVelocidadesPresion::BoundaryCondition() {
    // Canal: no slip en paredes, velocidad en entrada
    for (int j = 0; j < G.ny; j++) {
        u[j][0] = 1.0;   // entrada
        u[j][G.nx-1] = u[j][G.nx-2]; // salida Neumann
        v[j][0] = 0.0;
        v[j][G.nx-1] = 0.0;
    }

    for (int i = 0; i < G.nx; i++) {
        u[0][i] = 0.0;   // pared inferior
        u[G.ny-1][i] = 0.0; // pared superior
        v[0][i] = 0.0;
        v[G.ny-1][i] = 0.0;
    }
}

// ---------------- PRESION ----------------
ComputePresion::ComputePresion(CampoVelocidadesPresion &campo, double rho_, double dt_, int nit_)
    : Campo(campo), rho(rho_), dt(dt_), nit(nit_) {}

void ComputePresion::buildUpB() {
    double dx = Campo.G.dx;
    double dy = Campo.G.dy;

    for (int j = 1; j < Campo.G.ny - 1; j++) {
        for (int i = 1; i < Campo.G.nx - 1; i++) {
            double dudx = (Campo.u[j][i+1] - Campo.u[j][i-1]) / (2.0*dx);
            double dvdy = (Campo.v[j+1][i] - Campo.v[j-1][i]) / (2.0*dy);

            double term1 = dudx + dvdy;

            double dudx2 = std::pow((Campo.u[j][i+1] - Campo.u[j][i-1])/(2.0*dx),2);
            double dvdy2 = std::pow((Campo.v[j+1][i] - Campo.v[j-1][i])/(2.0*dy),2);
            double dudydvdx = ( (Campo.u[j+1][i]-Campo.u[j-1][i])/(2.0*dy) ) *
                              ( (Campo.v[j][i+1]-Campo.v[j][i-1])/(2.0*dx) );

            Campo.b[j][i] = rho*(1.0/dt*term1 - dudx2 - 2.0*dudydvdx - dvdy2);
        }
    }
}

void ComputePresion::presionUpdate() {
    double dx = Campo.G.dx;
    double dy = Campo.G.dy;

    buildUpB();

    for (int q = 0; q < nit; q++) {
        std::vector<std::vector<double>> pn = Campo.p;

        for (int j = 1; j < Campo.G.ny-1; j++) {
            for (int i = 1; i < Campo.G.nx-1; i++) {
                Campo.p[j][i] = ((pn[j][i+1] + pn[j][i-1])*dy*dy +
                                (pn[j+1][i] + pn[j-1][i])*dx*dx) /
                                (2.0*(dx*dx + dy*dy))
                                - dx*dx*dy*dy/(2.0*(dx*dx+dy*dy)) * Campo.b[j][i];
            }
        }

        // Boundary conditions for pressure
        for (int j = 0; j < Campo.G.ny; j++) {
            Campo.p[j][Campo.G.nx-1] = Campo.p[j][Campo.G.nx-2]; // salida
            Campo.p[j][0] = Campo.p[j][1];                       // entrada
        }
        for (int i = 0; i < Campo.G.nx; i++) {
            Campo.p[0][i] = Campo.p[1][i];                       // pared
            Campo.p[Campo.G.ny-1][i] = 0.0;                      // referencia
        }
    }
}

// ---------------- CAMPO (U,V) ----------------
ComputeCampo::ComputeCampo(ComputePresion &presion) : Presion(presion) {}

void ComputeCampo::velocidadesUpdate() {
    auto &Campo = Presion.Campo;
    double dx = Campo.G.dx;
    double dy = Campo.G.dy;
    double dt = Presion.dt;
    double rho = Presion.rho;
    double nu = 0.1; // viscosidad

    auto un = Campo.u;
    auto vn = Campo.v;

    for (int j = 1; j < Campo.G.ny-1; j++) {
        for (int i = 1; i < Campo.G.nx-1; i++) {
            Campo.u[j][i] = un[j][i]
                - un[j][i]*dt/dx*(un[j][i] - un[j][i-1])
                - vn[j][i]*dt/dy*(un[j][i] - un[j-1][i])
                - dt/(2.0*rho*dx)*(Presion.Campo.p[j][i+1] - Presion.Campo.p[j][i-1])
                + nu*(dt/(dx*dx)*(un[j][i+1]-2*un[j][i]+un[j][i-1]) +
                      dt/(dy*dy)*(un[j+1][i]-2*un[j][i]+un[j-1][i]));

            Campo.v[j][i] = vn[j][i]
                - un[j][i]*dt/dx*(vn[j][i] - vn[j][i-1])
                - vn[j][i]*dt/dy*(vn[j][i] - vn[j-1][i])
                - dt/(2.0*rho*dy)*(Presion.Campo.p[j+1][i] - Presion.Campo.p[j-1][i])
                + nu*(dt/(dx*dx)*(vn[j][i+1]-2*vn[j][i]+vn[j][i-1]) +
                      dt/(dy*dy)*(vn[j+1][i]-2*vn[j][i]+vn[j-1][i]));
        }
    }
}

// ---------------- FIELD WRITER ----------------
FieldWriter::FieldWriter(const std::string &fname) : filename(fname) {}

void FieldWriter::writePosicionCampo(const Grid &G, const CampoVelocidadesPresion &Campo) {
    std::ofstream file(filename);
    file << std::fixed << std::setprecision(6);

    for (int j = 0; j < G.ny; j++) {
        for (int i = 0; i < G.nx; i++) {
            double x = G.xmin + i*G.dx;
            double y = G.ymin + j*G.dy;
            file << x << " " << y << " "
                 << Campo.u[j][i] << " "
                 << Campo.v[j][i] << " "
                 << Campo.p[j][i] << "\n";
        }
        file << "\n";
    }
}
