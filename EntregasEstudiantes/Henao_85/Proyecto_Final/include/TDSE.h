#include <vector>
#include <complex>

using cdouble = std::complex<double>;
using namespace std;

// Guardar la función de onda en un archivo
void save_wavefunction(const vector<cdouble>& psi, int step, double dx);

// Producto matriz * vector
vector<cdouble> matvec(const vector<vector<cdouble>>& M, const vector<cdouble>& v);

// Función que ejecuta toda la simulación Crank-Nicolson
void run_cn_simulation(int N, double L, double dt, int nsteps,
                       double x0, double k0, double sigma);


