#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

// override permite que la clase hija sobreescriba el método de la clase padre
// virtual permite que la clase padre pueda ser apuntada por un puntero de la clase hija

class Figura{
    public:
        virtual void msg(){
            std::cout<<"Esto es una  figura generica"<<"\n";
        };   
        virtual ~Figura()=default;  //destructor virtual por defecto. 
 
};

class Circulo: public Figura{    
    public:               
        void msg() override{ //La  no queda oculta se sobre escribie
            std::cout<<"Esto es un circulo"<<"\n";
        }
        
};

int main(){
    Figura f;
    f.msg();

    Circulo c;
    c.msg();

    Circulo c1;
    Figura *p=&c1; //No esta oculta la clase padre
    p->msg();
    c1.msg();     //sobreescrible la clase hija 


    return 0;
}