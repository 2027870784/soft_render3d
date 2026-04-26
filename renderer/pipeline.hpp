#pragma once
#include "math3d.hpp"
#include "framebuffer.hpp"
#include "mesh.hpp"
#include <cmath>

#define MY_PI 3.14159265

class Pipeline{
    public:
        Pipeline(int width = 800, int height = 600);
        ~Pipeline();

        void render(const Mesh& mesh,
                    const Matrix4& model_matrix,
                    const Vector3& eye_pos,
                    const Vector3& light_dir);
        const Framebuffer& getFramebuffer() const { return framebuffer; }
    private:
        Framebuffer framebuffer;
        Vector3 light_dir;
};
