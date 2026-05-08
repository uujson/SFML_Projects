#include "object.h"

float randF(){
    return float(rand()%200-100)/10.f;
}

float quad(float a,float b,float c){
    float nx = (-b - sqrt(pow(b,2)-(4*a*(c-(RADIUS*RADIUS*4.f)))))/(2.f*a);
    float px = (-b + sqrt(pow(b,2)-(4*a*(c-(RADIUS*RADIUS*4.f)))))/(2.f*a);
    return abs(std::max(nx,px));
}

object::object(sf::Vector2f pos){
    position = pos;
    velocity = {randF(), randF()};
    mass = 1;
}

void object::update(){
    position += velocity/20.f;
    int walls[4] = {(position.y < 0)*1, (position.x >= windowWidth)*2, (position.x < 0)*3, (position.y >= windowHeight)*4};
    for (int i = 0; i < 4; i++){
        collide(walls[i]);
    }
}

bool object::collision(object &other){
    return (sqd(sf::Vector2f(other),position) < (10.f));
}

sf::Vector2f object::getPosition(){ return position; }

sf::Vector2f object::getVelocity(){ return velocity; }

float object::getMass(){ return mass; }

void object::setVelocity(sf::Vector2f v){ velocity = v; }

void object::setPosition(sf::Vector2f pos){ position = pos; }

object::operator sf::Vector2f() const{ return position; }

void object::collide(object& other){
    sf::Vector2f otherP = sf::Vector2f(other);
    sf::Vector2f otherV = other.getVelocity();
    sf::Vector2f p = otherP-position;
    sf::Vector2f v = otherV-velocity;
    float t = (quad((pow(p.x,2) + pow(p.y,2)),(-2*(p.x*v.x + p.y*v.y)),(pow(v.x,2) + pow(v.y,2))));
    sf::Vector2f tempP1 = position - velocity*t;
    sf::Vector2f tempP2 = otherP - otherV*t;
    sf::Vector2f tempV = velocity - otherV;
    sf::Vector2f tempP = tempP1 - tempP2;
    sf::Vector2f newV1 = velocity - (tempV.x*tempP.x + tempV.y*tempP.y)/(float(pow(tempP.x,2) + pow(tempP.y,2)))*(tempP);
    sf::Vector2f newV2 = otherV - ((otherV.x - velocity.x)*(tempP2.x - tempP1.x) + (otherV.y - velocity.y)*(tempP2.y - tempP1.y))/(float(pow((tempP2.x - tempP1.x),2) + pow((tempP2.y - tempP1.y),2)))*(tempP2 - tempP1);
    other.setVelocity(newV2);
    other.setPosition(tempP2 + newV2*t);
    setVelocity(newV1);
    setPosition(tempP1 + newV1*t);
}

/*
0 -> north
1 -> east
2 -> south
3 -> west
*/
void object::collide(int wall){
    float dt = 0;
    switch(wall){
        case 1:
            if (position.y + velocity.y*tickTime < 0){
                dt = abs((position.y)/velocity.y);
                velocity.y *= -1.f;
                position.y = velocity.y*(tickTime-dt);
            }
            break;
        case 2:
            if (position.x + velocity.x*tickTime >= windowWidth){
                dt = abs((windowWidth - (position.x))/velocity.x);
                velocity.x *= -1.f;
                position.x = windowWidth + (velocity.x*(tickTime-dt));
            }
            break;
        case 3:
            if (position.x + velocity.x*tickTime < 0){
                dt = abs((position.x)/velocity.x);
                velocity.x *= -1.f;
                position.x = velocity.x*(tickTime-dt);
            }
            break;
        case 4:
            if (position.y + velocity.y*tickTime >= windowHeight){
                dt = abs((windowHeight - (position.y))/velocity.y);
                velocity.y *= -1.f;
                position.y = windowHeight + (velocity.y*(tickTime-dt));
            }
            break;
    }
}