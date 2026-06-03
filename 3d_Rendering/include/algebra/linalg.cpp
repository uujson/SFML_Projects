#include "linalg.hpp"


double magnitude(vec3 v){ return v.magnitude(); }

vec3 normalize(vec3 v){ return v.normalized(); }

vec3 cross(vec3 l, vec3 r){ return l(r); }


vec2::vec2() : vec2(0,0){}
vec2::vec2(const double &X, const double &Y) : x(X), y(Y){}
vec2 vec2::operator/(const double &o){ return vec2(x/o,y/o); }


vec3::vec3() : vec3(0,0,0){}
vec3::vec3(const double &X, const double &Y, const double &Z) : x(X), y(Y), z(Z){}
// scalar operators
vec3 vec3::operator*(const double &o){ return vec3(x * o, y * o, z * o); }
vec3 vec3::operator/(const double &o){ return vec3(x / o, y / o, z / o); }
vec3 vec3::operator-(){ return vec3(-x,-y,-z); }
// vector operators
vec3 vec3::operator+(const vec3 &o){ return vec3(x + o.x, y + o.y, z + o.z); }
vec3 vec3::operator-(const vec3 &o){ return vec3(x - o.x, y - o.y, z - o.z); }
// scalar assignment operators
vec3& vec3::operator/=(const double &o){ x /= o; y /= o; z /= o; return *this; }
vec3& vec3::operator*=(const double &o){ x *= o; y *= o; z *= o; return *this; }
// vector assignment operators
vec3& vec3::operator=(const vec3 &o){ x = o.x; y = o.y; z = o.z; return *this; }
vec3& vec3::operator+=(const vec3 &o){ x += o.x; y += o.y; z += o.z; return *this; }
vec3& vec3::operator-=(const vec3 &o){ x -= o.x; y -=o.y; z -=o.z; return *this; }
// dot product
double vec3::operator*(const vec3 &o){ return (x*o.x + y*o.y + z*o.z); }
// cross product
vec3 vec3::operator()(const vec3 &o){ return vec3((y*o.z)-(z*o.y),(z*o.x)-(x*o.z),(x*o.y)-(y*o.x)); }
// index operator
double vec3::operator[](const int n){ return xyz[n]; }
// matrix multiplication
vec3 vec3::operator*(mat3 o){ return vec3(vec3(x,y,z)*o[0], vec3(x,y,z)*o[1], vec3(x,y,z)*o[2]); }
vec3 &vec3::operator*=(mat3 o){
    double X,Y,Z;
    X = vec3(x,y,z)*o[0];
    Y = vec3(x,y,z)*o[1];
    Z = vec3(x,y,z)*o[2];
    x = X; y = Y; z = Z;
    return *this;
}
// boolean comparison
bool vec3::operator==(const vec3 &o){ return ((x == o.x) & (y == o.y) & (z == o.z)); }
bool vec3::operator!=(const vec3 &o){ return ((x != o.x) || (y != o.y) || (z != o.z)); }
double vec3::magnitude(){ return sqrt(x*x + y*y + z*z); }
vec3 vec3::normalized(){ return vec3(x,y,z)/magnitude(); }


