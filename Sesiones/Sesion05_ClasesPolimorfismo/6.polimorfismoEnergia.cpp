#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

class Energia {
public:
    virtual double calcular() const = 0;
    virtual ~Energia() = default;
};

class EnergiaCinetica : public Energia {
    double masa, velocidad;
public:
    EnergiaCinetica(double m, double v) : masa(m), velocidad(v) {}
    double calcular() const override {
        return 0.5 * masa * velocidad * velocidad;
    }
};

class EnergiaPotencialGravitacional : public Energia {
    double masa, altura;
    static constexpr double g = 9.81;
public:
    EnergiaPotencialGravitacional(double m, double h) : masa(m), altura(h) {}
    double calcular() const override {
        return masa * g * altura;
    }
};

class EnergiaElastica : public Energia {
    double k, x;
public:
    EnergiaElastica(double constante, double deformacion)
        : k(constante), x(deformacion) {}
    double calcular() const override {
        return 0.5 * k * x * x;
    }
};

int main() {
    // Vector de punteros inteligentes a diferentes energías
    std::vector<std::unique_ptr<Energia>> energias;

    energias.push_back(std::make_unique<EnergiaCinetica>(2.0, 3.0));           // 9 J
    energias.push_back(std::make_unique<EnergiaPotencialGravitacional>(1.0, 10.0)); // 98.1 J
    energias.push_back(std::make_unique<EnergiaElastica>(100.0, 0.1));         // 0.5 J

    double energia_total = 0.0;

    std::cout << "Energías individuales:\n";
    for (const auto& e : energias) {
        double valor = e->calcular();
        std::cout << "  - " << valor << " J\n";
        energia_total += valor;
    }

    std::cout << "Energía total: " << energia_total << " J\n";

    return 0;
}
