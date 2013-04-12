#ifndef FINISH_H
#define FINISH_H

#include <string>

#include "ParsingUtility.h"

class Finish {
public:
    float Ambient;
    float Diffuse;
    float Specular;
    float Roughness;
    float Reflection;
    float Refraction;
    float Ior;
    
    Finish(std::string finishParams);
    Finish();
};

#endif