vec4::vec4() : vec4(0,0,0,1){}
vec4::vec4(const double &X,const double &Y,const double &Z,const double &W) : x(X), y(Y), z(Z), w(W){}
vec4::vec4(vec3 v) : vec4(v.x,v.y,v.z,1.0){}
vec4::vec4(vec3 v, const double &W) : vec4(v.x,v.y,v.z,W){}
// scalar operators
vec4 vec4::operator*(const double &o){ return vec4(x * o, y * o, z * o, w * o); }
vec4 vec4::operator/(const double &o){ return vec4(x / o, y / o, z / o, w / o); }
vec4 vec4::operator-(){ return vec4(-x,-y,-z,-w); }
// vector operators
vec4 vec4::operator+(const vec4 &o){ return vec4(x + o.x, y + o.y, z + o.z, w + o.w); }
vec4 vec4::operator-(const vec4 &o){ return vec4(x - o.x, y - o.y, z - o.z, w + o.w); }
// scalar assignment operators
vec4& vec4::operator/=(const double &o){ x /= o; y /= o; z /= o; w /= o; return *this; }
vec4& vec4::operator*=(const double &o){ x *= o; y *= o; z *= o; w *= o; return *this; }
// vector assignment operators
vec4& vec4::operator=(const vec4 &o){ x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
vec4& vec4::operator+=(const vec4 &o){ x += o.x; y += o.y; z += o.z; w += o.w; return *this; }
vec4& vec4::operator-=(const vec4 &o){ x -= o.x; y -=o.y; z -=o.z; w -= o.w; return *this; }
// dot product
double vec4::operator*(const vec4 &o){ return (x*o.x + y*o.y + z*o.z + w*o.w); }
// index operator
double vec4::operator[](const int n){ return xyzw[n]; }
// matrix multiplication
vec4 vec4::operator*(mat4 o){ return vec4(vec4(x,y,z,w)*o[0], vec4(x,y,z,w)*o[1], vec4(x,y,z,w)*o[2], vec4(x,y,z,w)*o[3]); }
vec4& vec4::operator*=(mat4 o){
    double X,Y,Z,W;
    X = vec4(x,y,z,w)*o[0];
    Y = vec4(x,y,z,w)*o[1];
    Z = vec4(x,y,z,w)*o[2];
    W = vec4(x,y,z,w)*o[3];
    x = X; y = Y; z = Z, w = W;
    return *this;
}
// boolean comparison
bool vec4::operator==(const vec4 &o){ return ((x == o.x) & (y == o.y) & (z == o.z) & (w == o.w)); }
bool vec4::operator!=(const vec4 &o){ return ((x != o.x) || (y != o.y) || (z != o.z) || (w != o.w)); }
double vec4::magnitude(){ return sqrt(x*x + y*y + z*z + w*w); }
vec4 vec4::normalized(){ return vec4(x,y,z,w)/magnitude(); }



mat3::mat3() : mat3(1.0){}
mat3::mat3(const double &n){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            m[i][j] = 0;
        }
    }
    m[0][0] = n;
    m[1][1] = n;
    m[2][2] = n;
}
mat3::mat3(const vec3 r0, const vec3 r1, const vec3 r2){
    m00 = r0.x; m01 = r0.y; m02 = r0.z;
    m10 = r1.x; m11 = r1.y; m12 = r1.z;
    m20 = r2.x; m21 = r2.y; m22 = r2.z;
}
vec3 mat3::operator*(vec3 v){ return vec3(v*mv[0], v*mv[1], v*mv[2]); }
mat3 mat3::operator*(mat3 o){
    vec3 o0,o1,o2,m0,m1,m2;
    o0 = o.col(0);
    o1 = o.col(1);
    o2 = o.col(2);
    m0 = mv[0];
    m1 = mv[1];
    m2 = mv[2];
    return mat3(
        vec3(m0*o0, m0*o1, m0*o2),
        vec3(m1*o0, m1*o1, m1*o2),
        vec3(m2*o0, m2*o1, m2*o2)
    );
}
vec3 mat3::row(const int &n){ return mv[n]; }
vec3 mat3::col(const int &n){ return vec3(m[n][0], m[n][1], m[n][2]); }
mat3& mat3::operator*=(mat3 o){
    vec3 o0,o1,o2,m0,m1,m2;
    o0 = o.col(0);
    o1 = o.col(1);
    o2 = o.col(2);
    m0 = mv[0];
    m1 = mv[1];
    m2 = mv[2];
    m00 = m0*o0; m01 = m0*o1; m02 = m0*o2;
    m10 = m1*o0; m11 = m1*o1; m12 = m1*o2;
    m20 = m2*o0; m21 = m2*o1; m22 = m2*o2;
    return *this;
}
mat3& mat3::operator=(const mat3 &o){
    m00 = o.m00; m01 = o.m01; m02 = o.m02;
    m10 = o.m10; m11 = o.m11; m12 = o.m12;
    m20 = o.m20; m21 = o.m21; m22 = o.m22;
    return *this;
}
vec3 mat3::operator[](const int n){ return mv[n]; }


mat4::mat4() : mat4(1.0){}
mat4::mat4(const double &n){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            m[i][j] = 0;
        }
    }
    m[0][0] = n;
    m[1][1] = n;
    m[2][2] = n;
    m[3][3] = n;
}
mat4::mat4(const vec4 r0, const vec4 r1, const vec4 r2, const vec4 r3){
    m00 = r0.x; m01 = r0.y; m02 = r0.z; m03 = r0.w;
    m10 = r1.x; m11 = r1.y; m12 = r1.z; m13 = r1.w;
    m20 = r2.x; m21 = r2.y; m22 = r2.z; m23 = r2.w;
    m20 = r2.x; m21 = r2.y; m32 = r3.z; m33 = r3.w;
}
vec4 mat4::operator*(vec4 v){ return vec4(v*mv[0], v*mv[1], v*mv[2], v*mv[3]); }
mat4 mat4::operator*(mat4 o){
    vec4 o0,o1,o2,o3,m0,m1,m2,m3;
    o0 = o.col(0);
    o1 = o.col(1);
    o2 = o.col(2);
    o3 = o.col(3);
    m0 = mv[0];
    m1 = mv[1];
    m2 = mv[2];
    m3 = mv[3];
    return mat4(
        vec4(m0*o0, m0*o1, m0*o2, m0*o3),
        vec4(m1*o0, m1*o1, m1*o2, m1*o3),
        vec4(m2*o0, m2*o1, m2*o2, m2*o3),
        vec4(m3*o0, m3*o1, m3*o2, m3*o3)
    );
}
vec4 mat4::row(const int &n){ return mv[n]; }
vec4 mat4::col(const int &n){ return vec4(m[n][0], m[n][1], m[n][2], m[n][3]); }
mat4& mat4::operator*=(mat4 o){
    vec4 o0,o1,o2,o3,m0,m1,m2,m3;
    o0 = o.col(0);
    o1 = o.col(1);
    o2 = o.col(2);
    o3 = o.col(3);
    m0 = mv[0];
    m1 = mv[1];
    m2 = mv[2];
    m3 = mv[3];
    m00 = m0*o0; m01 = m0*o1; m02 = m0*o2; m03 = m0*o3;
    m10 = m1*o0; m11 = m1*o1; m12 = m1*o2; m13 = m1*o3;
    m20 = m2*o0; m21 = m2*o1; m22 = m2*o2; m23 = m2*o3;
    m30 = m3*o0; m21 = m3*o1; m22 = m3*o2; m33 = m3*o3;
    return *this;
}
mat4& mat4::operator=(const mat4 &o){
    m00 = o.m00; m01 = o.m01; m02 = o.m02; m03 = o.m03;
    m10 = o.m10; m11 = o.m11; m12 = o.m12; m13 = o.m13;
    m20 = o.m20; m21 = o.m21; m22 = o.m22; m23 = o.m23;
    m30 = o.m30; m31 = o.m31; m32 = o.m32; m33 = o.m33;
    return *this;
}
vec4 mat4::operator[](const int n){ return mv[n]; }