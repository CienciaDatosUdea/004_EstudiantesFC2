Calculadora de Números Complejos
Descripción
Este programa realiza operaciones básicas con números complejos (suma, resta, multiplicación, división y cálculo de magnitud).

Compilación
Para compilar el programa, ejecuta:

bash
make
Ejecución
Para ejecutar el programa:

bash
make run
O directamente:

bash
./bin/numero_complejos
Uso
El programa te pedirá que ingreses dos números complejos

Ingresa la parte real e imaginaria de cada número

El programa mostrará automáticamente todos los resultados:

Suma (A + B)

Resta (A - B)

Multiplicación (A * B)

División (A / B)

Magnitud (módulo) de ambos números

Estructura del proyecto
text
.
├── include/          # Archivos de cabecera (.h)
├── src/             # Archivos de implementación (.cpp)
├── main.cpp         # Programa principal
├── Makefile         # Configuración de compilación
└── bin/             # Ejecutables (generados al compilar)
Comandos útiles
make clean - Limpia los archivos compilados

make rebuild - Limpia y recompila

make debug - Compila con información de depuración

Requisitos
Compilador g++ compatible con C++11

Sistema Linux/macOS (o WSL en Windows)
