#include <iostream>
#include <fstream>

#include "bmp.h"

BMP::BMP() = default;
BMP::~BMP(){};
BMP::BMP(uint32_t width, uint32_t height){
    info.imageInfo.fWidth = width;
    info.imageInfo.fHeight = height;

    info.fileInfo.fDataOffset = sizeof(info.fileInfo) + sizeof(info.imageInfo);
    
    info.imageInfo.fSizeImage = ((width * info.imageInfo.fBitCount + 31)/32)*4 * height; // ( (width * 3 + 3)/4 ) *4    // w*3 + (4 - (w*3)%4)

    dib.resize(info.imageInfo.fSizeImage);

    info.fileInfo.fSize = info.fileInfo.fDataOffset + info.imageInfo.fSizeImage;
}

    bmpInfo BMP::getInfo(){return info;}
    std::vector<uint8_t> BMP::getData(){return dib;}

void BMP::Read(std::ifstream& file){
    file.read(reinterpret_cast<char*>(&info), sizeof(bmpInfo));
    dib.resize(info.imageInfo.fSizeImage);
    file.read(reinterpret_cast<char*>(dib.data()), dib.size());
}

RGB BMP::GetPixel(uint32_t x, uint32_t y){
    const uint32_t line_bytes = info.imageInfo.fSizeImage / info.imageInfo.fHeight;
    RGB color;
    color.b = dib[3 * x + line_bytes * y + 0];
    color.g = dib[3 * x + line_bytes * y + 1];
    color.r = dib[3 * x + line_bytes * y + 2];
    return color;
}

void BMP::SetPixel(uint32_t x, uint32_t y, const RGB& color){
    const uint32_t line_bytes = info.imageInfo.fSizeImage / info.imageInfo.fHeight;
    dib[3 * x + line_bytes * y + 0] = color.b;
    dib[3 * x + line_bytes * y + 1] = color.g;
    dib[3 * x + line_bytes * y + 2] = color.r;
}

void BMP::write(std::ofstream& outfile) const{
    outfile.write((const char*)(&info), sizeof(bmpInfo));
    outfile.write((const char*)(dib.data()), dib.size());
}

RGB sumRGB(const RGB& col1, const RGB& col2){
    RGB colRes(0,0,0);

    colRes.r = std::max(0, std::min(255, col1.r + col2.r));

    colRes.g = std::max(0, std::min(255, col1.g + col2.g));

    colRes.b = std::max(0, std::min(255, col1.b + col2.b));

    return colRes;
}

RGB cutRGB(const RGB& color, const RGB& light){
    return RGB{std::min(color.r, light.r), std::min(color.g, light.g), std::min(color.b, light.b)};
}

RGB operator*(const RGB& color, float brightness){
    RGB colRes;
    colRes.r = color.r * std::max(0.0f, std::min(brightness, 1.0f));
    colRes.g = color.g * std::max(0.0f, std::min(brightness, 1.0f));
    colRes.b = color.b * std::max(0.0f, std::min(brightness, 1.0f));
    return colRes;
}

RGB operator*(float brightness, const RGB& color){
    RGB colRes;
    colRes.r = color.r * std::max(0.0f, std::min(brightness, 1.0f));
    colRes.g = color.g * std::max(0.0f, std::min(brightness, 1.0f));
    colRes.b = color.b * std::max(0.0f, std::min(brightness, 1.0f));
    return colRes;
}

RGB sky(int n){
    std::vector<RGB> colors;
    std::vector<int> colorPoint;
    int numColors = 5;
    colors.resize(numColors);
    colorPoint.resize(numColors);

    colors[0] = {93, 117, 153};
    colorPoint[0] = 0;

    colors[1] = {93, 117, 153};
    colorPoint[1] = 180;

    colors[2] = {220, 220, 220};
    colorPoint[2] = 240;

    colors[3] = {220, 220, 220};
    colorPoint[3] = 250;

    colors[4] = {105, 98, 94};
    colorPoint[4] = 255;

    // colors[5] = {105, 98, 94};
    // colorPoint[5] = 255;

    if(n>=255){
        return colors[numColors-1];
    }

    for(int i = 0; i < numColors - 1; i++){

        if((n >= colorPoint[i]) && (n < colorPoint[i+1])){

            uint8_t red = (colors[i+1].r * (n - colorPoint[i]) + colors[i].r * (colorPoint[i+1] - n)) / float(colorPoint[i+1]-colorPoint[i]);
            uint8_t green = (colors[i+1].g * (n - colorPoint[i]) + colors[i].g * (colorPoint[i+1] - n)) / float(colorPoint[i+1]-colorPoint[i]);
            uint8_t blue = (colors[i+1].b * (n - colorPoint[i]) + colors[i].b * (colorPoint[i+1] - n)) / float(colorPoint[i+1]-colorPoint[i]);

            return RGB(red, green, blue);
        }
    }
    if(colorPoint[0] >= 0 && n < colorPoint[0]){
        uint8_t red = colors[0].r;
        uint8_t green = colors[0].g;
        uint8_t blue = colors[0].b;

        return RGB(red, green, blue);
    }
    else{
        uint8_t red = (colors[numColors-1].r * (255 - n)) / float(255-colorPoint[numColors-1]);
        uint8_t green = (colors[numColors-1].g * (255 - n)) / float(255-colorPoint[numColors-1]);
        uint8_t blue = (colors[numColors-1].b * (255 - n)) / float(255-colorPoint[numColors-1]);

        return RGB(red, green, blue);
    }
    
}

RGB skyBlur(int n){
    const int size = 5;
    float coeff[size] = {17.0f/273, 66.0f/273, 107.0f/273, 66.0f/273, 17.0f/273};
    RGB res = coeff[0] * sky(n-size/2);
    for(int i = 1; i < size; i++){
        res = sumRGB(res, coeff[i] * sky(n-size/2+i));
    }
    return res;
}