#include "grid.h"

grid::grid(){
    firstObject = 0;
    count = 0;
    x = 0;
    y = 0;
    size = 0.f;
}

grid::grid(float dim, int32_t X, int32_t Y){
    firstObject = -1;
    count = 0;
    x = X;
    y = Y;
    size = dim;
}

int32_t grid::element(){
    return firstObject;
}

void grid::insert(){ count += 1; }

bool grid::contains(float X, float Y){
    return ((float(x+1)*size >= X) & (float(x)*size <= X)) & ((float(y)*size >= Y) & (float(y+1)*size <= Y));
}

bool grid::contains(vector2f xy){
    return contains(xy.x, xy.y);
}

bool grid::contains(object o){
    return contains(o.getPosition());
}

void grid::clear(){
    firstObject = -1;
    count = 0;
}