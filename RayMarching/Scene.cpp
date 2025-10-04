#include "Scene.h"

Scene::~Scene(){};
Scene::Scene(){};

const Objects& Scene::getObjects() const{
    return objects;
}

void Scene::addObject(std::unique_ptr<Object>& newObject){
    objects.push_back(std::move(newObject));
}

const LightSources& Scene::getLights() const{
    return lights;
}

void Scene::addLight(std::unique_ptr<LightSource>& newLight){
    lights.push_back(std::move(newLight));
}

void Scene::skyBoxOn(){
    skyBox = true;
}

void Scene::skyBoxOff(){
    skyBox = false;
}

bool Scene::getSkyBox() const{
    return skyBox;
}