#pragma once
// #include "../vec.h"
#include "../bmp.h"

#include "Object.h"

const float kMinDistance = 0.001f;
const int kMaxStep = 300;
const float kMaxDistance = 1500.0f;

class Ray{

    int numOfStep;

    vec3 position;
    vec3 direction;

    bool isOutside;
    float minDist;
    Object* nearestObject;


    public:

    ~Ray();
    Ray();

    Ray(const Scene& scene, vec3 x, vec3 v, int n);

    bool getIsOutside();

    RGB locateObject(const Scene& scene);

    int isSolidObjectOnDistance(const Scene& scene, float dist);

    RGB lightThroughObjects(const Scene& scene, float dist);

    RGB colorVisible(const Scene& scene);

};