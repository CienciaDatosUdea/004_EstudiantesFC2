#include <iostream>
#include <memory>

class Perro {
public:
    Perro(const std::string& nombre) : nombre(nombre) {
        std::cout << "Perro " << nombre << " creado\n";
    }

    ~Perro() {
        std::cout << "Perro " << nombre << " destruido\n";
    }

    void ladrar() const {
        std::cout << nombre << " dice: ¡Guau!\n";
    }

private:
    std::string nombre;
};

int main() {
    Perro* p1 = new Perro("Firulais");
    p1->ladrar();
    delete p1;  // ¡IMPORTANTE! Si lo olvidas, hay fuga de memoria

    std::unique_ptr<Perro> p2 = std::make_unique<Perro>("Firulais");
    p2->ladrar();
    // No necesitas delete → se destruye automáticamente al salir del main()
    return 0;

}


