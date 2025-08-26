#include "flow.h"

int main(){
    int nx = 51;
    int ny = 51;
    int nit = 100;
    int nt = 1000;
    char filename[64];
    double xmin = 0.0, xmax = 2.0;
    double ymin = 0.0, ymax = 2.0;
    double dt = 0.001;
    double rho = 1.0;
    double F = 1.0; // Fuerza externa

    Grid grid(xmin, xmax, ymin, ymax, nx, ny);
    CampoVelocidadesPresion Campo(grid);
    ComputePresion presion(Campo, rho, dt, nit);
    ComputeCampo omega(presion, F);
    Campo.CondicionesIniciales();
    Campo.BoundaryCondition();
    for (int i = 0; i<nt; i++){
        presion.presionUpdate();
        omega.velocidadesUpdate();
        if(i % (10) == 0 && i>500){
            std::snprintf(filename, sizeof(filename), "data/campos_%03d.txt", i);        
            FieldWriter writer(filename);
            writer.writePosicionCampo(grid, Campo);
        }
    }
    return 0;
}