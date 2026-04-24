#include "math3d.hpp"
#include <cmath>

class Vector3 {
public:
    float x, y, z;

    Vector3() = default;
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
    ~Vector3() = default;

    Vector3 operator+(const Vector3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }

    Vector3 operator-(const Vector3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }

    float dot(const Vector3& other) const {//点积
        return x * other.x + y * other.y + z * other.z;
    }

    Vector3 cross(const Vector3& other) const {//叉积
        return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
    }

    float norm() const {//取模
        return std::sqrt(x * x + y * y + z * z);
    }

    Vector3 normalize() const {//归一化
        float n = norm();
        return {x / n, y / n, z / n};
    }
};

class Vector4 {
public:
    float x, y, z, w;

    Vector4() = default;
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    ~Vector4() = default;

    Vector4 operator+(const Vector4& other) const {
        return {x + other.x, y + other.y, z + other.z, w + other.w};
    }

    Vector4 operator-(const Vector4& other) const {
        return {x - other.x, y - other.y, z - other.z, w - other.w};
    }

    float norm() const {//取模
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    Vector4 normalize() const {//归一化
        float n = norm();
        return {x / n, y / n, z / n, w / n};
    }

    float dot(const Vector4& other) const {//点积
        return x * other.x + y * other.y + z * other.z + w * other.w;
    }

    Vector4 cross(const Vector4& other) const {//叉积
        return {y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x,
                w * other.z - z * other.w};
    }
};

class Matrix4 {
public:
    float m[4][4] = {0};

    Matrix4() = default;
    Matrix4(float elem = 0.0f){//为矩阵所有元素赋相同值
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 4; j++){
                m[i][j] = elem;
            }
        }
    }
    Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33)
        : m{{m00, m01, m02, m03},
            {m10, m11, m12, m13},
            {m20, m21, m22, m23},
            {m30, m31, m32, m33}} {}
    ~Matrix4() = default;
};
