#include "vector2f.h"

vector2f::vector2f(){
    x = 0;
    y = 0;
}

vector2f::vector2f(float X, float Y){
    x = X;
    y = Y;
}

vector2f vector2f::operator+(vector2f other){
    return vector2f(x+other.x, y+other.y);
}

vector2f vector2f::operator-(vector2f other){
    return vector2f(x-other.x, y-other.y);
}

vector2f vector2f::operator/(const float f){
    return vector2f(x/f, y/f);
}

float vector2f::operator*(vector2f other){
    return (x*other.x + y*other.y);
}

vector2f vector2f::operator*(const float f){
    return vector2f(x*f, y*f);
}

vector2f &vector2f::operator=(const vector2f other){
    x = other.x;
    y = other.y;
}

vector2f &vector2f::operator=(const int other){
    x = float(other);
    y = float(other);
}

vector2f &vector2f::operator/=(const float other){
    x /= other;
    y /= other;
}

vector2f &vector2f::operator*=(const float other){
    x *= other;
    y *= other;
}

vector2f &vector2f::operator+=(const vector2f other){
    x += other.x;
    y += other.y;
}

vector2f &vector2f::operator-=(const vector2f other){
    x -= other.x;
    y -= other.y;
}

bool vector2f::operator==(const vector2f other){
    return (x == other.x & y == other.y);
}

bool vector2f::operator!=(const vector2f other){
    return (x != other.x || y != other.y);
}

bool vector2f::operator==(const float f){
    return (x == f || y == f);
}

bool vector2f::operator!=(const float f){
    return (x != f || y != f);
}

float vector2f::dot(vector2f other){
    return (x*other.x + y*other.y);
}

float vector2f::sqd(){
    return (x*x + y*y);
}

void vector2f::zero(){
    x = 0;
    y = 0;
}

