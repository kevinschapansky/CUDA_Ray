#include "Raytracer.h"

__device__ Intersection GetIntersection(SceneData data, Ray ray, float minInt, float maxInt) {
    Intersection closestInt;
    glm::vec3 d_model;
    glm::vec3 p0_model;
    
    closestInt.T = maxInt;
    closestInt.ClosestShape = -1;
    
    for (int i = 0; i < data.NumShapes; i++) {
        d_model = glm::vec3(data.Shapes[i].InverseTransform * glm::vec4(ray.D, 0));
        p0_model = glm::vec3(data.Shapes[i].InverseTransform * glm::vec4(ray.P0, 1));
        
        if (data.Shapes[i].Type == Shape::SPHERE) {
            float A = glm::dot(d_model, d_model);
            float B = 2.0f * glm::dot(d_model, (p0_model - data.Shapes[i].Position));
            float C = glm::dot((p0_model - data.Shapes[i].Position), (p0_model - data.Shapes[i].Position))
            - data.Shapes[i].Radius * data.Shapes[i].Radius;
            float descriminant = B * B - 4 * A * C;
            float t;
            
            if (descriminant < 0) {
                continue;
            } else if (descriminant == 0) {
                t = -B / (2.0f * A);
                
                if (t < closestInt.T && t > minInt && t < maxInt) {
                    closestInt.T = t;
                    closestInt.ClosestShape = i;
                    closestInt.SurfaceNormal = glm::vec3(glm::inverseTranspose(data.Shapes[i].Transform) * glm::vec4((p0_model + t * d_model) - data.Shapes[i].Position, 0));
                }
            } else {
                float root = std::sqrt(descriminant);
                t = min(((-B + root) / (2.0f * A)), ((-B - root) / (2.0f * A)));
                if (t < closestInt.T && t > minInt && t < maxInt) {
                    closestInt.T = t;
                    closestInt.ClosestShape = i;
                    closestInt.SurfaceNormal = glm::vec3(glm::inverseTranspose(data.Shapes[i].Transform) * glm::vec4((p0_model + t * d_model) - data.Shapes[i].Position, 0));
                }
            }
        } else if (data.Shapes[i].Type == Shape::PLANE) {
            glm::vec3 P = glm::normalize(data.Shapes[i].Normal) * data.Shapes[i].Distance;
            float denom = glm::dot(d_model, data.Shapes[i].Normal);
            float t = glm::dot((P - p0_model), data.Shapes[i].Normal) / denom;

            if (abs(denom) > 0.001f && t < closestInt.T && t > minInt && t < maxInt) {
                closestInt.T = t;
                closestInt.ClosestShape = i;
                closestInt.SurfaceNormal = glm::vec3(glm::inverseTranspose(data.Shapes[i].Transform) * glm::vec4(data.Shapes[i].Normal, 0));
            }
        }
    }
    return closestInt;
}

__device__ glm::vec3 GetLightingAtIntersection(SceneData data, Intersection inter, Ray ray) {
    glm::vec3 intersectionColor(0);
    Shape curShape = data.Shapes[inter.ClosestShape];
    Intersection lightInt;
    glm::vec3 intersectionPoint = ray.P0 + inter.T * ray.D;
    glm::vec3 lightPosition_model;
    Ray lightRay;
    
    lightRay.P0 = intersectionPoint;
    intersectionColor = curShape.Pig.Color * curShape.Fin.Ambient;
    
    for (int i = 0; i < data.NumLights; i++) {
        lightRay.D = glm::normalize(data.Lights[i].Position - intersectionPoint);
        lightInt = GetIntersection(data, lightRay, 0.01f,
                                   glm::length(data.Lights[i].Position - intersectionPoint));
        
        if (lightInt.ClosestShape < 0) {
            glm::vec3 reflection = - 2.0f * (max(glm::dot(lightRay.D, inter.SurfaceNormal), 0.0f)) * inter.SurfaceNormal + lightRay.D;
            
            intersectionColor += curShape.Pig.Color * max(glm::dot(inter.SurfaceNormal, lightRay.D), 0.0f) * data.Lights[i].Color * curShape.Fin.Diffuse;
            intersectionColor += curShape.Pig.Color * pow(max(glm::dot(-ray.D, reflection), 0.0f), 1.0f / curShape.Fin.Roughness) * data.Lights[i].Color * curShape.Fin.Specular;
        }
    }
    intersectionColor.x = min(intersectionColor.x, 1.0f);
    intersectionColor.y = min(intersectionColor.y, 1.0f);
    intersectionColor.z = min(intersectionColor.z, 1.0f);
    
    return intersectionColor;
}

