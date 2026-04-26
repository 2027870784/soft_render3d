#pragma once
#include "Triangle.hpp"
#include "framebuffer.hpp"


class Rasterizer{
private:
    int width;
    int height;

public:
    Rasterizer(int width, int height);
    ~Rasterizer();

    void rasterizeTriangle(const Triangle& triangle, Framebuffer& framebuffer);
};
