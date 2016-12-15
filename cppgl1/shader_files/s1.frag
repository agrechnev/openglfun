#version 330 core
in vec3 ourColor;
in vec2 texCoord;

out vec4 color;

// Load 2 textures
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;
uniform float mixing;

void main(){
  color = mix (texture(ourTexture1, texCoord), texture(ourTexture2, texCoord), mixing);
}