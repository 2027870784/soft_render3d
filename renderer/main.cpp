#include "pipline.hpp"
#include "mesh.hpp"
#include "rasterizer.hpp"


int main(){
    Pipline pipline(800, 600);
    Mesh cube = Mesh::createCube();
    Matrix4 model_matrix = Matrix4::identity();
    pipline.render(cube, model_matrix, Vector3(0,0,0), Vector3(0,0,1));
    return 0;
}