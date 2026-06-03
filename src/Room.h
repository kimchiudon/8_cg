#ifndef ROOM_H
#define ROOM_H

#include <glad/glad.h>
#include "../Dependencies/include/glm/glm.hpp"
#include "shader.h"


class Room {
public:
    Room(float width, float depth, float height);
    ~Room();
    
    bool Contains(float x, float z, float margin) const;
    void Draw(Shader& shader);

private:
    float width;
    float depth;
    float height;

    
    struct Face {
        unsigned int VAO;
        unsigned int VBO;
        unsigned int texture;
        glm::mat4 model;        
    };


    Face floor;
    Face ceiling;
    Face wallFront;     
    Face wallBack;      
    Face wallLeft;     
    Face wallRight;     

  
    void   setupFace(Face& face);
    unsigned int loadTexture(const char* path);
    void   drawFace(const Face& face, Shader& shader);
};

#endif