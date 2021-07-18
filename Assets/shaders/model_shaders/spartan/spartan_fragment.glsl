#version 330 core
#define MAXIMUM_DIR_LIGHTS 1
#define MAXIMUM_POINT_LIGHTS 1
// Fragment Shader
// Requires a normal mapping material (set here in fragment)
// Lighting conversion to tangent space is done in this shader

struct DiffuseMaterial {
    sampler2D m_sampler;
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

uniform int active_dirlight_qty;
uniform DirectionalLight dirlight[MAXIMUM_DIR_LIGHTS];

//uniform int active_pointlight_qty;
//uniform PointLight pointlight[MAXIMUM_POINT_LIGHTS];

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
                            vec2 fragment_tex_coords,
                            mat3 tbn_matrix);

vec3 calc_point_light(PointLight pointlight, 
                      DiffuseMaterial diffuse_material,
                      SceneLight scenelight,                       
                      vec3 normalized_frag_model_normals, 
                      vec3 view_direction, 
                      vec2 fragment_tex_coords,
                      vec3 fragment_position,
                      mat3 tbn_matrix);

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
        result += calc_directional_light(dirlight[i], 
                                         diffuse_material, 
                                         scenelight, 
                                         normalized_frag_model_normals, 
                                         tangent_view_direction, 
                                         fragment_tex_coords,
                                         fragment_tbn_matrix);
    }

     // Point
//    for(int i = 0; i <= active_pointlight_qty; i++){    
//        result += calc_point_light(pointlight[i], 
//                                   diffuse_material, 
//                                   scenelight, 
//                                   normalized_frag_model_normals, 
//                                   tangent_view_direction, 
//                                   fragment_tex_coords, 
//                                   tangent_fragment_position,
//                                   fragment_tbn_matrix);
//    }
    
    fragment_color = vec4(result, 1.0);
};

// Function Definitions
vec3 calc_directional_light(DirectionalLight dirlight, 
                            DiffuseMaterial diffuse_material,
                            SceneLight scenelight, 
                            vec3 normalized_frag_model_normals, 
                            vec3 view_direction, 
                            vec2 fragment_tex_coords,
                            mat3 tbn_matrix){
    
    DirectionalLight dirlight_tangent = convert_dirlight_to_tangent_space(dirlight, fragment_tbn_matrix);

    vec3 light_direction = normalize(dirlight_tangent.direction);
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
                      vec3 fragment_position,
                      mat3 tbn_matrix){
    
    // Note that pointlight converted has its distance converted into tbn space
    // No other variables in pointlight are converted.
    PointLight pointlight_converted = convert_pointlight_to_tangent_space(pointlight, fragment_tbn_matrix);

    vec3 light_direction = normalize(pointlight_converted.position - fragment_position);
    vec3 halfway_btwn_view_and_light_dir = normalize(light_direction + view_direction);
    
    // Ambient
    vec3 ambient  = scenelight.ambient * vec3(texture(diffuse_material.m_sampler, fragment_tex_coords));

    // Diffuse
    float diffuse_impact = max(dot(normalized_frag_model_normals, light_direction), 0.0);
    vec3 diffuse = scenelight.diffuse * diffuse_impact * vec3(texture(diffuse_material.m_sampler, fragment_tex_coords));
    
    // Attenuation
    float distance_to_light = length(pointlight_converted.position - fragment_position);
    float attenuation = 1.0 / (pointlight_converted.constant + pointlight_converted.linear * distance_to_light + pointlight_converted.quadratic * (distance_to_light * distance_to_light));    
    
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
    //       The object in the shader will have a black outline.
    // Note2: This isn't normalized! If it was, your distance calculations to
    //        will be incorrect!
    pointlight.position = tbn_matrix * pointlight.position;
    return pointlight;

};