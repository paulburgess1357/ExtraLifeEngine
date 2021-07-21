#version 330 core
// Vertex Shader
// Positional Lights
// OGL4 Shader Language Cookbook Pg. 112
// Pg. 86 for general light diagram
// Note: No attenuation or anything is taken into account with this example.

layout (location = 0) in vec3 vertex_position;
layout (location = 1) in vec3 vertex_normal;

// =============== Definitions ============

// ======== Structure Definitions =========
struct LightInfo {
    vec3 light_position_in_world;
    vec3 ambient_light_intensity;
    vec3 diffuse_specular_light_intensity;
};

// Note that the refectivity is really the color of the cube for these examples
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
uniform LightInfo light_info[2];
uniform MaterialInfo material_info;

// Matrices
// Normal matrix already multiplied by model matrix before shader
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

// Output
out vec3 calculated_frag_color;

// ========= Function Prototypes ==========
// *** Pay close attention to out variables! ***
void convert_norm_pos_to_eye_space(out vec3 out_vertex_position, out vec3 out_vertex_normal);
vec3 phong_lighting_from_pos_light_array(int subset, vec3 vertex_position_eye_space, vec3 vertex_normal_eye_space);


// ================== Main =================
void main(){	

    // Convert cube normals and cube position to view space (eye/camera space)
    // Note that the model matrix has already been multiplied by the view matrix by the time its sent to the shader (for normal matrix calculation)
    vec3 vertex_position_eye;
    vec3 vertex_normal_eye;
    convert_norm_pos_to_eye_space(vertex_position_eye, vertex_normal_eye);
    
    calculated_frag_color = vec3(0.0f);
    for(int i = 0; i < 2; i++){
        calculated_frag_color += phong_lighting_from_pos_light_array(i, vertex_position_eye, vertex_normal_eye);
    }
   
    // Convert vertex position to clip space for fragment shader
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex_position, 1.0);
}


// ========= Function Definitions ===========
void convert_norm_pos_to_eye_space(out vec3 out_vertex_position, out vec3 out_vertex_normal){  
    out_vertex_position = (view_matrix * model_matrix * vec4(vertex_position, 1.0)).xyz;
    out_vertex_normal = normalize(normal_matrix * vertex_normal);
}

vec3 phong_lighting_from_pos_light_array(int subset, vec3 vertex_position_eye_space, vec3 vertex_normal_eye_space){

    // Convert light position to eye space & get direction
    vec3 light_position_eye = vec3(view_matrix * vec4(light_info[subset].light_position_in_world, 1.0));
    vec3 light_direction_from_surface_to_lightsource = normalize(light_position_eye - vertex_position_eye_space);

    // Lighting Calculations
    // The value here gives us a scalar for how strong our light is (if light_dir and vertex_normals were at 90 degees, the result would be zero): pg 80
    float light_dir_to_normals_dot = max(dot(light_direction_from_surface_to_lightsource, vertex_normal_eye_space), 0.0f);

    // Ambient
    vec3 ambient_light = light_info[subset].ambient_light_intensity * material_info.ambient_reflectivity;

    // Diffuse
    vec3 diffuse_light = material_info.diffuse_reflectivity * light_dir_to_normals_dot;

    // Specular
    vec3 specular_light = vec3(0.0f);
    
    // When light_dir_to_normals_dot is greater than 0, it means we have some lighting in effect from our lightsource to our object.
    if(light_dir_to_normals_dot > 0){
        vec3 vector_towards_viewer = normalize(-vertex_position_eye_space.xyz);
        vec3 vector_of_perfect_reflection = reflect(-light_direction_from_surface_to_lightsource, vertex_normal_eye_space); 
        specular_light = material_info.specular_reflectivity * pow(max(dot(vector_of_perfect_reflection, vector_towards_viewer), 0.0f), material_info.shininess);
    }

    // Combine lights (Note that diffuse and specular are multiplied by the intensity)
    return ambient_light + (diffuse_light + specular_light) * light_info[subset].diffuse_specular_light_intensity;

}