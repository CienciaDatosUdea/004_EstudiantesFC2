---
title: Complejos

---

#  Proyecto: Operaciones con Números Complejos en C++

Este proyecto implementa clases en C++ para trabajar con **números complejos** y realizar operaciones matemáticas básicas:  

- ✅ Suma  
- ✅ Resta  
- ✅ Multiplicación  
- ✅ División (con control de división por cero)  
- ✅ Magnitud (módulo del número complejo)  

---

## 📂 Estructura del proyecto

```
clase03/
│── .vscode/             # Configuración de VSCode (opcional)
│   └── settings.json
│── include/             # Archivos de cabecera (.h)
│   ├── complejos.h
│   └── op_complejos.h
│── src/                 # Implementación (.cpp)
│   ├── complejos.cpp
│   ├── op_complejos.cpp
│── main.cpp             # Programa principal
│── Makefile             # Script de compilación
│── complejos_app.out    # Ejecutable generado tras compilar
│── README.md            # Documentación del proyecto
```

---

## Compilación y ejecución

El proyecto usa un **Makefile** para simplificar la compilación.  

### Compilar:
```bash
make
```

### Ejecutar:
```bash
./complejos_app.out
```

###  Limpiar:
```bash
make clean
```

---

## Uso del programa

Ejemplo incluido en `main.cpp`:

```cpp
#include "op_complejos.h"

int main() {
    op_complejos A(-2, 8), B(8, 10);
    op_complejos SUMA = A + B;
    op_complejos RESTA = A - B;
    op_complejos MULTP = A * B;
    op_complejos DIV = A / B;
    
    std::cout<<"A = "; A.get_complejos();         // imprime valor de A
    std::cout<<"B = "; B.get_complejos();         // imprime valor de B
    std::cout<<"A + B = "; SUMA.get_complejos();  // debería imprimir A + B = 6 + 18i
    std::cout<<"A - B = "; RESTA.get_complejos(); // imprime A - B = -10 + -2i
    std::cout<<"A * B = "; MULTP.get_complejos(); // imprime A * B = -96 + 44i
    std::cout<<"A / B = "; DIV.get_complejos();   // imprime A / B = 0.390244 + 0.512195i

    std::cout << "Magnitud |SUMA|= " << SUMA.magnitud_complejo() << "\n"; // imprime la magnitud de SUMA 
    
    return 0;
}
```

---

## Ejemplo de salida

```
A + B = 6 + 18i
A - B = -10 + -2i
A * B = -96 + 44i
A / B = 0.390244 + 0.512195i
Magnitud: 19.6977
```

---

## Tecnologías usadas
- Lenguaje: **C++17**
- Compilador: `g++`
- Herramienta: **Makefile**
- Entorno recomendado: Visual Studio Code

---

## Fórmulas utilizadas

Dado $A = a + bi$ y $B = c + di$:

- **Suma**:  
  $(a+bi) + (c+di) = (a+c) + (b+d)i$

- **Resta**:  
  $(a+bi) - (c+di) = (a-c) + (b-d)i$

- **Multiplicación**:  
  $(a+bi)(c+di) = (ac - bd) + (ad + bc)i$

- **División**:  
  $\frac{a+bi}{c+di} = \frac{(ac+bd) + (bc-ad)i}{c^2 + d^2}$

- **Magnitud**:  
  $|a+bi| = \sqrt{a^2 + b^2}$

---

**Autor: Jader Enrique Mario Mendoza**  
