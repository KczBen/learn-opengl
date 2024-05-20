#version 330 core
in vec3 customColor;
in vec2 TextureCoord;

uniform sampler2D customTexture;

out vec4 FragColor;

void main() {
   FragColor = texture(customTexture, TextureCoord);
}