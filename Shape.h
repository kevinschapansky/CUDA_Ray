#ifndef SHAPE_H
#define SHAPE_H

#include <string>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "ParsingUtility.h"
#include "Pigment.h"
#include "Finish.h"

class Shape {
public:
    enum {BOX, CONE, PLANE, SPHERE, TRIANGLE};
    //needed by all types
    glm::mat4 Transform;
    glm::mat4 InverseTransform;
    Pigment Pig;
    Finish Fin;
    int Type;
    
    //box
    glm::vec3 LeftUpper;
    glm::vec3 RightLower;
    
    //cone
    glm::vec3 End1;
    float Radius1;
    glm::vec3 End2;
    float Radius2;
    
    //plane
    glm::vec3 Normal;
    float Distance;
    
    //sphere
    glm::vec3 Position;
    float Radius;
    
    //triangle
    glm::vec3 Corner1;
    glm::vec3 Corner2;
    glm::vec3 Corner3;
    
    Shape(std::string shapeParams, int shapeType) {
        std::string pigmentInfo;
        std::string finishInfo;
        Type = shapeType;
        
        if (ParsingUtility::NamedBracketedParameterStringExtraction(shapeParams, "pigment", pigmentInfo) > 0) {
            Pig = Pigment(pigmentInfo);
        }
        if (ParsingUtility::NamedBracketedParameterStringExtraction(shapeParams, "finish", finishInfo) > 0) {
            Fin = Finish(finishInfo);
        }
        ParsingUtility::ExtractTransformationMatrix(shapeParams, Transform);
        InverseTransform = glm::inverse(Transform);
        
        switch (shapeType) {
            case BOX:
                ParsingUtility::NamedBracketedParameterToVec3(shapeParams, "<", LeftUpper, 0, 1);
                ParsingUtility::NamedBracketedParameterToVec3(shapeParams, "<", RightLower, 0, 2);
                break;
            case CONE:
                ParsingUtility::NamedBracketedParameterToVec3(shapeParams, "<", End1, 0, 1);
                ParsingUtility::NamedSingleParameterToFloat(shapeParams, ",", 3, Radius1);
                ParsingUtility::NamedBracketedParameterToVec3(shapeParams, "<", End2, 0, 2);
                ParsingUtility::NamedSingleParameterToFloat(shapeParams, ",", 7, Radius2);
                break;
            case PLANE:
                ParsingUtility::NamedBracketedParameterToVec3(shapeParams, "<", Normal, 0, 1);
                ParsingUtility::NamedSingleParameterToFloat(shapeParams, ",", 3, Distance);
                break;
            case SPHERE:
                ParsingUtility::NamedBracketedParameterToVec3(shapeParams, "<", Position, 0, 1);
                ParsingUtility::NamedSingleParameterToFloat(shapeParams, ",", 3, Radius);
                break;
            case TRIANGLE:
                ParsingUtility::NamedBracketedParameterToVec3(shapeParams, "<", Corner1, 0, 1);
                ParsingUtility::NamedBracketedParameterToVec3(shapeParams, "<", Corner2, 0, 2);
                ParsingUtility::NamedBracketedParameterToVec3(shapeParams, "<", Corner3, 0, 3);
                break;
        }
    }
    Shape() {
        
    }
};

#endif