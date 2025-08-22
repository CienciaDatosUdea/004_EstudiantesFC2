#include <fstream>
#include <vector>
#include <string>

class Grid{
	public:
	Grid(double dz, double dt, int K, int N);
	double dz; //espacio entre puntos
	double dt; //espacio entre puntos temporales

	int K; //número de nodos espaciales
	int N; //número de nodos temporales

};

class Writer;

class Fields{
	double beta;
	public:
	Fields(Grid &G,double C, std::string bc_type);
	Grid G;
	double C; //velocidad de la onda
	std::string bc_type; //tipo de condición de frontera
	double t0; //tiempo actual de la simulación

	std::vector<double> H; //campo magnético
	std::vector<double> E; //campo eléctrico

	void initial_conditions();
	void boundary_conditions(std::vector<double>,std::vector<double>);

	void update_fields();
	void run_simulation(Writer* writer = nullptr);
};

class Writer{
public:
	Writer(const std::string &filename);
	std::ofstream file;
	void writeFields(Fields const &F);

};
