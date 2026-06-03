#ifndef STAIRCASE_H
#define STAIRCASE_H

#include <glad/glad.h>
#include "../Dependencies/include/glm/glm.hpp"
#include "shader.h"


class Staircase {
public:
    Staircase();
    ~Staircase();

  
    void Draw(Shader& shader);

   
    float GetFloorHeightAt(float x, float z) const;

private:

    struct Block {
        float minX, maxX;
        float topY;
        float width;
        glm::mat4 model;   
    };

    Block* blocks;    
    int    blockCount; 

    unsigned int VAO;
    unsigned int VBO;
    unsigned int texture;

    void setupCube();
    unsigned int loadTexture(const char* path);
};

#endif