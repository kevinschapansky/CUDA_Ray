#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <stdio.h>

#include "Raytracer.h"

#define WIDTH_POS 1
#define HEIGHT_POS 2
#define FILE_FLAG 3
#define FILE_POS 4
#define ARG_COUNT 5

void parseFileIntoBlocks(std::string fileName, std::vector<std::string> & rawComponents);

int main(int argc, char **argv) {
    std::vector<std::string> rawComponents;
    std::string fileFlag = "-I";
    int width, height;
    
    if (argc != ARG_COUNT || fileFlag.compare(argv[FILE_FLAG]) != 0) {
        printf("Usage: raytrace <width> <height> -I <fileName\n");
        return EXIT_FAILURE;
    }
    
    width = strtol(argv[WIDTH_POS], NULL, 10);
    height = strtol(argv[HEIGHT_POS], NULL, 10);
    
    parseFileIntoBlocks(argv[FILE_POS], rawComponents);
    Raytracer tracer(width, height, rawComponents);
    Image* result = tracer.TraceScene();
    
    std::string fileName = argv[FILE_POS];
    fileName = fileName.substr(0, fileName.length() - 4);
    fileName += ".tga";
    
    result->WriteTga((char*)fileName.c_str(), true);
    
    return EXIT_SUCCESS;
}

void parseFileIntoBlocks(std::string fileName, std::vector<std::string> & rawComponents) {
    std::ifstream povRayFile(fileName.c_str());
    std::string nextLine;
    int bracketOffset = 0;
    bool inBlock = false;
    std::string componentBlock;
    
    if (povRayFile.is_open()) {
        while (getline(povRayFile, nextLine)){
            
            nextLine += '\n';
            if (std::string::npos != nextLine.find("//")) {
                continue;
            }
            
            for (int i = 0; i < nextLine.length(); i++) {
                if (nextLine[i] == '{') {
                    inBlock = true;
                    bracketOffset++;
                } else if (nextLine[i] == '}') {
                    bracketOffset--;
                }
            }
            if (inBlock)
                componentBlock += nextLine;
            if (inBlock && bracketOffset == 0) {
                rawComponents.push_back(componentBlock);
                componentBlock = "";
                inBlock = false;
            }
        }
        povRayFile.close();
    } else {
        printf("Error opening POV Ray file\n");
    }
}