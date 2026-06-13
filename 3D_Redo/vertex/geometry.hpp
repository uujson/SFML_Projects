#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "SFML/Graphics.hpp"
#include "../math/math.hpp"
#include "../render/render.hpp"
#include <cmath>
#include <vector>
#include <algorithm>
/*
     0-----1
    /|     |\    
   2-+-----+-3
   | 4-----5 |
   |/       \|
   6---------7
*/



const float GOLDEN_RATIO = (1 + sqrt(5))*0.5;

vec3 CUBE[8] = {
       {0,0,1},{1,0,1},
    {0,1,1},      {1,1,1},

       {0,0,0},{1,0,0},
    {0,1,0},      {1,1,0}
};

class tri : public sf::Drawable{
    public:
        vec3 normal;
        vec3 points[3];
        float zValue;
        sf::Color color;
        sf::VertexArray vertices;
        bool canDraw;
        tri() : tri({0,1,0},{0,0,0},{1,0,0}){}
        tri(vec3 p0, vec3 p1, vec3 p2){
            points[0] = p0;
            points[1] = p1;
            points[2] = p2;
            normal = normalize(cross(points[0]-points[1], points[2]-points[1]));
            color = sf::Color::White;
            vertices.resize(3);
            vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
            canDraw = false;
            updateColor();
        }
        tri& operator=(sf::Color c){
            color = c;
            updateColor();
            return *this;
        }
        tri& operator=(tri t){
            vertices = t.vertices;
            color = t.color;
            normal = t.normal;
            for (int i = 0; i < 3; i++){
                points[i] = t.points[i];
            }
            updateColor();
            return *this;
        }
        tri& operator*=(mat4 m){
            for (int i = 0; i < 3; i++){
                points[i] *= m;
            }
            normal = normalize(cross(points[0]-points[1], points[2]-points[1]));
            return *this;
        }
        tri& operator-=(vec3 translate){
            points[0] -= translate;
            points[1] -= translate;
            points[2] -= translate;
            normal = normalize(cross(points[0]-points[1], points[2]-points[1]));
            return *this;
        }
        tri& operator+=(vec3 translate){
            points[0] += translate;
            points[1] += translate;
            points[2] += translate;
            normal = normalize(cross(points[0]-points[1], points[2]-points[1]));
            return *this;
        }
        tri& operator*=(float scale){
            points[0] *= scale;
            points[1] *= scale;
            points[2] *= scale;
            normal = normalize(cross(points[0]-points[1], points[2]-points[1]));
            return *this;
        }
        void operator()(render r){
            vec3 temp[3];
            if ((normal*normalize(points[0] - r.getCameraPosition()) < 0)){
                zValue = 2;
                canDraw = false;
                vertices[0].position = {0,0};
                vertices[1].position = {0,0};
                vertices[2].position = {0,0};
                return;
            }
            for (int i = 0; i < 3; i++){
                temp[i] = r(points[i]);
                if (temp[i].z >= 1){
                    zValue = 2;
                    canDraw = false;
                    vertices[0].position = {0,0};
                    vertices[1].position = {0,0};
                    vertices[2].position = {0,0};
                    return;
                }
            }
            zValue = (temp[0].z + temp[1].z + temp[2].z + temp[3].z)*0.25;
            canDraw = true;
            for (int i = 0; i < 3; i++){
                vertices[i].position = {temp[i].x, temp[i].y};
            }
        }
        void updateColor(){ for (int i = 0; i < 3; i++){ vertices[i].color = color; } }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override{
            if (canDraw){ target.draw(vertices); }
        }
        bool operator<(const tri &o){
            return zValue <= o.zValue;
        }
};

