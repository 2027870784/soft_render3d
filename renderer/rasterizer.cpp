#include "rasterizer.hpp"
#include "Triangle.hpp"
#include "math3d.hpp"
#include <algorithm>
#include <cmath>
#include <tuple>


namespace{//匿名空间，只允许在当前文件中使用
    bool insideTriangle(float x, float y, const Triangle& triangle){
        Vector3 p(x, y, 1);//z=1不影响后续叉积结果的z分量符号
        Vector3 e0 = triangle.a().toVector3() - triangle.b().toVector3();
        Vector3 e1 = triangle.c().toVector3() - triangle.a().toVector3();
        Vector3 e2 = triangle.b().toVector3() - triangle.c().toVector3();
        
        Vector3 p0 = p - triangle.b().toVector3();
        Vector3 p1 = p - triangle.a().toVector3();
        Vector3 p2 = p - triangle.c().toVector3();
        
        Vector3 a = e0.cross(p0);
        Vector3 b = e1.cross(p1);
        Vector3 c = e2.cross(p2);

        
        if((a.z() < 0 && b.z() < 0 && c.z() < 0) || (a.z() >= 0 && b.z() >= 0 && c.z() >= 0)) return true;
        return false;
    }

    //获取重心坐标
    std::tuple<float, float, float> computeBarycentric2D(float x, float y, const std::array<Vector3,3>& v){
    float c1 = (x*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*y + v[1].x()*v[2].y() - v[2].x()*v[1].y()) / (v[0].x()*(v[1].y() - v[2].y()) + (v[2].x() - v[1].x())*v[0].y() + v[1].x()*v[2].y() - v[2].x()*v[1].y());
    float c2 = (x*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*y + v[2].x()*v[0].y() - v[0].x()*v[2].y()) / (v[1].x()*(v[2].y() - v[0].y()) + (v[0].x() - v[2].x())*v[1].y() + v[2].x()*v[0].y() - v[0].x()*v[2].y());
    float c3 = (x*(v[0].y() - v[1].y()) + (v[1].x() - v[0].x())*y + v[0].x()*v[1].y() - v[1].x()*v[0].y()) / (v[2].x()*(v[0].y() - v[1].y()) + (v[1].x() - v[0].x())*v[2].y() + v[0].x()*v[1].y() - v[1].x()*v[0].y());
    return {c1,c2,c3};
}
}

Rasterizer::Rasterizer(int width, int height):width(width), height(height) {}

Rasterizer::~Rasterizer() = default;

void Rasterizer::rasterizeTriangle(const Triangle& triangle, Framebuffer& framebuffer){
    Vector4 a = triangle.a();
    Vector4 b = triangle.b();
    Vector4 c = triangle.c();
    auto colors = triangle.getColors();

    //计算包围盒
    float min_x = std::min(a.x(), std::min(b.x(), c.x()));
    float min_y = std::min(a.y(), std::min(b.y(), c.y()));
    float max_x = std::max(a.x(), std::max(b.x(), c.x()));
    float max_y = std::max(a.y(), std::max(b.y(), c.y()));

    int bbox_min_x = std::max(0, static_cast<int>(std::floor(min_x)));
    int bbox_min_y = std::max(0, static_cast<int>(std::floor(min_y)));
    int bbox_max_x = std::min(width - 1, static_cast<int>(std::ceil(max_x)));
    int bbox_max_y = std::min(height - 1, static_cast<int>(std::ceil(max_y)));

    for(int x = bbox_min_x; x <= bbox_max_x; x++){
        for(int y = bbox_min_y; y <= bbox_max_y; y++){
            if(insideTriangle(x + 0.5, y + 0.5, triangle)){
                auto [alpha, beta, gamma] = computeBarycentric2D(x + 0.5, y + 0.5, {a.toVector3(),b.toVector3(),c.toVector3()});
                //利用重心坐标插值z值
                float w_reciprocal = 1.0/(alpha / a.w() + beta / b.w() + gamma / c.w());
                float z_interpolated = alpha * a.z() / a.w() + beta * b.z() / b.w() + gamma * c.z() / c.w();
                z_interpolated *= w_reciprocal;

                int pixel_index = framebuffer.getIndex(x,y);
                if(z_interpolated < framebuffer.z_buffer[pixel_index]){
                    //利用重心坐标插值颜色
                    Vector3 final_color = colors[0] * alpha + colors[1] * beta + colors[2] * gamma;
                    framebuffer.setPixel(x,y,z_interpolated,final_color);
                }
            }   
        }
    }
}
