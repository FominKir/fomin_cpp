#pragma once
#include "../bmp.h"

class Texture{
    RGB rgb{200, 200, 200};

    public:
    ~Texture();
    Texture();
    Texture(const RGB& color);
    
    RGB getColor();
};