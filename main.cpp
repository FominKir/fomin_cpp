#include <iostream>
#include <fstream>
#include "complex.h"
#include <vector>
#pragma pack(push, 1)

struct bfi {
    uint16_t fSignature=19778;
    uint32_t fSize = 0;
    uint32_t fReserved=0;
    uint32_t fDataOffset;
};

struct cfi {

    uint32_t fSize=40;
    uint32_t fWidth = 0;
    uint32_t fHeight = 0;
    uint16_t fPlanes=1;
    uint16_t fBitCount=24;
    uint32_t fCompression=0;
    uint32_t fSizeImage=0;
    uint32_t XpixelsPerM=0;
    uint32_t YpixelsPerM=0;
    uint32_t ColorsUsed=0;
    uint32_t ColorsImportant=0;

};

struct BMP {
    bfi fileInfo;
    cfi imageInfo;
};

struct RGB {
    uint8_t r, g, b;

    RGB() = default;

    RGB(uint8_t ri, uint8_t gi, uint8_t bi){
        r = ri;
        g = gi;
        b = bi;
    }
};


struct bmpImage {
    BMP bmp;
    std::vector<uint8_t> dib;
    uint32_t row_stride;

    bmpImage() = default;
    ~bmpImage(){};

    bmpImage(uint32_t width, uint32_t height){
        bmp.imageInfo.fWidth = width;
        bmp.imageInfo.fHeight = height;

        bmp.fileInfo.fDataOffset = sizeof(bmp.fileInfo) + sizeof(bmp.imageInfo);
        
        row_stride = width * 3 + 1;
        dib.resize(row_stride * height);
 
        int32_t new_stride = make_stride_aligned(4);
        bmp.fileInfo.fSize = bmp.fileInfo.fDataOffset + dib.size()/* + bmp.imageInfo.fHeight * (new_stride - row_stride)*/;
    }

    uint32_t make_stride_aligned(uint32_t align_stride) {
        uint32_t new_stride = row_stride;
        while (new_stride % align_stride != 0) {
            new_stride++;
        }
        return new_stride;
    }

    void Read(std::ifstream& file) {
        file.read(reinterpret_cast<char*>(&bmp), sizeof(BMP));
        dib.resize(bmp.imageInfo.fSizeImage);
        file.read(reinterpret_cast<char*>(dib.data()), dib.size());
    };

    RGB GetPixel(uint32_t x, uint32_t y) const {
        const uint32_t line_bytes = bmp.imageInfo.fSizeImage / bmp.imageInfo.fHeight;
        RGB color;
        color.b = dib[3 * x + line_bytes * y + 0];
        color.g = dib[3 * x + line_bytes * y + 1];
        color.r = dib[3 * x + line_bytes * y + 2];
        return color;   
    }

    void SetPixel(uint32_t x, uint32_t y, const RGB& color) {
        const uint32_t line_bytes = bmp.imageInfo.fSizeImage / bmp.imageInfo.fHeight;
        dib[3 * x + line_bytes * y + 0] = color.b;
        dib[3 * x + line_bytes * y + 1] = color.g;
        dib[3 * x + line_bytes * y + 2] = color.r;
    }

    void write(std::ofstream& outfile) const {
        outfile.write((const char*)(&bmp), sizeof(BMP));
        outfile.write((const char*)(dib.data()), dib.size());
    }

};

#pragma pack(pop)

Complex toC(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
    float re = x/float(w) * 3 - 2;
    float im = y/float(h) * 2 - 1;
    return Complex(re, im);
}

int M(Complex c){
    int n = 0;
    Complex z = 0;

    for(int i=0; z.norm() < 2; i++){
        z = z*z + c;
        n++;
        if(n>10){break;}
    }

    return n;
}

void Calc(bmpImage& b){
    for(int x=0; x < b.bmp.imageInfo.fWidth; x++){
        for(int y=0; y < b.bmp.imageInfo.fWidth; y++){
            int n = M(toC(x, y, b.bmp.imageInfo.fWidth, b.bmp.imageInfo.fHeight));
            RGB color;
            color.r = n;
            color.g = n;
            color.b = n;
            b.SetPixel(x, y, color);
        }
    }
}

int main() {
    
    bmpImage bm;

    {
    std::ifstream file("C:\\Users\\Raywud\\Downloads\\test.bmp", std::ios::binary);

    bm.Read(file);
    
    RGB rgb1 = bm.GetPixel(5, 5);

    RGB color(1, 1, 1);

    bm.SetPixel(1, 1, color);
    }

    
    std::ofstream newFile("C:\\Users\\Raywud\\Downloads\\newnewTest.bmp", std::ios::binary);

    bmpImage bm123(100, 100);

    bm123.write(newFile);
    
    std::cout << sizeof(bm) << std::endl;
    std::cout << sizeof(bm123) << std::endl;

    return 0;
    
}