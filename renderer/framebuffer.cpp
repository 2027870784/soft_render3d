#include "framebuffer.hpp"
#include <cmath>
#include <fstream>
#include <iostream>


Framebuffer::Framebuffer(int width, int height){
    this->width = width;
    this->height = height;
    this->colors.resize(width*height, Vector3(0,0,0));
    this->z_buffer.resize(width*height, INFINITY);
}

Framebuffer::~Framebuffer(){
    this->colors.clear();
    this->z_buffer.clear();
}

void Framebuffer::clear(Vector3 color){
    for(int i = 0; i < width*height; i++)
    {
        colors[i] = color;
        z_buffer[i] = INFINITY;
    }
}

void Framebuffer::setPixel(int x, int y, float z, Vector3 color){
    if(z < z_buffer[getIndex(x,y)]){
        colors[getIndex(x,y)] = color;
        z_buffer[getIndex(x,y)] = z;
    }
}

void Framebuffer::saveAsPPM(const std::string& file_path) const{ 
    std::ofstream file(file_path, std::ios::out);
    if(!file.is_open()){
        std::cerr << "Error: Failed to open file " << file_path << std::endl;
        return;
    }
    file << "P3\n" << width << " " << height << "\n255\n";
    for(int i = 0; i < width*height; i++)
    {
        file << (int)(colors[i].r()*255) << " " << (int)(colors[i].g()*255) << " " << (int)(colors[i].b()*255) << std::endl;
    }
}

