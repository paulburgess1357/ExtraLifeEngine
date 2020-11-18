#version 330 core

in vec3 frag_cube_normals;
in vec3 fragment_world_position;
in vec2 fragment_tex_coords;

// Global uniforms
layout (std140) uniform uniform_camera_world_position{
    vec3 camera_world_position;
};

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct Light {
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Material material;
uniform Light light;

out vec4 fragment_color;

void main() {
    
    // Ambient
    vec3 ambient_color = light.ambient * texture(material.diffuse, fragment_tex_coords).rgb;

    // Diffuse
    vec3 normalized_frag_cube_normals = normalize(frag_cube_normals);
    vec3 light_direction = normalize(light.position - fragment_world_position);
    float diffuse_impact = max(dot(normalized_frag_cube_normals, light_direction), 0.0);
    vec3 diffuse_color = light.diffuse * diffuse_impact * texture(material.diffuse, fragment_tex_coords).rgb; 

    // Specular
    vec3 view_direction = normalize(camera_world_position - fragment_world_position);
    vec3 reflection_direction = reflect(-light_direction, normalized_frag_cube_normals);
    float specular_impact = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
    vec3 specular_color = light.specular * specular_impact * texture(material.specular, fragment_tex_coords).rgb; 

    vec3 result = ambient_color + diffuse_color + specular_color;
    fragment_color = vec4(result, 1.0); // set all 4 vector values to 1.0
}