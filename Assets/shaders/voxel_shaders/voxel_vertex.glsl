#version 330 core
layout (location = 0) in vec4 cube_position; // contains world position & block type (w)
layout (location = 1) in vec3 cube_normals;

// Global uniforms
layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

// ************************ EXTREMELY IMPORTANT ***************************
// All shaders are working in view space.  The voxel shader is working
// in world space.  The normal matrix supplied does not take into account
// the view matrix.  The normal matrix for a voxel is created when the 
// Chunk is initialized.  This needs to be updated to take into account
// the view matrix.  You need to update the voxel renderer as well.  Right
// now an identify matrix is being used to bypass this issue.
// *************************************************************************

uniform mat4 model_matrix;
uniform mat3 normal_matrix;

out vec3 fragment_world_position; 
out vec3 frag_cube_normals;
out float frag_color_type_test;

void main(){	
    fragment_world_position = vec3(model_matrix * vec4(cube_position.xyz, 1.0)); // World Space
    gl_Position = projection_matrix * view_matrix * vec4(fragment_world_position, 1.0);   
    frag_cube_normals = normal_matrix * cube_normals; // World Space (World space or view space here is impacted by how the normal matrix is made (in render system))
    frag_color_type_test = cube_position.w;
}