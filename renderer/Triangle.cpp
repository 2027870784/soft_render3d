#include "Triangle.hpp"
#include <iostream>

Triangle::Triangle(){
    vex[0] = Vector4(0,0,0,1);
    vex[1] = Vector4(0,0,0,1);
    vex[2] = Vector4(0,0,0,1);

    normal = Vector3(0,0,0);
    
    color[0] = Vector3(0,0,0);
    color[1] = Vector3(0,0,0);
    color[2] = Vector3(0,0,0);
}

Triangle::Triangle(const std::array<Vector4,3>& vexs, const std::array<Vector3,3>& colors, const Vector3& n){
    setVexs(vexs);
    setColors(colors);
    setNormal(n);
}

Triangle::~Triangle() = default;

void Triangle::setVex(int index, const Vector4& vex){
    this->vex[index] = vex;
}

void Triangle::setColor(int index, float r, float g, float b){
    if((r<0.0) || (r>255.) ||
       (g<0.0) || (g>255.) ||
       (b<0.0) || (b>255.)) {
        std::cout << "Error: color value out of range." << std::endl;
        return;
    }
    color[index] = Vector3(r/255.,g/255.,b/255.);
}

void Triangle::setColor(int index, const Vector3& col){
    setColor(index, col.r(), col.g(), col.b());
}

Triangle::Triangle(const Vector4& a, const Vector4& b, const Vector4& c, const Vector3& color, const Vector3& n){
    setVexs({a,b,c});
    setColor(0, color);
    setColor(1, color);
    setColor(2, color);
    setNormal(n);
}

void Triangle::setNormal(const Vector3& n){
    normal = n;
}

void Triangle::setVexs(const std::array<Vector4,3>& vexs){
    vex[0] = vexs[0];
    vex[1] = vexs[1];
    vex[2] = vexs[2];
}

void Triangle::setColors(const std::array<Vector3,3>& colors){
    color[0] = colors[0];
    color[1] = colors[1];
    color[2] = colors[2];
}
