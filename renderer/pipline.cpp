#include "pipline.hpp"
#include "rasterizer.hpp"

namespace{
    //获取视图矩阵，只处理相机平移
    Matrix4 get_view_matrix(const Vector3& eye_pos){
        auto view_matrix = Matrix4::identity();
        view_matrix.m[0][3] = -eye_pos.x();
        view_matrix.m[1][3] = -eye_pos.y();
        view_matrix.m[2][3] = -eye_pos.z();
        return view_matrix;
    };

    // Matrix4 get_model_matrix(const Vector3& model_pos){
    //     auto model_matrix = Matrix4::identity();
    //     model_matrix.m[0][3] = model_pos.x();
    //     model_matrix.m[1][3] = model_pos.y();
    //     model_matrix.m[2][3] = model_pos.z();
    //     return model_matrix;
    // };

    Matrix4 get_projection_matrix(float eye_fov, float aspect_ratio, float zNear, float zFar){
        auto projection = Matrix4::identity();
        double fovy = eye_fov*MY_PI/180.0;
        projection.m[0][0] = 1/(aspect_ratio*tan(fovy/2));
        projection.m[1][1] = 1/tan(fovy/2);
        projection.m[2][2] = -(zFar+zNear)/(zFar-zNear);
        projection.m[2][3] = -2*zFar*zNear/(zFar-zNear);
        projection.m[3][2] = -1;
        projection.m[3][3] = 0;
        return projection;
    }
}

Pipline::Pipline(int width, int height)
    : framebuffer(width, height) {
    light_dir = Vector3(0,0,1);
}

Pipline::~Pipline() = default;

void Pipline::render(const Mesh& mesh,
                     const Matrix4& model_matrix,
                     const Vector3& eye_pos,
                     const Vector3& light_direction){
    light_dir = light_direction.normalize();
    float aspect_ratio = framebuffer.getWidth() * 1.0f/framebuffer.getHeight();
    auto projection_matrix = get_projection_matrix(90.0f, aspect_ratio, 0.1f, 100.0f);
    auto view_matrix = get_view_matrix(eye_pos);
    auto MVP = projection_matrix * view_matrix * model_matrix;

    /*all by AI*/
    Rasterizer rasterizer(framebuffer.getWidth(), framebuffer.getHeight());

    framebuffer.clear(Vector3(0.0f, 0.0f, 0.0f));

    for (const auto& triangle : mesh.triangles) {
        Vector4 v0_clip = MVP * triangle.a();
        Vector4 v1_clip = MVP * triangle.b();
        Vector4 v2_clip = MVP * triangle.c();

        Vector4 v0_ndc = v0_clip.w_division();
        Vector4 v1_ndc = v1_clip.w_division();
        Vector4 v2_ndc = v2_clip.w_division();

        float intensity = std::max(0.0f, triangle.getNormal().normalize().dot(light_dir));
        auto colors = triangle.getColors();

        Vector4 sv0(
            (v0_ndc.x() * 0.5f + 0.5f) * (framebuffer.getWidth() - 1),
            (1.0f - (v0_ndc.y() * 0.5f + 0.5f)) * (framebuffer.getHeight() - 1),
            v0_ndc.z() * 0.5f + 0.5f,
            1.0f);
        Vector4 sv1(
            (v1_ndc.x() * 0.5f + 0.5f) * (framebuffer.getWidth() - 1),
            (1.0f - (v1_ndc.y() * 0.5f + 0.5f)) * (framebuffer.getHeight() - 1),
            v1_ndc.z() * 0.5f + 0.5f,
            1.0f);
        Vector4 sv2(
            (v2_ndc.x() * 0.5f + 0.5f) * (framebuffer.getWidth() - 1),
            (1.0f - (v2_ndc.y() * 0.5f + 0.5f)) * (framebuffer.getHeight() - 1),
            v2_ndc.z() * 0.5f + 0.5f,
            1.0f);

        std::array<Vector3, 3> shaded_colors = {
            colors[0] * intensity,
            colors[1] * intensity,
            colors[2] * intensity
        };
        Triangle shaded_triangle({sv0, sv1, sv2}, shaded_colors, triangle.getNormal());
        rasterizer.rasterizeTriangle(shaded_triangle, framebuffer);
        /*by AI end*/
        framebuffer.saveAsPPM("../build/output.ppm");
    }
}
