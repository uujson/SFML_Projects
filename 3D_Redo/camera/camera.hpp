#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "../math/math.hpp"
#include <cmath>

const vec3 UP = vec3(0,0,1);
const float D2R = M_PI/180.0;
const float R2D = 1.0/D2R;

class camera{
    public:
        vec3 position, lookingAt, targetNormal, upNormal, rightNormal;
        float longitude, latitude;
        float fov;
        camera() : camera(vec3(0,0,0), vec3(1,0,0), 45.0){}
        camera(vec3 pos, vec3 target, float FOV){
            position = pos;
            fov = FOV;
            lookingAt = target;
            latitude = asin(target.z)*R2D/2;
            longitude = acos(target.z)*R2D;
            checkAngle();
            checkFOV();
        }
        // getters
        vec3 getPosition(){ return position; }
        vec3 getTarget(){ return lookingAt; }
        vec3 getNormal(){ return targetNormal; }
        vec3 getRightNormal(){ return rightNormal; }
        vec3 getUpNormal(){ return upNormal; }
        float getFOV(){ return fov; }

        mat4 getViewMatrix(){
            vec3 temp = -position;
            return mat4(
                vec4(rightNormal.x, rightNormal.y, rightNormal.z,(rightNormal*temp)),
                vec4(upNormal.x, upNormal.y, upNormal.z,(upNormal*temp)),
                vec4(targetNormal.x, targetNormal.y, targetNormal.z,(targetNormal*temp)),
                vec4(0,0,0,1)
            );
        }
        // setters
        void setPosition(vec3 v){
            position = v;
            update();
        }
        void setTarget(vec3 v){
            targetNormal = normalize(v - position);
            latitude = asin(targetNormal.z)*R2D;
            longitude = acos(targetNormal.z)*R2D;
            checkAngle();
        }
        void setFOV(float FOV){
            fov = FOV;
            checkFOV();
        }
        // operators
        camera& operator+=(vec3 v){
            if (v.x == 0 & v.y == 0 & v.z == 0){ return *this; }
            if (v.x != 0 || v.y != 0){
                vec3 temp = normalize(vec3(v.x, v.y, 0))*0.01;
                position += vec3(temp.x*rightNormal.y + temp.y*rightNormal.x, -temp.x*rightNormal.x + temp.y*rightNormal.y, 0);
            }
            position += vec3(0,0,v.z*0.01);
            update();
            return *this;
        }
        camera& operator+=(float f[2]){
            longitude += f[0];
            latitude += f[1];
            checkAngle();
            return *this;
        }
        camera& operator+=(float f){
            fov += f;
            checkFOV();
            return *this;
        }
        camera& operator-=(float f){
            fov -= f;
            checkFOV();
            return *this;
        }
        // util
        void checkFOV(){
            if (fov > 90.0){ fov = 90.0; }
            else if (fov < 15.0){ fov = 15.0; }
            update();
        }
        void checkAngle(){
            if (longitude > 360.0){ longitude -= 360.0; }
            else if ( longitude < 0.0){ longitude += 360; }
            if (latitude > 85.0){ latitude = 85.0; }
            else if (latitude < -85.0){ latitude = -85.0; }
            update();
        }
        void update(){
            float longtemp = longitude*D2R;
            float lattemp = latitude*D2R;
            targetNormal = vec3(cos(lattemp)*cos(longtemp), cos(lattemp)*sin(longtemp),sin(lattemp));
            lookingAt = position - targetNormal;
            rightNormal = normalize(cross(targetNormal, UP));
            upNormal = normalize(cross(targetNormal, rightNormal));
        }
};

#endif