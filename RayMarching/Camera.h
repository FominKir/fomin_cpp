#pragma once
#include "../vec.h"

#include "Scene.h"

const int numOfThreads = 18;

class Camera{

    vec3 position;

    vec3 viewVec;
    vec3 cameraUp;

    int wResolution;
    int hResolution;

    float pixInMillimeter;

    float screenDist;

    public:

    ~Camera();
    Camera();
    Camera(const vec3& pos, const vec3& view, vec3 up, int w, int h, float pixInMm, float FOV);
    
    void bmpOutput(const Scene& scene);

    void bmpOutputLocate(const Scene& scene);

    void bmpOutputLimited(const Scene& scene, int x_left, int x_right, vec3 start, BMP& bmp);
};