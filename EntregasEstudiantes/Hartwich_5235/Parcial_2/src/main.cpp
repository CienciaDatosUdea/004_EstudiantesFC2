#include <interface.h>

#include <iostream>
#include <vector>
#include <array>

int main() {

    // velocidad de la luz
    constexpr double c{299792458};

    // parámetros fijos espaciales
    constexpr double z_min{0};
    constexpr double z_max{200};

    // número de puntos espaciales
    constexpr size_t n_z{201};

    // para que se guarde la evolución total (-> animaciones).
    // Esta parte no fue implementada y queda como idea para el futuro. Las funciones toman estos parámetros pero no los usan. Se podría implementar con un nuevo miembro de Solver std::optional<std::vector<Fields>> logs_ que se inicializa con número de componentes según la variable logs, logs_(logs), y al cual se appenden los campos logs veces durante la evolución si log_full_evolution=true. Así, estos datos también se añadirían al .txt, para que se pueda animar la evolución completa. Por ahora, la clase Solver solo guarda las configuraciones finales.
    constexpr bool log_full_evolution{true};
    constexpr int logs{100}; // cantidad de "snapshots" durante la evolución

    /* PRIMERA PARTE: COMPARACIÓN CONDICIONES DE FRONTERA PERIÓDICAS Y REFLEXIVAS */
    {
        std::cout << "\nStarting Phase 1.\n" << std::endl;

        // discretisación espacial resultante y discretización temporal
        const double dz{(z_max - z_min) / (n_z - 1)};
        const double dt{dz/(2*c)}; // valor máximo de dt según el "criterio de estabilidad Courtrand" :   c/(dz/dt) <= 1/2   <=>   dt <= dz/(2c). Luego se investiga qué pasa cuando no se cumple.


        // construir objeto que contiene geometría unidimensional (z)
        const Grid g(z_min, z_max, n_z);

        // construir campos iniciales
        const Fields initial_fields(g);

        // guardar datos de la condición inicial
        WriteFieldsToTxt(
            "initial_condition",
            initial_fields
        );


        // la idea es evoluar el sistema con y sin condiciones reflectivas para 2 tiempos respectivamente
        // nombres de los archivos
        const std::vector<std::vector<std::string>> filenames{
            {"reflective_t1", "reflective_t2"},
            {"not_reflective_t1", "not_reflective_t2"}
        };

        // tiempos
        const std::vector<double> times{.3, 1.4};

        // condiciones de frontera reflexivas (E=H=0)
        const std::array<bool, 2> reflective_boundaries{true, false};

        // evoluar sistema con condiciones reflectivas para dos tiempos
        for (size_t i{0}; i < reflective_boundaries.size(); ++i) {
            for (size_t j{0}; j < times.size(); ++j) {
                std::cout << "\n\nConfiguration " << i * times.size() + j + 1 << std::endl;
                const Solver sol(
                    initial_fields,
                    times[j],
                    dt,
                    reflective_boundaries[i],
                    log_full_evolution,
                    logs
                );
                WriteFieldsToTxt(
                    filenames[i][j],
                    sol.get_fields_()
                );
            }
        }
    }

    /* SEGUNDA PARTE: INVESTIGACIÓN DE ESTABILIDAD */
    {
        std::cout << "\n\n\nStarting Phase 2." << std::endl;

        // parámetros de arriba (sirve como punto de base)
        const double dz_0{(z_max - z_min) / (n_z - 1)};
        const double dt_0{dz_0/(2*c)}; // valor máximo de dt según el "criterio de estabilidad Courtrand" :   c/(dz/dt) <= 1/2   <=>   dt <= dz/(2c).
        
        // Según el criterio de estabilidad de Courtrand, bastaría variar o dz o dt, pero el ejercicio pide explícitamente variar ambos.
        // el bucle va a iterar para un tiempo fijo sobre:
            // dz/dt = 1.0 dz_0 / dt_0
            // dz/dt = 0.33 dz_0 / dt_0
            // dz/dt = 1.0 dz_0 / (3 * dt_0) = 0.33 dz_0 / dt_0 (cómo el caso anterior, pero con dz y dt diferente)
            // dz/dt = 0.5 dz_0 / (0.5 dt_0) = 1.0 dz_0 / dt_0 (cómo el caso inicial, pero con dz y dt diferente)
        const std::vector<std::vector<double>> dz_dt_pairs{
            {1.00 * dz_0,  1.00 * dt_0}, // corresponde a la configuración de parte 1
            {0.33 * dz_0,  1.00 * dt_0},
            {1.00 * dz_0,  3.00 * dt_0},
            {0.50 * dz_0,  0.50 * dt_0}
        };
        const std::vector<std::string> filenames {
            "1_dz_1_dt.txt",
            "033_dz_1_dt.txt",
            "1_dz_3_dt.txt",
            "05_dz_05_dt.txt"
        };

        // mismo tiempo para evolucionar todos (tiempo muy corto)
        constexpr double t_end{.00001};

        // crear grid, aplicar condiciones iniciales y evoluar campos para los dz/dt diferentes
        for (size_t i{0}; i < dz_dt_pairs.size(); ++i) {
            std::cout << "\n\nConfiguration " << i + 1 << std::endl;
            // construir objeto que contiene geometría unidimensional (depende de dz)
            const int n_z{static_cast<int>((z_max - z_min)/dz_dt_pairs[i][0]) + 1};
            const Grid g(z_min, z_max, n_z);
            // construir campos iniciales
            const Fields initial_fields(g);
            // solución
            const Solver sol(
                initial_fields,
                t_end,
                dz_dt_pairs[i][1],
                false,
                log_full_evolution,
                logs
            );
            WriteFieldsToTxt(
                filenames[i],
                sol.get_fields_()
            );
        }
    }

    std::cout << "\nExecution of main sucessful." << std::endl;

    return 0;
}