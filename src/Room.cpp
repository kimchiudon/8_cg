#include "Room.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Dependencies/include/stb/stb_image.h"

#include "../Dependencies/include/glm/gtc/matrix_transform.hpp"
#include <iostream>



static float quadVertices[] = {
    
    -0.5f, 0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,  
     0.5f, 0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
     0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,  

    -0.5f, 0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f, 
     0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, 
    -0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  
};


Room::Room(float w, float d, float h)
    : width(w), depth(d), height(h)
{
   
    setupFace(floor);
    setupFace(ceiling);
    setupFace(wallFront);
    setupFace(wallBack);
    setupFace(wallLeft);
    setupFace(wallRight);

    floor.model = glm::mat4(1.0f);
    floor.model = glm::scale(floor.model, glm::vec3(width, 1.0f, depth));

  
    ceiling.model = glm::mat4(1.0f);
    ceiling.model = glm::translate(ceiling.model, glm::vec3(0.0f, height, 0.0f));
    ceiling.model = glm::rotate(ceiling.model, glm::radians(180.0f), glm::vec3(1, 0, 0));
    ceiling.model = glm::scale(ceiling.model, glm::vec3(width, 1.0f, depth));

   
    wallFront.model = glm::mat4(1.0f);
    wallFront.model = glm::translate(wallFront.model, glm::vec3(0.0f, height / 2.0f, -depth / 2.0f));
    wallFront.model = glm::rotate(wallFront.model, glm::radians(-90.0f), glm::vec3(1, 0, 0));
    wallFront.model = glm::scale(wallFront.model, glm::vec3(width, 1.0f, height));


    wallBack.model = glm::mat4(1.0f);
    wallBack.model = glm::translate(wallBack.model, glm::vec3(0.0f, height / 2.0f, depth / 2.0f));
    wallBack.model = glm::rotate(wallBack.model, glm::radians(90.0f), glm::vec3(1, 0, 0));
    wallBack.model = glm::scale(wallBack.model, glm::vec3(width, 1.0f, height));


    wallLeft.model = glm::mat4(1.0f);
    wallLeft.model = glm::translate(wallLeft.model, glm::vec3(-width / 2.0f, height / 2.0f, 0.0f));
    wallLeft.model = glm::rotate(wallLeft.model, glm::radians(-90.0f), glm::vec3(0, 0, 1));
    wallLeft.model = glm::scale(wallLeft.model, glm::vec3(height, 1.0f, depth));


    wallRight.model = glm::mat4(1.0f);
    wallRight.model = glm::translate(wallRight.model, glm::vec3(width / 2.0f, height / 2.0f, 0.0f));
    wallRight.model = glm::rotate(wallRight.model, glm::radians(90.0f), glm::vec3(0, 0, 1));
    wallRight.model = glm::scale(wallRight.model, glm::vec3(height, 1.0f, depth));


    floor.texture = loadTexture("textures/floor.jpg");
    ceiling.texture = loadTexture("textures/whiteWall.jpg");
    wallFront.texture = loadTexture("textures/whiteWall.jpg");
    wallBack.texture = loadTexture("textures/whiteWall.jpg");
    wallLeft.texture = loadTexture("textures/whiteWall.jpg");
    wallRight.texture = loadTexture("textures/wall.png");
}



Room::~Room() {
    Face* faces[] = { &floor, &ceiling, &wallFront, &wallBack, &wallLeft, &wallRight };
    for (Face* f : faces) {
        glDeleteVertexArrays(1, &f->VAO);
        glDeleteBuffers(1, &f->VBO);
        glDeleteTextures(1, &f->texture);
    }
}

bool Room::Contains(float x, float z, float margin) const {
    float halfW = width / 2.0f; 
    float halfD = depth / 2.0f;   
    
    return (x >= -halfW + margin) && (x <= halfW)
        && (z >= -halfD + margin) && (z <= halfD - margin);
}


void Room::setupFace(Face& face) {
    glGenVertexArrays(1, &face.VAO);
    glGenBuffers(1, &face.VBO);

    glBindVertexArray(face.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, face.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);

 
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}



unsigned int Room::loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data) {
        GLenum format = GL_RGB;
        if (nrChannels == 1)      format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
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


void Room::drawFace(const Face& face, Shader& shader) {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, face.texture);
    shader.setInt("texture1", 0);

    shader.setMat4("model", face.model);

    glBindVertexArray(face.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}


void Room::Draw(Shader& shader) {
    shader.use();

    drawFace(floor, shader);
    drawFace(ceiling, shader);
    drawFace(wallFront, shader);
    drawFace(wallBack, shader);
    drawFace(wallLeft, shader);
}