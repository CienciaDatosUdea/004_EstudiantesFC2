#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

class Figura{
    public:
        void msg(){
            std::cout<<"Esto es una  figura generica"<<"\n";
        };       
};

class Circulo: public Figura{    
    public:               
        void msg() { //La  clase queda oculta, 
            std::cout<<"Esto es un circulo"<<"\n";
        }
       
};

int main(){
    Figura f;
    f.msg();

    Circulo c;
    c.msg();

    Circulo c1;
    Figura *p=&c1; //Oculta la clase padre
    p->msg();
    c1.msg();     //No sobreescrible la clase hija 


    return 0;
}