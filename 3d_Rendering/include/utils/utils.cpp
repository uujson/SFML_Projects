#include "utils.hpp"

const double G = -6.6743e-11;
const double AU = 1.495978707e11;
// AU in pixel units
const double AU_PIXEL = 100.0;
const double ROTATE_UNIT = 1.0/180.0*M_PI;

void print(mat3 m){
    system("clear");
    std::cout.precision(4);
    std::cout << "[" << m.m[0][0] << "\t]\t\t[" << m.m[0][1] << "\t]\t\t[" << m.m[0][2] << "\t]\n"
              << "[" << m.m[1][0] << "\t]\t\t[" << m.m[1][1] << "\t]\t\t[" << m.m[1][2] << "\t]\n"
              << "[" << m.m[2][0] << "\t]\t\t[" << m.m[2][1] << "\t]\t\t[" << m.m[2][2] << "\t]\n";
}

void print(mat4 m){
    system("clear");
    std::cout.precision(3);
    std::cout << "[" << m.m[0][0] << "\t]\t\t[" << m.m[0][1] << "\t]\t\t[" << m.m[0][2] << "\t]\t\t[" << m.m[0][3] << "\t]\n"
              << "[" << m.m[1][0] << "\t]\t\t[" << m.m[1][1] << "\t]\t\t[" << m.m[1][2] << "\t]\t\t[" << m.m[1][3] << "\t]\n"
              << "[" << m.m[2][0] << "\t]\t\t[" << m.m[2][1] << "\t]\t\t[" << m.m[2][2] << "\t]\t\t[" << m.m[2][3] << "\t]\n"
              << "[" << m.m[3][0] << "\t]\t\t[" << m.m[3][1] << "\t]\t\t[" << m.m[3][2] << "\t]\t\t[" << m.m[3][3] << "\t]\n\n";
}

// aspectRatio = Width/Height
mat4 projectionMatrix(double degrees, double aspectRatio, double nearPlane, double farPlane){
    double fov = 1.0/tan(degrees*DEG2RADS*0.5);
    mat4 perspective = mat4(
        vec4(fov*aspectRatio, 0, 0, 0),
        vec4(0, fov, 0, 0),
        vec4(0, 0, (farPlane)/(farPlane-nearPlane), (farPlane*nearPlane)/(farPlane-nearPlane)),
        vec4(0,0,1, 0)
    );
    return perspective;
}