# include<iostream>

void suma_uno(double *k){
    *k=*k+1;
}

int main(){
    double n = 10.0;
    double *p; 
    p = &n;

    suma_uno(p);
    std::cout<<*p<<"\n";
    std::cout<<n<<"\n";

    return 0 ;
}