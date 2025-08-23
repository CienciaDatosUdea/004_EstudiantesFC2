
#ifndef FDTD_H
#define FDTD_H

#include <cmath>
#include <vector>
#include <string>
#include <fstream>

/**
 * @struct Geometria
 * @brief Define la geometría y parámetros de discretización para la simulación
 */
struct Geometria{
    Geometria(int K_, int N_, double dz_, double dt_);
    int K;          ///< Número total de pasos temporales
    int N;          ///< Número total de puntos espaciales
    double dz;      ///< Paso espacial
    double dt;      ///< Paso temporal
};

/**
 * @enum TipoFrontera
 * @brief Tipo de condiciones de frontera disponibles
 */
enum TipoFrontera {
    DIRICHLET,      ///< Condiciones de conductor perfecto
    PERIODICAS,     ///< Condiciones periódicas
    ABSORBENTES,    ///< Condiciones absorbentes
    ABIERTAS        ///< Condiciones abiertas (derivada cero)
};

/**
 * @class Campos
 * @brief Maneja los campos electromagnéticos y su evolución temporal
 */
class Campos{
    public:
    Campos(Geometria const & G_, TipoFrontera tipo = DIRICHLET);
    
    Geometria G;            ///< Objeto con geometría y discretización
    double beta;            ///< Parámetro de estabilidad (CFL)
    std::vector<std::vector<double>> E;  ///< Campo eléctrico
    std::vector<std::vector<double>> H;  ///< Campo magnético
    TipoFrontera tipoFrontera; ///< Tipo de condiciones de frontera

    void evolucion();
    void condiciones_iniciales();
    void aplicar_fronteras(int n);
    void fronteras_dirichlet(int n);
    void fronteras_periodicas(int n);
    void fronteras_absorbentes(int n);
    void fronteras_abiertas(int n);
    void set_tipo_frontera(TipoFrontera nuevo_tipo);
};

/**
 * @class Datos
 * @brief Maneja la entrada/salida de datos de la simulación
 */
class Datos{
    public:
    Datos(Campos const & C_);
    Campos C;
    std::ofstream file;

    void guardar_txt(std::string filename);
    void imprimir();
};

#endif