#pragma once

#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "../../include/algebra/linalg.hpp"
#include "../../include/settings/settings.hpp"
#include "../../include/utils/utils.hpp"

enum MULTISWITCH{BACK = -1, OFF = 0, FORWARD = 1};

class camera{
    public:
        vec3 position, normal, rightNormal, upNormal, lookingAt;
        double fov;
        camera() : camera(0.0,0.0,0.0){}
        camera(const double &x, const double &y, const double &z) : camera(vec3(x,y,z),vec3(0.0,0.0,0.0), 45.0){}
        camera(vec3 pos, double fovDegrees) : camera(pos, vec3(0,0,0), fovDegrees){}
        camera(vec3 pos, vec3 target, double FOV){
            position = pos;
            lookingAt = target;
            setFOV(FOV);
            update();
        }
        void setPosition(vec3 pos){
            position = pos;
            update();
        }
        void lookAt(vec3 target){
            lookingAt = target;
            update();
        }
        void setFOV(double FOV){ fov = FOV; }
        void update(){
            normal = normalize(position-lookingAt);
            rightNormal = normalize(cross(vec3(0,0,1),normal));
            upNormal = normalize(cross(normal, rightNormal));
        }
        vec3 worldTranslate(){ return -position; }
        mat4 viewMatrix(){
            update();
            vec3 temp = worldTranslate();
            return mat4(
                vec4(rightNormal, rightNormal*temp),
                vec4(upNormal, upNormal*temp),
                vec4(normal, normal*temp),
                vec4(0,0,0,1)
            );
        }
};

class render{
    private:
        camera Camera;
        mat4 projection, view, model;
    public:
        render() : render(vec3(0,0,0)){}
        render(vec3 cameraPosition) : render(cameraPosition, 45.0){}
        render(vec3 cameraPosition, double fov) : render(cameraPosition, vec3(0,0,0), fov){}
        render(vec3 cameraPosition, vec3 cameraTarget, double fov){
            Camera = camera(cameraPosition, cameraTarget, fov);
            updateFOV();
            update();
        }
        void setFOV(double FOV){
            Camera.setFOV(FOV);
            updateFOV();
        }
        void setCameraPosition(vec3 cameraPosition){
            Camera.setPosition(cameraPosition);
            update();
        }
        void setCameraTarget(vec3 cameraTarget){
            Camera.lookAt(cameraTarget);
            update();
        }
        void updateFOV(){ projection = projectionMatrix(Camera.fov, WINDOW_WIDTH/WINDOW_HEIGHT, 0.1, 100.0); }
        void update(){
            model = modelMatrix(vec3(1.0,1.0,1.0), vec3(0.0,0.0,0.0), Camera.worldTranslate());
            view = Camera.viewMatrix();
        }
        vec3 project(vec3 v){
            vec4 v4 = projection*view*model*vec4(v);
            vec3 v3 = vec3(v4.x,v4.y,v4.z)/(4.0*v4.w);
            v3.x = v3.x * WINDOW_WIDTH + WINDOW_WIDTH_HALF;
            v3.y = v3.y * WINDOW_HEIGHT + WINDOW_HEIGHT_HALF;
            return v3;
        }
        vec3 getCameraNormal(){ return Camera.normal; }
        vec3 getCameraPosition(){ return Camera.position; }
        vec3 getCameraTarget(){ return Camera.lookingAt; }
};

#endif