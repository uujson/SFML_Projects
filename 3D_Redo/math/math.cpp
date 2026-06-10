#include "math.hpp"

const vec2 ZERO2 = vec2(0,0);
const vec3 ZERO3 = vec3(0,0,0);
const vec4 ZERO4 = vec4(0,0,0,1);
const mat3 IDEN3 = mat3(
    1,0,0,
    0,1,0,
    0,0,1
);
const mat4 IDEN4 = mat4{
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
};

const float D2R = M_PI/180.0;

// |------------------------------------------VEC2------------------------------------------|

vec2::vec2() : vec2(0,0){}
vec2::vec2(vec4 v) : vec2(v.x,v.y){}
vec2::vec2(vec3 v) : vec2(v.x,v.y){}
vec2::vec2(const float X, const float Y){ x = X; y = Y; }
// scalar ops
vec2 vec2::operator*(const float f){ return vec2(x*f, y*f); }
vec2 vec2::operator/(const float f){ return vec2(x/f, y/f); }
vec2 vec2::operator-(){ return vec2(-x, -y); }
// vector ops
vec2 vec2::operator+(vec2 v){ return vec2(x+v.x, y+v.y); }
vec2 vec2::operator-(vec2 v){ return vec2(x-v.x, y-v.y); }
// scalar assignment ops
vec2& vec2::operator/=(const float f){
    x /= f;
    y /= f;
    return *this;
}
vec2& vec2::operator*=(const float f){
    x *= f;
    y *= f;
    return *this;
}
// vector assignment ops
vec2& vec2::operator=(vec2 v){
    x = v.x;
    y = v.y;
    return *this;
}
vec2& vec2::operator=(float f[2]){
    x = f[0];
    y = f[1];
    return *this;
}
vec2& vec2::operator+=(vec2 v){
    x += v.x;
    y += v.y;
    return *this;
}
vec2& vec2::operator-=(vec2 v){
    x -= v.x;
    y -= v.y;
    return *this;
}
// dot product
float vec2::operator*(vec2 v){
    return (x*v.x + y*v.y);
}
// comparison ops
bool vec2::operator==(vec2 v){
    return ((x == v.x) && (y == v.y));
}
bool vec2::operator!=(vec2 v){
    return ((x != v.x) || (y != v.y));
}
// util
float vec2::magnitude(){
    return sqrt(x*x + y*y);
}
vec2 vec2::normal(){
    return vec2(x,y)/magnitude();
}

// |------------------------------------------VEC3------------------------------------------|

vec3::vec3() : vec3(0,0,0){}
vec3::vec3(vec4 v) : vec3(v.x,v.y,v.z){}
vec3::vec3(vec2 v) : vec3(v.x,v.y,0){}
vec3::vec3(const float X, const float Y, const float Z){ x = X; y = Y; z = Z; }
// scalar ops
vec3 vec3::operator*(const float f){ return vec3(x*f, y*f, z*f); }
vec3 vec3::operator/(const float f){ return vec3(x/f, y/f, z/f); }
vec3 vec3::operator-(){ return vec3(-x, -y, -z); }
// vector ops
vec3 vec3::operator+(vec3 v){ return vec3(x+v.x, y+v.y, z+v.z); }
vec3 vec3::operator-(vec3 v){ return vec3(x-v.x, y-v.y, z-v.z); }
// scalar assignment ops
vec3& vec3::operator/=(const float f){
    x /= f;
    y /= f;
    z /= f;
    return *this;
}
vec3& vec3::operator*=(const float f){
    x *= f;
    y *= f;
    z *= f;
    return *this;
}
// vector assignment ops
vec3& vec3::operator=(vec3 v){
    x = v.x;
    y = v.y;
    z = v.z;
    return *this;
}
vec3& vec3::operator=(float f[3]){
    x = f[0];
    y = f[1];
    z = f[2];
    return *this;
}
vec3& vec3::operator+=(vec3 v){
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}
vec3& vec3::operator-=(vec3 v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}
// dot product
float vec3::operator*(vec3 v){
    return (x*v.x + y*v.y + z*v.z);
}
// cross product
vec3 vec3::operator^(vec3 v){
    return vec3( ((y*v.z)-(z*v.y)), ((z*v.x)-(x*v.z)), ((x*v.y)-(y*v.x)) );
}
// cross product assignment op
vec3& vec3::operator*=(vec3 v){
    x = ((y*v.z)-(z*v.y));
    y = ((z*v.x)-(x*v.z));
    z = ((x*v.y)-(y*v.x));
    return *this;
}
// matrix mult
vec3 vec3::operator*(mat3 m){
    return vec3(vec3(x,y,z)*m.row(0), vec3(x,y,z)*m.row(1), vec3(x,y,z)*m.row(2));
}
vec3& vec3::operator*=(mat3 m){
    x = vec3(x,y,z)*m.row(0);
    y = vec3(x,y,z)*m.row(1);
    z = vec3(x,y,z)*m.row(2);
    return *this;
}
// comparison ops
bool vec3::operator==(vec3 v){
    return ((x == v.x) & (y == v.y) & (z == v.z));
}
bool vec3::operator!=(vec3 v){
    return ((x != v.x) || (y != v.y) || (z != v.z));
}
// util
float vec3::magnitude(){
    return sqrt(x*x + y*y + z*z);
}
vec3 vec3::normal(){
    return vec3(x,y,z)/magnitude();
}

