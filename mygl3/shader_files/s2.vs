#version 330 core
layout (location=0) in vec3 pos;
layout (location=1) in vec3 color;
uniform float xOffset;
uniform float yOffset;
out vec3 ourColor;
void main(){
  gl_Position=vec4(pos.x+xOffset, -pos.y+yOffset, pos.z, 1.0);
  ourColor=color;
}