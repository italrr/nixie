#include <stdio.h>
#include <cmath>

#define STB_IMAGE_IMPLEMENTATION

#include "3rdparty/stb_image.h"
#include "TN.hpp"
#include "Tools.hpp"



nx::Bitmap::Bitmap(){
    pixels = NULL;
    size.set(0);
}
nx::Bitmap::Bitmap(unsigned w, unsigned h, const nx::Color &fill){
    this->create(w, h, fill);
}
nx::Bitmap::~Bitmap(){
    clear();
}

void nx::Bitmap::clear(){
    if(pixels != NULL){
        delete this->pixels;
        this->pixels = NULL;
        size.set(0);
    }
}

nx::Pixel nx::Bitmap::sample(int x, int y){
    if(x < 0 || x >= this->size.x || y < 0 || y >= this->size.y){
        return nx::Pixel(0);
    }else{
        return this->pixels[x + this->size.x * y];
    }
}

bool nx::Bitmap::load(const std::string &path){
    
    if(!nx::File::exists(path)){
        printf("Failed to load %s: it doesn't exist\n", path.c_str());
        return false;
    }

    int width, height, nrChannels;
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0); 
    this->size.x = width;
    this->size.y = height;    

    this->create(width, height, nx::Color(0));

    for(int i = 0; i < width * height * nrChannels; i += 4){
        #define uchar unsigned char
        uchar &r = data[i];
        uchar &g = data[i + 1];
        uchar &b = data[i + 2];
        uchar &a = data[i + 3];
        this->pixels[i/4] = nx::Pixel(r, g, b, a);
    }

    stbi_image_free(data);

    printf("Loaded Bitmap: %s (%ix%i)\n", path.c_str(), width, height);


    return true;
}

void nx::Bitmap::create(unsigned w, unsigned h, const nx::Color &fill){
    clear();
    this->pixels = new nx::Pixel[w * h];
    for(unsigned x = 0; x < w; ++x){
        for(unsigned y = 0; y < h; ++y){
            this->pixels[x + y * w] = nx::Pixel(fill);
        }
    }
}



bool nx::Draw::Bitmap(nx::Bitmap *bm, const nx::v2<int> &pos, const nx::v2<int> &size, const nx::v2<float> &origin, float angle){

    for(unsigned x = 0; x < bm->size.x; ++x){
        for(unsigned y = 0; y < bm->size.y; ++y){
            auto &pixel = bm->pixels[x + y * bm->size.y];
            
            int _x = x;
            int _y = y;

            if(angle != 0){
                float _a = angle * (3.14159265358979323846f / 180.0f);
                float r = std::sqrt(x*x + y*y);
                _x = std::cos(_a) * r;
                _y = std::sin(_a) *r;
            }

            nx::Draw::Pixel((pos.x - origin.x * size.x) + _x, (pos.y - origin.y * size.y) + _y, pixel);
        }
    }

    return true;
}