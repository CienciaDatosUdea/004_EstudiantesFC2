#ifndef FDTD_HPP
#define FDTD_HPP

#include <vector>
#include <string>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

enum class BCType { Periodic, FixedZeros };

struct FDTDParams {
    int nx = 200;        // nodos espaciales
    double dz = 1.0;     // paso espacial
    double c  = 3.0e8;   // velocidad de la luz
    double beta = 0.49;  // c*dt/dz (usar <= 0.5)
    BCType bc = BCType::Periodic;
};

class FDTD {
public:
    explicit FDTD(const FDTDParams& p);

    void initialize_sine(double amp = 0.1, double lambda = 100.0);
    void step();              // un paso temporal (según BC)
    void run(int nsteps, int output_every, const std::string& outpath);

    // acceso de solo lectura
    const std::vector<double>& Ex() const { return Ex_old; }
    const std::vector<double>& Hy() const { return Hy_old; }

    // parámetros derivados
    double dt() const { return params.beta * params.dz / params.c; }
    double get_beta() const { return params.beta; }

private:
    FDTDParams params;
    std::vector<double> Ex_old, Ex_new;
    std::vector<double> Hy_old, Hy_new;

    void step_periodic();
    void step_fixed();
    void write_frame(std::ostream& os, int tstep) const;
};

#endif
