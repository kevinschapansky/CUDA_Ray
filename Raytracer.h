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

struct Ray {
    glm::vec3 d;
    glm::vec3 p0;
};

class Raytracer {
public:
    Raytracer(int width, int height, std::vector<std::string> rawComponents);
    
    Image* TraceScene();
private:
    int Width;
    int Height;
    
    Camera *Cam;
    std::vector<LightSource *> Lights;
    std::vector<Sphere *> Spheres;
    std::vector<Box *> Boxes;
    std::vector<Cone *> Cones;
    std::vector<Plane *> Planes;
    std::vector<Triangle *> Triangles;
    
    std::vector<Ray *> Rays;
    
    void ParseRawComponents(std::vector<std::string> components);
    void GenerateRays();
};

#endif