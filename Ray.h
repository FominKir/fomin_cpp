// #include <iostream>
// #include "vec.h"
// #include "bmp.h"
// #include "vec_functions.h"
// #include <vector>
// #include <memory>

// //shadertoy.com

// const float kMinDistance = 0.01f;
// const int kMaxStep = 100;

// class Scene;

// class Texture{
//     RGB rgb;

//     public:
//     ~Texture() = default;
//     Texture(){
//         rgb = RGB(200, 200, 200);
//     }
//     Texture(const RGB& color){
//         rgb.r = color.r;
//         rgb.g = color.g;
//         rgb.b = color.b;
//     }
    
//     RGB getColor(){
//         return rgb;
//     }
// };

// class Material{

//     public:
//     Texture texture;

//     float reflectivity = 0;
//     float transparency = 0;
//     float refraction = 0;

//     // public:

//     ~Material() = default;
//     // Material() = default;
//     Material(){
//         texture = Texture();
//         reflectivity = 0;
//         transparency = 0;
//         refraction = 0;
//     };

//     Material(float refl, float tr, float refract){
//         refraction = refract;
//         transparency = std::max(0.0f, std::min(1.0f, tr));
//         reflectivity = std::max(0.0f, std::min(1.0f, refl));
//     }

    
//     RGB color(const Scene& scene, vec3 position, vec3 direction, vec3 norm, int numOfStep);
    
//     // float getReflectivity(){
//     //     return reflectivity;
//     // }

//     // float getTransparency(){
//     //     return transparency;
//     // }

//     // float getRefraction(){
//     //     return refraction;
//     // }

//     // Texture getTexture(){
//     //     return texture;
//     // }
// };

// class Object{

//     vec3 position;

//     Material* material;

//     public:


//     virtual float SDF(vec3 point) = 0;
//     virtual vec3 getNorm(vec3 point) = 0;

//     virtual ~Object() = default;

//     const vec3& getPosition() const{
//         return position;
//     }

//     void setPosition(vec3 pos){
//         position = pos;
//     }

//     Material* getMaterial(){
//         return material;
//     }

//     void setMaterial(Material* mat){
//         material = mat;
//     }

//     void setMaterial(){
//         material = &(Material());
//     }

// };

// class LightSource{
    
//     vec3 position;

//     float brightness;

//     RGB color;

//     public:

//     LightSource(vec3 pos, float br, RGB col){
//         position = pos;
//         brightness = br;
//         color = col;
//     }

//     float getBrightness(){
//         return brightness;
//     }

//     vec3 getPosition(){
//         return position;
//     }

//     RGB getColor(){
//         return color;
//     }

// };

// class Sphere: public Object{

//     float R;
    
//     public:
//     Sphere(vec3 pos, float r){
//         setMaterial();
//         this->setPosition(pos);
//         R = r;
//     }

//     float SDF(vec3 point){
//         return length(point - getPosition()) - R;
//     }

//     vec3 getNorm(vec3 point){
//         return normalize(point - getPosition());
//     }

// };

// using Objects = std::vector<std::unique_ptr<Object>>;
// using LightSources = std::vector<std::unique_ptr<LightSource>>;

// class Scene{
//     public:

//     Objects objects;
//     LightSources lights;
    
//     ~Scene() = default;
//     Scene() = default;
    
//     const Objects& getObjects() const {
//         return objects;}

//     void addObject(std::unique_ptr<Object>& newObject){
//         objects.push_back(std::move(newObject));
//     }

//     const LightSources& getLights() const {
//         return lights;}

//     void addLight(std::unique_ptr<LightSource>& newLight){
//         lights.push_back(std::move(newLight));
//     }



// };

// struct Intersection {


//      bool IsContact();
// };

// class Ray{

//     int numOfStep;

//     vec3 position;
//     vec3 direction;

//     float minDist;
//     Object* nearestObject;



//     public:

//     ~Ray() = default;
//     Ray() = default;

//     Ray(const Scene& scene, vec3 x, vec3 v, int n){
//         position = x;
//         direction = normalize(v);
//         numOfStep = n;

//         minDist = 5000;
//         nearestObject;

//         for(auto& object: scene.getObjects()){
//             const auto d = object->SDF(position);
//             if(minDist > d){
//                 minDist = d;
//                 nearestObject = object.get();
//             }
//         }
//     }

    

//     bool isOutside(){
//         if(minDist > 0.0f){return true;}
//         return false;
//     }

//     RGB locateObject(const Scene& scene){
        
//         if(minDist < kMinDistance){return RGB(255, 255, 255);}
        
//         if(numOfStep > kMaxStep){return RGB(0, 0, 0);}

//         return Ray(scene, position + minDist*direction, direction, numOfStep+1).locateObject(scene);

//     }

//     int isObjectOnDistance(const Scene& scene, float dist){
        
//         if((minDist > dist) || (numOfStep > kMaxStep)){return 0;}

//         if(minDist < kMinDistance){return 1;}
        
//         return Ray(scene, position + minDist*direction, direction, numOfStep+1).isObjectOnDistance(scene, dist - minDist);

//     }

//     RGB colorVisible(const Scene& scene){

//         if(minDist < kMinDistance){
//             // vec3 norm = nearestObject->getNorm(position);
//             // int numOfLigthSources = scene.getLights().size();
            
//             // RGB color(0, 0, 0);
//             // for(auto& light: scene.getLights()){

