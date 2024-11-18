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