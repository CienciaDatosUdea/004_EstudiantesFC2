#include "complejos.h"
class op_complejos: public complejos{
    public:
        op_complejos(double x0, double y0);
    
        double magnitud_complejo() ;       
        op_complejos operator+(complejos &ob);
    /*
    Construir las otras clases heredades que permita realizar la suma, resta 
    multiplcacion y division entre complejos
    */   
};

