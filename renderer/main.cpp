#include "pipeline.hpp"
#include "mesh.hpp"
#include "rasterizer.hpp"
#include <cmath>

int main(){
    Pipeline pipeline(800, 600);
    Mesh cube = Mesh::createCube();
        constexpr float deg_to_rad = 3.14159265f / 180.0f;
    float angle_y = 35.0f * deg_to_rad;
    float angle_x = -20.0f * deg_to_rad;

    Matrix4 rotation_y(
        std::cos(angle_y), 0.0f, std::sin(angle_y), 0.0f,
        0.0f,              1.0f, 0.0f,              0.0f,
        -std::sin(angle_y),0.0f, std::cos(angle_y), 0.0f,
        0.0f,              0.0f, 0.0f,              1.0f
    );

    Matrix4 rotation_x(
        1.0f, 0.0f,               0.0f,              0.0f,
        0.0f, std::cos(angle_x), -std::sin(angle_x), 0.0f,
        0.0f, std::sin(angle_x),  std::cos(angle_x), 0.0f,
        0.0f, 0.0f,               0.0f,              1.0f
    );

    Matrix4 model_matrix = rotation_y * rotation_x;
    pipeline.render(cube, model_matrix, Vector3(0,0,3), Vector3(0,0,1));
    return 0;
}