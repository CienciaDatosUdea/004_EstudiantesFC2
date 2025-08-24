#include <vector>
#include <complex>

using cplx = std::complex<double>;
using namespace std;

// Inicialización del paquete gaussiano
vector<cplx> init_psi(int N, double x_0, double k, double sigma, double dx);

// Solución analítica de un paquete gaussiano libre
vector<cplx> exact_psi(double x_0, double k, double sigma, double dt, int Nx, int Nt, double dx);

// Generador de intervalos uniformes
vector<double> generateEvenlySpacedIntervals(double start, double end, double interval);

// Algoritmo de Thomas (resolución tridiagonal)
void thomas_tridiag(const vector<cplx>& a,
                    const vector<cplx>& b,
                    const vector<cplx>& c,
                    const vector<cplx>& psi,
                    vector<cplx>& u);

// Función principal que corre toda la simulación y guarda los archivos
void run_simulation(double x_0, double k, double sigma, double h, double m,
                    double start_x, double end_x, double dx,
                    double start_t, double end_t, double dt);


