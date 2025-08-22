# include<iostream>

// g++ -std=c++17 -Wall programa.cpp -o programa.out

int main(){
    system("clear");
   
    char names[3][8]= {"Bob", "Alice", "Maxwelp"}; //Propio de c
    
    std::cout<<names[0]<<"\n";
    std::cout<<names[1]<<"\n";
    std::cout<<names[2][6]<<"\n";

    const char *names1[]= {"Bob", "Alice", "Maxwelp"}; 

    std::cout<<names1[0]<<"\n";
    std::cout<<names1[1]<<"\n";
    std::cout<<names1[2]<<"\n";

}

