#include "Tarea_01_EstructurasClases_clases.h"

int main() {

    // system("clear -x"); // solo funciona en linux (y si tiene clear de Ncurses)
    std::cout << "\033[H\033[J"; // alternativa para system("clear -x") que debería funcionar en MacOS también (más no Windows)

    // constantes
    const int N{10};         // Número de partículas
    const double R{1.0};     // Radio de la circunferencia de la esfera 2D
    const double DS{0.1};    // Rango de perturbación aleatoria (por componente espacial)
    const double DF{1};      // Rango de fuerza aleatoria (por componente espacial)

    // creación del objeto (sistema), uso de las funciones integradas y output correspondiente pal usuario
    std::cout << "\nInitiating system with\n\n\tN  = " << N << "\n\tR  = " << R << "\n\tDS = " << DS << "\n\tDF = " << DF << std::endl;

    pSystem s(N, R, DS, DF);

    s.print_min_and_max_dist();

    std::cout << "\nApplying random perturbations. Now," << std::endl;
    s.apply_perturbation();
    s.print_min_and_max_dist();

    std::cout << "\nApplying random forces." << std::endl;
    s.apply_forces();
    s.print_total_force();

    std::cout << std::endl;
    
    return 0;

}