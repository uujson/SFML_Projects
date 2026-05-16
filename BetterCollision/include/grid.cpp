#include "grid.h"

grid::grid(){
    objects.clear();
    x = 0;
    y = 0;
    xy = 0;
    size = 0.f;
}

grid::grid(float dim, int32_t X, int32_t Y){
    objects.clear();
    x = X;
    y = Y;
    xy.x = (X+1)*dim - dim/2;
    xy.y = (Y+1)*dim - dim/2;
    size = dim;
}

std::vector<std::shared_ptr<object>> grid::update(){
    std::vector<std::shared_ptr<object>> oob;
    for(int i = 0; i < objects.size(); i++){
        for(int j = i+1; j < objects.size(); j++){
            if (objects[i]->intersect(*objects[j])){
                objects[i]->collide(*objects[j]);
            }
        }
        objects[i]->update();
    }
    for(int i = 0; i < objects.size(); i++){
        if(!contains(*objects[i])){
            oob.push_back(objects[i]);
            objects.erase(objects.begin()+i);
            i--;
        }
    }
    return oob;
}

void grid::insert(std::shared_ptr<object> o){
    if(std::find(objects.begin(), objects.end(), o) == objects.end()){
        objects.push_back(o);
    }
}

bool grid::contains(float X, float Y){
    return ((xy.x+size/2 >= X) & (xy.x-size/2 <= X)) & ((xy.y+size/2 >= Y) & (xy.y-size/2 <= Y));
}

bool grid::contains(vector2f xy){
    return contains(xy.x, xy.y);
}

bool grid::contains(object o){
    vector2f position = o.getPosition();
    float radius = o.getRadius();
    return (contains(vector2f(position.x-radius, position.y)) ||
            contains(vector2f(position.x+radius, position.y)) ||
            contains(vector2f(position.x, position.y-radius)) ||
            contains(vector2f(position.x, position.y+radius)) ||
            contains(position));
}

bool grid::contains(std::shared_ptr<object> o){
    return contains(*o);
}

bool grid::isEmpty(){
    return (objects.size() == 0);
}

void grid::clear(){
    objects.clear();
}