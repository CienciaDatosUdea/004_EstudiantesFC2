# include <cstdio>
# include <iostream>
# include "flow.h"

//Problema del codigo, no es general, se puede hacer general
Grid::Grid(double x_min_, double x_max_,
        double y_min_, double y_max_, int nx_, int ny_)
    :x_min(x_min_),x_max(x_max_),y_min(y_min_),y_max(y_max_),nx(nx_),ny(ny_){
        
        dx=(x_max-x_min)/(nx-1);
        dy=(y_max-y_min)/(ny-1);
        XY.resize(nx, std::vector<std::vector<double>>(ny, std::vector<double>(2)));
        
        for(int i=0;i<nx;i++){
            for(int j=0;j<ny;j++){
                XY[i][j][0] = x_min+i*dx;
                XY[i][j][1] = y_min+j*dy;
            }
        }
};

CampoVelocidadesPresion::CampoVelocidadesPresion(Grid &G_)
    :G(G_){}



void CampoVelocidadesPresion::CondicionesIniciales(){
    U.resize(G.nx, std::vector<double>(G.ny, 0.0));
    V.resize(G.nx, std::vector<double>(G.ny, 0.0));
    P.resize(G.nx, std::vector<double>(G.ny, 0.0));  
}


void CampoVelocidadesPresion::BoundaryCondition(){
    //Frontera izquierda
    for(int j=0;j<G.ny;j++){
        U[0][j]=0;
        V[0][j]=0;
        P[0][j] = P[1][j];
    }    
    //Frontera derecha
    for(int j=0;j<G.ny;j++){
        U[G.nx-1][j]=0;
        V[G.nx-1][j]=0;
        P[G.nx-1][j] = P[G.nx-2][j];
    }    
    //Frontera inferior
    for(int i=0;i<G.nx;i++){
        U[i][0]=0;
        V[i][0]=0;
        P[i][0] = P[i][1];
    }    
    //Frontera superior
    for(int i=0;i<G.nx;i++){
        U[i][G.ny-1]=1;
        V[i][G.ny-1]=0;
        P[i][G.ny-1]=0;
    }
    
}


FileWriter::FileWriter(const std::string &filename)    
    {
        file.open(filename);
        if (!file.is_open()) 
            throw std::runtime_error("No se pudo abrir el archivo: " + filename);
        
        file << std::fixed << std::setprecision(6);
    }


void FileWriter::writePosicion(const Grid &G, const CampoVelocidadesPresion &F)
{
    auto nx=G.nx;
    auto ny=G.ny;
    
    file<<"#"<<"i"<<"j"<<"x"<<"y"<<"\n";
    file<<"#"<<nx<<"\t"<<ny;
    
    for(int i=0;i<nx;i++){
        for(int j=0;j<ny;j++){
            file<<i<<"\t"<<j<<"\t"<<G.XY[i][j][0]<<"\t"<<G.XY[i][j][1]<<"\t"<<F.U<<"\t"<<F.V<<"\t"<<F.P<<"\n";
        }
    }

    
}

