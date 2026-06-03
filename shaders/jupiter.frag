#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture1;

uniform vec3 lightDir;
uniform vec3 lightColor;
uniform float ambientStrength;
uniform float emissiveStrength;

void main()
{
    vec3 objectColor = texture(texture1, TexCoord).rgb;
    vec3 norm = normalize(Normal);

    vec3 ambient = ambientStrength * objectColor;

    vec3 dir = normalize(-lightDir);
    float diff = max(dot(norm, dir), 0.0);
    vec3 diffuse = diff * lightColor * objectColor;

    vec3 emissive = emissiveStrength * objectColor;

    vec3 result = ambient + diffuse + emissive;

    result = result * 1.08;

  
    result = clamp(result, 0.0, 1.0);

    FragColor = vec4(result, 1.0);
}