#include "../vec_functions.h"

#include "Material.h"
#include "Scene.h"
#include "Ray.h"




Material::~Material(){};
Material::Material(){};
Material::Material(Texture& tex){
    texture = tex;
    reflectivity = 0;
    refraction = 0;
    transparency = 0;
};
Material::Material(float refl, float tr, float refract, Texture& tex){
    texture = tex;
    refraction = refract;
    transparency = std::max(0.0f, std::min(1.0f, tr));
    reflectivity = std::max(0.0f, std::min(1.0f, refl));
}

RGB Material::color(const Scene& scene, vec3 position, vec3 direction, vec3 norm, int numOfStep, bool isOutside){
    RGB resColor(0,0,0);

    /*vec3 reflectDirection = reflect(direction, norm);
    Ray reflect = Ray(scene, position + normalize(reflectDirection), reflectDirection, numOfStep + 1);
    RGB reflectColor;
    if(reflect.isOutside() && (reflectivity > 0)){
        reflectColor = reflectivity * cutRGB(texture.getColor(), reflect.colorVisible(scene));
    }
    else{
        reflectColor = RGB(0, 0, 0);
    }*/

    vec3 refractDirection = refract(direction, (-1.0f+2.0f*int(isOutside))*norm, std::pow(refraction, (-1.0f+2.0f*int(isOutside))));
    if(refractDirection[0]==0 && refractDirection[1]==0 && refractDirection[2]==0){
        refractDirection = reflect(direction, (-1.0f+2.0f*int(isOutside))*norm);
    }
    
    //std::cout << std::pow(2.0f, (-1.0f+2.0f*int(isOutside))) << std::endl << std::endl;
    Ray refrac = Ray(scene, position + normalize(refractDirection), refractDirection, numOfStep + 1);
    RGB refracColor;
    if(transparency > 0){
        refracColor = transparency * cutRGB(texture.getColor(), refrac.colorVisible(scene));
    }
    else{
        refracColor = RGB(0, 0, 0);
    }




    RGB colorOfObject = RGB{0, 0, 0};

    // if(Ray(scene, position + norm, scene.getGlobalLightDirection(), numOfStep+1).isSolidObjectOnDistance(scene, kMaxDistance) == 0){
    //     colorOfObject = sumRGB(colorOfObject,(1.0f - transparency)*cutRGB(texture.getColor(), scene.getGlobalLightBrightness() * scene.getGlobalLightColor() * dot(norm, normalize(scene.getGlobalLightDirection()))));
    // }

    for(auto& light: scene.getLights()){

        Ray rayToLight(scene, light->lightRayPosition(position, norm), light->lightDirection(position), 0);

        if(rayToLight.isSolidObjectOnDistance(scene, length(light->lightDirection(position))) == 0){
            colorOfObject = sumRGB(colorOfObject, (1.0f - transparency)*cutRGB(texture.getColor(), light->getColor() * light->getBrightness()
                * dot(norm, normalize(light->lightDirection(position))))
            );
        }
    }

   // resColor = sumRGB(resColor, reflectColor);
    resColor = sumRGB(resColor, refracColor);
    resColor = sumRGB(resColor, colorOfObject);

    return resColor;
}