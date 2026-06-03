#pragma once
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glad/glad.h>
#include "shader.h"
#include "Camera.h"

struct JupiterVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texUV;
};


struct Planet {
    std::string name;
    float size;
    glm::mat4 axialTilt;
    float rotationSpeed;
    float rotationPhase;
    float orbitRadius;
    glm::mat4 orbitRotation;
    float orbitSpeed;
    float orbitPhase;
    glm::vec4 orbitColor;
    unsigned int diffuseTexID; 
    unsigned int specularTexID;
};

class JupiterSystem {
public:
    JupiterSystem();
    ~JupiterSystem();

    void Draw(Shader& shader, Camera& camera, float time, glm::vec3 centerPos);

private:
    std::vector<Planet> planets;

    unsigned int sphereVAO, sphereVBO, sphereEBO;
    int sphereIndexCount;

    unsigned int orbitVAO, orbitVBO, orbitEBO;
    int orbitIndexCount;

    void setupSphere(float radius, int thetaCount, int phiCount);
    void setupOrbit(float radius, int segmentCount);
    unsigned int loadTexture(const char* path);
};