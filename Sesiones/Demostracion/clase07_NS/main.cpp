#include "flow.h"
#include <iostream>

int main(){   
    double xmin=0;
    double xmax=2;
    double ymin=0;
    double ymax=2;
    int  nx=10;
    int  ny=10;


    Grid G(xmin, xmax, ymin, ymax, nx, ny);
    
    CampoVelocidadesPresion F(G);
    G.BoundaryCondition();
    
    FileWriter f("datos/geometria.txt");
    
    
    f.writePosicion(G, );
    // // for(int i=0;i<nx;i++){
    // //     for(int j=0;j<ny;j++){
    // //         std::cout<<G.XY[i][j][0]<<"\t"<<G.XY[i][j][1]<<"\n"     ;
            
    //     }
    // }

    return 0;

}