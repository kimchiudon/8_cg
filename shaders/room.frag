#version 330 core

out vec4 FragColor;


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;


uniform sampler2D texture1;


uniform vec3 viewPos;


uniform float ambientStrength;


uniform vec3 entranceLightPos;
uniform vec3 entranceLightColor;

uniform vec3 domeLightPos;
uniform vec3 domeLightColor;


uniform vec3 panelLightPositions[6];
uniform vec3 panelLightColor;
uniform float panelLightStrength;

vec3 CalcPointLight(vec3 lightPos, vec3 lightColor, float strength, vec3 norm, vec3 fragPos)
{
    vec3 lightDir = normalize(lightPos - fragPos);

    float diff = max(dot(norm, lightDir), 0.0);

    float distance = length(lightPos - fragPos);
    float attenuation = 1.0 / (1.0 + 0.12 * distance + 0.035 * distance * distance);

    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 24.0);

    vec3 diffuse = diff * lightColor * strength;
    vec3 specular = spec * lightColor * 0.18 * strength;

    return (diffuse + specular) * attenuation;
}

void main()
{
    vec3 objectColor = texture(texture1, TexCoord).rgb;
    vec3 norm = normalize(Normal);

    
    vec3 ambient = ambientStrength * objectColor;

  
    vec3 entranceLight = CalcPointLight(
        entranceLightPos,
        entranceLightColor,
        1.25,
        norm,
        FragPos
    );

    
    vec3 domeLight = CalcPointLight(
        domeLightPos,
        domeLightColor,
        0.85,
        norm,
        FragPos
    );

    
    vec3 panelLight = vec3(0.0);

    for (int i = 0; i < 6; i++)
    {
        panelLight += CalcPointLight(
            panelLightPositions[i],
            panelLightColor,
            panelLightStrength,
            norm,
            FragPos
        );
    }

    vec3 lighting = ambient + entranceLight + domeLight + panelLight;

    vec3 result = lighting * objectColor;

    result = clamp(result, 0.0, 1.0);

    FragColor = vec4(result, 1.0);
}