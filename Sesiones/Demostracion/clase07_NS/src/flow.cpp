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
    :G(G_){
        U.resize(G.nx, std::vector<double>(G.ny, 0.0));
        V.resize(G.nx, std::vector<double>(G.ny, 0.0));
        P.resize(G.nx, std::vector<double>(G.ny, 0.0));  
}

FileWriter::FileWriter(const std::string &filename)    
    {
        file.open(filename);
        if (!file.is_open()) 
            throw std::runtime_error("No se pudo abrir el archivo: " + filename);
        
        file << std::fixed << std::setprecision(6);
    }


void FileWriter::writePosicion(const Grid &G)
{
   // int nx=G.nx;
   // int ny=G.ny;
    
    file<<"ejemplo de escritura de archivios";
    //file << "# i\t\tj\t\tx\t\ty\t\tu\t\tv\t\tp\n";    
   // file << "# nx\t\tny\t\t\n";
    //file << "# "<<nx<<"\t\t"<<ny<<"\n";
    //file << "# =================================\n";
    
    
}
void CampoVelocidadesPresion::CondicionesIniciales(){


}


void CampoVelocidadesPresion::BoundaryCondition(){

    
}





