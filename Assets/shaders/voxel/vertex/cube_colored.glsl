#version 330 core
layout (location = 0) in vec4 cube_position;

// Global uniforms
layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

uniform mat4 model_matrix;
out vec3 fragment_world_position;
out vec4 texcoord;

void main(){	
    fragment_world_position = vec3(model_matrix * vec4(cube_position.xyz, 1.0)); // World Space
    gl_Position = projection_matrix * view_matrix * vec4(fragment_world_position, 1.0);   
    texcoord = cube_position;
}