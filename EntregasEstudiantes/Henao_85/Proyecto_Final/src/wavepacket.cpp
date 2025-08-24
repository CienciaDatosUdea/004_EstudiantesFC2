#include "wavepacket.h"
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <filesystem>
#include <iostream>

using namespace std;

// ==============================
// Inicialización del paquete gaussiano
// ==============================
vector<cplx> init_psi(int N, double x_0, double k, double sigma, double dx) {
    vector<cplx> result(N);
    double norm = pow((2 * M_PI) * (sigma * sigma), -0.25);

    for (int i = 0; i < N; i++) {
        double x = i * dx;
        double realPart = -(x - x_0) * (x - x_0) / (4 * sigma * sigma);
        double imagPart = k * x;
        result[i] = norm * exp(cplx(realPart, imagPart));
    }
    return result;
}

// ==============================
// Solución analítica de un paquete gaussiano libre
// ==============================
vector<cplx> exact_psi(double x_0, double k, double sigma, double dt, int Nx, int Nt, double dx) {
    vector<cplx> result(Nx);
    cplx zi(0.0, 1.0);
    double time = Nt * dt;

    for (int i = 0; i < Nx; i++) {
        double x = dx * i;
        cplx norm = pow(pow(2.0 * M_PI, 0.25) * sqrt(sigma + (time * zi) / (2.0 * sigma)), -1);
        cplx gaussian_term = -(pow((x - x_0 - k * time), 2)) /
                             (4.0 * pow(sigma, 2) + 2.0 * zi * time)
                             + (zi * k * (x - k * time / 2.0));
        result[i] = norm * exp(gaussian_term);
    }
    return result;
}

// ==============================
// Generador de intervalos uniformes
// ==============================
vector<double> generateEvenlySpacedIntervals(double start, double end, double interval) {
    int size = static_cast<int>((end - start) / interval) + 1;
    vector<double> intervals(size);
    for (int i = 0; i < size; i++) {
        intervals[i] = start + i * interval;
    }
    return intervals;
}

// ==============================
// Algoritmo de Thomas (resolución tridiagonal)
// ==============================
void thomas_tridiag(const vector<cplx>& a,
                    const vector<cplx>& b,
                    const vector<cplx>& c,
                    const vector<cplx>& psi,
                    vector<cplx>& u) {
    int n = b.size();
    vector<cplx> gam(n);
    cplx bet;

    if (b[0] == cplx(0.0, 0.0)) {
        throw runtime_error("Error 1 in tridag");
    }

    u[0] = psi[0] / (bet = b[0]);

    for (int j = 1; j < n; j++) {
        gam[j] = c[j - 1] / bet;
        bet = b[j] - a[j] * gam[j];
        if (bet == cplx(0.0, 0.0)) {
            throw runtime_error("Error 2 in tridag");
        }
        u[j] = (psi[j] - a[j] * u[j - 1]) / bet;
    }

    for (int j = n - 2; j >= 0; j--) {
        u[j] -= gam[j + 1] * u[j + 1];
    }
}

// ==============================
// Función principal de simulación
// ==============================
void run_simulation(double x_0, double k, double sigma, double h, double m,
                    double start_x, double end_x, double dx,
                    double start_t, double end_t, double dt) {

    namespace fs = std::filesystem;
    fs::create_directory("resultados");  // Crear carpeta resultados si no existe

    vector<double> x_i = generateEvenlySpacedIntervals(start_x, end_x, dx);
    vector<double> t_n = generateEvenlySpacedIntervals(start_t, end_t, dt);

    int Nx = x_i.size();
    int Nt = t_n.size();

    vector<cplx> a(Nx - 1, cplx(0, -dt * h / (4 * m * pow(dx, 2))));
    vector<cplx> b(Nx, cplx(1, dt * h / (2 * m * pow(dx, 2))));
    vector<cplx> c(Nx - 1, cplx(0, -dt * h / (4 * m * pow(dx, 2))));

    vector<cplx> f(Nx, 0.0);
    vector<cplx> psi = init_psi(Nx, x_0, k, sigma, dx);
    vector<cplx> final(Nx);

    // Evolución temporal
    for (int i = 0; i < Nt; ++i) {
        thomas_tridiag(a, b, c, psi, f);
        for (int j = 0; j < Nx; j++) {
            final[j] = 2.0 * f[j] - psi[j];
        }
        psi = final;
    }

    // Guardar solución numérica
    ofstream outfile("resultados/cn.csv");
    for (int i = 0; i < Nx; i++) {
        double nrm_t = norm(psi[i]);
        outfile << dx * i << "," << nrm_t << endl;
    }
    outfile.close();

    // Comparación con la solución exacta
    vector<cplx> exact_psi_result = exact_psi(x_0, k, sigma, dt, Nx, Nt, dx);
    ofstream outputFile3("resultados/ex-psi-initial-norm2.csv");
    outputFile3 << scientific;
    for (int i = 0; i < Nx; i++) {
        double exact_val = norm(exact_psi_result[i]);
        outputFile3 << dx * i << "," << exact_val << endl;
    }
    outputFile3.close();

    cout << "Simulación finalizada. Archivos generados en la carpeta 'resultados'." << endl;
}
