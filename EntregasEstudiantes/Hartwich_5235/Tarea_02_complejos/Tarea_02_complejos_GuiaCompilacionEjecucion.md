El siguiente programa es una implementación básica de los siguientes conceptos:
- estructurar código en archivos diferentes que se juntan usando `include "<filename>"`
- usar clases
- usar el concepto de inherencia de clases
- definir operadores para clases

En el archivo que termina en clases.h, se implementa una clase `complexBase` que define un número complejo. Contiene la información tanto expresada por (parte real, parte imaginaria) como expresada por (magnitud absoluta, ángulo en el plano complejo). Además, tiene dos métodos que se deben usar para que actualice el segundo (primero) par de coordenadas cuando hay habido un cambio en el primero (segundo).

Además, se define una *child class* `complex` de la *parent class* `complexBase`. Esta clase es la única que se va a usar en main.cpp. Hereda todas las variables y los métodos protectados o públicos de complexBase (en el caso implementado: todo). Esta clase contiene todos los demás métodos que se van a usar en main.cpp, entre otros funciones para imprimir el valor del número complejo en las coordenadas deseadas, operadorec para acceder directamente a las coordenadas deseadas (operator[] sobrecargado) y operadores para aritmética básica (+, -, *, /, +=, -=, *=, /=, ==).

En el archivo main.cpp, se usan las clases y los métodos definidos en clases.h y métodos.cpp para comprobar su funcionamiento. No se implementa ninguna clase nueva ni ningún método nuevo.

Este programa no requiere más interacción del usuario aparte de compilar `Tarea_02_complejos_main.cpp` y ejecutar el ejecutable según la siguiente descripción.

---

Lo siguiente es una copia parcial del GuiaCompilacionEjecucion de la Tarea_00. **Una alternativa más eficaz para proyectos muy extensos en tiempo de cómputo sería usar un Makefile.**

---

Programando y usando C++, hay que diferenciar entre los archivos que contienen el código de forma legible para humanos y archivos que son comprensibles para computadores.
Los anteriores, usualmente con extensión ".cpp", tienen que ser compilados con un compilador. Este proceso genera un ejecutable, que es el tipo de archivo que se puede correr finalmente, por ejemplo tras la terminal de Linux.

En sistemas Linux, un compilador que se puede usar es "GCC". Para compilar un archivo que contiene código de C++, hay que ingresar lo siguiente al terminal,

    g++ <filename> -o <execname>

donde <filename> es el nombre del archivo (por ejemplo mi_archivo.cpp) y <execname> es el nombre el que se le va a asignar al ejecutable (por ejemplo mi_executable.out).
Para entonces correr el ejecutable, hay que ingresar al terminal

    ./<execname>

Sin embargo, se presta automatizar el proceso, por ejemplo añadiendo la función siguiente al archivo .bashrc (en sistemas Ubuntu):

    cpr() {

        outputfiletype=".out"

        clear -x

        if [ -z "$1" ]; then
            echo "Error: No filename provided."
            return
        fi

        if [[ "$1" == *.cpp ]]; then
            filename="$1"
            execname="${1%.cpp}${outputfiletype}"
        elif [[ -f "$1.cpp" ]]; then
            filename="$1.cpp"
            execname="${1}${outputfiletype}"
        else
            echo "Error: Filename must end in .cpp or corresponding \"filename.cpp\" file must exist."
            return
        fi

        g++ "$filename" -o "$execname" && ./"$execname"

    }

En el ejemplo donde el archivo inicial se llama mi_archivo.cpp, se puede llamar la función ingresando tanto

    cpr mi_archivo.cpp

como

    cpr mi_archivo

a la terminal de Linux. En ambos casos, aquel archivo en el directorio actual que se llame mi_archivo.cpp va a ser compilado en un ejecutable llamado mi_archivo.out, y este ejecutable va a ser ejecutado de una vez.