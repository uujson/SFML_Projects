#include "utils.hpp"

const double G = -6.6743e-11;
const double AU = 1.495978707e11;
// AU in pixel units
const double AU_PIXEL = 100.0;
const double ROTATE_UNIT = 1.0/180.0*M_PI;

// aspectRatio = Width/Height
mat4 projectionMatrix(double degrees, double aspectRatio, double nearPlane, double farPlane){
    double fov = 1.0/tan(degrees*DEG2RADS*0.5);
    mat4 perspective = mat4(
        vec4(fov*aspectRatio, 0, 0, 0),
        vec4(0, fov, 0, 0),
        vec4(0, 0, -(farPlane)/(farPlane-nearPlane), -1),
        vec4(0,0,-(farPlane*nearPlane)/(farPlane-nearPlane), 0)
    );
    return perspective;
}