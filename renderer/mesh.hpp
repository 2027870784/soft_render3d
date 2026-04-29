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

    static Mesh createPyramid(float base_size = 1.0f, float height = 1.2f){
        const float h = base_size / 2.0f;
        const float base_y = -height / 2.0f;
        const float apex_y = height / 2.0f;

        Mesh pyramid;
        pyramid.vertices = {
            Vector4(-h, base_y, -h, 1),
            Vector4(h,  base_y, -h, 1),
            Vector4(h,  base_y,  h, 1),
            Vector4(-h, base_y,  h, 1),
            Vector4(0,  apex_y,  0, 1),
        };

        pyramid.normals = {
            Vector3(0, -1, 0),
            Vector3(0, h, -height / 2.0f).normalize(),
            Vector3(height / 2.0f, h, 0).normalize(),
            Vector3(0, h, height / 2.0f).normalize(),
            Vector3(-height / 2.0f, h, 0).normalize(),
        };

        pyramid.colors = {
            Vector3(255, 220, 80)
        };

        pyramid.triangles = {
            Triangle(pyramid.vertices[0], pyramid.vertices[2], pyramid.vertices[1], pyramid.colors[0], pyramid.normals[0]),
            Triangle(pyramid.vertices[0], pyramid.vertices[3], pyramid.vertices[2], pyramid.colors[0], pyramid.normals[0]),
            Triangle(pyramid.vertices[0], pyramid.vertices[1], pyramid.vertices[4], pyramid.colors[0], pyramid.normals[1]),
            Triangle(pyramid.vertices[1], pyramid.vertices[2], pyramid.vertices[4], pyramid.colors[0], pyramid.normals[2]),
            Triangle(pyramid.vertices[2], pyramid.vertices[3], pyramid.vertices[4], pyramid.colors[0], pyramid.normals[3]),
            Triangle(pyramid.vertices[3], pyramid.vertices[0], pyramid.vertices[4], pyramid.colors[0], pyramid.normals[4]),
        };

        return pyramid;
    }

    static Mesh createOctahedron(float size = 1.0f){
        const float h = size / 2.0f;

        Mesh octahedron;
        octahedron.vertices = {
            Vector4(0,  h, 0, 1),
            Vector4(h,  0, 0, 1),
            Vector4(0,  0, h, 1),
            Vector4(-h, 0, 0, 1),
            Vector4(0,  0,-h, 1),
            Vector4(0, -h, 0, 1),
        };

        octahedron.normals = {
            Vector3(1, 1, 1).normalize(),
            Vector3(-1, 1, 1).normalize(),
            Vector3(-1, 1, -1).normalize(),
            Vector3(1, 1, -1).normalize(),
            Vector3(1, -1, 1).normalize(),
            Vector3(-1, -1, 1).normalize(),
            Vector3(-1, -1, -1).normalize(),
            Vector3(1, -1, -1).normalize(),
        };

        octahedron.colors = {
            Vector3(80, 180, 255)
        };

        octahedron.triangles = {
            Triangle(octahedron.vertices[0], octahedron.vertices[1], octahedron.vertices[2], octahedron.colors[0], octahedron.normals[0]),
            Triangle(octahedron.vertices[0], octahedron.vertices[2], octahedron.vertices[3], octahedron.colors[0], octahedron.normals[1]),
            Triangle(octahedron.vertices[0], octahedron.vertices[3], octahedron.vertices[4], octahedron.colors[0], octahedron.normals[2]),
            Triangle(octahedron.vertices[0], octahedron.vertices[4], octahedron.vertices[1], octahedron.colors[0], octahedron.normals[3]),
            Triangle(octahedron.vertices[5], octahedron.vertices[2], octahedron.vertices[1], octahedron.colors[0], octahedron.normals[4]),
            Triangle(octahedron.vertices[5], octahedron.vertices[3], octahedron.vertices[2], octahedron.colors[0], octahedron.normals[5]),
            Triangle(octahedron.vertices[5], octahedron.vertices[4], octahedron.vertices[3], octahedron.colors[0], octahedron.normals[6]),
            Triangle(octahedron.vertices[5], octahedron.vertices[1], octahedron.vertices[4], octahedron.colors[0], octahedron.normals[7]),
        };

        return octahedron;
    }
};

