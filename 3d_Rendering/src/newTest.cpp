#include "../include/renderer/renderer.hpp"
#include <algorithm>
#include <vector>
#include <cmath>


const double N = -1;
const double P = 1;

vec3 CUBE[8] = {
       {N,N,P},{P,N,P},
    {N,P,P},      {P,P,P},

       {N,N,N},{P,N,N},
    {N,P,N},      {P,P,N}
};

class triangle{
    public:
        vec3 normal;
        vec3 midpoint;
        sf::Color color;
        vec3 points[3];
        triangle(){}
        triangle(vec3 p0, vec3 p1, vec3 p2){
            points[0] = p0;
            points[1] = p1;
            points[2] = p2;
            color = sf::Color::White;
            updateNormal();
            updateMidpoint();
        }
        void updateNormal(){
            normal = normalize(cross((points[1]-points[2]),(points[1]-points[0])));
        }
        void updateMidpoint(){ midpoint = (points[0]+points[1]+points[2])/3; }
        triangle& operator=(const triangle o){
            for (int i = 0; i < 3; i++){
                points[i] = o.points[i];
            }
            normal = o.normal;
            midpoint = o.midpoint;
            color = o.color;
            return *this;
        }
        bool operator*(camera c){
            return (normal*(midpoint - c.position) < 0) || (normal*(midpoint - c.lookingAt) < 0);
        }  
};

bool tsort(triangle a, triangle b, camera c){
    return ((c.tNormal*(c.lookingAt - a.midpoint)) <= (c.tNormal*(c.lookingAt - b.midpoint)));
}

class cube : public sf::Drawable{
    public:
        std::vector<triangle> triangles;
        vec3 translate;
        vec3 rotate;
        vec3 scale;
        sf::VertexArray verts;
        vec3 points[36];
        cube() : cube(ZERO3, ZERO3, vec3(1,1,1)){}
        cube(vec3 t,vec3 r, vec3 s){
            verts.resize(36);
            verts.setPrimitiveType(sf::Triangles);
            triangles.reserve(12);
            translate = t;
            rotate = r;
            scale = s;
            // bottom
            triangles[0] = triangle(CUBE[6],CUBE[7],CUBE[5]);
            triangles[1] = triangle(CUBE[5],CUBE[4],CUBE[6]);
            triangles[0].color = sf::Color::Green;
            triangles[1].color = sf::Color::Green;
            
            // top
            triangles[2] = triangle(CUBE[0],CUBE[1],CUBE[3]);
            triangles[3] = triangle(CUBE[3],CUBE[2],CUBE[0]);
            triangles[2].color = sf::Color::Green;
            triangles[3].color = sf::Color::Green;
            
            // back
            triangles[4] = triangle(CUBE[4],CUBE[5],CUBE[1]);
            triangles[5] = triangle(CUBE[1],CUBE[0],CUBE[4]);
            triangles[4].color = sf::Color::Magenta;
            triangles[5].color = sf::Color::Magenta;

            // front
            triangles[10] = triangle(CUBE[7],CUBE[6],CUBE[2]);
            triangles[11] = triangle(CUBE[2],CUBE[3],CUBE[7]);
            triangles[10].color = sf::Color::Blue;
            triangles[11].color = sf::Color::Blue;
            
            // right
            triangles[6] = triangle(CUBE[1],CUBE[5],CUBE[7]);
            triangles[7] = triangle(CUBE[7],CUBE[3],CUBE[1]);
            triangles[6].color = sf::Color::Yellow;
            triangles[7].color = sf::Color::Yellow;
            
            // left
            triangles[8] = triangle(CUBE[6],CUBE[4],CUBE[0]);
            triangles[9] = triangle(CUBE[0],CUBE[2],CUBE[6]);
            triangles[8].color = sf::Color::Red;
            triangles[9].color = sf::Color::Red;
        }
        void update(renderer r){
            std::sort(triangles.begin(), triangles.end(),
                        std::bind(tsort, std::placeholders::_1,std::placeholders::_2, r.Camera));
            for (int i = 0; i < 12; i++){
                int temp = i*3;
                if (triangles[i]*r.Camera){
                    points[temp] = triangles[i].points[0];
                    points[temp+1] = triangles[i].points[1];
                    points[temp+2] = triangles[i].points[2];
                }
                else{
                    points[temp] = ZERO3;
                    points[temp+1] = ZERO3;
                    points[temp+2] = ZERO3;
                }
            }
            for (int i = 0; i < 36; i++){
                vec3 temp = r.project(points[i]);
                verts[i].position = sf::Vector2f(temp.x, temp.y);
                verts[i].color = triangles[i/3].color;
            }
        }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override{
            target.draw(verts);
        }


};

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


int main(){
    renderer r = renderer(vec3(1,1,1),45.0,vec3(0,0,1));
    window.setFramerateLimit(60.0);
    vec3 d = vec3(0,0,0);
    double angles[] = {0,0};
    cube test = cube(ZERO3, ZERO3, vec3(1,1,1));
    line axes[3] = {line(vec3(3,0,0), vec3(0,0,0)), 
                    line(vec3(0,3,0), vec3(0,0,0)), 
                    line(vec3(0,0,3), vec3(0,0,0))};
    axes[0].color(0);
    axes[1].color(1);
    axes[2].color(2);
    while (window.isOpen()){
        test.update(r);
        angles[0] = 0;
        angles[1] = 0;
        d.x = 0;
        d.y = 0;
        d.z = 0;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){ window.close(); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ d.x -= 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ d.x += 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){ d.y -= 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){ d.y += 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){ d.z -= 0.01; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){ d.z += 0.01; }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){ angles[0] += 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){ angles[0] -= 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ angles[1] -= 1; }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){ angles[1] += 1; }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){ r += 1; }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){ r -= 1; }


        r += d;
        r += angles;
        for (int i = 0; i < 3; i++){
            axes[i].setPos(r.project(axes[i].points[0]), r.project(axes[i].points[1]));
        }
        window.clear(sf::Color::Black);
        for (int i = 0; i < 3; i++){
            window.draw(axes[i]);
        }
        window.draw(test);
        system("clear");
        std::cout << r.Camera.position.x << ' ' << r.Camera.position.y << ' ' << r.Camera.position.z << std::endl;
        std::cout << r.Camera.lookingAt.x << ' ' << r.Camera.lookingAt.y << ' ' << r.Camera.lookingAt.z  << std::endl;
        std::cout << r.Camera.tNormal.x << ' ' << r.Camera.tNormal.y << ' ' << r.Camera.tNormal.z << std::endl;
        std::cout << r.Camera.rNormal.x << ' ' << r.Camera.rNormal.y << ' ' << r.Camera.rNormal.z << std::endl;
        std::cout << r.Camera.uNormal.x << ' ' << r.Camera.uNormal.y << ' ' << r.Camera.uNormal.z << std::endl;
        std::cout << r.Camera.longitude << ' ' << r.Camera.latitude<< std::endl;
        std::cout << r.Camera.fov << std::endl;
        window.display();
    }
}