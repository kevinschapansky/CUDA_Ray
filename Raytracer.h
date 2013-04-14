#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <vector>
#include <string>
#include <cuda.h>
#include <stdio.h>
#include <cfloat>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "Camera.h"
#include "LightSource.h"
#include "Sphere.h"
#include "Box.h"
#include "Cone.h"
#include "Plane.h"
#include "Triangle.h"
#include "Image.h"
#include "Types.h"

typedef struct SceneParameters {
    glm::vec3 U;
    glm::vec3 V;
    glm::vec3 W;
    
    float Left;
    float Right;
    float Top;
    float Bottom;
} SceneParameters;

typedef struct SceneData {
    int Width;
    int Height;
    
    SceneParameters Params;
    Camera Cam;
    LightSource* Lights;
    LightSource* Lights_d;
    int NumLights;
    Plane* Planes;
    Plane* Planes_d;
    int NumPlanes;
    Sphere* Spheres;
    Sphere* Spheres_d;
    int NumSpheres;
} SceneData;

class Raytracer {
public:
    SceneData Data;
    std::vector<LightSource> Lights;
    std::vector<Sphere> Spheres;
    std::vector<Plane> Planes;
    
    Raytracer(int width, int height, std::vector<std::string> rawComponents);
    
    Image* TraceScene();
    void TraceSceneNoCUDA();
private:
    Image* TracedScene;
    
    void SetupAndLaunchCUDA();
    void ParseRawComponents(std::vector<std::string> components);
};

#endif