#include <cmath>
#include <iostream>
using namespace std;


// ESTE CODIGO CALCULA EL VALOR DE PI USANDO LA SERIE DE LEIBNIZ POR DOS METODOS Y COMPARA LOS RESULTADOS CON EL VALOR TEORICO
// PARA EJECUTAR ESTE CODIGO: ./Tarea_00_pi.out
// Input:
// n -> Número de términos de la serie de Leibniz a utilizar para aproximar Pi.
// Output:
// Pi_aprox -> Valor aproximado de Pi calculado usando la serie de Leibniz.
// Pi_separado -> Valor aproximado de Pi calculado separando términos positivos y negativos de la serie de Leibniz.
// Error -> Diferencia entre el valor teórico de Pi (M_PI de Cmath) y el valor aproximado calculado.

double calcularPiLeibniz(int n);
double calcularPiSeparado(int n);


int main() {
    int n; // Número de términos
    cout << "Ingrese el número de términos para calcular Pi: "<<endl;
    cin >> n;

    //Validar que n sea positivo
    if(n <= 0){
        cout << "El número de términos debe ser positivo" << endl;
        return 1; // Salir del programa si n es inválido
    }

    // Calcular Pi usando la serie de Leibniz

    double Pi_leibniz = calcularPiLeibniz(n);
    double Pi_separado = calcularPiSeparado(n);

    cout << "Valor de Pi usando la serie de Leibniz: " << Pi_leibniz << endl;
    cout<<"Error: "<< abs(M_PI - Pi_leibniz)<<endl;
    cout << "Valor de Pi usando la suma separada: " << Pi_separado<< endl;
    cout<<"Error: "<< abs(M_PI - Pi_separado)<<endl;

    return 0;
}

double calcularPiLeibniz(int n){
    // ESTA FUNCION CALCULA EL VALOR DE PI USANDO LA SERIE DE lEIBNIZ
    // pi = 4 * (1 - 1/3 + 1/5 - 1/7 + 1/9 - ...)

    double i = 0;
    double pi = 0.0;

    for(i = 0; i< n; i++){
        pi += pow(-1, i) /(2*i +1);
    }
    double pi_aprox = 4 * pi;
    
    return pi_aprox;
}

double calcularPiSeparado(int n){
    // ESTA FUNCION CALCULA EL VALOR DE PI USANDO LA SERIE DE lEIBNIZ PERO SEPARANDO TERMINOS POSITIVOS Y NEGATIVOS


    double i = 0;
    double pi_pos = 0.0;
    double pi_neg = 0.0;
    cout<<n<<endl;

    for(i = 0; i<n; i+=1){

        pi_pos += 1.0/(4*i + 1);
        pi_neg += 1.0/(4*i + 3);

    }
    double pi_aprox = 4 * (pi_pos - pi_neg);


    return pi_aprox;
}