


#include "DifusionCalor.h"
#include <fstream>
#include <iostream>


/*

EN este problema 



*/

//================ Implementación Geometría ================

Geometria::Geometria(int N_, double xmin_, double xmax_)
    : N(N_), xmin(xmin_), xmax(xmax_) {
    dx = (xmax - xmin) / (N - 1);
    x.resize(N);
    for (int i = 0; i < N; i++) x[i] = xmin + i * dx;
}



//------------------------------------------------------------------------------------

//================Condiciones Iniciales==================================================


CondicionesIniciales::CondicionesIniciales(Geometria &G_, TipoInicial tipo)
    : G(G_), u(G_.N, 0.0), tipo_inicial(tipo) {}

void CondicionesIniciales::aplicar() {
    switch (tipo_inicial) {
        case IMPULSO_CENTRAL:
            std::fill(u.begin(), u.end(), 0.0);
            u[G.N/2] = 100.0;
            break;

        case ESCALON:
            for (int i = 0; i < G.N; ++i)
                u[i] = (i < G.N/2) ? 50.0 : 0.0;
            break;

        case UNIFORME:
            std::fill(u.begin(), u.end(), 20.0);
            break;

        case GAUSSIANA:
            for (int i = 0; i < G.N; ++i) {
                double x = G.x[i];
                u[i] = std::exp(-100.0 * std::pow(x - 0.5 * (G.xmin + G.xmax), 2));
            }
            break;
    }
}





//============= Implementación CondicionesFrontera ==========

CondicionesFrontera::CondicionesFrontera(Geometria &G_,
                                         TipoFrontera tipo)

    : G(G_), u(G_.N,0.0), tipo_frontera(tipo){}

void CondicionesFrontera::aplicar() {
    switch (tipo_frontera) {
        case NULA:
            u[0] = 0;
            u[G.N - 1] =0;
            break;

        case VALOR:
            // Ghost-like: extremos copian vecinos interiores
            u[0]     = u[G.N - 2];
            u[G.N-1] = u[1];
            break;
    }
}

void CondicionesFrontera::setTipoFrontera(TipoFrontera f) { tipo_frontera = f; }





//==================== Implementación Simulador =========================================


Simulador::Simulador(CondicionesIniciales &CI_, CondicionesFrontera &CF_,
                     double alpha_, double dt_)
    : CI(CI_), CF(CF_), alpha(alpha_), dt(dt_) {
    r = alpha * dt / (CI.G.dx * CI.G.dx);
    u_nuevo.resize(CI.G.N, 0.0);
    CF.aplicar();
}


void Simulador::pasoTiempo() {
    //std::vector<double>& u = CI.getU();
    std::vector<double>& u = CI.u; // u es publico 

    // Usamos la froma explícita en como se actualiza el valor de U
    for (int i = 1; i < CI.G.N - 1; ++i) {
        u_nuevo[i] = u[i] + r * (u[i + 1] - 2.0 * u[i] + u[i - 1]);
    }
    //Definimos U como el nuevo estado
    u = u_nuevo;

    //alicamos la frontera (para fijar u[0] y u[N-1]) en cada ciclo
    CF.aplicar();

    //ejecutamos el siguiente paso
    //tiempo_actual += dt;
}


/*
void Simulador::guardar_evolucion(const std::string& nombre_archivo,
                                   double tiempo_max, double intervalo) {
    // Ruta de salida
    std::string ruta = "python/datos/" + nombre_archivo;

    std::ofstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << ruta << std::endl;
        return;
    }

    // Número de pasos totales y cada cuántos pasos guardar
    int pasos_totales = static_cast<int>(tiempo_max / dt);
    int cada_cuantos = static_cast<int>(intervalo / dt);

    // Encabezado: x, t_0, t_intervalo, ...
    archivo << "x";
    for (int p = 0; p <= pasos_totales; p += cada_cuantos) {
        archivo << ",t_" << p * dt;
    }
    archivo << "\n";

    // Vector para ir guardando los datos en columnas
    std::vector<std::vector<double>> datos(CI.G.N);
    for (int i = 0; i < CI.G.N; ++i) datos[i].push_back(CI.u[i]); // estado inicial

    // Avanzar en el tiempo y guardar cada intervalo
    for (int paso = 1; paso <= pasos_totales; ++paso) {
        pasoTiempo();
        if (paso % cada_cuantos == 0) {
            for (int i = 0; i < CI.G.N; ++i) {
                datos[i].push_back(CI.u[i]);
            }
        }
    }

    // Escribir en el archivo
    for (int i = 0; i < CI.G.N; ++i) {
        archivo << CI.G.x[i];
        for (double v : datos[i]) archivo << "," << v;
        archivo << "\n";
    }
    archivo.close();
}

*/

void Simulador::guardar_evolucion(const std::string& nombre_archivo,
                                   double tiempo_max, double intervalo) {
    // Ruta de salida
    std::string ruta = "python/datos/" + nombre_archivo;

    std::ofstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << ruta << std::endl;
        return;
    }

    // Número de pasos totales y cada cuántos pasos guardar
    int pasos_totales = static_cast<int>(tiempo_max / dt);
    int cada_cuantos = static_cast<int>(intervalo / dt);

    // Encabezado: x, t_0, t_intervalo, ...
    archivo << "Tiempo,     x,      u(x)\n";


    // Estado inicial
    for (int i = 0; i < CI.G.N; ++i) {
        archivo << 0.0 << ", " << CI.G.x[i] << ", " << CI.u[i] << "\n";
    }

    //for (int p = 0; p <= pasos_totales; p += cada_cuantos) {
     //   archivo << ",t_" << p * dt;
    //}
    //archivo << "\n";

    // Vector para ir guardando los datos en columnas
    //std::vector<std::vector<double>> datos(CI.G.N);
    //for (int i = 0; i < CI.G.N; ++i) datos[i].push_back(CI.u[i]); // estado inicial

    // Evolución en el tiempo
    for (int paso = 1; paso <= pasos_totales; ++paso) {
        pasoTiempo();
        if (paso % cada_cuantos == 0) {
            double t_actual = paso * dt;
            for (int i = 0; i < CI.G.N; ++i) {
                archivo << t_actual << ", " << CI.G.x[i] << ", " << CI.u[i] << "\n";
            }
        }
    }

    
    archivo.close();
}

void Simulador::imprimir(double tiempo_max, double intervalo) {
    int pasos_totales = static_cast<int>(tiempo_max / dt);
    int cada_cuantos = static_cast<int>(intervalo / dt);

    // Imprime encabezado
    std::cout << "Tiempo, x, u(x)\n";

    // Estado inicial
    for (int i = 0; i < CI.G.N; ++i) {
        std::cout << 0.0 << ", " << CI.G.x[i] << ", " << CI.u[i] << "\n";
    }

    // Evolución en el tiempo
    for (int paso = 1; paso <= pasos_totales; ++paso) {
        pasoTiempo();
        if (paso % cada_cuantos == 0) {
            double t_actual = paso * dt;
            for (int i = 0; i < CI.G.N; ++i) {
                std::cout << t_actual << ", " << CI.G.x[i] << ", " << CI.u[i] << "\n";
            }
        }
    }
}



