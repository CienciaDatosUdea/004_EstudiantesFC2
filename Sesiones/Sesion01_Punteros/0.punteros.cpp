# include<iostream>

// g++ -std=c++17 -Wall programa.cpp -o programa.out

int main(){
    system("clear");
    int n=1;
    double d=2.0;
    std::cout<<"Valor de n: "<<n<< "\n";
    std::cout<<"Valor de d: "<<d<< "\n";

    std::cout<<"Posición de memoria de n: "<<&n<< "\n";
    std::cout<<"Posición de memoria de d: "<<&d<< "\n";

    int *p;
    p = &n;
    std::cout<<"Valor de p: "<<p<< "\n";   // VAlor de la posicion de memoria de n 
    std::cout<<"Valor de p: "<<*p<< "\n"; //Valor que apunta a la posicion de memoria de n
    std::cout<<"Valor de p: "<<&p<< "\n"; //Tiene una posicion de memoria diferente

    
}

