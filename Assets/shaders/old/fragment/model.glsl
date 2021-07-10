#version 330 core
#define MAXIMUM_DIR_LIGHTS 2
#define MAXIMUM_POINT_LIGHTS 6
// Fragment Shader

struct DiffuseMaterial {
    sampler2D m_sampler;
};

struct SpecularMaterial {
    sampler2D m_sampler;
    float m_shininess;
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
// uniform int active_diffuse_qty;
uniform DiffuseMaterial diffuse_material;

// uniform int active_specular_qty;
uniform SpecularMaterial specular_material;

uniform SceneLight scenelight;

uniform int active_dirlight_qty; // Set to -1 during shader initialization
uniform int active_pointlight_qty; // Set to -1 during shader initialization

uniform DirectionalLight dirlight[MAXIMUM_DIR_LIGHTS];
uniform PointLight pointlight[MAXIMUM_POINT_LIGHTS];

// Vertex Variables
in vec3 frag_model_normals;
in vec3 fragment_world_position;
in vec2 fragment_tex_coords;

// Output
out vec4 fragment_color;

// Function Definitions
vec3 calc_directional_light(DirectionalLight dirlight, 
                            DiffuseMaterial diffuse_material,
                            SpecularMaterial specular_material,
                            SceneLight scenelight, 
                            vec3 normalized_frag_model_normals, 
                            vec3 view_direction, 
                            vec2 fragment_tex_coords);

vec3 calc_point_light(PointLight pointlight, 
                      DiffuseMaterial diffuse_material,
                      SpecularMaterial specular_material,
                      SceneLight scenelight,                       
                      vec3 normalized_frag_model_normals, 
                      vec3 view_direction, 
                      vec2 fragment_tex_coords,
                      vec3 fragment_position);

// Shader
void main() {
    
    vec3 normalized_frag_model_normals = normalize(frag_model_normals);
    vec3 view_direction = normalize(camera_world_position - fragment_world_position);

    // Lighting
    vec3 result = vec3(0.0f);
    
    // Directional
    for(int i = 0; i <= active_dirlight_qty; i++) {
        result += calc_directional_light(dirlight[i], diffuse_material, specular_material, scenelight, normalized_frag_model_normals, view_direction, fragment_tex_coords);
    }

    // Point (active pointlight qty set to -1 during shader compilation)
    for(int i = 0; i <= active_pointlight_qty; i++){
        result += calc_point_light(pointlight[i], diffuse_material, specular_material, scenelight, normalized_frag_model_normals, view_direction, fragment_tex_coords, fragment_world_position);
    }

    if(result.x == 0.0f && result.y==0.0f && result.z==0.0f){
       result = scenelight.ambient * vec3(texture(diffuse_material.m_sampler, fragment_tex_coords)); 
    }
    
    fragment_color = vec4(result, 1.0);
};

// Function Definitions
vec3 calc_directional_light(DirectionalLight dirlight, 
                            DiffuseMaterial diffuse_material,
                            SpecularMaterial specular_material,
                            SceneLight scenelight, 
                            vec3 normalized_frag_model_normals, 
                            vec3 view_direction, 
                            vec2 fragment_tex_coords){
    
    vec3 light_direction = normalize(dirlight.direction);
    vec3 halfway_btwn_view_and_light_dir = normalize(light_direction + view_direction);

    // Ambient
    vec3 ambient = scenelight.ambient * vec3(texture(diffuse_material.m_sampler, fragment_tex_coords));

    // Diffuse
    float diffuse_impact = max(dot(normalized_frag_model_normals, light_direction), 0.0);
    vec3 diffuse = scenelight.diffuse * diffuse_impact * vec3(texture(diffuse_material.m_sampler, fragment_tex_coords));

    // Specular
    float specular_impact = pow(max(dot(normalized_frag_model_normals, halfway_btwn_view_and_light_dir), 0.0), specular_material.m_shininess);
    vec3 specular = scenelight.specular * specular_impact * vec3(texture(specular_material.m_sampler, fragment_tex_coords));
            
    return (ambient + diffuse + specular);
}  

vec3 calc_point_light(PointLight pointlight, 
                      DiffuseMaterial diffuse_material,
                      SpecularMaterial specular_material,
                      SceneLight scenelight,                       
                      vec3 normalized_frag_model_normals, 
                      vec3 view_direction, 
                      vec2 fragment_tex_coords,
                      vec3 fragment_position){
    
    vec3 light_direction = normalize(pointlight.position - fragment_position);
    vec3 halfway_btwn_view_and_light_dir = normalize(light_direction + view_direction);
    
    // Ambient
    vec3 ambient  = scenelight.ambient * vec3(texture(diffuse_material.m_sampler, fragment_tex_coords));

    // Diffuse
    float diffuse_impact = max(dot(normalized_frag_model_normals, light_direction), 0.0);
    vec3 diffuse = scenelight.diffuse * diffuse_impact * vec3(texture(diffuse_material.m_sampler, fragment_tex_coords));

    // Specular
    float specular_impact = pow(max(dot(normalized_frag_model_normals, halfway_btwn_view_and_light_dir), 0.0), specular_material.m_shininess);
    vec3 specular = scenelight.specular * specular_impact * vec3(texture(specular_material.m_sampler, fragment_tex_coords));
    
    // Attenuation
    float distance_to_light = length(pointlight.position - fragment_position);
    float attenuation = 1.0 / (pointlight.constant + pointlight.linear * distance_to_light + pointlight.quadratic * (distance_to_light * distance_to_light));    
    
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
} 