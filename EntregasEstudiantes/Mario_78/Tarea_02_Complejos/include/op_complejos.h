#include "complejos.h"
class op_complejos: public complejos{
    public:
        op_complejos(double x0, double y0);
    
        double magnitud_complejo() ;                  // Magnitud (módulo)    
        op_complejos operator+(complejos &ob);        // Suma
    /*
    Construir las otras clases heredades que permita realizar la suma, resta 
    multiplcacion y division entre complejos
    */ 
        op_complejos operator-(complejos &ob);       // Resta
        op_complejos operator*(complejos &ob);       // Multiplicación
        op_complejos operator/(complejos &ob);       // Division
    
};

