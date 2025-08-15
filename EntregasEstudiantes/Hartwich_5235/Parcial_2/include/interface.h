#include<vector>
#include<optional>
#include<string>
#include<fstream>

// clase que contiene la geometría espacial (red discretizada de z)
class Grid {
    public:
        Grid(
            double z_min,
            double z_max,
            size_t n_z
        );
        const double z_min_;
        const double z_max_;
        const size_t n_z_;
        const double dz_;
        const std::vector<double> z_;
    private:
        // calcular dz
        double DZWrapper(
            double z_min,
            double z_max,
            size_t n_z
        ) const;
        // crear el vector con los valores
        std::vector<double> GridWrapper(
            double z_min,
            double z_max,
            size_t n_z
        ) const;
};

// clase que contiene los campos eléctricos y magnéticos
// tiene miembros para aplicar la condición inicial y las condiciones reflectivas de los campos
// omitiendo los índices de los campos: e_ representa E_x, h_ representa H_y
class Fields {
    public:
        Fields(const Grid& g);
        const Grid& g_;
        std::vector<double> e_;
        std::vector<double> h_;
        void ApplyEBoundaryCondition();
        void ApplyHBoundaryCondition();
    private:
        void ApplyInitialCondition(const Grid& g);
};

// clase que contiene la lógica para evolucionar los campos en el tiempo
class Solver {
    public:
        Solver(
            const Fields& f,
            double t_end,
            double dt,
            bool reflective_boundaries = false,
            bool log_full_evolution = false,
            int logs = 0
        );
        const Fields& get_fields_() const;
    private:
        std::optional<Fields> final_fields_;
        const double t_end_;
        const double dt_;
        const bool reflective_boundaries_;
        const bool log_full_evolution_;
        const int logs_;
        void Run(const Fields& f);
};

// función para escribir los resultados a un archivo .txt
void WriteFieldsToTxt(
    const std::string& filename,
    const Fields& f
);