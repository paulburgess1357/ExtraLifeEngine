#version 330 core
// Textured cube shader (no lighting)

layout (location = 0) in vec3 in_cube_position;
layout (location = 1) in vec2 in_texture_coords;

// Global uniforms
layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

uniform mat4 model_matrix;
uniform mat3 normal_matrix;

out vec2 tex_coords;

void main(){
    tex_coords = in_texture_coords;  
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_cube_position, 1.0); // View Space
}