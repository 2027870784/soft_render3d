#include "math3d.hpp"
#include <cmath>

//Vector3类

Vector3::Vector3(float x, float y, float z) : xx(x), yy(y), zz(z) {}

Vector3::~Vector3() = default;

Vector3 Vector3::operator+(const Vector3& other) const {
    return {xx + other.x(), yy + other.y(), zz + other.z()};
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return {xx - other.x(), yy - other.y(), zz - other.z()};
}

Vector3 Vector3::operator*(float scalar) const {
    return {xx * scalar, yy * scalar, zz * scalar};
}

Vector3& Vector3::operator=(const Vector3& other){
    if(this == &other) return *this;
    xx = other.x();
    yy = other.y();
    zz = other.z();
    return *this;
}


float Vector3::dot(const Vector3& other) const {
    return xx * other.x() + yy * other.y() + zz * other.z();
}

Vector3 Vector3::cross(const Vector3& other) const {
    return {yy * other.z() - zz * other.y(),
            zz * other.x() - xx * other.z(),
            xx * other.y() - yy * other.x()};
}

float Vector3::norm() const {
    return std::sqrt(xx * xx + yy * yy + zz * zz);
}

Vector3 Vector3::normalize() const {
    float n = norm();
    if(n < 1e-6f) return {0.0f, 0.0f, 0.0f};
    return {xx / n, yy / n, zz / n};
}



//Vector4类

Vector4::Vector4(float xx, float yy, float zz, float ww) : xx(xx), yy(yy), zz(zz), ww(ww) {}

Vector4::~Vector4() = default;

Vector4 Vector4::operator+(const Vector4& other) const {
    return {xx + other.x(), yy + other.y(), zz + other.z(), ww + other.w()};
}

Vector4 Vector4::operator-(const Vector4& other) const {
    return {xx - other.x(), yy - other.y(), zz - other.z(), ww - other.w()};
}


float Vector4::normXYZ() const {
    return std::sqrt(xx * xx + yy * yy + zz * zz);
}

Vector4 Vector4::normalizeXYZ() const {
    float n = normXYZ();
    if(n < 1e-6f) return {0.0f, 0.0f, 0.0f, ww};
    return {xx / n, yy / n, zz / n, ww};
}

Vector3 Vector4::toVector3() const {
    return {xx, yy, zz};
}

Vector4 Vector4::w_division() const {
    if(std::abs(ww) < 1e-6f) return {0.0f, 0.0f, 0.0f, 1.0f};
    return {xx / ww, yy / ww, zz / ww, 1.0f};
}

float Vector4::dotXYZ(const Vector4& other) const {
    return xx * other.x() + yy * other.y() + zz * other.z();
}

Vector4 Vector4::crossXYZ(const Vector4& other) const {
    return {yy * other.z() - zz * other.y(),
            zz * other.x() - xx * other.z(),
            xx * other.y() - yy * other.x(),
            0.0f};
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
        other.x() * m[0][0] + other.y() * m[0][1] + other.z() * m[0][2] + other.w() * m[0][3],
        other.x() * m[1][0] + other.y() * m[1][1] + other.z() * m[1][2] + other.w() * m[1][3],
        other.x() * m[2][0] + other.y() * m[2][1] + other.z() * m[2][2] + other.w() * m[2][3],
        other.x() * m[3][0] + other.y() * m[3][1] + other.z() * m[3][2] + other.w() * m[3][3]);
}

Matrix4 Matrix4::operator*(const Matrix4& other) const {//矩阵与矩阵乘法
    Matrix4 result(0.0f);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                result.m[i][j] += m[i][k] * other.m[k][j];
            }
        }
    }
    return result;
}

Matrix4 Matrix4::transpose() const {//返回转置矩阵
    Matrix4 result(0.0f);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.m[i][j] = m[j][i];
        }
    }
    return result;
}
