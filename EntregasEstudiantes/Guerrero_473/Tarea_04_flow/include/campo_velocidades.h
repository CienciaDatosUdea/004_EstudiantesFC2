

#include <vector>
#include <iostream>
#include <fstream>

//DECLARACIÓN DE CLASES ....................................................................................

// Enumeraciones para configuraciones
enum class ProblemType { CHANNEL_FLOW, CAVITY_FLOW };
enum class ForceType { NONE, CONSTANT_X, CONSTANT_Y, CUSTOM };

// Clase donde defino la malla espacial donde se resuelve la ecación 
class Grid{
    public:             
    //Parámetros de la malla
        Grid(double x_min, double x_max, 
            double y_min, double y_max, 
            int nx, int ny);

        double dx, dy;
        double x_min, x_max; //VAlores mínimos que toma la malla
        double y_min, y_max; // Valores maximos que toma la malla
        int nx, ny;//Número de puntos espaciales por cada dimensión                 
        std::vector<std::vector<std::vector<double>>> XY; // dimensiones nx x ny 
};

// Clase que contiene la distribución del campo en la malla 
//Aplicar las condiciones iniciales y de frontera 
class Condiciones{
    public:
        Condiciones(Grid &G, ProblemType ptype = ProblemType::CAVITY_FLOW, 
                   ForceType ftype = ForceType::NONE); // Constructor con opciones
        
        Grid &G;         
        std::vector<std::vector<double>> U; //Campo de velocidades de la coordenada i
        std::vector<std::vector<double>> V;//Campo de velocidades de la coordenada j 
        std::vector<std::vector<double>> P; //Campo de presiones 
        std::vector<std::vector<double>> Fx; // Fuerza en dirección x
        std::vector<std::vector<double>> Fy; // Fuerza en dirección y

        ProblemType problemType;
        ForceType forceType;

        void CondicionesIniciales();
        void CondicionesFrontera();
        void AplicarFuerza();
};

class Presion{
    public:
        //Aplicamos el constructor en el campo de presiones 
        Presion (Condiciones &C, double rho, double dt, int nit);
        
        Condiciones &C;
        double rho;
        double dt;
        int nit;
        void calcularPresion();
};

class Velocidades{
    public:
        Velocidades (Presion &omega);
        Presion &omega;        
        void calcularVelocidades();
};

class EscribirCampo {
    public:
        EscribirCampo(const std::string &filename);
        std::ofstream file;    
        void PosicionCampo(const Grid &G, const Condiciones &C, double tiempo);
};