// |------------------------------------------VEC4------------------------------------------|

vec4::vec4() : vec4(0,0,0,1){}
vec4::vec4(vec3 v) : vec4(v.x,v.y,v.z,1){}
vec4::vec4(vec2 v) : vec4(v.x,v.y,0,1){}
vec4::vec4(const float X, const float Y, const float Z, const float W) : x(X), y(Y), z(Z), w(W){}
// scalar ops
vec4 vec4::operator*(const float f){ return vec4(x*f, y*f, z*f, w*f); }
vec4 vec4::operator/(const float f){ return vec4(x/f, y/f, z/f, w/f); }
vec4 vec4::operator-(){ return vec4(-x, -y, -z, -w); }
// vector ops
vec4 vec4::operator+(vec4 v){ return vec4(x+v.x, y+v.y, z+v.z, w+v.w); }
vec4 vec4::operator-(vec4 v){ return vec4(x-v.x, y-v.y, z-v.z, w-v.w); }
// scalar assignment ops
vec4& vec4::operator/=(const float f){
    x /= f;
    y /= f;
    z /= f;
    w /= f;
    return *this;
}
vec4& vec4::operator*=(const float f){
    x *= f;
    y *= f;
    z *= f;
    w *= f;
    return *this;
}
// vector assignment ops
vec4& vec4::operator=(vec4 v){
    x = v.x;
    y = v.y;
    z = v.z;
    w = v.w;
    return *this;
}
vec4& vec4::operator=(float f[4]){
    x = f[0];
    y = f[1];
    z = f[2];
    w = f[3];
    return *this;
}
vec4& vec4::operator+=(vec4 v){
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;
    return *this;
}
vec4& vec4::operator-=(vec4 v){
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;
    return *this;
}
// dot product
float vec4::operator*(vec4 v){
    return (x*v.x + y*v.y + z*v.z + w*v.w);
}
// matrix mult
vec4 vec4::operator*(mat4 m){
    return vec4(vec4(x,y,z,w)*m.row(0), vec4(x,y,z,w)*m.row(1), vec4(x,y,z,w)*m.row(2), vec4(x,y,z,w)*m.row(3));
}
vec4& vec4::operator*=(mat4 m){
    x = vec4(x,y,z,w)*m.row(0);
    y = vec4(x,y,z,w)*m.row(1);
    z = vec4(x,y,z,w)*m.row(2);
    w = vec4(x,y,z,w)*m.row(3);
    return *this;
}
// comparison ops
bool vec4::operator==(vec4 v){
    return ((x == v.x) & (y == v.y) & (z == v.z) & (w == v.w));
}
bool vec4::operator!=(vec4 v){
    return ((x != v.x) || (y != v.y) || (z != v.z) || (w != v.w));
}
// util
float vec4::magnitude(){
    return sqrt(x*x + y*y + z*z + w*w);
}
vec4 vec4::normal(){
    return vec4(x,y,z,w)/magnitude();
}

// |------------------------------------------MAT3------------------------------------------|

