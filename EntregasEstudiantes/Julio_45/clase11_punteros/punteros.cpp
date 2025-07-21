#include <iostream>

using namespace std;

int main(){
    system("clear");
    int u=1;
    int *v; // Un puntero, lo sé porque tiene un asterisco
            // Almacena a direcciones de memoria

    v = &u;  // El & indica la posición de memoria de la variable en cuestión

    std::cout<<"posicion de memoria de u "<<&u<<endl;
    std::cout<<"valor de u "<<u<<endl;

    std::cout<<"-------------------------------------------"<<endl;

    std::cout<<"posicion de memoria de v "<<&v<<endl; // la posición de memoria de p es distinta a la posición a la que apunta
    std::cout<<"valor de v "<<v<<endl;  // p guarda la dirección de memoria
    std::cout<<"valor de que hay en esa posicion de memoria "<<*v<<endl;   // se puede acceder a lo que hay en la dirección a la que apunta

    *v += 1;  // puedo modificar el valor que almacena la dirección en memoria de lo que hay allá

    std::cout<<"-------------------------------------------"<<endl;
    std::cout<<"posicion de memoria de v "<<&v<<endl; 
    std::cout<<"valor de v "<<v<<endl;  
    std::cout<<"valor de que hay en esa posicion de memoria "<<*v<<endl;   

    /*
    DOBLES PUNTEROS **
    */

    int **w;

    w = &v;

    std::cout<<"-------------------------------------------"<<endl;
    std::cout<<"posicion de memoria de w "<<&w<<endl; 
    std::cout<<"valor de w "<<w<<endl;  
    std::cout<<"valor de que hay en esa posicion de memoria "<<*w<<endl;
    std::cout<<"valor de que hay en esa posicion de memoria "<<**w<<endl;   

    return 0;

}