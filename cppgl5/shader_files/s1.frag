#version 330 core
in vec2 texCoord;

out vec4 color;

// Load 2 textures
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main(){
  color = mix (texture(ourTexture1, texCoord), texture(ourTexture2, texCoord), 0.2);
}
