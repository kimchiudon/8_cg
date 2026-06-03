#ifndef INFOPANEL_H
#define INFOPANEL_H

#include <glad/glad.h>
#include "../Dependencies/include/glm/glm.hpp"
#include "shader.h"


class InfoPanel {
public:
   
    InfoPanel(float posX, float posZ, float floorY,
        const char* infoTexturePath = "textures/florrguide.jpg",
        float facingYaw = 0.0f);
    ~InfoPanel();

    void Draw(Shader& shader);

private:
    
    glm::mat4 baseModel;
    glm::mat4 panelModel;

    unsigned int VAO;
    unsigned int VBO;
    unsigned int baseTexture;   
    unsigned int panelTexture;  

    void setupCube();
    unsigned int loadTexture(const char* path);

    glm::mat4 infoQuadModel;    
    unsigned int quadVAO;       
    unsigned int quadVBO;
    unsigned int infoTexture;  
    void setupQuad();           
};

#endif
