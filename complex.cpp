#include <iostream>
#include "complex.h"

Complex::Complex(){};
Complex::~Complex(){};

Complex::Complex(float a){Re = a;}
Complex::Complex(float a, float b){Re = a; Im = b;}
Complex::Complex(const Complex &c){Re = c.Re; Im = c.Im;}

float Complex::norm(){ return sqrt( Re*Re + Im*Im ); }

Complex Complex::conj(){ return { Re, -Im }; }

std::ostream& operator << (std::ostream &os, const Complex &c){
    if (c.Im < 0) 
    {
        return os << c.Re << " - " << -c.Im << "i";
    }
    return os << c.Re << " + " << c.Im << "i";
}

Complex operator+(const Complex& c1, const Complex& c2)
{
    return { c1.Re + c2.Re, c1.Im + c2.Im };
}

Complex operator-(const Complex& c1, const Complex& c2)
{
    return { c1.Re - c2.Re, c1.Im - c2.Im };
}

Complex operator*(const Complex& c1, const Complex& c2)
{
    return { c1.Re * c2.Re - c1.Im * c2.Im, c1.Re * c2.Im + c1.Im * c2.Re };
}

Complex operator/(const Complex& c, const float& f)
{
    return { c.Re / f, c.Im / f };
}

Complex operator/(const Complex& c1, const Complex& c2)
{
    return { (c1.Re * c2.Re + c1.Im * c2.Im)/(c2.Re * c2.Re + c2.Im * c2.Im),
        (-c1.Re * c2.Im + c1.Im * c2.Re)/(c2.Re * c2.Re + c2.Im * c2.Im) };
}

