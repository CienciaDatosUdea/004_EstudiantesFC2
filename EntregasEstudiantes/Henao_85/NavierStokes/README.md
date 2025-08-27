
# Para compilar un programa use: 

g++ -std=c++17 -Wall programa.cpp -o programa.out


| Parte              | Significado                                                                 |
|--------------------|------------------------------------------------------------------------------|
| `g++`              | Llama al compilador de C++ de GNU                                            |
| `-std=c++17`       | Indica que se debe usar el estándar **C++17** (puede ser `c++11`, `c++20`, etc.) |
| `-Wall`            | Activa **todas las advertencias ("warnings") útiles** para detectar posibles errores |
| `programa.cpp`     | Archivo fuente que se va a compilar                                          |
| `-o programa.out`  | Especifica el **nombre del ejecutable** que se generará (salida)             |