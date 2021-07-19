#version 330 core
// Vertex Shader
layout (location = 0) in vec3 cube_position;
layout (location = 1) in vec3 cube_normals;

// ============ Global uniforms ============
layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

// ============ Shader Uniforms ============
// Lights
uniform vec3 light_position_in_world;
uniform vec3 light_intensity;

// Colors
uniform vec3 diffuse_color;

// Matrices
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

// Output
out vec3 calculated_frag_color;

// ================== Main =================
void main(){	

    // Convert light position to view space (eye/camera space)
    vec3 light_position_eye = vec3(view_matrix * vec4(light_position_in_world, 1.0));

    // Convert cube normals and cube position to view space (eye/camera space)
    // Note that the model matrix has already been multiplied by the view matrix by the time its sent to the shader
    vec3 cube_normals_eye = normalize(vec3(normal_matrix * cube_normals));
    vec3 cube_position_eye = vec3(view_matrix * model_matrix * vec4(cube_position, 1.0));
    vec3 light_direction_from_surface_to_lightsource = normalize(light_position_eye - cube_position_eye);

    // Diffuse shading equation
    // Note that ins the max(dot()) formula, both variables are unit vectors (normalized)
    // Therefore, the lighting is impacted by the angle (so vector magnitude as no impact on dot product)
    // I.e. the dot product of 2 unit vectors equals the cos of the angle.
    calculated_frag_color = diffuse_color * light_intensity * max(dot(light_direction_from_surface_to_lightsource, cube_normals_eye), 0.0);

    // Convert vertex position to clip space for fragment shader
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(cube_position, 1.0);
}