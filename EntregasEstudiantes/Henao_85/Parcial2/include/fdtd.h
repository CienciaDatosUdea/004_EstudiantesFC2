#include <vector>
#include <string>

enum class BCType { PERIODIC, DIRICHLET };

class FDTD1D_Yee {
public:
    FDTD1D_Yee(int N, int nsteps, double dz, double dt, BCType bc_);

    // Inicializa una onda seno; Hy se desplaza medio paso espacial
    void init_sine(double amplitude, double wavelength);

    // Ejecuta la simulación y guarda snapshots en CSV
    void run(const std::string& outdir);

private:
    int Nnodes;      // número de nodos de Ex (k = 0..N-1)
    int Nsteps;      // pasos de tiempo
    double dz, dt;
    double eps0, mu0, c;
    double betaE, betaH;   // coeficientes de actualización

    BCType bc;

    // Malla de Yee:
    // Ex[k] en posiciones enteras k
    // Hy[k] en posiciones semi–enteras k+1/2 (Hy[N-1] está entre Ex[N-1] y Ex[0] si PERIODIC)
    std::vector<double> Ex; // tamaño N
    std::vector<double> Hy; // tamaño N

    // Paso de actualización de campos (interior)
    void update_E_interior();
    void update_H_interior();

    // Bordes según la condición de frontera
    void apply_E_boundaries();
    void apply_H_boundaries();

    // Utilidad: guardar CSV
    void save_snapshot(int step, const std::string& outdir);
};




























