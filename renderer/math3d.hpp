#pragma once

class Vector3 {
private:
    float xx, yy, zz;

public:
    Vector3():xx(0.0f), yy(0.0f), zz(0.0f) {}
    Vector3(float x, float y, float z);
    ~Vector3();

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;
    Vector3& operator=(const Vector3& other);
    float dot(const Vector3& other) const;
    Vector3 cross(const Vector3& other) const;
    float norm() const;
    Vector3 normalize() const;

    float x() const {return xx;}
    float y() const {return yy;}
    float z() const {return zz;}

    float r() const {return xx;}
    float g() const {return yy;}
    float b() const {return zz;}
};

class Vector4 {
private:
    float xx, yy, zz, ww;

public:
    Vector4():xx(0.0f), yy(0.0f), zz(0.0f), ww(0.0f) {}
    Vector4(float x, float y, float z, float w);
    ~Vector4();

    Vector4 operator+(const Vector4& other) const;
    Vector4 operator-(const Vector4& other) const;
    float normXYZ() const;
    Vector4 normalizeXYZ() const;
    Vector4 w_division() const;
    float dotXYZ(const Vector4& other) const;
    Vector4 crossXYZ(const Vector4& other) const;//计算XYZ分量的叉积
    Vector3 toVector3() const;

    float x() const {return xx;}
    float y() const {return yy;}
    float z() const {return zz;}
    float w() const {return ww;}
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
    Matrix4 operator*(const Matrix4& other) const;//矩阵与矩阵乘法
    Matrix4 transpose() const;//返回转置矩阵
};
