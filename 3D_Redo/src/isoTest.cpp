#include "globals.hpp"
#include "../render/render.hpp"
#include "../vertex/geometry.hpp"

class line : public sf::Drawable {
    public:
    vec3 points[2];
    sf::VertexArray verts;
    line(vec3 p1, vec3 p2){
        verts.resize(2);
        verts.setPrimitiveType(sf::Lines);
        points[0] = p1;
        points[1] = p2;
    }
    void color(int c){
        switch(c){
            case 0:
                verts[0].color = sf::Color::Red;
                verts[1].color = sf::Color::Red;
                break;
            case 1:
                verts[0].color = sf::Color::Cyan;
                verts[1].color = sf::Color::Cyan;
                break;
            case 2:
                verts[0].color = sf::Color::Green;
                verts[1].color = sf::Color::Green;
                break;
        }
    }
    void setPos(vec3 pos1, vec3 pos2){
        verts[0].position = sf::Vector2f(pos1.x, pos1.y);
        verts[1].position = sf::Vector2f(pos2.x, pos2.y);
    }
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
        target.draw(verts);
    }
};

int main(){
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D RENDERER");
    sf::Event event;
    window.setFramerateLimit(144.0);
    userProcess up = userProcess();
    render r = render(vec3(10,10,10),vec3(0,0,0));
    float ftemp[2] = {0,0};

    icosphere test = icosphere();
    test.subdivide();
    test.subdivide();
    // test.subdivide();
    // test.subdivide();
    // test.subdivide();
    // test.subdivide();




    line axes[3] = {line(vec3(1,0,0),vec3(0,0,0)),
                    line(vec3(0,1,0),vec3(0,0,0)),
                    line(vec3(0,0,1),vec3(0,0,0))};
    axes[0].color(0);
    axes[1].color(1);
    axes[2].color(2);

    while (window.isOpen()){
        up.process();
        if (up.isClosed()){ window.close(); break; }
        ftemp[0] = up.longitude;
        ftemp[1] = up.latitude;
        r+=vec3((float)up.dx,(float)up.dy,(float)up.dz);
        r.zoom(up.fov);
        r+=(ftemp);

        for (int i = 0; i < 3; i++){
            axes[i].setPos(r.projectPoint(axes[i].points[0]), r.projectPoint(axes[i].points[1]));
        }
        test(r);


        window.clear(sf::Color::Black);
        for (int i = 0; i < 3; i++){
            window.draw(axes[i]);
        }
        window.draw(test);
        window.display();
        // r.print();
        // test.print();
    }
    return 0;
}