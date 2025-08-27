#include"../include/difusion_model.h"

Geometria::Geometria(int N_, double xmin_, double xmax_): N(N_), xmin(xmin_), xmax(xmax_) {
    // Calcular dx y llenar el vector de posiciones x
    dx =  (xmax - xmin) / (N - 1);
    x.resize(N);
    for (int i = 0; i < N; i++) {
        // Calcular la posición x[i]
        x[i] = xmin + i * dx;
    }
};

CampoInicial::CampoInicial(double TL_, double TR_, double x0, double alpha, Geometria &geom): TL(TL_), TR(TR_) {
    // Calcular el campo de temperatura inicial u
    u.resize(geom.N);
    for (int i = 0; i < geom.N; i++) {
        // Calcular la temperatura inicial en u[i], por defecto gaussiana
        u[i] = exp(-alpha *(geom.x[i] - x0) * (geom.x[i] - x0));
    }
    u[0] = TL;
    u[geom.N-1] = TR;
}

DiffusionSolver::DiffusionSolver(Geometria& g, CampoInicial& u, double D_, 
    double dt_) : geom(g), temp(u), D(D_), dt(dt_) {
    alpha = D * dt / (geom.dx * geom.dx);

}

void DiffusionSolver::step() {
    // Implementar un paso de la solución
    for (int i = 1; i < geom.N - 1; i++) {
        temp.u[i] += alpha * (temp.u[i-1] - 2*temp.u[i] + temp.u[i+1]);
    }
    
}

void DiffusionSolver::evolucion(double tmax) {
    this->save("solucion.csv", true);

    // Implementar la evolución temporal hasta tmax
    Nsteps = static_cast<int>(tmax / dt);
    for (int n = 0; n < Nsteps; n++) {
        this->step();
        // Guardar cada paso
        this->save("solucion.csv", false, n);
        
    }
}

void DiffusionSolver::save(string filename, bool is_first, int n) {
    // Guardar la solución en un archivo CSV
    ofstream file;
    if (is_first) {
        file.open(filename);
        file << "n; x; u"<<endl;
    }
    else{
        // Si el archivo ya existe, abrir en modo append
        file.open(filename, ios::app);
    }

    for (int i = 0; i < geom.N; i++) {
        file << n << ";"<<geom.x[i] << ";" << temp.u[i] << "\n";
    }
    file << endl;
    file.close();
}


