#pragma once

class Vector3 {
public:
    float x, y, z;

    Vector3();
    Vector3(float x, float y, float z);
    ~Vector3();

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    float dot(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
    float norm() const;
    Vector3 normalize() const;
};

class Vector4 {
public:
    float x, y, z, w;

    Vector4();
    Vector4(float x, float y, float z, float w);
    ~Vector4();

    Vector4 operator+(const Vector4& other) const;
    Vector4 operator-(const Vector4& other) const;
    float norm() const;
    Vector4 normalize() const;
    float dot(const Vector4& other) const;
    Vector4 cross(const Vector4& other) const;
};

class Matrix4 {
public:
    float m[4][4];

    Matrix4();
    Matrix4(float elem);//单值初始化矩阵所有元素值
    Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);//初始化矩阵元素值
    static Matrix4 identity();//返回单位矩阵
    ~Matrix4();

    Vector4 operator*(const Vector4& other) const;//矩阵与向量乘法
};
