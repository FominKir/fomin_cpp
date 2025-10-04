#include "Texture.h"

Texture::~Texture(){};
Texture::Texture(){
    rgb = RGB(200, 200, 200);
}
Texture::Texture(const RGB& color){
    rgb.r = color.r;
    rgb.g = color.g;
    rgb.b = color.b;
}

RGB Texture::getColor(){
    return rgb;
}