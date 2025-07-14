# Guía de Compilación y Ejecución en Linux



Esta guía explica cómo compilar y ejecutar un programa en C++ que aproxima el valor del número π utilizando dos métodos distintos:

- Serie de **Leibniz**.
- Serie separada en términos con denominadores de la forma `4k+1` y `4k+3`.

El programa solicita al usuario el número de términos a usar y compara los resultados con el valor real de π, mostrando el error absoluto de cada método.

---

##  Primero debes asegurarte de : 

- Tener un sistema operativo Linux.
- Tener instalado un compilador de C++, como `g++`.
- Tener el archivo fuente en C++ (`Tarea_00_pi.cpp`).

---

##  Estructura del proyecto

Supongamos que el archivo `Tarea_00_pi.cpp` se encuentra en el siguiente directorio:

/home/yuliana/Documentos/FisicaComputacionalII/Tarea0


##  Pasos para compilar y ejecutar

### 1. Abrir la terminal

Abre la terminal de Linux. Puedes hacerlo desde el menú de aplicaciones buscando “Terminal”.

Una vez abierta, verás algo como:

yuliana@Yuliana-Linux:~


### 2. Navegar hasta la carpeta que contiene el archivo

Utiliza el comando `cd` (change directory) para cambiar al directorio donde guardaste el archivo `.cpp`. 

pones cd y el nombre de la primera carpeta en este caso Documentos 

Por ejemplo:


yuliana@Yuliana-Linux:~ cd Documentos

Presionas enter y aparece algo como:


yuliana@Yuliana-Linux:~/Documentos

luego accedes a la siguiente carpeta usando cd 

yuliana@Yuliana-Linux:~/Documentos/FisicaComputacionalII/

Y así sucesivamente hasta encontar la carpeta que contien el archivo.

yuliana@Yuliana-Linux:~/Documentos/FisicaComputacionalII/Tarea0



Puedes verificar que estás en el directorio correcto usando:

ls 

Deberías ver tu archivo Tarea_00_pi.cpp listado.


### 3. Compilar el programa 

Ejecuta este comando en el terminal 

g++ -o Tarea_00_pi Tarea_00_pi.cpp


g++ es el compilador de C++.

-o Tarea_00_pi indica el nombre del archivo ejecutable que se generará.

Tarea_00_pi.cpp es el archivo fuente con el código.



### 4. Ejecutar 


Una vez compilado, ejecuta el programa con:

./Tarea_00_pi

El programa te pedirá ingresar el número de términos a usar en la aproximación, lo ingresas y das Enter. 

Debería verse algo como : 

yuliana@Yuliana-Linux:~/Documentos/FisicaComputacionalII/Tarea0$ g++ -o Tarea_00_pi Tarea_00_pi.cpp
yuliana@Yuliana-Linux:~/Documentos/FisicaComputacionalII/Tarea0$ ./Tarea_00_pi 
¿Cuántos términos deseas usar para la aproximación? 100
Método 1: Aproximación del número PI con 100 términos usando Leibniz es : 3.13159
Método 2: Aproximación del número PI con 100 términos usando términos separados  : 3.13659
Valor usando cmath :    3.14159
Error absoluto asociado el método 1: 0.00999975
Error absoluto asociado al método 2: 0.00499997
yuliana@Yuliana-Linux:~/Documentos/FisicaComputacionalII/Tarea0$ 



