#pragma once
#include "../vec.h"
#include "../vec_functions.h"
#include "../bmp.h"
#include "Ray.h"

class LightSource{
    
    float brightness;
    RGB color;

    public:

    ~LightSource();
    LightSource();
    LightSource(float _brightness, RGB _color);
    
    float getBrightness();
    RGB getColor();

    virtual vec3 lightDirection(vec3 point);
    virtual vec3 lightRayPosition(vec3 point, vec3 norm);

};

using LightSources = std::vector<std::unique_ptr<LightSource>>;

class PointLightSource: public LightSource{
    vec3 position;

    public:

    ~PointLightSource();
    PointLightSource();
    PointLightSource(vec3 pos, float br, RGB col);

    vec3 getPosition();
    vec3 lightDirection(vec3 point);
    vec3 lightRayPosition(vec3 point, vec3 norm);
};

class GlobalLight: public LightSource{
    vec3 direction;

    public:

    ~GlobalLight();
    GlobalLight();
    GlobalLight(vec3 _direction, float _brightness, RGB _color);

    vec3 lightDirection(vec3 point);
    vec3 lightRayPosition(vec3 point, vec3 norm);
};