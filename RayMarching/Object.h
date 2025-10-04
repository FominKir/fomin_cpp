#pragma once
#include "../vec.h"

#include "Material.h"


class Object{

    vec3 position;

    Material* material{};

    public:


    virtual float SDF(vec3 point) = 0;
    virtual vec3 getNorm(vec3 point) = 0;

    virtual ~Object();

    const vec3& getPosition() const;
    void setPosition(vec3 pos);

    Material* getMaterial();
    void setMaterial();
    void setMaterial(Material* mat);

};

using Objects = std::vector<std::unique_ptr<Object>>;

class Sphere: public Object{

    float R;
    
    public:

    ~Sphere();
    Sphere();
    Sphere(vec3 pos, float r, Material* mat);

    float SDF(vec3 point);

    vec3 getNorm(vec3 point);

};

class Plane: public Object{

    vec3 norm;

    public:

    ~Plane();
    Plane();
    Plane(vec3 p, vec3 n, Material* mat);

    float SDF(vec3 point);

    vec3 getNorm(vec3 point);
};

class Intersection: public Object{

    Object* obj1;
    Object* obj2;

    public:
    ~Intersection();
    Intersection();
    Intersection(std::unique_ptr<Object>& obj1, std::unique_ptr<Object>& obj2, Material* mat);

    float SDF(vec3 point);

    vec3 getNorm(vec3 point);
};

class Box: public Object{

    vec3 vertex;

    public:
    ~Box();
    Box();
    Box(vec3 p, vec3 v, Material* mat);

    float SDF(vec3 point);

    vec3 getNorm(vec3 point);

};