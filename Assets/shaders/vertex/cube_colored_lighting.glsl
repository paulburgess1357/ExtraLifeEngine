#version 330 core

layout (location = 0) in vec3 cube_position;
layout (location = 1) in vec3 cube_normals;

// Global uniforms
layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

uniform mat4 model_matrix;
uniform mat3 normal_matrix;

out vec3 frag_cube_normals;
out vec3 fragment_world_position;

void main(){	
    fragment_world_position = vec3(model_matrix * vec4(cube_position, 1.0)); // World Space
    gl_Position = projection_matrix * view_matrix * vec4(fragment_world_position, 1.0);
    frag_cube_normals = normal_matrix * cube_normals; // World Space (World space or view space here is impacted by how the normal matrix is made (in render system))
}