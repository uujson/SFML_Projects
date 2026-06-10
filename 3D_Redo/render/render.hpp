#ifndef RENDER_HPP
#define RENDER_HPP

#include "../math/math.hpp"
#include "../camera/camera.hpp"
#include "../userprocess/userprocess.hpp"
#include "../src/globals.hpp"

class render{
    public:
        camera Camera;
        mat4 project, view, model;
        render() : render(vec3(0,0,0)){}
        render(vec3 cameraPosition) : render(cameraPosition, 45.0){}
        render(vec3 cameraPosition, float fov) : render(cameraPosition, vec3(1,0,0)){}
        render(vec3 cameraPosition, vec3 cameraTarget) : render(cameraPosition, cameraTarget, 45.0){}
        render(vec3 cameraPosition, vec3 cameraTarget, float fov){
            Camera = camera(cameraPosition, cameraTarget, fov);
            Camera.setTarget(cameraTarget);
            updateFOV();
            update();
        }
        // getters
        float getFOV(){ return Camera.getFOV(); }
        vec3 getCameraPosition(){ return Camera.getPosition(); }
        vec3 getCameraTarget(){ return Camera.getTarget(); }
        vec3 getCameraNormal(){ return Camera.getNormal(); }
        // setters
        void setFOV(float fov){ Camera.setFOV(fov); updateFOV();}
        void setCameraPosition(vec3 v){ Camera.setPosition(v); update(); }
        void setCameraTarget(vec3 v){ Camera.setTarget(v); update(); }
        // util
        void updateFOV(){
            float fov = 1.0/tan(Camera.getFOV()*0.5*D2R);
            project = mat4(
                fov, 0, 0, 0,
                0, fov*(WINDOW_WIDTH/WINDOW_HEIGHT), 0, 0,
                0, 0, (500)/(499.9), -(50)/(499.9),
                0, 0, 1, 0
            );
            update(); 
        }
        void update(){
            model = modelMatrix(vec3(1,1,1),vec3(0,0,0),vec3(0,0,0));
            view = Camera.getViewMatrix();
        }
        render& operator+=(vec3 v){
            Camera += v;
            update();
            return *this;
        }
        render& operator+=(float angle[2]){
            Camera += angle;
            updateFOV();
            return *this;
        }
        void move(vec3 v){
            Camera += v;
            update();
        }
        void rotate(float angle[2]){
            Camera += angle;
            update();
        }
        void zoom(float f){
            Camera += f;
            updateFOV();
        }
        vec3 projectPoint(vec3 v){
            vec4 v4 = project*view*model*vec4(v);
            vec3 v3 = vec3(v4.x,v4.y,v4.z)/(4.0*v4.w);
            v3.x = v3.x*WINDOW_WIDTH + WINDOW_WIDTH2;
            v3.y = v3.y*WINDOW_HEIGHT + WINDOW_HEIGHT2;
            return v3;
        }
        vec3 operator()(vec3 v){
            return projectPoint(v);
        }
        void print(){
            system("clear");
            std::cout << Camera.position.x << ' ' << Camera.position.y << ' ' << Camera.position.z << std::endl;
            std::cout << Camera.lookingAt.x << ' ' << Camera.lookingAt.y << ' ' << Camera.lookingAt.z << std::endl;
            std::cout << Camera.targetNormal.x << ' ' << Camera.targetNormal.y << ' ' << Camera.targetNormal.z << std::endl;
            std::cout << Camera.rightNormal.x << ' ' << Camera.rightNormal.y << ' ' << Camera.rightNormal.z << std::endl;
            std::cout << Camera.upNormal.x << ' ' << Camera.upNormal.y << ' ' << Camera.upNormal.z << std::endl;
            std::cout << Camera.longitude << ' ' << Camera.latitude << std::endl;
            std::cout << Camera.fov << std::endl;
        }
};

#endif