#pragma once

#ifndef UTILS_HPP
#define UTILS_HPP

#include "../settings/settings.hpp"
#include "../algebra/linalg.hpp"

extern const double G;
extern const double AU;
extern const double AU_PIXEL;
extern const double ROTATE_UNIT;

void print(mat3 matrix);
void print(mat4 matrix);

mat4 projectionMatrix(double degrees, double aspectRatio, double nearPlane, double farPlane);

#endif