class quad : public sf::Drawable{
    public:
        vec3 normal;
        vec3 points[4];
        float zValue;
        sf::Color color;
        sf::VertexArray vertices;
        bool canDraw;
        quad() : quad({0,1,0},{0,0,0},{1,0,0},{1,1,0}){}
        quad(vec3 p0, vec3 p1, vec3 p2, vec3 p3){
            points[0] = p0;
            points[1] = p1;
            points[2] = p2;
            points[3] = p3;
            normal = normalize(cross(points[0]-points[1], points[3]-points[1]));
            color = sf::Color::White;
            vertices.resize(6);
            vertices.setPrimitiveType(sf::PrimitiveType::Triangles);
            canDraw = false;
            updateColor();
        }
        quad& operator=(sf::Color c){
            color = c;
            updateColor();
            return *this;
        }
        quad& operator=(quad q){
            vertices = q.vertices;
            color = q.color;
            normal = q.normal;
            for (int i = 0; i < 4; i++){
                points[i] = q.points[i];
            }
            updateColor();
            return *this;
        }
        quad& operator*=(mat4 m){
            for (int i = 0; i < 4; i++){
                points[i] *= m;
            }
            normal = normalize(cross(points[0]-points[1], points[3]-points[1]));
            return *this;
        }
        void operator()(render r){
            vec3 temp[4];
            if ((normal*normalize(points[0] - r.getCameraPosition()) < 0)){
                zValue = 2;
                canDraw = false;
                vertices[0].position = {0,0};
                vertices[1].position = {0,0};
                vertices[2].position = {0,0};
                vertices[3].position = {0,0};
                vertices[4].position = {0,0};
                vertices[5].position = {0,0};
                return;
            }
            for (int i = 0; i < 4; i++){
                temp[i] = r(points[i]);
                if (temp[i].z >= 1.0){
                    zValue = 2;
                    canDraw = false;
                    vertices[0].position = {0,0};
                    vertices[1].position = {0,0};
                    vertices[2].position = {0,0};
                    vertices[3].position = {0,0};
                    vertices[4].position = {0,0};
                    vertices[5].position = {0,0};
                    return;
                }
            }
            zValue = (temp[0].z + temp[1].z + temp[2].z + temp[3].z)*0.25;
            canDraw = true;
            vertices[0].position = {temp[0].x, temp[0].y};
            vertices[1].position = {temp[1].x, temp[1].y};
            vertices[2].position = {temp[2].x, temp[2].y};
            vertices[3].position = {temp[2].x, temp[2].y};
            vertices[4].position = {temp[3].x, temp[3].y};
            vertices[5].position = {temp[0].x, temp[0].y};
        }
        void updateColor(){ for (int i = 0; i < 6; i++){ vertices[i].color = color; } }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override{
            if (canDraw){ target.draw(vertices); }
        }
        bool operator<(const quad &o){
            return zValue < o.zValue;
        }
};
/*
       {N,N,P},{P,N,P},
    {N,P,P},      {P,P,P},

       {N,N,N},{P,N,N},
    {N,P,N},      {P,P,N}
*/

class cube : public sf::Drawable{
    public:
        std::vector<quad> faces;
        sf::Color colors[6];
        vec3 position;
        cube() : cube({0,0,0}, 1){}
        cube(vec3 translate) : cube(translate, 1){}
        cube(vec3 translate, float scale){
            faces.reserve(6);
            float f = scale*0.5;
            float x = translate.x;
            float y = translate.y;
            float z = translate.z;
            float px,py,pz,
                nx,ny,nz;
            px = x+f; py = y+f; pz = z+f;
            nx = x-f; ny = y-f; nz = z-f;
            vec3 F[8] = {
                    /*0*/{nx,ny,pz},{px,ny,pz},/*1*/
                /*2*/{nx,py,pz},         {px,py,pz},/*3*/

                    /*4*/{nx,ny,nz},{px,ny,nz},/*5*/
                /*6*/{nx,py,nz},         {px,py,nz}/*7*/
            };
            faces.push_back(quad(F[2],F[0],F[1],F[3]));
            faces.push_back(quad(F[6],F[2],F[3],F[7]));
            faces.push_back(quad(F[4],F[6],F[7],F[5]));
            faces.push_back(quad(F[5],F[1],F[0],F[4]));
            faces.push_back(quad(F[7],F[3],F[1],F[5]));
            faces.push_back(quad(F[4],F[0],F[2],F[6]));
        }
        cube& operator=(sf::Color c){ for (int i = 0; i < 6; i++){ colors[i] = c; } updateColor(); return *this; }
        void setColor(int n, sf::Color c){ colors[n] = c; faces[n] = c; }
        void operator()(render r){
            for (int i = 0; i < 6; i++){ faces[i](r); }
            std::sort(faces.begin(), faces.end());
        }
        void updateColor(){ for (int i = 0; i < 6; i++){ faces[i] = colors[i]; } }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override{
            for (int i = 0; i < 6; i++){ target.draw(faces[i]); }
        }
};

