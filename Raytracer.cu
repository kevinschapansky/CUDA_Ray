#include "Raytracer.h"

__global__ void CudaTest() {
    
}

Raytracer::Raytracer(int width, int height, std::vector<std::string> rawComponents) {
    Width = width;
    Height = height;
    ParseRawComponents(rawComponents);
}

Image* Raytracer::TraceScene() {
    Image* scene = new Image(Width, Height);
    
    glm::vec3 U(Cam->Right->x, Cam->Right->y, Cam->Right->z);
    glm::vec3 V(Cam->Up->x, Cam->Up->y, Cam->Up->z);
    glm::vec3 W(1.0);
    float left = -1 * glm::length(*Cam->Right) / 2.0;
    float right = -left;
    float top = glm::length(*Cam->Up) / 2.0;
    float bottom = -top;
    
    U = glm::normalize(U);
    V = glm::normalize(V);
    W = glm::normalize(glm::cross(U, V));
    
    for (int i = 0; i < Width; i++) {
        for (int j = 0; j < Height; j++) {
            float Us = left + (right - left) * ((i + 0.5) / ((float) Width));
            float Vs = bottom + (top - bottom) * ((j + 0.5) / ((float) Height));
            glm::vec3 sPrime = *Cam->Location + Us * U + Vs * V + 1.0f * W;
            glm::vec3 d = glm::normalize(*Cam->Location - sPrime);
            glm::vec3 p0 = *Cam->Location;
            color_t color;
            float closestIntersection = FLT_MAX;
            float curIntersection;
            
            color.r = 0;
            color.g = 0;
            color.b = 0;
            color.f = 0;
            
            for (int k = 0; k < Spheres.size(); k++) {
                float A = glm::dot(d, d);
                float B = 2 * glm::dot(d, (p0 - *Spheres[k]->Position));
                float C = glm::dot((p0 - *Spheres[k]->Position), (p0 - *Spheres[k]->Position))
                - Spheres[k]->Radius * Spheres[k]->Radius;
                float descriminant = B * B - 4 * A * C;
                glm::vec3 colorVec = *Spheres[k]->Pig->Color;
                
                if (descriminant < 0) {
                    continue;
                } else if (descriminant == 0) {
                    curIntersection = -B / (2 * A);
                    
                    if (curIntersection < closestIntersection) {
                        closestIntersection = curIntersection;
                        color.r = colorVec.x;
                        color.g = colorVec.y;
                        color.b = colorVec.z;
                        color.f = Spheres[k]->Pig->Filter;
                    }
                } else {
                    float root = std::sqrt(descriminant);
                    curIntersection = min(((-B + root) / (2 * A)), ((-B - root) / (2 * A)));
                    
                    if (curIntersection < closestIntersection) {
                        closestIntersection = curIntersection;
                        color.r = colorVec.x;
                        color.g = colorVec.y;
                        color.b = colorVec.z;
                        color.f = Spheres[k]->Pig->Filter;
                    }
                }
            }
            for (int k = 0; k < Planes.size(); k++) {
                glm::vec3 P = glm::normalize(*Planes[k]->Normal) * -Planes[k]->Distance;
                float denom = glm::dot(d, *Planes[k]->Normal);
                float t = glm::dot((P - p0), *Planes[k]->Normal) / denom;
                glm::vec3 colorVec = *Planes[k]->Pig->Color;
                
                if (denom < 0.01) {
                    continue;
                }
                
                if (t < closestIntersection) {
                    closestIntersection = t;
                    color.r = colorVec.x;
                    color.g = colorVec.y;
                    color.b = colorVec.z;
                    color.f = Planes[k]->Pig->Filter;
                }
            }
            scene->pixel(i, j, color);
        }
    }
    
    return scene;
}

void Raytracer::GenerateRays() {
    glm::vec3 U(Cam->Right->x, Cam->Right->y, Cam->Right->z);
    glm::vec3 V(Cam->Up->x, Cam->Up->y, Cam->Up->z);
    glm::vec3 W(1.0);
    float left = - ((float) Width) / ((float) Height);
    float right = -left;
    float top = 1;
    float bottom = -1;
    
    U = glm::normalize(U);
    V = glm::normalize(V);
    W = glm::normalize(glm::cross(U, V));
    
    for (int i = 0; i < Width; i++) {
        for (int j = 0; j < Height; j++) {
            float Us = left + (right - left) * ((i + 0.5) / ((float) Width));
            float Vs = bottom + (top - bottom) * ((j + 0.5) / ((float) Height));
            glm::vec3 sPrime = *Cam->Location + Us * U + Vs * V + -1.0f * W;
            glm::vec3 d = glm::normalize(*Cam->Location - sPrime);
            glm::vec3 p0 = *Cam->Location;
            glm::vec3 color(0);
            float closestIntersection = FLT_MAX;
            float curIntersection;
            
            for (int k = 0; k < Spheres.size(); k++) {
                float A = glm::dot(d, d);
                float B = 2 * glm::dot(d, (p0 - *Spheres[k]->Position));
                float C = glm::dot((p0 - *Spheres[k]->Position), (p0 - *Spheres[k]->Position))
                - Spheres[k]->Radius * Spheres[k]->Radius;
                float descriminant = B * B - 4 * A * C;
                
                if (descriminant < 0) {
                    continue;
                } else if (descriminant == 0) {
                    curIntersection = -B / (2 * A);
                    
                    if (curIntersection < closestIntersection) {
                        closestIntersection = curIntersection;
                        color = *Spheres[k]->Pig->Color;
                    }
                } else {
                    float root = std::sqrt(descriminant);
                    curIntersection = min(((-B + root) / (2 * A)), ((-B - root) / (2 * A)));
                    
                    if (curIntersection < closestIntersection) {
                        closestIntersection = curIntersection;
                        color = *Spheres[k]->Pig->Color;
                    }
                }
            }
            
        }
    }
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