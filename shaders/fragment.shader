#version 330 core

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void main() {
    float ambientStrength = 0.1;
    vec3 ambientLight = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseLight = diff * lightColor;

    vec3 result = (ambientLight + diffuseLight) * objectColor;
    FragColor = vec4(result, 1.0);
}