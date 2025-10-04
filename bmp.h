#pragma once
#include <iostream>
#include <fstream>
#include "complex.h"
#include <vector>

#pragma pack(push, 1)
struct bfi {
    uint16_t fSignature = 19778;
    uint32_t fSize = 0;
    uint32_t fReserved = 0;
    uint32_t fDataOffset = 0;
};

struct cfi {
    uint32_t fSize = 40;
    uint32_t fWidth = 0;
    uint32_t fHeight = 0;
    uint16_t fPlanes = 1;
    uint16_t fBitCount = 24;
    uint32_t fCompression = 0;
    uint32_t fSizeImage = 0;
    uint32_t XpixelsPerM = 0;
    uint32_t YpixelsPerM = 0;
    uint32_t ColorsUsed = 0;
    uint32_t ColorsImportant = 0;
};

struct bmpInfo {
    bfi fileInfo;
    cfi imageInfo;
};

struct RGB {
    uint8_t r, g, b;

    RGB() = default;
    ~RGB(){};
    
    RGB(uint8_t ri, uint8_t gi, uint8_t bi){
        r = ri;
        g = gi;
        b = bi;
    }
    RGB(const RGB& color){
        r = color.r;
        g = color.g;
        b = color.b;
    }
};

RGB sumRGB(const RGB& col1, const RGB& col2);
RGB cutRGB(const RGB& color, const RGB& light);
RGB operator*(const RGB& color, float brightness);
RGB operator*(float brightness, const RGB& color);
RGB sky(int n);
RGB skyBlur(int n);

class BMP{
    private:
        bmpInfo info;
        std::vector<uint8_t> dib;
    public:
        BMP();
        ~BMP();
        BMP(uint32_t width, uint32_t height);

        bmpInfo getInfo();
        std::vector<uint8_t> getData();

        void Read(std::ifstream& file);
        RGB GetPixel(uint32_t x, uint32_t y);
        void SetPixel(uint32_t x, uint32_t y, const RGB& color);
        void write(std::ofstream& outfile) const;
};
