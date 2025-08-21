#include <iostream>
#include <string>
#include <cmath>
#define _USE_MATH_DEFINES

class complexBase {
    protected:
        double real {};
        double imag {};
        double abs {};
        double arg {};

    public:
        complexBase(double, double, const std::string&);
        void updateRadialCoords();
        void updateCartesianCoords();
};

class complex : public complexBase {
    public:
        complex(double, double, const std::string& mode = "cartesian");
        void printCartesian();
        void printRadial();
        double operator[](int) const;  
        double operator[](char) const; 
        complex operator+(const complex&) const;
        complex operator-(const complex&) const;
        complex operator*(const complex&) const;
        complex operator/(const complex&) const;
        void operator+=(const complex&);
        void operator-=(const complex&);
        void operator*=(const complex&);
        void operator/=(const complex&);
        bool operator==(const complex&);
};
