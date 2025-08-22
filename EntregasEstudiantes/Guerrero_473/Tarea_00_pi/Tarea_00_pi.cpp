
#include <iostream>
#include <cmath>
using namespace std;



/* Calcular el  númer PI usando la serie de Leibniz 

El usuario debe elegir el número de términos 


En este código se calcula el valor de PI de dos fromas diferentes. En una forma usamos 
la serie de Leibniz dada por: 
 ____
 \     (-1)^n   =  PI 
 /___   2n +1      4 
 n= 0 

 En la otra forma tenemos en cuenta que los términos de la serie están dados por: 

 1 - 1/3 + 1/5 -1/7 +   1/9 - ... = Pi/4 

La expresion de la izquierda la podemos descomponer en  los términos positivos 
(con denominadores de la forma 4k+1) y negativos (de la forma 4k+3)

T1=
T2= 




*/




double calcularPiLeibniz(int n){

    /*
    Esta función retorna el valor del número PI mediante :
      ____
    4 \     (-1)^n   =  PI 
      /___   2n +1      
      n= 0 

    inputs:

    n: Número de términos a considerar en la serie 

    */ 

    double x= 0.0;

    // se inicia un ciclo for que recorre los términos de la serie 
    for (int i = 0; i < n; i++) {
        
        double termino = 4*pow((-1),i) / (2*i +1);
        //La expresión término se va acutualizando en cada ciclo para cada valor de i 

        x= x + termino;
        // A la variable x se le va sumando el termino en cada paso del ciclo 
        
    }
    
    //salimos del for para retornar el valor que adquirió x en la suma asignada en el for
    return x;

}






double calcularPiSeparado(int n) {
    double suma4k1 = 0.0;
    double suma4k3 = 0.0;

    /*
    Esta función aproxima el valor del número PI utilizando la forma separada de la serie de Leibniz:

        π ≈ 4 * [ 1/(4k+1) - 1/(4k+3) ]

    donde k = 0 hasta n-1

    Parámetros:
        n: Número de términos a considerar en la serie.
    */

    for (int i = 0; i < n; i++) {
        double termino1 = 1.0 / (4.0 * i + 1.0);  // denominadores 4k+1
        double termino2 = 1.0 / (4.0 * i + 3.0);  // denominadores 4k+3

        suma4k1 += termino1;
        suma4k3 += termino2;
    }

    double resultado = 4.0 * (suma4k1 - suma4k3);
    return resultado;
}




int main() {
    int num_terminos;

    // Validar que num_terminos sea positivo usando Do while

    /* Para  asegurarnos de que el usuario ingrese un número positivos 
    se ejecuta el código dentro de while solamente cuando la condición se cumpla. 
    
    
    Se ejecuta el bloque  en do una vez al menos

    Luego evalúa while (num_terminos <= 0), esto es: 

    Si es verdadera (el número ingresado es 0 o negativo), se repite el bucle.
    Si es falsa (el número es positivo), el bucle termina.
    
    */

    do { 
        //
        cout << "¿Cuántos términos deseas usar para la aproximación? ";
        cin >> num_terminos;

        if (num_terminos <= 0) {
            cout << "El número de términos debe ser un entero positivo. Intenta de nuevo.\n";
        }
    } while (num_terminos <= 0);

    // Calculamos PI mediante los dos métodos llamando las funciones anteriores
    double valorPI1 = calcularPiLeibniz(num_terminos);
    double valorPI2 = calcularPiSeparado(num_terminos);

    // Calculamos los  errores absolutos
    double error1 = fabs(valorPI1 - M_PI);
    double error2 = fabs(valorPI2 - M_PI);

    // Resultados.....................................

    cout << "Método 1: Aproximación del número PI con " << num_terminos << " términos usando Leibniz es : " << valorPI1 << endl;
    cout << "Método 2: Aproximación del número PI con " << num_terminos << " términos usando términos separados  : " << valorPI2 << endl;
    cout << "Valor usando cmath :    " << M_PI << endl;

   
    cout << "Error absoluto asociado el método 1: " << error1 << endl;

    cout << "Error absoluto asociado al método 2: " << error2 << endl;

    return 0;
}