/*




*/
const vec3 ICOSPHERE[12] = {
    normalize({0.5,0,GOLDEN_RATIO*0.5}),normalize({-0.5,0,GOLDEN_RATIO*0.5}),normalize({-0.5,0,-GOLDEN_RATIO*0.5}),normalize({0.5,0,-GOLDEN_RATIO*0.5}),
    normalize({0,0-GOLDEN_RATIO*0.5,-0.5}),normalize({0,-GOLDEN_RATIO*0.5,0.5}),normalize({0,GOLDEN_RATIO*0.5,0.5}),normalize({0,GOLDEN_RATIO*0.5,-0.5}),
    normalize({GOLDEN_RATIO*0.5,0.5,0}),normalize({GOLDEN_RATIO*0.5,-0.5,0}),normalize({-GOLDEN_RATIO*0.5,-0.5,0}),normalize({-GOLDEN_RATIO*0.5,0.5,0})
};

vec3 getMiddlePoint(vec3 a, vec3 b){
    return normalize(a+b);
}


class icosphere : public sf::Drawable{
    public:
        vec3 position;
        std::vector<tri> faces;
        int size;
        icosphere() : icosphere(1.0){}
        icosphere(float scale) : icosphere({0,0,0}, scale){}
        icosphere(vec3 translate, float scale){
            float f = scale*0.5;
            size = 20;
            position = translate;
            faces.push_back(tri(ICOSPHERE[0], ICOSPHERE[6], ICOSPHERE[1]));
            faces.push_back(tri(ICOSPHERE[0], ICOSPHERE[8], ICOSPHERE[6]));
            faces.push_back(tri(ICOSPHERE[0], ICOSPHERE[9], ICOSPHERE[8]));
            faces.push_back(tri(ICOSPHERE[0], ICOSPHERE[5], ICOSPHERE[9]));
            faces.push_back(tri(ICOSPHERE[0], ICOSPHERE[1], ICOSPHERE[5]));
            
            faces.push_back(tri(ICOSPHERE[1], ICOSPHERE[6], ICOSPHERE[11]));
            faces.push_back(tri(ICOSPHERE[6], ICOSPHERE[8], ICOSPHERE[7]));
            faces.push_back(tri(ICOSPHERE[8], ICOSPHERE[9], ICOSPHERE[3]));
            faces.push_back(tri(ICOSPHERE[9], ICOSPHERE[5], ICOSPHERE[4]));
            faces.push_back(tri(ICOSPHERE[5], ICOSPHERE[1], ICOSPHERE[10]));
            
            faces.push_back(tri(ICOSPHERE[2], ICOSPHERE[7], ICOSPHERE[3]));
            faces.push_back(tri(ICOSPHERE[2], ICOSPHERE[3], ICOSPHERE[4]));
            faces.push_back(tri(ICOSPHERE[2], ICOSPHERE[4], ICOSPHERE[10]));
            faces.push_back(tri(ICOSPHERE[2], ICOSPHERE[10], ICOSPHERE[11]));
            faces.push_back(tri(ICOSPHERE[2], ICOSPHERE[11], ICOSPHERE[7]));
            
            faces.push_back(tri(ICOSPHERE[3], ICOSPHERE[7], ICOSPHERE[8]));
            faces.push_back(tri(ICOSPHERE[7], ICOSPHERE[11], ICOSPHERE[6]));
            faces.push_back(tri(ICOSPHERE[11], ICOSPHERE[10], ICOSPHERE[1]));
            faces.push_back(tri(ICOSPHERE[10], ICOSPHERE[4], ICOSPHERE[5]));
            faces.push_back(tri(ICOSPHERE[4], ICOSPHERE[3], ICOSPHERE[9]));
            updateColor();
        }
        void subdivide(){
            std::vector<tri> newFaces;
            for (auto i : faces){
                vec3 a = getMiddlePoint(i.points[0], i.points[1]);
                vec3 b = getMiddlePoint(i.points[1], i.points[2]);
                vec3 c = getMiddlePoint(i.points[2], i.points[0]);
                newFaces.push_back(tri(i.points[0], a, c));
                newFaces.push_back(tri(i.points[1], b, a));
                newFaces.push_back(tri(i.points[2], c, b));
                newFaces.push_back(tri(a, b, c));
            }
            faces = newFaces;
            std::cout << faces.size() << std::endl;
            updateColor();
        }
        void updateColor(){
            float r,g,b;
            for (auto& i : faces){
                r = i.normal.x*122;
                g = i.normal.y*122;
                b = i.normal.z*122;
                if (r < 0){ r += 225; }
                if (g < 0){ g += 225; }
                if (b < 0){ b += 225; }
                i = sf::Color((int)r,(int)g,(int)b);
            }
        }
        // icosphere& operator=(icosphere s){}
        void operator()(render r){
            for (auto& i : faces){ i(r); }
            // std::sort(std::begin(faces), std::end(faces));
        }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override{
            for (const auto i : faces){ target.draw(i); }
        }
};



#endif