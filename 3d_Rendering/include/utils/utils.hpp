#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include "../settings/settings.hpp"
#include "../algebra/linalg.hpp"

enum DIRECTION{ NEGATIVE = -1, NONE = 0, POSITIVE = 1};

struct XYZ{
    DIRECTION xy,z;
};

extern const double SQRT_TWO;
extern const double SQRT_TWO_INVERSE;
extern const double G;
extern const double AU;
extern const double AU_PIXEL;
extern const double ROTATE_UNIT;
extern const double TRANSLATE_UNIT;
extern const double PERSPECTIVE_CONST;
extern XYZ ROTATE;

mat4 perspectiveMatrix(double degrees, double aspectRatio, double nearPlane, double farPlane);

#endif