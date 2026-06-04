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

extern const double DEG2RADS;

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
        double m[3][3];
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
        double m[4][4];
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

mat4 modelMatrix(vec3 scale, vec3 rotate, vec3 translate);
mat4 translate4(vec3 xyz);
mat4 scale4(vec3 xyz);
mat4 rotate4(vec3 xyz);
mat4 rotatex(double d);
mat4 rotatey(double d);
mat4 rotatez(double d);

#endif