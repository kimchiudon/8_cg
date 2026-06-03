#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

#include "Camera.h"
#include "shader.h"
#include "Room.h"
#include "Staircase.h"
#include "InfoPanel.h"
#include "PlanetariumDome.h"
#include "JupiterSystem.h"

Camera camera(glm::vec3(-12.0f, 3.5f, 0.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;


bool firstMouse = true;
float lastX = 800.0f / 2.0f;
float lastY = 600.0f / 2.0f;
bool isRightMousePressed = false;


float floorVertices[] = {
     50.0f, -0.5f,  50.0f,
    -50.0f, -0.5f,  50.0f,
    -50.0f, -0.5f, -50.0f,

     50.0f, -0.5f,  50.0f,
    -50.0f, -0.5f, -50.0f,
     50.0f, -0.5f, -50.0f
};


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        if (action == GLFW_PRESS) {
            isRightMousePressed = true;
            firstMouse = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
        else if (action == GLFW_RELEASE) {
            isRightMousePressed = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
    if (!isRightMousePressed) return;

    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}


void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);


    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        camera.MovementSpeed = 7.5f;
    else
        camera.MovementSpeed = 2.5f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

  
}




int main() {
   
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "3D Mini Gallery - Jupiter", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);


    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    glDisable(GL_CULL_FACE);


    Shader ourShader("shaders/basic.vert", "shaders/basic.frag");          
    Shader roomShader("shaders/room.vert", "shaders/room.frag");           
    Shader jupiterShader("shaders/jupiter.vert", "shaders/jupiter.frag");  

    Room room(40.0f, 12.0f, 11.0f);
    Staircase stairs;

   
    PlanetariumDome dome(44.33f, 0.0f, 25.0f, 20.0f);

    InfoPanel infoPanel(-7.0f, 3.0f, 2.0f);

    InfoPanel jupiterPanel(24.0f, 0.0f, 0.0f, "textures/jupiterInfo.jpg", 90.0f);
    InfoPanel ioPanel(59.9f, 15.6f, 0.0f, "textures/ioInfo.jpg", -135.0f);
    InfoPanel europaPanel(28.8f, 15.6f, 0.0f, "textures/europaInfo.jpg", 135.0f);
    InfoPanel callistoPanel(28.8f, -15.6f, 0.0f, "textures/CallistoInfo.jpg", 45.0f);
    InfoPanel ganymedePanel(59.9f, -15.6f, 0.0f, "textures/ganymedeInfo.jpg", -45.0f);

    unsigned int floorVAO, floorVBO;
    glGenVertexArrays(1, &floorVAO);
    glGenBuffers(1, &floorVBO);

    glBindVertexArray(floorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    struct PanelObstacle {
        float x;
        float z;
        float radius;
    };

    std::vector<PanelObstacle> panelObstacles = {
        { -7.0f,   3.0f, 0.8f },   
        { 24.0f,   0.0f, 0.8f },   
        { 59.9f,  15.6f, 0.8f },   
        { 28.8f,  15.6f, 0.8f },   
        { 28.8f, -15.6f, 0.8f },   
        { 59.9f, -15.6f, 0.8f },   
    };


    auto isWalkable = [&](float x, float z) {
        const float MARGIN = 0.5f;

        
        if (!(room.Contains(x, z, MARGIN) || dome.Contains(x, z, MARGIN)))
            return false;

        
        for (const auto& p : panelObstacles) {
            float dx = x - p.x;
            float dz = z - p.z;

            if (dx * dx + dz * dz < p.radius * p.radius)
                return false;
        }

        return true;
        };

    
    JupiterSystem jupiterSys;

   
    while (!glfwWindowShouldClose(window)) {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glm::vec3 oldPos = camera.Position;
        processInput(window);

        glm::vec3 p = camera.Position;

        if (!isWalkable(p.x, oldPos.z))
            p.x = oldPos.x;

        if (!isWalkable(p.x, p.z))
            p.z = oldPos.z;

        camera.Position.x = p.x;
        camera.Position.z = p.z;

        float floorH = stairs.GetFloorHeightAt(camera.Position.x, camera.Position.z);
        camera.StickToFloor(floorH);

        glClearColor(0.025f, 0.025f, 0.055f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(
            glm::radians(camera.Zoom),
            800.0f / 600.0f,
            0.1f,
            100.0f
        );

        glm::mat4 view = camera.GetViewMatrix();

        roomShader.use();

        roomShader.setMat4("projection", projection);
        roomShader.setMat4("view", view);
        roomShader.setVec3("viewPos", camera.Position);

        roomShader.setFloat("ambientStrength", 0.055f);

 
        roomShader.setVec3("entranceLightPos", glm::vec3(-8.0f, 5.0f, 0.0f));
        roomShader.setVec3("entranceLightColor", glm::vec3(0.95f, 0.72f, 0.45f));

     
        roomShader.setVec3("domeLightPos", glm::vec3(44.33f, 14.0f, 0.0f));
        roomShader.setVec3("domeLightColor", glm::vec3(0.18f, 0.24f, 0.48f));

       
        roomShader.setVec3("panelLightPositions[0]", glm::vec3(-7.0f, 3.0f, 3.0f));      
        roomShader.setVec3("panelLightPositions[1]", glm::vec3(24.0f, 2.4f, 0.0f));      
        roomShader.setVec3("panelLightPositions[2]", glm::vec3(59.9f, 2.4f, 15.6f));   
        roomShader.setVec3("panelLightPositions[3]", glm::vec3(28.8f, 2.4f, 15.6f));   
        roomShader.setVec3("panelLightPositions[4]", glm::vec3(28.8f, 2.4f, -15.6f));    
        roomShader.setVec3("panelLightPositions[5]", glm::vec3(59.9f, 2.4f, -15.6f));    

        
        roomShader.setVec3("panelLightColor", glm::vec3(1.0f, 0.82f, 0.52f));

      
        roomShader.setFloat("panelLightStrength", 1.15f);

        room.Draw(roomShader);
        stairs.Draw(roomShader);
        dome.Draw(roomShader);

        infoPanel.Draw(roomShader);

        jupiterPanel.Draw(roomShader);
        ioPanel.Draw(roomShader);
        europaPanel.Draw(roomShader);
        callistoPanel.Draw(roomShader);
        ganymedePanel.Draw(roomShader);

      
        float time = static_cast<float>(glfwGetTime());

        jupiterShader.use();

        jupiterShader.setMat4("projection", projection);
        jupiterShader.setMat4("view", view);

        
        jupiterShader.setVec3("lightDir", glm::vec3(-0.2f, -0.7f, -0.25f));
        jupiterShader.setVec3("lightColor", glm::vec3(1.05f, 1.03f, 0.95f));

        
        jupiterShader.setFloat("ambientStrength", 0.12f);

      
        jupiterShader.setFloat("emissiveStrength", 0.35f);

        jupiterSys.Draw(
            jupiterShader,
            camera,
            time,
            glm::vec3(44.33f, 5.0f, 0.0f)
        );

       
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

  
    glDeleteVertexArrays(1, &floorVAO);
    glDeleteBuffers(1, &floorVBO);

    glfwTerminate();
    return 0;
}