# include<iostream>

// g++ -std=c++17 -Wall programa.cpp -o programa.out

int main(){
    system("clear");
    int n=1;
    int *p;
    std::cout<<"Valor de n: "<<n<< "\n";
    std::cout<<"Direccion de memoria de n: "<<&n<< "\n";
    std::cout<<"------------------\n";

    p=&n;
    std::cout<<"Valor de p: "<<*p<< "\n";
    std::cout<<"Direccion de memoria de p: "<<&p<< "\n";
    std::cout<<"Direccion de memoria de p es la misma de n: "<<p<< "\n";
    
    *p = *p+2; //modique el valor en esa posicion de memoria 
//   std::cout<<"Valor de p: "<<*n<< "\n";
    std::cout<<"Direccion de memoria de p: "<<&n<< "\n";
    std::cout<<"Direccion de memoria de p es la misma de n: "<<n<< "\n";

    
    int u = 1;
    int *v;
    int **w;    

    v = &u;
    
    std::cout<<"Direccion de memoria de u: "<<&u<< "\n";
    std::cout<<"Direccion de memoria de v: "<<&v<< "\n";
    std::cout<<"Direccion de memoria de w: "<<&w<< "\n";
    
    w=&v;     
    std::cout<<"Direccion de memoria de w: "<<*w<< "\n";
    std::cout<<"Direccion de memoria de w: "<<**w<< "\n";
    std::cout<<"Direccion de memoria de w: "<<&w<< "\n";

    **w=**w+2;
    std::cout<<"Direccion de memoria de n: "<<u<< "\n";

    




}

