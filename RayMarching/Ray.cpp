#include <iostream>

#include "../vec_functions.h"

#include "Ray.h"
#include "Scene.h"
#include "Object.h"




Ray::~Ray(){};
Ray::Ray(){};

Ray::Ray(const Scene& scene, vec3 x, vec3 v, int n){
    position = x;
    direction = normalize(v);
    numOfStep = n;

    isOutside = true;
    minDist = 5000;
    nearestObject;

    for(auto& object: scene.getObjects()){
        const auto d = object->SDF(position);
        if((minDist > std::abs(d)) /*&& (d>0 || std::abs(d)<kMinDistance)*/){
            minDist = std::abs(d);
            nearestObject = object.get();

            if(d<0){
                isOutside = false;
            }
        }
    }
}

bool Ray::getIsOutside(){
    return isOutside;
}

RGB Ray::locateObject(const Scene& scene){
    if(minDist < kMinDistance){return RGB(255, 255, 255);}
        
    if(numOfStep > kMaxStep){return RGB(0, 0, 0);}

    return Ray(scene, position + minDist*direction, direction, numOfStep+1).locateObject(scene);
}

int Ray::isSolidObjectOnDistance(const Scene& scene, float dist){
    if((minDist > dist) || (numOfStep > kMaxStep)){return 0;}

    if(minDist < kMinDistance){return 1;}
    
    return Ray(scene, position + minDist*direction, direction, numOfStep+1).isSolidObjectOnDistance(scene, dist - minDist);
}

RGB Ray::lightThroughObjects(const Scene& scene, float dist){
    RGB resColor;
    
    return resColor;
}

RGB Ray::colorVisible(const Scene& scene){

    if(numOfStep>kMaxStep){
        if(!scene.getSkyBox()){
            return RGB{0,0,0};
        }
        float theta = std::acos(direction[2]/std::sqrt(direction[0]*direction[0] + direction[1]*direction[1] + direction[2]*direction[2]));
        return skyBlur(510*theta/3.141592653589f);
    }


    if(minDist < kMinDistance){

        return nearestObject->getMaterial()->color(scene, position, direction, nearestObject->getNorm(position), numOfStep, isOutside);

    }
    

    return Ray(scene, position + minDist*direction, direction, numOfStep+1).colorVisible(scene);

}