__global__ void CUDATrace(SceneData data, color_t *scenePixels, int N) {
    int i = (blockIdx.x * blockDim.x) + threadIdx.x;
    int j = (blockIdx.y * blockDim.y) + threadIdx.y;
    int sceneIx = i * data.Height + j;
    
    if (i * blockDim.x + j > N) return;
    scenePixels[sceneIx].r = 0;
    scenePixels[sceneIx].g = 0;
    scenePixels[sceneIx].b = 0;
    scenePixels[sceneIx].f = 0;
    
    
    float Us = data.Params.Left + (data.Params.Right - data.Params.Left) * ((i + 0.5f) / ((float) data.Width));
    float Vs = data.Params.Bottom + (data.Params.Top - data.Params.Bottom) * ((j + 0.5f) / ((float) data.Height));
    glm::vec3 sPrime = data.Cam.Location + Us * data.Params.U + Vs * data.Params.V + -1.0f * data.Params.W;
    Ray castRay;
    glm::vec3 pixelColor;
    
    castRay.D = glm::normalize(sPrime - data.Cam.Location);
    castRay.P0 = data.Cam.Location;
    
    Intersection closestInt = GetIntersection(data, castRay, FLT_MIN, FLT_MAX);
    
    if (closestInt.ClosestShape >= 0) {
        glm::vec3 pixelColor = GetLightingAtIntersection(data, closestInt, castRay);
        scenePixels[sceneIx].r = pixelColor.x;
        scenePixels[sceneIx].g = pixelColor.y;
        scenePixels[sceneIx].b = pixelColor.z;
        scenePixels[sceneIx].f = 0;
    }
     
}



Raytracer::Raytracer(int width, int height, std::vector<std::string> rawComponents) {
    Data.Width = width;
    Data.Height = height;
    
    ParseRawComponents(rawComponents);
}

Image* Raytracer::TraceScene() {
    TracedScene = new Image(Data.Width, Data.Height);
    
    Data.Params.U = glm::normalize(glm::vec3(Data.Cam.Right.x, Data.Cam.Right.y, Data.Cam.Right.z));
    Data.Params.V = glm::normalize(glm::vec3(Data.Cam.Up.x, Data.Cam.Up.y, Data.Cam.Up.z));
    Data.Params.W = glm::normalize(glm::cross(Data.Params.U, Data.Params.V));
    
    Data.Params.Left = -1 * glm::length(Data.Cam.Right) / 2.0;
    Data.Params.Right = -Data.Params.Left;
    Data.Params.Top = glm::length(Data.Cam.Up) / 2.0;
    Data.Params.Bottom = -Data.Params.Top;
    
    SetupAndLaunchCUDA();
    
    return TracedScene;
}

void Raytracer::SetupAndLaunchCUDA() {
    dim3 threadsPerBlock(8,8);
    dim3 numBlocks(Data.Width / threadsPerBlock.x,
                   Data.Height / threadsPerBlock.y);
    
    SceneData cudaData_d = Data;
    
    color_t *scenePixels_h = new color_t[Data.Width * Data.Height];
    color_t *scenePixels_d;
    
    LightSource *lights_d;
    Shape *shapes_d;
    
    HandleCUDAError(cudaMalloc((void **) &lights_d, Data.NumLights * sizeof(LightSource)));
    HandleCUDAError(cudaMalloc((void **) &shapes_d, Data.NumShapes * sizeof(Shape)));
    
    HandleCUDAError(cudaMemcpy(lights_d, Data.Lights, Data.NumLights * sizeof(LightSource), cudaMemcpyHostToDevice));
    HandleCUDAError(cudaMemcpy(shapes_d, Data.Shapes, Data.NumShapes * sizeof(Shape), cudaMemcpyHostToDevice));
    
    HandleCUDAError(cudaMalloc((void **) &scenePixels_d, Data.Width * Data.Height * sizeof(color_t)));
               
    cudaData_d.Lights = lights_d;
    cudaData_d.Shapes = shapes_d;
    
    CUDATrace <<<numBlocks, threadsPerBlock>>> (cudaData_d, scenePixels_d, Data.Width * Data.Height);
    
    HandleCUDAError(cudaMemcpy(scenePixels_h, scenePixels_d, Data.Width * Data.Height * sizeof(color_t), cudaMemcpyDeviceToHost));
    
    for (int i = 0; i < Data.Width; i++) {
        for (int j = 0; j < Data.Height; j++) {
            TracedScene->pixel(i, j, scenePixels_h[i * Data.Height + j]);
        }
    }
    HandleCUDAError(cudaFree(lights_d));
    HandleCUDAError(cudaFree(shapes_d));
    HandleCUDAError(cudaFree(scenePixels_d));
}

void Raytracer::ParseRawComponents(std::vector<std::string> components) {
    for (int i = 0; i < components.size(); i++) {
        std::string curComp = components[i];
        
        if (std::string::npos != curComp.find("camera")) {
            Data.Cam = *(new Camera(curComp));
        } else if (std::string::npos != curComp.find("light_source")) {
            Lights.push_back(new LightSource(curComp));
        } else if (std::string::npos != curComp.find("sphere")) {
            Shapes.push_back(new Shape(curComp, Shape::SPHERE));
        } else if (std::string::npos != curComp.find("plane")) {
            Shape *curShape = new Shape(curComp, Shape::PLANE);
            Shapes.push_back(curShape);
            
            //printf("Normal: %f, %f, %f Distance: %f\n", curShape->Normal.x, curShape->Normal.y, curShape->Normal.z, curShape->Distance);
        } 
    }
    Data.Lights = new LightSource[Lights.size()];
    Data.NumLights = Lights.size();
    
    for (int i = 0; i < Lights.size(); i++) {
        Data.Lights[i] = *Lights[i];
    }
    
    Data.Shapes = new Shape[Shapes.size()];
    Data.NumShapes = Shapes.size();
    
    for (int i = 0; i < Shapes.size(); i++) {
        Data.Shapes[i] = *Shapes[i];
    }
}

void Raytracer::HandleCUDAError(cudaError_t error) {
    if (error != cudaSuccess) {
        printf("CUDA Problem: %s\n", cudaGetErrorString(error));
        exit(-1);
    }
}
