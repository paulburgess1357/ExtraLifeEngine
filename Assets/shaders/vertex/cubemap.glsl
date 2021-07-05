#version 330 core
// Vertex Shader

layout (location = 0) in vec3 cube_position;

// Global uniforms
layout (std140) uniform uniform_matrices {
    mat4 projection_matrix;
    mat4 view_matrix;
};

// Altered translation matrix.  This ensures the skybox does not rotate with
// the player
uniform mat4 view_matrix_no_translation;

// Tex coordinates are vec3 for samplerCube
out vec3 fragment_tex_coords;

void main(){	
    fragment_tex_coords = cube_position;
    vec4 position = projection_matrix * view_matrix_no_translation * vec4(cube_position, 1.0);
    gl_Position = position.xyww;    
}

// Cubemap Notes:
// No texture coords needed for skybox.  The reason is because we can sample
// the cube using the local positions of the cube as its texture coordinates,
// because it is centered on the origin.  Each of its position vectors
// is also a direction vector from the origin.  This direction vector
// is what is needed to get the corresponding texture value at that 
// specific cubes position.  The output tex_coords is the input cubes position.

// They skybox is rendered last based on its depth value.  We trick the 
// depth buffer into believing the skybox has the maximum depth value
// of 1.0.  This causes it to fail the depth test whenever a different
// object is in front of it.  

// Perspective dimension is performed after the vertex shader, and is done
// by dividing gl_Position xyz by its w component.  The resulting z 
// value after the division is the objects depth value.  We can set the 'z'
// component to be equal to the 'w' component before this occurs.  This 
// ensures the resulting depth value is 1 (w/w = 1).  This is the maximum
// depth value.  As a result, the skybox will only be rendered whenever
// there are no objects visible (as it passed the depth test).

// Perspective dimension is done after the vertex shader using the
// gl_Position xyz divided by w.  We set the z comp