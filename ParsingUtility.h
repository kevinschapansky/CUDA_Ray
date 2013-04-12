#ifndef PARSING_UTILITY_H
#define PARSING_UTILITY_H

#include <string>
#include <cstdlib>

#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class ParsingUtility {
public:
    static glm::vec3* NamedBracketedParameterToVec3(std::string source,
                                                    std::string name,
                                                    int startIdx,
                                                    int instance);
    static int NamedSingleParameterToFloat(std::string source,
                                           std::string name,
                                           int instance,
                                           float &result);
    static int NamedBracketedParameterStringExtraction(std::string source,
                                                       std::string paramName,
                                                       std::string &destination);
};

#endif