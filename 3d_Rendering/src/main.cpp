#include "renderer/renderer.hpp"


int main(){
    renderer r = renderer(vec3(2.0,2.0,2.0),45.0);
    r.project(vec3(0.0,0.0,0.0));
    r.project(vec3(0.1,0.0,0.0));
    r.project(vec3(0.0,0.1,0.0));
    r.project(vec3(0.0,0.0,0.1));
    // renderer r = renderer();
    // line xline = line(0);
    // line yline = line(1);
    // // line zline = line(2);
    // window.setFramerateLimit(60.0);
    // while (window.isOpen()){
    //     ROTATE.xy = NONE;
    //     ROTATE.z = POSITIVE;
    //     r.rotate();
    //     xline.setpos(r.screenProjection(r.project(xline.linepos)));
    //     yline.setpos(r.screenProjection(r.project(yline.linepos)));
    //     // zline.setpos(r.screenProjection(r.project(zline.linepos)));

    //     if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
    //     if (window.pollEvent(event)){
    //         if (event.type == sf::Event::Closed){ window.close(); }
    //     }
    //     window.clear(sf::Color::Black);
    //     window.draw(xline);
    //     window.draw(yline);
    //     // window.draw(zline);
    //     window.display();
    // }
    return 0;
}