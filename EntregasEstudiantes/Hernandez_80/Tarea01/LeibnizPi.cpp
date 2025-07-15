//Calculo de pi con la serie de leibniz

#include<iostream>
#include<cmath>

using namespace std;

float serie(int);

float serie2(int);



int main(){int n, numero;

    cout<<"Introduzca cuantos términos quiere para la aproximación de pi"<<endl;
    cin>>n;

    cout<<"Con el método 1, pi es igual a: "<<serie(n)<<endl;
    cout<<"Con el método 2, pi es igual a: "<<serie2(n)<<endl;
    

    return 0;
}

float serie(int n){float s=0;

    for(int i=0; i<=n; i++){
        s+= (pow(-1,i))/(2*i +1);
    }
    return 4*s;
}

float serie2(int n){float s, t1=0, t2=0;

    for(int i=1; i<=(n+1)/2;i=i+4){
        t1 += 1./i;
        t2 += 1./(i+2);
    }


    s = t1-t2;

    return 4*s;
}

