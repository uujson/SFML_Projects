#include "object.h"

object::object(){
    index = -1;
    next = -1;
    radius = 0.f;
    mass = 0.f;
    position.zero();
    velocity.zero();
    newVelocity.zero();
}

object::object(int32_t n){
    index = n;
    next = -1;
    radius = 0.f;
    mass = 0.f;
    position.zero();
    velocity.zero();
    newVelocity.zero();
}

object::object(int32_t n, vector2f pos){
    index = n;
    next = -1;
    position = pos;
    radius = float(rand()%5)+1.f;
    mass = radius*radius*M_PI;
    velocity.x = randFloat();
    velocity.y = randFloat();
    newVelocity = velocity;
}

object::object(int32_t n, float x, float y) : object(n, vector2f(x,y)) {}

vector2f object::getPosition(){ return position; }

vector2f object::getVelocity(){ return velocity; }

float object::getX(){ return position.x; }

float object::getY(){ return position.y; }

float object::getRadius(){ return radius; }

float object::getMass(){ return mass; }

int32_t object::getIndex(){ return index; }

int32_t object::getNext(){ return next; }

void object::setNext(int32_t n){ next = n; }

void object::update(){
    if (newVelocity != 0.f){
        velocity = newVelocity;
        newVelocity.zero();
    }
    position += velocity;
}

void object::clear(){ next = -1; }

void object::setVelocity(vector2f v){ velocity = v; }

void object::velocityChange(vector2f v){
    newVelocity += v;
}

bool object::intersect(object other){
    float totalRadius = (other.getRadius() + radius);
    vector2f temp = position - other.getPosition();
    return ((position - other.getPosition()).sqd() <= (totalRadius*totalRadius));
}

vector2f object::collide(object &other){
    vector2f p0 = position;
    vector2f p1 = other.getPosition();
    vector2f v0 = velocity;
    vector2f v1 = other.getVelocity();
    float m0 = getMass();
    float m1 = other.getMass();
    vector2f p10 = p1-p0;
    vector2f p01 = p0-p1;
    vector2f v10 = v1-v0;
    vector2f v01 = v0-v1;
    vector2f new0 = v0 - p10 * (2.f*m1/(m0+m1) * (v10*p10)/p10.sqd());
    vector2f new1 = v1 - p01 * (2.f*m0/(m0+m1) * (v01*p01)/p01.sqd());
    velocityChange(new0);
    other.velocityChange(new1);
}