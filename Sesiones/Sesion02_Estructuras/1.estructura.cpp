# include<iostream>

// g++ -std=c++17 -Wall programa.cpp -o programa.out
struct posicion{
    double x;
    double y;
   
};

struct particula{
    posicion p;
    double spin s;
};

int main(int argc, char *argv []){
    srand(time(NULL));

    posicion p={1.0,1.0};
    particula part={{1.0,1.0},{1./2}};
    
    std::cout<<part.p.x<<"\n";
    std::cout<<part.p.y<<"\n";
    std::cout<<part.s<<"\n";

    return 0;
}

