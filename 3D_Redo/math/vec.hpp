#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cmath>
#include "mat.hpp"

class vec2;
class vec3;
class vec4;

extern const vec2 ZERO2;
extern const vec3 ZERO3;
extern const vec4 ZERO4;

vec3 cross(vec3 l, vec3 r);
vec3 normalize(vec3 v);
float magnitude(vec3 v);
float buffer(vec3 v);

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

#endif