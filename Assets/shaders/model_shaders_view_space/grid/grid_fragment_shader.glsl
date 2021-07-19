#version 330 core
#define MAXIMUM_DIR_LIGHTS 1
#define MAXIMUM_POINT_LIGHTS 1
// Fragment Shader

struct DiffuseMaterial {
    sampler2D m_sampler;
};

struct DirectionalLight {
    vec3 direction;
};

struct SceneLight {
    vec3 ambient;
    vec3 diffuse;
    // vec3 specular; 
};

// Global Uniforms
layout (std140) uniform uniform_camera_world_position{
    vec3 camera_world_position;
};

// Shader Uniforms
uniform DiffuseMaterial diffuse_material;
uniform SceneLight scenelight;

uniform int active_dirlight_qty;
uniform DirectionalLight dirlight[MAXIMUM_DIR_LIGHTS];

// Vertex Variables
in vec3 frag_model_normals;
in vec3 fragment_world_position;
in vec2 fragment_tex_coords;

// Output
out vec4 fragment_color;

// Function Definitions
vec3 calc_directional_light(DirectionalLight dirlight, 
                            DiffuseMaterial diffuse_material,
                            SceneLight scenelight, 
                            vec3 normalized_frag_model_normals, 
                            vec3 view_direction, 
                            vec2 fragment_tex_coords);

// Shader
void main() {
    
    vec3 normalized_frag_model_normals = normalize(frag_model_normals);
    vec3 view_direction = normalize(camera_world_position - fragment_world_position);

    // Lighting
    vec3 result = vec3(0.0f);
    
    // Directional
    for(int i = 0; i <= active_dirlight_qty; i++) {
        result += calc_directional_light(dirlight[i], diffuse_material, scenelight, normalized_frag_model_normals, view_direction, fragment_tex_coords);
    }
    
    fragment_color = vec4(result, 1.0);
};

// Function Definitions
vec3 calc_directional_light(DirectionalLight dirlight, 
                            DiffuseMaterial diffuse_material,
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
            
    return (ambient + diffuse);
}  
