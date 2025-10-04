#include "../vec_functions.h"

#include "Object.h"

//OBJECT
Object::~Object(){};

const vec3& Object::getPosition() const{
    return position;
}

void Object::setPosition(vec3 pos){
    position = pos;
}

Material* Object::getMaterial(){
    return material;
}

void Object::setMaterial(){
    Material defaultMaterial;
    material = &(defaultMaterial);
}

void Object::setMaterial(Material* mat){
    material = mat;
}




//SPHERE
Sphere::~Sphere(){};
Sphere::Sphere(){};
Sphere::Sphere(vec3 pos, float r, Material* mat){
    setMaterial(mat);
    this->setPosition(pos);
    R = r;
}

float Sphere::SDF(vec3 point){
    return length(point - getPosition()) - R;
}

vec3 Sphere::getNorm(vec3 point){
    return normalize(point - getPosition());
}




//INTERSECTION
Intersection::~Intersection(){};
Intersection::Intersection(){};
Intersection::Intersection(std::unique_ptr<Object>& obj1_, std::unique_ptr<Object>& obj2_, Material* mat){
    obj1 = obj1_.get();
    obj2 = obj2_.get();
    setMaterial(mat);
};

float Intersection::SDF(vec3 point){
    return std::max(obj1->SDF(point), obj2->SDF(point));
}

vec3 Intersection::getNorm(vec3 point){
    if(obj1->SDF(point)>obj2->SDF(point)){
        return obj1->getNorm(point);
    }
    return obj2->getNorm(point);
}




//PLANE
Plane::~Plane(){};
Plane::Plane(){};
Plane:: Plane(vec3 pos, vec3 n, Material* mat){
    this->setMaterial(mat);
    this->setPosition(pos);
    norm = normalize(n);
}

float Plane::SDF(vec3 point){
    return std::abs(dot(point, norm) - dot(norm, this->getPosition()));
}

vec3 Plane::getNorm(vec3 point){
    return norm;
}


Box::~Box(){};
Box::Box(){};
Box::Box(vec3 p, vec3 v, Material* mat){
    this->setMaterial(mat);
    this->setPosition(p);
    vertex = v;
};

float Box::SDF(vec3 point){
    vec3 tmp = abs(vertex - this->getPosition());
    vec3 q = abs(point - this->getPosition()) - abs(vertex - this->getPosition());
    return length(max(q, 0.0f)) + std::min(std::max(q[0], std::max(q[1], q[2])), 0.0f);
}

// vec3 Box::getNorm(vec3 point){
//     vec3 q = abs(point - this->getPosition()) - (vertex - this->getPosition());
//     vec3 q1 = normalize(max(q, 0.0f) + clamp(q, std::max(q[0], std::max(q[1], q[2])), 0.0f));
//     vec3 q2 = point - this->getPosition();
//     vec3 res = q1*vec3(-1.0f + 2*int(q2[0]>0), -1.0f + 2*int(q2[1]>0), -1.0f + 2*int(q2[2]>0));
//     return res;
// }

vec3 Box::getNorm(vec3 point){
    vec3 q = abs(point - this->getPosition()) - (vertex - this->getPosition());
    vec3 q1 = normalize(max(q, 0.0f) + clamp(q, std::max(q[0], std::max(q[1], q[2])), 0.0f));
    vec3 q2 = point - this->getPosition();
    vec3 res = q1*vec3(-1.0f + 2*int(q2[0]>0), -1.0f + 2*int(q2[1]>0), -1.0f + 2*int(q2[2]>0));
    return res;
}



//BOX