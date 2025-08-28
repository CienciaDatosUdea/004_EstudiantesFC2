#include "../include/flow.h"
#include <cmath>
using namespace std;

ComputePresion::ComputePresion(CampoVelocidadesPresion &Campo_, double rho_, double dt_, int nit_)
    : Campo(Campo_), rho(rho_), dt(dt_), nit(nit_) {}

void ComputePresion::presionUpdate() {
    // placeholder simple
    for (int k = 0; k < nit; k++) {
        for (int i = 1; i < Campo.G.nx - 1; i++) {
            for (int j = 1; j < Campo.G.ny - 1; j++) {
                Campo.P[i][j] = (Campo.P[i+1][j] + Campo.P[i-1][j] +
                                 Campo.P[i][j+1] + Campo.P[i][j-1]) / 4.0;
            }
        }
    }
}

ComputeCampo::ComputeCampo(ComputePresion &omega_) : omega(omega_) {}

void ComputeCampo::velocidadesUpdate() {
    auto &Campo = omega.Campo;
    for (int i = 1; i < Campo.G.nx - 1; i++) {
        for (int j = 1; j < Campo.G.ny - 1; j++) {
            Campo.U[i][j] -= omega.dt * (Campo.P[i+1][j] - Campo.P[i-1][j]) / (2 * Campo.G.dx);
            Campo.V[i][j] -= omega.dt * (Campo.P[i][j+1] - Campo.P[i][j-1]) / (2 * Campo.G.dy);
        }
    }
}
