#version 330 core
// Vertex Shader

layout (location = 0) in vec3 model_position;
layout (location = 1) in vec3 model_normals;
layout (location = 2) in vec2 tex_coords;
layout (location = 3) in vec3 in_tangent;
layout (location = 4) in vec3 in_bitangent;

// Requires a normal mapping material (set in fragment)
// Lighting conversion to tangent space is done in fragment

// Global uniforms
layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

layout (std140) uniform uniform_camera_world_position{
    vec3 camera_world_position;
};

// Input 
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

// Output
out vec3 tangent_camera_position;
out vec3 tangent_fragment_position;
out vec2 fragment_tex_coords;
out mat3 fragment_tbn_matrix;

// Function Definitions
mat3 calc_tbn_matrix(mat3 normal_matrix, vec3 model_normals, vec3 tangent_vec);

void main(){
   
    // TBN Matrix
    fragment_tbn_matrix = calc_tbn_matrix(normal_matrix, model_normals, in_tangent);

    // Output
    vec3 fragment_position = vec3(model_matrix * vec4(model_position, 1.0)); // World space 
    fragment_tex_coords = tex_coords;
    tangent_camera_position = fragment_tbn_matrix * camera_world_position;
    tangent_fragment_position = fragment_tbn_matrix * fragment_position;
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(model_position, 1.0);
    
}

mat3 calc_tbn_matrix(mat3 normal_matrix, vec3 model_normals, vec3 tangent_vec){

    vec3 t = normalize(normal_matrix * tangent_vec);
    vec3 n = normalize(normal_matrix * model_normals);    
    t = normalize(t - dot(t, n) * n);
    vec3 b = cross(n, t);

    // Check for right handedness (TBN must form a right handed coordinate
    // system.  Some models will have symmetric UV's.  This causes the 
    // 'T' to be oriented the wrong way.  The fix is simply to invert the 
    // 'T'.
    if(dot(cross(n, t), b) < 0.0f){
        t = t * -1.0f; 
    }

    mat3 tbn_matrix = transpose(mat3(t, b, n));
    return tbn_matrix;
};