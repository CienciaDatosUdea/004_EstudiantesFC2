
//Include de la ecuacion dependiente del tiempo 


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


                    



// Función que ejecuta toda la simulación Crank-Nicolson
// Nueva función con evolución completa
void run_cn_simulation_evolution(int N, double L, double dt, int nsteps,
                                double x0, double k0, double sigma);


// Guardar evolución temporal completa en un solo archivo
void save_time_evolution(const vector<vector<cdouble>>& psi_history, 
                         const vector<double>& time_points, 
                         double dx, const string& filename);


