#ifndef PROPAGADOR_ONDA_HPP
#define PROPAGADOR_ONDA_HPP

// --- Librerías Estándar ---
#include <vector>
#include <string>
#include <fstream>

/**
 * @class WavePropagator
 * @brief Simula la propagación de ondas electromagnéticas 1D usando el método FDTD.
 *
 * Esta clase se encarga de configurar, ejecutar y guardar los resultados
 * de una simulación de campo electromagnético en una malla unidimensional.
 */
class WavePropagator {
public:
    /**
     * @brief Constructor de la clase.
     * @param cantidadNodos Número de puntos en la malla de simulación.
     * @param factorBeta Relación de la velocidad de la luz y el paso temporal/espacial.
     */
    WavePropagator(int cantidadNodos, double factorBeta);

    /**
     * @brief Establece el tipo de condiciones de frontera para la simulación.
     * @param tipoDeBorde Una cadena que especifica el tipo de borde (ej. "PEC").
     */
    void definirLimites(const std::string& tipoDeBorde);

    /**
     * @brief Inicia y corre la simulación por un número determinado de pasos.
     * @param pasosTemporales El número total de iteraciones de tiempo a ejecutar.
     * @param intervaloDeGuardado La frecuencia con la que se guardarán los datos.
     * @param archivoDeSalida El nombre del archivo donde se guardarán los resultados.
     */
    void iniciarSimulacion(int pasosTemporales, int intervaloDeGuardado, const std::string& archivoDeSalida);

private:
    // --- Métodos privados para la lógica interna ---

    /** @brief Inicializa los vectores de campo a sus valores iniciales (generalmente cero). */
    void inicializarVectores();

    /** @brief Avanza la simulación un único paso en el tiempo, actualizando los campos E y H. */
    void avanzarEnElTiempo();

    /** @brief Aplica las condiciones de contorno definidas en los extremos de la malla. */
    void aplicarCondicionesDeBorde();

    /** @brief Escribe el estado actual de los campos en el archivo de salida. */
    void guardarDatos(std::ofstream& flujoDeArchivo);

    // --- Atributos de la simulación ---
    int numPuntos;
    double BETA_FACTOR;
    std::string tipoDeCondicionDeBorde;

    // Vectores para los campos electromagnéticos. La segunda dimensión es para
    // almacenar el valor actual [0] y el siguiente [1].
    std::vector<std::vector<double>> campoE; // Componente del campo eléctrico (Ex)
    std::vector<std::vector<double>> campoH; // Componente del campo magnético (Hy)
};

#endif // PROPAGADOR_ONDA_HPP
