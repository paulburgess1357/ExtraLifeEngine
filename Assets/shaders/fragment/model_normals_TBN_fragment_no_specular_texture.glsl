#version 330 core
#define MAXIMUM_DIR_LIGHTS 2
#define MAXIMUM_POINT_LIGHTS 8
// Fragment Shader
// Requires a normal mapping material (set here in fragment)
// Lighting conversion to tangent space is done in this shader

struct DiffuseMaterial {
    sampler2D m_sampler;
};

struct SpecularMaterial {
    sampler2D m_sampler;
    float m_shininess;
};

struct NormalMaterial {
    sampler2D m_sampler;
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

// Shader Uniforms
uniform DiffuseMaterial diffuse_material;
uniform NormalMaterial normal_material;

uniform SceneLight scenelight;

uniform int active_dirlight_qty; // Set to -1 during shader initialization
uniform DirectionalLight dirlight[MAXIMUM_DIR_LIGHTS];

uniform int active_pointlight_qty; // Set to -1 during shader initialization
uniform PointLight pointlight[MAXIMUM_POINT_LIGHTS];

in mat3 fragment_tbn_matrix;
in vec3 tangent_camera_position;
in vec3 tangent_fragment_position;
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

vec3 calc_point_light(PointLight pointlight, 
                      DiffuseMaterial diffuse_material,
                      SceneLight scenelight,                       
                      vec3 normalized_frag_model_normals, 
                      vec3 view_direction, 
                      vec2 fragment_tex_coords,
                      vec3 fragment_position);

DirectionalLight convert_dirlight_to_tangent_space(DirectionalLight dirlight, mat3 tbn_matrix);
PointLight convert_pointlight_to_tangent_space(PointLight pointlight, mat3 tbn_matrix);

// Shader
void main() {
    
    // Normal map to normal vector; Transform to range -1, 1
    vec3 normalized_frag_model_normals = normalize(texture(normal_material.m_sampler, fragment_tex_coords).rgb);
    
    // Convert normal to tangent space
    normalized_frag_model_normals = normalize(normalized_frag_model_normals * 2 - 1); 
    vec3 tangent_view_direction = normalize(tangent_camera_position - tangent_fragment_position);
    
    // Lighting
    vec3 result = vec3(0.0f);
    
    // Directional
    for(int i = 0; i <= active_dirlight_qty; i++) {
        result += calc_directional_light(convert_dirlight_to_tangent_space(dirlight[i], fragment_tbn_matrix), 
                                         diffuse_material, 
                                         scenelight, 
                                         normalized_frag_model_normals, 
                                         tangent_view_direction, 
                                         fragment_tex_coords);
    }

    // Point
    for(int i = 0; i <= active_pointlight_qty; i++){    
        result += calc_point_light(convert_pointlight_to_tangent_space(pointlight[i], 
                                   fragment_tbn_matrix), 
                                   diffuse_material, 
                                   scenelight, 
                                   normalized_frag_model_normals, 
                                   tangent_view_direction, 
                                   fragment_tex_coords, 
                                   tangent_fragment_position);
    }

    if(result.x == 0.0f && result.y==0.0f && result.z==0.0f){
       result = scenelight.ambient  * vec3(texture(diffuse_material.m_sampler, fragment_tex_coords)); 
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
    vec3 diffuse = scenelight.diffuse  * diffuse_impact * vec3(texture(diffuse_material.m_sampler, fragment_tex_coords));
            
    return (ambient + diffuse);
}  

vec3 calc_point_light(PointLight pointlight, 
                      DiffuseMaterial diffuse_material,
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
    
    // Attenuation
    float distance_to_light = length(pointlight.position - fragment_position);
    float attenuation = 1.0 / (pointlight.constant + pointlight.linear * distance_to_light + pointlight.quadratic * (distance_to_light * distance_to_light));    
    
    ambient  *= attenuation;
    diffuse  *= attenuation;

    return (ambient + diffuse);
} 

DirectionalLight convert_dirlight_to_tangent_space(DirectionalLight dirlight, mat3 tbn_matrix){
    dirlight.direction = normalize(tbn_matrix * dirlight.direction);
    return dirlight;
};

PointLight convert_pointlight_to_tangent_space(PointLight pointlight, mat3 tbn_matrix){
    // Note: If pointlight is (0, 0, 0), the normalization will cause a division by 0.
    // The object in the shader will have a black outline.
    pointlight.position = normalize(tbn_matrix * pointlight.position);
    return pointlight;

};