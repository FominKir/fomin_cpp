#include <iostream>
#include <thread>
#include <vector>

#include "../vec_functions.h"

#include "Camera.h"
#include "Ray.h"

Camera::~Camera() = default;
Camera::Camera() = default;
Camera::Camera(const vec3& pos, const vec3& view, vec3 up, int w, int h, float pixInMm, float FOV){
    position = pos;
    viewVec = normalize(view);
    cameraUp = normalize(up - view*dot(up,view));
    wResolution = w;
    hResolution = h;
    pixInMillimeter = pixInMm;
    screenDist = 1/std::tan(FOV*3.14159265/360)/pixInMm*float(w)/2.0;
}

void Camera::bmpOutputLimited(const Scene& scene, int x_left, int x_right, vec3 start, BMP& bmp){
    for(int x = x_left; x < x_right && x < wResolution; x++){
        for(int y = 0; y < hResolution; y++){
            Ray ray(scene, start + y/pixInMillimeter*cameraUp,
            start + x/pixInMillimeter*cross(viewVec, cameraUp) + y/pixInMillimeter*cameraUp - position, 0);
            bmp.SetPixel(x, y, ray.colorVisible(scene));
        }
    }
}

void Camera::bmpOutput(const Scene& scene){
    std::ofstream file("C:\\Users\\Raywud\\Documents\\cpp_prog\\fomin_cpp\\CameraView.bmp", std::ios::binary);
    BMP bmp(wResolution, hResolution);
    vec3 startPixel = position + screenDist*viewVec - cameraUp/pixInMillimeter*(float(hResolution)/2.0f - 0.5f)/**/
        - cross(viewVec, cameraUp)/pixInMillimeter*(float(wResolution)/2.0f - 0.5f);

    std::vector<std::unique_ptr<std::thread>> threads;

    int pixInCol = (wResolution + numOfThreads - 1)/numOfThreads;

    for(int i = 0; i < numOfThreads; i++){
        auto th = std::make_unique<std::thread>(&Camera::bmpOutputLimited, this, std::ref(scene), i*pixInCol, (i+1)*pixInCol, startPixel, std::ref(bmp));
        threads.push_back(std::move(th));
    }

    for(auto& thread: threads){
        thread->join();
    }




    // std::thread th(&Camera::bmpOutputLimited, scene, 0, wResolution, startPixel, bmp);
    // th.join();




    // Camera::bmpOutputLimited(scene, 0, wResolution, startPixel, bmp);

    bmp.write(file);
}

void Camera::bmpOutputLocate(const Scene& scene){
    std::ofstream file("C:\\Users\\Raywud\\Documents\\cpp_prog\\fomin_cpp\\CameraView.bmp", std::ios::binary);
    BMP bmp(wResolution, hResolution);
    vec3 startPixel = position + screenDist*viewVec - cameraUp/pixInMillimeter*(float(hResolution)/2.0f - 0.5f)
        - cross(viewVec, cameraUp)/pixInMillimeter*(float(wResolution)/2.0f - 0.5f);
    for(int x = 0; x < wResolution; x++){
        for(int y = 0; y < hResolution; y++){
            Ray ray(scene, startPixel + x/pixInMillimeter*cross(viewVec, cameraUp) + y/pixInMillimeter*cameraUp,
            startPixel + x/pixInMillimeter*cross(viewVec, cameraUp) + y/pixInMillimeter*cameraUp - position, 0);
            int located = ray.isSolidObjectOnDistance(scene, 100000);
            RGB color(255*located, 255*located, 255*located);
            bmp.SetPixel(x, y, color);
        }
    }
    bmp.write(file);
}
