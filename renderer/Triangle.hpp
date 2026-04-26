#pragma once
#include "math3d.hpp"
#include <array>

class Triangle {
public:
    Vector4 vex[3];//三角形初始顶点坐标
    Vector3 color[3];//三角形顶点颜色
    Vector3 normal;//三角形法线向量（针对整个三角形面）
    //使用顶点着色时，要将顶点相邻的所有三角形面的法线向量进行平均处理作为该顶点的法线向量
    //此处法线定义不适用于片元着色，使用片元着色时，需要给每个顶点定义法线向量

    Triangle();
    Triangle(const std::array<Vector4,3>& vexs, const std::array<Vector3,3>& colors, const Vector3& n);
    Triangle(const Vector4& a, const Vector4& b, const Vector4& c, const Vector3& color, const Vector3& n);
    ~Triangle();

    //返回三角形顶点坐标
    Vector4 a() const {return vex[0];}
    Vector4 b() const {return vex[1];}
    Vector4 c() const {return vex[2];}

    //返回三角形法线向量
    Vector3 getNormal() const {return normal;}

    void setVex(int index, const Vector4& vex);
    void setColor(int index, const Vector3& col);
    void setColor(int index, float r, float g, float b);
    void setNormal(const Vector3& n);

    void setVexs(const std::array<Vector4,3>& vexs);
    void setColors(const std::array<Vector3,3>& colors);

    std::vector<Vector3> getColors() const;

};
