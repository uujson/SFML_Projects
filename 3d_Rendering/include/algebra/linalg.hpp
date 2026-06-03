#pragma once

#ifndef VECTOR_MATRIX_HPP
#define VECTOR_MATRIX_HPP

#include <cmath>

class vec2;
class vec3;
class vec4;
class mat3;
class mat4;

double magnitude(vec3 v);
vec3 normalize(vec3 v);
vec3 cross(vec3 l, vec3 r);

class vec2{
    public:
        double x,y;
        vec2();
        vec2(const double &X, const double &Y);
        vec2 operator/(const double &o);
};

class vec3{
    public:
        double x,y,z;
        double xyz[3] = {x,y,z};
        vec3();
        vec3(const double &X, const double &Y, const double &Z);
        // scalar operators
        vec3 operator*(const double &o);
        vec3 operator/(const double &o);
        vec3 operator-();
        // vector operators
        vec3 operator+(const vec3 &o);
        vec3 operator-(const vec3 &o);
        // scalar assignment operators
        vec3& operator/=(const double &o);
        vec3& operator*=(const double &o);
        // vector assignment operators
        vec3& operator=(const vec3 &o);
        vec3& operator+=(const vec3 &o);
        vec3& operator-=(const vec3 &o);
        // dot product
        double operator*(const vec3 &o);
        // cross product
        vec3 operator()(const vec3 &o);
        // index operator
        double operator[](const int n);
        // matrix multiplication
        vec3 operator*(mat3 o);
        vec3& operator*=(mat3 o);
        // boolean comparison
        bool operator==(const vec3 &o);
        bool operator!=(const vec3 &o);
        double magnitude();
        vec3 normalized();
};

class vec4{
    public:
        double x,y,z,w;
        double xyzw[4] = {x,y,z,w};
        vec4();
        vec4(const double &X,const double &Y,const double &Z,const double &W);
        vec4(vec3 v);
        vec4(vec3 v, const double &W);
        // scalar operators
        vec4 operator*(const double &o);
        vec4 operator/(const double &o);
        vec4 operator-();
        // vector operators
        vec4 operator+(const vec4 &o);
        vec4 operator-(const vec4 &o);
        // scalar assignment operators
        vec4& operator/=(const double &o);
        vec4& operator*=(const double &o);
        // vector assignment operators
        vec4& operator=(const vec4 &o);
        vec4& operator+=(const vec4 &o);
        vec4& operator-=(const vec4 &o);
        // dot product
        double operator*(const vec4 &o);
        // index operator
        double operator[](const int n);
        // matrix multiplication
        vec4 operator*(mat4 o);
        vec4& operator*=(mat4 o);
        // boolean comparison
        bool operator==(const vec4 &o);
        bool operator!=(const vec4 &o);
        double magnitude();
        vec4 normalized();
};

class mat3{
    public:
        double m00, m01, m02,
               m10, m11, m12,
               m20, m21, m22;
        double m[3][3] = {
            {m00, m01, m02},
            {m10, m11, m12},
            {m20, m21, m22}
        };
        vec3 mv[3] = {
            vec3(m00, m01, m02),
            vec3(m10, m11, m12),
            vec3(m20, m21, m22),
        };
        mat3();
        mat3(const double &n);
        mat3(const vec3 r0, const vec3 r1, const vec3 r2);
        vec3 operator*(vec3 v);
        mat3 operator*(mat3 o);
        vec3 row(const int &n);
        vec3 col(const int &n);
        mat3& operator*=(mat3 o);
        mat3& operator=(const mat3 &o);
        vec3 operator[](const int n);
};

class mat4{
    public:
        double
          m00, m01, m02, m03,
          m10, m11, m12, m13,
          m20, m21, m22, m23,
          m30, m31, m32, m33;
        double m[4][4] = {
            {m00, m01, m02, m03},
            {m10, m11, m12, m23},
            {m20, m21, m22, m33},
            {m30, m31, m32, m33}
        };
        vec4 mv[4] = {
            vec4(m00, m01, m02, m03),
            vec4(m10, m11, m12, m13),
            vec4(m20, m21, m22, m23),
            vec4(m30, m31, m32, m33)
        };
        mat4();
        mat4(const double &n);
        mat4(const vec4 r0, const vec4 r1, const vec4 r2, const vec4 r3);
        vec4 operator*(vec4 v);
        mat4 operator*(mat4 o);
        vec4 row(const int &n);
        vec4 col(const int &n);
        mat4& operator*=(mat4 o);
        mat4& operator=(const mat4 &o);
        vec4 operator[](const int n);
};

#endif