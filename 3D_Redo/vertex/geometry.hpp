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
        vec3 midpoint;
        sf::Color color;
        sf::VertexArray vertices;
        bool canDraw;
        tri() : tri({0,1,0},{0,0,0},{1,0,0}){}
        tri(vec3 p0, vec3 p1, vec3 p2){
            points[0] = p0;
            points[1] = p1;
            points[2] = p2;
            midpoint = (points[0]+points[1]+points[2])/3.0;
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
            midpoint = (points[0]+points[1]+points[2])/3.0;
            normal = normalize(cross(points[0]-points[1], points[2]-points[1]));
            return *this;
        }
        void operator()(render r){
            if ((normal*(midpoint - r.getCameraPosition()) >= 0) || (normal*r.getCameraNormal() >= 0)){
                canDraw = false;
                return;
            }
            canDraw = true;
            vec3 temp[3];
            for (int i = 0; i < 3; i++){
                temp[i] = r(points[i]);
                vertices[i].position = {temp[i].x, temp[i].y};
            }
        }
        void updateColor(){ for (int i = 0; i < 3; i++){ vertices[i].color = color; } }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override{
            if (canDraw){ target.draw(vertices); }
        }
};

class quad : public sf::Drawable{
    public:
        vec3 normal;
        vec3 points[4];
        vec3 midpoint;
        sf::Color color;
        sf::VertexArray vertices;
        bool canDraw;
        quad() : quad({0,1,0},{0,0,0},{1,0,0},{1,1,0}){}
        quad(vec3 p0, vec3 p1, vec3 p2, vec3 p3){
            points[0] = p0;
            points[1] = p1;
            points[2] = p2;
            points[3] = p3;
            midpoint = (points[0] + points[1] + points[2] + points[3])/4;
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
            midpoint = (points[0] + points[1] + points[2] + points[3])/4;
            normal = normalize(cross(points[0]-points[1], points[3]-points[1]));
            return *this;
        }
        void operator()(render r){
            if ((normal*(r.getCameraPosition() - midpoint) >= 0)){
                canDraw = false;
                return;
            }
            else{ canDraw = true;}
            vec3 temp[4];
            for (int i = 0; i < 4; i++){
                temp[i] = r(points[i]);
            }
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
        bool canDraw;
        cube() : cube({0,0,0}, 1){}
        cube(vec3 translate) : cube(translate, 1){}
        cube(vec3 translate, float scale){
            faces.resize(6);
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
            faces[0] = quad(F[2],F[0],F[1],F[3]);
            faces[1] = quad(F[6],F[2],F[3],F[7]);
            faces[2] = quad(F[4],F[6],F[7],F[5]);
            faces[3] = quad(F[5],F[1],F[0],F[4]);
            faces[4] = quad(F[7],F[3],F[1],F[5]);
            faces[5] = quad(F[4],F[0],F[2],F[6]);
        }
        cube& operator=(sf::Color c){ for (int i = 0; i < 6; i++){ colors[i] = c; } updateColor(); return *this; }
        void setColor(int n, sf::Color c){ colors[n] = c; faces[n] = c; }
        void operator()(render r){
            for (int i = 0; i < 6; i++){ faces[i](r); }
        }
        void updateColor(){ for (int i = 0; i < 6; i++){ faces[i] = colors[i]; } }
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override{
            for (int i = 0; i < 6; i++){ target.draw(faces[i]); }
        }
};

#endif