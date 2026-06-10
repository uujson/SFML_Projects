#ifndef USER_PROCESS_HPP
#define USER_PROCESS_HPP

#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

class userProcess{
    public:
        float dx,dy,dz,fov,longitude,latitude;
        bool close;
        userProcess(){
            close = false;
        }
        void process(){
            dx = 0;
            dy = 0;
            dz = 0;
            fov = 0;
            longitude = 0;
            latitude = 0;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ close = true; }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ dx -= 1; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ dx += 1; }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){ dy += 1; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){ dy -= 1; }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ dz += 1; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){ dz -= 1; }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ longitude -= 1; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ longitude += 1; }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ latitude += 1; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ latitude -= 1; }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add)){ fov -= 1; }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract)){ fov += 1; }
        }
        bool isClosed(){ return close; }
};

#endif