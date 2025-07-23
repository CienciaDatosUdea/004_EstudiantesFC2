#include <iostream>

class particula{
    public:
        double masa;
        void imprimir(){
            std::cout << "Masa: " << masa << std::endl;
        }

};

int main(){
    particula p;
    p.masa=2;
    p.imprimir();

    particula *ptr = &p;
    ptr->masa = 10; // equivalente a (*ptr).masa = 10.0
    ptr->imprimir();// equivalente a (*ptr).imprimir()

}