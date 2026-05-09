#include "object.h"

float randF(){
    return float(rand()%200-100)/10.f;
}

object::object(sf::Vector2f pos){
    position = pos;
    velocity = {randF(), randF()};
    mass = 1;
    // mass = float(rand()%10)+0.1;
}

void object::update(){
    position += velocity/20.f;
    int walls[4] = {(position.y <= RADIUS)*1, (position.x > windowWidth-RADIUS)*2, (position.x <= RADIUS)*3, (position.y > windowHeight-RADIUS)*4};
    for (int i = 0; i < 4; i++){
        collide(walls[i]);
    }
}

bool object::estimate(object &other){
    sf::Vector2f distance = position - sf::Vector2f(other);
    return ((abs(distance.x) <= RADIUS) || (abs(distance.y) <= RADIUS));
}

bool object::collision(object &other){
    return (sqd(sf::Vector2f(other),position) < (SQUARE_RADIUS));
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
    sf::Vector2f tempP1 = position;
    sf::Vector2f tempP2 = otherP;
    sf::Vector2f tempV = velocity - otherV;
    sf::Vector2f tempP = tempP1 - tempP2;
    sf::Vector2f newV1 = velocity - ((2*other.getMass())/(other.getMass()+mass))*(tempV.x*tempP.x + tempV.y*tempP.y)/(float(pow(tempP.x,2) + pow(tempP.y,2)))*(tempP);
    sf::Vector2f newV2 = otherV - ((2*mass)/(other.getMass()+mass))*((otherV.x - velocity.x)*(tempP2.x - tempP1.x) + (otherV.y - velocity.y)*(tempP2.y - tempP1.y))/(float(pow((tempP2.x - tempP1.x),2) + pow((tempP2.y - tempP1.y),2)))*(tempP2 - tempP1);
    other.setVelocity(newV2);
    setVelocity(newV1);
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
            if ((position.y - RADIUS) + velocity.y*tickTime < 0){
                velocity.y *= -1.f;
            }
            break;
        case 2:
            if (position.x + RADIUS + velocity.x*tickTime >= windowWidth){
                velocity.x *= -1.f;
            }
            break;
        case 3:
            if (position.x - RADIUS + velocity.x*tickTime < 0){
                velocity.x *= -1.f;
            }
            break;
        case 4:
            if (position.y + RADIUS + velocity.y*tickTime >= windowHeight){
                velocity.y *= -1.f;
            }
            break;
    }
}