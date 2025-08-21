#pragma once
#include <vector>
#include <string>
#include <fstream>

// ===================== Malla =====================
struct Grid1D {
    int Nz;       // número de nodos
    double dz;    // paso espacial
    Grid1D(int Nz_, double dz_) : Nz(Nz_), dz(dz_) {}
};

// ===================== Campos =====================
struct CampoEM {
    // buffers 0=viejo, 1=nuevo
    std::vector<double> Ex0, Ex1;
    std::vector<double> Hy0, Hy1;
    explicit CampoEM(int Nz) : Ex0(Nz,0.0), Ex1(Nz,0.0), Hy0(Nz,0.0), Hy1(Nz,0.0) {}
};

// ===================== Tipo de frontera =====================
enum class BoundaryType {
    Periodic,      // condiciones periódicas (wrap)
    DirichletZero  // E = H = 0 en los extremos (z = 0 y z = L)
};

// ===================== Esquema FDTD 1D =====================
struct FDTD1D {
    Grid1D   G;
    CampoEM  F;
    double   beta;          // beta = c*dt/dz en unidades normalizadas
    BoundaryType bc;        // tipo de frontera

    // ctor
    FDTD1D(const Grid1D& g, double beta_, BoundaryType bc_ = BoundaryType::Periodic);

    // inicialización
    void init_sine(double A, double period);

    // un paso de tiempo (usa el tipo de frontera seleccionado)
    void step();

    // cambiar frontera en tiempo de ejecución (opcional)
    void set_boundary(BoundaryType bc_new) { bc = bc_new; }

    // salidas
    void write_snapshot(const std::string& filename) const; // k, z, Ex, Hy
    void write_csv(const std::string& filename) const;      // k, zE, zH, Ex, Hy
    void write_all(std::ofstream &f, double t) const;       // bloque con "# Tiempo: t"
};
