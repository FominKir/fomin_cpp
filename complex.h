#pragma once
#include <iostream>

class Complex{

    public:
        float Re = 0.0;
        float Im = 0.0;

    // public:
        Complex();
        ~Complex();
        Complex(float a);
        Complex(float a, float b);
        Complex(const Complex &c);

        float norm();
        
        Complex conj();
};

std::ostream& operator << (std::ostream &os, const Complex &c);

Complex operator+(const Complex& c1, const Complex& c2);

Complex operator-(const Complex& c1, const Complex& c2);

Complex operator*(const Complex& c1, const Complex& c2);

Complex operator/(const Complex& c, const float& f);

Complex operator/(const Complex& c1, const Complex& c2);