#version 330 core

layout (location = 0) in vec3 in_cube_position;

// Global uniforms
layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

uniform mat4 model_matrix;

void main(){
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(in_cube_position, 1.0);
}