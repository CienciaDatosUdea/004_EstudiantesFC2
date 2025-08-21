# include <cstdio>
# include <iostream>
# include <cmath>
# include "include.h"

using namespace std;


int main(){
    op_complejos a(1, 0);
    op_complejos b(0, 1);
    op_complejos c(1, 1);

    cout << "Sean los numeros complejos: " << endl;
    cout << "a: " << endl;
    a.get_complejos();

    cout << "b: " << endl;
    b.get_complejos();

    auto apb = a.operator+(b);
    auto amb = a.operator-(b);
    auto amultb = a.operator*(b);
    auto adivb = a.operator/(b);

    cout << "a+b = " << endl;
    apb.get_complejos();

    cout << "a-b = " << endl;
    amb.get_complejos();

    cout << "a*b = " << endl;
    amultb.get_complejos();

    cout << "a/b = " << endl;
    adivb.get_complejos();

  
    return 0;
}