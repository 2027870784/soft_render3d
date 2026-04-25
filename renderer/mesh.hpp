#pragma once
#include "Triangle.hpp"
#include <vector>
#include <array>

struct Mesh
{
    /* data */
    std::vector<Vector4> vertices;
    std::vector<Triangle> triangles;
    std::vector<Vector3> normals;
    std::vector<Vector3> colors;
    
    static Mesh createCube(float size = 1.0f){
        float h = size/2.0f;

        Mesh cube;
        cube.vertices = {
            Vector4(-h, -h, -h, 1),
            Vector4(h, -h, -h, 1),
            Vector4(-h, h, -h, 1),
            Vector4(h, h, -h, 1),
            Vector4(-h, -h, h, 1),
            Vector4(h, -h, h, 1),
            Vector4(-h, h, h, 1),
            Vector4(h, h, h, 1),
        };

        cube.normals = {
            Vector3(0,0,1),
            Vector3(0,0,-1),
            Vector3(1,0,0),
            Vector3(-1,0,0),
            Vector3(0,1,0),
            Vector3(0,-1,0),
        };

        cube.colors = {
            Vector3(255,0,0)
        };

        cube.triangles = {
            // z = -h (背面), normal (0, 0, -1)
            Triangle(cube.vertices[0], cube.vertices[3], cube.vertices[1], cube.colors[0], cube.normals[1]),
            Triangle(cube.vertices[0], cube.vertices[2], cube.vertices[3], cube.colors[0], cube.normals[1]),

            // z = +h (正面), normal (0, 0, 1)
            Triangle(cube.vertices[4], cube.vertices[5], cube.vertices[7], cube.colors[0], cube.normals[0]),
            Triangle(cube.vertices[4], cube.vertices[7], cube.vertices[6], cube.colors[0], cube.normals[0]),

            // x = -h (左面), normal (-1, 0, 0)
            Triangle(cube.vertices[0], cube.vertices[4], cube.vertices[6], cube.colors[0], cube.normals[3]),
            Triangle(cube.vertices[0], cube.vertices[6], cube.vertices[2], cube.colors[0], cube.normals[3]),

            // x = +h (右面), normal (1, 0, 0)
            Triangle(cube.vertices[1], cube.vertices[3], cube.vertices[7], cube.colors[0], cube.normals[2]),
            Triangle(cube.vertices[1], cube.vertices[7], cube.vertices[5], cube.colors[0], cube.normals[2]),

            // y = -h (下面), normal (0, -1, 0)
            Triangle(cube.vertices[0], cube.vertices[1], cube.vertices[5], cube.colors[0], cube.normals[5]),
            Triangle(cube.vertices[0], cube.vertices[5], cube.vertices[4], cube.colors[0], cube.normals[5]),

            // y = +h (上面), normal (0, 1, 0)
            Triangle(cube.vertices[2], cube.vertices[6], cube.vertices[7], cube.colors[0], cube.normals[4]),
            Triangle(cube.vertices[2], cube.vertices[7], cube.vertices[3], cube.colors[0], cube.normals[4]),
        };

        return cube;
    }
};

