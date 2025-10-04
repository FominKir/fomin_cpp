#pragma once
#include <iostream>

#include "Object.h"
#include "LightSource.h"

class Scene{

    Objects objects;
    LightSources lights;

    bool skyBox = false;

    public:
    
    ~Scene();
    Scene();
    
    const Objects& getObjects() const;

    void addObject(std::unique_ptr<Object>& newObject);

    const LightSources& getLights() const;

    void addLight(std::unique_ptr<LightSource>& newLight);

    void skyBoxOn();

    void skyBoxOff();

    bool getSkyBox() const;
};