# Cálculo de $\pi$

Este programa realiza el calculo de $\pi$ mediante la fórmula de Leibnitz:
$$\sum_{k=0}^{k=n} \dfrac{ (-1)^k }{ 2k + 1 }$$
y lo compara con el valor teórico.

Cuenta con dos funciones, la primera ```calcularPiLeibniz``` calcula sumatoria término por término
la segunda ```calcularPiSeparado``` calcula los términos con denominador $4k + 1$ y $4k + 3$ por aparte y luego los resta.

**Funcionamiento:** 

Para compilar el código emplea:

    g++ -std=c++17 -Wall Tarea_00_pi.cpp -o Tarea_00_pi.out

Para ejecutar el codigo emplea: 

    ./Tarea_00_pi.out

**Parametros entrada:**

n: cantidad de términos a calcular

**Parametros de salida:** 

pi_leibnitz\
error_absoluto_leibnitz\
pi_separado\
error_absoluto_separado
