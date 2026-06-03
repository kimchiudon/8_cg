#version 330 core

in vec3 FragPos; 

out vec4 FragColor;

void main() {
    
    float gridSize = 1.0; 
    float thickness = 0.05; 

    
    float xPos = fract(FragPos.x / gridSize);
    float zPos = fract(FragPos.z / gridSize);

   
    if(xPos < thickness || zPos < thickness) {
        FragColor = vec4(1.0, 1.0, 1.0, 1.0); // ÇÏ¾á»ö ¼±
    } else {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0); // ÁÖÈ²»ö ¹Ù´Ú
    }
}