# include<iostream>

int main(){
    system("clear");
   
    int a=1;
    int *p;
    
    p = &a;

    std::cout<<"Valor de  a "<<a<<"\n";
    std::cout<<"Posicion de memoria de  a"<<&a<<"\n";
    std::cout<<"--------------------------\n";
    std::cout<<"Valor de  p "<<p<<"\n";
    std::cout<<"Posicion de memoria de  p"<<&p<<"\n";
    std::cout<<"Puntero, apunta a la variable a"<<*p<<"\n";
    std::cout<<"--------------------------\n";
    *p=*p+1;
    std::cout<<"Valor de  a "<<a<<"\n";
    std::cout<<"Posicion de memoria de  a"<<&a<<"\n";
    std::cout<<"Valor de  p "<<p<<"\n";
    std::cout<<"Posicion de memoria de  p"<<&p<<"\n";
    std::cout<<"Puntero, apunta a la variable a"<<*p<<"\n";
    
    return 0;
}
