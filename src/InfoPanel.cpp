#include "InfoPanel.h"

#include "../Dependencies/include/stb/stb_image.h"
#include "../Dependencies/include/glm/gtc/matrix_transform.hpp"
#include <iostream>



static float cubeVertices[] = {
  
    -0.5f, 0.0f, -0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 0.0f,
     0.5f, 0.0f, -0.5f,  0.0f,-1.0f, 0.0f,  1.0f, 0.0f,
     0.5f, 0.0f,  0.5f,  0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
     0.5f, 0.0f,  0.5f,  0.0f,-1.0f, 0.0f,  1.0f, 1.0f,
    -0.5f, 0.0f,  0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, 0.0f, -0.5f,  0.0f,-1.0f, 0.0f,  0.0f, 0.0f,

    -0.5f, 1.0f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
     0.5f, 1.0f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
     0.5f, 1.0f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
     0.5f, 1.0f,  0.5f,  0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
    -0.5f, 1.0f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, 1.0f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f,
  
    -0.5f, 0.0f, -0.5f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
     0.5f, 0.0f, -0.5f,  0.0f, 0.0f,-1.0f,  1.0f, 0.0f,
     0.5f, 1.0f, -0.5f,  0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
     0.5f, 1.0f, -0.5f,  0.0f, 0.0f,-1.0f,  1.0f, 1.0f,
    -0.5f, 1.0f, -0.5f,  0.0f, 0.0f,-1.0f,  0.0f, 1.0f,
    -0.5f, 0.0f, -0.5f,  0.0f, 0.0f,-1.0f,  0.0f, 0.0f,
 
    -0.5f, 0.0f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,
     0.5f, 0.0f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f,
     0.5f, 1.0f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
     0.5f, 1.0f,  0.5f,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
    -0.5f, 1.0f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 1.0f,
    -0.5f, 0.0f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f, 0.0f,

    -0.5f, 1.0f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    -0.5f, 1.0f, -0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
    -0.5f, 0.0f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, 0.0f, -0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, 0.0f,  0.5f, -1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
    -0.5f, 1.0f,  0.5f, -1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
    
     0.5f, 1.0f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
     0.5f, 1.0f, -0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,
     0.5f, 0.0f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, 0.0f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
     0.5f, 0.0f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
     0.5f, 1.0f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,
};

static float quadVertices[] = {
   
    -0.5f, -0.5f, 0.0f,  0.0f,0.0f,1.0f,  0.0f, 0.0f,
     0.5f, -0.5f, 0.0f,  0.0f,0.0f,1.0f,  1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,  0.0f,0.0f,1.0f,  1.0f, 1.0f,
     0.5f,  0.5f, 0.0f,  0.0f,0.0f,1.0f,  1.0f, 1.0f,
    -0.5f,  0.5f, 0.0f,  0.0f,0.0f,1.0f,  0.0f, 1.0f,
    -0.5f, -0.5f, 0.0f,  0.0f,0.0f,1.0f,  0.0f, 0.0f,
};


InfoPanel::InfoPanel(float posX, float posZ, float floorY,
    const char* infoTexturePath, float facingYaw) {
    setupCube();
    baseTexture  = loadTexture("textures/panel2.jpg");   
    panelTexture = loadTexture("textures/panel2.jpg"); 

  
    float baseW = 1.3f;  
    float baseH = 0.9f;   
    float baseD = 0.1f;   
    {
        glm::mat4 m = glm::mat4(1.0f);
        
        m = glm::translate(m, glm::vec3(posX, floorY, posZ));
        m = glm::rotate(m, glm::radians(facingYaw), glm::vec3(0, 1, 0));
        m = glm::scale(m, glm::vec3(baseW, baseH, baseD));
        baseModel = m;
    }

    
    float panelW = 1.3f;     
    float panelLen = 0.9f;   
    float panelThick = 0.08f; 
    float tilt = 55.0f;      
    {
        glm::mat4 m = glm::mat4(1.0f);
        
        m = glm::translate(m, glm::vec3(posX, floorY + baseH, posZ));
        
        m = glm::rotate(m, glm::radians(facingYaw), glm::vec3(0.0f, 1.0f, 0.0f));
        m = glm::rotate(m, glm::radians(tilt), glm::vec3(1.0f, 0.0f, 0.0f));
      
        m = glm::scale(m, glm::vec3(panelW, panelLen, panelThick));
        panelModel = m;

        setupQuad();
        infoTexture = loadTexture(infoTexturePath);

 
        {
            glm::mat4 m = glm::mat4(1.0f);

       
            m = glm::translate(m, glm::vec3(posX, floorY + baseH, posZ));

            m = glm::rotate(m, glm::radians(facingYaw), glm::vec3(0.0f, 1.0f, 0.0f));

         
            m = glm::rotate(m, glm::radians(tilt), glm::vec3(1.0f, 0.0f, 0.0f));

            
            m = glm::translate(m, glm::vec3(0.0f, panelLen / 2.0f, -(panelThick / 2.0f + 0.01f)));
            m = glm::rotate(m, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
            m = glm::scale(m, glm::vec3(panelW * 0.9f, panelLen * 0.9f, 1.0f));

            infoQuadModel = m;
        }
    }
}



InfoPanel::~InfoPanel() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &baseTexture);
    glDeleteTextures(1, &panelTexture);
    glDeleteVertexArrays(1, &quadVAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteTextures(1, &infoTexture);
}


void InfoPanel::setupCube() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void InfoPanel::setupQuad() {
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);
}


unsigned int InfoPanel::loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int w, h, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &w, &h, &nrChannels, 0);

    if (data) {
        GLenum format = GL_RGB;
        if (nrChannels == 1)      format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0,
            format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else {
        std::cout << "Failed to load texture: " << path << std::endl;
    }

    stbi_image_free(data);
    return textureID;
}


void InfoPanel::Draw(Shader& shader) {
    shader.use();
    glBindVertexArray(VAO);


    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, baseTexture);
    shader.setInt("texture1", 0);
    shader.setMat4("model", baseModel);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindTexture(GL_TEXTURE_2D, panelTexture);
    shader.setMat4("model", panelModel);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, infoTexture);
    shader.setMat4("model", infoQuadModel);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
}
