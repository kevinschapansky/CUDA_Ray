#include "ParsingUtility.h"

int ParsingUtility::NamedBracketedParameterToVec3(std::string source,
                                                  std::string name,
                                                  glm::vec3 &result,
                                                  int startIdx,
                                                  int instance) {
    int namePos = startIdx - 1;
    int curPos;
    int curInstance = 0;
    float x, y, z;
    
    do {
        namePos = source.find(name, namePos + 1);
        curInstance++;
        
        if (namePos == std::string::npos) {
            return NULL;
        }
    } while (curInstance != instance);
    
    curPos = source.find("<", namePos);
    
    x = atof(source.substr(curPos + 1).c_str());
    curPos = source.find(",", curPos);
    y = atof(source.substr(curPos + 1).c_str());
    curPos = source.find(",", curPos + 1);
    z = atof(source.substr(curPos + 1).c_str());
    
    result.x = x;
    result.y = y;
    result.z = z;
}

int ParsingUtility::NamedSingleParameterToFloat(std::string source, std::string name,
                                                int instance, float &result) {
    int namePos = -1;
    int curInstance = 0;
    
    do {
        namePos = source.find(name, namePos + 1);
        curInstance++;
        
        if (namePos == std::string::npos) {
            return -1;
        }
    } while (curInstance != instance);
    result = atof(source.substr(namePos + name.length()).c_str());
    return 1;
}

int ParsingUtility::NamedBracketedParameterStringExtraction(std::string source,
                                                            std::string paramName,
                                                            std::string &destination) {
    int start = source.find(paramName);
    int end = source.find("}");
    
    if (start == std::string::npos || end == std::string::npos) {
        return -1;
    }
    destination = source.substr(start, end + 1 - start);
    return 1;
}

int ParsingUtility::ExtractTransformationMatrix(std::string source,
                                                glm::mat4x4 &result) {
    std::string transformName;
    glm::vec3 foundTransform;
    result = glm::mat4(1);
    int foundIx;
    
    while ((foundIx = FindNextTransform(transformName, source) - 1) >= 0) {
        NamedBracketedParameterToVec3(source, transformName, foundTransform, foundIx, 1);
        
        if (transformName == TRANSLATE_OP) {
            result = glm::translate(result, foundTransform);
            //printf("translate: %f, %f, %f\n", foundTransform.x, foundTransform.y, foundTransform.z);
        } else if (transformName == ROTATE_OP) {
            result = glm::rotate(result, foundTransform.x, glm::vec3(1, 0, 0));
            result = glm::rotate(result, foundTransform.y, glm::vec3(0, 1, 0));
            result = glm::rotate(result, foundTransform.z, glm::vec3(0, 0, 1));
            //printf("rotate: %f, %f, %f\n", foundTransform.x, foundTransform.y, foundTransform.z);
        } else if (transformName == SCALE_OP) {
            result = glm::scale(result, foundTransform);
            //printf("scale: %f, %f, %f\n", foundTransform.x, foundTransform.y, foundTransform.z);
        } else {
            printf("Illegal transform name, stuff's broke\n");
        }
        source = source.substr(0, foundIx);
    }
    
    return 1;
}

int ParsingUtility::FindNextTransform(std::string &transformName, std::string source) {
    int foundIx = 0;
    int highestIndex = -1;
    
    if ((foundIx = source.rfind(TRANSLATE_OP)) > highestIndex && foundIx != std::string::npos) {
        highestIndex = foundIx;
        transformName = TRANSLATE_OP;
    }
    if ((foundIx = source.rfind(ROTATE_OP)) > highestIndex && foundIx != std::string::npos) {
        highestIndex = foundIx;
        transformName = ROTATE_OP;
    }
    if ((foundIx = source.rfind(SCALE_OP)) > highestIndex && foundIx != std::string::npos) {
        highestIndex = foundIx;
        transformName = SCALE_OP;
    }
    return highestIndex;
}