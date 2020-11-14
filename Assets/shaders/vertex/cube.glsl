#version 330 core

layout (location = 0) in vec3 in_cube_position;

// Global uniforms
layout (std140) uniform uniform_matrices {
    mat4 projection;
    mat4 view;
};

uniform mat4 model;

void main(){
	gl_Position = projection * view * model * vec4(in_cube_position, 1.0);
}