mat3::mat3() : mat3(1.0){}
mat3::mat3(const float n) : mat3(vec3(n,0,0), vec3(0,n,0), vec3(0,0,n)){}
mat3::mat3(float f00, float f01, float f02,
            float f10, float f11, float f12,
            float f20, float f21, float f22
) : mat3(vec3(f00,f01,f02), vec3(f10,f11,f12), vec3(f20,f21,f22)){}
mat3::mat3(vec3 v0, vec3 v1, vec3 v2){
    m[0][0] = v0.x; m[0][1] = v0.y; m[0][2] = v0.z;
    m[1][0] = v1.x; m[1][1] = v1.y; m[1][2] = v1.z;
    m[2][0] = v2.x; m[2][1] = v2.y; m[2][2] = v2.z;
}
vec3 mat3::operator*(vec3 v){
    return vec3(
        v*row(0),
        v*row(1),
        v*row(2)
    );
}
mat3 mat3::operator*(mat3 M){
    vec3 c0 = M.col(0);
    vec3 c1 = M.col(1);
    vec3 c2 = M.col(2);
    vec3 r0 = row(0);
    vec3 r1 = row(1);
    vec3 r2 = row(2);
    return mat3(
        vec3(r0*c0, r0*c1, r0*c2),
        vec3(r1*c0, r1*c1, r1*c2),
        vec3(r2*c0, r2*c1, r2*c2)
    );
}
mat3& mat3::operator*=(mat3 M){
    vec3 c0 = M.col(0);
    vec3 c1 = M.col(1);
    vec3 c2 = M.col(2);
    vec3 r0 = row(0);
    vec3 r1 = row(1);
    vec3 r2 = row(2);
    m[0][0] = r0*c0; m[0][1] = r0*c1; m[0][2] = r0*c2;
    m[1][0] = r1*c0; m[1][1] = r1*c1; m[1][2] = r1*c2;
    m[2][0] = r1*c0; m[2][1] = r2*c1; m[2][2] = r2*c2;
    return *this;
}
mat3& mat3::operator=(mat3 M){
    m[0][0] = M.m[0][0]; m[0][1] = M.m[0][1]; m[0][2] = M.m[0][2];
    m[1][0] = M.m[1][0]; m[1][1] = M.m[1][1]; m[1][2] = M.m[1][2];
    m[2][0] = M.m[2][0]; m[2][1] = M.m[2][1]; m[2][2] = M.m[2][2];
    return *this;
}
mat3& mat3::operator=(float M[9]){
    m[0][0] = M[0]; m[0][1] = M[1]; m[0][2] = M[2];
    m[1][0] = M[3]; m[1][1] = M[4]; m[1][2] = M[5];
    m[2][0] = M[6]; m[2][1] = M[7]; m[2][2] = M[8];
    return *this;
}
vec3 mat3::row(int n){
    return vec3(m[n][0], m[n][1], m[n][2]);
}
vec3 mat3::col(int n){
    return vec3(m[0][n], m[1][n], m[2][n]);
}

// |------------------------------------------MAT4------------------------------------------|

