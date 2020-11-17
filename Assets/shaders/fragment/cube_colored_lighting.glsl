#version 330 core

in vec3 frag_cube_normals;
in vec3 fragment_world_position;

// Global uniforms
layout (std140) uniform uniform_camera_world_position{
    vec3 camera_world_position;
};

uniform vec3 cube_color;
uniform vec3 light_color;
uniform vec3 light_world_position;

out vec4 fragment_color;

void main() {
    
    // Ambient
    float ambient_str = 0.3;
    vec3 ambient_color = ambient_str * light_color;

    // Diffuse
    vec3 normalized_frag_cube_normals = normalize(frag_cube_normals);
    vec3 light_direction = normalize(light_world_position - fragment_world_position);
    float diffuse_impact = max(dot(normalized_frag_cube_normals, light_direction), 0.0);
    vec3 diffuse_color = diffuse_impact * light_color;

    // Specular
    float specular_str = 0.5;
    vec3 view_direction = normalize(camera_world_position - fragment_world_position);
    vec3 reflection_direction = reflect(-light_direction, normalized_frag_cube_normals);
    float specular_impact = pow(max(dot(view_direction, reflection_direction), 0.0), 32);
    vec3 specular_color = specular_str * specular_impact * light_color;

    vec3 result = (ambient_color + diffuse_color + specular_color) * cube_color;
    fragment_color = vec4(result, 1.0); // set all 4 vector values to 1.0
}