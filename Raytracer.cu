#include "Raytracer.h"

__global__ void CUDATrace(SceneData data, color_t *scenePixels, int N) {
    int i = (blockIdx.x * blockDim.x) + threadIdx.x;
    int j = (blockIdx.y * blockDim.y) + threadIdx.y;
    
    if (i * blockDim.x + j > N) return;

    float Us = data.Params.Left + (data.Params.Right - data.Params.Left) * ((i + 0.5f) / ((float) data.Width));
    float Vs = data.Params.Bottom + (data.Params.Top - data.Params.Bottom) * ((j + 0.5f) / ((float) data.Height));
    glm::vec3 sPrime = data.Cam.Location + Us * data.Params.U + Vs * data.Params.V + -1.0f * data.Params.W;
    glm::vec3 d = glm::normalize(data.Cam.Location - sPrime);
    glm::vec3 p0 = data.Cam.Location;
    color_t color;
    float closestIntersection = FLT_MAX;
    float curIntersection;
    
    for (int k = 0; k < data.NumSpheres; k++) {
        glm::vec3 d_model = glm::vec3(glm::inverse(data.Spheres[k].Transform) * glm::vec4(d, 0));
        glm::vec3 p0_model = glm::vec3(glm::inverse(data.Spheres[k].Transform) * glm::vec4(p0, 1));
        float A = glm::dot(d_model, d_model);
        float B = 2.0f * glm::dot(d_model, (p0_model - data.Spheres[k].Position));
        float C = glm::dot((p0_model - data.Spheres[k].Position), (p0_model - data.Spheres[k].Position))
        - data.Spheres[k].Radius * data.Spheres[k].Radius;
        float descriminant = B * B - 4 * A * C;
        glm::vec3 colorVec = data.Spheres[k].Pig.Color;
        
        if (descriminant < 0) {
            continue;
        } else if (descriminant == 0) {
            curIntersection = -B / (2.0f * A);
            
            if (curIntersection < closestIntersection) {
                closestIntersection = curIntersection;
                color.r = colorVec.x;
                color.g = colorVec.y;
                color.b = colorVec.z;
                color.f = data.Spheres[k].Pig.Filter;
            }
        } else {
            float root = std::sqrt(descriminant);
            curIntersection = min(((-B + root) / (2.0f * A)), ((-B - root) / (2.0f * A)));
            
            if (curIntersection < closestIntersection) {
                closestIntersection = curIntersection;
                color.r = colorVec.x;
                color.g = colorVec.y;
                color.b = colorVec.z;
                color.f = data.Spheres[k].Pig.Filter;
            }
        }
    }
    for (int k = 0; k < data.NumPlanes; k++) {
        glm::vec3 d_model = glm::vec3(glm::inverse(data.Planes[k].Transform) * glm::vec4(d, 0));
        glm::vec3 p0_model = glm::vec3(glm::inverse(data.Planes[k].Transform) * glm::vec4(p0, 1));
        glm::vec3 P = glm::normalize(data.Planes[k].Normal) * -data.Planes[k].Distance;
        float denom = glm::dot(d_model, data.Planes[k].Normal);
        float t = glm::dot((P - p0_model), data.Planes[k].Normal) / denom;
        glm::vec3 colorVec = data.Planes[k].Pig.Color;
        
        if (denom < 0.001f) {
            continue;
        }
        
        if (t < closestIntersection) {
            closestIntersection = t;
            color.r = colorVec.x;
            color.g = colorVec.y;
            color.b = colorVec.z;
            color.f = data.Planes[k].Pig.Filter;
        }
    }
     
    scenePixels[i * data.Height + j] = color;
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
    Sphere *spheres_d;
    Plane *planes_d;
    
    HandleCUDAError(cudaMalloc((void **) &lights_d, Data.NumLights * sizeof(LightSource)));
    HandleCUDAError(cudaMalloc((void **) &spheres_d, Data.Width * Data.NumSpheres * sizeof(Sphere)));
    HandleCUDAError(cudaMalloc((void **) &planes_d, Data.Width * Data.NumPlanes * sizeof(Plane)));
    
    HandleCUDAError(cudaMemcpy(lights_d, Data.Lights, Data.NumLights * sizeof(LightSource), cudaMemcpyHostToDevice));
    HandleCUDAError(cudaMemcpy(spheres_d, Data.Spheres, Data.NumSpheres * sizeof(Sphere), cudaMemcpyHostToDevice));
    HandleCUDAError(cudaMemcpy(planes_d, Data.Planes, Data.NumPlanes * sizeof(Plane), cudaMemcpyHostToDevice));
    
    HandleCUDAError(cudaMalloc((void **) &scenePixels_d, Data.Width * Data.Height * sizeof(color_t)));
               
    cudaData_d.Lights = lights_d;
    cudaData_d.Spheres = spheres_d;
    cudaData_d.Planes = planes_d;
    
    CUDATrace <<<numBlocks, threadsPerBlock>>> (cudaData_d, scenePixels_d, Data.Width * Data.Height);
    
    HandleCUDAError(cudaMemcpy(scenePixels_h, scenePixels_d, Data.Width * Data.Height * sizeof(color_t), cudaMemcpyDeviceToHost));
    
    for (int i = 0; i < Data.Width; i++) {
        for (int j = 0; j < Data.Height; j++) {
            TracedScene->pixel(i, j, scenePixels_h[i * Data.Height + j]);
        }
    }
}

void Raytracer::ParseRawComponents(std::vector<std::string> components) {
    for (int i = 0; i < components.size(); i++) {
        std::string curComp = components[i];
        
        if (std::string::npos != curComp.find("camera")) {
            Data.Cam = Camera(curComp);
        } else if (std::string::npos != curComp.find("light_source")) {
            Lights.push_back(LightSource(curComp));
        } else if (std::string::npos != curComp.find("sphere")) {
            Spheres.push_back(Sphere(curComp));
        } else if (std::string::npos != curComp.find("plane")) {
            Planes.push_back(Plane(curComp));
        } else if (std::string::npos != curComp.find("triangle")) {
            Triangles.push_back(Triangle(curComp));
        }
    }
    Data.Lights = Lights.data();
    Data.NumLights = Lights.size();
    
    Data.Spheres = Spheres.data();
    Data.NumSpheres = Spheres.size();
    
    Data.Planes = Planes.data();
    Data.NumPlanes = Planes.size();
}

void Raytracer::HandleCUDAError(cudaError_t error) {
    if (error != cudaSuccess) {
        printf("CUDA Problem: %s\n", cudaGetErrorString(error));
        exit(-1);
    }
}
