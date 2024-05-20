#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextureCoord;

out vec3 customColor;
out vec2 TextureCoord;

void main() {
   gl_Position = vec4(aPos, 1.0);
   customColor = aColor;
   TextureCoord = aTextureCoord;
}