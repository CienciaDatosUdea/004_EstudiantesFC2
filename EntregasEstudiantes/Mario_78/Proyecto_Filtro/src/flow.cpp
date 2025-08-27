#include "../include/flow.h"

// Constructor de la clase FlowManager 
FlowManager::FlowManager() {
    // Inicialización si se requiere
}

// Método principal que gestiona la interacción con el usuario
void FlowManager::run() {
    int numtaps;  // Número de coeficientes del filtro (se generan numtaps + 1 coeficientes)
    double fs;    // Frecuencia de muestreo
    int option;   // Opción elegida por el usuario (tipo de filtro)

    // Menú inicial
    std::cout << "=== Diseñador de Filtros FIR (Ventana de Hamming) ===\n";
    std::cout << "Ingrese número de coeficientes: ";
    std::cin >> numtaps;

    std::cout << "Ingrese frecuencia de muestreo [Hz]: ";
    std::cin >> fs;
    
    // Selección del tipo de filtro
    std::cout << "\nSeleccione tipo de filtro:\n";
    std::cout << "1) Pasa-bajas\n";
    std::cout << "2) Pasa-altas\n";
    std::cout << "3) Pasa-banda\n";
    std::cout << "4) Rechaza-banda\n";
    std::cout << "Opcion: ";
    std::cin >> option;

    
    // --- Filtro pasa-bajas ---
    if (option == 1) {
        double cutoff;
        std::cout << "Ingrese frecuencia de corte [Hz]: ";
        std::cin >> cutoff;

        // Se construye el filtro FIR de tipo pasa-bajas
        FIRFilter lp(numtaps, fs, cutoff, FilterType::LOWPASS);
        lp.printCoefficients();                         // Mostrar coeficientes por pantalla
        lp.exportData("datos/filtro_lowpass.txt");      // Exportar coeficientes a archivo
    }

    // --- Filtro pasa-altas ---
    else if (option == 2) {
        double cutoff;
        std::cout << "Ingrese frecuencia de corte [Hz]: ";
        std::cin >> cutoff;

        FIRFilter hp(numtaps, fs, cutoff, FilterType::HIGHPASS);
        hp.printCoefficients();
        hp.exportData("datos/filtro_highpass.txt");
    }

     // --- Filtro pasa-banda ---
    else if (option == 3) {
        double f1, f2;
        std::cout << "Ingrese frecuencia baja [Hz]: ";
        std::cin >> f1;
        std::cout << "Ingrese frecuencia alta [Hz]: ";
        std::cin >> f2;

        FIRFilter bp(numtaps, fs, f1, f2, FilterType::BANDPASS);
        bp.printCoefficients();
        bp.exportData("datos/filtro_bandpass.txt");
    }

    //--- Filtro rechaza-banda ---
    else if (option == 4) {
        double f1, f2;
        std::cout << "Ingrese frecuencia baja [Hz]: ";
        std::cin >> f1;
        std::cout << "Ingrese frecuencia alta [Hz]: ";
        std::cin >> f2;

        FIRFilter bs(numtaps, fs, f1, f2, FilterType::BANDSTOP);
        bs.printCoefficients();
        bs.exportData("datos/filtro_bandstop.txt");
    }

    // --- Opción inválida ---
    else {
        std::cout << "Opcion invalida.\n";
    }
}
