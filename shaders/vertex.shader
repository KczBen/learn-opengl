#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

uniform float offset;
out vec3 customColor;

void main() {
   vec3 offsetPos = vec3(aPos.x+offset, aPos.y, aPos.z);
   gl_Position = vec4(offsetPos, 1.0);
   customColor = aColor;
}