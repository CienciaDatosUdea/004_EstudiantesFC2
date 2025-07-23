#include "Tarea_02_complejos_metodos.cpp"

int main() {        

    complex c(-1, 0);

    // output descriptivo
    std::cout << "Define some complex object, test printCartesian() and printRadial() and assure that accessing coordinates with operator[] yields the same result:" << std::endl;

    // testing print cartesian
    std::cout << "\nc";
    c.printCartesian();

    // testing operator[] with arguments 0, 1 (should yield same result as c.print_cartesian())
    std::cout << "c";
    std::cout << "\t" << c[0] << " + i" << c[1] << std::endl;

    // testing print radial
    std::cout << "c";
    c.printRadial();

    // testing operator[] with arguments 'r', 'a' (should yield same result as c.print_radial())
    std::cout << "c";
    std::cout << "\t" << c['r'] << " * exp(i " << c['a'] << ")" << std::endl;

    // testing addition
    std::cout << "\nDefine a second complex object and test operator+, operator+= and operator==" << std::endl;
    complex u(1,0);
    std::cout << "\nu";
    u.printCartesian();
    complex v = c + u;
    std::cout << "c + u" ;
    v.printCartesian();

    // testing operator+=
    c += u;
    std::cout << "c += u";
    c.printCartesian();

    // testing operator==
    std::cout << "After c+=u, is c the same as c+u was before? -> " << std::boolalpha << (c == v) << std::endl;

    // testing operator/=
    std::cout << "\nDefine two more complex objects and test oparator/=" << std::endl;
    complex w(0,-1);
    std::cout << "\nw";
    w.printCartesian();

    complex z(0, 1);
    std::cout << "z";
    z.printCartesian();
    
    z /= w;
    std::cout << "z /= w";
    z.printCartesian();
    std::cout << "Result is correct up to machine precision." << std::endl;

    std::cout << std::endl;

    return 0;

}