#include <iostream>     
#include <cmath>        
#include <random>       
#include <ctime>        

const int N = 10; 

/*
 Función que devuelve una referencia a un generador de números aleatorios
 Estático: se inicializa solo una vez y se conserva durante toda la ejecución del programa.
 */
std::mt19937_64& global_rng() {
    static std::mt19937_64 rng{ /*semilla*/ }; // Puede agregarse una semilla para resultados reproducibles
    return rng;
}

/*
 Función que genera un número aleatorio uniforme en el rango [a, b]
 Utiliza el generador global de 64 bits.
 */
double random_number(double a, double b) {
    std::uniform_real_distribution<double> dist(a, b); // Distribución uniforme entre a y b
    return dist(global_rng()); // Genera el número usando el generador global
}


struct particula {         //  Partícula en el plano (x, y)
 
 
private:
    double x; 
    double y; 

public:
    // Constructor por defecto: posiciona la partícula en el origen
    particula() : x(0), y(0) {}


    double fx; //Fuerza en x.
    double fy; // Fuerza en y.
    
      //Método que inicializa la posición de la partícula
     // Se elige un ángulo aleatorio y se coloca la partícula sobre la circunferencia unitaria
     
    void init_configuracion() {
        double theta = random_number(0, 2 * M_PI); // Ángulo aleatorio entre 0 y 2π
        x = cos(theta); // Posición x
        y = sin(theta); // Posición y
    }

    
     // Método para actualizar la posición sumando un desplazamiento
     
    void update_position(double delta_x, double delta_y) {
        x = x + delta_x;
        y = y + delta_y;  
    }

    // Método para asignar una fuerza a cada partícula.

    void asig_fuerza (){
        fx = random_number(-1,1);
        fy = random_number(-1,1); 
    }

    // Getters para obtener coordenadas
    double get_x() { 
        return x; }
    double get_y() { 
        return y; }
};

 //sistema de partículas
 
struct sistema {
private:
    std::vector<particula> p; // Vector que contiene las partículas. 
    
public:  

    double valor_minimo; // Distancia mínima entre pares de partículas
    double valor_max;  // Distancia máxima entre pares de partículas.

    // Constructor: inicializa el sistema con N partículas
    sistema(int N) : p(N) {}

    
     // Inicializa todas las partículas en posiciones aleatorias sobre el círculo unitario
     
    void init_all_particles() {
        for (auto& v : p) {
            v.init_configuracion();
            double delta_x = random_number(0,0.1);
            double delta_y = random_number(0,0.1);
            v.update_position(delta_x,delta_y);
            v.asig_fuerza();
           
            std::cout << v.get_x()<<"           "<<v.get_y() << "\n"; // Imprime la posición x de cada partícula
        }
    }

    // Devuelve la posición x de la i-ésima partícula
    double posicion_i_esima_x(int i) {
        return p[i].get_x();
    }

    // Sobrecarga del operador [] para acceder a partículas directamente
    particula& operator[](int i) {
        return p[i];
    }

    
     /* Calcula la distancia mínima entre todas las partículas del sistema
        Se compara cada par (i, j) distinto y se guarda el menor valor */
    
    void distancia_minima() {
        double dx, dy, dij;
        double R = 10000000.0; // Inicialización con un valor grande

        for (int i = 0; i < N; i++) {             // Recorre cada partícula i
            for (int j = 0; j < N; j++) {         // Compara con otra partícula j
                if (i == j)
                    continue; // Ignora comparación de una partícula consigo misma
                dx = p[i].get_x() - p[j].get_x();
                dy = p[i].get_y() - p[j].get_y();
                dij = sqrt(dx * dx + dy * dy); // Distancia euclideana entre i y j
                if (dij < R)
                    R = dij; // Guarda la menor distancia encontrada
            }
        }
        valor_minimo = R; // Guarda resultado en el atributo del sistema
    }

      void distancia_max() { //distancia máxima entre todas las partículas.
        double dx, dy, dij;
        double D;

        for (int i = 0; i < N; i++) {             // Recorre cada partícula i
            for (int j = 0; j < N; j++) {         // Compara con otra partícula j
                if (i == j)
                    continue; // Ignora comparación de una partícula consigo misma
                dx = p[i].get_x() - p[j].get_x();
                dy = p[i].get_y() - p[j].get_y();
                dij = sqrt(dx * dx + dy * dy); // Distancia euclideana entre i y j
                if (dij >0)
                    D = dij; // Guarda la mayor distancia encontrada.
            }
        }
        valor_max= D; // Guarda resultado en el atributo del sistema
    }

    void calc_fuerza (){          // Calcula la fuerza resultante de las partículas

        double Fx_total = 0.0;
        double Fy_total = 0.0;

       
        for (const auto& v : p) {   
            Fx_total += v.fx;
            Fy_total += v.fy;
        }

         double F_total = sqrt(Fx_total * Fx_total + Fy_total * Fy_total);
         std::cout<< "La fuerza total del sistema es: "<<Fx_total << " en dirección x, "<<Fy_total<< " en dirección y"<<"\n"; 
    }
};


int main(int argc, char* argv[]) {
   
   
    sistema s(N);         // Crea un sistema con N partículas
    std::cout << "Posición en x   "<< "  Posición en y"<< "\n"; // Imprime la posición x,y de cada partícula
    s.init_all_particles(); // Inicializa posiciones aleatorias
    s.distancia_minima();   // Calcula la distancia mínima entre partículas.
    s.distancia_max();  //Calcula la distancia máxima entre partículas. 
    std::cout << "la distancia mínima entre partículas es: "<< s.valor_minimo << "\n"; // Muestra la distancia mínima.
    std::cout << "la distancia máxima entre partículas es: "<< s.valor_max << "\n"; // Muestra la distancia máxima.
    s.calc_fuerza(); // Calcula la fuerza total.
  

    
    return 0;
}