//             //     Ray rayToLight(scene, position + 1.0f * normalize(light->getPosition() - position),
//             //         light->getPosition() - position, 0);

//             //     if(rayToLight.isObjectOnDistance(scene, length(light->getPosition() - position)) == 0){
//             //         color = sumRGB(color, light->getColor() * light->getBrightness()
//             //             * dot(norm, normalize(light->getPosition() - position))
//             //         );
//             //     }
//             // }

//             return nearestObject->getMaterial()->color(scene, position, direction, nearestObject->getNorm(position), numOfStep);
            
//         }
        
//         if(numOfStep>500){return RGB(0, 0, 0);}

//         return Ray(scene, position + minDist*direction, direction, numOfStep+1).colorVisible(scene);

//     }

// };

// class Camera{

//     vec3 position;

//     vec3 viewVec;
//     vec3 cameraUp;

//     int wResolution;
//     int hResolution;

//     float pixInMillimeter;

//     float screenDist;

//     public:

//     ~Camera() = default;
//     Camera() = default;
//     Camera(const vec3& pos, const vec3& view, vec3 up, int w, int h, float pixInMm, float FOV){
//         position = pos;
//         viewVec = normalize(view);
//         cameraUp = normalize(up - view*dot(up,view));
//         wResolution = w;
//         hResolution = h;
//         pixInMillimeter = pixInMm;
//         screenDist = 1/std::tan(FOV*3.14159265/360)/pixInMm*float(w)/2.0;
//     }
    
//     void bmpOutput(const Scene& scene){
//         std::ofstream file("C:\\Users\\Raywud\\Documents\\cpp_prog\\fomin_cpp\\CameraView.bmp", std::ios::binary);
//         BMP bmp(wResolution, hResolution);
//         vec3 startPixel = position + screenDist*viewVec - cameraUp/pixInMillimeter*(float(hResolution)/2.0f - 0.5f)
//             - cross(viewVec, cameraUp)/pixInMillimeter*(float(wResolution)/2.0f - 0.5f);
//         for(int x = 0; x < wResolution; x++){
//             for(int y = 0; y < hResolution; y++){
//                 Ray ray(scene, startPixel + x/pixInMillimeter*cross(viewVec, cameraUp) + y/pixInMillimeter*cameraUp,
//                 startPixel + x/pixInMillimeter*cross(viewVec, cameraUp) + y/pixInMillimeter*cameraUp - position, 0);
//                 bmp.SetPixel(x, y, ray.colorVisible(scene));
//             }
//         }
//         bmp.write(file);
//     }

//     void bmpOutputLocate(const Scene& scene){
//         std::ofstream file("C:\\Users\\Raywud\\Documents\\cpp_prog\\fomin_cpp\\CameraView.bmp", std::ios::binary);
//         BMP bmp(wResolution, hResolution);
//         vec3 startPixel = position + screenDist*viewVec - cameraUp/pixInMillimeter*(float(hResolution)/2.0f - 0.5f)
//             - cross(viewVec, cameraUp)/pixInMillimeter*(float(wResolution)/2.0f - 0.5f);
//         for(int x = 0; x < wResolution; x++){
//             for(int y = 0; y < hResolution; y++){
//                 Ray ray(scene, startPixel + x/pixInMillimeter*cross(viewVec, cameraUp) + y/pixInMillimeter*cameraUp,
//                 startPixel + x/pixInMillimeter*cross(viewVec, cameraUp) + y/pixInMillimeter*cameraUp - position, 0);
//                 int located = ray.isObjectOnDistance(scene, 100000);
//                 RGB color(255*located, 255*located, 255*located);
//                 bmp.SetPixel(x, y, color);
//             }
//         }
//         bmp.write(file);
//     }
// };

// RGB Material::color(const Scene& scene, vec3 position, vec3 direction, vec3 norm, int numOfStep){
//     RGB colRes(0,0,0);

//     vec3 reflectDirection = reflect(direction, norm);
//     Ray reflect = Ray(scene, position + normalize(reflectDirection), reflectDirection, numOfStep);
//     RGB reflectColor;
//     if(reflect.isOutside() && (reflectivity > 0)){
//         reflectColor = reflectivity * underLight(texture.getColor(), reflect.colorVisible(scene));
//     }
//     else{
//         reflectColor = RGB(0, 0, 0);
//     }

//     vec3 refractDirection = refract(direction, norm, refraction);
//     Ray refrac = Ray(scene, position + normalize(refractDirection), refractDirection, numOfStep);
//     RGB refracColor;
//     if(transparency > 0){
//         refracColor = transparency * underLight(texture.getColor(), refrac.colorVisible(scene));
//     }
//     else{
//         refracColor = RGB(0, 0, 0);d
//     }

//     RGB colorOfObject;
//     for(auto& light: scene.getLights()){

//         Ray rayToLight(scene, position + 1.0f * normalize(light->getPosition() - position),
//             light->getPosition() - position, 0);

//         if(rayToLight.isObjectOnDistance(scene, length(light->getPosition() - position)) == 0){
//             colorOfObject = sumRGB(colorOfObject, light->getColor() * light->getBrightness()
//                 * dot(norm, normalize(light->getPosition() - position))
//             );
//         }
//     }

//     colRes = sumRGB(colRes, reflectColor);
//     colRes = sumRGB(colRes, refracColor);
//     colRes = sumRGB(colRes, texture.getColor());

//     return colRes;
// }