mat4::mat4() : mat4(1.0){}
mat4::mat4(const float n) : mat4(vec4(n,0,0,0), vec4(0,n,0,0), vec4(0,0,n,0), vec4(0,0,0,1)){}
mat4::mat4(float f00, float f01, float f02, float f03,
            float f10, float f11, float f12, float f13,
            float f20, float f21, float f22, float f23,
            float f30, float f31, float f32, float f33
) : mat4(vec4(f00,f01,f02,f03), vec4(f10,f11,f12,f13), vec4(f20,f21,f22,f23), vec4(f30,f31,f32,f33)){}
mat4::mat4(vec4 v0, vec4 v1, vec4 v2, vec4 v3){
    m[0][0] = v0.x; m[0][1] = v0.y; m[0][2] = v0.z; m[0][3] = v0.w;
    m[1][0] = v1.x; m[1][1] = v1.y; m[1][2] = v1.z; m[1][3] = v1.w;
    m[2][0] = v2.x; m[2][1] = v2.y; m[2][2] = v2.z; m[2][3] = v2.w;
    m[3][0] = v3.x; m[3][1] = v3.y; m[3][2] = v3.z; m[3][3] = v3.w;
}
vec4 mat4::operator*(vec4 v){
    return vec4(
        v*row(0),
        v*row(1),
        v*row(2),
        v*row(3)
    );
}
mat4 mat4::operator*(mat4 M){
    vec4 c0,c1,c2,c3,r0,r1,r2,r3;
    c0 = M.col(0);
    c1 = M.col(1);
    c2 = M.col(2);
    c3 = M.col(3);
    r0 = row(0);
    r1 = row(1);
    r2 = row(2);
    r3 = row(3);
    return mat4(
        vec4(r0*c0, r0*c1, r0*c2, r0*c3),
        vec4(r1*c0, r1*c1, r1*c2, r1*c3),
        vec4(r2*c0, r2*c1, r2*c2, r2*c3),
        vec4(r3*c0, r3*c1, r3*c2, r3*c3)
    );
}
mat4& mat4::operator*=(mat4 M){vec4 c0,c1,c2,c3,r0,r1,r2,r3;
    c0 = M.col(0);
    c1 = M.col(1);
    c2 = M.col(2);
    c3 = M.col(3);
    r0 = row(0);
    r1 = row(1);
    r2 = row(2);
    r3 = row(3);
    m[0][0] = r0*c0; m[0][1] = r0*c1; m[0][2] = r0*c2; m[0][3] = r0*c3;
    m[1][0] = r1*c0; m[1][1] = r1*c1; m[1][2] = r1*c2; m[1][3] = r1*c3;
    m[2][0] = r1*c0; m[2][1] = r2*c1; m[2][2] = r2*c2; m[2][3] = r2*c3;
    m[3][0] = r3*c0; m[3][1] = r3*c1; m[3][2] = r3*c2; m[3][3] = r3*c3;
    return *this;
}
mat4& mat4::operator=(mat4 M){
    m[0][0] = M.m[0][0]; m[0][1] = M.m[0][1]; m[0][2] = M.m[0][2]; m[0][3] = M.m[0][3];
    m[1][0] = M.m[1][0]; m[1][1] = M.m[1][1]; m[1][2] = M.m[1][2]; m[1][3] = M.m[1][3];
    m[2][0] = M.m[2][0]; m[2][1] = M.m[2][1]; m[2][2] = M.m[2][2]; m[2][3] = M.m[2][3];
    m[3][0] = M.m[3][0]; m[3][1] = M.m[3][1]; m[3][2] = M.m[3][2]; m[3][3] = M.m[3][3];
    return *this;
}
mat4& mat4::operator=(float M[16]){
    m[0][0] = M[0]; m[0][1] = M[1]; m[0][2] = M[2]; m[0][3] = M[3];
    m[1][0] = M[4]; m[1][1] = M[5]; m[1][2] = M[6]; m[1][3] = M[7];
    m[2][0] = M[8]; m[2][1] = M[9]; m[2][2] = M[10]; m[2][3] = M[11];
    m[3][0] = M[12]; m[3][1] = M[13]; m[3][2] = M[14]; m[3][3] = M[15];
    return *this;
}
vec4 mat4::row(int n){
    return vec4(m[n][0], m[n][1], m[n][2], m[n][3]);
}
vec4 mat4::col(int n){
    return vec4(m[0][n], m[1][n], m[2][n], m[3][n]);
}

// |------------------------------------------UTIL------------------------------------------|

vec3 cross(vec3 l, vec3 r){
    return (l^r);
}
vec3 normalize(vec3 v){
    return v.normal();
}
float magnitude(vec3 v){
    return v.magnitude();
}
float buffer(vec3 v){
    return (v.x*v.x + v.y*v.y + v.z*v.z);
}
mat4 modelMatrix(vec3 scale, vec3 rotate, vec3 translate){
    return ((translate4(translate)) * (rotate4(rotate)) * (scale4(scale)));
}
mat4 scale4(vec3 v){
    return mat4(
        vec4(v.x,0,0,0),
        vec4(0,v.y,0,0),
        vec4(0,0,v.z,0),
        vec4(0,0,0,1)
    );
}
mat4 translate4(vec3 v){
    return mat4(
        vec4(1,0,0,v.x),
        vec4(0,1,0,v.y),
        vec4(0,0,1,v.z),
        vec4(0,0,0,1)
    );
}
mat4 rotate4(vec3 v){
    mat4 x = IDEN4;
    mat4 y = IDEN4;
    mat4 z = IDEN4;
    if (v.x != 0){ x = rotatex(v.x*D2R); }
    if (v.y != 0){ x = rotatey(v.y*D2R); }
    if (v.z != 0){ x = rotatez(v.z*D2R); }
    return x*y*z;
}
mat4 rotatex(float d){
    return mat4(
        1,0,0,0,
        0,cos(d),sin(d),0,
        0,-sin(d),cos(d),0,
        0,0,0,1
    );
}
mat4 rotatey(float d){
    return mat4(
        cos(d),0,-sin(d),0,
        0,1,0,0,
        sin(d),0,cos(d),0,
        0,0,0,1
    );
}
mat4 rotatez(float d){
    return mat4(
        cos(d),sin(d),0,0,
        -sin(d),cos(d),0,0,
        0,0,1,0,
        0,0,0,1
    );
}