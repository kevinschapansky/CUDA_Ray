#include "Raytracer.h"

__global__ void CudaTest() {
    
}

Raytracer::Raytracer(std::vector<std::string> rawComponents) {
    ParseRawComponents(rawComponents);
}

void Raytracer::ParseRawComponents(std::vector<std::string> components) {
    for (int i = 0; i < components.size(); i++) {
        std::string curComp = components[i];
        
        if (std::string::npos != curComp.find("camera")) {
            Cam = new Camera(curComp);
        } else if (std::string::npos != curComp.find("light_source")) {
            Lights.push_back(new LightSource(curComp));
        } else if (std::string::npos != curComp.find("sphere")) {
            Spheres.push_back(new Sphere(curComp));
        } else if (std::string::npos != curComp.find("box")) {
            Boxes.push_back(new Box(curComp));
        } else if (std::string::npos != curComp.find("cone")) {
           Cones.push_back(new Cone(curComp));
        } else if (std::string::npos != curComp.find("plane")) {
            Planes.push_back(new Plane(curComp));
        } else if (std::string::npos != curComp.find("triangle")) {
            Triangles.push_back(new Triangle(curComp));
        }
    }
}