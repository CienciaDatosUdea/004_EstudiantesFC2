# include <cstdio>
# include <iostream>
# include <cmath>

using namespace std;

class complejos{  //Esta clase representa un número complejo con parte real y parte imaginaria
    protected:   // Protected significa que las clases hijas pueden acceder, pero desde fuera del objeto no se pueden usar directamente.
        double real;
        double imag;
    public: 
        //Cosntructor de la clase 
        complejos(double x0, double y0): real(x0), imag(y0) {}; //Esto es una lista de inicialización: 
        // Es como decir: “cuando alguien cree un complejos, inicialízalo con real = x0 y imag = y0”.
        void get_complejos(){
            cout<<real<<" + "<<imag<<"i"<<" \n";
        }       
        double get_real(){return real;}; // Estos "getters" permiten obtener las partes real e imaginaria desde fuera de la clase.
        double get_imag(){return imag;};
    };

    
class op_complejos: public complejos{ //Hereda de complejos y le agrega operaciones.
    //Esto dice: "Voy a crear una clase que hereda de complejos y le voy a agregar más cosas."
    public:
        op_complejos(double x0, double y0): complejos(x0,y0) {}; //Llama al constructor de la clase base.
    
    double magnitud_complejo(){
        return sqrt(real * real + imag * imag);
    };

    complejos operator+(complejos &ob) {
        return op_complejos(real + ob.get_real(), imag + ob.get_imag());    
    };   
    /*
    Construir las otras clases heredades que permita realizar la suma, resta 
    multiplcacion y division entre complejos
    */

    op_complejos operator-(complejos &ob) {
        return op_complejos(real - ob.get_real(), imag - ob.get_imag()); 
    };

    op_complejos operator*(complejos &ob) {
        return op_complejos(real * ob.get_real() - imag * ob.get_imag(), real * ob.get_imag() + imag * ob.get_real());
    };

    op_complejos operator/(complejos &ob) {
        double denom = ob.get_real() * ob.get_real() + ob.get_imag() * ob.get_imag();
        if (denom == 0) {
        throw std::runtime_error("División por cero en número complejo.");
}
        return op_complejos((real * ob.get_real() + imag * ob.get_imag()) / denom, (imag * ob.get_real() - real * ob.get_imag()) / denom);
    };
    
};

int main(){
    complejos a(0, 0); // La clase complejos crea el objeto 0+0i
    complejos b(0, 0);
    complejos c(1, 2);

    c.get_complejos();  //  Muestra c por consola
    op_complejos pp(2,1); //Se crea un objeto de la clase derivada op_complejos llamado pp = 2 + 1i
    pp.magnitud_complejo(); 
    cout << "Magnitud de pp: " << pp.magnitud_complejo() << endl; //Para mostrar la magnitud de pp
    pp.get_complejos(); //Muestra pp por consola

    b = pp + c; //Suma pp y c, y el resultado se guarda en b.
    cout << "pp + c: "; 
    b.get_complejos(); //Muestra el resultado de la suma por consola

    a=pp-c; //Resta pp y c, y el resultado se guarda en a.
    cout << "pp - c: "; 
    a.get_complejos(); //Muestra el resultado de la resta por consola

    // Multiplicación de pp * C
    c = pp * c;
    cout << "pp * c: "; 
    c.get_complejos();

    // División de pp / C

    c=pp/c;
    cout << "pp / c: ";
    c.get_complejos();
    return 0;
}