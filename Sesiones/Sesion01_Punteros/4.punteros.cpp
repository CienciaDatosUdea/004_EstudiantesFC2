# include<iostream>

// g++ -std=c++17 -Wall programa.cpp -o programa.out

void elementos_matriz(double a[][5]){
    a[1][1]=10;
}

int main(){
    system("clear");
   
   double A[3][5]={};
   std::cout<<A[2][4]<<"\n";



   elementos_matriz(A);
   std::cout<<A[1][1]<<"\n";
}

