#version 330 core

// Type Definitions
struct Material {
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct DirectionalLight {
    vec3 direction;
};

struct SceneLight {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular; 
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
};

// Global Uniforms
layout (std140) uniform uniform_camera_world_position{
    vec3 camera_world_position;
};

// Shader Uniforms
uniform Material material;
uniform SceneLight scenelight;

uniform int active_dirlight_qty;
uniform DirectionalLight dirlight[8];

uniform int active_pointlight_qty;
uniform PointLight pointlight[16];

// Vertex Variables
in vec3 frag_cube_normals;
in vec3 fragment_world_position;

// Output
out vec4 fragment_color;

// Function Definitions
vec3 calc_directional_light_no_texture(DirectionalLight dirlight, 
                                       Material material, 
                                       SceneLight scenelight, 
                                       vec3 normalized_frag_cube_normals, 
                                       vec3 view_direction);

vec3 calc_point_light_no_texture(PointLight pointlight, 
                                 Material material, 
                                 SceneLight scenelight,                       
                                 vec3 normalized_frag_cube_normals, 
                                 vec3 view_direction,
                                 vec3 fragment_world_position);

// Shader
void main() {
    
    vec3 normalized_frag_cube_normals = normalize(frag_cube_normals);
    vec3 view_direction = normalize(camera_world_position - fragment_world_position);

    // Lighting
    vec3 result = vec3(0.0f);

    // Directional
    for(int i = 0; i <= active_dirlight_qty; i++) {
        result += calc_directional_light_no_texture(dirlight[i], material, scenelight, normalized_frag_cube_normals, view_direction);
    }

    // Point
    for(int i = 0; i <= active_pointlight_qty; i++){
        result += calc_point_light_no_texture(pointlight[i], material, scenelight, normalized_frag_cube_normals, view_direction, fragment_world_position);
    }

    fragment_color = vec4(result, 1.0); // set all 4 vector values to 1.0
}

// Function Definitions
vec3 calc_directional_light_no_texture(DirectionalLight dirlight, 
                                       Material material, 
                                       SceneLight scenelight, 
                                       vec3 normalized_frag_cube_normals, 
                                       vec3 view_direction){
    
    vec3 light_direction = normalize(dirlight.direction);

    // Diffuse
    float diffuse_impact = max(dot(normalized_frag_cube_normals, light_direction), 0.0);

    // Specular
    vec3 reflection_direction = reflect(-light_direction, normalized_frag_cube_normals);
    float specular_impact = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);

    // Combine
    vec3 ambient = scenelight.ambient  * material.diffuse;
    vec3 diffuse = scenelight.diffuse  * diffuse_impact * material.diffuse;
    vec3 specular = scenelight.specular * specular_impact * material.specular;

    return (ambient + diffuse + specular);
} 

vec3 calc_point_light_no_texture(PointLight pointlight, 
                                 Material material, 
                                 SceneLight scenelight,                       
                                 vec3 normalized_frag_cube_normals, 
                                 vec3 view_direction,                                 
                                 vec3 fragment_world_position){
    
    vec3 light_direction = normalize(pointlight.position - fragment_world_position);
    
    // Diffuse
    float diffuse_impact = max(dot(normalized_frag_cube_normals, light_direction), 0.0);
    
    // Specular
    vec3 reflection_direction = reflect(-light_direction, normalized_frag_cube_normals);
    float specular_impact = pow(max(dot(view_direction, reflection_direction), 0.0), material.shininess);
    
    // Attenuation
    float distance_to_light = length(pointlight.position - fragment_world_position);
    float attenuation = 1.0 / (pointlight.constant + pointlight.linear * distance_to_light + pointlight.quadratic * (distance_to_light * distance_to_light));    

    // Combine
    vec3 ambient  = scenelight.ambient  * material.diffuse;
    vec3 diffuse  = scenelight.diffuse  * diffuse_impact * material.diffuse;
    vec3 specular = scenelight.specular * specular_impact * material.specular;
   
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
} 