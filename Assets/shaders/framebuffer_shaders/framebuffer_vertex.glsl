#version 330 core
// Framebuffer Vertex Shader

layout (location = 0) in vec2 quad_position;
layout (location = 1) in vec2 quad_tex_coords;

out vec2 fragment_tex_coords;

void main(){
    // The z component for depth testing is from: xyz/w.  The z component from
    // the resulting division is the depth value.  Since we haev z set as 0,
    // 0.0/1.0 = 0.  Therefore the depth value is 0 which renders in front 
    // of everything else.
    gl_Position = vec4(quad_position.x, quad_position.y, 0.0, 1.0); 
    fragment_tex_coords = quad_tex_coords;
} 