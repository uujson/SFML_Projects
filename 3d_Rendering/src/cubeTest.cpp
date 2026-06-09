#include "renderer/render.hpp"
#include "../include/algebra/shape.hpp"

class axis : public sf::Drawable {
    public:
    vec3 points[2];
    sf::VertexArray verts;
    axis(vec3 p1, vec3 p2){
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
                verts[0].color = sf::Color::Blue;
                verts[1].color = sf::Color::Blue;
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


class line : public sf::Drawable {
    public:
        vec3 position[2];
        sf::VertexArray vertices;
        line(){
            vertices.resize(2);
            vertices.setPrimitiveType(sf::Lines);
            vertices[0].color = sf::Color::White;
            vertices[1].color = sf::Color::White;
        }
        void setPosition(vec3 pos1,){
            vertices[0].position = sf::Vector2f(pos1.x, pos1.y);
        }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
            target.draw(vertices);
        }
};


int main(){
    double radians = 0.0;
    double Z = 0.0;
    render r = render(vec3(0,0,0),45.0);
    cube testCube = cube({0,0,0},{0,0,0},{1,1,1});
    cube tCube = cube({2,2,0},{0,0,0},{0.5,0.5,0.5});
    line lines[12];
    line lineline[12];
    sf::CircleShape circ = sf::CircleShape(5);
    circ.setOrigin(5,5);
    axis x = axis(vec3(10,0,0), vec3(-10,0,0));
    x.color(0);
    axis y = axis(vec3(0,10,0), vec3(0,-10,0));
    y.color(1);
    axis z = axis(vec3(0,0,10), vec3(0,0,-10));
    z.color(2);
    // cube testCube;
    // testCube;
    sf::VertexArray verts;
    sf::VertexArray tv;
    tv.resize(36);
    tv.setPrimitiveType(sf::Triangles);
    verts.resize(36);
    verts.setPrimitiveType(sf::Triangles);
    window.setFramerateLimit(60.0);
    double radius = 5;
    while (window.isOpen()){
        r.setCameraPosition(vec3(radius*cos(Z)*cos(radians),radius*cos(Z)*sin(radians),radius*sin(Z)));
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ radians += 0.01; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ radians -= 0.01; }
        // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ r.moveCamera(vec3(-0.1,0,0)); }
        // else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ r.moveCamera(vec3(0.1,0,0)); }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ Z -= 0.01; }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ Z += 0.01; }
        for (int i = 0; i < 36; i++){
            vec3 temp = r.project(testCube.points[i]);
            vec3 temp1 = r.project(tCube.points[i]);
            verts[i].position = sf::Vector2f(temp.x,temp.y);
            verts[i].color = testCube.triangles[(i)/3].color;
            tv[i].position = sf::Vector2f(temp1.x,temp1.y);
            tv[i].color = tCube.triangles[(i)/3].color;
        }
        for (int i = 0; i < 12; i++){
            vec3 temptemp = r.project(r.getCameraTarget());
            vec3 tempcc = r.project(r.getCameraPosition());
            vec3 temp = r.project(testCube.triangles[i].midpoint);
            vec3 temp2 = r.project(testCube.triangles[i].midpoint + testCube.triangles[i].normal);
            lineline[i].setPosition(temp);
            lines[i].vertices[0].position = sf::Vector2f(temp2.x, temp2.y);
            lines[i].setPosition(temp);
            lines[i].vertices[0].color = sf::Color::Red;
            lineline[i].vertices[0].position = sf::Vector2f(temptemp.x,temptemp.y);

        }
        vec3 tempt = r.project(r.getCameraTarget());
        x.setPos(r.project(x.points[0]), r.project(x.points[1]));
        y.setPos(r.project(y.points[0]), r.project(y.points[1]));
        z.setPos(r.project(z.points[0]), r.project(z.points[1]));
        circ.setPosition({(float)tempt.x, (float)tempt.y});
        testCube.updatePoints(r.getCameraPosition(),r.getCameraNormal(),r.getCameraTarget());
        tCube.updatePoints(r.getCameraPosition(),r.getCameraNormal(),r.getCameraTarget());
        if (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){ window.close(); }
        }
        window.clear(sf::Color::Black);
        window.draw(verts);
        window.draw(tv);
        for (int i = 0; i < 12; i++){
            window.draw(lineline[i]);
        }
        for (int i = 0; i < 12; i++){
            window.draw(lines[i]);
        }
        window.draw(x);
        window.draw(y);
        window.draw(z);
        window.draw(circ);
        window.display();
        vec3 temp = r.getCameraTarget();
        std::cout << temp.x << ' ' << temp.y << ' ' << temp.z << std::endl;
        // radians += 0.01;
    }
    return 0;
}