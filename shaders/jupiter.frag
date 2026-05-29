#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D diffuse0;   // Draw에서 설정하는 샘플러 이름과 동일

void main() {
    FragColor = texture(diffuse0, TexCoord);
}