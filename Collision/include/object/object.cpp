#include "object.h"

object::object(int n, float h, float w, float e, float f, float m, float av, float a, sf::Vector2f v, sf::Vector2f pos){
    npoints = n;
    height = h;
    width = w;
    elasticity = e;
    friction = f;
    mass = m;
    angv = av;
    angle = a;
    velocity = v;
    position = pos;
}

object::object() :
    object(4,50.0,50.0,1,-0.01,1,0,0,sf::Vector2f(0,0),sf::Vector2f(windowWidth/2,windowHeight/2)){}

object::object(int n) :
    object(n,50.0,50.0,1,-0.01,1,0,0,sf::Vector2f(0,0),sf::Vector2f(windowWidth/2,windowHeight/2)){}

object::object(int n, float r) :
    object(n,r,r,1,-0.01,1,0,0,sf::Vector2f(0,0),sf::Vector2f(windowWidth/2,windowHeight/2)){}

object::object(float r, sf::Vector2f pos) :
    object(4,r,r,1,-0.01,1,0,0,sf::Vector2f(0,0),pos){}

object::object(int n, float r, sf::Vector2f pos) :
    object(n,r,r,1,-0.01,1,0,0,sf::Vector2f(0,0),pos){}

void object::rotate(float degrees){
    angle += degrees;
}

void object::move(sf::Vector2f v){
    position += v;
}

void object::update(){
    if (angv != 0){
        rotate(angv);
        float accelDegrees = friction*angv/mass;
        angv += accelDegrees;
        if (abs(angv*60) < 0.01){ angv = 0; }
    }
    if (velocity != sf::Vector2f(0,0)){
        move(velocity);
        float acceleration = friction/mass;
        velocity.x += acceleration*velocity.x;
        velocity.y += acceleration*velocity.y;
        if (abs(velocity.x) < friction){ velocity.x = 0; }
        if (abs(velocity.y) < friction){ velocity.y = 0; }
    }
}