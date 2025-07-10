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

Para la tarea presente, falta solo una interacción más del usuario. Al ejecutar, el script explicará en la terminal qué es la función del código y pedirá al usuario de ingresar un número (entero positivo). Después de ingresar el número y presionar "enter", el script hará las calculaciones anunciadas y mostrará los resultados en la terminal.