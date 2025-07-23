#define _USE_MATH_DEFINES
#include <cstdlib> 
#include <iostream>
#include <cmath>

using namespace std;

double calcularPiLeibniz(int n);
double calcularPiSeparado(int n);
double error(double true_val, double false_val);

int main(){
    int n;
    double Pi_1, Pi_2;

    cout << "Escriba el numero de terminos que desea en su serie: " << endl; cin >> n;
    if (n <= 1){
        cout << "eligio un numero negativo, intente de nuevo! " << endl;
        exit(1);
    }
    Pi_1 =  calcularPiLeibniz(n);
    Pi_2 =  calcularPiSeparado(n);

    cout << "El valor aproximado de pi con " << n << " terminos usando el metodo de Leibniz es: " << Pi_1 << endl;
    cout << "El anterior valor respresenta un error de " << 100*error(M_PI,Pi_1) <<"%" << endl;
    cout << "El valor aproximado de pi con " << n << " terminos usando el metodo de separacion es: " << Pi_2 << endl;
    cout << "El anterior valor respresenta un error de " << 100*error(M_PI,Pi_2) <<"%" << endl;

    return 0;
}

double calcularPiLeibniz(int n){
    double sum  = 0.;
    for(int k = 0 ; k <=n ;k++){
        sum += pow(-1,k) / (2*k + 1);
    }
    return 4.*sum;
}
double calcularPiSeparado(int n){
    double sum_positive = 0.;
    double sum_negative = 0.;
    for(int k = 0 ; k <=n ;k++){
        sum_positive += 1. / (4*k + 1);
    }
     for(int k = 0 ; k <n ;k++){
        sum_negative += 1. / (4*k + 3);
    }
    return 4.*(sum_positive - sum_negative);
}
double error(double true_val, double false_val){
    return abs(true_val - false_val)/true_val;
}

