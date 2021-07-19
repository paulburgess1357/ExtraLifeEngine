#version 330 core
// Vertex Shader
layout (location = 0) in vec3 cube_position;
layout (location = 1) in vec3 cube_normals;

// =============== Definitions ============
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
LightInfo light_info;
MaterialInfo material_info;

// Matrices
uniform mat4 model_matrix;
uniform mat3 normal_matrix;

// Output
out vec3 calculated_frag_color;

// ================== Main =================
void main(){	

    // Convert light position to view space (eye/camera space)
    // Note that there isn't a need to dot his conversion each time.  Normally we
    // would just calculate this prior to sending to the shader (as the light
    // position in this example is not changing)
    vec3 light_position_eye = vec3(view_matrix * vec4(light_info.light_position_in_world, 1.0));

    // Convert cube normals and cube position to view space (eye/camera space)
    // Note that the model matrix has already been multiplied by the view matrix by the time its sent to the shader (for normal matrix calculation)
    vec3 cube_normals_eye = normalize(vec3(normal_matrix * cube_normals));
    vec3 cube_position_eye = vec3(view_matrix * model_matrix * vec4(cube_position, 1.0));
    vec3 light_direction_from_surface_to_lightsource = normalize(light_position_eye - cube_position_eye);

    // Lighting Calculations
    vec3 ambient_light = light_info.ambient_light_intensity * material_info.ambient_reflectivity;
    // Note that ins the max(dot()) formula, both variables are unit vectors (normalized)
    // Therefore, the lighting is impacted by the angle (so vector magnitude has no impact on dot product)
    // I.e. the dot product of 2 unit vectors equals the cos of the angle.
    float light_dir_to_normals_dot = max(dot(light_direction_from_surface_to_lightsource, cube_normals_eye), 0.0f);
    vec3 diffuse_light = light_info.diffuse_light_intensity * material_info.diffuse_reflectivity * light_dir_to_normals_dot;
    

    // Specular light reflection is highest when there is pure reflection (Page 86: OpenGL4 Shading Language Cookbook.)
    vec3 specular_light = vec3(0.0f);
    // Note that when light_dir_to_normals_dot is greater than 0, it means we have some lighting in effect from our 
    // lightsource to our object.  If it was 0 (or less than 0 : note that its its clamped from above), the angle between 
    // the light direction vector and normal vector is greater than 90 degrees).  This would mean that the incoming light 
    // is coming from within the surface of the object.  This means that no light would reach the outside surface of the object 
    // (Note that if you want lighting here, normal vectors need to be reversed).  See page 83 in OpenGL4 Shading Language Cookbook.

    if(light_dir_to_normals_dot > 0){
        // Note that since we are working in view space, the viewer is located at the origin.  This is why we can simply 
        // negate and normalize the vertex position to get the direction towards the viewer.
        vec3 vector_towards_viewer = normalize(-cube_position_eye.xyz);
        
        // note that the specular effect would be highest when the viewer is aligned with this vector (Page 86: OpenGL4 Shading Language Cookbook.)
        vec3 vector_of_perfect_reflection = reflect(-light_direction_from_surface_to_lightsource, cube_normals_eye); 

        // Note that both vector_of_perfect_reflection and vector_towards_viewer should be normalized (The reflect function returns a normal 
        // vector as both inputs are normalized above).  As such, the same idea as the above takes place.  If its 0 or less than 0, the angle 
        // between the view and the reflection vector is greater than 90 degrees. Again, this would mean the reflection source is coming from 
        // within the object.  Therefore, we wouldn't want a specular effect.
        specular_light = light_info.specular_light_intensity * material_info.specular_reflectivity * pow(max(dot(vector_of_perfect_reflection, vector_towards_viewer), 0.0f), material_info.shininess);
    }

    // Final Light Color
    calculated_frag_color = ambient_light + diffuse_light + specular_light;

    // Convert vertex position to clip space for fragment shader
    gl_Position = projection_matrix * view_matrix * model_matrix * vec4(cube_position, 1.0);
}