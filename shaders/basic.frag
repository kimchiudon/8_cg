#version 330 core

// 버텍스 쉐이더에서 보낸 월드 좌표와 법선 벡터를 받습니다.
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

// 방향광 구조체입니다.
// 전시관 전체에 은은하게 들어오는 빛을 표현할 때 사용합니다.
struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// 스포트라이트 구조체입니다.
// 목성 전시물 위를 집중적으로 비추는 조명을 표현할 때 사용합니다.
struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float outerCutOff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

// main.cpp에서 전달받을 조명 값들입니다.
uniform DirectionalLight dirLight;
uniform SpotLight spotLight;

// 카메라 위치, 객체 색상, 반짝임 정도입니다.
uniform vec3 viewPos;
uniform vec3 objectColor;
uniform float shininess;

// 방향광 계산 함수입니다.
vec3 CalcDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    // 빛이 들어오는 방향을 계산합니다.
    vec3 lightDir = normalize(-light.direction);

    // diffuse는 표면이 빛을 얼마나 정면으로 받는지 계산합니다.
    float diff = max(dot(normal, lightDir), 0.0);

    // specular는 카메라 방향으로 반사되는 하이라이트를 계산합니다.
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // ambient: 기본 밝기, diffuse: 직접 빛, specular: 반사광
    vec3 ambient = light.ambient * objectColor;
    vec3 diffuse = light.diffuse * diff * objectColor;
    vec3 specular = light.specular * spec;

    return ambient + diffuse + specular;
}

// 스포트라이트 계산 함수입니다.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    // 현재 픽셀에서 조명 위치를 향하는 방향입니다.
    vec3 lightDir = normalize(light.position - fragPos);

    // 표면이 스포트라이트를 얼마나 받는지 계산합니다.
    float diff = max(dot(normal, lightDir), 0.0);

    // 카메라 방향으로 반사되는 하이라이트를 계산합니다.
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

    // 조명과 픽셀 사이의 거리에 따른 빛 감소를 계산합니다.
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (
        light.constant +
        light.linear * distance +
        light.quadratic * distance * distance
    );

    // 스포트라이트 원뿔 안쪽인지 계산합니다.
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // ambient: 기본 밝기, diffuse: 직접 빛, specular: 반사광
    vec3 ambient = light.ambient * objectColor;
    vec3 diffuse = light.diffuse * diff * objectColor;
    vec3 specular = light.specular * spec;

    // 거리 감소와 스포트라이트 강도를 적용합니다.
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return ambient + diffuse + specular;
}

void main()
{
    // 법선 벡터와 카메라 방향을 정규화합니다.
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // 방향광과 스포트라이트를 모두 적용합니다.
    vec3 result = CalcDirectionalLight(dirLight, norm, viewDir);
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

    FragColor = vec4(result, 1.0);
}