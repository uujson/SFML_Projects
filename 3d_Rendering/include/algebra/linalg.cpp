#include "linalg.hpp"

//----------------------------------------------| Constant Variables |----------------------------------------------\\

const double DEG2RADS = M_PI/180.0;
const vec3 ZERO3 = vec3(0,0,0);
const vec4 ZERO4 = vec4(0,0,0,1);
const mat3 IDEN3 = mat3(
    1,0,0,
    0,1,0,
    0,0,1
);
const mat4 IDEN4 = mat4(
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1
);

//----------------------------------------------| 3D Vector Helpers |----------------------------------------------\\

double magnitude(vec3 v){ return v.magnitude(); }

vec3 normalize(vec3 v){ return v.normalized(); }

vec3 cross(vec3 l, vec3 r){ return l(r); }

double buffer(vec3 v){ return (v.x*v.x + v.y*v.y + v.z*v.z); }

//----------------------------------------------| 2D Vector |----------------------------------------------\\

vec2::vec2() : vec2(0,0){}
vec2::vec2(const double &X, const double &Y) : x(X), y(Y){}
vec2 vec2::operator/(const double &o){ return vec2(x/o,y/o); }

//----------------------------------------------| 3D Vector |----------------------------------------------\\

vec3::vec3() : vec3(0,0,0){}
vec3::vec3(const double XYZ[3]) : vec3(XYZ[0], XYZ[1], XYZ[2]){}
vec3::vec3(vec4 XYZW) : vec3(XYZW.x, XYZW.y, XYZW.z){}
vec3::vec3(const double &X, const double &Y, const double &Z) : x(X), y(Y), z(Z){}
// scalar operators
vec3 vec3::operator*(const double &o){ return vec3(x * o, y * o, z * o); }
vec3 vec3::operator/(const double &o){ return vec3(x / o, y / o, z / o); }
vec3 vec3::operator-(){ return vec3(-x,-y,-z); }
// vector operators
vec3 vec3::operator+(const vec3 &o){ return vec3(x + o.x, y + o.y, z + o.z); }
vec3 vec3::operator-(const vec3 &o){ return vec3(x - o.x, y - o.y, z - o.z); }
// scalar assignment operators
vec3& vec3::operator=(const double o[3]){ x = o[0]; y = o[1]; z = o[2]; return *this; }
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

//----------------------------------------------| 4D Vector |----------------------------------------------\\

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

//----------------------------------------------| 3x3 Matrix |----------------------------------------------\\

mat3::mat3() : mat3(1.0){}
mat3::mat3(const double d00, const double d01, const double d02,
        const double d10, const double d11, const double d12,
        const double d20, const double d21, const double d22) : mat3(
            vec3(d00,d01,d02),
            vec3(d10,d11,d12),
            vec3(d20,d21,d22)
        ){}
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
    m[0][0] = r0.x; m[0][1] = r0.y; m[0][2] = r0.z;
    m[1][0] = r1.x; m[1][1] = r1.y; m[1][2] = r1.z;
    m[2][0] = r2.x; m[2][1] = r2.y; m[2][2] = r2.z;
}
vec3 mat3::operator*(vec3 v){ return vec3(v*(*this)[0], v*(*this)[1], v*(*this)[2]); }
mat3 mat3::operator*(mat3 o){
    vec3 o0,o1,o2,m0,m1,m2;
    o0 = o.col(0);
    o1 = o.col(1);
    o2 = o.col(2);
    m0 = (*this)[0];
    m1 = (*this)[1];
    m2 = (*this)[2];
    return mat3(
        vec3(m0*o0, m0*o1, m0*o2),
        vec3(m1*o0, m1*o1, m1*o2),
        vec3(m2*o0, m2*o1, m2*o2)
    );
}
vec3 mat3::row(const int &n){ return (*this)[n]; }
vec3 mat3::col(const int &n){ return vec3(m[0][n], m[1][n], m[2][n]); }
mat3& mat3::operator*=(mat3 o){
    vec3 o0,o1,o2,m0,m1,m2;
    o0 = o.col(0);
    o1 = o.col(1);
    o2 = o.col(2);
    m0 = (*this)[0];
    m1 = (*this)[1];
    m2 = (*this)[2];
    m[0][0] = m0*o0; m[0][1] = m0*o1; m[0][2] = m0*o2;
    m[1][0] = m1*o0; m[1][1] = m1*o1; m[1][2] = m1*o2;
    m[2][0] = m2*o0; m[2][1] = m2*o1; m[2][2] = m2*o2;
    return *this;
}
mat3& mat3::operator=(const mat3 &o){
    m[0][0] = o.m[0][0]; m[0][1] = o.m[0][1]; m[0][2] = o.m[0][2];
    m[1][0] = o.m[1][0]; m[1][1] = o.m[1][1]; m[1][2] = o.m[1][2];
    m[2][0] = o.m[2][0]; m[2][1] = o.m[2][1]; m[2][2] = o.m[2][2];
    return *this;
}
vec3 mat3::operator[](const int n){ return vec3(m[n][0],m[n][1],m[n][2]); }

//----------------------------------------------| 4x4 Matrix |----------------------------------------------\\

mat4::mat4() : mat4(1.0){}
mat4::mat4(const double d00, const double d01, const double d02, const double d03,
    const double d10, const double d11, const double d12, const double d13,
    const double d20, const double d21, const double d22, const double d23,
    const double d30, const double d31, const double d32, const double d33) : mat4(
            vec4(d00,d01,d02,d03),
            vec4(d10,d11,d12,d13),
            vec4(d20,d21,d22,d23),
            vec4(d30,d31,d32,d33)
        ){}
