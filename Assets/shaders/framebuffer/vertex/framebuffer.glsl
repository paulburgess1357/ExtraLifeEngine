#version 330 core
// Framebuffer Vertex Shader

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main(){
    // The z component for depth testing is from: xyz/w.  The z component from
    // the resulting division is the depth value.  Since we haev z set as 0,
    // 0.0/1.0 = 0.  Therefore the depth value is 0 which renders in front 
    // of everything else.
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
    TexCoords = aTexCoords;
} 