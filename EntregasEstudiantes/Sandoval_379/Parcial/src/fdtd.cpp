#include "em1d.h"
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <iomanip>

static constexpr double PI = 3.14159265358979323846;

// índices cíclicos para BC periódica
static inline int Lp(int k, int N){ return (k - 1 + N) % N; }
static inline int Rp(int k, int N){ return (k + 1) % N; }

// ------------------ Constructor ------------------
FDTD1D::FDTD1D(const Grid1D& g, double beta_, BoundaryType bc_)
: G(g), F(g.Nz), beta(beta_), bc(bc_) {
    if (beta <= 0.0)  throw std::runtime_error("beta debe ser > 0");
    // Para c=1 normalizado en 1D, CFL: beta <= 0.5
    // (No arrojamos excepción si lo excede para permitir pruebas del apartado 1.2b)
}

// ------------------ Inicialización seno ------------------
void FDTD1D::init_sine(double A, double period){
    for (int k = 0; k < G.Nz; ++k){
        double zE = k * G.dz;
        double zH = (k + 0.5) * G.dz;  // staggering (Yee)
        F.Ex0[k] = A * std::sin(2.0 * PI * zE / period);
        F.Hy0[k] = A * std::sin(2.0 * PI * zH / period);
    }
}

// ------------------ Paso temporal ------------------
void FDTD1D::step(){
    const int N = G.Nz;

    if (bc == BoundaryType::Periodic) {
        // ===== Periódica: diferencias con wrap-around =====
        for (int k = 0; k < N; ++k){
            F.Ex1[k] = F.Ex0[k] + beta * ( F.Hy0[Lp(k,N)] - F.Hy0[Rp(k,N)] );
        }
        for (int k = 0; k < N; ++k){
            F.Hy1[k] = F.Hy0[k] + beta * ( F.Ex1[Lp(k,N)] - F.Ex1[Rp(k,N)] );
        }
    } else {
        // ===== DirichletZero: E=H=0 en bordes =====
        // Interior con diferencias centradas
        for (int k = 1; k < N-1; ++k){
            F.Ex1[k] = F.Ex0[k] + beta * ( F.Hy0[k-1] - F.Hy0[k+1] );
        }
        // Bordes: imponer condición (campos se anulan)
        F.Ex1[0]   = 0.0;
        F.Ex1[N-1] = 0.0;

        // H usa E nuevo; interior
        for (int k = 1; k < N-1; ++k){
            F.Hy1[k] = F.Hy0[k] + beta * ( F.Ex1[k-1] - F.Ex1[k+1] );
        }
        // Bordes: imponer condición (se anulan)
        F.Hy1[0]   = 0.0;
        F.Hy1[N-1] = 0.0;
    }

    // swap nuevo->viejo
    F.Ex0.swap(F.Ex1);
    F.Hy0.swap(F.Hy1);
}

// ------------------ Escritura snapshot simple ------------------
void FDTD1D::write_snapshot(const std::string& filename) const {
    std::ofstream f(filename);
    if (!f.is_open()) throw std::runtime_error("No se pudo abrir " + filename);
    f << "# k\tz\tEx\tHy\n";
    f << std::setprecision(10);
    for (int k = 0; k < G.Nz; ++k){
        double z = k * G.dz;
        f << k << '\t' << z << '\t' << F.Ex0[k] << '\t' << F.Hy0[k] << '\n';
    }
}

// ------------------ Escritura CSV (staggered) ------------------
void FDTD1D::write_csv(const std::string& filename) const {
    std::ofstream f(filename);
    if (!f.is_open()) throw std::runtime_error("No se pudo abrir " + filename);
    f << "k,zE,zH,Ex,Hy\n";
    f << std::setprecision(10);
    for (int k = 0; k < G.Nz; ++k){
        double zE = k * G.dz;
        double zH = (k + 0.5) * G.dz;
        f << k << "," << zE << "," << zH << "," << F.Ex0[k] << "," << F.Hy0[k] << "\n";
    }
}

// ------------------ Escritura en archivo único (bloques con tiempo) ------------------
void FDTD1D::write_all(std::ofstream &f, double t) const {
    if (!f.good()) throw std::runtime_error("Stream de salida no válido en write_all");
    f << "# Tiempo: " << std::fixed << std::setprecision(6) << t << "\n";
    f << "# k\tzE\tzH\tEx\tHy\n";
    f << std::setprecision(10);
    for (int k = 0; k < G.Nz; ++k){
        double zE = k * G.dz;
        double zH = (k + 0.5) * G.dz;
        f << k << '\t' << zE << '\t' << zH << '\t'
          << F.Ex0[k] << '\t' << F.Hy0[k] << '\n';
    }
    f << "\n";
}
