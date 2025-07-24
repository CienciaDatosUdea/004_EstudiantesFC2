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

// Cuando implemento el método circulo la clase padre queda oculta

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

    Circulo c1; //CIrculo es un objeto y yo apunto a las posiciones de memoria de la clase padre Figura
    Figura *p=&c1; //No queda oculta la clase padre 
    p->msg();  //Está apuntando a la clase padre, por lo tanto no se sobreescribe el método msg de la clase hija Circulo
    c1.msg();     //No sobreescribre la clase hija 


    return 0;
}