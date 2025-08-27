#include <cmath>
#include <iostream>


using namespace std;
const int N=10; // Número de partículas

struct particula{ 
    //Definición de la estructura particula
    double x; //posición en x
    double y; //posición en y
    double fx; //fuerza en x
    double fy; //fuerza en y
};

void init_particle(particula *p, double r){   
    // Funcion para inicializar las particulas

    double theta;
    double r1,r2;
    double fx,fy;
    double x, y;
    int i=0;                  
    while(i<N){
        // Angulo aleatorio entre 0 y 2pi
        theta = 2 * M_PI * (double)rand() / RAND_MAX; 
       
        // Radios aleatorios dentro de un circulo de radio r
        r1 = r *(double(rand()) / RAND_MAX);
        r2 = r *(double(rand()) / RAND_MAX);

        // Posicion en coordenadas cartesianas
        x = r1 * cos(theta);    
        y = r2 * sin(theta);

        //Asignacion de los valores x y y para cada particula
        p[i].x = x;
        p[i].y = y;
        p[i].fx= (double(rand()) / RAND_MAX); // Fuerza en x aleatoria
        p[i].fy= (double(rand()) / RAND_MAX); // Fuerza en y aleatoria
        i++;
    }}

void pertubation(particula *p, double delta ){
    // Funcion que perturba aleatoriamente las particulas
    double dx, dy;
    for(int i=0;i<N;i++){
        // Valor aleatorio entre -delta y delta
        dx = ((double)rand() / RAND_MAX) * 2 *delta - delta;
        dy = ((double)rand() / RAND_MAX)* 2 *delta - delta;

        // Actualizacion de la posicion de cada particula
        p[i].x += dx;
        p[i].y += dy;
    }
}

double max_distance(particula *p){
    // Funcion que calcula la distancia máxima entre todas las particulas
    double max_dist = 0.0;
    for(int i=0;i<N;i++){
        // Calcula la distancia entre cada par de particulas
        for(int j=0;j<N;j++){
        double dist = sqrt((p[i].x - p[j].x ) * (p[i].x - p[j].x ) + (p[i].y - p[j].y)*(p[i].y - p[j].y));
        if(dist > max_dist){
            // Actualiza la distancia máxima si se encuentra una mayor
            max_dist = dist;
        }
        }
    }
    return max_dist;
}

double total_force(particula *p){
    //Funcion que calcula la fuerza total sobre las particulas
    double fx = 0.0;
    double fy = 0.0;
    for(int i=0;i<N;i++){
        // Suma las fuerzas en x e y de cada particula
        fx += p[i].fx;
        fy += p[i].fy;
    }
    // Retorna la magnitud de la fuerza total
    return sqrt(fx * fx + fy * fy);
}


int main(){
    double radio = 1.0; // radio del circulo
    double delta = 0.1; // Valor máximo de perturbación
    double max_dist = 0.0;
    double force_abs;


   srand(0); // Semilla para reproducibilidad

    particula part[N];  //Arreglo de particulas

    // Inicialización de las particulas  
    init_particle(part, radio);

    cout<<"Posicion inicial de cada particula "<<": "<<endl;
    for(int i=0;i<N;i++){
        cout<<part[i].x<< " ,"<<part[i].y<<endl;
    }
    // Perturbación de las particulas
    pertubation(part, delta);

    cout<<"Posicion perturbada de cada particula "<<": "<<endl;   
    for(int i=0;i<N;i++){
        cout<<part[i].x<< " ,"<<part[i].y<<endl;
    }

    // Cálculo de la distancia máxima y la fuerza total
    max_dist = max_distance(part);
    force_abs = total_force(part);

    cout<<"La distancia maxima entre particulas es: "<<max_dist<<endl;
    cout<<"La fuerza total sobre las particulas es: "<<force_abs<<endl;

    return 0;      
}