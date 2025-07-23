#include <iostream>
#include <vector>
#include <memory>
#include <cmath>


class Ejemplo {
public:
    void saluda() {
        std::cout << "Hola sin nombre\n";
    }
    //Sobrecarga del metodo
    void saluda(std::string nombre) {
        std::cout << "Hola " << nombre << "\n";
    }
};
int main(){
    Ejemplo a;
    a.saluda("hola mundo" );
    a.saluda( );    
    return 0;
}