# Cálculo de π usando la serie de Leibniz

Este programa, escrito en C++, permite calcular una aproximación del número π utilizando la serie de Leibniz. El usuario puede comparar dos métodos de cálculo y observar el error absoluto respecto al valor real de π.

## Requisitos

Para compilar y ejecutar este programa, se necesita tener instalado un compilador de C++, como `g++`, en un sistema operativo Linux.

Puedes verificar si tienes `g++` instalado con el siguiente comando:

```bash
g++ --version
```

Si no está instalado, puedes instalarlo en distribuciones basadas en Debian/Ubuntu con:

```bash
sudo apt update
sudo apt install g++
```

## Archivos

* `Tarea_00_pi.cpp`: archivo fuente con el código en C++.
* `Tarea_00_pi.out`: archivo ejecutable (se generará después de la compilación).

## Compilación

Para compilar el programa, abre una terminal en el mismo directorio donde se encuentra el archivo `Tarea_00_pi.cpp` y ejecuta:

```bash
g++ -o Tarea_00_pi.out Tarea_00_pi.cpp
```

Este comando crea un archivo ejecutable llamado `Tarea_00_pi.out`.

## Ejecución

Una vez compilado el programa, se puede ejecutar con:

```bash
./Tarea_00_pi.out
```

El programa pedirá ingresar un número entero positivo que representará la cantidad de términos a usar en la serie de Leibniz.

### Ejemplo de ejecución

```
Ingrese el número de términos (entero) de la serie de Leibniz para realizar el cálculo de pi:
1000000

1) Valor de pi con la serie de Leibniz: 3.141591...
2) Valor de pi con la serie de Leibniz, pero separando pares e impares: 3.141592...
Valor de real de pi: 3.141593...
Error absoluto para el primer caso: ...
Error absoluto para el segundo caso: ...
```

## Notas

* Si se introduce un número no positivo, el programa solicitará repetir la entrada hasta que sea válida.
* Los resultados pueden variar dependiendo de la cantidad de términos ingresados.
