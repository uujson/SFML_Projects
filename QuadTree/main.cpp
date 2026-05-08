#include "settings.h"
#include "object.h"
#include "quadtree.h"

int main(){
    window.setFramerateLimit(144);
    window.setPosition(sf::Vector2i(0,0));
    // quadtree tree = quadtree(20);
    object o1({100,250});
    object o2({100,200});
    o1.setVelocity({0,-10});
    o2.setVelocity({0,10});
    sf::CircleShape c1;
    sf::CircleShape c2;
    c1.setRadius(10);
    c2.setRadius(10);
    c1.setOrigin({10,10});
    c2.setOrigin({10,10});
    c1.setFillColor(sf::Color::Blue);
    c2.setFillColor(sf::Color::Red);
    while(window.isOpen()){
        // tree.update();
        o1.update();
        o2.update();
        if (o1.collision(o2)){ o1.collide(o2); }
        c1.setPosition(sf::Vector2f(o1));
        c2.setPosition(sf::Vector2f(o2));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
        if (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.close(); }
        }
        window.clear(sf::Color::Black);
        window.draw(c1);
        window.draw(c2);
        // window.draw(tree);
        window.display();
    }
}