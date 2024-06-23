#version 330 core

struct Material {
	sampler2D diffuse;
    sampler2D specular;
	float shininess;
};

struct Light {
    // vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;
uniform Material material;

in vec3 Normal;
in vec3 FragPos;
in vec3 LightPos;
in vec2 TextureCoords;

out vec4 FragColor;

void main() {
    // Ambient light
    vec3 ambientLight = light.ambient * vec3(texture(material.diffuse, TextureCoords));

    // Diffuse light
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuseLight = light.diffuse * diff * vec3(texture(material.diffuse, TextureCoords));

    // Specular light
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specularLight = light.specular * spec * vec3(texture(material.specular, TextureCoords));

    vec3 result = ambientLight + diffuseLight + specularLight;
    FragColor = vec4(result, 1.0);
}