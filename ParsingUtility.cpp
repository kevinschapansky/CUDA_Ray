#include "ParsingUtility.h"

glm::vec3* ParsingUtility::NamedBracketedParameterToVec3(std::string source,
                                                         std::string name,
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
    
    return new glm::vec3(x, y, z);
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
    
    result = atof(source.substr(namePos + 1).c_str());
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