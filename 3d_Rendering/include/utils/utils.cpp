#include "utils.hpp"

const double PERSPECTIVE_CONST = M_PI/360.0;
const double SQRT_TWO = sqrt(2.0);
const double SQRT_TWO_INVERSE = 1.0/SQRT_TWO;
const double G = -6.6743e-11;
const double AU = 1.495978707e11;
// AU in pixel units
const double AU_PIXEL = 100.0;
const double ROTATE_UNIT = 1.0/180.0*M_PI;

XYZ ROTATE{.xy = NONE, .z = NONE};

// aspectRatio = Width/Height
mat4 perspectiveMatrix(double degrees, double aspectRatio, double nearPlane, double farPlane){
    double fov = 1.0/tan(degrees/2.0*M_PI/180.0);
    mat4 perspective = mat4(0.0);
    perspective.m00 = fov;
    perspective.m11 = fov;
    perspective.m22 = -(farPlane)/(farPlane-nearPlane);
    perspective.m23 = (-farPlane * nearPlane)/(farPlane - nearPlane);
    perspective.m32 = -1;
    return perspective;
}