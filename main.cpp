#include <iostream>
#include <fstream>
#include "complex.h"
#include "Rect.h"
#include "bmp.h"
#include "vec.h"
#include <vector>

#pragma pack(pop)
RGB nToColor(int n){
    std::vector<RGB> colors;
    std::vector<int> colorPoint;
    int numColors = 5;
    colors.resize(numColors);
    colorPoint.resize(numColors);

    colors[0] = {255, 0, 0};
    colorPoint[0] = 1;

    colors[1] = {255, 255, 0};
    colorPoint[1] = 40;

    colors[2] = {0, 255, 0};
    colorPoint[2] = 80;

    colors[3] = {0, 255, 255};
    colorPoint[3] = 120;

    colors[4] = {0, 0, 255};
    colorPoint[4] = 255;

    if(n==255){
        if(colorPoint[numColors-1]<255){
            return RGB(0, 0, 0);
        }
        else{
            return colors[numColors-1];
        }
    }

    for(int i = 0; i < numColors - 1; i++){

        if((n >= colorPoint[i]) && (n < colorPoint[i+1])){

            uint8_t red = (colors[i+1].r * (n - colorPoint[i]) + colors[i].r * (colorPoint[i+1] - n)) / float(colorPoint[i+1]-colorPoint[i]);
            uint8_t green = (colors[i+1].g * (n - colorPoint[i]) + colors[i].g * (colorPoint[i+1] - n)) / float(colorPoint[i+1]-colorPoint[i]);
            uint8_t blue = (colors[i+1].b * (n - colorPoint[i]) + colors[i].b * (colorPoint[i+1] - n)) / float(colorPoint[i+1]-colorPoint[i]);

            return RGB(red, green, blue);
        }
    }
    if(colorPoint[0] > 0 && n < colorPoint[0]){
        uint8_t red = (colors[0].r * n) / float(colorPoint[0]);
        uint8_t green = (colors[0].g * n) / float(colorPoint[0]);
        uint8_t blue = (colors[0].b * n) / float(colorPoint[0]);

        return RGB(red, green, blue);
    }
    else{
        uint8_t red = (colors[numColors-1].r * (255 - n)) / float(255-colorPoint[numColors-1]);
        uint8_t green = (colors[numColors-1].g * (255 - n)) / float(255-colorPoint[numColors-1]);
        uint8_t blue = (colors[numColors-1].b * (255 - n)) / float(255-colorPoint[numColors-1]);

        return RGB(red, green, blue);
    }
    
}

Complex toC(uint32_t x, uint32_t y, Rect<uint32_t> window, Rect<float> space){
    float re = x/float(window.width()) * space.width() + space.x0;
    float im = y/float(window.height()) * space.height() + space.y0;
    return Complex(re, im);
}

int M(Complex c){
    int n = 0;
    int lim = 1000;
    Complex z = 0;

    for(int i=0; z.norm() < 4; i++){
        z = z*z + c;
        n++;
        if(n>lim){
            n = 0;
            break;
        }
    }
    n = int((n * 255) / float(lim));

    return n;
}

void Calc(BMP& b, const Rect<float> space){
    for(int x=0; x < b.getInfo().imageInfo.fWidth; x++){
        for(int y=0; y < b.getInfo().imageInfo.fHeight; y++){
            int n = M(toC(x, y, Rect<uint32_t> (b.getInfo().imageInfo.fWidth, b.getInfo().imageInfo.fHeight), space));
            RGB color;
            // color.r = n * 15;
            // color.g = n * 15;
            // color.b = n * 15;

            color = nToColor(n*15);

            b.SetPixel(x, y, color);

        }
    }
}

int main() {    
    std::ofstream file("C:\\Users\\Raywud\\Documents\\cpp_prog\\fomin_cpp\\Fractal.bmp", std::ios::binary);
    std::ofstream fileRGB("C:\\Users\\Raywud\\Documents\\cpp_prog\\fomin_cpp\\RGBLine.bmp", std::ios::binary);
    BMP bm(1920, 1080);
    BMP bmRGB(256, 10);
    for(int j = 0; j<10; j++){
        for(int i = 0; i<256; i++){
            bmRGB.SetPixel(i, j, nToColor(i));
        }
    }

    
    Calc(bm, Rect<float>(-0.75, -0.9, -0.3, -0.3));
    // Calc(bm, Rect<float>(-2, -1, 1, 1));
    

    bm.write(file);
    bmRGB.write(fileRGB);


    return 0;
    
}