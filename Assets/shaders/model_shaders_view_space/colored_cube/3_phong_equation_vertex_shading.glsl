#version 330 core
// Vertex Shader
// Phong Lighting (AKA Gouraud b/c its implemented in vertex shader)
// OGL4 Shader Language Cookbook Pg. 88

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normals;

// =============== Definitions ============

// ======== Structure Definitions =========
struct LightInfo {
    vec3 light_position_in_world;
    vec3 ambient_light_intensity;
    vec3 diffuse_light_intensity;
    vec3 specular_light_intensity; 
};

struct MaterialInfo {
    vec3 ambient_reflectivity;
    vec3 diffuse_reflectivity;
    vec3 specular_reflectivity;
    float shininess;
};

// ============ Global Uniforms ============
layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

// ============ Shader Uniforms ============
// Lights
uniform LightInfo light_info;
uniform MaterialInfo material_info;

// Matrices
// Normal matrix already multiplied by model matrix before shader
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

// Output
out vec3 calculated_frag_color;

// ========= Function Prototypes ==========
// *** Pay close attention to out variables! ***
void convert_norm_pos_to_eye_space(out vec3 out_vertex_position, out vec3 out_vertex_normals);
vec3 phong_lighting(vec3 vertex_position_eye_space, vec3 vertex_normals_eye_space);


// ================== Main =================
void main(){	

    // Convert cube normals and cube position to view space (eye/camera space)
    // Note that the model matrix has already been multiplied by the view matrix by the time its sent to the shader (for normal matrix calculation)
    vec3 vertex_position_eye;
    vec3 vertex_normals_eye;
    convert_norm_pos_to_eye_space(vertex_position_eye, vertex_normals_eye);
    calculated_frag_color = phong_lighting(vertex_position_eye, vertex_normals_eye);
   
    // Convert vertex position to clip space for fragment shader
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1.0);
}


// ========= Function Definitions ===========
void convert_norm_pos_to_eye_space(out vec3 out_vertex_position, out vec3 out_vertex_normals){  
    out_vertex_position = (view_matrix * model_matrix * vec4(vertex_position, 1.0)).xyz;
    out_vertex_normals = normalize(normal_matrix * vertex_normals);
}

vec3 phong_lighting(vec3 vertex_position_eye_space, vec3 vertex_normals_eye_space){

    // Convert light position to eye space & get direction
    vec3 light_position_eye = vec3(view_matrix * vec4(light_info.light_position_in_world, 1.0));
    vec3 light_direction_from_surface_to_lightsource = normalize(light_position_eye - vertex_position_eye_space);

    // Lighting Calculations
    float light_dir_to_normals_dot = max(dot(light_direction_from_surface_to_lightsource, vertex_normals_eye_space), 0.0f);

    // Ambient
    vec3 ambient_light = light_info.ambient_light_intensity * material_info.ambient_reflectivity;
    
    // Diffuse
    vec3 diffuse_light = light_info.diffuse_light_intensity * material_info.diffuse_reflectivity * light_dir_to_normals_dot;
    
    // Specular light
    vec3 specular_light = vec3(0.0f);
    if(light_dir_to_normals_dot > 0){
        vec3 vector_towards_viewer = normalize(-vertex_position_eye_space.xyz);
        vec3 vector_of_perfect_reflection = reflect(-light_direction_from_surface_to_lightsource, vertex_normals_eye_space); 
        specular_light = light_info.specular_light_intensity * material_info.specular_reflectivity * pow(max(dot(vector_of_perfect_reflection, vector_towards_viewer), 0.0f), material_info.shininess);
    }

    // Final Light Color
    return(ambient_light + diffuse_light + specular_light);

}