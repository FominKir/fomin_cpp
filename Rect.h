#pragma once
#include <iostream>

template<typename T>
struct Rect
{
    T x0 = 0, y0 = 0;
    T x1 = 0, y1 = 0;

    T width() const{
        return (x1 - x0);
    }

    T height() const{
        return (y1 - y0);
    }

    Rect() = default;

    Rect(T w, T h){
        x0 = 0;
        y0 = 0;
        x1 = w;
        y1 = h;
    };

    Rect(T x0, T y0, T x1, T y1){
        this->x0 = x0;
        this->y0 = y0;
        this->x1 = x1;
        this->y1 = y1;
    };

};

