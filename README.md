# 8_cg

컴퓨터 그래픽스 팀프로젝트: 3D 미니 전시관

## 개발 환경
- C++
- OpenGL
- GLFW
- GLAD

## 폴더 구조
- src/: 소스코드
- shaders/: 셰이더 코드
- resources/: 텍스처, 이미지 등 리소스 파일
- docs/: 보고서, 회의록, 발표자료
- record/: 시연 영상 관련 자료

## 작업 방식
1. main 브랜치는 최종본/안정본으로 사용
2. 각자 기능별 브랜치를 만들어 작업
3. 작업 후 Pull Request로 main에 병합

## 브랜치 예시
- feature/camera
- feature/lighting
- feature/objects
- feature/texture
- docs/report


## 조작법
 
### 카메라 이동
| 입력 | 동작 |
|------|------|
| `W` | 앞으로 |
| `S` | 뒤로 |
| `A` | 왼쪽 |
| `D` | 오른쪽 |
| `E` | 위로 |
| `Q` | 아래로 |
 
### 시점 변경
| 입력 | 동작 |
|------|------|
| `마우스 우클릭 + 드래그` | 시점 회전 (Yaw / Pitch) |
| `마우스 스크롤` | 줌 (FOV 1° ~ 45°) |
 
### 종료
| 입력 | 동작 |
|------|------|
| `ESC` | 프로그램 종료 |