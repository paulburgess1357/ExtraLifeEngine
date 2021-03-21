#version 330 core
#define MAXIMUM_DIR_LIGHTS 2
#define MAXIMUM_POINT_LIGHTS 6

// Voxel

struct DiffuseMaterial {
    vec3 m_sampler;
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
uniform DiffuseMaterial diffuse_material;
uniform SceneLight scenelight;

uniform int active_dirlight_qty; // Set to -1 during shader initialization
uniform DirectionalLight dirlight[MAXIMUM_DIR_LIGHTS];

uniform int active_pointlight_qty; // Set to -1 during shader initialization
uniform PointLight pointlight[MAXIMUM_POINT_LIGHTS];

// Vertex Variables
in vec3 frag_cube_normals;
in vec3 fragment_world_position;
in float frag_color_type_test;

// Output
out vec4 fragment_color;

// Function Definitions
vec3 calc_directional_light_no_texture(DirectionalLight dirlight, 
                                       DiffuseMaterial diffuse_material,
                                       SceneLight scenelight, 
                                       vec3 normalized_frag_cube_normals, 
                                       vec3 view_direction);

vec3 calc_point_light_no_texture(PointLight pointlight, 
                                 DiffuseMaterial diffuse_material,
                                 SceneLight scenelight,                       
                                 vec3 normalized_frag_cube_normals, 
                                 vec3 view_direction,
                                 vec3 fragment_position);

// Shader
void main() {
    
    vec3 normalized_frag_cube_normals = normalize(frag_cube_normals);
    vec3 view_direction = normalize(camera_world_position - fragment_world_position);

    // Temp for testing (diffuse_material in the functions has been replaced by diffuse_material_temp for testing)
    DiffuseMaterial diffuse_material_temp;
    
    float r = 0;
    float g = 0;
    float b = 0;

    if(frag_color_type_test <= 1.1f){
        r = 0;
        g = 1;
        b = 0;
    } else if(frag_color_type_test <= 2.1f) {
        r = 1;
        g = 0;
        b = 0;
    } else if(frag_color_type_test <= 3.1f){
        r = 0;
        g = 0;
        b = 1;
    } else if(frag_color_type_test <= 4.1f){
        r = 1;
        g = 1;
        b = 0;
    } else if(frag_color_type_test <= 5.1f){
        r = 0;
        g = 1;
        b = 1;
    } else if(frag_color_type_test <= 6.1f){
        r = 1;
        g = 0;
        b = 1;
    } else {
        r = 1;
        b = 1;
        g = 1;
    }
    diffuse_material_temp.m_sampler.x = r;
    diffuse_material_temp.m_sampler.y = g;
    diffuse_material_temp.m_sampler.z = b;

    // Lighting
    vec3 result = vec3(0.0f);

    // Directional
    for(int i = 0; i <= active_dirlight_qty; i++) {
        result += calc_directional_light_no_texture(dirlight[i], diffuse_material_temp, scenelight, normalized_frag_cube_normals, view_direction);
    }

    // Point
    for(int i = 0; i <= active_pointlight_qty; i++){
        result += calc_point_light_no_texture(pointlight[i], diffuse_material_temp, scenelight, normalized_frag_cube_normals, view_direction, fragment_world_position);
    }

    if(result.x == 0.0f && result.y==0.0f && result.z==0.0f){
       result = scenelight.ambient  * diffuse_material_temp.m_sampler;
    }

    fragment_color = vec4(result, 1.0);
}

// Function Definitions
vec3 calc_directional_light_no_texture(DirectionalLight dirlight, 
                                       DiffuseMaterial diffuse_material,
                                       SceneLight scenelight, 
                                       vec3 normalized_frag_cube_normals, 
                                       vec3 view_direction){
    
    vec3 light_direction = normalize(dirlight.direction);
    vec3 halfway_btwn_view_and_light_dir = normalize(light_direction + view_direction);

    // Diffuse
    float diffuse_impact = max(dot(normalized_frag_cube_normals, light_direction), 0.0);

    // Combine
    vec3 ambient = scenelight.ambient  * diffuse_material.m_sampler;
    vec3 diffuse = scenelight.diffuse  * diffuse_impact * diffuse_material.m_sampler;

    return (ambient + diffuse);
} 

vec3 calc_point_light_no_texture(PointLight pointlight, 
                                 DiffuseMaterial diffuse_material,
                                 SceneLight scenelight,                       
                                 vec3 normalized_frag_cube_normals, 
                                 vec3 view_direction,                                 
                                 vec3 fragment_position){
    
    vec3 light_direction = normalize(pointlight.position - fragment_position);
    vec3 halfway_btwn_view_and_light_dir = normalize(light_direction + view_direction);
    
    // Diffuse
    float diffuse_impact = max(dot(normalized_frag_cube_normals, light_direction), 0.0);
    
    // Attenuation
    float distance_to_light = length(pointlight.position - fragment_position);
    float attenuation = 1.0 / (pointlight.constant + pointlight.linear * distance_to_light + pointlight.quadratic * (distance_to_light * distance_to_light));    

    // Combine
    vec3 ambient  = scenelight.ambient  * diffuse_material.m_sampler;
    vec3 diffuse  = scenelight.diffuse  * diffuse_impact * diffuse_material.m_sampler;
   
    ambient  *= attenuation;
    diffuse  *= attenuation;

    return (ambient + diffuse);
} 