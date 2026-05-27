#ifndef ROOM_H
#define ROOM_H

#include <glad/glad.h>
#include "../Dependencies/include/glm/glm.hpp"
#include "shader.h"

// ==========================================
// Room 클래스
// - 전시관 내부 공간(바닥/벽/천장)을 캡슐화
// - 외부에서는 Draw(shader) 한 줄만 호출하면 됨
// ==========================================
class Room {
public:
    // 생성자: 방의 크기를 받음
    //   width  : X축 길이 (가로)
    //   depth  : Z축 길이 (세로)
    //   height : Y축 길이 (높이, 천장 만들 때 사용)
    Room(float width, float depth, float height);

    // 소멸자: VAO/VBO/Texture 등 GPU 리소스 정리
    ~Room();

    // 외부에 노출되는 유일한 함수
    // main.cpp에서는 room.Draw(shader) 한 줄만 호출하면 됨
    void Draw(Shader& shader);

private:
    // 방 크기 (소멸자/Draw에서 참조하기 위해 멤버로 저장)
    float width;
    float depth;
    float height;

    // 바닥용 GPU 핸들 (OpenGL 객체의 번호표)
    unsigned int floorVAO;
    unsigned int floorVBO;
    unsigned int floorTexture;

    // 내부 헬퍼 함수
    void setupFloor();                            // 바닥 VAO/VBO 생성
    unsigned int loadTexture(const char* path);   // 이미지 파일을 GPU 텍스처로 로딩
};

#endif