#include "flow.h"
#include <iostream>


int main(){ 
    int nx = 51;
    int ny = 51;
    int nit = 100;
    int nt = 1000;
    char filename[64];
    double xmin=0,xmax=2;
    double ymin=0,ymax=2;
    double dt = 0.001;
    double rho=1.;
    
    Grid G(xmin, xmax, ymin, ymax, nx, ny);        
    CampoVelocidadesPresion Campo(G);
    ComputePresion presion(Campo,rho, dt, nit);
    ComputeCampo omega(presion);        
    Campo.CondicionesIniciales();
    Campo.BoundaryCondition();          
    for (int i = 0; i < nt; ++i) {
        presion.presionUpdate();        
        omega.velocidadesUpdate();    
        if (i % (10) == 0 && i>500) {
            std::snprintf(filename, sizeof(filename), "data/campos_%03d.txt", i);        
            FieldWriter writer(filename);
            writer.writePosicionCampo(G, Campo);
        }
    }
    return 0;
}
