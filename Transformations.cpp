#include "Transformations.h"

Transformations::Transformations(std::string transformationParams) {
    Operation *nextOp;
    int curIx = 0;
    
    while ((nextOp = FindNextOperation(transformationParams, curIx)) != NULL) {
        Operations.push_back(nextOp);
        curIx = nextOp->Index + 1;
    }
    
    for (int i = 0; i < Operations.size(); i++) {
        Operation * op = Operations[i];
    }
}

Transformations::Transformations() {
    
}

Operation* Transformations::FindNextOperation(std::string source, int from) {
    enum Operations curOp = Translate;
    int lowestLocation = from - 1;
    
    int nextLoc = 0;
    
    nextLoc = source.find(Operation::OperationToString(Translate) , from);
    
    if (nextLoc != std::string::npos) {
        curOp = Translate;
        lowestLocation = nextLoc;
    }
    
    nextLoc = source.find(Operation::OperationToString(Rotate), from);
    
    if (nextLoc != std::string::npos && nextLoc < lowestLocation) {
        curOp = Rotate;
        lowestLocation = nextLoc;
    }
    
    nextLoc = source.find(Operation::OperationToString(Scale), from);
    
    if (nextLoc != std::string::npos && nextLoc < lowestLocation) {
        curOp = Scale;
        lowestLocation = nextLoc;
    }
    
    if (lowestLocation >= from) {
        Operation *newOp = new Operation(curOp, lowestLocation);
        newOp->Parameters = ParsingUtility::NamedBracketedParameterToVec3(source, Operation::OperationToString(newOp->Op), newOp->Index, 1);
        return newOp;
    } else {
        return NULL;
    }
}

Operation::Operation(Operations op, int idx) {
    Op = op;
    Index = idx;
}

Operation::Operation() {
    
}

std::string Operation::OperationToString(Operations op) {
    switch (op) {
        case Translate:
            return "translate";
            break;
        case Rotate:
            return "rotate";
            break;
        case Scale:
            return "scale";
            break;
    };
}