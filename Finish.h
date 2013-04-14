#ifndef FINISH_H
#define FINISH_H

#include <string>

#include "ParsingUtility.h"

typedef struct Finish {
    float Ambient;
    float Diffuse;
    float Specular;
    float Roughness;
    float Reflection;
    float Refraction;
    float Ior;
    
    Finish(std::string finishParams) {
        if (ParsingUtility::NamedSingleParameterToFloat(finishParams, "ambient", 1, Ambient) < 0) {
            Ambient = 0.1;
        }
        if (ParsingUtility::NamedSingleParameterToFloat(finishParams, "diffuse", 1, Diffuse) < 0) {
            Diffuse = 0.6;
        }
        if (ParsingUtility::NamedSingleParameterToFloat(finishParams, "specular", 1, Specular) < 0) {
            Specular = 0.0;
        }
        if (ParsingUtility::NamedSingleParameterToFloat(finishParams, "roughness", 1, Roughness) < 0) {
            Roughness = 0.05;
        }
        if (ParsingUtility::NamedSingleParameterToFloat(finishParams, "reflection", 1, Reflection) < 0) {
            Reflection = 0.0;
        }
        if (ParsingUtility::NamedSingleParameterToFloat(finishParams, "refraction", 1, Refraction) < 0) {
            Refraction = 0.0;
        }
        if (ParsingUtility::NamedSingleParameterToFloat(finishParams, "ior", 1, Ior) < 0) {
            Ior = 1.0;
        }
    }
    
    Finish() {
        
    }
} Finish;

#endif