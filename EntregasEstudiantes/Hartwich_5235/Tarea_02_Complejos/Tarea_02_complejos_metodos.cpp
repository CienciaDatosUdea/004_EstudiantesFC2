#include "Tarea_02_complejos_clases.h"


complex::complex(double arg1, double arg2, const std::string& mode = "cartesian") : complexBase(arg1, arg2, mode) {}

complexBase::complexBase(double arg1, double arg2, const std::string& mode = "cartesian") {

    if (mode == "cartesian") {
        real = arg1;
        imag = arg2;
        updateRadialCoords();
    } else if (mode == "radial") {
        abs = arg1;
        arg = arg2;
        updateCartesianCoords();
    } else {
        real = 0;
        imag = 0;
        abs = 0;
        arg = 0;
        std::cout << "Warning: unknown mode; mode has to be string \"radial\" or \"cartesian\" (default). Defaulting to real = 0, imag = 0." << std::endl;
    }
}

void complexBase::updateRadialCoords() {
    abs = sqrt(pow(real, 2) + pow(imag, 2));
    arg = ( abs == 0 ? 0 : (real == 0 ? ( imag > 0 ? M_PI/2 : -M_PI/2 ) : atan2(imag, real)));
}

void complexBase::updateCartesianCoords() {
    real = abs * cos(arg);
    imag = abs * sin(arg);
}

double complex::operator[](int i) const {
    if (i == 0) {
        return real;
    } else if (i == 1) {
        return imag;
    }
    std::cout << "Warning: call real part with c[0], imaginary part with c[1]. Other indices will default to return the value 0." << std::endl;
    return 0;
}

double complex::operator[](char c) const {
    if (c == 'r') {
        return abs;
    } else if (c == 'a') {
        return arg;
    }
    std::cout << "Warning: call abs with c['r'], arg with c['a']. Other indices will default to return the value 0." << std::endl;
    return 0;
}

void complex::printCartesian() {
    if (imag >= 0) {
        std::cout << "\t" << real << " + i" << imag << std::endl;
    } else {
        std::cout << "\t" << real << " - i" << std::abs(imag) << std::endl;
    }
}

void complex::printRadial() {
    if (arg > 0) {
        std::cout << "\t" << abs << " * exp(i " << arg << ")" << std::endl;
    } else if (arg < 0 ){
        std::cout << "\t" << abs << " * exp(-i " << std::abs(arg) << ")" << std::endl;
    } else {
        std::cout << "\t" << abs << " * exp(0)" << std::endl;
    }
}

complex complex::operator+(const complex& c) const {
    return complex(real + c[0], imag + c[1]);
}

complex complex::operator-(const complex& c) const {
    return complex(real - c[0], imag - c[1]);
}

complex complex::operator*(const complex& c) const {
    double re2 { c[0] };
    double im2 { c[1] };
    return complex(real * re2 - imag * im2, real * im2 + re2 * imag);
}

complex complex::operator/(const complex& c) const {
    double rad2 { c['r'] == 0 ? std::numeric_limits<double>::infinity() : abs / c['r'] };
    double arg2 { arg * c['a'] };
    double re { rad2 * cos(arg2) };
    double im { rad2 * sin(arg2) };
    return complex(re, im);
}

void complex::operator+=(const complex& c) {
    real += c[0];
    imag += c[1];
    updateRadialCoords();
}

void complex::operator-=(const complex& c) {
    real -= c[0];
    imag -= c[1];
    updateRadialCoords();
}

void complex::operator*=(const complex& c) {
    abs *= c['r'];
    arg += c['a'];
    updateCartesianCoords();
}

void complex::operator/=(const complex& c) {
    abs /= c['r'];
    arg -= c['a'];
    updateCartesianCoords();
}

bool complex::operator==(const complex& c) {
    return (real == c[0] && imag == c[1]);
}