mat4::mat4(const double &n){
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            m[i][j] = 0;
        }
    }
    m[0][0] = n;
    m[1][1] = n;
    m[2][2] = n;
    m[3][3] = 1.0;
}
mat4::mat4(const vec4 r0, const vec4 r1, const vec4 r2, const vec4 r3){
    m[0][0] = r0.x; m[0][1] = r0.y; m[0][2] = r0.z; m[0][3] = r0.w;
    m[1][0] = r1.x; m[1][1] = r1.y; m[1][2] = r1.z; m[1][3] = r1.w;
    m[2][0] = r2.x; m[2][1] = r2.y; m[2][2] = r2.z; m[2][3] = r2.w;
    m[3][0] = r2.x; m[3][1] = r2.y; m[3][2] = r3.z; m[3][3] = r3.w;
}
vec4 mat4::operator*(vec4 v){ return vec4(v*row(0), v*row(1), v*row(2), v*row(3)); }
mat4 mat4::operator*(mat4 o){
    vec4 o0,o1,o2,o3,m0,m1,m2,m3;
    o0 = o.col(0);
    o1 = o.col(1);
    o2 = o.col(2);
    o3 = o.col(3);
    m0 = (*this)[0];
    m1 = (*this)[1];
    m2 = (*this)[2];
    m3 = (*this)[3];
    return mat4(
        vec4(m0*o0, m0*o1, m0*o2, m0*o3),
        vec4(m1*o0, m1*o1, m1*o2, m1*o3),
        vec4(m2*o0, m2*o1, m2*o2, m2*o3),
        vec4(m3*o0, m3*o1, m3*o2, m3*o3)
    );
}
vec4 mat4::row(const int &n){ return (*this)[n]; }
vec4 mat4::col(const int &n){ return vec4(m[0][n], m[1][n], m[2][n], m[3][n]); }
mat4& mat4::operator*=(mat4 o){
    vec4 o0,o1,o2,o3,m0,m1,m2,m3;
    o0 = o.col(0);
    o1 = o.col(1);
    o2 = o.col(2);
    o3 = o.col(3);
    m0 = (*this)[0];
    m1 = (*this)[1];
    m2 = (*this)[2];
    m3 = (*this)[3];
    m[0][0] = m0*o0; m[0][1] = m0*o1; m[0][2] = m0*o2; m[0][3] = m0*o3;
    m[1][0] = m1*o0; m[1][1] = m1*o1; m[1][2] = m1*o2; m[1][3] = m1*o3;
    m[2][0] = m2*o0; m[2][1] = m2*o1; m[2][2] = m2*o2; m[2][3] = m2*o3;
    m[3][0] = m3*o0; m[3][1] = m3*o1; m[3][2] = m3*o2; m[3][3] = m3*o3;
    return *this;
}
mat4& mat4::operator=(const mat4 &o){
    m[0][0] = o.m[0][0]; m[0][1] = o.m[0][1]; m[0][2] = o.m[0][2]; m[0][3] = o.m[0][3];
    m[1][0] = o.m[1][0]; m[1][1] = o.m[1][1]; m[1][2] = o.m[1][2]; m[1][3] = o.m[1][3];
    m[2][0] = o.m[2][0]; m[2][1] = o.m[2][1]; m[2][2] = o.m[2][2]; m[2][3] = o.m[2][3];
    m[3][0] = o.m[3][0]; m[3][1] = o.m[3][1]; m[3][2] = o.m[3][2]; m[3][3] = o.m[3][3];
    return *this;
}
vec4 mat4::operator[](const int n){ return vec4(m[n][0],m[n][1],m[n][2],m[n][3]); }


//----------------------------------------------| Modelling Matrix things |----------------------------------------------\\

mat4 modelMatrix(vec3 scale, vec3 rotate, vec3 translate){
    return ((translate4(translate))*(rotate4(rotate))*(scale4(scale)));
}

mat4 translate4(vec3 xyz){
    return mat4(
        vec4(1,0,0,xyz.x),
        vec4(0,1,0,xyz.y),
        vec4(0,0,1,xyz.z),
        vec4(0,0,0,1)
    );
}

mat4 rotate4(vec3 xyz){
    mat4 x = mat4();
    mat4 y = mat4();
    mat4 z = mat4();
    if (xyz.x != 0){ x = rotatex(xyz.x); }
    if (xyz.y != 0){ y = rotatey(xyz.y); }
    if (xyz.z != 0){ z = rotatez(xyz.z); }
    return (x*y*z);
}

mat4 scale4(vec3 xyz){
    return mat4(
        vec4(xyz.x,0,0,0),
        vec4(0,xyz.y,0,0),
        vec4(0,0,xyz.z,0),
        vec4(0,0,0,1)
    );
}

mat4 rotatex(double d){
    return mat4(
        vec4(1,0,0,0),
        vec4(0,cos(d),sin(d),0),
        vec4(0,-sin(d),cos(d),0),
        vec4(0,0,0,1)
    );
}

mat4 rotatey(double d){
    return mat4(
        vec4(cos(d),0,-sin(d),0),
        vec4(0,1,0,0),
        vec4(sin(d),0,cos(d),0),
        vec4(0,0,0,1)
    );
}

mat4 rotatez(double d){
    return mat4(
        vec4(cos(d),sin(d),0,0),
        vec4(-sin(d),cos(d),0,0),
        vec4(0,0,1,0),
        vec4(0,0,0,1)
    );
}