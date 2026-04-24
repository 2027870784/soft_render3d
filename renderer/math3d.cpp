#include "math3d.hpp"
#include <cmath>

//Vector3类
Vector3::Vector3() = default;

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::~Vector3() = default;

Vector3 Vector3::operator+(const Vector3& other) const {
    return {x + other.x, y + other.y, z + other.z};
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return {x - other.x, y - other.y, z - other.z};
}

float Vector3::dot(const Vector3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vector3 Vector3::cross(const Vector3& other) const {
    return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
}

float Vector3::norm() const {
    return std::sqrt(x * x + y * y + z * z);
}

Vector3 Vector3::normalize() const {
    float n = norm();
    return {x / n, y / n, z / n};
}



//Vector4类
Vector4::Vector4() = default;

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector4::~Vector4() = default;

Vector4 Vector4::operator+(const Vector4& other) const {
    return {x + other.x, y + other.y, z + other.z, w + other.w};
}

Vector4 Vector4::operator-(const Vector4& other) const {
    return {x - other.x, y - other.y, z - other.z, w - other.w};
}

//Vector4::norm和normalize函数缺少类名前缀
float Vector4::norm() const {
    return std::sqrt(x * x + y * y + z * z + w * w);
}

Vector4 Vector4::normalize() const {
    float n = norm();
    return {x / n, y / n, z / n, w / n};
}

float Vector4::dot(const Vector4& other) const {
    return x * other.x + y * other.y + z * other.z + w * other.w;
}

Vector4 Vector4::cross(const Vector4& other) const {
    return {y * other.z - z * other.y,
            z * other.x - x * other.z,
            x * other.y - y * other.x,
            w * other.z - z * other.w};
}



//Matrix4类
Matrix4::Matrix4() : Matrix4(0.0f) {}

Matrix4::Matrix4(float elem) {//单值初始化矩阵所有元素值
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            m[i][j] = elem;
        }
    }
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03,
                 float m10, float m11, float m12, float m13,
                 float m20, float m21, float m22, float m23,
                 float m30, float m31, float m32, float m33)
    : m{{m00, m01, m02, m03},
        {m10, m11, m12, m13},
        {m20, m21, m22, m23},
        {m30, m31, m32, m33}} {}

Matrix4 Matrix4::identity() {//返回单位矩阵
    return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
                  0.0f, 1.0f, 0.0f, 0.0f,
                  0.0f, 0.0f, 1.0f, 0.0f,
                  0.0f, 0.0f, 0.0f, 1.0f);
}

Matrix4::~Matrix4() = default;

Vector4 Matrix4::operator*(const Vector4& other) const {//矩阵与向量乘法
    return Vector4(
        other.x * m[0][0] + other.y * m[0][1] + other.z * m[0][2] + other.w * m[0][3],
        other.x * m[1][0] + other.y * m[1][1] + other.z * m[1][2] + other.w * m[1][3],
        other.x * m[2][0] + other.y * m[2][1] + other.z * m[2][2] + other.w * m[2][3],
        other.x * m[3][0] + other.y * m[3][1] + other.z * m[3][2] + other.w * m[3][3]);
}
