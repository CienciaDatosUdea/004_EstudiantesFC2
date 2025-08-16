# Aproximación de π con la serie de Leibniz

Este programa en C++ calcula aproximaciones al número π utilizando la **serie de Leibniz**.  
Se implementan dos variantes de la fórmula y se comparan sus resultados con el valor de referencia de π, mostrando además el **error absoluto** de cada método.

---

## 📌 Descripción general

- Genera una aproximación de π usando la serie clásica de Leibniz.
- Calcula también una variante de la suma separando términos según su módulo.
- Compara ambas aproximaciones contra el valor real de π (`acos(-1)`).
- Muestra en pantalla las aproximaciones y el error absoluto de cada una.

El programa solicita al usuario un número de términos `n`, que determina la precisión de la aproximación (a mayor `n`, mejor aproximación).

---

## ⚙️ Compilación

Compilar con **g++** (requiere C++17 o superior):

```bash
g++ -std=c++17 -Wall pi_leibniz.cpp -o pi_leibniz.out
