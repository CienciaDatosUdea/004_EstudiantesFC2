#include <iostream>

void suma_uno(double *k){
    *k += 1;
}

int main(){
    double n = 10.0;
    double *p;
    p = &n;

    std::cout<<p<<"\n";
    std::cout<<*p<<"\n";
    std::cout<<"---------------------"<<"\n";

    suma_uno(p);

    std::cout<<p<<"\n";
    std::cout<<*p<<"\n";
    std::cout<<n<<"\n";
    std::cout<<"---------------------"<<"\n";
    return 0;

}