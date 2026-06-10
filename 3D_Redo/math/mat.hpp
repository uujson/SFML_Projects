#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cmath>
#include "vec.hpp"

class mat3;
class mat4;

extern const mat3 IDEN3;
extern const mat4 IDEN4;

mat4 modelMatrix(vec3 scale, vec3 rotate, vec3 translate);
mat4 scale4(vec3 v);
mat4 translate4(vec3 v);
mat4 rotate4(vec3 v);
mat4 rotatex(float d);
mat4 rotatey(float d);
mat4 rotatez(float d);

class mat3{
    public:
        float m[3][3];
        mat3();
        mat3(const float n);
        mat3(float f00, float f01, float f02,
            float f10, float f11, float f12,
            float f20, float f21, float f22
        );
        mat3(vec3 v0, vec3 v1, vec3 v2);
        vec3 operator*(vec3 v);
        mat3 operator*(mat3 M);
        mat3& operator*=(mat3 M);
        mat3& operator=(mat3 M);
        mat3& operator=(float M[9]);
        vec3 row(int n);
        vec3 col(int n);
};

class mat4{
    public:
        float m[4][4];
        mat4();
        mat4(const float n);
        mat4(mat3 M);
        mat4(float f00, float f01, float f02, float f03,
            float f10, float f11, float f12, float f13,
            float f20, float f21, float f22, float f23,
            float f30, float f31, float f32, float f33
        );
        mat4(vec4 v0, vec4 v1, vec4 v2, vec4 v3);
        vec4 operator*(vec4 v);
        mat4 operator*(mat4 M);
        mat4& operator*=(mat4 M);
        mat4& operator=(mat4 M);
        mat4& operator=(float M[16]);
        vec4 row(int n);
        vec4 col(int n);
};

#endif