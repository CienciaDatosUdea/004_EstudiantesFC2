#include <string>
#include <vector>
#include "difusion_model.h"  // Para usar Geometria y Condiciones

class Flow {
public:
    Flow(const std::string &nombreArchivo);
    void guardarPaso(int paso, const Geometria &G, const std::vector<double> &u);

private:
    std::string rutaArchivo;
};


