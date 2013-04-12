#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <vector>
#include <string>
#include <cuda.h>
#include <stdio.h>

#include "Camera.h"
#include "LightSource.h"
#include "Sphere.h"
#include "Box.h"
#include "Cone.h"
#include "Plane.h"
#include "Triangle.h"

class Raytracer {
public:
    Raytracer(std::vector<std::string> rawComponents);
private:
    Camera *Cam;
    std::vector<LightSource *> Lights;
    std::vector<Sphere *> Spheres;
    std::vector<Box *> Boxes;
    std::vector<Cone *> Cones;
    std::vector<Plane *> Planes;
    std::vector<Triangle *> Triangles;
    
    void ParseRawComponents(std::vector<std::string> components);
};

#endif