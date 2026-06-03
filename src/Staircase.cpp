#include "Staircase.h"

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



Staircase::Staircase() {
    setupCube();
    texture = loadTexture("textures/floor.jpg");

   
    blockCount = 4;
    blocks = new Block[blockCount];

    blocks[0] = { -20.0f, -4.0f, 2.0f, 12.0f, glm::mat4(1.0f) };  
    blocks[1] = { -4.0f, -2.0f, 1.5f, 12.0f, glm::mat4(1.0f) };   
    blocks[2] = { -2.0f,  0.0f, 1.0f, 12.0f, glm::mat4(1.0f) };   
    blocks[3] = { 0.0f,  2.0f, 0.5f, 12.0f, glm::mat4(1.0f) };  

   
    for (int i = 0; i < blockCount; i++) {
        float cx = (blocks[i].minX + blocks[i].maxX) / 2.0f;  
        float sx = blocks[i].maxX - blocks[i].minX;           
        float sy = blocks[i].topY;                            
        float sz = blocks[i].width;                       

        glm::mat4 m = glm::mat4(1.0f);
        m = glm::translate(m, glm::vec3(cx, 0.0f, 0.0f));     
        m = glm::scale(m, glm::vec3(sx, sy, sz));             
        blocks[i].model = m;
    }
}



Staircase::~Staircase() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteTextures(1, &texture);
    delete[] blocks;
}



void Staircase::setupCube() {
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



unsigned int Staircase::loadTexture(const char* path) {
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



void Staircase::Draw(Shader& shader) {
    shader.use();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    shader.setInt("texture1", 0);

    glBindVertexArray(VAO);
    for (int i = 0; i < blockCount; i++) {
        shader.setMat4("model", blocks[i].model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    glBindVertexArray(0);
}



float Staircase::GetFloorHeightAt(float x, float z) const {
    for (int i = 0; i < blockCount; i++) {
        const Block& b = blocks[i];
        bool inX = (x >= b.minX && x <= b.maxX);
        bool inZ = (z >= -b.width / 2.0f && z <= b.width / 2.0f);
        if (inX && inZ)
            return b.topY;
    }
    return 0.0f;  
}