#include "settings.h"
#include "object.h"
#include "quadtree.h"

int main(){
    window.setFramerateLimit(144);
    window.setPosition(sf::Vector2i(0,0));
    quadtree tree = quadtree(35);
    sf::Clock clock;
    sf::Time elapsed;
    while(window.isOpen()){
        elapsed = clock.restart();
        std::cout << 1.f/elapsed.asSeconds() << std::endl;
        tree.update();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
        if (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.close(); }
        }
        window.clear(sf::Color::Black);
        window.draw(tree);
        window.display();
    }
}

// int main(){
//     window.setFramerateLimit(144);
//     window.setPosition(sf::Vector2i(0,0));
//     // quadtree tree = quadtree(20);
//     object o1({100,250});
//     object o2({100,200});
//     object o3({125,225});
//     o1.setVelocity({0,-10});
//     o2.setVelocity({0,10});
//     o3.setVelocity({-10,0});
//     sf::CircleShape c1;
//     sf::CircleShape c2;
//     sf::CircleShape c3;
//     c1.setRadius(5);
//     c2.setRadius(5);
//     c3.setRadius(5);
//     c1.setOrigin({5,5});
//     c2.setOrigin({5,5});
//     c3.setOrigin({5,5});
//     c1.setFillColor(sf::Color::Blue);
//     c2.setFillColor(sf::Color::Red);
//     c3.setFillColor(sf::Color::Green);
//     while(window.isOpen()){
//         // tree.update();
//         o1.update();
//         o2.update();
//         o3.update();
//         if (o1.collision(o2)){ o1.collide(o2); }
//         if (o2.collision(o3)){ o2.collide(o3); }
//         if (o3.collision(o1)){ o3.collide(o1); }
//         c1.setPosition(sf::Vector2f(o1));
//         c2.setPosition(sf::Vector2f(o2));
//         c3.setPosition(sf::Vector2f(o3));
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
//         if (window.pollEvent(event)){
//             if (event.type == sf::Event::Closed){ window.close(); }
//         }
//         window.clear(sf::Color::Black);
//         window.draw(c1);
//         window.draw(c2);
//         window.draw(c3);
//         // window.draw(tree);
//         window.display();
//     }
// }