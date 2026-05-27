#include "Room.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../Dependencies/include/stb/stb_image.h"

#include "../Dependencies/include/glm/gtc/matrix_transform.hpp"
#include <iostream>


static float floorVertices[] = {
    // 위치                   노멀                  UV
    // 삼각형 1: A → D → C
    -0.5f, 0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // A
     0.5f, 0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   5.0f, 0.0f,  // D
     0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   5.0f, 5.0f,  // C

     // 삼각형 2: A → C → B
     -0.5f, 0.0f,  0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,  // A
      0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   5.0f, 5.0f,  // C
     -0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 5.0f,  // B
};


// ==========================================
// 생성자
// ==========================================
Room::Room(float w, float d, float h)
    : width(w), depth(d), height(h),         // 멤버 초기화 리스트
    floorVAO(0), floorVBO(0), floorTexture(0)
{
    setupFloor();                             // VAO/VBO 만들기
    floorTexture = loadTexture("textures/floor.jpg");  // 텍스처 로딩
}


// ==========================================
// 소멸자: GPU 리소스 반환
// ==========================================
Room::~Room() {
    glDeleteVertexArrays(1, &floorVAO);
    glDeleteBuffers(1, &floorVBO);
    glDeleteTextures(1, &floorTexture);
}


// ==========================================
// setupFloor: 바닥 VAO/VBO 생성 + attribute 등록
// ==========================================
void Room::setupFloor() {
    // 1. VAO와 VBO 생성
    glGenVertexArrays(1, &floorVAO);
    glGenBuffers(1, &floorVBO);

    // 2. VAO 활성화
    glBindVertexArray(floorVAO);

    // 3. VBO에 정점 데이터 업로드
    glBindBuffer(GL_ARRAY_BUFFER, floorVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVertices), floorVertices, GL_STATIC_DRAW);

    // 4. attribute 등록 — "VBO 데이터를 어떻게 해석할지" VAO에 설명
    //    한 정점 = 8 floats = 32 bytes (stride)

    // location = 0 : position (vec3), 정점 시작 위치(offset=0)
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // location = 1 : normal (vec3), offset = 3 floats
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // location = 2 : texcoord (vec2), offset = 6 floats
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
        8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // 5. 정리 — VAO 바인딩 해제 (다른 코드의 실수 방지)
    glBindVertexArray(0);
}


// ==========================================
// loadTexture: 이미지 파일을 GPU 텍스처로 로딩
//   - stb_image로 디코딩
//   - OpenGL 텍스처 객체 생성 후 데이터 업로드
//   - 텍스처 ID 반환
// ==========================================
unsigned int Room::loadTexture(const char* path) {
    unsigned int textureID;
    glGenTextures(1, &textureID);

    // 이미지 파일 디코딩
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);  // OpenGL UV 좌표계에 맞게 상하 뒤집기
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    if (data) {
        // 채널 수에 따라 포맷 결정 (3=RGB, 4=RGBA)
        GLenum format = GL_RGB;
        if (nrChannels == 1)      format = GL_RED;
        else if (nrChannels == 3) format = GL_RGB;
        else if (nrChannels == 4) format = GL_RGBA;

        // GPU에 이미지 업로드
        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0,
            format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);   // 멀리서 볼 때 부드럽게 보이도록 밉맵 생성

        // 텍스처 옵션 설정
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);    // UV가 1을 넘으면 반복
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);  // 축소 필터링
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);                // 확대 필터링
    }
    else {
        std::cout << "Failed to load texture: " << path << std::endl;
    }

    stbi_image_free(data);   // 메모리 해제 (GPU에 올렸으니 CPU 쪽은 필요 없음)
    return textureID;
}


// ==========================================
// Draw: 매 프레임 호출됨 — 바닥을 그림
// ==========================================
void Room::Draw(Shader& shader) {
    shader.use();

    // 텍스처를 슬롯 0에 바인딩하고, 셰이더의 texture1 uniform에 슬롯 번호 전달
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, floorTexture);
    shader.setInt("texture1", 0);

    // 바닥의 model 행렬: 단위 바닥(-0.5~0.5)을 실제 크기로 늘림
    //   scale(width, 1, depth) — Y축은 평면이라 1
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(width, 1.0f, depth));
    shader.setMat4("model", model);

    // VAO 바인딩 후 그리기
    glBindVertexArray(floorVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);   // 정점 6개 = 삼각형 2개
    glBindVertexArray(0);
}