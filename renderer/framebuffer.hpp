#pragma once
#include "math3d.hpp"
#include <vector>
#include "math3d.hpp"
#include <vector>
#include <string>

class Vector3;

class Framebuffer{
public:
    int width;
    int height;
    std::vector<Vector3> colors;
    std::vector<float> z_buffer;
    
    Framebuffer(int width, int height);
    ~Framebuffer();

    int getWidth() const{return width;};
    int getHeight() const{return height;};

    void clear(Vector3 color);

    void setPixel(int x, int y, float z, Vector3 color);

    void saveAsPPM(const std::string& file_path) const;

};