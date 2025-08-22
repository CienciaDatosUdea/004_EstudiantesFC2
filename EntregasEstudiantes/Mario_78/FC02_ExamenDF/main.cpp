#include "fdtd.h"

int main() {
    Campos simulador(200, 1.0, 1.0, 100.0, 5);
    simulador.inicializar();
    simulador.simular("docs/datos.txt");
    return 0;
}
