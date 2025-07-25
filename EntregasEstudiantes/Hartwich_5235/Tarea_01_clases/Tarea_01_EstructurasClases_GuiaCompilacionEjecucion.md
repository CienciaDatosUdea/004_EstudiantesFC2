El siguiente programa es una implementación básica de los siguientes conceptos:
- estructurar código en archivos diferentes que se juntan usando `include "<filename>"`
- `struct` para contener datos y `class` para contener y aplicar métodos

En el archivo que termina en clases.h, se implementa un `struct partícula` que define una partícula con las propriedades "número, coordenada x, coordenada y, componente de fuerza x, componente de fuerza y".

Además, se define una `class pSystem` que representa a un sistema de `N` partículas. El constructor del sistema inicializa automáticamente sus posiciones y les asigna números (consecutivos de 0 a N-1). Los métodos implementados pueden aplicar una perturbación aleatoria de `[-ds, ds]` a las coordenadas `x` y `y` de todas partículas, aplicar una fuerza con componentes `[0, df]` a cada partícula, calcular e imprimir las distancias mínimas y máximas de cualquier dos partículas y calcular e imprimir la magnitud de la fuerza total actuando sobre todo el sistema.

Los dichos métodos están implementados en el archivo que termina en metodos.cpp.

En el archivo main.cpp, se usan las clases y los métodos definidos en clases.h y métodos.cpp para comprobar su funcionamiento (imprimiendo informaciones sobre el procedimiento para el usuario que lo ejecuta). No se implementa ninguna clase nueva ni ningún método nuevo.

Este programa no requiere más interacción del usuario aparte de compilar `Tarea_01_EstructurasClases_main.cpp` y ejecutar el ejecutable según la descripción siguiente.

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