#include "pipeline.hpp"
#include "mesh.hpp"
#include "rasterizer.hpp"


int main(){
    Pipeline pipeline(800, 600);
    Mesh cube = Mesh::createCube();
    Matrix4 model_matrix = Matrix4::identity();
    pipeline.render(cube, model_matrix, Vector3(0,0,3), Vector3(0,0,1));
    return 0;
}