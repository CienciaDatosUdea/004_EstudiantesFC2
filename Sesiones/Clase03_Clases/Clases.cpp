#include <iostream>
#include <cmath>
#include<random>
#include <cstdlib>
#include <ctime>

const int N=10;

std::mt19937_64& global_rng() {
    static std::mt19937_64 rng{ /*semilla*/ };
    return rng;
}

double random_number(double a, double b) {
    std::uniform_real_distribution<double> dist(a, b);
    return dist(global_rng());
}


class particula{
  

};

class sistema{

}

int main(){
    
    return 0;
}
