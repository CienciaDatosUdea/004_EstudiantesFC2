#include <iostream>
#include <vector>


#ifndef DIFUSION_MODEL_H
#define DIFUSION_MODEL_H

#include <vector>
#include <iostream>
#include <functional>
#include <cmath>
#include <fstream>
#include <string>
#include <iomanip>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

//==================== Geometría ===========================================

/*Define la clase para hacer la discretización de los puntos 
donde se evaluará el campo U
*/

class Geometria {
public:
    Geometria(int N, double xmin, double xmax);
    int N;
    double dx, xmin, xmax;
    std::vector<double> x;
};

//================ Condiciones iniciales ==================================


// enum permite elegir varias condiciones inciales i.e el valor que toma U 
//en cada punto de la  barra en t=0

enum TipoInicial {
    IMPULSO_CENTRAL,
    ESCALON,
    UNIFORME,
    GAUSSIANA
};

class CondicionesIniciales {
public:
    Geometria &G;              // referencia a la geometría
    std::vector<double> u;     // campo U directamente accesible
    TipoInicial tipo_inicial;  

    // constructor
    CondicionesIniciales(Geometria &G_, 
                        TipoInicial tipo = IMPULSO_CENTRAL);

    void aplicar();
    void setTipoInicial(TipoInicial t) { tipo_inicial = t; }
};




//================ Condiciones de frontera ==================================================



// enum permite elegir varias condiciones de frontera i.e el valor que toma U en los extremos

enum TipoFrontera {
    NULA,
    VALOR
};

class CondicionesFrontera {
public:
    Geometria &G;
    std::vector<double> u; 
    TipoFrontera tipo_frontera;


    CondicionesFrontera(Geometria &G,   // llamamos la geometría y el vector U que define el campo de calor
                        TipoFrontera tipo );// valores que defecto toma U en los extremos

    void aplicar();
    void setTipoFrontera(TipoFrontera f);

};

//==================== Simulador ==========================================================



class Simulador {
public:
    Simulador(CondicionesIniciales &CI_, CondicionesFrontera &CF_,
              double alpha_, double dt_);

    void pasoTiempo();
    void imprimir(double tiempo_max, double intervalo);
    void guardar_evolucion(const std::string& nombre_archivo,
                        double tiempo_max, 
                        double intervalo);

private:
    CondicionesIniciales &CI;
    CondicionesFrontera &CF;
    double alpha, dt;
    double r;
    std::vector<double> u_nuevo; // <- miembro de la clase
};





#endif // DIFUSION_MODEL_H