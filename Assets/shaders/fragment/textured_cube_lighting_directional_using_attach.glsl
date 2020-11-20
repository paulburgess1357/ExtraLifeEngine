#version 330 core

struct Material {
    sampler2D diffuse;
    sampler2D specular;    
    float shininess;
}; 

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

// Global uniforms
layout (std140) uniform uniform_camera_world_position{
    vec3 camera_world_position;
};

uniform Material material;

uniform int active_dirlight_qty;
uniform DirectionalLight dirlight[32];

in vec3 frag_cube_normals;
in vec3 fragment_world_position;
in vec2 fragment_tex_coords;

out vec4 fragment_color;

vec3 calc_directional_light(DirectionalLight dirlight, Material material, vec3 normalized_frag_cube_normals, vec3 view_direction);

void main() {
    
    vec3 normalized_frag_cube_normals = normalize(frag_cube_normals);
    vec3 view_direction = normalize(camera_world_position - fragment_world_position);

    vec3 result = vec3(0.0f);
    for(int i = 0; i <= active_dirlight_qty; i++) {
        result += calc_directional_light(dirlight[i], material, normalized_frag_cube_normals, view_direction);
    }
    
    fragment_color = vec4(result, 1.0);
};






vec3 calc_directional_light(DirectionalLight dirlight, Material material, vec3 normalized_frag_cube_normals, vec3 view_direction){
    
    vec3 light_direction = normalize(dirlight.direction);

    // Diffuse
    float diffuse_impact = max(dot(normalized_frag_cube_normals, light_direction), 0.0);

    // Specular
    vec3 reflection_direction = reflect(-light_direction, normalized_frag_cube_normals);
    float specular_impact = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);

    // Combine
    vec3 ambient = dirlight.ambient  * vec3(texture(material.diffuse, fragment_tex_coords));
    vec3 diffuse = dirlight.diffuse  * diffuse_impact * vec3(texture(material.diffuse, fragment_tex_coords));
    vec3 specular = dirlight.specular * specular_impact * vec3(texture(material.specular, fragment_tex_coords));

    return (ambient + diffuse + specular);
}  