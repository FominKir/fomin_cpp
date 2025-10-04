#include "LightSource.h"

LightSource::~LightSource(){};
LightSource::LightSource(){};
LightSource::LightSource(float _brightness, RGB _color){
    brightness = _brightness;
    color = _color;
}

float LightSource::getBrightness(){
    return brightness;
}

RGB LightSource::getColor(){
    return color;
}

vec3 LightSource::lightDirection(vec3 point){
    return vec3(0);
}

vec3 LightSource::lightRayPosition(vec3 point, vec3 norm){
    return vec3(0);
}

PointLightSource::~PointLightSource(){};

PointLightSource::PointLightSource(){};

PointLightSource::PointLightSource(vec3 pos, float br, RGB col) : LightSource::LightSource(br, col) {
    position = pos;
}

vec3 PointLightSource::lightDirection(vec3 point){
    return position - point;
}

vec3 PointLightSource::lightRayPosition(vec3 point, vec3 norm){
    return point + normalize(position - point);
}

GlobalLight::~GlobalLight(){};
GlobalLight::GlobalLight(){};
GlobalLight::GlobalLight(vec3 _direction, float _brightness, RGB _color) : LightSource::LightSource(_brightness, _color) {
    direction = _direction;
}

vec3 GlobalLight::lightDirection(vec3 point){
    return direction;
}

vec3 GlobalLight::lightRayPosition(vec3 point, vec3 norm){
    return point + norm;
}