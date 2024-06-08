#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 FragColor;

void main() {
    // Ambient light
    float ambientStrength = 0.1;
    vec3 ambientLight = ambientStrength * lightColor;

    // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseLight = diff * lightColor;

    // Specular light
    float specularStrength = 0.5;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specularLight = specularStrength * spec * lightColor;

    vec3 result = (ambientLight + diffuseLight + specularLight) * objectColor;
    FragColor = vec4(result, 1.0);
}