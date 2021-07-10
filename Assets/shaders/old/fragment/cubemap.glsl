#version 330 core
// Fragment Shader

out vec4 frag_color;
in vec3 fragment_tex_coords;
uniform samplerCube cubemap;

void main(){    
    frag_color = texture(cubemap, fragment_tex_coords);
}