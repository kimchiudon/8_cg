#ifndef LIGHT_H
#define LIGHT_H

#include "../Dependencies/include/glm/glm.hpp"

struct DirectionalLight
{
    glm::vec3 direction;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

struct SpotLight
{
    glm::vec3 position;
    glm::vec3 direction;

    float cutOff;
    float outerCutOff#ifndef LIGHT_H
#define LIGHT_H

#include "glm/glm.hpp"

        struct DirectionalLight
    {
        glm::vec3 direction;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };

    struct SpotLight
    {
        glm::vec3 position;
        glm::vec3 direction;

        float cutOff;
        float outerCutOff;

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;

        float constant;
        float linear;
        float quadratic;
    };

#endif

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

#endif#pragma once
