#ifndef MATH_HPP
#define MATH_HPP

#include <cmath>

class vec2;
class vec3;
class vec4;
class mat3;
class mat4;

extern const vec2 ZERO2;
extern const vec3 ZERO3;
extern const vec4 ZERO4;
extern const mat3 IDEN3;
extern const mat4 IDEN4;

vec3 cross(vec3 l, vec3 r);
vec3 normalize(vec3 v);
float magnitude(vec3 v);
float buffer(vec3 v);

mat4 modelMatrix(vec3 scale, vec3 rotate, vec3 translate);
mat4 scale4(vec3 v);
mat4 translate4(vec3 v);
mat4 rotate4(vec3 v);
mat4 rotatex(float d);
mat4 rotatey(float d);
mat4 rotatez(float d);

class vec2{
    public:
        float x,y;
        vec2();
        vec2(vec4 v);
        vec2(vec3 v);
        vec2(const float X, const float Y);
        // scalar ops
        vec2 operator*(const float f);
        vec2 operator/(const float f);
        vec2 operator-();
        // vector ops
        vec2 operator+(vec2 v);
        vec2 operator-(vec2 v);
        // scalar assignment ops
        vec2& operator/=(const float f);
        vec2& operator*=(const float f);
        // vector assignment ops
        vec2& operator=(vec2 v);
        vec2& operator=(float f[2]);
        vec2& operator+=(vec2 v);
        vec2& operator-=(vec2 v);
        // dot product
        float operator*(vec2 v);
        // comparison ops
        bool operator==(vec2 v);
        bool operator!=(vec2 v);
        // util
        float magnitude();
        vec2 normal();

};

class vec3{
    public:
        float x,y,z;
        vec3();
        vec3(vec4 v);
        vec3(vec2 v);
        vec3(const float X, const float Y, const float Z);
        // scalar ops
        vec3 operator*(const float f);
        vec3 operator/(const float f);
        vec3 operator-();
        // vector ops
        vec3 operator+(vec3 v);
        vec3 operator-(vec3 v);
        // scalar assignment ops
        vec3& operator/=(const float f);
        vec3& operator*=(const float f);
        // vector assignment ops
        vec3& operator=(vec3 v);
        vec3& operator=(float f[3]);
        vec3& operator+=(vec3 v);
        vec3& operator-=(vec3 v);
        // dot product
        float operator*(vec3 v);
        // cross product
        vec3 operator^(vec3 v);
        // cross product assignment op
        vec3& operator*=(vec3 v);
        // matrix mult
        vec3 operator*(mat3 m);
        vec3& operator*=(mat3 m);
        // comparison ops
        bool operator==(vec3 v);
        bool operator!=(vec3 v);
        // util
        float magnitude();
        vec3 normal();
};

class vec4{
    public:
        float x,y,z,w;
        vec4();
        vec4(vec2 v);
        vec4(vec3 v);
        vec4(const float X, const float Y, const float Z);
        vec4(const float X, const float Y, const float Z, const float W);
        // scalar ops
        vec4 operator*(const float f);
        vec4 operator/(const float f);
        vec4 operator-();
        // vector ops
        vec4 operator+(vec4 v);
        vec4 operator-(vec4 v);
        // scalar assignment ops
        vec4& operator/=(const float f);
        vec4& operator*=(const float f);
        // vector assignment ops
        vec4& operator=(vec4 v);
        vec4& operator=(float f[4]);
        vec4& operator+=(vec4 v);
        vec4& operator-=(vec4 v);
        // dot product
        float operator*(vec4 v);
        // matrix mult
        vec4 operator*(mat4 m);
        vec4& operator*=(mat4 m);
        // comparison ops
        bool operator==(vec4 v);
        bool operator!=(vec4 v);
        // util
        float magnitude();
        vec4 normal();
};

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