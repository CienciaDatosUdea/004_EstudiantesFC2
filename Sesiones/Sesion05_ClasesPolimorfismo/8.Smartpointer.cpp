#include <iostream>

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
    Perro* p = new Perro("Firulais");
    p->ladrar();
    delete p;  // ¡IMPORTANTE! Si lo olvidas, hay fuga de memoria

    std::unique_ptr<Perro> p = std::make_unique<Perro>("Firulais");
    p->ladrar();
    // No necesitas delete → se destruye automáticamente al salir del main()
    return 0;

}


