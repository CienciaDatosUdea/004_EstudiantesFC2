## Descripción del programa

Este programa tiene como objetivo aproximar el valor de π utilizando dos métodos numéricos basados en series. 
A partir de un número de términos proporcionado por el usuario, el programa calcula una aproximación de π usando la serie de Leibniz:

   \[
   \pi \approx 4 \left(1 - \frac{1}{3} + \frac{1}{5} - \frac{1}{7} + \dots \right)
   \]

y una segunda aproximación utilizando la resta entre dos series separadas:

   \[
   \pi \approx 4 \left( \sum_{i=0}^{n} \frac{1}{4i + 1} - \sum_{i=0}^{n} \frac{1}{4i + 3} \right)
   \]

Ambos valores calculados se comparan con el valor teórico de π (obtenido de la constante M_PI definida en <cmath>) y se calcula su error absoluto respecto al valor real.


## Ejecución del programa

Para ejecutar el programa en sistemas Linux, se debe abrir una terminal y compilar el código usando el compilador g++ de la siguiente forma: 
g++ -o Tarea_00_pi.out Tarea_00_pi.cpp

Esto generará un archivo ejecutable llamado Tarea_00_pi.out.

Luego, se debe ejecutar el programa con el comando: ./Tarea_00_pi.out 

Al iniciar la ejecución, el programa pedirá al usuario ingresar el número de términos que desea usar en la serie para calcular π. Si el usuario ingresa un valor negativo o cero, el programa no continuará hasta que se proporcione un valor positivo. 