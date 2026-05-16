#include "object.h"

float randFloat(){
    return float(rand()%5)-2.5;
}

object::object(){
    radius = 0.f;
    mass = 0.f;
    position.zero();
    velocity.zero();
}

object::object(vector2f pos){
    position = pos;
    radius = 2.f;
    mass = 1.f;
    velocity.x = randFloat();
    velocity.y = randFloat();
}

object::object(float x, float y) : object(vector2f(x,y)) {}

vector2f object::getPosition(){ return position; }

vector2f object::getVelocity(){ return velocity; }

float object::getRadius(){ return radius; }

float object::getMass(){ return mass; }

void object::update(){
    position += velocity*tickTime;
    int walls[4] = {(position.y <= radius)*1, (position.x > windowWidth-radius)*2, (position.x <= radius)*3, (position.y > windowHeight-radius)*4};
    for (int i = 0; i < 4; i++){
        bounce(walls[i]);
    }
}

void object::setVelocity(vector2f v){ velocity = v; }

void object::velocityChange(vector2f v){
    newVelocity += v;
}

bool object::intersect(object other){
    float totalRadius = (other.getRadius() + radius);
    vector2f temp = position - other.getPosition();
    return ((position - other.getPosition()).sqd() <= (totalRadius*totalRadius));
}

void object::collide(object &other){
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
    setVelocity(new0);
    other.setVelocity(new1);
}

void object::bounce(int wall){
    float dt = 0;
    float tempX = velocity.x;
    float tempY = velocity.y;
    switch(wall){
        case 1:
            if ((position.y - radius) + velocity.y*tickTime < 0){
                tempY *= -1.f;
            }
            break;
        case 2:
            if (position.x + radius + velocity.x*tickTime >= windowWidth){
                tempX *= -1.f;
            }
            break;
        case 3:
            if (position.x - radius + velocity.x*tickTime < 0){
                tempX *= -1.f;
            }
            break;
        case 4:
            if (position.y + radius + velocity.y*tickTime >= windowHeight){
                tempY *= -1.f;
            }
            break;
    }
    setVelocity(vector2f(tempX,tempY));
}