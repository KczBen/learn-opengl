#version 330 core

struct Material {
	vec3 ambient;
    vec3 diffuseColor;
    vec3 specularColor;
	float shininess;
};

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;

out vec4 FragColor;

void main() {
    // Ambient light
    vec3 ambientLight = light.ambient * material.ambient;

    // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseLight = light.diffuse * (diff * material.diffuseColor);

    // Specular light
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularLight = light.specular * (spec * material.specularColor);

    vec3 result = ambientLight + diffuseLight + specularLight;
    FragColor = vec4(result, 1.0);
}