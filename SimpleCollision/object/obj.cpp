#include "obj.h"

obj::obj(sf::Vector2f pos, sf::Vector2f v){
    point.setRadius(10.f);
    point.setOrigin({10.f,10.f});
    point.setPosition(pos);
    point.setFillColor(sf::Color::Blue);
    velocity = v;
}

obj::obj(sf::Vector2f pos) : obj(pos, {0.f,0.f}){}

int obj::inBounds(sf::Vector2f v){
    sf::Vector2f tempPos = point.getPosition() + v;
    if (tempPos.x < 0){ return 1; }
    else if (tempPos.x > windowWidth){ return 2; }
    if (tempPos.y < 0){ return 3; }
    else if (tempPos.y > windowHeight){ return 4; }
    return 0;
}

void obj::setVelocity(sf::Vector2f v){
    velocity = v;
}

void obj::update(float dt){
    sf::Vector2f temp = point.getPosition();
    float oldX = temp.x;
    float oldY = temp.y;
    float newX;
    float newY;
    float dt1;
    switch(inBounds({velocity.x*dt,0.f})){
        case 0:
            newX = oldX + velocity.x*dt;
            break;
        case 1:
            dt1 = oldX/velocity.x;
            velocity.x *= -1;
            newX = (dt-dt1)*velocity.x;
            break;
        case 2:
            dt1 = (windowWidth - oldX - 10)/velocity.x;
            velocity.x *= -1;
            newX = windowWidth + (dt-dt1)*velocity.x;
            break;
    }
    switch(inBounds({0.f,velocity.y*dt})){
        case 0:
            newY += oldY + velocity.y*dt;
            break;
        case 3:
            dt1 = oldY/velocity.y;
            velocity.y *= -1;
            newY = (dt-dt1)*velocity.y;
            break;
        case 4:
            dt1 = (windowHeight - oldY - 10)/velocity.y;
            velocity.y *= -1;
            newY = windowHeight + (dt-dt1)*velocity.y;
            break;
    }
    point.setPosition({newX,newY});
}

void obj::draw(sf::RenderTarget &target, sf::RenderStates states) const{
    target.draw(point);
}