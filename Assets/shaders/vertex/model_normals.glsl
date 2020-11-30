#version 330 core
#define MAXIMUM_DIR_LIGHTS 2
#define MAXIMUM_POINT_LIGHTS 2

struct DirectionalLight {
    vec3 direction;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
};

layout (location = 0) in vec3 model_position;
layout (location = 1) in vec3 model_normals;
layout (location = 2) in vec2 tex_coords;
layout (location = 3) in vec3 in_tangent;
layout (location = 4) in vec3 in_bitangent;

// Global uniforms
layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

layout (std140) uniform uniform_camera_world_position{
    vec3 camera_world_position;
};

uniform int active_dirlight_qty; // Set to -1 during shader initialization
uniform DirectionalLight dirlight[MAXIMUM_DIR_LIGHTS];

uniform int active_pointlight_qty; // Set to -1 during shader initialization
uniform PointLight pointlight[MAXIMUM_POINT_LIGHTS];

// Input 
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

// Output
out PointLight tangent_pointlights[MAXIMUM_POINT_LIGHTS];
out DirectionalLight tangent_dirlights[MAXIMUM_DIR_LIGHTS];

out vec3 tangent_camera_position;
out vec3 tangent_fragment_position;
out vec2 fragment_tex_coords;

// Function Definitions
mat3 calc_tbn_matrix(mat3 normal_matrix, vec3 model_normals, vec3 tangent_vec);
PointLight convert_pointlight_to_tangent_space(PointLight pointlight, mat3 tbn_matrix);
DirectionalLight convert_dirlight_to_tangent_space(DirectionalLight dirlight, mat3 tbn_matrix);

void main(){
   
    // TBN Matrix
    mat3 tbn_matrix = calc_tbn_matrix(normal_matrix, model_normals, in_tangent);

    // Calc fragment_position for gl_Position and tangent_fragment_position
    vec3 fragment_position = vec3(model_matrix * vec4(model_position, 1.0)); // World space 

    // Convert Pointlights to Tangent Space
    for(int i = 0; i < active_pointlight_qty; i++){
        tangent_pointlights[i] = convert_pointlight_to_tangent_space(pointlight[i], tbn_matrix);
    }

    // Convert Directional Lights to Tangent Space
    for(int i = 0; i < active_dirlight_qty; i++){
        tangent_dirlights[i] = convert_dirlight_to_tangent_space(dirlight[i], tbn_matrix);
    }          

    // Output (tangent_pointlights and tangent_dirlights are also output)
    fragment_tex_coords = tex_coords;
    tangent_camera_position = tbn_matrix * camera_world_position;
    tangent_fragment_position = tbn_matrix * fragment_position;
    gl_Position = projection_matrix * view_matrix * vec4(fragment_position, 1.0);
    
}

mat3 calc_tbn_matrix(mat3 normal_matrix, vec3 model_normals, vec3 tangent_vec){

    vec3 t = normalize(normal_matrix * tangent_vec);
    vec3 n = normalize(normal_matrix * model_normals);    
    t = normalize(t - dot(t, n) * n);
    vec3 b = cross(n, t);
    mat3 tbn_matrix = transpose(mat3(t, b, n));

    return tbn_matrix;

};

PointLight convert_pointlight_to_tangent_space(PointLight pointlight, mat3 tbn_matrix){
    pointlight.position = normalize(tbn_matrix * pointlight.position);
    return pointlight;

};

DirectionalLight convert_dirlight_to_tangent_space(DirectionalLight dirlight, mat3 tbn_matrix){
    dirlight.direction = normalize(tbn_matrix * dirlight.direction);
    return dirlight;
};