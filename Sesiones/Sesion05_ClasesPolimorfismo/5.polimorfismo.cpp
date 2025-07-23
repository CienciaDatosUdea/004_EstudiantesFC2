#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

class Shape {
public:
    virtual double area() const = 0;
    virtual ~Shape() = default;
};

class Circulo : public Shape {
    double radio;
public:
    Circulo(double r) : radio(r) {}
    double area() const override {
        return M_PI * radio * radio;
    }
};

class Triangulo : public Shape {
    double b, h;
public:
    Triangulo(double base, double altura) : b(base), h(altura) {}
    double area() const override {
        return 0.5 * b * h;
    }
};

int main() {


    // make_unique: Puntero inteligente
    ///Crea un puntero inteligente (unique_ptr) llamado ptr que apunta a un objeto Circulo 
    // de radio 10.0, pero lo trata como si fuera de tipo Shape.
    //Voy a tratar a este objeto Circulo como si fuera un Shape (clase base), 
    // pero sin preocuparme de liberar la memoria
    std::vector<std::unique_ptr<Shape>> figuras;

    figuras.push_back(std::make_unique<Circulo>(5.0));
    figuras.push_back(std::make_unique<Triangulo>(3.0, 4.0));
    figuras.push_back(std::make_unique<Circulo>(2.0));

    for (const auto& figura : figuras) {
        std::cout << "Área: " << figura->area() << "\n";  // Llamada polimórfica
    }

    return 0;
}
