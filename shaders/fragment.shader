#version 330 core
in vec2 TextureCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixture;

out vec4 FragColor;

void main() {
   FragColor = mix(texture(texture1, TextureCoord), texture(texture2, TextureCoord), mixture);
}