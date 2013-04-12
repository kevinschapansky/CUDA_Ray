#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <string>
#include <vector>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ParsingUtility.h"

enum Operations {
    Translate,
    Rotate,
    Scale
};

class Operation {
public:
    Operations Op;
    glm::vec3* Parameters;
    int Index;
    
    Operation(Operations op, int idx);
    Operation();
    
    static std::string OperationToString(Operations op);
};

class Transformations {
public:
    
    std::vector<Operation *> Operations;
    
    Transformations(std::string transformationParams);
    Transformations();
    
private:
    Operation* FindNextOperation(std::string source, int from);
};

#endif