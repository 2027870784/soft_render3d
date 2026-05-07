#include "pipeline.hpp"
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

Pipeline::Pipeline(int width, int height)
    : framebuffer(width, height) {
    light_dir = Vector3(0,0,1);
}

Pipeline::~Pipeline() = default;

void Pipeline::render(const Mesh& mesh,
                     const Matrix4& model_matrix,
                     const Vector3& eye_pos,
                     const Vector3& light_direction){
    light_dir = light_direction.normalize();
    float aspect_ratio = framebuffer.getWidth() * 1.0f/framebuffer.getHeight();
    auto projection_matrix = get_projection_matrix(90.0f, aspect_ratio, 0.1f, 100.0f);
    auto view_matrix = get_view_matrix(eye_pos);
    auto MVP = projection_matrix * view_matrix * model_matrix;

    // /*all by AI_temp*/
    // Rasterizer rasterizer(framebuffer.getWidth(), framebuffer.getHeight());
    //
    // framebuffer.clear(Vector3(0.0f, 0.0f, 0.0f));
    //
    // for (const auto& triangle : mesh.triangles) {
    //     Vector4 v0_clip = MVP * triangle.a();
    //     Vector4 v1_clip = MVP * triangle.b();
    //     Vector4 v2_clip = MVP * triangle.c();
    //
    //     if(std::abs(v0_clip.w()) <= 1e-6 || std::abs(v1_clip.w()) <= 1e-6 || std::abs(v2_clip.w()) <= 1e-6){
    //         continue;
    //     }
    //     Vector4 v0_ndc = v0_clip.w_division();
    //     Vector4 v1_ndc = v1_clip.w_division();
    //     Vector4 v2_ndc = v2_clip.w_division();
    //
    //     auto normal_world_ = model_matrix * triangle.getNormal().toVector4_w0();
    //     auto normal_world = normal_world_.toVector3().normalize();
    //
    //     float intensity = std::max(0.0f, normal_world.dot(light_dir));
    //     auto colors = triangle.getColors();
    //
    //     Vector4 sv0(
    //         (v0_ndc.x() * 0.5f + 0.5f) * (framebuffer.getWidth() - 1),
    //         (1.0f - (v0_ndc.y() * 0.5f + 0.5f)) * (framebuffer.getHeight() - 1),
    //         v0_ndc.z() * 0.5f + 0.5f,
    //         1.0f);
    //     Vector4 sv1(
    //         (v1_ndc.x() * 0.5f + 0.5f) * (framebuffer.getWidth() - 1),
    //         (1.0f - (v1_ndc.y() * 0.5f + 0.5f)) * (framebuffer.getHeight() - 1),
    //         v1_ndc.z() * 0.5f + 0.5f,
    //         1.0f);
    //     Vector4 sv2(
    //         (v2_ndc.x() * 0.5f + 0.5f) * (framebuffer.getWidth() - 1),
    //         (1.0f - (v2_ndc.y() * 0.5f + 0.5f)) * (framebuffer.getHeight() - 1),
    //         v2_ndc.z() * 0.5f + 0.5f,
    //         1.0f);
    //
    //     std::array<Vector3, 3> shaded_colors = {
    //         colors[0] * intensity,
    //         colors[1] * intensity,
    //         colors[2] * intensity
    //     };
    //     Triangle shaded_triangle({sv0, sv1, sv2}, shaded_colors, triangle.getNormal());
    //     rasterizer.rasterizeTriangle(shaded_triangle, framebuffer);
    //     /*temp end*/
    // }

    //创建光栅器
    Rasterizer rasterizer(framebuffer.getWidth(), framebuffer.getHeight());

    //清空帧缓冲，颜色清为黑色
    framebuffer.clear(Vector3(0.0f, 0.0f, 0.0f));

    for (const auto& triangle : mesh.triangles) {
        //顶点变换
        Vector4 v0_projected = MVP * triangle.a();
        Vector4 v1_projected = MVP * triangle.b();
        Vector4 v2_projected = MVP * triangle.c();

        //透视除法前检查
        if (std::abs(v0_projected.w()) <= 1e-6 ||
            std::abs(v1_projected.w()) <= 1e-6 ||
            std::abs(v2_projected.w()) <= 1e-6) {
            continue;
        }

        //透视除法，把齐次坐标转换到NDC坐标
        Vector4 v0_ndc = v0_projected.w_division();
        Vector4 v1_ndc = v1_projected.w_division();
        Vector4 v2_ndc = v2_projected.w_division();

        //法线变换：法线使用 w = 0，避免模型矩阵中的平移影响方向向量
        //如果出现费等比缩放，需要更高级的处理
        Vector4 normal_projected = model_matrix * triangle.getNormal().toVector4_w0();
        Vector3 normal_world = normal_projected.toVector3().normalize();

        //简单漫反射光照Lambert模型,点积越大代表越朝向光源，小于 0 则说明背光
        float light_intensity = std::max(0.0f, normal_world.dot(light_dir));
        auto vertex_colors = triangle.getColors();

        //屏幕映射view_transform,把 NDC 的 x/y/z 映射到 framebuffer 的像素坐标和深度范围
        Vector4 screen_v0(
            (v0_ndc.x() * 0.5f + 0.5f) * (framebuffer.getWidth() - 1),
            (1.0f - (v0_ndc.y() * 0.5f + 0.5f)) * (framebuffer.getHeight() - 1),
            v0_ndc.z() * 0.5f + 0.5f,
            1.0f);
        Vector4 screen_v1(
            (v1_ndc.x() * 0.5f + 0.5f) * (framebuffer.getWidth() - 1),
            (1.0f - (v1_ndc.y() * 0.5f + 0.5f)) * (framebuffer.getHeight() - 1),
            v1_ndc.z() * 0.5f + 0.5f,
            1.0f);
        Vector4 screen_v2(
            (v2_ndc.x() * 0.5f + 0.5f) * (framebuffer.getWidth() - 1),
            (1.0f - (v2_ndc.y() * 0.5f + 0.5f)) * (framebuffer.getHeight() - 1),
            v2_ndc.z() * 0.5f + 0.5f,
            1.0f);

        //顶点颜色着色,当前使用同一个面法线，所以三个顶点乘以相同的光照强度
        std::array<Vector3, 3> lit_vertex_colors = {
            vertex_colors[0] * light_intensity,
            vertex_colors[1] * light_intensity,
            vertex_colors[2] * light_intensity
        };

        //光栅化：构造屏幕空间三角形，交给 rasterizer 进行像素填充和深度测试
        Triangle screen_triangle({screen_v0, screen_v1, screen_v2}, lit_vertex_colors, triangle.getNormal());
        rasterizer.rasterizeTriangle(screen_triangle, framebuffer);
    }
    framebuffer.saveAsPPM("./output.ppm");
}
