#include <iostream>
#include <cmath>
#define _USE_MATH_DEFINES


class Shape {
public:
    Shape()=default;
    virtual double area() const = 0;
    virtual ~Shape()=default;

};

class Circulo: public Shape{
    private:
        double radio;
    public:
        Circulo(double radio0): radio(radio0){};

        double area() const override  {
           return M_PI*radio*radio;
        }

};

class Triangulo: public Shape{
    private:
        double b,h;
    public:
        Triangulo(double b0, double h0): b(b0), h(h0) {};

        double area() const override  {
           return b*h*1.0/2;
        }

};



int main() {
    Circulo a(10.0);
    
    
    Shape* ptr = &a;     
    std::cout << ptr->area() << "\n";  //  polimorfismo dinámico
    
    return 0;
}
    