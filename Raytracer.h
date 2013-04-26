#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <vector>
#include <string>
#include <cuda.h>
#include <stdio.h>
#include <cfloat>
#include <driver_types.h>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"

#include "Camera.h"
#include "LightSource.h"
#include "Shape.h"
#include "Image.h"
#include "Types.h"

typedef struct Intersection {
    float T;
    int ClosestShape;
    glm::vec3 SurfaceNormal;
} Intersection;

typedef struct Ray {
    glm::vec3 D;
    glm::vec3 P0;
} Ray;

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
    
    int NumLights;
    LightSource* Lights;
    
    int NumShapes;
    Shape* Shapes;
} SceneData;

class Raytracer {
public:
    SceneData Data;
    std::vector<LightSource *> Lights;
    std::vector<Shape *> Shapes;
    
    Raytracer(int width, int height, std::vector<std::string> rawComponents);
    
    Image* TraceScene();
private:
    Image* TracedScene;
    
    void SetupAndLaunchCUDA();
    void ParseRawComponents(std::vector<std::string> components);
    void HandleCUDAError(cudaError_t error);
};

#endif